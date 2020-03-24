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
* Implementation OF PROGRAM simulation(rp_library/rp_funcx1/calculation_crossingBall.c)
**********************************************************************************************/

/************************************* LIBRARIES *********************************************/
#include <bur/plctypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif
// declaration function
int cmpfunc(const void *a, const void *b);

void calculation_crossingBall(struct calculation_crossingBall* c_cB)
{
	USINT initial_state;
	USINT count_aI[2];
	USINT i, s_i, t_iB1, t_iB1N, t_iB2, t_iB2N, i_aux, i_loaded, i_timeL, i_fbI, i_fbO;
	BOOL both_ball;
	REAL x_position[2], y_auxiliaryPos[4];
	REAL x_auxiliaryPos[4];
	
	struct arrival_timeOfBall a_tOfBall;
	
	x_auxiliaryPos[0] = c_cB->x_positions[0];
	x_auxiliaryPos[1] = c_cB->x_positions[1];
	x_auxiliaryPos[2] = c_cB->x_positions[2];
	x_auxiliaryPos[3] = c_cB->x_positions[3];
	
	c_cB->act_posOfAxesX[0] = x_auxiliaryPos[0];
	c_cB->act_posOfAxesX[1] = x_auxiliaryPos[1];
	c_cB->act_posOfAxesX[2] = x_auxiliaryPos[2];
	c_cB->act_posOfAxesX[3] = x_auxiliaryPos[3];
	
	x_position[0] = c_cB->ball1_x;
	x_position[1] = c_cB->first_reflection_x;
	
	if(isnan(c_cB->ball2_x) && isnan(c_cB->ball2_y)){
		both_ball = 0;
	}else{
		both_ball = 1;
	}
	
	for(i = 0; i < (int)(sizeof(x_position)/sizeof(x_position[0])); i++){
		if(x_position[i] > x_auxiliaryPos[3]){
			count_aI[i] = 4;
		}else if((x_position[i] > x_auxiliaryPos[2]) && (x_position[i] <= x_auxiliaryPos[3])){
			count_aI[i] = 3;
		}else if((x_position[i] > x_auxiliaryPos[1]) && (x_position[i] <= x_auxiliaryPos[2])){
			count_aI[i] = 2;
		}else if((x_position[i] > x_auxiliaryPos[0]) && (x_position[i] <= x_auxiliaryPos[1])){
			count_aI[i] = 1;
		}else{
			count_aI[i] = 0;
		}
	}
	
	c_cB->count_axesIntersection[0] = count_aI[0];
	c_cB->count_axesIntersection[1] = count_aI[1];
	
	if((fabs(c_cB->second_reflection_x - c_cB->first_reflection_x) < 1500) && (fabs(c_cB->first_reflection_x - c_cB->ball2_x) < 1500)){
		initial_state = 0;
	}else{
		if(c_cB->tilted == 1){
			initial_state = 1;
		}else{
			initial_state = 0;
		}
	}
	
	switch(initial_state){
		case 0:
			{
				// straight direction of ball
				for(s_i = 0; s_i < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); s_i++){
					if(both_ball == 1){
						c_cB->act_posOfAxesY[s_i] = c_cB->ball2_y;
					}else{
						c_cB->act_posOfAxesY[s_i] = c_cB->ball1_y;
					}
				}
			}
			break;
		case 1:
			{
				// tilted direction of ball
				if(c_cB->ball1_x > c_cB->ball2_x){
					for(t_iB1 = 0; t_iB1 < count_aI[0]; t_iB1++){
						if( t_iB1 < count_aI[1]){
							// down direction
							y_auxiliaryPos[t_iB1] = c_cB->first_reflection_y - (c_cB->first_reflection_y - c_cB->second_reflection_y)/((c_cB->first_reflection_x - c_cB->second_reflection_x)/(c_cB->first_reflection_x - x_auxiliaryPos[t_iB1]));
						}else{
							// up direction
							y_auxiliaryPos[t_iB1] = c_cB->ball2_y + ((c_cB->first_reflection_y - c_cB->ball2_y)/((c_cB->ball2_x - c_cB->first_reflection_x)/(c_cB->ball2_x - x_auxiliaryPos[t_iB1])));
						}
					}
					
					for(t_iB1N = count_aI[0]; t_iB1N < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); t_iB1N++){
						y_auxiliaryPos[t_iB1N] = c_cB->ball2_y;
					}
				}else{
					for(t_iB2 = count_aI[0]; t_iB2 < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); t_iB2++){
						if( t_iB2 < count_aI[1]){
							// up direction
							y_auxiliaryPos[t_iB2] = c_cB->ball2_y + (c_cB->first_reflection_y - c_cB->ball2_y)/((c_cB->ball2_x - c_cB->first_reflection_x)/(c_cB->ball2_x - x_auxiliaryPos[t_iB2]));
						}else{
							// down direction
							y_auxiliaryPos[t_iB2] = c_cB->first_reflection_y - (c_cB->first_reflection_y - c_cB->second_reflection_y)/((c_cB->first_reflection_x - c_cB->second_reflection_x)/(c_cB->first_reflection_x - x_auxiliaryPos[t_iB2]));
						}
					}
					
					for(t_iB2N = 0; t_iB2N < count_aI[0]; t_iB2N++){
						y_auxiliaryPos[t_iB2N] = c_cB->ball2_y;
					}
				}
			
				for(i_aux = 0; i_aux < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); i_aux++){
					if((y_auxiliaryPos[i_aux] < -3515) || (y_auxiliaryPos[i_aux] > 3515)){
						y_auxiliaryPos[i_aux] = c_cB->ball2_y;
					}
				}
				
				for(i_loaded = 0; i_loaded < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); i_loaded++){
					c_cB->act_posOfAxesY[i_loaded] = y_auxiliaryPos[i_loaded];
				}	
			}
			break;
		
	}// end switch
	
	if((both_ball == 1 && count_aI[0] != 0) || (count_aI[1] != 0) || (x_auxiliaryPos[0] != 3800)){
		a_tOfBall.ball1_x 			 = c_cB->ball1_x;
		a_tOfBall.ball1_y 			 = c_cB->ball1_y;
		a_tOfBall.ball2_x 		     = c_cB->ball2_x;
		a_tOfBall.ball2_y 			 = c_cB->ball2_y;
		a_tOfBall.first_reflection_x = c_cB->first_reflection_x;
		a_tOfBall.first_reflection_y = c_cB->first_reflection_y;
		// input parameters into the function block arrival time of the ball
		for(i_fbI = 0; i_fbI < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); i_fbI++){
			a_tOfBall.act_posOfAxesX[i_fbI] = c_cB->act_posOfAxesX[i_fbI];
			a_tOfBall.act_posOfAxesY[i_fbI] = c_cB->act_posOfAxesY[i_fbI];
		}
	    a_tOfBall.time_B2B			 	      = c_cB->time_B2B;
		a_tOfBall.tilted	         		  = c_cB->tilted;
		a_tOfBall.count_axesIntersection[0]   = count_aI[0];
		a_tOfBall.count_axesIntersection[1]   = count_aI[1];
		// call function block arrival time of the ball
		arrival_timeOfBall(&a_tOfBall);
		// output parameters
		c_cB->overall_velocity = a_tOfBall.velocity;
		for(i_fbO = 0; i_fbO < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); i_fbO++){
			c_cB->time_axisIntersection[i_fbO] = a_tOfBall.time_aI[i_fbO];
		}
		
	}else{
		c_cB->overall_velocity = 150000;
		
		for(i_timeL = 0; i_timeL < (int)(sizeof(y_auxiliaryPos)/sizeof(y_auxiliaryPos[0])); i_timeL++){
			c_cB->time_axisIntersection[i_timeL] = fabs(x_auxiliaryPos[i_timeL] - x_position[0])/c_cB->overall_velocity ;
		}
		
	}
}// end function

void arrival_timeOfBall(struct arrival_timeOfBall* a_tOB)
{
	USINT initial_state;
	USINT i_eqS, i_B1S, i_B1Sn, i_OS, i_OSn, i_B1T, iB1Tn, iOT, iOTn;
	REAL time_f[4], previous_time;
	
	if(a_tOB->tilted == 1){
		initial_state = 1;
	}else{
		initial_state = 0;
	}
	
	switch(initial_state){
		case 0:
			{
				// straight direction of ball
				if(a_tOB->ball1_x == a_tOB->ball2_x){
					a_tOB->velocity = fabs((a_tOB->ball1_y - a_tOB->ball2_y))/a_tOB->time_B2B;

					for(i_eqS = 0; i_eqS < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); i_eqS++){
						a_tOB->time_aI[i_eqS] = fabs((a_tOB->ball1_y - a_tOB->ball2_y))/a_tOB->velocity;
					}
					
				}else if(a_tOB->ball1_x > a_tOB->ball2_x){
					a_tOB->velocity = fabs((a_tOB->ball1_x - a_tOB->ball2_x))/a_tOB->time_B2B;
					
					for(i_B1S = 0; i_B1S < a_tOB->count_axesIntersection[0]; i_B1S++){
						time_f[i_B1S] = fabs((a_tOB->ball2_x - a_tOB->act_posOfAxesX[i_B1S]))/a_tOB->velocity;
					}
					
					qsort(time_f,sizeof(time_f)/sizeof(time_f[0]),sizeof(REAL),cmpfunc);
					for(i_B1Sn = 0; i_B1Sn < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); i_B1Sn++){
						if(i_B1Sn < a_tOB->count_axesIntersection[0]){
							a_tOB->time_aI[i_B1Sn] = time_f[i_B1Sn];
						}else{
							a_tOB->time_aI[i_B1Sn] = a_tOB->time_B2B;
						}
					}
				}else{
					a_tOB->velocity = fabs((a_tOB->ball1_x - a_tOB->ball2_x))/a_tOB->time_B2B;
					
					if(a_tOB->ball2_x > 8300){
						for(i_OS = a_tOB->count_axesIntersection[0]; i_OS < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); i_OS++){
							a_tOB->time_aI[i_OS] = fabs((a_tOB->ball2_x - a_tOB->act_posOfAxesX[i_OS]))/a_tOB->velocity;
						}
					}else{
						for(i_OSn = 0; i_OSn < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); i_OSn++){
							a_tOB->time_aI[i_OSn] = a_tOB->time_B2B;
						}
					}
				}
			}
			break;
		case 1:
			{
				// tilted direction of ball
				a_tOB->velocity = sqrt(pow((a_tOB->ball1_x - a_tOB->ball2_x),2) + pow((a_tOB->ball1_y - a_tOB->ball2_y),2))/a_tOB->time_B2B;		
				previous_time 	= sqrt(pow((a_tOB->ball2_x - a_tOB->first_reflection_x),2) + pow((a_tOB->ball2_y - a_tOB->first_reflection_y),2))/a_tOB->velocity;
			
				if(a_tOB->ball1_x > a_tOB->ball2_x){
					for(i_B1T = 0; i_B1T < a_tOB->count_axesIntersection[0]; i_B1T++){
						if(i_B1T < a_tOB->count_axesIntersection[1]){
							time_f[i_B1T] = sqrt(pow((a_tOB->first_reflection_x - a_tOB->act_posOfAxesX[i_B1T]),2) + pow((a_tOB->first_reflection_y - a_tOB->act_posOfAxesY[i_B1T]),2))/a_tOB->velocity + previous_time;
						}else{
							time_f[i_B1T] = sqrt(pow((a_tOB->ball2_x - a_tOB->act_posOfAxesX[i_B1T]),2) + pow((a_tOB->ball2_y - a_tOB->act_posOfAxesY[i_B1T]),2))/a_tOB->velocity;
						}
					}
					qsort(time_f,sizeof(time_f)/sizeof(time_f[0]),sizeof(REAL),cmpfunc);
					
					for(iB1Tn = 0; iB1Tn < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); iB1Tn++){
						if(iB1Tn < a_tOB->count_axesIntersection[0]){
							a_tOB->time_aI[iB1Tn] = time_f[iB1Tn];
						}else{
							a_tOB->time_aI[iB1Tn] = a_tOB->time_B2B;
						}
					}
				}else{
					for(iOT = a_tOB->count_axesIntersection[0]; iOT < (int)(sizeof(a_tOB->act_posOfAxesX)/sizeof(a_tOB->act_posOfAxesX[0])); iOT++){
						if(iOT < a_tOB->count_axesIntersection[1]){
							a_tOB->time_aI[iOT] = sqrt(pow((a_tOB->ball2_x - a_tOB->act_posOfAxesX[iOT]),2) + pow((a_tOB->ball2_y - a_tOB->act_posOfAxesY[iOT]),2))/a_tOB->velocity;
						}else{
							a_tOB->time_aI[iOT] = sqrt(pow((a_tOB->first_reflection_x - a_tOB->act_posOfAxesX[iOT]),2) + pow((a_tOB->first_reflection_y - a_tOB->act_posOfAxesY[iOT]),2))/a_tOB->velocity + previous_time;
						}
					}
					
					for(iOTn = 0; iOTn < a_tOB->count_axesIntersection[0]; iOTn++){
						a_tOB->time_aI[iOTn] = a_tOB->time_B2B;
					}
				}
			}
			break;
	}//end switch
}// end function

int cmpfunc(const void *a, const void *b)
{
	return (*(REAL*)b - *(REAL*)a);
}