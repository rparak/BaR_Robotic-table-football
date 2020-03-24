
#include <bur/plctypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <MpAxis.h>


#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif
void init_control_axis(struct axes_control* a_c);

void axes_control(struct axes_control* a_c)
{

	if(!a_c->Enable){
		init_control_axis(&a_c);
	}
	
	switch(a_c->Internal.state){
		case 0:
			{
				a_c->Internal.before_state = 0;
			
				if(a_c->start_move == 1){
					a_c->successfully = 0;
					
					if(a_c->successfully == 0){
						if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
						|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
							// cyclic position -> off
							a_c->linear_axis_cyclic->CyclicPosition = 0;
							a_c->rotary_axis_cyclic->CyclicPosition = 0;
							if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
								// go to error state
								a_c->Internal.state = 10;
							}
						}else{
							// start cyclic position
							a_c->linear_axis_cyclic->CyclicPosition = 1;
							a_c->rotary_axis_cyclic->CyclicPosition = 1;
							// go to next state
							a_c->Internal.state = 1;
						}
					}else if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
					|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
						// cyclic position -> off
						a_c->linear_axis_cyclic->CyclicPosition = 0;
						a_c->rotary_axis_cyclic->CyclicPosition = 0;
						if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
							// go to error state
							a_c->Internal.state = 10;
						}
					}
				}
			}
			break;
		case 1:
			{
				a_c->Internal.before_state = 1;
			
				if(a_c->linear_axis_param->Acceleration == a_c->linear_param.acceleration && a_c->linear_axis_cyclic->Velocity == a_c->linear_param.velocity){
					if(a_c->rotary_axis_param->Acceleration == a_c->rotary_param.acceleration && a_c->rotary_axis_cyclic->Velocity == a_c->rotary_param.velocity){
						if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
						|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
							// cyclic position -> off
							a_c->linear_axis_cyclic->CyclicPosition = 0;
							a_c->rotary_axis_cyclic->CyclicPosition = 0;
							if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
								// go to error state
								a_c->Internal.state = 10;
							}
						}else{
							a_c->Internal.state = 2;
						}
					}else{
						if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
						|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
							// cyclic position -> off
							a_c->linear_axis_cyclic->CyclicPosition = 0;
							a_c->rotary_axis_cyclic->CyclicPosition = 0;
							if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
								// go to error state
								a_c->Internal.state = 10;
							}
						}else{
							a_c->Internal.state = 3;
						}
					}
				}else{
					if(a_c->rotary_axis_param->Acceleration == a_c->rotary_param.acceleration && a_c->rotary_axis_cyclic->Velocity == a_c->rotary_param.velocity){
						if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
						|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
							// cyclic position -> off
							a_c->linear_axis_cyclic->CyclicPosition = 0;
							a_c->rotary_axis_cyclic->CyclicPosition = 0;
							if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
								// go to error state
								a_c->Internal.state = 10;
							}
						}else{
							a_c->Internal.state = 4;
						}
					}else{
						if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
						|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
							// cyclic position -> off
							a_c->linear_axis_cyclic->CyclicPosition = 0;
							a_c->rotary_axis_cyclic->CyclicPosition = 0;
							if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
								// go to error state
								a_c->Internal.state = 10;
							}
						}else{
							a_c->Internal.state = 5;
						}
					}
				}
			}
			break;
		case 2:
			{
				a_c->Internal.before_state = 2;
			
				// linear axis param cyclic
				a_c->linear_axis_cyclic->Position 				= a_c->linear_param.displacement;
				// rotary axis param cyclic
				a_c->rotary_axis_cyclic->Position 				= a_c->rotary_param.displacement;
			
				if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
				|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
					// cyclic position -> off
					a_c->linear_axis_cyclic->CyclicPosition = 0;
					a_c->rotary_axis_cyclic->CyclicPosition = 0;
					if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
						// go to error state
						a_c->Internal.state = 10;
					}
				}else{
					a_c->Internal.state = 6;
				}
			}
			break;
		case 3:
			{
				a_c->Internal.before_state = 3;
				// turn off 
				a_c->rotary_axis_cyclic->CyclicPosition = 0;
			
				if(a_c->rotary_axis_cyclic->CyclicPosition == 0){
					// linear axis param cyclic
					a_c->linear_axis_cyclic->Velocity   			= a_c->linear_param.velocity;
					a_c->linear_axis_cyclic->Position 				= a_c->linear_param.displacement;
					// rotary axis param
					a_c->rotary_axis_param->Acceleration		    = a_c->rotary_param.acceleration;
					a_c->rotary_axis_param->Deceleration			= a_c->rotary_param.deceleration;
					// rotary axis param cyclic
					a_c->rotary_axis_cyclic->Velocity   			= a_c->rotary_param.velocity;
					a_c->rotary_axis_cyclic->Position 				= a_c->rotary_param.displacement;
			
					// update parameters
					a_c->rotary_axis_cyclic->Update = 1;
			
					if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
					 || (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
						// cyclic position -> off
						a_c->linear_axis_cyclic->CyclicPosition = 0;
						a_c->rotary_axis_cyclic->CyclicPosition = 0;
						if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
							// go to error state
							a_c->Internal.state = 10;
						}
					}else{
						if(a_c->rotary_axis_cyclic->UpdateDone == 1){
							a_c->rotary_axis_cyclic->Update = 0;
							if(a_c->rotary_axis_cyclic->Update == 0){
								// turn on
								a_c->rotary_axis_cyclic->CyclicPosition = 1;
								if(a_c->rotary_axis_cyclic->CyclicPosition == 1){
									a_c->Internal.state = 6;
								}
							}
						}
					}
				}
			}
			break;
		case 4:
			{
				a_c->Internal.before_state = 4;
			
				// turn off 
				a_c->linear_axis_cyclic->CyclicPosition = 0;
			
				if(a_c->linear_axis_cyclic->CyclicPosition == 0){
					// linear axis param
					a_c->linear_axis_param->Acceleration		    = a_c->linear_param.acceleration;
					a_c->linear_axis_param->Deceleration			= a_c->linear_param.deceleration;
					// linear axis param cyclic
					a_c->linear_axis_cyclic->Velocity   			= a_c->linear_param.velocity;
					a_c->linear_axis_cyclic->Position 				= a_c->linear_param.displacement;
					// rotary axis param cyclic
					a_c->rotary_axis_cyclic->Velocity   			= a_c->rotary_param.velocity;
					a_c->rotary_axis_cyclic->Position 				= a_c->rotary_param.displacement;
			
					// update parameters
					a_c->linear_axis_cyclic->Update = 1;
			
					if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
					|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
						// cyclic position -> off
						a_c->linear_axis_cyclic->CyclicPosition = 0;
						a_c->rotary_axis_cyclic->CyclicPosition = 0;
						if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
							// go to error state
							a_c->Internal.state = 10;
						}
					}else{
						if(a_c->linear_axis_cyclic->UpdateDone == 1){
							a_c->linear_axis_cyclic->Update = 0;
							if(a_c->linear_axis_cyclic->Update == 0){
								// turn on
								a_c->linear_axis_cyclic->CyclicPosition = 1;
								if(a_c->linear_axis_cyclic->CyclicPosition == 1){
									a_c->Internal.state = 6;
								}
							}
						}
					}
				}
			}
			break;
		case 5:
			{
				a_c->Internal.before_state = 5;
			
				// turn off
				a_c->linear_axis_cyclic->CyclicPosition = 0;
				a_c->rotary_axis_cyclic->CyclicPosition = 0;
			
				if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
					// linear axis param
					a_c->linear_axis_param->Acceleration		    = a_c->linear_param.acceleration;
					a_c->linear_axis_param->Deceleration			= a_c->linear_param.deceleration;
					// linear axis param cyclic
					a_c->linear_axis_cyclic->Velocity   			= a_c->linear_param.velocity;
					a_c->linear_axis_cyclic->Position 				= a_c->linear_param.displacement;
					// rotary axis param
					a_c->rotary_axis_param->Acceleration		    = a_c->rotary_param.acceleration;
					a_c->rotary_axis_param->Deceleration			= a_c->rotary_param.deceleration;
					// rotary axis param cyclic
					a_c->rotary_axis_cyclic->Velocity   			= a_c->rotary_param.velocity;
					a_c->rotary_axis_cyclic->Position 				= a_c->rotary_param.displacement;
			
					// update parameters
					a_c->linear_axis_cyclic->Update = 1;
					a_c->rotary_axis_cyclic->Update = 1;
					
					if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
					|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
						// cyclic position -> off
						a_c->linear_axis_cyclic->CyclicPosition = 0;
						a_c->rotary_axis_cyclic->CyclicPosition = 0;
						if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
							// go to error state
							a_c->Internal.state = 10;
						}
					}else{
						if(a_c->linear_axis_cyclic->UpdateDone == 1 && a_c->rotary_axis_cyclic->UpdateDone == 1){
							a_c->linear_axis_cyclic->Update = 0;
							a_c->rotary_axis_cyclic->Update = 0;
							if(a_c->linear_axis_cyclic->Update == 0 && a_c->rotary_axis_cyclic->Update == 0){
								// turn on
								a_c->linear_axis_cyclic->CyclicPosition = 1;
								a_c->rotary_axis_cyclic->CyclicPosition = 1;
								if(a_c->linear_axis_cyclic->CyclicPosition == 1 && a_c->rotary_axis_cyclic->CyclicPosition == 1){
									a_c->Internal.state = 6;
								}
							}
						}
					}
				}
			}
			break;
		case 6:
			{
				a_c->Internal.before_state = 6;
			
				if(((a_c->rotary_axis_cyclic->Error == 1 && a_c->rotary_axis_cyclic->StatusID != 0) || (a_c->linear_axis_cyclic->Error == 1 && a_c->linear_axis_cyclic->StatusID != 0))
				|| (a_c->rotary_axis_cyclic->CommandAborted == 1 || a_c->linear_axis_cyclic->CommandAborted == 1)){
					// cyclic position -> off
					a_c->linear_axis_cyclic->CyclicPosition = 0;
					a_c->rotary_axis_cyclic->CyclicPosition = 0;
					if(a_c->linear_axis_cyclic->CyclicPosition == 0 && a_c->rotary_axis_cyclic->CyclicPosition == 0){
						// go to error state
						a_c->Internal.state = 10;
					}
				}else{			
					a_c->successfully = 1;
					
					if(a_c->successfully == 1){
						a_c->Internal.state = 0;
					}
				}
			}
			break;
		case 10:
			{
				// error reset -> on
				a_c->rotary_axis_cyclic->ErrorReset = 1;
				a_c->linear_axis_cyclic->ErrorReset = 1;
			
				if((a_c->rotary_axis_cyclic->Error == 0 && a_c->linear_axis_cyclic->Error == 0 && a_c->rotary_axis_cyclic->StatusID == 0 && a_c->linear_axis_cyclic->StatusID == 0)
				&& (a_c->rotary_axis_cyclic->CommandAborted == 0 && a_c->linear_axis_cyclic->CommandAborted == 0)){
					// error reset -> off
					a_c->rotary_axis_cyclic->ErrorReset = 0;
					a_c->linear_axis_cyclic->ErrorReset = 0;
					// cyclic position -> on
					a_c->linear_axis_cyclic->CyclicPosition = 1;
					a_c->rotary_axis_cyclic->CyclicPosition = 1;
					
					if(a_c->rotary_axis_cyclic->ErrorReset == 0 && a_c->linear_axis_cyclic->ErrorReset == 0){
						a_c->Internal.state = a_c->Internal.before_state;
					}
				}
			
			}
			break;
	}// end switch
	
}// end function

void init_control_axis(struct axes_control* a_c)
{
	a_c->Internal.state 	   = 0;
	a_c->Internal.before_state = 0;
	a_c->successfully 		   = 0;
}
