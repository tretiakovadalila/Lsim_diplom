/******************************************************************************
*  FILE NAME:	Chebyshev_window.cpp
*
*  PURPOSE:		
*
*  FUNCTIONS LIST:
*
*  DEVELOPMENT HISTORY:	
*     Date         Author      Description Of Change                    
*     -----        -------     ----------------------   
*     2010/08/17   Afanasiev   Development           
*
*  REMARKS: See data description in included header files
*           		
******************************************************************************/
//#include "stdafx.h"
#include "Math.h"


void Chebyshev_window(int n_iwindow,int WF_SideLobe,double *weight_FFT){

	//Hamming window	
	//for(int i0=0;i0<n_iwindow;i0++) weight_FFT[i0]=0.54-0.46*cos(2*PI*i0/(n_iwindow-1));
	//for(int i0=0;i0<n_pulses;i0++) weight_FFT[i0]=0.54-0.46*cos(2*PI*(i0+(pHead->ndf-n_pulses)/2)/(pHead->ndf-1));

	//without window function
	for(int i0=0;i0<n_iwindow;i0++)	weight_FFT[i0]=1.0;

	if(n_iwindow==3){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL   
				weight_FFT[0]=0.501001001001001;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=0.501001001001001;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.500316327797650;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=0.500316327797650;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.500100010001000;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=0.500100010001000;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.500031623776633;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=0.500031623776633;
				break;
			default:break;
		}
	}

	if(n_iwindow==4){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL   
				weight_FFT[0]=0.341839643637910;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.341839643637910;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.337254923787282;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.337254923787282;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.335147867140887;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.335147867140887;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.334174339968279;   weight_FFT[1]=1.000000000000000;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.334174339968279;
				break;
			default:break;
		}
	}

	if(n_iwindow==5){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.187615097436522;   weight_FFT[1]=0.686241241097988;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.686241241097988;
				weight_FFT[4]=0.187615097436522;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.178177978739727;   weight_FFT[1]=0.677749196918087;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.677749196918087;
				weight_FFT[4]=0.178177978739727;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.173056856274851;   weight_FFT[1]=0.672922258363387;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.672922258363387;
				weight_FFT[4]=0.173056856274851;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.170234190702150;   weight_FFT[1]=0.670191802710409;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=0.670191802710409;
				weight_FFT[4]=0.170234190702150;
				break;
			default:break;
		}
	}

	if(n_iwindow==6){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.132651034355647;   weight_FFT[1]=0.547708542960869;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.547708542960869;   weight_FFT[5]=0.132651034355647;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.119633137340034;   weight_FFT[1]=0.530143442947293;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.530143442947293;   weight_FFT[5]=0.119633137340034;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.112020113839728;   weight_FFT[1]=0.519029643256962;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.519029643256962;   weight_FFT[5]=0.112020113839728;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.107442151599965;   weight_FFT[1]=0.512009511728871;   weight_FFT[2]=1.000000000000000;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.512009511728871;   weight_FFT[5]=0.107442151599965;
				break;
			default:break;
		}
	}

	if(n_iwindow==7){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.087062625923214;   weight_FFT[1]=0.380025263041963;   weight_FFT[2]=0.794724449457172;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.794724449457172;   weight_FFT[5]=0.380025263041963;   weight_FFT[6]=0.087062625923214;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.073211008501984;   weight_FFT[1]=0.353752433427355;   weight_FFT[2]=0.781081556179379;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.781081556179379;   weight_FFT[5]=0.353752433427355;   weight_FFT[6]=0.073211008501984;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.064942032106815;   weight_FFT[1]=0.336240455843155;   weight_FFT[2]=0.771465688553990;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.771465688553990;   weight_FFT[5]=0.336240455843155;   weight_FFT[6]=0.064942032106815;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.059797456231283;   weight_FFT[1]=0.324506460105982;   weight_FFT[2]=0.764761151890953;   weight_FFT[3]=1.000000000000000;
				weight_FFT[4]=0.764761151890953;   weight_FFT[5]=0.324506460105982;   weight_FFT[6]=0.059797456231283;
				break;
			default:break;
		}
	}

	if(n_iwindow==11){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.036863960450862;   weight_FFT[1]=0.151528500357350;   weight_FFT[2]=0.369527601617877;   weight_FFT[3]=0.653252748399912;
				weight_FFT[4]=0.901001861360709;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=0.901001861360709;   weight_FFT[7]=0.653252748399912;
				weight_FFT[8]=0.369527601617877;   weight_FFT[9]=0.151528500357350;   weight_FFT[10]=0.036863960450862;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.023984445424866;   weight_FFT[1]=0.118876262856552;   weight_FFT[2]=0.325095250502233;   weight_FFT[3]=0.618409056791750;
				weight_FFT[4]=0.888988399201660;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=0.888988399201660;   weight_FFT[7]=0.618409056791750;
				weight_FFT[8]=0.325095250502233;   weight_FFT[9]=0.118876262856552;   weight_FFT[10]=0.023984445424866;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.016887725551016;   weight_FFT[1]=0.096905637744672;   weight_FFT[2]=0.291528999512173;   weight_FFT[3]=0.590087605475519;
				weight_FFT[4]=0.878813940547886;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=0.878813940547886;   weight_FFT[7]=0.590087605475519;
				weight_FFT[8]=0.291528999512173;   weight_FFT[9]=0.096905637744672;   weight_FFT[10]=0.016887725551016;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.012697968171370;   weight_FFT[1]=0.081767173543968;   weight_FFT[2]=0.266052935068830;   weight_FFT[3]=0.567212472162990;
				weight_FFT[4]=0.870301412618103;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=0.870301412618103;   weight_FFT[7]=0.567212472162990;
				weight_FFT[8]=0.266052935068830;   weight_FFT[9]=0.081767173543968;   weight_FFT[10]=0.012697968171370;
				break;
			default:break;
		}
	}

	if(n_iwindow==12){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.033256789774487;   weight_FFT[1]=0.131091046886511;   weight_FFT[2]=0.318993757229342;   weight_FFT[3]=0.577754924043134;
				weight_FFT[4]=0.836534677908391;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.836534677908391;
				weight_FFT[8]=0.577754924043134;   weight_FFT[9]=0.318993757229342;   weight_FFT[10]=0.131091046886511;   weight_FFT[11]=0.033256789774487;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.020595250740051;   weight_FFT[1]=0.099163297239022;   weight_FFT[2]=0.272784252043852;   weight_FFT[3]=0.535993763171992;
				weight_FFT[4]=0.816378111222923;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.816378111222923;
				weight_FFT[8]=0.535993763171992;   weight_FFT[9]=0.272784252043852;   weight_FFT[10]=0.099163297239022;   weight_FFT[11]=0.020595250740051;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.013809925645713;   weight_FFT[1]=0.077975556250786;   weight_FFT[2]=0.238076144996062;   weight_FFT[3]=0.501966999874274;
				weight_FFT[4]=0.799107048183509;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.799107048183509;
				weight_FFT[8]=0.501966999874274;   weight_FFT[9]=0.238076144996062;   weight_FFT[10]=0.077975556250786;   weight_FFT[11]=0.013809925645713;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.009907205666027;   weight_FFT[1]=0.063557103377881;   weight_FFT[2]=0.211824041639656;   weight_FFT[3]=0.474346429140266;
				weight_FFT[4]=0.784456429521457;   weight_FFT[5]=1.000000000000000;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.784456429521457;
				weight_FFT[8]=0.474346429140266;   weight_FFT[9]=0.211824041639656;   weight_FFT[10]=0.063557103377881;   weight_FFT[11]=0.009907205666027;
				break;
			default:break;
		}
	}

	if(n_iwindow==13){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.029365410627165;   weight_FFT[1]=0.110663776386050;   weight_FFT[2]=0.267052761877024;   weight_FFT[3]=0.490552137856446;
				weight_FFT[4]=0.734754388285004;   weight_FFT[5]=0.926897360710954;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.926897360710954;
				weight_FFT[8]=0.734754388285004;   weight_FFT[9]=0.490552137856446;   weight_FFT[10]=0.267052761877024;   weight_FFT[11]=0.110663776386050;
				weight_FFT[12]=0.029365410627165;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.017293445696835;   weight_FFT[1]=0.080459041659152;   weight_FFT[2]=0.220837168830775;   weight_FFT[3]=0.442905038219853;
				weight_FFT[4]=0.703030652946616;   weight_FFT[5]=0.916886005320190;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.916886005320190;
				weight_FFT[8]=0.703030652946616;   weight_FFT[9]=0.442905038219853;   weight_FFT[10]=0.220837168830775;   weight_FFT[11]=0.080459041659152;
				weight_FFT[12]=0.017293445696835;
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.011029159722062;   weight_FFT[1]=0.060828225748590;   weight_FFT[2]=0.186633584258355;   weight_FFT[3]=0.404405857799656;
				weight_FFT[4]=0.675874581274411;   weight_FFT[5]=0.908028561709532;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.908028561709532;
				weight_FFT[8]=0.675874581274411;   weight_FFT[9]=0.404405857799656;   weight_FFT[10]=0.186633584258355;   weight_FFT[11]=0.060828225748590;
				weight_FFT[12]=0.011029159722062;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.007536130382532;   weight_FFT[1]=0.047728353895525;   weight_FFT[2]=0.161082073739769;   weight_FFT[3]=0.373327524098407;
				weight_FFT[4]=0.652797478968329;   weight_FFT[5]=0.900276234073557;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=0.900276234073557;
				weight_FFT[8]=0.652797478968329;   weight_FFT[9]=0.373327524098407;   weight_FFT[10]=0.161082073739769;   weight_FFT[11]=0.047728353895525;
				weight_FFT[12]=0.007536130382532;
				break;
			default:break;
		}
	}

	if(n_iwindow==14){
		switch (WF_SideLobe){
			case 0:			//Chebyshev window 60 dB SLL
				weight_FFT[0]=0.027440031687009;   weight_FFT[1]=0.098719277645085;   weight_FFT[2]=0.235317793637060;   weight_FFT[3]=0.435322495110466;
				weight_FFT[4]=0.667541658828393;   weight_FFT[5]=0.876019420574782;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=1.000000000000000;
				weight_FFT[8]=0.876019420574782;   weight_FFT[9]=0.667541658828393;   weight_FFT[10]=0.435322495110466;   weight_FFT[11]=0.235317793637060;
				weight_FFT[12]=0.098719277645085;  weight_FFT[13]=0.027440031687009;
				break;

			case 1:			//Chebyshev window 70 dB SLL
				weight_FFT[0]=0.015523299215911;   weight_FFT[1]=0.069561294224720;   weight_FFT[2]=0.189449905801330;   weight_FFT[3]=0.384542014820840;
				weight_FFT[4]=0.628602442810060;   weight_FFT[5]=0.858972035682100;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=1.000000000000000;
				weight_FFT[8]=0.858972035682100;   weight_FFT[9]=0.628602442810060;   weight_FFT[10]=0.384542014820840;   weight_FFT[11]=0.189449905801330;
				weight_FFT[12]=0.069561294224720;  weight_FFT[13]=0.015523299215911;  
				break;

			case 2:			//Chebyshev window 80 dB SLL
				weight_FFT[0]=0.009499694391204;   weight_FFT[1]=0.050922807829791;   weight_FFT[2]=0.155911300919988;   weight_FFT[3]=0.343801318403038;
				weight_FFT[4]=0.595309265758557;   weight_FFT[5]=0.843799249876925;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=1.000000000000000;
				weight_FFT[8]=0.843799249876925;   weight_FFT[9]=0.595309265758557;   weight_FFT[10]=0.343801318403038;   weight_FFT[11]=0.155911300919988;
				weight_FFT[12]=0.050922807829791;  weight_FFT[13]=0.009499694391204;
				break;

			case 3:			//Chebyshev window 90 dB SLL
				weight_FFT[0]=0.006228276340983;   weight_FFT[1]=0.038689755441001;   weight_FFT[2]=0.131127799546558;   weight_FFT[3]=0.311088213760019;
				weight_FFT[4]=0.566996428988380;   weight_FFT[5]=0.830418027448931;   weight_FFT[6]=1.000000000000000;   weight_FFT[7]=1.000000000000000;
				weight_FFT[8]=0.830418027448931;   weight_FFT[9]=0.566996428988380;   weight_FFT[10]=0.311088213760019;   weight_FFT[11]=0.131127799546558;
				weight_FFT[12]=0.038689755441001;  weight_FFT[13]=0.006228276340983;  
				break;
			default:break;
		}
	}
}
//---------------------------------------
