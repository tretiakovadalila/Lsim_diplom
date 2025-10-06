#ifndef TCLUTSIMPAR_TYPE_H
#define TCLUTSIMPAR_TYPE_H
/*---------------------------------------------------------------------------*/

//const int N_SURFACECLUT	= 3; // Max number of simulated surface clutter (e.g., hills)

/*  Surface Type Designation
    1 - highly densed urban area,
    2 - low densed urban area,
    3 - wooden area,
    4 - paddy, wheat, vegetable field,
    5 - paddy, marsh area,
    6 - sea area,
    7 - lake,river
*/
/* Surface Type for LSim
    1 - General rural
    2 - Continuous forest
    3 - Mountains
    6 - sea area
    */
// total data structure of clutter initial parameters set by menu
typedef struct
{
    int ClutterOn;						// Sign to simulate clutter (Surf Clutter presence)
    int TerrainMapUsing;				//
    int AtmLossOn;						// Sign to simulate atmosphere absorbtion loss
    int MulpathOn;						// Sign to simulate multipath phenomena
    int BackgrSurface;					// type of Earth background surface - see above comments
    int SeaState;						// Sea state
    int	   rain_pres;					// rain clutter presense sign
    double rain_rate;					// rainfall rate mm/hour
    double rain_vel;					// rain radial velocity (m/sec)
    double rain_velstd;					// rain velocity std (m/sec)
    double rain_rmin;					// rain min range in m
    double rain_rmax;					// rain max range in m
    double rain_hmax;					// rain max altitude in m
    double wind_az;						// azimuth direction of wind velocity (rad)
    double wind_vel;					// wind velocity (m/s)
    double vel_dev;						// wind velocity deviation (m/s)
} ClutSimPar_type;

/*---------------------------------------------------------------------------*/

// Default clutter parameters

#include "MathConst.h"
const float D_R=(float)D_TO_R;

const ClutSimPar_type CLUTSIMPAR =
    {
        // Generap controls
        1,		//	int ClutterOn;					// Sign to simulate clutter
        1,		//	TerrainMapUsing;
        1,		//	int AtmLossOn;					// Sign to simulate atmosphere absorbtion loss
        0,		//	int MulpathOn;					// Sign to simulate multipath phenomena
        2,		//	int BackgrSurface;				// type of Earth background surface - see above comments
        0,		//  int SeaState
        1,		//	int	  rain_pres;				// rain clutter presense sign
        4,		//	double rain_rate;				// rainfall rate mm/hour
        -5.,	//	double rain_vel;				// rain radial velocity (m/sec)
        5.,		//	double rain_velstd;				// rain velocity std (m/sec)
        0.,		//	double rain_rmin;				// rain min range in m
        100000,	//	double rain_rmax;				// rain max range in m
        5000,	//	double rain_hmax;				// rain max altitude in m
        45*D_TO_R,	//	double wind_az;				// azimuth direction of wind velocity (rad)
        2.6,//	double wind_vel;					// wind velocity (m/s)
        3,	//	double vel_dev;						// wind velocity deviation (m/s)
};

typedef struct
{
    double stepR;// m, is filled in initialization RadSim
    double stepAz;// rad, is filled in initialization RadSim
    double initR;//m, initial range for calculation ClutAux
    int Naz;// =2PI/stepAz
    int Nrg;// =(150000 - initR)/stepR
    double ClAux[2000000];//
} ClutMap_type;
// Structure of ClAux:
//NRG in current Az direction where CNR>0, CNR(initR), CNR(initR+stepR), CNR(initR+2*stepR),...CNR(150000), //az=0
//NRG in current Az direction where CNR>0, CNR(initR), CNR(initR+stepR), CNR(initR+2*stepR),...CNR(150000), //az=stepAz
//NRG in current Az direction where CNR>0, CNR(initR), CNR(initR+stepR), CNR(initR+2*stepR),...CNR(150000), //az=2*stepAz
//...
//NRG in current Az direction where CNR>0, CNR(initR), CNR(initR+stepR), CNR(initR+2*stepR),...CNR(150000)//az=~2PI
//Here CNR - precalculated value of surface CNR (voltage) ratio without taking into account Receive Beam Pattern by Elevation and waveform ambiguity by R


typedef struct
{
    int GrN;//number of CNR ground points for current azimuth direction (<=100)
    double R_gr[100];//array of ranges where ground clutter point is presented (step >=100 m), in m
    double El_gr[100];//array of elevations where ground clutter point is presented, in rad
    double A_gr[100];//array of signals reflected from ground clutter (one way), in voltage
    double A_gr_beam[100][15];//array of signals reflected from ground clutter (two way)for every beam by elevation, in voltage
} ClutGrArray;
//structure for simulation ground clutter signals in Full mode (RSP)
//contain set of signals reflected from ground clutters (simulation by H profile and Weibull distribution)
//signals calculate with taking into account range blanks and one way antenna pattern (transmit)


// Plots accumulating structure:
typedef struct
{
    int p;
    double az_deg[1000];
    double el_deg[1000];
    double r_m[1000];
}PlAccum_type;
extern PlAccum_type *pPlAccum;

#endif
