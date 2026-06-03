#ifndef L_RADARPAR_TYPE_H
#define L_RADARPAR_TYPE_H   /* to avoid repetition of this file include  */

#include <math.h>

#include "MathConst.h"

// Array sizing

const int NEL_MAX			= 15;		// Max number of Rx elevation beams
const int NROWS_MAX			= 64;		// Max number of rows 36/2007
const int NPULSES_MAX		= 21;		// Max number of pulses per burst
const int NDF_MAX			= 32;		// Max FFT size (RSP output array size in DF) for Full Doppler Mode, 4 for Hybrid Mode
const int NRG_MAX			= 1050;     // Max number of processed range gates (RSP output array size in RG)for Full Doppler Mode, 9400-Hybrid Mode
const int NDFxNRG_MAX		= 37700;	//Max size of RSPSim output array for one elevation beam, 33600-Full Doppler Mode, 37700-Hybrid Mode
const int NRSP_MAX			= NDFxNRG_MAX*NEL_MAX*2;	// Max size of RSPSim structure for NEL_MAX elevation beams

// Mode control
const double ACCELERATION = 20*D_TO_R; // 1/sec^2

const int	 SEARCH_MODE= 0;		// 0 - Full Doppler mode, 1 - Hybrid mode

const double RPM[2]		= {10,10};	//~Ant rotation speed (rotations per minute), user can be changed by menu
const int	 NBEAMS[2]	= {15,15};	// Number of active el beams, user can be changed by menu
const int	 FREQ_AGILITY	= 0;	// frequency agility mode:
    // 0 - none
    // 1 - scan to scan
    // 2 - each 4 bursts
    // 3 - each burst

/*-------------------------- Tx and Rx parameters ---------------------------------*/
const int	  N_TXF		= 100;		// Number of possible Tx carrier frequencies
const double  TX_FMIN	= 2.9e9;	// lower carrier frequency (Hz)
const double  TX_FMAX	= 3.3e9;	// upper carrier frequency (Hz)
const double  TX_F	    = (TX_FMAX+TX_FMIN)/2;	// average carrier frequency (Hz)
const double  LAMBDAF   = C_LIGHT /TX_F;	//C_LIGHT /TX_F average wavelength 0.1034

const double  FREF		= 3000000.;					// Reference frequency in Hz     1500000.
const double  CLC		= 1./FREF;					// LSB of PRI and Range in sec
const double  RG_STEP	= 0.5*C_LIGHT*CLC;			// range gate step in m

// Radar
const double PPEAK		= 8960;	    // peak transmitter power (Wt)25000
const double DUTYCYCLE	= 0.15;		// transmitter duty cycle (dimensionless)
const double NOISEFIGURE= 3.0;		// receiver noise factor (dB)
const double LOSS_TX_DB	= 1.;		// Tx line loss (dB)
const double LOSS_RX_DB	= 1;		// Rx line loss (dB)
const double LOSS_RSP_DB= 3.0;		// 4 RSP loss including DSP,discrepancy and RG straddling loss (dB)

// Antenna
const int    POLAR		= 1;		// polarization (0 - H, 1 - V)
const double HANT		= 10.0;		// antenna location height, m
const double ELANT		= 10*D_TO_R;// antenna tilt, rad
const double AZWIDTH	= 1.5*D_TO_R;	// azimuth beam one-way 3 dB width
const int	 NROW		= 64;		// number of antenna slot waveguide rows by elevation
const double DROW		= 0.0625;	//distance between rows, m 0.0615/2007

//Tx Elevation beams parameters
const double TX_EL		= 3*D_TO_R;	// Tx beam elevation angle (degree)
const double TX_ELWIDTH	= 8*D_TO_R;// Tx beam one-way 3 dB width in vertical plane (degree)
const double TX_GAIN_DB	= 32;		// Tx beam max gain 32.5/2007
const int	 CSC_SIGN	= 1;		// CSC shape of Tx beam on/off
const double CSC_ELMIN  = 6*D_TO_R;// CSC shape start angle, deg
const double CSC_ELMAX  = 50*D_TO_R;// CSC shape max angle, deg
const double CSC_LOSS_DB= 2;		// CSC loss, dB

// Rx Elevation beams parameters for 15 beam set
const double BEAM_GAIN_DB_15[NEL_MAX]	= {38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38 };// Rx beams  gain
const double BEAM_EL_15[NEL_MAX]		= { -3.5*D_TO_R, -2.0*D_TO_R, -0.5*D_TO_R, 1.0*D_TO_R, 2.5*D_TO_R, 4*D_TO_R, 5.5*D_TO_R, 7*D_TO_R, 8.5*D_TO_R, 10*D_TO_R, 11.5*D_TO_R, 13*D_TO_R, 14.5*D_TO_R, 16*D_TO_R, 17.5*D_TO_R};// Rx beams elevation angle (degree)

const double KB		= 1.38e-23;		// Bolzman's constant
const double T0		= 290;			// reference temperature T0=290 K
const double KT		= KB*T0;		// Bolzman's constant product with standard temperature T0=290 K
const double TA		= 0.876*100 + 36;// typical antenna efficient temperature in K degree (see Scolnik's Radar Handbook. 1990, p 2.30)

/*-------------------------------- Waveforms parameters ---------------------------*/
/* Waveform symbolic names */

const int NPULSES_AR[]		= {21, 21, 20, 19, // number of pulses per burst for various mode & waveforms
                          3, 3, 7, 7, 7};	   //Hybrid mode: Clr1, Clr2, Dop0-1, Dop0-2, Dop0-3
const int NFILL_PULSES_AR[]	= {7, 7, 6, 5,		// number of fill pulses for various waveforms
                               0, 0, 1, 1, 1};		//Hybrid mode
const int NDF_AR[]			= {32, 32, 32, 32,  4, 4, 8, 8, 8};	// FFT size for various waveforms

/* Waveform parameters */
//29.09.2010	const double TPULSE_SEC[]	= {36e-6, 41.4e-6, 47.4e-6,52.5e-6,  470e-6, 470e-6, 75.e-6};// Pulse length for various waveforms
const double TPULSE_SEC[]	= {36e-6, 41.4e-6, 47.4e-6, 52.0e-6,  470e-6, 470e-6, 75.e-6, 75.e-6, 75.e-6};// Pulse length for various waveforms

const int    TPULSE_CLK[]	= {int(FREF*TPULSE_SEC[0]), int(FREF*TPULSE_SEC[1]), int(FREF*TPULSE_SEC[2]), int(FREF*TPULSE_SEC[3]),
                          int(FREF*TPULSE_SEC[4]), int(FREF*TPULSE_SEC[5]), int(FREF*TPULSE_SEC[6]), int(FREF*TPULSE_SEC[7]), int(FREF*TPULSE_SEC[8])};

const int	 TB_CLK[]		= {2, 2, 2, 2, 2,2,2,2,2};//blank after end of transmit pulse

const int	 TBLANK_CLK[]	= {TPULSE_CLK[0]+TB_CLK[0], TPULSE_CLK[1]+TB_CLK[1], TPULSE_CLK[2]+TB_CLK[2], TPULSE_CLK[3]+TB_CLK[3],
                          TPULSE_CLK[4]+TB_CLK[4], TPULSE_CLK[5]+TB_CLK[5], TPULSE_CLK[6]+TB_CLK[6], TPULSE_CLK[7]+TB_CLK[7], TPULSE_CLK[8]+TB_CLK[8]};

const double PRIMIN[2]		= {240e-6, 45e-6};//boundary of pulse repeatition interval for various PRF mode
const double PRIMAX[2]		= {350e-6, 53e-6};//boundary of pulse repeatition interval for various PRF mode

const double PRFMIN[2]		= {1./PRIMAX[0], 1./PRIMAX[1]};//boundary of pulse repeatition frequency for various PRF mode
const double PRFMAX[2]		= {1./PRIMIN[0], 1./PRIMIN[1]};

const int	 PRI_SET[]		= {int(240e-6*FREF),int(276e-6*FREF),int(316e-6*FREF),int(350e-6*FREF),
                       int(3133.33e-6*FREF),int(3133.33e-6*FREF),int(500e-6*FREF),int(550e-6*FREF),int(600e-6*FREF)};

const double FM_DEVIATION[2]	= {2500000, 2500000};	// (Hz)
const double R_WIDTH[2]		= {1.5*0.5* C_LIGHT/FM_DEVIATION[0], 1.5*0.5* C_LIGHT/FM_DEVIATION[1]}; // compressed pulse 3 dB width in m for various PRF mode
const double SLL_R[2]			= {1.0e-4, 1.0e-4};	// pulse compression side-lobe level (power coefficient)for various PRF mode
const double F_WIDTH[]		= {1.6/(NPULSES_AR[0]-NFILL_PULSES_AR[0]),1.6/(NPULSES_AR[1]-NFILL_PULSES_AR[1]), 1.6/(NPULSES_AR[2]-NFILL_PULSES_AR[2]),1.6/(NPULSES_AR[3]-NFILL_PULSES_AR[3]),	// normalized to PRF width of Doppler Filter for various PRF mode
                          1.6/(NPULSES_AR[4]-NFILL_PULSES_AR[4]),1.6/(NPULSES_AR[5]-NFILL_PULSES_AR[5]), 1.6/(NPULSES_AR[6]-NFILL_PULSES_AR[6]), 1.6/(NPULSES_AR[7]-NFILL_PULSES_AR[7]), 1.6/(NPULSES_AR[8]-NFILL_PULSES_AR[8])};
const double SLL_DF[2]		= {1.0e-6, 1.0e-7};	// Doppler Filtering side-lobe level (power coefficient)for various PRF mode

/*-------------------------------- Algorithm Parameters ---------------------------*/

const double PFA = 1e-6; // false alarm probability per detection test in resolution cell
const double THR_CFAR = 9.0;		// CFAR threshold coefficient

/* radar instrumental errors */
const double RBIAS  = 2;	// m
const double RSTD   = 5;	// m

const double AZBIAS = 0;			// rad
const double AZSTD  = 0.1*D_TO_R;	// rad

const double ELBIAS = 0;			// rad
const double ELSTD  = 0;	// rad0.2*D_TO_R

const double VBIAS  = 0;	// m/s
const double VSTD   = 1;	// m/s

/* System parameters for TWS */
const double FA_RATE[2]		= {1, 2}; // # per sec
const double R_COVERAGE[2]	= {460000, 460000};

const double EL_COVERAGE[2]	= {70*D_TO_R, 70*D_TO_R};
const double BEAM_ELWIDTH = 1.6*D_TO_R;

/*-------------------------- Radar Par Data Structure -------------------------------------*/
typedef struct
{
    // General control
    int search_mode;	// 0 - medium PRF, 1 - high PRF, user can be changed by Radar menu
    int auto_mode;		// sign to choice mode automatically
    int n_beams;		// number of active Rx elevation beams, user can be changed by Radar menu
    double rpm;			// antenna rotation speed, user can be changed by Radar menu
    int freq_agility;	// frequency agility mode:  0 - none
        // 1 - scan to scan
        // 2 - each 4 burst
        // 3 - each burst

    // Radar
    double tx_fmin;		// lower carrier frequency (Hz)
    double tx_fmax;		// upper carrier frequency (Hz)
    int    n_txf;		// Number of possible frequencies

    double p_peak;	    // Tx peak power (Wt)
    double duty;		// transmitter duty cycle (dimensionless)
    double tx_loss_dB;	// Transmitting line loss
    double rx_loss_dB;	// Transmitting line loss
    double rsp_loss_dB;	// RSP loss ncluding DSP,discrepancy and weigthing function
    double noisefig_dB; // Rx noise figure
    int ndf[9];			// length of FFT for current PRF mode and rpm (ndf>=npulses-nfill_pulses)
    int npulses[9];		// number of pulses for current PRF mode,  user can be changed by Radar menu
    int nfill_pulses[9];	// number of fill pulses for current PRF mode

    double tpulse_sec[9];		// Pulse length {24e-6, 13e-6}
    int    tpulse_clk[9];		//TPULSE_CLK[2]	= {int(FREF*TPULSE_SEC[0]), int(FREF*TPULSE_SEC[1])};

    double primin;			//
    double primax;			//
    double prfmin;			//
    double prfmax;			//

    int	 pri_set[9];		//in CLK
    double fm_deviation;	//FM_DEVIATION	= 1000000;	// (Hz)3000000
    double r_width;			//R_WIDTH		= 1.5*0.5* C_LIGHT/FM_DEVIATION; // compressed pulse 3 dB width in m
    double sll_r;			//SLL_R			= 1.0e-4;	// pulse compression side-lobe level (power coefficient)
    double f_width[9];			//F_WIDTH[]		= {1.6/(NPULSES_AR[0]-NFILL_PULSES_AR[0]),1.6/(NPULSES_AR[1]-NFILL_PULSES_AR[1])};	// normalized to PRF width of Doppler Filter
    double sll_df;			//SLL_DF		= 1.0e-5;	// Doppler Filtering side-lobe level (power coefficient)

    // Antenna
    int	   polar;		// polarization (0 - H, 1 - V)
    double hant;		// antenna height, m
    double eltilt;		// antenna tilt
    double azwidth;		// azimuth beam one-way 3 dB width
    int		nrows;		// number of antenna slot waveguide rows
    double drows;		//distance between rows, m

    // Elevation beams parameters
    double tx_el;		// Tx beam elevation angle (rad)
    double tx_elwidth;	// Tx beam one-way 3 dB width in vertical plane (rad)
    double tx_gain_dB;	// Tx beam max gain

    int	   csc_sign;	// CSC shape of Tx beam
    double csc_elmin;	// CSC shape start angle (rad)
    double csc_elmax;	// CSC shape max angle (rad)
    double csc_loss_dB;	// CSC loss

    int	   window_function;         // 0 - no weighting, 2 - 21 - argument of Taylor's function affecting on sidelobes level
    double weight_Taylor[NROWS_MAX];		// weighting factors for Taylor window (normalized output noise to unity power)
    double beam_el[NEL_MAX];		// Rx beams elevation angle (rad)
    double beam_elwidth;	// Rx beams one-way 3 dB width in vertical plane (rad)
    double beam_gain_dB;	// Rx beams gain
    double loss_dB[NEL_MAX];        // Rx beam loss due to weighting & DBF

    double kr; // slope coefficient for calculation of error by R ( CCF approx. - exp(), see funct. KvKr() in RspSim.cpp)
    double kv[9]; // slope coefficient for calculation of error by V ( CCF approx. - exp(), see funct. KvKr() in RspSim.cpp)
    double slope[NEL_MAX];
    double elmax[NEL_MAX];
    // Systematic errors and random errors not dependent on SNR
    double r_bias;		// m
    double r_std;		// m
    double az_bias;		// rad
    double az_std;		// rad
    double el_bias;		// rad
    double el_std;		// rad
    double v_bias;		// m/s
    double v_std;		// m/s

    // Calculated data from above parameters
    double pot[NEL_MAX];	// radar potencial for each el beam (for radar equation: SNR = pot[i] * RCS / R^4)

    // Inhibit sectors (rad):
    double InhSectMin[5];
    double InhSectMax[5];
    int N_InhSect;
    // RSP full mode:
    int MTI_mode; // 0 - off !, 1 - 1 tap, 2 - 2 taps, 3 - 3 taps
    int WF_SideLobe; // 0 - 60 dB !, 1 - 70 dB, 2 -80 dB, 3 - 90 db
    int DF_min; //0... ndf-1						0
    int DF_max; //0... ndf-1 (DF_max>DF_min)		ndf-1
    int SL_Thr; // 0 - Off, 1 - on, switching of side lobes threshold by velocity

    int GrClMapForming; // 0 - off, 1- on, 10 turns without tgt and save plots structure PlAccum_type in file
    int FilterBank;	// 0 - FFT, 1 - FIR
    char FIRCoeffFile[9][2048];
} RadarPar_type;


/*-------------------------- Radar Parameters Data Structure Initialization ----------------------------------*/

const RadarPar_type RADARPAR =
    {
        // General control
        SEARCH_MODE,		// =0, Default mode: 0 - medium PRF, 1 - high PRF
        0,					// AUTO mode sign
        NBEAMS[1],			// =15, number of active Rx elevation beams
        10,//RPM[0],				// =5, antenna rotation speed
        0,//FREQ_AGILITY

        // Radar
        TX_FMIN,			// =2.7 GHz, lower carrier frequency (Hz)
        TX_FMAX,			// =3.1 GHz, upper carrier frequency (Hz)
        N_TXF,				// =100, Number of possible frequencies

        PPEAK,				// =16800, Tx peak power (Wt)
        DUTYCYCLE,			// =0.1, transmitter duty cycle (dimensionless)
        LOSS_TX_DB,			// =2, Transmitting line loss (power coefficient <1)
        LOSS_RX_DB,			// =1, Transmitting line loss (power coefficient <1)
        LOSS_RSP_DB,		// =4, RSP loss ncluding DSP,discrepancy and weigthing function(power coefficient <1)
        NOISEFIGURE,		// =3, Rx noise figure (power coefficient > 1)
        NDF_AR[0],NDF_AR[1],NDF_AR[2],NDF_AR[3],NDF_AR[4],NDF_AR[5],NDF_AR[6],NDF_AR[7],NDF_AR[8],//FFT size
        NPULSES_AR[0],NPULSES_AR[1],NPULSES_AR[2],NPULSES_AR[3],NPULSES_AR[4],NPULSES_AR[5],NPULSES_AR[6],NPULSES_AR[7],NPULSES_AR[8], // npulses in burst
        NFILL_PULSES_AR[0],NFILL_PULSES_AR[1],NFILL_PULSES_AR[2],NFILL_PULSES_AR[3],NFILL_PULSES_AR[4],NFILL_PULSES_AR[5],NFILL_PULSES_AR[6],NFILL_PULSES_AR[7],NFILL_PULSES_AR[8], //nfill_pulses;

        TPULSE_SEC[0],TPULSE_SEC[1],TPULSE_SEC[2],TPULSE_SEC[3],TPULSE_SEC[4],TPULSE_SEC[5],TPULSE_SEC[6],TPULSE_SEC[7],TPULSE_SEC[8],//TPULSE_SEC[0],		// =20e-6, (sec)
        int(FREF*TPULSE_SEC[0]), int(FREF*TPULSE_SEC[1]), int(FREF*TPULSE_SEC[2]), int(FREF*TPULSE_SEC[3]), int(FREF*TPULSE_SEC[4]), int(FREF*TPULSE_SEC[5]), int(FREF*TPULSE_SEC[6]),int(FREF*TPULSE_SEC[7]), int(FREF*TPULSE_SEC[8]),//TPULSE_CLK[0],		// Pulse length (clc)

        PRIMIN[0],			//primin (sec)
        PRIMAX[0],			//primax (sec)

        PRFMIN[0],			// Hz
        PRFMAX[0],			// Hz

        PRI_SET[0],PRI_SET[1],PRI_SET[2],PRI_SET[3],PRI_SET[4],PRI_SET[5],PRI_SET[6],PRI_SET[7],PRI_SET[8], // clc

        FM_DEVIATION[0],	// =1 MHz, (Hz)
        R_WIDTH[0],			// ~ compressed pulse 3 dB width in m
        SLL_R[0],			// =1.0e-4, pulse compression side-lobe level (power coefficient)
        1.6/(NPULSES_AR[0]-NFILL_PULSES_AR[0]),1.6/(NPULSES_AR[1]-NFILL_PULSES_AR[1]), 1.6/(NPULSES_AR[2]-NFILL_PULSES_AR[2]),1.6/(NPULSES_AR[3]-NFILL_PULSES_AR[3]),//F_WIDTH[0],			// normalized to PRF width of Doppler Filter
        1.6/(NPULSES_AR[4]-NFILL_PULSES_AR[4]),1.6/(NPULSES_AR[5]-NFILL_PULSES_AR[5]), 1.6/(NPULSES_AR[6]-NFILL_PULSES_AR[6]),1.6/(NPULSES_AR[7]-NFILL_PULSES_AR[7]), 1.6/(NPULSES_AR[8]-NFILL_PULSES_AR[8]),
        SLL_DF[0],			// =1.0e-5, pulse compression side-lobe level (power coefficient)
        // Antenna
        POLAR,				// polarization (0 - H, 1 - V)
        HANT,				// antenna location height, m
        ELANT,				// antenna tilt, rad
        AZWIDTH,			// azimuth beam one-way 3 dB width
        NROW,				//=64, number of rows
        DROW,				//=0.06515, distance between rows

        // Elevation beams parameters
        TX_EL,				// Tx beam elevation angle (degree)
        TX_ELWIDTH,			// Tx beam one-way 3 dB width in vertical plane (degree)
        TX_GAIN_DB,			// Tx beam max gain(power coefficient)

        CSC_SIGN,			// CSC shape of Tx beam
        CSC_ELMIN,			// CSC shape start angle
        CSC_ELMAX,			// CSC shape max angle
        CSC_LOSS_DB,		// CSC loss (power coefficient < 1)

        4, //Taylor's window function number with sidelobe level < 30 dB
        0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0, //weighting factors are calculated by initialization and depend on window function number

        BEAM_EL_15[0],BEAM_EL_15[1],BEAM_EL_15[2],BEAM_EL_15[3],BEAM_EL_15[4],BEAM_EL_15[5],BEAM_EL_15[6],BEAM_EL_15[7],BEAM_EL_15[8],BEAM_EL_15[9],BEAM_EL_15[10],BEAM_EL_15[11],BEAM_EL_15[12],BEAM_EL_15[13],BEAM_EL_15[14],
        0, //0,0,0,0,0,0,0,0,0,0,0,0,0,0, //beam width are calculated by initialization and depend on DBF control parameters
        0, //BEAM_GAIN_DB_15[0],BEAM_GAIN_DB_15[1],BEAM_GAIN_DB_15[2],BEAM_GAIN_DB_15[3],BEAM_GAIN_DB_15[4],BEAM_GAIN_DB_15[5],BEAM_GAIN_DB_15[6],BEAM_GAIN_DB_15[7],BEAM_GAIN_DB_15[8],BEAM_GAIN_DB_15[9],BEAM_GAIN_DB_15[10],BEAM_GAIN_DB_15[11],BEAM_GAIN_DB_15[12],BEAM_GAIN_DB_15[13],BEAM_GAIN_DB_15[14],
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //losses in Rx beam due to weighting function (dB)are calculated by initialization and depend on DBF control parameters

        // Systematic errors and random errors not dependent on SNR
        1.17996,				// kr
        1.834,1.834,1.834,1.834,1.834,1.834,1.834,1.834,1.834,	// kv
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//slope
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//elmax

        RBIAS ,				// m
        RSTD,				// m
        AZBIAS,				// rad
        AZSTD,				// rad
        ELBIAS,				// rad
        ELSTD,				// rad
        VBIAS ,				// m/s
        VSTD,				// m/s
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//POT
        // Inhibit sectors (rad):
        10*D_TO_R, 0*D_TO_R, 0*D_TO_R, 0*D_TO_R, 0*D_TO_R, // InhSectMin;
        265*D_TO_R, 0*D_TO_R, 0*D_TO_R, 0*D_TO_R, 0*D_TO_R, // InhSectMax;
        1,	// int N_InhSect;
        // RSP full mode:
        0,	// int MTI_mode; // 0 - off !, 1 - 1 tap, 2 - 2 taps, 3 - 3 taps
        0,	// int WF_SideLobe;// 0 - 60 dB !, 1 - 70 dB, 2 -80 dB, 3 - 90 db
        0,	// int DF_min;//0... ndf-1						0
        31, // int DF_max;//0... ndf-1 (DF_max>DF_min)		ndf-1
        1,	// int SL_Thr; // 0 - Off, 1 - on
        0,  // 0 - off, 1- on, 10 turns without tgt and save plots structure PlAccum_type in file

        0,	// 0 - FFT, 1 - FIR int FilterBank;
        "..\\Out\\FilterBank\\Dop1_0.txt",//char FIRCoeffFile[0][2048];
        "..\\Out\\FilterBank\\Dop2_0.txt",//char FIRCoeffFile[1][2048];
        "..\\Out\\FilterBank\\Dop3_0.txt",//char FIRCoeffFile[2][2048];
        "..\\Out\\FilterBank\\Dop4_0.txt",//char FIRCoeffFile[3][2048];
        "",//char FIRCoeffFile[4][2048];
        "",//char FIRCoeffFile[5][2048];
        "..\\Out\\FilterBank\\Dop0_0.txt",//char FIRCoeffFile[6][2048];
        "..\\Out\\FilterBank\\Dop5_0.txt",//char FIRCoeffFile[7][2048];
        "..\\Out\\FilterBank\\Dop6_0.txt",//char FIRCoeffFile[8][2048];
};


#endif
