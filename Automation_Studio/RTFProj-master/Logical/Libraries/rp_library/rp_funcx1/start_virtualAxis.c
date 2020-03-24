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
void initialization_sva(struct start_virtualAxis* s_va);

void start_virtualAxis(struct start_virtualAxis* s_va)
{		
	if(!s_va->Enable){
		initialization_sra(s_va);
	}
	
	switch(s_va->Internal.state){
		case 0:
			{	
				s_va->Internal.before_state     = s_va->Internal.state;
			
				if(s_va->start_btn == 1){
					// reset output {virtual}
					s_va->succesfully = 0;
					if(s_va->axis_name->Error == 1 || s_va->axis_name->StatusID != 0){
						s_va->axis_name->ErrorReset = 0;
						if(s_va->axis_name->ErrorReset == 0){
							s_va->Internal.state = 10;
						}
					}else{
						if(s_va->start_btn == 1){
							s_va->Internal.state = 1;
						}
					}
				}
			}
			break;
		case 1:
			{
				s_va->Internal.before_state = s_va->Internal.state;
				// power on -> axis
				s_va->axis_name->Power = 1;
			
				if(s_va->axis_name->Error == 1 || s_va->axis_name->StatusID != 0){
					s_va->axis_name->ErrorReset = 0;
					if(s_va->axis_name->ErrorReset == 0){
						s_va->Internal.state = 10;
					}
				}else{
					if(s_va->axis_name->PowerOn == 1){
						s_va->Internal.state = 2;
					}
				}
			}
			break;
		case 2:
			{
				s_va->Internal.before_state = s_va->Internal.state;
				// home -> axis
				s_va->axis_name->Home = 1;
			
				if(s_va->axis_name->Error == 1 || s_va->axis_name->StatusID != 0){
					s_va->axis_name->ErrorReset = 0;
					if(s_va->axis_name->ErrorReset == 0){
						s_va->Internal.state = 10;
					}
				}else{
					if(s_va->axis_name->IsHomed == 1){
						s_va->axis_name->Home = 0;
						s_va->Internal.state  = 3;
					}
				}
			}
			break;
		case 3:
			{
				s_va->Internal.before_state = s_va->Internal.state;
			
				if(s_va->axis_name->Error == 1 || s_va->axis_name->StatusID != 0){
					s_va->axis_name->ErrorReset = 0;
					if(s_va->axis_name->ErrorReset == 0){
						s_va->Internal.state = 10;
					}
				}else{
					s_va->succesfully	 = 1;
					s_va->Internal.state = 0;
				}
			}
			break;
		case 10:
			{
				s_va->axis_name->ErrorReset = 1;
				
				if(s_va->axis_name->Error == 1 || s_va->axis_name->StatusID != 0){
					s_va->Internal.state = 10;
				}else{
					s_va->axis_name->ErrorReset = 0;
					s_va->Internal.state 		= s_va->Internal.before_state;
				}
			}
			break;			
	}// end switch
}// end function

void initialization_sva(struct start_virtualAxis* s_va)
{
	s_va->Internal.state 		= 0;
	s_va->Internal.before_state = 0;
	s_va->start_btn				= 0;
	s_va->succesfully     		= 0;
}// end function
