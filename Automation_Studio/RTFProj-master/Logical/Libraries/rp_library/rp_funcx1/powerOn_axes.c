
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
void initialization_pO_a(struct powerOn_axes* pO_a);

void powerOn_axes(struct powerOn_axes* pO_a)
{		
	if(!pO_a->start_btn){
		initialization_pO_a(pO_a);
	}
	
	switch(pO_a->Internal.state){
		case 0:
			{
				pO_a->Internal.before_state     = pO_a->Internal.state;
				
				if(pO_a->axis_name_R->Error == 1 || pO_a->axis_name_R->StatusID != 0 || pO_a->axis_name_L->Error == 1 || pO_a->axis_name_L->StatusID != 0){
					pO_a->Internal.state = 10;
				}else{
					if(pO_a->start_btn == 1){
						pO_a->Internal.state = 1;
					}
				}
			}
			break;
		case 1:
			{
				pO_a->Internal.before_state = pO_a->Internal.state;
				// power on -> axis
				pO_a->axis_name_R->Power = 1;
				pO_a->axis_name_L->Power = 1;
			
				if(pO_a->axis_name_R->PowerOn == 1 && pO_a->axis_name_L->PowerOn == 1){
					pO_a->succesfully = 1;
				}else if(pO_a->axis_name_R->Error == 1 || pO_a->axis_name_L->StatusID != 0){
					pO_a->Internal.state = 10;
				}else{
					pO_a->Internal.state = pO_a->Internal.before_state;
				}
			}
			break;
		case 10:
			{
				pO_a->axis_name_R->ErrorReset = 1;
				pO_a->axis_name_L->ErrorReset = 1;
				
			if(pO_a->axis_name_R->Error == 1 || pO_a->axis_name_R->StatusID != 0 || pO_a->axis_name_L->Error == 1 || pO_a->axis_name_L->StatusID != 0){
					pO_a->Internal.state = 10;
				}else{
					pO_a->axis_name_R->ErrorReset = 0;
					pO_a->axis_name_L->ErrorReset = 0;
					pO_a->Internal.state 		= pO_a->Internal.before_state;
				}
			}
			break;			
	}// end switch
}// end function

void initialization_pO_a(struct powerOn_axes* pO_a)
{
	pO_a->Internal.state 		= 0;
	pO_a->Internal.before_state = 0;
	pO_a->start_btn				= 0;
	pO_a->succesfully     		= 0;
}// end function
