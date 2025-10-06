//******************************************************************************
//******************************************************************************
//*																			 
//*	1. FILE NAME:		 Complex.cpp											
//*																			
//*	2. DESCRIPTIONS:	 Aux math functions to operate with complex numbers  
//*                                                  
//* 3. PROGRAMMER: 	     V. Shashkin 	    
//*												
//* 4. UPDATE HISTORY:   2006/02/02 - Development	
//*
//*
//******************************************************************************
//******************************************************************************

//#include "stdafx.h"
#include <math.h>

void c_mult(double re1, double im1, double re2, double im2, double *re_out, double *im_out)
{
	double re = re1*re2 - im1*im2;
	double im = re1*im2 + re2*im1;
	*re_out   = re;
	*im_out   = im;
}

void c_div(double re1, double im1, double re2, double im2, double *re_out, double *im_out)
{
	double re =  re1*re2 + im1*im2;
	double im = -re1*im2 + re2*im1;
	double a  = re2*re2 + im2*im2 + 1e-10;
	*re_out   = re/a;
	*im_out   = im/a;
}

double c_phase(double re, double im)
{
	return(atan2(im, re));
}

double c_norm(double re, double im)
{
	return(re*re + im*im);
}

double c_abs(double re, double im)
{
	return(sqrt(re*re + im*im));
}

void c_sqrt(double re, double im, double *re_out, double *im_out)
{

	double r     = sqrt(c_abs(re, im));
	double phase = 0.5*c_phase(re, im);
	*re_out      = r * cos(phase);
	*im_out      = r * sin(phase);
}
/*---------------------------------------------------------------------------*/
