/******************************************************************************
*					 
*  FILE NAME:	    TgtSimPar_type.h
*
*  PURPOSE:	        Data structure of Target Simulator Parameters for LSim
*					which can be changed by menu
*
*  DEVELOPMENT HISTORY:	
*     Date         Author		Description Of Change                    
*     -----        -------		----------------------   
*     2010/08/21   Korolev		Development           
*
*  REMARKS:             		
******************************************************************************/

#ifndef TGTSIMPAR_TYPE_H
#define TGTSIMPAR_TYPE_H   /* to avoid repetition of this file include  */

#include "MathConst.h"

const int NTGT_MAX	  = 100;		  // Number of track arrays (for memory reservation)

const int TGT_SIM_RANGE_MAX = 460000;// Max of range simulation (m) 

const int TGT_VAR_NUM = 10;
/////////////////////////////////////////////////////////////////////////////////

				/* TARGET Type Constants */
const	int 
		AIRTYPE     = 3,	//AIRCRAFT
		ARMTYPE		= 9,	//Anti-Radar Missile 
		TBMTYPE		= 6,    //Tactical Ballistic missile 
		ALCMTYPE	= 7,	//Cruise Missile -Flying above a surface
		JAMMERTYPE  = 0;
		
/////////////////////////////////////////////////////////////////////////////////

const int RAN_MAX	= 10;
const int A_N		= 6;	// Maximum number of aircraft  
const int R_N		= 5;	// Maximum number of ARMs 
const int T_N		= 5;    // Maximum number of TBMs 
const int C_N		= 5;	// Maximum number of SCM 
const int JAM_MAX	= 5;

//AIR//////////////////////////////////////////////////////////////////////////
				/* Air Target Group Order Type Constants */
const int CHAIN_TYPE = 0,	// Chain 
		  WEDGE_TYPE = 1,	// Wedge 
          FRONT_TYPE = 2;	// Front 

				/* Air Target Maneuver Type Constants */
const int NO_MAN	= 0,       // No Maneuver 
      JINKING_MAN	= 1,       // Jinking via velocity value changing 
      ONE_EIGHTY	= 2,       // 180 degree turn in any plane 
      THREE_SIXTY	= 3,       // 360 degree turn in any plane 
      SIDE_JINKING	= 4,       // Jinking via flight direction changing 
      ALT_CHANGE	= 5,       // Altitude change 
      TURN_MAN		= 6,       // Flight direction change in horizontal plane 
      SNAKE_P_MAN	= 7,       // Snake man (type path is parallel. lines) 
      SNAKE_S_MAN	= 8,       // Snake man(type path is Sinus-line)
      OVAL_MAN		= 9;       // Oval man

				/* ARM Type Constants */
const int COMMON_ARM = 0;         // Common (Air) ARM 

				/* SCM Type Constants */
const int	ACM_TYPE =  0;        // Strategic Cruise Missile -Flying above a surface
const int	TCM_TYPE =  1;        // Strategic Cruise Missile -Flying polinom

				/* TBM Type Constants */
const int COMMON_TBM =    0;      // TBM 

				/* ECM Type Constants */
const int	NO_ECM     = 0,  	    // No ECM 
			ESJ_TYPE   = 1,  	    // Escort Jamming 
			SSJ_TYPE   = 2,         // Self Screen Jamming 
			RGPO_TYPE  = 3,         // Range Gate Pull-Off 
			VGPO_TYPE  = 4,         // Velocity Gate Pull-Off 
			RVGPO_TYPE = 5;         // Range & Velocity Gate Pull-Off 

/////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
 int      type,		// REZ		Aircraft- type=3 
	      t0,		// Start time (s) 
	      r,		// Initial horizontal range (< 350000 m)
	      h;		// Altitude (<35000 m) 		   
 double   b;		// Initial azimuth (0 - 360 deg) 
 int	  v;		// Speed (0 - 700m/s) 
 double	  dir;		// Flight direction (0 - 360 deg) 		  
 int      n,		// Number of aircraft in the group (0 - A_N) 
          fo,		// Flight order (CHAIN_TYPE, WEDGE_TYPE, FRONT_TYPE) 
	      dis,		// Distance between next aircraft (100 - 3000 m) 
          mtyp,		// Type of manoeuvre: 
							//	0 - No_MAN			(No manoeuvre)
							//	1 - JINKING_MAN		(Jinking via velocity value changing)
							//	2 - ONE_EIGHTY		(turn on 180 deg)
							//	3 - THRE_SIXTY		(turn on 180 deg)
							//	4 - SIDE_JINKING	(Jinking via flight direction changing)
							//	5 - ALT_CHANGE		(Altitude change)
							//	6 - TURN_MAN		(Flight direction change in horizontal plane)
							//	7 - SNAKE_P_MAN		(Snake manoeuvre: type path is parallel. lines)
							//  8 - SNAKE_S_MAN		(Snake manoeuvre: type path is Sinus-lines) 
							//	9 - OVAL			(Oval manoeuvre: type path is oval)
          rm,		// Slant distance of manoeuvre beginning (<r m) 
					// for SNAKE_P_MAN: Length of a linear zone  
          am;		// Manoeuvre angle (maneuvre plane for ONE_EIGHTY,THRE_SIXTY or turn angle for TURN_MAN) (+180 - -180 deg) 
 double   rcs;		// RCS (1.0 - 15.0 m2) 
 int      swr,		// Swerling case # (0-4) 
          ecm;		// REZ		  
 double	  sdp;		// Jamming spectral density of power for (0 - 999 W/MHz) 
 double   a;		// Acceleration for SNAKE_ and OVAL manoeuvre (0 - 8g) 
} RandTgt_type;
//----------
typedef struct
{ 
	int		type,	//REZ+ Type of tgt SCM=7
			mtype, // REZ	ARM type 
			t,     // Start time (s) 
			h,     // Initial altitude for COMMON_ARM (25 - 15000 m) 
			r;     // Initial horizontal range (1000 - 99999 m) 
	double	b;     // Azimuth (0 - 360 deg) 
	int		v,     // Speed for 500 - 800 m/s) 
			aa;    // Angle of attack for COMMON_ARM (10 - 90 deg) 
	double	rcs;   // RCS (0.1 - 0.2 m2) 
	int		swr;   // Swerling case # (0 - 4)  
} ARMPathPar_type;
//---------------
typedef struct
{ 
 int      type,  //REZ	 TBM type (COMMON_TBM)
	      t,     // Start time (s) 
		  Tf,    //REZ	 
	      r,     // Horizontal range (initial for COMMON_TBM ) (1000 - 99999 m)
	      h;     // Initial altitude for COMMON_TBM (50000 - 80000 m) 		   
 double   b;     // Azimuth (initial for COMMON_TBM ) (0 - 360 deg) 
 int      v;     // Initial speed for COMMON_TBM (2000 m/s) 
 double	  dir,   // Flight direction (0 - 360 deg) 
		  ent,   // Re-entry angle for COMMON_TBM (30 - 50 deg) 
          bf,    // Ballistic factor for COMMON_TBM (0 - 0.01 m2/kg)
          rcs;   // RCS (0.2 - 0.4 m2) 
 int      swr;   // Swerling case # (0 - 4)   
} TBMPathPar_type;


//--------------
typedef struct
{
	int		type,	//REZ+ Type of tgt ARM=6
			mtype,  //REZ	+ Type of SCM (ACM_TYPE, TCM_TYPE)
			t,     //+ Start time (s) 
			r,     // Initial horizontal range (1000 - 99999 m) 
			h;     //+ Altitude (60 - 6000 m)		  
	double	b;     // Initial azimuth (0 - 360 deg) 
	int		v;     //+ Speed (0 - 300 m/s) 
	double	dir,   // Flight direction (0 - 360 deg) 
			rcs;   //+ RCS (0.2  - 0.4 m2) 
	int		swr;   //+ Swerling case # (0 - 4) 
	double	ra;    // Random acceleration (0 - 9.99 m/s2) 
} SCMPathPar_type;
const int N_POINT = 500;
typedef struct
{
	int		np;			//amount of point
	double	t[N_POINT], // time (s) 
			x[N_POINT],	//x- Cartesian coordinates (m) on t[i] 
			y[N_POINT], //y-
			z[N_POINT]; //z-
} SCMTrackPar_type;

//-----------
typedef struct
{
 int	type,				// REZ		Jammer- type =0
		range;              // Initial range (m) (50 - 18000 m)
 double azimuth;            // Initial azimuth (0 - 360 degree)
 int	swr;                // Swerling case # of fluctuations ()
 double rcs,                // Radar cross section (0.1 - 500 m2 )
	    t0,                 // Start time (0 - 5 s)
		sdp;				// Spectral density of power (0 - 999.99 W/MHz) 
} JamTgt_type;

//###### REZERV ##################################################
/*
typedef struct
{
 int	type,       //REZ  Ship- type=4
        mtyp,		//+ Model of Ship: 0 - Small, 1 - Middle, 2 - Large, 3 - Dinghy
								//Model of Ship:	0 -Small	(rcs=510m2,		ton=<200t), 
								//					1 -Middle	(rcs=3000m2,	ton=<750t), 
								//					2 -Large	(rcs=12000m2,	ton=3000t), 
								//					3 -Dinghy	(rcs=5m2,		ton=<1t)
		range,      // Initial range (< 150000 m)
		height,		// Height of ship (m)
		velocity;   // Velocity (0 - 20 m/s)
 double azimuth,    // Initial azimuth (0 - 360 degree)
		direction,	// Direction of movement (0 - 360 deg) 
		ton,		//REZ Displacement (tons) 
		rcs;		// f(r) RCS (see mtyp) 
 int	swr,        // Swerling case # of fluctuations ()
		species;	//REZ:    Ship mode:....
 double t0,         // Start time (0 - 5 s)
		sdp;		// Spectral density of power (0 - 999 W/MHz) 
} ShipTgt_type;
*/

//###################################################################

//summ struct-----------------------------------------------------------------
typedef struct
{
	int var;							// Choice of input data (0-Menu,>0 - Fixed set of data)   
//   
	int nRAND;							// Amount of random Air targets
	RandTgt_type randTgt[RAN_MAX];		// Rand Air targets parameters
//   
	int rn;								// Amount of ARMs 
	ARMPathPar_type rin[R_N];			// ARM parameters
//   
	int tn;								// Amount of of TBMs 
	TBMPathPar_type tin[T_N];			// TBM targets parameters
//	
	int cn;								// Amount of SCMs 
	SCMPathPar_type cin[C_N];			// SCM parameters
//  
	int nJAM;							// Amount of jamm targets
	JamTgt_type jamTgt[JAM_MAX];		// Jamm targets parameters
} TgtSimPar_type;

const TgtSimPar_type TGTSIMPAR[] = //TGT_VAR_NUM
{
	{	0,		//MAX_TEST	 0-variant 			
		10,{	
//		type	t0     r       h    Az   v   dir  n  fo  dist typman  rm   am rcs swr ecm sdp av			 
	{AIRTYPE   , 0, 250000,  2000, 310, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  10},
	{AIRTYPE   , 0, 252000,  4000, 315, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 254000,  6000, 320, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 256000,  8000, 325, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 258000, 10000, 330, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 260000, 11000, 335, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 262000, 12000, 340, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 264000, 13000, 345, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 266000, 14000, 350, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 268000, 15000, 355, 700, 160, 5,  0, 2000,   0,  40000, 0, 2,  1,  0,  0,  4}
		},
		5,{	
//   		 type	 mtype  t    h      r    az   v  ang  rcs swr
			{ARMTYPE, 0,   0, 5000, 60000,  15, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000,  30, 600, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000,  45, 500, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000, 195, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000, 215, 500, 20, 0.1, 1}
		},
		5,	{
//			  type  t Tf     r     h   b    v dir ent    bf rcs swr
		{COMMON_TBM,0, 0,60000, 5000,215,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,60000, 5000,225,1750,45,  35,0.001,0.4,1},
		{COMMON_TBM,0, 0,60000, 5000,235,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,60000, 5000,245,1750,45,  25,0.001,0.4,1},
		{COMMON_TBM,0, 0,60000, 5000,255,1800,45,  30,0.001,0.4,1}
		 },
		0,{	
//  		type    mtype  t    r       h    az   v   dir  rcs swr ra
			{ALCMTYPE, 0,  0,  70000,  100,  90, 280, 270, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 135, 280, 315, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  40000,   90, 180, 280,   0, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  90000,   90, 225, 280,  45, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 270, 280,  90, 0.2, 1,  0}
		 },
		 0,{	
//            type         r     az swr rcs t0 sdp
			{JAMMERTYPE,  5000,  50, 0,  20, 0, 1},
			{JAMMERTYPE, 15000,  90, 0,  20, 0, 1},
			{JAMMERTYPE, 35000, 150, 0,  20, 0, 1},
			{JAMMERTYPE, 45000, 180, 0,  20, 0, 1},
			{JAMMERTYPE, 75000, 330, 0,  20, 0, 1}
		 }
	},

	
	//===========================================================
	{
		1,	//TURN_MAN		1-variant	
		4,	{	
//		type	t0     r       h    Az   v   dir  n  fo  dist typman  rm     am  rcs swr ecm sdp av			 
	{AIRTYPE   , 0, 250000,  3000, 255, 300,  55, 1,  0, 1500,   6,  40000,  30,  2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 250000,  2000, 235, 300,  35, 1,  0, 1500,   6,  40000, -30,  2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 250000,  4000,  35, 300, 215, 1,  0, 1500,   6,  40000,  30,  2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 250000,  5000,  55, 300, 235, 1,  0, 1500,   6,  40000, -30,  2,  1,  0,  0,  4},
			
	{AIRTYPE   , 0,  50000,  1000,  80, 500, 270, 1,  0, 1500,   2,  30000, 0,  5,  1,  0,  0,  4},
	{AIRTYPE   , 0,  50000,  5000, 160, 500,   0, 1,  0, 1500,   3,  30000, 0,  5,  1,  0,  0,  4},
	{AIRTYPE   , 0,  60000, 10000, 270, 500,  90, 1,  0, 1500,   2,  30000, 0,  5,  1,  0,  0,  4},
	{AIRTYPE   , 0,  60000, 14000, 340, 500, 180, 1,  0, 1500,   3,  30000, 0,  5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 100000,  4600, 350, 400, 160, 1,  0, 3000,   0,  40000, 0,  5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 100000,  4800, 355, 400, 160, 1,  0, 3000,   0,  40000, 0,  5,  1,  0,  0,  4}
			},
		0,{	
//   		 type	 mtype  t    h      r    az   v  ang  rcs swr
			{ARMTYPE, 0,   0, 5000, 60000,  15, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000,  30, 600, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000,  45, 500, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000, 195, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000, 215, 500, 20, 0.1, 1}
		  },
		0,	{
		{COMMON_TBM,0, 0,70000,50000,215,1800,45,30,0.001f,0.4f,1},
		{COMMON_TBM,0, 0,80000,60000,225,1750,45,35,0.001f,0.4f,1},
		{COMMON_TBM,0, 0,85000,50000,235,1800,45,30,0.001f,0.4f,1},
		{COMMON_TBM,0, 0,80000,70000,245,1750,45,25,0.001f,0.4f,1},
		{COMMON_TBM,0, 0,80000,50000,255,1800,45,30,0.001f,0.4f,1}
		 },
		0,{	
//  		type    mtype  t    r       h    az   v   dir  rcs swr ra
			{ALCMTYPE, 0,  0,  70000,  100,  90, 280, 270, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 135, 280, 315, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  40000,   90, 180, 280,   0, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  90000,   90, 225, 280,  45, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 270, 280,  90, 0.2, 1,  0}
		 },
		0,{	
//            type         r     az swr rcs t0 sdp
			{JAMMERTYPE,  5000,  50, 0,  20, 0, 1},
			{JAMMERTYPE, 15000,  90, 0,  20, 0, 1},
			{JAMMERTYPE, 35000, 150, 0,  20, 0, 1},
			{JAMMERTYPE, 45000, 180, 0,  20, 0, 1},
			{JAMMERTYPE, 75000, 330, 0,  20, 0, 1}
		  }
	},
//===============================================
	{
		2,	//DEMO		2-variant 							//OLD -Low Alt Tgt
		5,	{	
//		type	t0     r       h    Az   v   dir  n  fo  dist typman  rm   am  rcs  swr ecm sdp av			 
	{AIRTYPE   , 0, 150000,  2000, 310, 500, 150, 1,  0, 3000,   0,  40000, 0, 2,   1,  0,  0,  4},
	{AIRTYPE   , 0, 160000,  6000, 320, 400, 150, 1,  0, 3000,   0,  40000, 0, 2,   1,  0,  0,  4},
	{AIRTYPE   , 0, 220000, 10000, 330, 700, 150, 1,  0, 3000,   0,  40000, 0, 100, 1,  0,  0,  4},
	{AIRTYPE   , 0, 180000, 12000, 340, 300, 150, 1,  0, 3000,   0,  40000, 0, 2,   1,  0,  0,  4},
	{AIRTYPE   , 0, 190000, 14000, 350, 100, 150, 1,  0, 3000,   0,  40000, 0, 2,   1,  0,  0,  4},
	{AIRTYPE   , 0, 252000,  4000, 315, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,   1,  0,  0,  4},
	{AIRTYPE   , 0, 256000,  8000, 325, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,   1,  0,  0,  4},
	{AIRTYPE   , 0, 260000, 11000, 335, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,   1,  0,  0,  4},
	{AIRTYPE   , 0, 264000, 13000, 345, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,   1,  0,  0,  4},
	{AIRTYPE   , 0, 268000, 15000, 355, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,   1,  0,  0,  4}
			},
		0,{	
//   		 type	 mtype  t    h      r    az   v  ang  rcs swr
			{ARMTYPE, 0,   0, 5000, 60000,  15, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000,  30, 600, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000,  45, 500, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000, 195, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000, 215, 500, 20, 0.1, 1}
		  },
		0,	{
//			  type    t Tf     r     h   b    v dir ent    bf rcs swr
		{COMMON_TBM,0, 0,70000,50000,215,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,60000,225,1750,45,  35,0.001,0.4,1},
		{COMMON_TBM,0, 0,85000,50000,235,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,70000,245,1750,45,  25,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,50000,255,1800,45,  30,0.001,0.4,1}
		 },
		0,{	
//  		type    mtype  t    r       h    az   v   dir  rcs swr ra
			{ALCMTYPE, 0,  0,  70000,  100,  90, 280, 270, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 135, 280, 315, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  40000,   90, 180, 280,   0, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  90000,   90, 225, 280,  45, 0.2, 1,  0},
			{ALCMTYPE, 0,  0,  50000,  100, 270, 280,  90, 0.2, 1,  0}
		 },
		0,{	
//            type         r     az swr rcs t0 sdp
			{JAMMERTYPE,  5000,  50, 0,  20, 0, 1},
			{JAMMERTYPE, 15000,  90, 0,  20, 0, 1},
			{JAMMERTYPE, 35000, 150, 0,  20, 0, 1},
			{JAMMERTYPE, 45000, 180, 0,  20, 0, 1},
			{JAMMERTYPE, 75000, 330, 0,  20, 0, 1}
		  }
	},
//============================================================
	{
		3,	//SCM (Polynom)		3-variant 							//OLD -Low Alt Tgt
		0,	{	
//		type	t0     r       h    Az   v   dir  n  fo  dist typman  rm   am  rcs swr ecm sdp av			 
	{AIRTYPE   , 0, 150000,  2000, 310, 500, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 160000,  6000, 320, 700, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 170000, 10000, 330, 400, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 180000, 12000, 340, 300, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 190000, 14000, 350, 100, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 252000,  4000, 315, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 256000,  8000, 325, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 260000, 11000, 335, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 264000, 13000, 345, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4},
	{AIRTYPE   , 0, 268000, 15000, 355, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4}
			},
		0,{	
//   		 type	 mtype  t    h      r    az   v  ang  rcs swr
			{ARMTYPE, 0,   0, 5000, 60000,  15, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000,  30, 600, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000,  45, 500, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 4000, 60000, 195, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000, 215, 500, 20, 0.1, 1}
		  },
		0,	{
//			  type    t Tf     r     h   b    v dir ent    bf rcs swr
		{COMMON_TBM,0, 0,70000,50000,215,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,60000,225,1750,45,  35,0.001,0.4,1},
		{COMMON_TBM,0, 0,85000,50000,235,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,70000,245,1750,45,  25,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,50000,255,1800,45,  30,0.001,0.4,1}
		 },
		1,{	
//  		type    mtype  t    r       h     az   v   dir  rcs swr ra
			{ALCMTYPE, 1,  0,  70000,  1000,  90, 500, 270, 0.2, 1,  0}
		 },
		0,{	
//            type         r     az swr rcs t0 sdp
			{JAMMERTYPE,  5000,  50, 0,  20, 0, 1},
			{JAMMERTYPE, 15000,  90, 0,  20, 0, 1},
			{JAMMERTYPE, 35000, 150, 0,  20, 0, 1},
			{JAMMERTYPE, 45000, 180, 0,  20, 0, 1},
			{JAMMERTYPE, 75000, 330, 0,  20, 0, 1}
		  }
	},
//============================================================
	{
		4,	//Ground clutter forming		4-variant 						
		0,	{	
//		type	t0     r       h    Az   v   dir  n  fo  dist typman  rm   am  rcs swr ecm sdp av			 
	{AIRTYPE   , 0, 150000,  2000, 310, 500, 150, 1,  0, 3000,   0,  40000, 0, 2,  1,  0,  0,  4},
	{AIRTYPE   , 0, 268000, 15000, 355, 700, 160, 1,  0, 3000,   0,  40000, 0, 5,  1,  0,  0,  4}
			},
		0,{	
//   		 type	 mtype  t    h      r    az   v  ang  rcs swr
			{ARMTYPE, 0,   0, 5000, 60000,  15, 630, 20, 0.1, 1},
			{ARMTYPE, 0,   0, 3000, 60000, 215, 500, 20, 0.1, 1}
		  },
		0,	{
//			  type    t Tf     r     h   b    v dir ent    bf rcs swr
		{COMMON_TBM,0, 0,70000,50000,215,1800,45,  30,0.001,0.4,1},
		{COMMON_TBM,0, 0,80000,50000,255,1800,45,  30,0.001,0.4,1}
		 },
		0,{	
//  		type    mtype  t    r       h     az   v   dir  rcs swr ra
			{ALCMTYPE, 1,  0,  70000,  1000,  90, 500, 270, 0.2, 1,  0}
		 },
		0,{	
//            type         r     az swr rcs t0 sdp
			{JAMMERTYPE,  5000,  50, 0,  20, 0, 1},
			{JAMMERTYPE, 75000, 330, 0,  20, 0, 1}
		  }
	}
//============================================================
};
 #endif
/************************************ END of FILE *****************************/























//REZERVE
//-------------
/*typedef struct
{   
 int      type,  // Helicopter type =5 
	      t,     // rez 
	      r,     // Initial horizontal range (1000 - 150000 m) 
	      h;     // Altitude (0 - 5000 m) 		  
 double   t0;    // Start time (0 - 5 s)
 float    b;     // Initial azimuth (0 - 360 deg) 
 int      v;     // Speed (0 - 150 m/s) 
 float	  dir;   // Flight direction (0 - 360 deg) 
 int	  rad;   // Radius of circle trajectory (0 - 50000 m, 0-linear path) 
 float    hvd,   // Hub spectrum velocity deviation (0 - 15.0 m/s)  
          rcs;   // RCS (1 - 5.0  m2) 
 int      swr;   // Swerling case # (0 - 4) 
 float	  sdp;   // Jamming spectral density of power (0 - 999.99 W/MHz) 		  
} HelPathPar_type;
*/
/*
typedef struct 
{
 int	type,	// REZ		SSST- type=1
        mtyp;	// Type of manoeuvre: 0 - SIMPLE_MAN, 1 - COMPLICATED_MAN+; 
 double r,		// Initial range (<25000 m)
		b,		// Initial azimuth (0 - 360 deg) 
		re,		// 0 - SIMPLE_MAN ONLY : Range after manoeuvre (m) 
		v,		// Initial velocity (<1000 m/s)
		ve,		// Velocity after manoeuvre (m/s)
		h,		// Initial altitude (<100 m)
		he,		// Sea Skimming Altitude (after manoeuvres, 5<he<h) (m)
		dir,	// Flight direction (235-305 deg - SIMPLE_MAN)
		tman,	//+ Time  of beginning  of manoeuvre after start time (0 - 3 s)
		nCycle,	//+ Number of modifications of flight direction (1 per 5000m ~10g)
		ga,		//REZ Max of longitudinal manoeuvre overload for azimuth (<10 g)
		ge,		//REZ Max of longitudinal manoeuvre overload for elevation (<7 g)
		gs,		//REZ Max of longitudinal manoeuvre overload for speeding-up (<15 g)
		gb;		//REZ Max of longitudinal manoeuvre overload for braking (<15 g)
 int	swr;    // Swerling case # of fluctuations (0 - 1)
 double rcs,    // Radar cross section (0.1 - 1.0 m2)
		hm,		//+ Normal Crossing Altitude (between manoeuvres, h>hm>he)(m)
	    t0,     // Start time (0 - 5 s)
		sdp;	// REZ		Spectral density of power	(0 - 999.99 W/MHz) 
} SSSTgt_type;

typedef struct 
{
 int type,			// REZ		ASM- type=2
	 rand_type, 	// REZ		
	 range,         // Initial range (m) ( m)
     velocity;      // Initial velocity (70 - 700 m/s)
 double azimuth,    // Initial azimuth (0 - 360 deg)
        elevation,  // Initial elevation (0 - 30 deg)
		az_shift, 	// REZ
        az_sector;  // REZ
 int swr;           // Swerling case # of fluctuations ()
 double rcs,        // Radar cross section (0.1 - 5.0 m2)
	    t0,         // Start time (0 - 5 s)
		sdp;		// REZ		Spectral density of power	(W/MHz) 
} ASMTgt_type;
*/
//  -----------------  REZERV  --------------------------------
//   
	//int nHEL;							// Amount of helicopters 
	//HelPathPar_type helTgt[HEL_MAX];	// Helicopter parameters
//   
//		int nSSST;	//SSS parameters 	// Amount of SSSTs 
//		SSSTgt_type ssstTgt[SSST_MAX];	// SSST parameters
//		int nASM;	//ASM parameters	// Amount of ASMs 
//		ASMTgt_type asmTgt[ASM_MAX];	// ASM parameters
//   
	//int nSHIP;							// Amount of ship targets
	//ShipTgt_type shipTgt[SHIP_MAX];		// Ship targets parameters
// ------------------------------------------------------------

		//0,{	
//			type    subtype   r     h    v     Az   dir   -  rcs swr - t0 sdp
		//	{SHIPTYPE  , 1, 115000, 10,	20,	  250,   70,  0,  0,  1, 0, 0, 0},
		//	{SHIPTYPE  , 2, 100000, 15,	10,	  230,   60,  0,  0,  1, 0, 0, 0},
		//	{SHIPTYPE  , 3, 155000, 10,	20,	  250,   70,  0,  0,  1, 0, 0, 0},
		//	{SHIPTYPE  , 2, 110000, 15,	10,	  230,   60,  0,  0,  1, 0, 0, 0},
		//	{SHIPTYPE  , 0,  80000,  4,	10,	  240,  120,  0,  0,  1, 0, 0, 0}
		//  },
		//0,{	
//			type    subtype   r    Az     re    v    ve   h he  dir tm cyc ga  ge gs  gb swr rcs  hm t0 sdp
		//	{SKIMERTYPE, 0, 20000, 90,  10000, 800, 400, 50, 6, 270, 2, 2, 10, 7, 15, 15, 1, 0.1, 20, 0, 0}
		//  },
		//0,{	
//            type  r_type	  r     v   az 	  el azs azc swr rcs t0 sdp
		//	{ASMTYPE   , 0, 20000, 500, 100, 0.3, 5,  0,  1,  1,  0, 0}
		 // },
