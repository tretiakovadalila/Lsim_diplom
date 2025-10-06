/******************************************************************************
*  FILE NAME:	    L_TwsPar_type.h
*  PURPOSE:	        Structure of TWS parameters for LSim
*					
*
*  DEVELOPMENT HISTORY:	
*     Date         Author      Description Of Change                  
*     -----        -------     ----------------------   
*     2006/04/21   Y_Ilch      Development
*     2006/06/30   Y_Ilch      Upgrade for MHT
*
*  REMARKS:        None     		
******************************************************************************/

#ifndef TWSPAR_TYPE_H
#define TWSPAR_TYPE_H   // to avoid repetition of this file include

				// Multi-Target Tracking Method
const int TWS_MH    = 0;	// MH
const int TWS_MH_NN = 1;	// MH&NN
const int TWS_NN    = 2;	// NN
const int TWS_JP    = 3;	// JP

				// Multi- Hypothesis Parameters
const int MHT_OUT_DELAY      = 1;    // Out data delay (0 - no, 1 - yes)
const int MHT_PREDICT        = 1;    // Out data prediction (0 - no, 1 - yes)
const int MHT_DEPTH          = 3;	 // MaxDepth  
const int MHT_GROUPS         = 100;  // MaxGrHypos  
const double MHT_MIN_MAX = 0.01; // MinMaxRatio
const double MHT_TTDP    = 1E-3; // TrueTrackDelPr
const double MHT_FTCP    = 1E-3; // FalseTrackPr

				// General
const int TWS_RV_USE  = 0;	  // RV usage (0 - no, 1 - yes)
const int TWS_IMM     = 0;    // IMM filtering (0 - no, 1 - yes)
const int TWS_BYES    = 0;    // Byes rule while IMM filtering (0 - no, 1 - yes)	
const int TWS_NO_PLOT = 6;	  // Max scans without plots			

typedef struct
{
 int type,             	  // Type (0 - MH, 1 - MH&NN, 2 - NN, 3 - JP)
	 rv_use,              // RV usage (0 - no, 1 - yes) 
	 imm_filter,          // IMM filter (0 - no, 1 - yes)
     byes,				  // Byes rule while IMM filtering (0 - no, 1 - yes)
	 no_plot_max;		  // Max scans without plots (2 - 6)

			// Next parameters are valid for type == MH only
 int outDelay,            // Out data delay (0 - no, 1 - yes)
	 outPredict,          // Out data prediction (0 - no, 1 - yes)
	 maxDepth,            // MaxDepth (0-6) 	     
     maxGHypos;			  // MaxGrHypos (1-100) 
 double minGHypoRatio,    // MinMaxRatio (0-1)
	    trueTrDelProb,    // TrueTrackDelPr (1E-6 - 1E-1) 
		falseTrackProb;   // FalseTrackPr (1E-6 - 1E-1)
} TwsPar_type;

const TwsPar_type TWSPAR = {TWS_NN,
                            TWS_RV_USE,
							TWS_IMM, 
							TWS_BYES,
							TWS_NO_PLOT,
							MHT_OUT_DELAY,
							MHT_PREDICT,
							MHT_DEPTH,
							MHT_GROUPS,
							MHT_MIN_MAX,
							MHT_TTDP,
							MHT_FTCP};

#endif
/************************************ END of FILE *****************************/