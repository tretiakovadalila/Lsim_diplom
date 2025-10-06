#ifndef MATHCONST_H
#define MATHCONST_H   /* to avoid repetition of this file include  */


/* Physics constants */

//const double C_LIGHT	= 299792458.;	    /* Light velocity (m/s) */
const double C_LIGHT	= 300000000.;	    /* Light velocity (m/s) */
const double L_S		= C_LIGHT;

const double R_EARTH	= 6371210.;	        /* Earth radius (m) */
const double R_EFF		= (4./3.)*R_EARTH; 	/* Effective Earth radius with refraction phenomena (m) */

const double EGA		= 9.81;        // Earth's gravitation acceleration (m/s2)

const double KT0		= 1.38e-23 * 290;     /* Bolzman constant product with standard temperature */

/* PI - Constants */
const double _PI	= 3.14159265359;

const double  PI	= _PI;
const double  PI_2	= _PI/2;
const double  PI_3	= _PI/3;
const double  PI_4	= _PI/4;
const double  TWOPI = 2*_PI;
const double  PI2	= _PI*_PI;
const double  PI2_4	= PI2/4;

/* Scale */
const double R_TO_D	= (180./_PI);       /* radian -> degree  */
const double D_TO_R	= (_PI/180.);       /* degree -> radian  */

const double R_TO_M	= (60*180./_PI);    /* radian -> minute  */
const double M_TO_R	= (_PI/(60*180.));  /* minute -> radian  */
const double S_TO_R	= (_PI/(60*60*180.));  /* minute -> radian  */

const double NM_TO_KM	= 1.852;		// nautical miles to km
const double KM_TO_NM	= 1./1.852;		// km to nautical miles
const double M_TO_NM	= 1./1000./1.852;   // m to nautical miles
const double M_TO_FEET	= 1./0.3048;	// meter to feet
const double FEET_TO_M	= 0.3048;		// feet to meter
const double M_TO_KFEET	= 1./0.3048/1000.;	// meter to kfeet
const double KFEET_TO_M	= 0.3048*1000;		// kfeet to meter
const double MS_TO_KNOT	= 3600./1852.;	// m/c to knot
const double KNOT_TO_MS	= 1852./3600.;	// knot to m/c


#endif
