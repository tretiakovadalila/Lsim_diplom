/******************************************************************************
*  FILE NAME:	Rnd.cpp
*
*  PURPOSE:		Set of functions to generate random numbers
*
*  FUNCTIONS LIST:
*
*  DEVELOPMENT HISTORY:	
*     Date         Author      Description Of Change                    
*     -----        -------     ----------------------   
*     2003/12/31   V_Shash     ReDevelopment           
*
******************************************************************************/

#include <math.h>

#include "MathConst.h"

static double s_qrnrtab[65536]; 

static int sign_qrnr_init = 0;; 

/*******************************************************************************
 * Function name:   rnd()                               		
 * Description:     random numbers generator with even 0-1 distribution         
 * Arguments:       none	
 * Return value:    random number	
 * Called from:     General purpose	
 ******************************************************************************/
static unsigned long s_lrnd=987654321;

double rnd(void)
{
s_lrnd *= 65539;
return(s_lrnd*0.2328305e-9);
}
/*---------------------------End of function ---------------------------------*/

/*******************************************************************************
 * Function name:   rnr()                               		
 * Description:     random numbers generator with Gauss (mean=0,variation=1)distribution
 * Arguments:       none
 * Return value:    random number	
 * Called from:     General purpose		
 ******************************************************************************/
double rnr(void)
{
double r, s;
r = rnd(); s = rnd();
r = sqrt(-2.*log(r)); s = 2*_PI*s;
return(r*sin(s));
/*return(r*cos(s));*/
}
/*---------------------------End of function ---------------------------------*/

/*******************************************************************************
 * Function name:   qrnr_init()                               		
 * Description:     Initialization of table consisting of 65536 float point words
 *                  with Gauss random numbers    
 * Return value:    none	
 * Called from:     General Purpose	
 ******************************************************************************/
void qrnr_init()
{
unsigned i;double r,s;

for(i=0;i<65536;i+=2)
	{
	r = rnd(); s = rnd();
	r = sqrt(-2.*log(r)); s = 2*_PI*s;
	s_qrnrtab[i]  = r*sin(s); 
	s_qrnrtab[i+1]= r*cos(s);
	}
sign_qrnr_init = 1;
}
/*---------------------------End of function ---------------------------------*/

/*******************************************************************************
 * Function name:   qrnr() 
 * Description:     fast random numbers generator with Gauss (mean=0,variation=1)distribution
 * Arguments:       none
 * Return value:    random number
 * Called from:     General purpose
 * Remark:          function uses the advanced generated s_qrnrtab array
 ******************************************************************************/
double qrnr()
{
static double* rnraddress = &s_qrnrtab[0];
unsigned i;

if(sign_qrnr_init == 0) qrnr_init();

s_lrnd *= 65539;
i = s_lrnd>>16;

return(*(rnraddress+i));
}
/*----------------------------------------------------------------------------*/
/* Fast random numbers generator z = 0.5*(x^2+y^2) where x, y are Gauss (0,1)         */
double qrnr2()
{
unsigned i;
double x, y;

if(sign_qrnr_init == 0) qrnr_init();

i = (unsigned)(65536*rnd()); x = s_qrnrtab[i];
i = (unsigned)(65536*rnd()); y = s_qrnrtab[i];

return(0.5*(x*x+y*y));
}
/*---------------------------End of function ---------------------------------*/


