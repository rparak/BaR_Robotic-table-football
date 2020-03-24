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
* Implementation OF PROGRAM simulation(rp_library/rp_funcx1/calculation_posDummiesOpponent.c)
**********************************************************************************************/

/************************************* LIBRARIES *********************************************/
#include <bur/plctypes.h>
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

void calculation_posDummies(struct calculation_posDummies* c_pD)
{
	/*
		Args:
			INPUT
				displacemen : 	     displacement of individual axes()a
								     array of data type REAL, where the index of array is individual axis 
								     e.g. goalkeeper has index 0 etc.
			OUTPUT
				gk_posD 		   : position dummy of the axis name Goalkeeper
									 1 position
				df_posD 		   : position dummies of the axis name Defender
									 2 positions
				md_posD 		   : position dummies of the axis name Midfielder
									 5 positions
				fw_posD 		   : position dummies of the axis name Forward
									 3 positions
				real_displacement  : real displacement, for example due to mistake at reading from the sensors
									 array of data type REAL - all output values	
	*/

	/***************************************** declaration variables ****************************************/
	REAL max_dispOfD[4], min_dispOfD[4], matrix_posOfOpponent[4][5], actual_positions[4][5];
	USINT i,j;
	// Indexes : GK - 0, DF - 1, MD - 2, FW - 3
	// max displacement of dummies
	max_dispOfD[0] = c_pD->max_disp[0];
	max_dispOfD[1] = c_pD->max_disp[1];
	max_dispOfD[2] = c_pD->max_disp[2];
	max_dispOfD[3] = c_pD->max_disp[3];
	// min displacement of dummies
	min_dispOfD[0] = c_pD->min_disp[0];
	min_dispOfD[1] = c_pD->min_disp[1];
	min_dispOfD[2] = c_pD->min_disp[2];
	min_dispOfD[3] = c_pD->min_disp[3];
	// matrix of parameters
	// goalkeeper
	matrix_posOfOpponent[0][0] = 0;
	// defender
	matrix_posOfOpponent[1][0] = -1200;
	matrix_posOfOpponent[1][1] = 1200;
	// midfielder
	matrix_posOfOpponent[2][0] = -2400;
	matrix_posOfOpponent[2][1] = -1200;
	matrix_posOfOpponent[2][2] = 0;
	matrix_posOfOpponent[2][3] = 1200;
	matrix_posOfOpponent[2][4] = 2400;
	// forward
	matrix_posOfOpponent[3][0] = -2100;
	matrix_posOfOpponent[3][1] = 0;
	matrix_posOfOpponent[3][2] = 2100;

	/********************************************* calculation **********************************************/
	for(i = 0; i < (int)(sizeof(c_pD->displacement)/sizeof(c_pD->displacement[0])); i++){
		for(j = 0; j <= (int)(sizeof(c_pD->displacement)/sizeof(c_pD->displacement[0])); j++){
			if(c_pD->displacement[i] > max_dispOfD[i]){
				actual_positions[i][j] 	   = max_dispOfD[i] + matrix_posOfOpponent[i][j];
				c_pD->real_displacement[i] = max_dispOfD[i];
			}else if(c_pD->displacement[i] < min_dispOfD[i]){
				actual_positions[i][j] 	   = min_dispOfD[i] + matrix_posOfOpponent[i][j];
				c_pD->real_displacement[i] = min_dispOfD[i];
			}else{
				actual_positions[i][j]     = c_pD->displacement[i] + matrix_posOfOpponent[i][j];
				c_pD->real_displacement[i] = c_pD->displacement[i];
			}
		}
	}
	
	/**************************************** output real parameters ****************************************/
	// goalkeeper
	c_pD->actual_positionsOfDummies[0]  = actual_positions[0][0];
	// defender
	c_pD->actual_positionsOfDummies[1]  = actual_positions[1][0];
	c_pD->actual_positionsOfDummies[2]  = actual_positions[1][1];
	// midfielder
	c_pD->actual_positionsOfDummies[3]  = actual_positions[2][0];
	c_pD->actual_positionsOfDummies[4]  = actual_positions[2][1];
	c_pD->actual_positionsOfDummies[5]  = actual_positions[2][2];
	c_pD->actual_positionsOfDummies[6]  = actual_positions[2][3];
	c_pD->actual_positionsOfDummies[7]  = actual_positions[2][4];
	// forward
	c_pD->actual_positionsOfDummies[8]  = actual_positions[3][0];
	c_pD->actual_positionsOfDummies[9]  = actual_positions[3][1];
	c_pD->actual_positionsOfDummies[10] = actual_positions[3][2];
	
}// end function
