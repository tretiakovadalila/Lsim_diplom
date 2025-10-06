//******************************************************************************
//	1. FILE NAME:	   BeamPattern.cpp											
//	2. DESCRIPTIONS:   Beam pattern function approximation for LSim
//  3. PROGRAMMER: 	   V. Shashkin	  								        
//  4. UPDATE HISTORY: 
//		2006/03/23 - Development							
//		2007/04/25 - ReDevelopment for LSim (Taras)							
//******************************************************************************

//#include "stdafx.h"
#include <math.h>

#include <MathConst.h>
#include "L_RadarPar_type.h"
void c_mult(double re1, double im1, double re2, double im2, double *re_out, double *im_out);
void PASim(double teta, double lambda, double d, int N,double *A_re,double *A_im);
void DBF(int nrows, double d, double lambda, double *w, int nbeams, double *A_re, double *A_im, double *arr_teta, double *U);
void PatternPPI(double el,RadarPar_type* pRadarPar,double *U);
double rnd(void);

//********************************************************************************
//																			
//  Function name: beampattern()                                        	
//                                                               			
//  Description:   Approximation of 1 D antenna beam pattern used for Tx pattern 
//                                                               			
//  Arguments:     x - offaxis angle normalysed to beam width                                              					
//
//  Return value:  One way antenna normalized voltage gain ( G(x)/G(0))		
//                                                              	
// ********************************************************************************

// Power gain of the cosine illumination pattern
double beampattern(double teta	/* input angle normalyzed to beam width*/ )
{
	double k = 3.7352;
	double t = k*teta;
	double x = (0.25*PI*PI - t*t);
	double y = PI/4;
	if (fabs(x) > 1e-2) y = 0.25*PI*PI*cos(t) / x;
	return (fabs(y)); //MM 10.11.2006
}

/*-------------------------------------------------------------------------------*/

//********************************************************************************
//																			
//  Function name: beampattern_tx()                                        	
//                                                               			
//  Description:   Tx beam pattern with optional cosecant shape
//                                                               			
//  Return value:  One way antenna normalized voltage gain ( G(x)/G(0))		
//                                                              	
// ********************************************************************************

double beampattern_tx(
					double el,			// target elevation	 (rad)		
					double elbeam,		// beam elevation (rad)
					double elwidth,		// beam 3 dB one way width (rad)
					int	   csc_sign,	// Cosecant beam shape parameters
					double csc_elmin,	
					double csc_elmax	
					)
{
	double g;
double elD=el*R_TO_D, elbeamD=elbeam*R_TO_D,elwidthD=elwidth*R_TO_D,csc_elminD=csc_elmin*R_TO_D,csc_elmaxD=csc_elmax*R_TO_D;
	if (csc_sign==0 || el < csc_elmin) 
	{
		g = beampattern((el - elbeam) / elwidth);
	}
	else
	{
		if(el < csc_elmax) 
		{
			g = beampattern((csc_elmin - elbeam) / elwidth);
			double csce  = 1/sin(el);
			double csce0 = 1/sin(csc_elmin);
			g *= csce / csce0;
		}
		else 
			g =0;
	}
	
	return g;

}
/*-------------------------------------------------------------------------------*/

//********************************************************************************
//																			
//  Function name: ElBeamShape()                                        	
//                                                               			
//  Description:   Calculates tx, rx beams el coverage within 0-45 deg to display on PPI
//					using PatternPPI(), beampattern_tx()
//                                                               			
//    2007/04/25 - ReDevelopment for LSim (Taras)                                                           	
// ********************************************************************************
 
void ElBeamShape(
				  RadarPar_type* pRadarPar, // input radar parameters
				  int n,					// input size of output arrays
				  double el_out[],			// output elevation angles array
				  double gain_tx[],			// output normalized tx pattern gain for each elevation
				  double gain_rx[]			// output normalized rx pattern gain for each elevation
				  )
{

	int nbeams = pRadarPar->n_beams;	
	
	double grx[NEL_MAX];
	double grxmax = 0;
	for(int i=0; i < nbeams; i++)
	{
        grx[i] = pow((double)10.0,  pRadarPar->beam_gain_dB/10);
		if(grx[i]>grxmax) grxmax = grx[i];
	}
	
	for(int j=0; j<n; j++)
	{
		double el = -10*D_TO_R+j*0.5*PI/2./n;
		el_out[j] = el;
		double gain = beampattern_tx(el, pRadarPar->tx_el, pRadarPar->tx_elwidth, pRadarPar->csc_sign, pRadarPar->csc_elmin, pRadarPar->csc_elmax);
		gain_tx[j] = fabs(gain);
		
		double U[NEL_MAX];//
		PatternPPI(el,pRadarPar,U);//out, 

		double gmax=0;
		for(int i=0; i<nbeams; i++)
		{
			gain =  U[i] * grx[i] / grxmax;//

			if(gmax <gain) gmax =gain; 
		}
		gain_rx[j] = gmax*gain_tx[j];//
	}
}
/*-------------------------------------------------------------------------------*/

// This aux function calculates rx elevation beam number nearest to specified "el" value
int elbeam_no(
			 double el, // input angle
			 RadarPar_type* pRadarPar // input radar parameters
			 )
{
	int nbeams = pRadarPar->n_beams;	
	
	double d, dmin = 1e6;
	int beam_no;
	for(int i=0; i < nbeams; i++)
	{
        d = fabs(el-pRadarPar->beam_el[i])/pRadarPar->beam_elwidth;
		if(dmin > d) {dmin = d; beam_no = i;}
	}

	return beam_no;

}

/*-------------------------------------------------------------------------------*/
double deltapattern	// Voltage gain pattern 
			(
			double teta	// input angle normalyzed to beam width
			)
{
	double squint = 0.5;
	double d = 0.707 * (beampattern(teta-squint) - beampattern(teta+squint));
	return d;
}

/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
//********************************************************************************
//  Function name: PASim()                                        	
//  Description:   Calculates normalized signal magnitudes in antenna rows
//				   depend on signal arrival angle relative antenna normal and antenna parameters
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************

 void PASim(double teta,//tgt  
	 double lambda,	//wave length 
	 double d,		//step between rows 
	 int N,			//number of antenna rows
	 double *A_re,	//out, tgt signal magnitude in antenna rows [1:nrows]
	 double *A_im)	//out, tgt signal magnitude in antenna rows [1:nrows]
 {
	double dphase = -TWOPI*d*sin(teta)/lambda;
	double a= cos(teta);
	for (int k=0; k<N; k++) 
	{
		A_re[k]=a*cos(k*dphase)/N;
		A_im[k]=a*sin(k*dphase)/N;
	}
 }

//********************************************************************************
//  Function name: DBF()                                        	
//  Description:   Digital beam former, calculates Sum vector for all receive beams
//					in predetermined position depend on antenna parameters and window function
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************

void DBF(int nrows,			//number of antenna rows 
		 double d,			//step between rows
		 double lambda,		//wave length 
		 double *w,			//illimination function [1:nrows]
		 int nbeams,		//number of output receive beam
		 double *A_re,		//input, tgt signal magnitude in antenna rows [1:nrows]
		 double *A_im,		//input, tgt signal magnitude in antenna rows [1:nrows]
		 double *arr_teta,	//beam steering angles relative antenna normal [1:nbeams] 
		 double *U)			//out, weighted vector sum (voltage scale) for all beams [1:nbeams]
{
	double re_out, im_out;
	for (int k= 0; k<nbeams; k++)
	{
		double dfi=TWOPI*d*sin(arr_teta[k])/lambda;
		double U_re=0, U_im=0;
		for (int j=0; j<nrows; j++)
		{
			c_mult(A_re[j], A_im[j], cos(j*dfi), sin(j*dfi), &re_out, &im_out);
			U_re=U_re + re_out*w[j];
			U_im=U_im + im_out*w[j];
		}
		U[k]=sqrt(U_re*U_re + U_im*U_im);
	}
}
//********************************************************************************
//  Function name: PatternPPI()                                        	
//  Description:   Auxialary function for calculation beam coverage for PPI 
//                 is used in ElBeamShape() function 
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************

void PatternPPI(double el,					//input, tgt elevation, rad 
				RadarPar_type* pRadarPar,	// input radar parameters
				double *U)		//out, array of normalized Sum vector for all elevation beam (voltage scale)
{
	double X[NEL_MAX],A_re[NROWS_MAX],A_im[NROWS_MAX];

	PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
	for (int i=0; i<pRadarPar->n_beams; i++) X[i]=pRadarPar->beam_el[i]-pRadarPar->eltilt;//
	DBF(pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X, U);
}
void PatternDBF(double el,					//input, tgt elevation, rad 
				RadarPar_type* pRadarPar,	// input radar parameters
				double *U)		//out, array of normalized Sum vector for all elevation beam (voltage scale)
{
	double X[NEL_MAX],A_re[NROWS_MAX],A_im[NROWS_MAX];

	PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
	for (int i=0; i<pRadarPar->n_beams; i++) X[i]=pRadarPar->beam_el[i]-pRadarPar->eltilt;//
	DBF(pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X, U);
}


//********************************************************************************
//  Function name: U1b()                                        	
//  Description:   Auxialary function for calculation Sum signal for appointed beam
//					is used in  ElParam() function
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************
double U1b(int Nbeam,		//beam number
		 int nrows,			//number of antenna rows 
		 double d,			//step between rows
		 double lambda,		//wave length 
		 double *w,			//illimination function [1:nrows]
		 int nbeams,		//number of output receive beam
		 double *A_re,		//tgt signal magnitude in antenna rows [1:nrows]
		 double *A_im,
		 double *arr_teta	//beam steering angles relative antenna normal [1:nbeams] 
		 )					//out, wheighted vector sum (voltage scale) for Nbeam beam 
{
	double re_out, im_out;

		double dfi=TWOPI*d*sin(arr_teta[Nbeam])/lambda;
		double U_re=0, U_im=0;
		for (int j=0; j<nrows; j++)
		{
			c_mult(A_re[j], A_im[j], cos(j*dfi), sin(j*dfi), &re_out, &im_out);
			U_re=U_re + re_out*w[j];
			U_im=U_im + im_out*w[j];
		}
	return sqrt(U_re*U_re + U_im*U_im);
}
double PatternDBF0(double el,					//input, tgt elevation, rad 
				RadarPar_type* pRadarPar	// input radar parameters
				)		//out, normalized Sum for 0 elevation beam (voltage scale)
{
	double X[NEL_MAX],A_re[NROWS_MAX],A_im[NROWS_MAX];

	PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
	X[0]=pRadarPar->beam_el[0]-pRadarPar->eltilt;//
return	U1b(0,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);
}

//********************************************************************************
//  Function name:  ElEstimator()                                        	
//  Description:    Calculate estimation of elevation by signal amplitudes in all beams
//					
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************

double ElEstimator(								//output, estimation of elevation (rad) by signal amplitudes in all beams 
				   RadarPar_type* pRadarPar,	// input, radar parameters
				   double *U)					// input, array of signal amplitudes in all receive beams after DBF
{
	int bmax;
	double elest, amax=-100.;
double delMax;
	for (int i=0; i<pRadarPar->n_beams; i++)
	if (amax<U[i]){amax=U[i]; bmax=i;}
	if (bmax==0) 
	{
		elest=0.5*(pRadarPar->beam_el[bmax+1]+pRadarPar->beam_el[bmax])
				+pRadarPar->slope[bmax]*(U[1]-U[0])/(U[0]+U[1]);
delMax = pRadarPar->slope[bmax]*(U[1]-U[0])/(U[0]+U[1])*R_TO_D;
if (fabs(delMax)>0.7)
delMax=delMax;
//if (fabs(elest)>(pRadarPar->beam_el[bmax+1]-pRadarPar->beam_el[bmax])/2) elest=pRadarPar->beam_el[bmax];
		return elest;
	}
	if (bmax==pRadarPar->n_beams-1) 
	{
		elest=0.5*(pRadarPar->beam_el[bmax-1]+pRadarPar->beam_el[bmax])
				+pRadarPar->slope[bmax-1]*(U[bmax]-U[bmax-1])/(U[bmax]+U[bmax-1]);
delMax = pRadarPar->slope[bmax-1]*(U[bmax]-U[bmax-1])/(U[bmax]+U[bmax-1])*R_TO_D;
if (fabs(delMax)>0.7)
delMax=delMax;

		return elest;
	}

	if (U[bmax-1]>=U[bmax+1])
	{
		elest=0.5*(pRadarPar->beam_el[bmax-1]+pRadarPar->beam_el[bmax])
				+pRadarPar->slope[bmax-1]*(U[bmax]-U[bmax-1])/(U[bmax]+U[bmax-1]);
delMax = pRadarPar->slope[bmax-1]*(U[bmax]-U[bmax-1])/(U[bmax]+U[bmax-1])*R_TO_D;
if (fabs(delMax)>0.7)
delMax=delMax;

		return elest;
	}
	else
	{
		elest=0.5*(pRadarPar->beam_el[bmax+1]+pRadarPar->beam_el[bmax])
				+pRadarPar->slope[bmax]*(U[bmax+1]-U[bmax])/(U[bmax]+U[bmax+1]);//
delMax = pRadarPar->slope[bmax]*(U[bmax+1]-U[bmax])/(U[bmax]+U[bmax+1])*R_TO_D;
if (fabs(delMax)>0.7)
delMax=delMax;

		return elest;
	}
}
//********************************************************************************
//  Function name: factorial()                                        	
//  Description:   Auxialary function for factorial calculation 
//					is used in  Taylorwin() function for calculation Taylor weighting factors
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************
double factorial(int n)
{
	double fact=1.;
	for (int i=1; i<=n; i++)
		fact=fact*i;
	return fact;
}
//********************************************************************************
//  Function name: Taylorwin()                                        	
//  Description:   Auxialary function for calculation Taylor weighting factors
//                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************
void Taylorwin(int N, int n, double *w)
{
	int i, k, m;
	double z[21], f[21];
	if (N<2) {w[0]=1; return;}
	if (n<2) {for (int i=0; i<N; i++) w[i]=1; return;}
	if (n>20) n=20;
	const double SLT[]={0,15,20,25,30,35,40,45,50,52,55,57,60,62,65,67,70,72,75,77,80};
	double g=pow(10, SLT[n]/20.);
	double At=log(g+sqrt(g*g-1))/PI;
	for (i=0; i<n-1; i++)
		z[i]=n*sqrt((At*At+(i+0.5)*(i+0.5))/(At*At+(n-0.5)*(n-0.5)));

	for (i=0; i<n-1; i++)
	{
		double ff1=double(factorial(n-1))/factorial(n+i);

		double ff2=double(factorial(n-1)/factorial(n-i-2));
		double ff=ff1*ff2;
		f[i]=ff;
		for (m=0; m<n-1; m++)
			f[i] = f[i] * (1-(i+1)*(i+1)/(z[m]*z[m]));
	}
	double x;
	for (k=0; k<N; k++)
	{
		x=-0.5+k/(N-1.);
		w[k]=1.;
		for (i=0; i<n-1; i++)
			w[k]=w[k]+2*f[i]*cos(2*PI*(i+1)*x);
	}
	double w0=1;
	for (i=0; i<n-1; i++) w0+=2*f[i];

	for (k=0; k<N; k++) w[k] = w[k]/w0;
}

//********************************************************************************
//  Function name: ElParam()                                        	
//  Description:   Calculation of widthes, losses, slopes for all appointed Rx beams formed with using DBF, 
//					
//  Remark: Function is called only by initialization or control parameters change from menu                                                               			
//    2007/04/25 - Development for LSim (Taras)                                                           	
// ********************************************************************************
void ElParam(RadarPar_type* pRadarPar,	// input radar parameters
			double *Elw,				// out, width of elevation beams (deg)
			double *Loss)				// out, loss of elevation beams (level ~3dB)
{
	double X[NEL_MAX],A_re[NROWS_MAX],A_im[NROWS_MAX];//,U[NEL_MAX]
	double el;
	int i,j,n=400;//k,
	double f[400];
	double fm=0,elm=0;
	double eldown, elup, elwidth;

//================== Calculation of weighting factors ============================================
	Taylorwin(pRadarPar->nrows, pRadarPar->window_function, pRadarPar->weight_Taylor);
	double s=0;
	for (int j=0; j<pRadarPar->nrows; j++)
	s=s+pRadarPar->weight_Taylor[j]*pRadarPar->weight_Taylor[j];
	for (int j=0; j<pRadarPar->nrows; j++)
	pRadarPar->weight_Taylor[j]=pRadarPar->weight_Taylor[j]*sqrt(pRadarPar->nrows/s);



	for (i=0; i<pRadarPar->n_beams; i++) X[i]=pRadarPar->beam_el[i]-pRadarPar->eltilt;//

	for (i=0; i<pRadarPar->n_beams; i++)
	{
		fm=-10;elm=0;
		for (j=-n/2; j<n/2; j++)
		{
			el=j*8./n*D_TO_R+pRadarPar->beam_el[i];
			PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
			
			f[j+n/2]=U1b(i,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);//, U
			if (fm<f[j+n/2]) {fm=f[j+n/2]; elm=el;};
		}
		for (j=0; j<n/2; j++) 
			if (f[j]>0.707*fm) {eldown=(j-n/2)*8./n*D_TO_R+pRadarPar->beam_el[i]; break;}
		for (j=n/2; j<n; j++) 
			if (f[j]<0.707*fm) {elup=(j-n/2)*8./n*D_TO_R+pRadarPar->beam_el[i];	break;}
        elwidth=(elup-eldown);
		Elw[i]=elwidth;						//output, width of every beam (deg) 
		Loss[i]=20*log10(fm);				//output, loss in every beam (dB)
		pRadarPar->loss_dB[i]=Loss[i];		//output, loss in every beam (dB)
        pRadarPar->beam_elwidth=1;	//output, width of every beam (deg)
	}
//=========== slopes calculation ==========================		
	double a0, a1;
	for (i=0; i<pRadarPar->n_beams; i++) X[i]=pRadarPar->beam_el[i]-pRadarPar->eltilt;//

	double elstep=0.1*LAMBDAF/(pRadarPar->nrows*pRadarPar->drows);
	for (i=0; i<pRadarPar->n_beams-1; i++)
	{
		el=pRadarPar->beam_el[i] + 0.5*(pRadarPar->beam_el[i+1]-pRadarPar->beam_el[i])-3*elstep;//

		PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
			
		a0=U1b(i,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);//, U
		a1=U1b(i+1,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);//, U
		double mr1=(a1-a0)/(a0+a1);
		el=pRadarPar->beam_el[i] + 0.5*(pRadarPar->beam_el[i+1]-pRadarPar->beam_el[i])+ 3*elstep;//

		PASim(el-pRadarPar->eltilt, LAMBDAF, pRadarPar->drows, pRadarPar->nrows,A_re,A_im);//
			
		a0=U1b(i,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);//, U
		a1=U1b(i+1,pRadarPar->nrows, pRadarPar->drows , LAMBDAF, pRadarPar->weight_Taylor, pRadarPar->n_beams,A_re,A_im, X);//, U
		double mr2=(a1-a0)/(a0+a1);

		double sl=(mr2-mr1)/(6*elstep);
		pRadarPar->slope[i]=1/sl;	//output, array of slope for every beam 
	}
}



