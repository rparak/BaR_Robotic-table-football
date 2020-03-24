/*********************************************************************************************
* B&R Automation - Perfection in Automation (https://www.br-automation.com)
    ******************************************************************************************
    * Program 	    : Master's Thesis - Soccer Table (Simulation)
    * Author  	    : Roman Parak
    * Created 	    : date ... 
	* University    : Brno University of Technology(BUT)
	* Faculty       : Faculty of Mechanical Engineering(FME)
	* Study Program : Applied Computer Science and Control
	* Institute     : Institute of Automation and Computer Science
**********************************************************************************************
* Implementation OF PROGRAM simulation(rp_library/rp_funcx1/rp_functions.c)
**********************************************************************************************/

/************************************* LIBRARIES *********************************************/
#include <bur/plctypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif

/**********************************************************************************************************/
/************************************** FUNCTIONS & FUNCTIONS BLOCKS **************************************/
/**********************************************************************************************************/

signed short random_number(signed short min_num, signed short max_num)
{	
    signed char result = 0,low_num = 0,high_num = 0;
    
    if(min_num < max_num){
        low_num  = min_num;
        high_num = max_num + 1;
    }else{
        low_num  = max_num + 1;
        high_num = min_num;
    }
	
    result = (rand()%(high_num - low_num)) + low_num;   
    return result;
	
}// end function

void get_rotationalPostition(struct get_rotationalPostition* g_rP)
{
	LREAL mod_pos, lrealPart, x;
	int i;
	
	for(i = 0; i < (int)(sizeof(g_rP->actual_position)/sizeof(g_rP->actual_position[0])); i++){
		if((g_rP->actual_position[i] - g_rP->define_position[i]) == 0){
			g_rP->result[i] = 0;
		}else{		
			if(fabs((g_rP->actual_position[i] - g_rP->define_position[i])) > 3600){
				x       = fabs((g_rP->actual_position[i] - g_rP->define_position[i]))/3600;
				mod_pos = modf(x,&lrealPart);
			
				if((g_rP->actual_position[i] - g_rP->define_position[i]) > 0){
					g_rP->result[i] = (g_rP->actual_position[i] - g_rP->define_position[i]) - (3600*lrealPart);
				}else{
					g_rP->result[i] = (g_rP->actual_position[i] - g_rP->define_position[i]) + (3600*lrealPart);
				}
			}else{
				g_rP->result[i] = fabs((g_rP->actual_position[i] - g_rP->define_position[i]));
			}
		}
	}
	
}// end function