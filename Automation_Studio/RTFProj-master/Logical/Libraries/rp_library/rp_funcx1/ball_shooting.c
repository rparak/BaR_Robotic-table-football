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
void init_ball_shooting(struct ball_shooting* b_s);
void ball_shooting(struct ball_shooting* b_s)
{
	if(b_s->Enable == 0){
		init_ball_shooting(&b_s);
	}
	
	switch(b_s->Internal.state){
		case 0:
			{
				if(b_s->start_shoot == 1){
					// initialization parameters of axes for shooting ball
					b_s->rotary_axes->CyclicPosition = 1;
					b_s->rotary_axes->Position		 = -500;
					b_s->rotary_axes->Velocity 		 = 63000;
			
					// change state
					b_s->Internal.state = 1;
				}
			}
			break;
		case 1:
			{	
				if(b_s->rotary_axes->Info.SlavePosition == b_s->rotary_axes->Position){
					// second position
					b_s->rotary_axes->Position	= 500;
					if(b_s->rotary_axes->Info.SlavePosition == 500){
						b_s->Internal.state = 2;
					}
				}
			}
			break;
		case 2:
			{
				if(b_s->rotary_axes->Info.SlavePosition == b_s->rotary_axes->Position){
					// second position
					b_s->rotary_axes->Position	= -250;
					
					if(b_s->rotary_axes->Info.SlavePosition == -250){
						b_s->successfully = 1;
						if(b_s->successfully == 1){
							b_s->Internal.state = 0;
						}
					}
				}
				
			}
			break;
	}// end switch
}// end function

void init_ball_shooting(struct ball_shooting* b_s)
{
	b_s->Internal.state = 0;
	b_s->successfully   = 0;
	b_s->start_shoot    = 0;
}
