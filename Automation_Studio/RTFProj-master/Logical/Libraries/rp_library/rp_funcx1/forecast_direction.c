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
* Implementation OF PROGRAM simulation(rp_library/rp_funcx1/forecast_direction.c)
**********************************************************************************************/

/************************************* LIBRARIES *********************************************/
#include <bur/plctypes.h>
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

void forecast_direction(struct forecast_direction* f_d)
{
	USINT initial_state;
	UDINT auxiliary_str;
	
	struct calculate_directionOfTilt calc_dirOfTilt;
	struct calculate_nextDirection calc_nextDir;
	
	if((isnan(f_d->ball2_x)) && (isnan(f_d->ball2_y))){
		initial_state = 0;
	}else{
		initial_state = 1;
	}
	
	switch(initial_state){
		case 0:
			{
				f_d->first_reflectionX  = 0;
				f_d->first_reflectionY  = f_d->ball1_y;
				f_d->second_reflectionX = sqrt(-1);
				f_d->second_reflectionY = sqrt(-1);
				f_d->tilted       		= 0;
            
				auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"straight");		
			}
			break;
		case 1:
			{
				if(f_d->ball1_y == f_d->ball2_y){
					f_d->tilted = 0;
                    
					if(f_d->ball1_x > f_d->ball2_x){
						auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"straight-backward");
						
						f_d->first_reflectionX  = 0;
						f_d->first_reflectionY  = f_d->ball2_y;
						f_d->second_reflectionX = sqrt(-1);
						f_d->second_reflectionY = sqrt(-1);
                        
					}else if(f_d->ball1_x < f_d->ball2_x){
						auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"straight-forward");
						
						f_d->first_reflectionX  = 12100;
						f_d->first_reflectionY  = f_d->ball2_y;
						f_d->second_reflectionX = sqrt(-1);
						f_d->second_reflectionY = sqrt(-1);
                        
					}else if(f_d->ball1_x == f_d->ball2_x){
						
						auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"stopped");
						
						f_d->first_reflectionX  = f_d->ball1_x;
						f_d->first_reflectionY  = f_d->ball1_y;
						f_d->second_reflectionX = f_d->ball2_x;
						f_d->second_reflectionY = f_d->ball2_y;
					}
				}else{
					if(f_d->ball1_x == f_d->ball2_x){
						if(f_d->ball1_y < f_d->ball2_y){
							auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"right");
						}else {
							auxiliary_str = (UDINT) strcpy(f_d->specific_direction,"left");
						}
						
						f_d->first_reflectionX  = f_d->ball1_x;
						f_d->first_reflectionY  = f_d->ball1_y;
						f_d->second_reflectionX = f_d->ball2_x;
						f_d->second_reflectionY = f_d->ball2_y;
                        
					}else{
						f_d->tilted = 1;
						// input parameters into the function block calculate direction of tilt
						calc_dirOfTilt.ball1_x = f_d->ball1_x;
						calc_dirOfTilt.ball1_y = f_d->ball1_y;
						calc_dirOfTilt.ball2_x = f_d->ball2_x;
						calc_dirOfTilt.ball2_y = f_d->ball2_y;
						// call function block calculate direction of tilt
						calculate_directionOfTilt(&calc_dirOfTilt);
						// output parameters
						f_d->first_reflectionX  = calc_dirOfTilt.reflection_x;
						f_d->first_reflectionY  = calc_dirOfTilt.reflection_y;
						
						auxiliary_str = (UDINT) strcpy(f_d->specific_direction,calc_dirOfTilt.specific_direction);
						
						// input parameters into the function block calculate next direction
						calc_nextDir.ball2_x 			= f_d->ball2_x;
						calc_nextDir.ball2_y 			= f_d->ball2_y;
						calc_nextDir.first_reflection_x = calc_dirOfTilt.reflection_x;
						calc_nextDir.first_reflection_y = calc_dirOfTilt.reflection_y;
						calc_nextDir.state_ofDirection  = calc_dirOfTilt.state_ofDirection;
						// call function block calculate next direction
						calculate_nextDirection(&calc_nextDir);
						// output parameters
						f_d->second_reflectionX = calc_nextDir.second_reflection_x;
						f_d->second_reflectionY = calc_nextDir.second_reflection_y;
					}
				}
			}
			break;
	}// end switch

}// end function

void calculate_directionOfTilt(struct calculate_directionOfTilt* c_dT)
{
	USINT ball_direction;
	UDINT auxiliary_str;
	REAL distanceOfRatio_y, distanceOfRatio_x;
	REAL x_auxiliary, y_auxiliary;
	
	if((c_dT->ball2_y > c_dT->ball1_y) && (c_dT->ball2_x < c_dT->ball1_x)){
		ball_direction = 1;
		auxiliary_str = (UDINT) strcpy(c_dT->specific_direction,"up_backward");
	}else if((c_dT->ball2_y < c_dT->ball1_y) && (c_dT->ball2_x < c_dT->ball1_x)){
		ball_direction = 2;
		auxiliary_str = (UDINT) strcpy(c_dT->specific_direction,"down_backward");
	}else if((c_dT->ball2_y > c_dT->ball1_y) && (c_dT->ball2_x > c_dT->ball1_x)){
		ball_direction = 3;
		auxiliary_str = (UDINT) strcpy(c_dT->specific_direction,"up_forward");		
	}else if((c_dT->ball2_y < c_dT->ball1_y) && (c_dT->ball2_x > c_dT->ball1_x)){
		ball_direction = 4;
		auxiliary_str = (UDINT) strcpy(c_dT->specific_direction,"down_forward");
	}
	
	switch(ball_direction){
		case 1:
			{
				// maximum of y : 3515
				// maximum of x : 0
				distanceOfRatio_y = ((3515 - c_dT->ball1_y)/(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				distanceOfRatio_x = ((c_dT->ball1_x)/(fabs(c_dT->ball1_x - c_dT->ball2_x)));
			
				c_dT->state_ofDirection = ball_direction;	
				
				x_auxiliary = c_dT->ball1_x - ((distanceOfRatio_y)*(fabs(c_dT->ball1_x - c_dT->ball2_x)));
				y_auxiliary = 3515;
			
				if((x_auxiliary >= 0) && (y_auxiliary <= 3515)){
					c_dT->reflection_x = x_auxiliary;
					c_dT->reflection_y = y_auxiliary;
				}else{
					c_dT->reflection_x = 0;
					c_dT->reflection_y = c_dT->ball1_y + ((distanceOfRatio_x)*(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				}
			}
			break;
		case 2:
			{
				// maximum of y : -3515
				// maximum of x : 0
				distanceOfRatio_y = ((c_dT->ball1_y + 3515)/(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				distanceOfRatio_x = ((c_dT->ball1_x)/(fabs(c_dT->ball1_x - c_dT->ball2_x)));
			
				c_dT->state_ofDirection = ball_direction;
			
				x_auxiliary = c_dT->ball1_x - ((distanceOfRatio_y)*(fabs(c_dT->ball1_x - c_dT->ball2_x)));
				y_auxiliary = -3515;
			
				if((x_auxiliary >= 0) && (y_auxiliary >= -3515)){
					c_dT->reflection_x = x_auxiliary;
					c_dT->reflection_y = y_auxiliary;
				}else{
					c_dT->reflection_x = 0;
					c_dT->reflection_y = c_dT->ball1_y - ((distanceOfRatio_x)*(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				}
			}
			break;
		case 3:
			{
				// maximum of y : 3515
				// maximum of x : 12100
				distanceOfRatio_y = ((3515 - c_dT->ball1_y)/(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				distanceOfRatio_x = ((12100 - c_dT->ball1_x)/(fabs(c_dT->ball1_x - c_dT->ball2_x)));
			
				c_dT->state_ofDirection = ball_direction;
			
				x_auxiliary = c_dT->ball1_x + ((distanceOfRatio_y)*(fabs(c_dT->ball1_x - c_dT->ball2_x)));
				y_auxiliary = 3515;
			
				if((x_auxiliary <= 12100) && (y_auxiliary <= 3515)){
					c_dT->reflection_x = x_auxiliary;
					c_dT->reflection_y = y_auxiliary;
				}else{
					c_dT->reflection_x = 12100;
					c_dT->reflection_y = c_dT->ball1_y + ((distanceOfRatio_x)*(fabs(c_dT->ball1_y-c_dT->ball2_y)));
				}
			}
			break;
		case 4:
			{
				// maximum of y : -3515
				// maximum of x : 12100
				distanceOfRatio_y = ((c_dT->ball1_y + 3515)/(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				distanceOfRatio_x = ((12100 - c_dT->ball1_x)/(fabs(c_dT->ball1_x - c_dT->ball2_x)));
			
				c_dT->state_ofDirection = ball_direction;
			
				x_auxiliary = c_dT->ball1_x + ((distanceOfRatio_y)*(fabs(c_dT->ball1_x - c_dT->ball2_x)));
				y_auxiliary = -3515;
			
				if((x_auxiliary <= 12100) && (y_auxiliary >= -3515)){
					c_dT->reflection_x = x_auxiliary;
					c_dT->reflection_y = y_auxiliary;
				}else{
					c_dT->reflection_x = 12100;
					c_dT->reflection_y = c_dT->ball1_y - ((distanceOfRatio_x)*(fabs(c_dT->ball1_y - c_dT->ball2_y)));
				}
			}
			break;
	}// end switch

}// end function

void calculate_nextDirection(struct calculate_nextDirection* c_nD)
{
	REAL x_n, y_n;
	
	struct calculate_directionOfTilt calc_dT;
	
	switch(c_nD->state_ofDirection){
		case 1:
			{
				// direction : up, forward
				if(c_nD->first_reflection_x == 0){
					x_n = c_nD->first_reflection_x + (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y + (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}else{
					x_n = c_nD->first_reflection_x - (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y - (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}
				
				// input parameters into the function block calculate direction of tilt
				calc_dT.ball1_x = c_nD->first_reflection_x;
				calc_dT.ball1_y = c_nD->first_reflection_y;
				calc_dT.ball2_x = x_n;
				calc_dT.ball2_y = y_n;
				// call function block calculate direction of tilt
				calculate_directionOfTilt(&calc_dT);
				// output parameters
				c_nD->second_reflection_x = calc_dT.reflection_x;
				c_nD->second_reflection_y = calc_dT.reflection_y;		
			}
			break;
		case 2:
			{
				// direction : down, forward
				if(c_nD->first_reflection_x == 0){
					x_n = c_nD->first_reflection_x + (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y - (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}else{
					x_n = c_nD->first_reflection_x - (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y + (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}
				
				// input parameters into the function block calculate direction of tilt
				calc_dT.ball1_x = c_nD->first_reflection_x;
				calc_dT.ball1_y = c_nD->first_reflection_y;
				calc_dT.ball2_x = x_n;
				calc_dT.ball2_y = y_n;
				// call function block calculate direction of tilt
				calculate_directionOfTilt(&calc_dT);
				// output parameters
				c_nD->second_reflection_x = calc_dT.reflection_x;
				c_nD->second_reflection_y = calc_dT.reflection_y;
			}
			break;
		case 3:
			{
				// direction : up, backward
				if(c_nD->first_reflection_x == 12100){
					x_n = c_nD->first_reflection_x - (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y + (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}else{
					x_n = c_nD->first_reflection_x + (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y - (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}
				
				// input parameters into the function block calculate direction of tilt
				calc_dT.ball1_x = c_nD->first_reflection_x;
				calc_dT.ball1_y = c_nD->first_reflection_y;
				calc_dT.ball2_x = x_n;
				calc_dT.ball2_y = y_n;
				// call function block calculate direction of tilt
				calculate_directionOfTilt(&calc_dT);
				// output parameters
				c_nD->second_reflection_x = calc_dT.reflection_x;
				c_nD->second_reflection_y = calc_dT.reflection_y;
			}
			break;
		case 4:
			{
				// direction : down, backward
				if(c_nD->first_reflection_x == 12100){
					x_n = c_nD->first_reflection_x - (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y - (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}else{
					x_n = c_nD->first_reflection_x + (fabs(c_nD->first_reflection_x - c_nD->ball2_x)*(0.01));
					y_n = c_nD->first_reflection_y + (fabs(c_nD->first_reflection_y - c_nD->ball2_y)*(0.01));
				}
				
				// input parameters into the function block calculate direction of tilt
				calc_dT.ball1_x = c_nD->first_reflection_x;
				calc_dT.ball1_y = c_nD->first_reflection_y;
				calc_dT.ball2_x = x_n;
				calc_dT.ball2_y = y_n;
				// call function block calculate direction of tilt
				calculate_directionOfTilt(&calc_dT);
				// output parameters
				c_nD->second_reflection_x = calc_dT.reflection_x;
				c_nD->second_reflection_y = calc_dT.reflection_y;
			}
			break;
	}// end switch
	
}// end function
