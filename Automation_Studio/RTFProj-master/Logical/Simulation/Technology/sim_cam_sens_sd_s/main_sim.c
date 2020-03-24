/*********************************************************************************************
* B&R Automation - Perfection in Automation (https://www.br-automation.com)
    ******************************************************************************************
    * Program 	    : Bachelor's Thesis
    * Author  	    : Lubo Bubco, Radek Otradovský
    * Created 	    : date ... 
	* University    : Brno University of Technology(BUT)
	* Faculty       : Faculty of Mechanical Engineering(FME), Faculty of Electrical Engineering and Communication(FEEC)
**********************************************************************************************
* Implementation OF PROGRAM sim_cam_sens_sd_s(Simulation/Technology/sim_cam_sens_sd_s/main_sim.c)
**********************************************************************************************/
    
#include <bur/plctypes.h>
#include <string.h>
#include <math.h>
#include "rp_funcx1.h"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

_LOCAL struct measurement_ofScore measurement_ofScore_1;

void _INIT ProgramInit(void)
{
    
}

void _CYCLIC ProgramCyclic(void)
{
    measurement_ofScore(&measurement_ofScore_1);
}


