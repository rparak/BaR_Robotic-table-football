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
void initialization_sra(struct start_rotaryAxis* s_ra);

void start_rotaryAxis(struct start_rotaryAxis* s_ra)
{		
	if(!s_ra->Enable){
		initialization_sra(s_ra);
	}
	
	switch(s_ra->Internal.state){
		case 0:
			{	
				s_ra->Internal.before_state     = s_ra->Internal.state;
			
				if(s_ra->start_btn == 1){
					// adjust param -> axis
					// move position
					s_ra->axis_param->Acceleration = 3969754;
					s_ra->axis_param->Deceleration = 3969754;
					s_ra->axis_param->Velocity     = 1000;
					s_ra->axis_param->Position 	   = 0;
					// home
					s_ra->axis_param->Home.Position = s_ra->value_ofRotatation;
					// reset output
					s_ra->succesfully = 0;
					if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
						s_ra->axis_name->ErrorReset = 0;
						if(s_ra->axis_name->ErrorReset == 0){
							s_ra->Internal.state = 10;
						}
					}else{
						if(s_ra->start_btn == 1){
							s_ra->Internal.state = 1;
						}
					}
				}
			}
			break;
		case 1:
			{
				s_ra->Internal.before_state = s_ra->Internal.state;
				// power on -> axis
				s_ra->axis_name->Power = 1;
			
				if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
					s_ra->axis_name->ErrorReset = 0;
					if(s_ra->axis_name->ErrorReset == 0){
						s_ra->Internal.state = 10;
					}
				}else{
					if(s_ra->axis_name->PowerOn == 1){
						s_ra->Internal.state = 2;
					}
				}
			}
			break;
		case 2:
			{
				s_ra->Internal.before_state = s_ra->Internal.state;
				// update -> axis
				s_ra->axis_name->Update = 1;
			
				if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
					s_ra->axis_name->ErrorReset = 0;
					if(s_ra->axis_name->ErrorReset == 0){
						s_ra->Internal.state = 10;
					}
				}else{
					if(s_ra->axis_name->UpdateDone == 1){
						s_ra->axis_name->Update = 0;
						if(s_ra->axis_name->Update == 0){
							s_ra->Internal.state = 3;
						}
					}
				}
			}
		case 3:
			{
				s_ra->Internal.before_state = s_ra->Internal.state;
				// home -> axis
				s_ra->axis_name->Home = 1;
			
				if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
					s_ra->axis_name->ErrorReset = 0;
					if(s_ra->axis_name->ErrorReset == 0){
						s_ra->Internal.state = 10;
					}
				}else{
					if(s_ra->axis_name->IsHomed == 1){
						s_ra->axis_name->Home = 0;
						s_ra->Internal.state  = 4;
					}
				}
			}
			break;
		case 4:
			{
				s_ra->Internal.before_state = s_ra->Internal.state;
				// move absolute -> axis
				s_ra->axis_name->MoveAbsolute = 1;
				
				if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
					s_ra->axis_name->ErrorReset = 0;
					if(s_ra->axis_name->ErrorReset == 0){
						s_ra->Internal.state = 10;
					}
				}else{
					if(s_ra->axis_name->InPosition == 1){
						s_ra->axis_name->MoveAbsolute = 0;
					
						if(s_ra->axis_name->MoveAbsolute == 0){
							s_ra->succesfully	 = 1;
							s_ra->Internal.state = 0;
						}
					}
				}
			}
			break;
		case 10:
			{
				s_ra->axis_name->ErrorReset = 1;
				
				if(s_ra->axis_name->Error == 1 || s_ra->axis_name->StatusID != 0){
					s_ra->Internal.state = 10;
				}else{
					s_ra->axis_name->ErrorReset = 0;
					s_ra->Internal.state 		= s_ra->Internal.before_state;
				}
			}
			break;			
	}// end switch
}// end function

void initialization_sra(struct start_rotaryAxis* s_ra)
{
	s_ra->Internal.state 		= 0;
	s_ra->Internal.before_state = 0;
	s_ra->start_btn				= 0;
	s_ra->succesfully     		= 0;
}// end function
