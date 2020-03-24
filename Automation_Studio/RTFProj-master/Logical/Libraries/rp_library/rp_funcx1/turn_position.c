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
void initial_turn_pos(struct turn_position* t_p);
void turn_position(struct turn_position* t_p)
{
	if(t_p->Enable == 0){
		initial_turn_pos(&t_p);
	}
	
	switch(t_p->Internal.state){
		case 0:
			{
				// parameters of move
				t_p->Internal.distance_ofMovePos  = 100 + 170 + 80 + 150;
				t_p->Internal.distance_ofMoveNeg  = (-1)*t_p->Internal.distance_ofMovePos;
				// velocity
				t_p->rotary_axes->Velocity 		= 1500;
				t_p->linear_axes->Velocity 		= 500;
				// initialization parameters
				t_p->Internal.max_pos_ofAxes[0] = 800;
				t_p->Internal.max_pos_ofAxes[1] = 1030;
				t_p->Internal.max_pos_ofAxes[2] = 520;
				t_p->Internal.max_pos_ofAxes[3] = 830;
			
				t_p->Internal.min_pos_ofAxes[0] = -910;
				t_p->Internal.min_pos_ofAxes[1] = -930;
				t_p->Internal.min_pos_ofAxes[2] = -500;
				t_p->Internal.min_pos_ofAxes[3] = -770;
			
				// start function
				if(t_p->start_turn == 1){
					t_p->successfully = 0;
					if(t_p->successfully == 0){
						// first position
						t_p->rotary_axes->Position = 500;
						if((t_p->linear_axes->Info.SlavePosition + t_p->Internal.distance_ofMovePos) > t_p->Internal.max_pos_ofAxes[t_p->index_ofAxis]){
							t_p->Internal.auxiliary_move_pos = t_p->linear_axes->Info.SlavePosition;
							t_p->linear_axes->Position = t_p->linear_axes->Info.SlavePosition + t_p->Internal.distance_ofMoveNeg;
						}else if((t_p->linear_axes->Info.SlavePosition + t_p->Internal.distance_ofMovePos) < t_p->Internal.min_pos_ofAxes[t_p->index_ofAxis]){
							t_p->Internal.auxiliary_move_pos = t_p->linear_axes->Info.SlavePosition;
							t_p->linear_axes->Position = t_p->linear_axes->Info.SlavePosition + t_p->Internal.distance_ofMovePos;
						}else{
							t_p->Internal.auxiliary_move_pos = t_p->linear_axes->Info.SlavePosition;
							t_p->linear_axes->Position = t_p->linear_axes->Info.SlavePosition + t_p->Internal.distance_ofMovePos;
						}
						// change state
						t_p->Internal.state = 1;
						
					}
				}
			}
			break;
		case 1:
			{

				if((t_p->rotary_axes->Position == t_p->rotary_axes->Info.SlavePosition) &&(t_p->linear_axes->Position == t_p->linear_axes->Info.SlavePosition)){
					t_p->rotary_axes->Position = -500;
					t_p->Internal.state = 2;
				}
				
			}
			break;
		case 2:
			{
				if((t_p->rotary_axes->Position == t_p->rotary_axes->Info.SlavePosition) &&(t_p->linear_axes->Position == t_p->linear_axes->Info.SlavePosition)){
					// initial position
					t_p->linear_axes->Position = t_p->Internal.distance_ofMoveNeg;
					t_p->rotary_axes->Position = -250;
					// change state
					t_p->Internal.state = 3;
				}
				
			}
			break;
		case 3:
			{
				if((t_p->rotary_axes->Position == t_p->rotary_axes->Info.SlavePosition) &&(t_p->linear_axes->Position == t_p->linear_axes->Info.SlavePosition)){
					t_p->successfully = 1;
					t_p->Internal.state = 0;
				}
				
			}
			break;
	}// end switch
}// end function

void initial_turn_pos(struct turn_position* t_p)
{
	t_p->Internal.state = 0;
	t_p->successfully   = 0;
	t_p->start_turn		= 0;
}
