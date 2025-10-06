//#include "InitMenu_type.h"
#include "L_RadarPar_type.h"

extern RadarPar_type gRadarPar;	

void ElParam(RadarPar_type* pRadarPar,	// input radar parameters
			double *Elw,				// out, width of elevation beams (deg)
			double *Loss);				// out, array of elevation beams (level ~3dB)

void RadarParInit(RadarPar_type* pRadarPar, int beam_el_change)
{
	int search_mode=0;//New
	int mod=pRadarPar->search_mode;

// ============ DBF ==================


if (pRadarPar->n_beams==15 && beam_el_change==0)
{
	for (int j=0; j<NEL_MAX; j++)
	{
        pRadarPar->beam_el[j]=BEAM_EL_15[j];
        pRadarPar->beam_gain_dB=38;
	}
}


double Elw[NEL_MAX], Loss[NEL_MAX];

if (beam_el_change==1 )
{

	ElParam(pRadarPar,Elw,Loss);
}

}




