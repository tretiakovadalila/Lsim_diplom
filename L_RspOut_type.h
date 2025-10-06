#ifndef L_RSPOUT_TYPE_H
#define L_RSPOUT_TYPE_H   /* to avoid repetition of this file include  */

#include "L_RadarPar_type.h"

typedef struct
{
    int    nexceed;		// number of radar cells in DF matrix where signal is detected (greater than adaptive threshold)
    float a[NDFxNRG_MAX ];  //NDF*NRG DF matrix: a[j] > 0  means detection,power signal, a[j] <= 0  means no detection
} cfar_type;

typedef struct
{
    cfar_type cfar[NEL_MAX]; // Cfar output for all elevation beams.
        // Actual number of active beams is specified in Head data
} RspOut_type;

/* Remark
1. Samples a[i] are  echo power in radar resolution cells
2. Samples a[i] in DF matrix are sorted by RG# at first, e.g.
    a[0]		->	DF# 0	RG# 0,
    a[1]		->	DF# 0	RG# 1,
    ....................................
    a[N_RG-1]	->	DF# 0	RG# N_RG-1,

    a[N_RG  ]	->	DF# 1	RG# 0,
    a[N_RG+1]	->	DF# 1	RG# 1,
    .....................................
*/

#endif
