/***************************************************************************/
/*																		   */
/*	1. FILE NAME:	   InitMenu_type.h		   							   */
/*																		   */
/*	2. DESCRIPTIONS:   Start data structures from Menu to LSim   		   */
/*																		   */
/*  3. PROGRAMMER: 	   Nik      										   */
/*																		   */
/*  4. UPDATE HISTORY: 2005/05/31 										   */
/*																		   */
/***************************************************************************/

#ifndef INIT_MENU
#define INIT_MENU	
    
#ifndef M_A_P     

#include "TgtSimPar_type.h"
#include "L_RadarPar_type.h"
#include "ClutSimPar_type.h"
#include "L_TwsPar_type.h"

const int INSTRUMENTAL_RANGE_M=300000;

typedef struct 
{
	int WndView;// 0-Header, 1-PPI, 2-AntDrv, 3-Rad, 4-RSP, 5-Det, 6-Trc, 7-Log, 8-Exh
	int Dscale; // 300000 m == INSTRUMENTAL_RANGE_M;
	int Hscale; // 15000 m
	int Header;
	int Profile;
	int step;
	int var_zero;

	int RSP_F_Number; 
	int Full_RSP_mode; // 0 - Fast, 1 - Full

	int sound; 
	int trtr;
	int trsim;
	int Background; //  0 - None, 1 - Geographical map, 2 - Grasing map, 3 - Elevation (screening) map
	int UNIT_OF_MEASURE;  // 0 - km, 1 - nm
// Layers:
	int airports;
	int cityesb;
	int cityesm;
	int cityess;
	int cityesp;
	int rivers;
	int border;
	int road;
	int highway;
	int railway;
// Layers sign:
	int air_k;
	int city_k;
	int pcity_k;
	int river_k;
	int border_k;
	int road_k;
	int railway_k;
//---------------
	int RadViewWindow;
	int SimSpeed; // 1 -RealTime,0 - Max 
	int RAD_LOC; // 0 - MapMaker, 1 - U1, 2 - U2, 3 - U3, 4 - YongIn Lab
	int RouteFormation;
	int RSP_view; // 0 - 6
	int RSP_bank; // 0, 1, 2
	char RouteFileName[2048];
} DisplayPar_type;

const DisplayPar_type DISPLAY =
{
	1,	// WndView: 0-Header, 1-PPI, 2-AntDrv, 3-Rad, 4-RSP, 5-Det, 6-Trc, 7-Log, 8-Exh
	INSTRUMENTAL_RANGE_M, // Dscale 
	15000,  // Hscale;
	1,	// Header;
	0,	// Profile;
	0,	// step
	0,	// var_zero 
	0,  // int RSP_F_Number;;
	0,  // Full_RSP_mode; // 0 - Fast, 1 - Full
	0,	// sound	
	1,  // trtr;
	0,  // trsim;
	1,  // 	Background; //  0 - None, 1 - Geographical map, 2 - Grasing map, 3 - Elevation (screening) map
	0,	// UNIT_OF_MEASURE: 0 - km, 1 - nm
// Layers:
	0,	// int airports;
	0,	// int cityesb;
	0,	// int cityesm;
	0,	// int cityess;
	0,	// int cityesp;
	1,	// int rivers;
	1,	// int border;
	0,	// int road;
	0,	// int highway;
	0,	// int railway;
// Layers sign:
	0,	// int air_k;
	0,	// int city_k;
	0,	// int pcity_k;
	0,	// int river_k;
	0,	// int border_k;
	0,	// int road_k;
	0,	// int railway_k;
//---------------
	0,	// RadViewWindow;;
	1,	// int SimSpeed; // 1 -RealTime, 0 - Max 
	2,	// int RAD_LOC; // 0 - MapMaker, 1 - U1, 2 - U2, 3 - U3, 4 - YongIn Lab
	0,	// int RouteFormation;
	0,	// int RSP_view; // 0 - 6
	0,	// int RSP_bank; // 0,1,2
	"..\\Out\\Scm_Track.txt", // char RouteFileName[2048]; 
};

// The Init Menu main structure:
typedef struct 
{
	TgtSimPar_type	pTgtSimPar;
	ClutSimPar_type	pClutSimPar;
	DisplayPar_type	pDisplayPar;
	RadarPar_type	pRadarPar;
	TwsPar_type		pTwsPar;
} INIT_MENU_type;

#endif

const int COL_RED[20]={0,62,63,31,32,37,70,64,105,100,106,65,249,38,71,23,227,22,148,189};
const int NUM_COL_RED=19;
const int COL_BLUE[23]={226,25,220,219,212,213,230,207,173,172,206,205,201,200,197,61,252,167,161,134,162,95,10};
const int NUM_COL_BLUE=22;
const int COL_GREEN[18]={194,193,224,192,156,228,60,250,53,51,118,113,45,40,72,33,34,13};
const int NUM_COL_GREEN=17;

typedef struct 
{
	char CurrentDirectory[2048]; // Exist but not using
	char OUTDirectory[2048];
	char lite_exe[2048];
	char defbin[2048];
	char menu_exe[2048];
	char reZERVVVVVVVVVVVVVVVVVVVVVVVVV[2048];
	char MapMaker[2048];
char REZERVE[2048];
	char RadLoc_bin[2048];
	char ok_button_sign[2048];
	char datalog_h[2048];
	char datalog_p[2048];
	char datalog_pe[2048];
	char datalog_a[2048];
	char explode[2048];
	char gunshot[2048];
	char cone[2048];
	char dangerous[2048];
	char help_chm[2048];
	char title_bmp[2048];
	char title_map_bmp[2048];
//-------
	char REZERV1[2048];
	char REZERV[2048];
	char koreaSea_bmp[2048];
	char PPImapTemp_bmp[2048];
//-------
	char Grazing_bmp[2048];
	char GrazingSea_bmp[2048];
	char GrazingTemp_bmp[2048];
//-------
	char Screening_bmp[2048];
	char ScreeningSea_bmp[2048];
	char ScreeningTemp_bmp[2048];
//--------
	char MemMap_bin[2048];
	char PPImap_bmp[2048];
	char PPImap500_bmp[2048];
} PATH_TO_EXTERNAL;
#endif



