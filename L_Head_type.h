#ifndef L_HEAD_TYPE_H
#define L_HEAD_TYPE_H   /* to avoid repetition of this file include  */

#include "L_RadarPar_type.h"

typedef struct
{
    // general
    int ban;        // 1 - radiation ban
    int search_mode;// 0 - Full Doppler Mode1, 1 - Hybrid Mode
    int n_beams;	// number of active Rx elevation beams
    int n_pulses;
    int fill_pulses;
    int ndf;		// boundaries to search target plot in velocity plane: initial DF#, number of processed DFs - ndf (<= NDF)

    // dwell control data
    int burst_no;	// current burst number
    double time;	// time instant of first pulse in burst (sec)
    int txf_no;		// carrier frequency number
    int wf_code;	// 0-3 Dop1-Dop3(Full Doppler mode), 4-Clr1, 5-Clr2, 6,7,8-Dop0 (Hybrid mode)

    double tpulse_sec;

    int r0;			// initial range of matrix in CLK
    int rgmin,		// initial range after blank in range gates (low boundary to search target plot in range)
        nrg;		// number of processed RG (nrg<= NRG), upper boundary to search target plot in range: rgmin + nrg
    int dfmin;		// low boundary of Doppler filters to search target plot in velocity plane
    int dfmax;		// upper boundary of Doppler filters to search target plot in velocity plane: max DF#, number of processed DFs <=NDF-1

    double el_ctrl; // elevation angle control to compensate nonverticality (rad)

    // aux data
    double txf;		// current carrier frequency (Hz)
    double vstep;	// current velocity step between Doppler filters (m/s)
    double kv;		// current slope by V

    int el_current; // N elevation current for full rsp mode
} Head_type;


const Head_type FHEAD = {
    0,					// radiation ban ==1
    0,					//search_mode - Full Doppler Mode1
    15,					//n_beams
    NPULSES_AR[0],		//n_pulses
    NFILL_PULSES_AR[0],	//fill_pulses
    NDF_AR[0],			//ndf = 32
    0,					//current burst number
    0,					//time instant of first pulse in burst (sec)
    50,					//txf_no - carrier frequency number
    0,					//wf_code

    36e-6,				// tpulse in sec
    // TPULSE_SEC[0]+TB_CLK[0]/FREF,//tblank_sec
    0,					//r0 - initial range of matrix in CLK
    0,					//rgmin - initial RG#
    500,				//nrg - number of processed RG
    0,					//dfmin - initial DF#
    NDF_AR[0]-1,		//dfmax -upper limit number of processing df
    0.,					//el_ctrl - elevation angle control to compensate nonverticality (rad)
    5.6e9, //2.9e9,				//current carrier frequency (Hz)
    0.,					//vstep
    0,					//kv
    0					//N elevation current for full rsp mode
};


#endif
