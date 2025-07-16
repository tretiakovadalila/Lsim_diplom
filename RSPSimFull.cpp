#include <iostream>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <QVector>
#include <vector>
#include <QProgressDialog>
#include <QFont>
#include <QCoreApplication>

#include "L_RadarPar_type.h"
#include "L_Head_type.h"
#include "AntPosition_type.h"
#include "L_RadSimOut_type.h"
#include "L_RspOut_type.h"
#include "ClutSimPar_type.h"
#include "TerMap_type.h"
#include "mainwindow.h"
#include "rspSimFull.h"
#include <fftw3.h>

using namespace std;

#define SIGNAL_COMPRESSION_OPT

#define QUANTITY_DWELL	9
#define MAX_NSIGNAL		1500
#define NRG_MAXALL		9504

// external functions declaration
extern void c_mult(double re1, double im1, double re2, double im2, double *re_out, double *im_out);
extern double qrnr(void);

extern void ClutGrA(double az, ClutMap_type *pCl, Head_type *pHead, ClutGrArray *pClA);

extern ClutMap_type *pCl;
extern ClutGrArray  *pClA;

extern double beampattern(double teta);	// input angle normalyzed to beam width
extern double atmloss(double elevation, double range, double freq);
extern double rainloss(double rain_rate, double rain_h, double rain_rmin, double rain_rmax, double elevation, double freq, int pol);

extern void Chebyshev_window(int n_iwindow,int WF_SideLobe,double *weight_FFT);
extern void RadarParInit(RadarPar_type* pRadarPar,int beam_el_change);

//------------- only for debugging - profiling --------------
extern int  dtmcs(int mode);
int timer0, timer01, timer02, timer03, timer04, timer05, timer1, timer100, timer10, timer11, timer2, timer20, timer21, timer3, timer4, timer40, timer5, timer50;
int timer6, timer60, timer601, timer61, timer7, timer8, timer80, timer81, timer82, timer83, timer84, timer85, timer86;

//----------- only debugging ----------------
int MSIZEH, MSIZEW;

static double PRI;				//sec
static double lambda;

int CFAR_n=32;
int CFAR_m=14;
double CFAR_thrlev=24.;

// vector<vector<vector<float>>> rsp_matrix_noise_re;
// vector<vector<vector<float>>> rsp_matrix_noise_im;

static float rsp_matrix_noise_re[QUANTITY_DWELL][NDF_MAX][NRG_MAXALL];
static float rsp_matrix_noise_im[QUANTITY_DWELL][NDF_MAX][NRG_MAXALL];


#ifdef DBF_ON
static double re_dbf[NEL_MAX*NROWS_MAX], im_dbf[NEL_MAX*NROWS_MAX];
#endif

double  FREF = 3000000.; // Reference frequency in Hz
double  CLC		= 1./FREF; // LSB of PRI and Range in sec
double  RG_STEP	= 0.5*C_LIGHT*CLC;			// range gate step in m

// double MAX_DISTANCE=(int)(100.e3/RG_STEP);

//double tblank_sec = TPULSE_SEC[0]+TB_CLK[0]/FREF;//tpulse_sec+TB_CLK[0]/FREF (total blank = tpulse+blank after end of transmit pulse)

int    TPULSE_CLK[]	= {int(FREF*TPULSE_SEC[0]), int(FREF*TPULSE_SEC[1]), int(FREF*TPULSE_SEC[2]), int(FREF*TPULSE_SEC[3]),
                         int(FREF*TPULSE_SEC[4]), int(FREF*TPULSE_SEC[5]), int(FREF*TPULSE_SEC[6]), int(FREF*TPULSE_SEC[7]), int(FREF*TPULSE_SEC[8])};

int	 TBLANK_CLK[]	= {TPULSE_CLK[0]+TB_CLK[0], TPULSE_CLK[1]+TB_CLK[1], TPULSE_CLK[2]+TB_CLK[2], TPULSE_CLK[3]+TB_CLK[3],
                          TPULSE_CLK[4]+TB_CLK[4], TPULSE_CLK[5]+TB_CLK[5], TPULSE_CLK[6]+TB_CLK[6], TPULSE_CLK[7]+TB_CLK[7], TPULSE_CLK[8]+TB_CLK[8]};

int	 PRI_SET[]		= {int(240e-6*FREF),int(276e-6*FREF),int(316e-6*FREF),int(350e-6*FREF),
                      int(3133.33e-6*FREF),int(3133.33e-6*FREF),int(500e-6*FREF),int(550e-6*FREF),int(600e-6*FREF)};

int	 pri_set[9] = {PRI_SET[0],PRI_SET[1],PRI_SET[2],PRI_SET[3],PRI_SET[4],PRI_SET[5],PRI_SET[6],PRI_SET[7],PRI_SET[8]};		//in CLK
int pri = PRI_SET[0];		// current pulse repetition interval in CLK

double tpulse_sec[9] = {int(FREF*TPULSE_SEC[0]), int(FREF*TPULSE_SEC[1]), int(FREF*TPULSE_SEC[2]), int(FREF*TPULSE_SEC[3]), int(FREF*TPULSE_SEC[4]), int(FREF*TPULSE_SEC[5]), int(FREF*TPULSE_SEC[6]),int(FREF*TPULSE_SEC[7]), int(FREF*TPULSE_SEC[8])};
int    tpulse_clk[9] = {TPULSE_SEC[0]+TB_CLK[0]/FREF, TPULSE_SEC[1]+TB_CLK[1]/FREF, TPULSE_SEC[2]+TB_CLK[2]/FREF, TPULSE_SEC[3]+TB_CLK[3]/FREF,TPULSE_SEC[4]+TB_CLK[4]/FREF, TPULSE_SEC[5]+TB_CLK[5]/FREF, TPULSE_SEC[6]+TB_CLK[6]/FREF, TPULSE_SEC[7]+TB_CLK[7]/FREF, TPULSE_SEC[8]+TB_CLK[8]/FREF};

//double tblank_sec[9] = {TPULSE_CLK[0]+TB_CLK[0], TPULSE_CLK[1]+TB_CLK[1], TPULSE_CLK[2]+TB_CLK[2], TPULSE_CLK[3]+TB_CLK[3],TPULSE_CLK[4]+TB_CLK[4], TPULSE_CLK[5]+TB_CLK[5], TPULSE_CLK[6]+TB_CLK[6],TPULSE_CLK[7]+TB_CLK[7], TPULSE_CLK[8]+TB_CLK[8]};

static __declspec (align(16))  float refsignal_re[QUANTITY_DWELL*MAX_NSIGNAL];
static __declspec (align(16))  float refsignal_im[QUANTITY_DWELL*MAX_NSIGNAL];
static __declspec (align(16))  float refsignal_amp[QUANTITY_DWELL*MAX_NSIGNAL];
static __declspec (align(16))  float refsignal_fi[QUANTITY_DWELL*MAX_NSIGNAL];

const int type_signal[QUANTITY_DWELL]={ 2, 2, 2, 2, 1, 1, 2};//0 - LFM, 1 - LFM+Hamming, 2 - NLFM

static int n_window[QUANTITY_DWELL];
static double weight_FFT[QUANTITY_DWELL][NDF_MAX];

vector<vector<float>> cnr_re;
vector<vector<float>> cnr_im;

vector<float> cnr1_re;
vector<float> cnr1_im;

vector<vector<float>> rain_signal_re;
vector<vector<float>> rain_signal_im;

static float reciever_noise_re[NROWS_MAX][NPULSES_MAX][NRG_MAXALL];
static float reciever_noise_im[NROWS_MAX][NPULSES_MAX][NRG_MAXALL];

static float reciever_noise_re_beam[NPULSES_MAX][NRG_MAXALL];
static float reciever_noise_im_beam[NPULSES_MAX][NRG_MAXALL];

vector<vector<float>> init_noise_re;
vector<vector<float>> init_noise_im;

Head_type		gHead = FHEAD;
RadarPar_type	gRadarPar	= RADARPAR;
TerMap_type gTerMap;
double i_angle;

static __declspec (align(16)) float FIR_coefficient[QUANTITY_DWELL][2*NDF_MAX*NDF_MAX];
static __declspec (align(16)) float FIR_input[2*NDF_MAX];
static __declspec (align(16)) double FIR_output[2*NDF_MAX];

//---------------------------------------

RSPSimFull::RSPSimFull(QObject *parent):QObject(parent) {

}

RSPSimFull::~RSPSimFull() {

}

void Cholesky_complex(double * in_re,double * in_im, double *out_re, double *out_im, int N){

    for(int i0=0; i0<N; i0++) in_re[i0*N+i0]=in_re[i0*N+i0]+1.e-5;//1.e-10;//for positive defined matrix

    out_re[0]=sqrt(in_re[0]);//first element - always real
    out_im[0]=0.;

    for(int i=1; i<N; i++){
        for(int j=0; j<i; j++){
            double sum0_re=0., sum0_im=0.;
            for(int k=0; k<j; k++){

                //complex conjugate
                sum0_re += out_re[i*N+k]*out_re[j*N+k]+out_im[i*N+k]*out_im[j*N+k];
                sum0_im += out_im[i*N+k]*out_re[j*N+k]-out_re[i*N+k]*out_im[j*N+k];
            }
            double num_re=in_re[i*N+j]-sum0_re;			double num_im=in_im[i*N+j]-sum0_im;
            double denom0=out_re[j*N+j]*out_re[j*N+j]+out_im[j*N+j]*out_im[j*N+j];

            out_re[i*N+j]=(num_re*out_re[j*N+j]+num_im*out_im[j*N+j])/denom0;
            out_im[i*N+j]=(num_im*out_re[j*N+j]-num_re*out_im[j*N+j])/denom0;
        }

        double sum1=0.;
        for (int k=0; k<i; k++) sum1 += out_re[i*N+k]*out_re[i*N+k]+out_im[i*N+k]*out_im[i*N+k];
        if((in_re[i*N+i] - sum1)<0)
            out_re[i*N+i]=0.;//mistake
        else out_re[i*N+i]=sqrt(in_re[i*N+i] - sum1);
        out_im[i*N+i]=0.;
    }
}

int FindElevationAngle(
    double r,		// input range
    double h,		// input altitude
    double ha,		// antenna height
    double *elout	// output elevation angle of point
    ){
    if(r <= fabs(h-ha)) return (-1);

    double el  = asin((2*R_EFF*(h-ha) + h*h - ha*ha -r*r) / (2*r*(R_EFF+ha)));
    *elout = el;

    // visibility range
    double r_visib = sqrt(2*R_EFF*ha + ha*ha) + sqrt(2*R_EFF*h + h*h);
    if (r > r_visib) return 0; // point is invisible
    else             return 1;
}

void RspSimFullInit(Head_type* pHead, RadarPar_type* pRadarPar,	ClutSimPar_type* pClutSimPar,
                    TerMap_type *pTerMap, double i_angle, double i_freq){

    // rsp_matrix_noise_re.clear();
    // rsp_matrix_noise_im.clear();

    cnr1_re.clear();
    cnr1_im.clear();

    init_noise_re.clear();
    init_noise_im.clear();

    FREF = i_freq;

    lambda=C_LIGHT/pHead->txf;

#ifdef DBF_ON
    for (int ibeam=0; ibeam<pHead->n_beams; ibeam++){
        //28.07.2010 double dfi=(2*PI)*(pRadarPar->drows)*sin(pRadarPar->beam_el[ibeam] /*- pRadarPar->eltilt*/)/lambda;
        double dfi=(2*PI)*(pRadarPar->drows)*sin(pRadarPar->beam_el[ibeam] - pRadarPar->eltilt)/lambda;

        for(int irow=0; irow < pRadarPar->nrows; irow++){
            re_dbf[ibeam*pRadarPar->nrows+irow] =cos((irow-pRadarPar->drows/2)*dfi)*pRadarPar->weight_Taylor[irow];
            im_dbf[ibeam*pRadarPar->nrows+irow] =sin((irow-pRadarPar->drows/2)*dfi)*pRadarPar->weight_Taylor[irow];
        }
    }
#endif

    //-------------------------- Transmit signals init ---------------------
    double BW=pRadarPar->fm_deviation;//FM deviation, Hz

    for(int idwell=0;idwell<QUANTITY_DWELL;idwell++){
        float *re_PCsignal0=refsignal_re+idwell*MAX_NSIGNAL;
        float *im_PCsignal0=refsignal_im+idwell*MAX_NSIGNAL;
        float *amp_signal=refsignal_amp+idwell*MAX_NSIGNAL;
        float *fi_signal=refsignal_fi+idwell*MAX_NSIGNAL;

        int Nsignal0=tpulse_clk[idwell];
        double Timpulse=Nsignal0*CLC;

        switch(type_signal[idwell]){
        case 0:{//LFM
            for(int irange=0;irange<Nsignal0;irange++){
                double t1=(irange-Nsignal0/2+0.5)*CLC;

                amp_signal[irange]=(float)1.;
                fi_signal[irange]=(float)(PI*t1*t1*BW/Timpulse);

                re_PCsignal0[irange]=(float)cos(-fi_signal[irange]);
                im_PCsignal0[irange]=(float)sin(-fi_signal[irange]);
            }
        }break;
        case 1:	{//LFM+Hamming
            for(int irange=0;irange<Nsignal0;irange++){
                double t1=(irange-Nsignal0/2+0.5)*CLC;

                amp_signal[irange]=1.;//transmit signal for target modeling
                fi_signal[irange]=(float)(PI*t1*t1*BW/Timpulse);

                double amp0=(float)(0.54-0.46*cos(2*PI*irange/(Nsignal0-1)));
                re_PCsignal0[irange]=(float)(amp0*cos(-fi_signal[irange]));//for rsp
                im_PCsignal0[irange]=(float)(amp0*sin(-fi_signal[irange]));
            }
        }	break;
        case 2:{//NLFM -  ?40-dB Taylor compressed pulse response
            const double K[7]={-0.1145, 0.0396, -0.0202, 0.0118, -0.0082, 0.0055, -0.0040};
            double *freq=new double[Nsignal0];	double *phase=new double[Nsignal0];

            phase[0]=0.;
            for(int irange=0;irange<Nsignal0;irange++){

                double _t_T=-0.5+irange/(Nsignal0-1.);
                double sum0=0.;
                for(int i0=0;i0<7;i0++) sum0+=K[i0]*sin(2*PI*(i0+1)*_t_T);
                freq[irange]  = BW*(_t_T+sum0);

                // frequency integration to get a phase vs time
                if(irange>0) phase[irange]=phase[irange-1] + PI*(freq[irange-1]+freq[irange])*CLC;
            }

            double min0=phase[0];
            for(int irange=0;irange<Nsignal0;irange++){if(min0>phase[irange]) min0=phase[irange];}
            for(int irange=0;irange<Nsignal0;irange++)	phase[irange]-=min0;

            for(int irange=0;irange<Nsignal0;irange++){
                amp_signal[irange]=(float)1.;
                fi_signal[irange]=(float)phase[irange];

                re_PCsignal0[irange]=(float)cos(-phase[irange]);
                im_PCsignal0[irange]=(float)sin(-phase[irange]);
            }

            delete [] freq;	delete [] phase;
        }break;
        default:	break;
        }
    }

//--------------------- Surface clutter init ---------------------
#if 0
    double _2_PI_lambda=(2*PI)/lambda;
    double _2_PI_lambda_k_rDmin=_2_PI_lambda*(2.*2.);//for current model - all clutters have Doppler speed = 2 m/sec

    for(int idwell=0;idwell<QUANTITY_DWELL;idwell++){

        float *re_ptr0=clutter_signal_re+idwell*MAX_NSIGNAL*NPULSES_MAX;
        float *im_ptr0=clutter_signal_im+idwell*MAX_NSIGNAL*NPULSES_MAX;

        float *fi_signal0=refsignal_fi+idwell*MAX_NSIGNAL;

        int Nsignal0=pRadarPar->tpulse_clk[idwell];
        int n_pulses0=pRadarPar->npulses[idwell] - pRadarPar->nfill_pulses[idwell];

        PRI=pRadarPar->pri_set[idwell]*CLC;

        double t0=0;//time - sec
        for(int ipulse=0;ipulse<n_pulses0;ipulse++){

            double k0=-_2_PI_lambda_k_rDmin*t0;
            double k1=_2_PI_lambda_k_rDmin*CLC;

            for(int irange=0;irange<Nsignal0;irange++){

                double fi=k0+k1*irange+fi_signal0[irange];
                *re_ptr0=(float)cos(fi);	*im_ptr0=(float)sin(fi);
                re_ptr0++;			im_ptr0++;
            }
            t0+=PRI;
        }
    }
#endif
    //-------------------- Window function by velocity channel init -------
    for(int idwell=0;idwell<QUANTITY_DWELL;idwell++){
        int n_pulses0=pRadarPar->npulses[idwell] - pRadarPar->nfill_pulses[idwell];
        if( (idwell!=4) && (idwell!=5) ){
            n_window[idwell]=n_pulses0-(pRadarPar->MTI_mode);
            Chebyshev_window(n_window[idwell],pRadarPar->WF_SideLobe,weight_FFT[idwell]);
        }else{//mode Clr1, Clr2
            n_window[idwell]=n_pulses0;
            for(int i0=0;i0<n_window[idwell];i0++)	weight_FFT[idwell][i0]=1.0;
        }
    }

//-------------------- Load Of FIR coefficient -------------
#if 0
    if(pRadarPar->FilterBank){
        for(int idwell=0;idwell<QUANTITY_DWELL;idwell++){
            if((idwell==4) || (idwell==5)) continue;

            FILE* fileHandle;
            if((fileHandle=fopen(pRadarPar->FIRCoeffFile[idwell],"r"))==NULL){
                printf( "The file 'FIRweights.txt' was not opened\n" );
            }
            char s0[512], s1[512], s2[512], s3[512], s4[512], s5[512], s6[512], s7[512], s8[512], s9[512], s10[512], s11[512];
            int txt_n_pulse, txt_ndf, res0;

            fscanf(fileHandle, "%s\n",s0);
            fscanf(fileHandle, "%s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5);
            fscanf(fileHandle, "%s \n",s0);
            fscanf(fileHandle, "%s %s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5,s6);
            fscanf(fileHandle, "%s \n",s0);
            fscanf(fileHandle, "%s %s \n",s0,s1);

            //if MTItype
            //	fprintf(fid, '%%   Preceding MTI: %d taps\n', MTItype);
            //end
            fscanf(fileHandle, "%s %s",s0,s1);
            if(strcmp(s1,"Preceding")==0){
                fscanf(fileHandle, "%s %s %s\n",s2,s3,s4);
                fscanf(fileHandle, "%s %s %s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5,s6,s7);
            }else fscanf(fileHandle, "%s %s %s %s %s %s \n",s2,s3,s4,s5,s6,s7);
            txt_n_pulse=atoi(s7);

            //	%%   Number of out filters: Nf = %d
            res0=fscanf(fileHandle,"%s %s %s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5,s6,s7);
            txt_ndf=atoi(s7);

            //for n = 1:nnotch
            //    fprintf(fid, '%%   Notch%d: freq=%6.3f, width=%5.3f CNR=%.1f dB \n', n, fnotch(n), fstdnotch(n), cnr_dB(n));
            //end
            int flag0=0;
            do{
                fscanf(fileHandle,"%s %s",s0,s1);
                s1[5]='\0';
                if(strcmp(s1,"Notch")==0){
                    fscanf(fileHandle,"%s %s %s %s \n",s0,s1,s2,s3);
                    flag0=1;
                }else flag0=0;
            }while(flag0);
            //fscanf(fileHandle,"%s \n",s0);

            fscanf(fileHandle,"%s %s \n",s0,s1);
            fscanf(fileHandle,"%s %s %s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5,s6,s7);
            fscanf(fileHandle,"%s %s %s %s %s %s %s %s %s %s %s %s\n",s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11);
            fscanf(fileHandle,"%s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5);
            fscanf(fileHandle,"%s %s %s %s %s %s %s %s %s %s %s %s \n",s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11);
            fscanf(fileHandle,"%s\n",s0);

            /*for k=1:Nf
                fprintf(fid, '\nk=%2d | ', k-1);
                for i=1:N
                    fprintf(fid, '  %9.6f %9.6f', real(w(k,i)), imag(w(k,i)));
                end
            end*/
            int index0=0;
            for(int indf=0;indf<txt_ndf;indf++){
                fscanf(fileHandle,"\n");
                fscanf(fileHandle,"%s %s",s0,s1);
                if(strcmp(s1,"|")!=0) fscanf(fileHandle,"%s",s1);

                for(int ipulse=0;ipulse<txt_n_pulse;ipulse++){
                    fscanf(fileHandle,"%s %s",s2,s3);
                    float re=(float)atof(s2);	float im=(float)atof(s3);
                    FIR_coefficient[idwell][index0++]=re;
                    FIR_coefficient[idwell][index0++]=im;
                }
                if((txt_n_pulse%2)!=0){
                    FIR_coefficient[idwell][index0++]=0.;
                    FIR_coefficient[idwell][index0++]=0.;
                }
            }
            fclose(fileHandle);

            for(int indf=0;indf<2*NDF_MAX;indf++) FIR_input[indf]=0.;
        }
    }
#endif
    //-------------------- Side Lobe Threshold init ------------
#if 0
    {
        fftw_complex *in, *out;
        fftw_plan p;

        in = (fftw_complex*)  fftw_malloc(sizeof(fftw_complex) * pRadarPar->ndf[0]);
        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * pRadarPar->ndf[0]);
        p = fftw_plan_dft_1d(pRadarPar->ndf[0], in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        for(int idwell=0;idwell<4;idwell++){

            int n_pulses0=pRadarPar->npulses[idwell] - pRadarPar->nfill_pulses[idwell];
            PRI=pRadarPar->pri_set[idwell]*CLC;
            double t0=0;//time - sec
            {
                int ipulse;
                for(ipulse=0;ipulse<n_pulses0;ipulse++){

                    double k0=-_2_PI_lambda_k_rDmin*t0;
                    in[ipulse][0]=(float)cos(k0); in[ipulse][1]=(float)sin(k0);
                    t0+=PRI;
                }
                for(;ipulse<pHead->ndf;ipulse++){in[ipulse][0]=0.;in[ipulse][1]=0.;}
            }

            //MTI processing
            if(pRadarPar->MTI_mode>0){
                int n_pulses0_mti= (pRadarPar->npulses[idwell] - pRadarPar->nfill_pulses[idwell]) - 1;
                for(int itap=0;itap<pRadarPar->MTI_mode;itap++){

                    for(int ipulse=0;ipulse<n_pulses0_mti;ipulse++){
                        in[ipulse][0]=(-in[ipulse][0]+in[ipulse+1][0]);
                        in[ipulse][1]=(-in[ipulse][1]+in[ipulse+1][1]);
                    }
                    in[n_pulses0_mti][0]=0;	in[n_pulses0_mti][1]=0;
                    n_pulses0_mti--;
                }

                double norm_ar[3]={2.,4.,8};
                double norm0=norm_ar[pRadarPar->MTI_mode-1];

                for(int ipulse=0;ipulse<n_window[idwell];ipulse++){
                    in[ipulse][0]/=norm0;
                    in[ipulse][1]/=norm0;
                }
            }

            //Windows function
            for(int ipulse=0;ipulse<n_window[idwell];ipulse++){
                in[ipulse][0]=in[ipulse][0]*weight_FFT[idwell][ipulse];
                in[ipulse][1]=in[ipulse][1]*weight_FFT[idwell][ipulse];
            }

            fftw_execute(p);

            for(int ivelocity=0;ivelocity<pRadarPar->ndf[idwell];ivelocity++)
                clutter_thr[idwell][ivelocity]=(float)(out[ivelocity][0]*out[ivelocity][0]+out[ivelocity][1]*out[ivelocity][1]);

            for(int ivelocity=1;ivelocity<pRadarPar->ndf[idwell];ivelocity++) clutter_thr[idwell][ivelocity]/=clutter_thr[idwell][0];
            clutter_thr[idwell][0]=1.0;
        }

        fftw_destroy_plan(p);
        fftw_free(in); fftw_free(out);
    }
#endif

    //----- Init receiver noise and rain clutter arrays ------
    // QProgressDialog prDialog(QString::fromUtf8("Загрузка данных..."),
    //                          QString::fromUtf8("Отмена"),
    //                          0, QUANTITY_DWELL - 1, nullptr);
    // prDialog.setWindowTitle(QString::fromUtf8("Процесс загрузки"));

    QProgressDialog prDialog("Загрузка данных...",
                             "Отмена",
                             0, QUANTITY_DWELL - 1, nullptr);
    prDialog.setWindowTitle("Процесс загрузки");
    prDialog.setMinimumDuration(0);

    for(int idwell=0;idwell<QUANTITY_DWELL;idwell++){
        prDialog.setValue(idwell);
        QCoreApplication::processEvents();
        if (prDialog.wasCanceled())
            break;

        int n_pulses0=pRadarPar->npulses[idwell]-pRadarPar->nfill_pulses[idwell];
        int pHead_nrg=PRI_SET[idwell]-TBLANK_CLK[idwell];

        PRI=pri_set[idwell]*CLC;
        double PRF=1./PRI;

        //---------- Rain clutter init -----
        if(pClutSimPar->rain_pres){

            //---- rain reflectivity RCS in m^2 per m^3 volume ---------
            double eta = 5.7e-14*pow(pClutSimPar->rain_rate,1.6) /(lambda*lambda*lambda*lambda);

            double gtx = pow((double)10.0, pRadarPar->tx_gain_dB/10);
            if( pRadarPar->csc_sign) gtx *= pow((double)10.0, -pRadarPar->csc_loss_dB/10);

            double x=4*PI; x=x*x*x;

            double loss_dB = pRadarPar->tx_loss_dB + pRadarPar->rsp_loss_dB;
            double loss_factor =pow((double)10.0, loss_dB/10.);
            double noise_factor=pow((double)10.0, pRadarPar->noisefig_dB/10);

            double rxline_lossfactor = pow((double)10.0, pRadarPar->rx_loss_dB/10.);
            double ts = TA + T0*(noise_factor*rxline_lossfactor - 1); //system noise temperature

            double sPot;

            double grx = pow((double)10.0,  pRadarPar->beam_gain_dB/10);
            sPot=(pRadarPar->p_peak*gtx*grx*LAMBDAF*LAMBDAF)/ (x*KB*ts*loss_factor);

            double hant0=(R_EFF+ pRadarPar->hant + pTerMap->tile[0].height);
            double hant0_2=hant0*hant0;

            double MAX_DISTANCE=(int)(100.e3/RG_STEP);

            for(int idistance=0; idistance<MAX_DISTANCE; idistance++){

                double range_cur=(idistance+1)*RG_STEP;

                double hpoint0_2=hant0_2+range_cur*range_cur+2*hant0*range_cur*sin(i_angle * D_TO_R);
                double hpoint0=sqrt(hpoint0_2);

                int raint_presense=0;
                if((hpoint0>R_EFF) && (hpoint0<(R_EFF+pClutSimPar->rain_hmax))){
                    double distance_p=asin(range_cur*cos(i_angle * D_TO_R)/hpoint0)*R_EFF;
                    if((distance_p>=pClutSimPar->rain_rmin) && (distance_p<=pClutSimPar->rain_rmax))
                        raint_presense=1;
                }

                if(cnr_re.size() <= idistance) {
                    cnr_re.resize(idistance + 1);
                    cnr_im.resize(idistance + 1);
                }

                if(cnr_re[idistance].size() < n_pulses0) {
                    cnr_re[idistance].resize(n_pulses0, 0.0f);
                    cnr_im[idistance].resize(n_pulses0, 0.0f);
                }

                if(raint_presense){
                    double rcs=(PI/4.)*eta*RG_STEP*(range_cur*pRadarPar->beam_elwidth)*(range_cur*AZWIDTH);

                    double cnr0=(sPot*tpulse_sec[idwell]*rcs)/pow(range_cur,4);

//----------------
#if 0
                            double vrcs = 0;
                            //double screenR = ScreenRain(pCl, range_cur, az);
                            for(int iel0 = (pRadarPar->n_beams-1)*2; iel0>=0; iel0--){
                                double el0;
                                int iel1=iel0/2;
                                if (iel1==iel0/2.) el0 = (pHead->el_ctrl + pRadarPar->beam_el[iel1]) - pRadarPar->beam_elwidth[ibeam]/2;
                                else el0 = (pHead->el_ctrl + pRadarPar->beam_el[iel1]);

                                //double ha = pMotionOut->h + pRadarPar->hant*cos(pMotionOut->Asum);
                                //if (altRain(range_cur, el0, ha) > pClutSimPar->rain_hmax) continue;
                                //if (el0<screenR) break;

                                // Antenna pattern gain
                                double gr_beampattern = beampattern((el0 - (pHead->el_ctrl + pRadarPar->beam_el[ibeam]) ) / pRadarPar->beam_elwidth[ibeam]);// power gain
                                double gt_beampattern = beampattern((el0 - pRadarPar->tx_el) / pRadarPar->tx_elwidth);										// power gain

                                double atmosphere_loss = atmloss(el0, range_cur, pHead->txf);
                                vrcs += atmosphere_loss*gr_beampattern*gr_beampattern*gt_beampattern*gt_beampattern;
                            }
#endif
#if 1
                    double rainrcs = 0;
                    {
                        double steph = 200.;							// m
                        int nh = int(pClutSimPar->rain_hmax/steph +1);	// number of points inside rain or chaff altitude distribution to integrate volume RCS
                        if (nh>100) nh=100;
                        steph = pClutSimPar->rain_hmax/nh;

                        double el, el1;

                        double ha=(pRadarPar->hant + pTerMap->tile[0].height);
                        FindElevationAngle(range_cur, 0, ha, &el1);

                        for(int irain0 = 1; irain0<=nh; irain0++)
                        {
                            double h =irain0*steph;

                            int ok = FindElevationAngle(range_cur, h, ha, &el);

                            if (ok==1) // h point is visible
                            {
                                // Antenna pattern gain
                                double gr = beampattern((0.5*(el+el1) - (i_angle * D_TO_R)) / pRadarPar->beam_elwidth);
                                double gt = beampattern((0.5*(el+el1) - pRadarPar->tx_el) / pRadarPar->tx_elwidth);

                                double loss = atmloss(el1, range_cur, pHead->txf);
                                rainrcs +=loss*gr*gt*eta*RG_STEP*(range_cur*(el-el1))*(range_cur*AZWIDTH/1.33);
                            }
                            el1 = el;
                        }
                    }
#endif
                    double rain_loss = rainloss(pClutSimPar->rain_rate, pClutSimPar->rain_hmax,  pClutSimPar->rain_rmin, range_cur, 0, pHead->txf, pRadarPar->polar);
                    cnr0*=rainrcs*rain_loss;
                    cnr0=sqrt(fabs(cnr0));
                    double fd=2*pClutSimPar->rain_vel/lambda;
                    double frstd=2*pClutSimPar->rain_velstd/lambda;

                    //--------- Clutter spectrum width induced by antenna rotation  -------------
                    double Azrate_degpersec = pRadarPar->rpm*360/60;
                    double fstd_rot;
                    if(pRadarPar->azwidth>1e-6){
                        double Azwidth_deg=(180.*pRadarPar->azwidth)/PI;
                        fstd_rot = Azrate_degpersec/((5.35*Azwidth_deg)/sqrt(2.));// Radar Design Pronciple, 2nd ed. Nathanson, eq. 9.76
                    }else fstd_rot=0;

                    double fstd=sqrt(frstd*frstd+fstd_rot*fstd_rot);
                    double ro=exp(-2*(PI*fstd/PRF)*(PI*fstd/PRF));
                    const double alfa=0.02;
                    //-------- Smooth with Rayleigh distributed magnitude ----------
                    if(idistance==0){
                        cnr1_re.push_back((float)(cnr0*qrnr()));
                        cnr1_im.push_back((float)(cnr0*qrnr()));
                    }else{
                        cnr1_re.push_back((float)((1-alfa)*cnr1_re[idistance-1]+alfa*cnr0*qrnr()));
                        cnr1_im.push_back((float)((1-alfa)*cnr1_im[idistance-1]+alfa*cnr0*qrnr()));
                    }

                    double *q_re=new double[n_pulses0*n_pulses0];	double *q_im=new double[n_pulses0*n_pulses0];
                    double *l_re=new double[n_pulses0*n_pulses0];	double *l_im=new double[n_pulses0*n_pulses0];

                    double amp_cnr=sqrt(cnr1_re[idistance]*cnr1_re[idistance]+cnr1_im[idistance]*cnr1_im[idistance]);

                    for(int ivel0=0;ivel0<n_pulses0;ivel0++){
                        for(int ivel1=0;ivel1<n_pulses0;ivel1++){
                            double amp0=amp_cnr*amp_cnr*pow(ro,(ivel0-ivel1)*(ivel0-ivel1));
                            double fi0=2*PI*(ivel0-ivel1)*fd/PRF;//+fi_cnr;

                            q_re[ivel0*n_pulses0+ivel1]=amp0*cos(fi0);
                            q_im[ivel0*n_pulses0+ivel1]=amp0*sin(fi0);

                            l_re[ivel0*n_pulses0+ivel1]=0.;
                            l_im[ivel0*n_pulses0+ivel1]=0.;
                        }
                    }
                    Cholesky_complex(q_re,q_im,l_re,l_im,n_pulses0);

                    double *noise_re=new double[n_pulses0*n_pulses0];	double *noise_im=new double[n_pulses0*n_pulses0];

                    int ivel0=0;
                    for(int ivel1=0;ivel1<n_pulses0;ivel1++){
                        noise_re[ivel0*n_pulses0+ivel1]=qrnr();	noise_im[ivel0*n_pulses0+ivel1]=qrnr();
                    }

                    for(int ivel0=0;ivel0<n_pulses0;ivel0++){
                        double re0=0.0, im0=0.0;
                        for(int ivel1=0;ivel1<n_pulses0;ivel1++){
                            int index = ivel0 * n_pulses0 + ivel1;
                            re0 += l_re[index] * noise_re[ivel1] + l_im[index] * noise_im[ivel1];
                            im0 += l_re[index] * noise_im[ivel1] - l_im[index] * noise_re[ivel1];
                        }
                        cnr_re[idistance][ivel0] = static_cast<float>(re0);
                        cnr_im[idistance][ivel0] = static_cast<float>(im0);
                    }

                    delete [] q_re;	delete [] q_im; delete [] l_re; delete [] l_im;
                    delete [] noise_re; delete [] noise_im;
                }else{
                    for(int ivel0 = 0; ivel0 < n_pulses0; ivel0++) {
                        cnr_re[idistance][ivel0] = 0.0f;
                        cnr_im[idistance][ivel0] = 0.0f;
                    }
                }
            }


            //---- convolution with LFT or NLFT signals ------
            fftw_complex *rain_in, *rain_out, *signal_in, *signal_out, *inverse_in, *inverse_out;
            fftw_plan rain_p, signal_p, inverse_p;

            rain_in = (fftw_complex*)  fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            rain_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            rain_p = fftw_plan_dft_1d(MAX_DISTANCE, rain_in, rain_out, FFTW_FORWARD, FFTW_ESTIMATE);

            signal_in = (fftw_complex*)  fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            signal_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            signal_p = fftw_plan_dft_1d(MAX_DISTANCE, signal_in, signal_out, FFTW_FORWARD, FFTW_ESTIMATE);

            inverse_in = (fftw_complex*)  fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            inverse_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * MAX_DISTANCE);
            inverse_p = fftw_plan_dft_1d(MAX_DISTANCE, inverse_in, inverse_out, FFTW_BACKWARD, FFTW_ESTIMATE);

            rain_signal_re.assign(n_pulses0, std::vector<float>(pHead_nrg, 0.0f));
            rain_signal_im.assign(n_pulses0, std::vector<float>(pHead_nrg, 0.0f));

            float *amp_signal=refsignal_amp+idwell*MAX_NSIGNAL;
            float *fi_signal=refsignal_fi+idwell*MAX_NSIGNAL;

#if 0
                int idistance;
                for(idistance=0; idistance<pRadarPar->tpulse_clk[idwell]; idistance++){
                    signal_in[idistance][0]=(float)(amp_signal[idistance]*cos(fi_signal[idistance]));
                    signal_in[idistance][1]=(float)(amp_signal[idistance]*sin(fi_signal[idistance]));
                }
                for(;idistance<MAX_DISTANCE; idistance++){	signal_in[idistance][0]=0.;		signal_in[idistance][1]=0.;	}
#else
            int idistance;
            for(idistance=0;idistance<MAX_DISTANCE; idistance++){	signal_in[idistance][0]=0.;		signal_in[idistance][1]=0.;	}

            for(idistance=0; idistance<tpulse_clk[idwell]; idistance++){
                int idis0=idistance-tpulse_clk[idwell]/2;
                if(idis0<0) idis0+=MAX_DISTANCE;

                signal_in[idis0][0]=(float)(amp_signal[idistance]*cos(fi_signal[idistance]));
                signal_in[idis0][1]=(float)(amp_signal[idistance]*sin(fi_signal[idistance]));
            }

#endif
            fftw_execute(signal_p);

            for(int ipulse=0;ipulse<n_pulses0;ipulse++){

#if 1
                for(int idistance=0; idistance<TBLANK_CLK[idwell]; idistance++){
                    rain_in[idistance][0]=0;
                    rain_in[idistance][1]=0;
                }
                for(int idistance=TBLANK_CLK[idwell]; idistance<MAX_DISTANCE; idistance++){
                    rain_in[idistance][0]=cnr_re[idistance][ipulse];
                    rain_in[idistance][1]=cnr_im[idistance][ipulse];
                }
#else
                for(int idistance=TBLANK_CLK[idwell]; idistance<MAX_DISTANCE; idistance++){
                    if(idistance==3000){
                        rain_in[idistance][0]=100000.;
                        rain_in[idistance][1]=100000.;
                    }else{
                        rain_in[idistance][0]=0;
                        rain_in[idistance][1]=0;
                    }
                }
#endif

                fftw_execute(rain_p);
                for(int idistance=0; idistance<MAX_DISTANCE; idistance++){
                    inverse_in[idistance][0]=rain_out[idistance][0]*signal_out[idistance][0]-rain_out[idistance][1]*signal_out[idistance][1];
                    inverse_in[idistance][1]=rain_out[idistance][0]*signal_out[idistance][1]+rain_out[idistance][1]*signal_out[idistance][0];
                }
                fftw_execute(inverse_p);

                //-- simulated of rain clutter given unambiguity range ----
                for(int idistance=0; idistance<MAX_DISTANCE; idistance++){

                    double tcur0=2*idistance*RG_STEP/C_LIGHT;
                    int range_channel=(int)((tcur0-((int)(tcur0/PRI))*PRI)*FREF);
                    range_channel-=TBLANK_CLK[idwell];

                    if((range_channel>=0) && (range_channel<pHead_nrg))
                    {
#if 1
                        rain_signal_re[ipulse][range_channel]+=(float)(inverse_out[idistance][0]/MAX_DISTANCE);
                        rain_signal_im[ipulse][range_channel]+=(float)(inverse_out[idistance][1]/MAX_DISTANCE);
#else
                        if(idistance<pHead_nrg){
                            rain_signal_re[ibeam][ipulse][idistance]=cnr_re[ibeam][idistance][ipulse];
                            rain_signal_im[ibeam][ipulse][idistance]=cnr_im[ibeam][idistance][ipulse];
                        }else{
                            rain_signal_re[ibeam][ipulse][idistance]=0;
                            rain_signal_im[ibeam][ipulse][idistance]=0;
                        }
#endif
                    }
                }
            }


            fftw_destroy_plan(rain_p);		fftw_free(rain_in);		fftw_free(rain_out);
            fftw_destroy_plan(signal_p);	fftw_free(signal_in);	fftw_free(signal_out);
            fftw_destroy_plan(inverse_p);	fftw_free(inverse_in);	fftw_free(inverse_out);
        }

//---- generating reciever noise  ------
#if 0
        for(int i0=0;i0<QUANTITY_NOISE;i0++){
            for(int i1=0;i1<NDFxNRG_MAX;i1++)//for(int i1=0;i1<((pHead->ndf)*(pHead->nrg));i1++)
                //05.082010	rsp_matrix_noise[i0][i1]=1.*qrnr();// 28.07.2010    /sqrt(2.*pRadarPar->nrows);
                rsp_matrix_noise[i0][][i1]=(float)qrnr();// 28.07.2010    /sqrt(2.*pRadarPar->nrows);
        }
#endif
        // reciever_noise_re.resize(n_pulses0);
        // reciever_noise_im.resize(n_pulses0);

        for (int irow=0; irow<pRadarPar->nrows; irow++){
            for(int ipulse=0;ipulse<n_pulses0;ipulse++){
                for(int irange=0;irange<pHead_nrg;irange++){
                    reciever_noise_re[irow][ipulse][irange]=(float)qrnr()/(float)sqrt(2.*pRadarPar->nrows);
                    reciever_noise_im[irow][ipulse][irange]=(float)qrnr()/(float)sqrt(2.*pRadarPar->nrows);
                }
            }
        }

        //---- DBF of reciever noise -----

        for(int ipulse=0;ipulse<n_pulses0;ipulse++){
            for(int irange=0;irange<pHead_nrg;irange++){
                reciever_noise_re_beam[ipulse][irange]=0.;
                reciever_noise_im_beam[ipulse][irange]=0.;

                for(int irow=0;irow<(pRadarPar->nrows);irow++){
                    double fi0=((2*PI)/lambda)*irow*pRadarPar->drows*sin((i_angle * D_TO_R) - pRadarPar->eltilt);

                    reciever_noise_re_beam[ipulse][irange]+=(float)(reciever_noise_re[irow][ipulse][irange]*cos(fi0)-
                                                                       reciever_noise_im[irow][ipulse][irange]*sin(fi0));
                    reciever_noise_im_beam[ipulse][irange]+=(float)(reciever_noise_re[irow][ipulse][irange]*sin(fi0)+
                                                                       reciever_noise_im[irow][ipulse][irange]*cos(fi0));
                }
            }
        }

        //addition of reciver noise and rain clutter
        if(pClutSimPar->rain_pres){

            init_noise_re.resize(n_pulses0);
            init_noise_im.resize(n_pulses0);

            for(int ipulse=0;ipulse<n_pulses0;ipulse++){

                init_noise_re[ipulse].resize(pHead_nrg);
                init_noise_im[ipulse].resize(pHead_nrg);

                for(int irange=0;irange<pHead_nrg;irange++){
                    init_noise_re[ipulse][irange]=reciever_noise_re_beam[ipulse][irange]+
                                                    rain_signal_re[ipulse][irange];
                    init_noise_im[ipulse][irange]=reciever_noise_im_beam[ipulse][irange]+
                                                    rain_signal_im[ipulse][irange];
                }
            }
        }else{

            init_noise_re.resize(n_pulses0);
            init_noise_im.resize(n_pulses0);

            for(int ipulse=0;ipulse<n_pulses0;ipulse++){

                init_noise_re[ipulse].resize(pHead_nrg);
                init_noise_im[ipulse].resize(pHead_nrg);

                for(int irange=0;irange<pHead_nrg;irange++){
                    init_noise_re[ipulse][irange]=reciever_noise_re_beam[ipulse][irange];
                    init_noise_im[ipulse][irange]=reciever_noise_im_beam[ipulse][irange];
                }
            }
        }
        //------------------ RSP of receivers noise and rain noise ---------------
        {
            fftw_complex *in0, *out0;
            fftw_plan p0;

            in0 = (fftw_complex*)  fftw_malloc(sizeof(fftw_complex) * pRadarPar->ndf[idwell]);
            out0 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * pRadarPar->ndf[idwell]);
            p0 = fftw_plan_dft_1d(pRadarPar->ndf[idwell], in0, out0, FFTW_FORWARD, FFTW_ESTIMATE);

            // vector<vector<float>> rsp_dwell_re; vector<vector<float>> rsp_dwell_im;

            for(int irange=0;irange<pHead_nrg;irange++){
                if (irange == 0) {
                    // rsp_dwell_re.clear();
                    // rsp_dwell_im.clear();
                    for (int ivelocity = 0; ivelocity < pRadarPar->ndf[idwell]; ++ivelocity) {
                        // rsp_dwell_re.push_back(vector<float>());
                        // rsp_dwell_im.push_back(vector<float>());
                    }
                }
                int ipulse;
                for(ipulse=0;ipulse<n_pulses0;ipulse++){
                    in0[ipulse][0]=(float)init_noise_re[ipulse][irange];
                    in0[ipulse][1]=(float)init_noise_im[ipulse][irange];
                }
                for(;ipulse<(pRadarPar->ndf[idwell]);ipulse++){
                    in0[ipulse][0]=0.;	in0[ipulse][1]=0.;
                }

                //MTI processing
                if((pRadarPar->MTI_mode>0) && (idwell!=4) && (idwell!=5) ){
                    int n_pulses0_mti= (pRadarPar->npulses[idwell] - pRadarPar->nfill_pulses[idwell]) - 1;
                    for(int itap=0;itap<pRadarPar->MTI_mode;itap++){

                        for(int ipulse=0;ipulse<n_pulses0_mti;ipulse++){
                            in0[ipulse][0]=(-in0[ipulse][0]+in0[ipulse+1][0]);
                            in0[ipulse][1]=(-in0[ipulse][1]+in0[ipulse+1][1]);
                        }
                        in0[n_pulses0_mti][0]=0;	in0[n_pulses0_mti][1]=0;
                        n_pulses0_mti--;
                    }

                    //double norm_ar[3]={sqrt(2.),sqrt(6.),sqrt(20.)};
                    double norm_ar[3]={2.,4.,8};
                    double norm0=norm_ar[pRadarPar->MTI_mode-1];

                    for(int ipulse=0;ipulse<n_window[idwell];ipulse++){
                        in0[ipulse][0]/=norm0;
                        in0[ipulse][1]/=norm0;
                    }
                }

                if((pRadarPar->FilterBank==0) || (idwell==4) || (idwell==5)){
                    //Windows function
                    for(int ipulse=0;ipulse<n_window[idwell];ipulse++){
                        in0[ipulse][0]=in0[ipulse][0]*weight_FFT[idwell][ipulse];
                        in0[ipulse][1]=in0[ipulse][1]*weight_FFT[idwell][ipulse];
                    }

                    fftw_execute(p0);

                    for(int ivelocity=0;ivelocity<pRadarPar->ndf[idwell];ivelocity++){
                        // float rsp_re = (float)out0[ivelocity][0];
                        // float rsp_im = (float)out0[ivelocity][1];
                        // rsp_dwell_re[ivelocity].push_back(rsp_re);
                        // rsp_dwell_im[ivelocity].push_back(rsp_im);

                        rsp_matrix_noise_re[idwell][ivelocity][irange]=(float)out0[ivelocity][0];
                        rsp_matrix_noise_im[idwell][ivelocity][irange]=(float)out0[ivelocity][1];

                    }

                }
            }

            // rsp_matrix_noise_re.push_back(rsp_dwell_re);
            // rsp_matrix_noise_im.push_back(rsp_dwell_im);

            fftw_destroy_plan(p0);
            fftw_free(in0); fftw_free(out0);
        }
        _sleep(50);
    }
    prDialog.setValue(100);
}


void* RSPSimFull::RspSFI(ClutSimPar_type* pClutSimPar, double i_angle, double i_freq) {
    RadarParInit(&gRadarPar, 1);
    RspSimFullInit(&gHead, &gRadarPar, pClutSimPar, &gTerMap, i_angle, i_freq);
}

vector<double>* RSPSimFull::get_to_ADC_1d(int idwell, int ivelocity) {

    Abs_1d.clear();

    int pHead_nrg=PRI_SET[idwell]-TBLANK_CLK[idwell];
    for (int i0 = 0; i0 < pHead_nrg; i0++) {
        double a = sqrt(pow(rsp_matrix_noise_re[idwell][ivelocity][i0], 2) +
                        pow(rsp_matrix_noise_im[idwell][ivelocity][i0], 2));
        Abs_1d.push_back(a);
    }
    return &Abs_1d;
}

vector<vector<double>>* RSPSimFull::get_to_ADC_2d(int idwell) {

    Abs_2d.clear();

    int pHead_nrg=PRI_SET[idwell]-TBLANK_CLK[idwell];
    for (int i0 = 0; i0 < pHead_nrg; i0++) {
        vector<double> Abs;
        for (int j0 = 0; j0 < gRadarPar.ndf[idwell]; j0++) {
            double a = sqrt(pow(rsp_matrix_noise_re[idwell][j0][i0], 2) +
                            pow(rsp_matrix_noise_im[idwell][j0][i0], 2));
            Abs.push_back(a);
        }
        Abs_2d.push_back(Abs);
    }
    return &Abs_2d;
}
