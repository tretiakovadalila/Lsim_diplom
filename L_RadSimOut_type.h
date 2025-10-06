#ifndef L_RADSIMOUT_TYPE_H
#define L_RADSIMOUT_TYPE_H   /* to avoid repetition of this file include  */

#include "L_RadarPar_type.h"


#ifndef NTMAX
#define NTMAX 50
#endif

#define N_BEAMSHAPE 500 // to display el coverage
#define NSCAN 1000      // to display SNR graphics

/* Symbolic names for status of simulated target detection */
#define UNKNOWN	0
#define DETECT	1
#define NoSNR	2
#define OUTofR	3
#define BLIND_R	4
#define BLIND_V	5

// One target data

typedef struct
{
    int		tnum;		// simulated target number
    int		status;		// detection status - for debud purposes
    double	r,			// Slant distance (m)
        rD,			// Slant distance derivative (m/s)
        az,			// Azimuth relative ship (rad)
        el,			// Elevation relative ship (rad)
        rcs,		// instant RCS
        prop_factor,
        snr[NEL_MAX],	// voltage SNR
        s_re[NEL_MAX],	// sum channel I, Q voltage  (snr = sqrt(s_re*s_re + s_im*s_im))
        s_im[NEL_MAX],
        d_re[NEL_MAX],	// elevation delta channel I, Q voltage
        d_im[NEL_MAX],
        del[NEL_MAX],	// elevation delta channel monopulse voltage ratio
        s_cnr[NEL_MAX],	// sea surface clutter to noise ratio (voltage) in point of target
        v_cnr[NEL_MAX],	// volume (weather) clutter to noise ratio (voltage) in point of target
        //			jnr[NEL];	// jammer to noise ratio (voltage)
        Amp;		//amplitude for Full RSP (voltage)
} tinf_type;


// All simulated target in azimuth beam

typedef struct
{
    int nsim;					// Number of simulated targets situated in current beam
    int nt;						// Number of selected targets (SNR>1) in the current beam
    int njam;					// Number of selected jammers (JNR>1) in the current beam position by azimuth
    double	jnr[NEL_MAX];			// jammer to noise ratio (voltage)

    double time;				// Current time (s)
    tinf_type tinf[NTMAX];

    // to diplay on PPI an "el coverage"
    double shape_el[N_BEAMSHAPE], shape_txbeam[N_BEAMSHAPE], shape_rxbeam[N_BEAMSHAPE]; // pattern normed to 1

    // to diplay clutter power
    double 	cnr_dB[NEL_MAX*NRG_MAX];	// surface+volume clutter power (dB) for all range gates


    /* Remark
    Samples cnr_dB[i] are sorted by elbeam # at first, e.g.
    a[0]		->	RG# 0	elbeam # 0,
    a[1]		->	RG# 0	elbeam # 1,
    ....................................
    a[NEL-1]	->	RG# 0	elbeam # NEL-1,

    a[N_RG  ]	->	RG# 1	elbeam # 0,
    a[N_RG+1]	->	RG# 1	elbeam # 1,
    .....................................
    */

} RadSimOut_type;

#endif
