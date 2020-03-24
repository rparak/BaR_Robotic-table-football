
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif

void check_attack_mode(struct check_attack_mode* ch_aM)
{
	struct calculation_posDummies calculation_posDummies_0;
	struct detect_axisNumber detect_axisNumber_0;
	struct choose_attack_mode choose_attack_mode_0;
	INT behind_position, before_position;
	USINT i_chp, i_aM, stand_mode;
	REAL max_pos[4], min_pos[4];
	
	max_pos[0] = 800;
	max_pos[1] = 1060;
	max_pos[2] = 550;
	max_pos[3] = 860;
	
	min_pos[0] = -910;
	min_pos[1] = -960;
	min_pos[2] = -530;
	min_pos[3] = -800;

	for(i_chp = 0; i_chp < (int)(sizeof(ch_aM->act_displacement_cpu)/sizeof(ch_aM->act_displacement_cpu[0])); i_chp++){
		calculation_posDummies_0.displacement[i_chp] = ch_aM->act_displacement_cpu[i_chp];
		calculation_posDummies_0.max_disp[i_chp]	 = max_pos[i_chp];
		calculation_posDummies_0.min_disp[i_chp]	 = min_pos[i_chp];
	}
	
	calculation_posDummies(&calculation_posDummies_0);
	
	detect_axisNumber_0.ball1_x = ch_aM->ball1_x;
	detect_axisNumber_0.ball2_x = ch_aM->ball2_x;
	detect_axisNumber(&detect_axisNumber_0);
	
	if(detect_axisNumber_0.axis_number != 10){
		if(ch_aM->angle_ofRotation[detect_axisNumber_0.axis_number] > 0){
			// stand before the ball
			behind_position = -90;
			before_position = 90;
			stand_mode		= 1;
		}else{
			// stand behind the ball
			behind_position = -200; // -170
			before_position = 350;  // 320
			stand_mode		= 2;
		}
		
		for(i_aM = 0; i_aM < (int)(sizeof(calculation_posDummies_0.actual_positionsOfDummies)/sizeof(calculation_posDummies_0.actual_positionsOfDummies[0])); i_aM++){
			choose_attack_mode_0.actual_positionsOfDummies[i_aM] = calculation_posDummies_0.actual_positionsOfDummies[i_aM];
		}
		choose_attack_mode_0.ball1_x 		 = ch_aM->ball1_x;
		choose_attack_mode_0.ball1_y 		 = ch_aM->ball1_y;
		choose_attack_mode_0.ball2_x 		 = ch_aM->ball2_x;
		choose_attack_mode_0.ball2_y 		 = ch_aM->ball2_y;
		choose_attack_mode_0.axis_number 	 = detect_axisNumber_0.axis_number;
		choose_attack_mode_0.before_position = before_position;
		choose_attack_mode_0.behind_position = behind_position;
		choose_attack_mode(&choose_attack_mode_0);
		
		if((choose_attack_mode_0.mode == 1) && (stand_mode == 1)){
			ch_aM->attack_mode = 1; // attack mode If ball is behind of dummy
		}else if((choose_attack_mode_0.mode == 1) && (stand_mode == 2)){
			ch_aM->attack_mode = 2; // attack mode If ball is before of dummy
		}else{
			ch_aM->attack_mode = 0; // If ball it isn't near of dummy
		}
		
		ch_aM->index_ofAxis = detect_axisNumber_0.axis_number;
	}else{
		ch_aM->attack_mode  = 0;
		ch_aM->index_ofAxis = 0;
	}
	
	
}

void detect_axisNumber(struct detect_axisNumber* d_aN)
{
	INT x_posOfD[4];
	REAL x_pos[2];
	USINT i_dAn, a_n[2];
	
	x_posOfD[0] = 800;
	x_posOfD[1] = 2300;
	x_posOfD[2] = 5300;
	x_posOfD[3] = 8300;
	
	x_pos[0] = d_aN->ball1_x;
	x_pos[1] = d_aN->ball2_x;
	
	for(i_dAn = 0; i_dAn < (int)(sizeof(x_pos)/sizeof(x_pos[0])); i_dAn++){
		if(x_pos[i_dAn] >= (x_posOfD[3] - 90)){
			a_n[i_dAn] = 3;
		}else if((x_pos[i_dAn] >= (x_posOfD[2] - 90)) && (x_pos[i_dAn] <= (x_posOfD[3] - 90))){
			a_n[i_dAn] = 2;
		}else if((x_pos[i_dAn] >= (x_posOfD[1] - 90)) && (x_pos[i_dAn] <= (x_posOfD[2] - 90))){
			a_n[i_dAn] = 1;
		}else if((x_pos[i_dAn] >= (x_posOfD[0] - 90)) && (x_pos[i_dAn] <= (x_posOfD[1] - 90))){
			a_n[i_dAn] = 0;
		}else{
			a_n[i_dAn] = 10;
		}
		
	}
	
	if((a_n[0] == a_n[1]) || isnan(x_pos[1])){
		d_aN->axis_number = a_n[0];
	}else{
		d_aN->axis_number = a_n[1];
	}
}

void choose_attack_mode(struct choose_attack_mode* ch_aMode)
{
	USINT aux_mode;
	USINT i_df, i_md, i_fw;
	INT x_posOfD[4];
	REAL gk_pos, df_pos[2], md_pos[5], fw_pos[3];
	
	// auxiliary mode 
	aux_mode = 0;
	// initial x pos of axes CPU
	x_posOfD[0] = 800;
	x_posOfD[1] = 2300;
	x_posOfD[2] = 5300;
	x_posOfD[3] = 8300;
	
	// goalkeeper
	gk_pos = ch_aMode->actual_positionsOfDummies[0];
	// defender
	df_pos[0] = ch_aMode->actual_positionsOfDummies[1];
	df_pos[1] = ch_aMode->actual_positionsOfDummies[2];
	// midfielder
	md_pos[0] = ch_aMode->actual_positionsOfDummies[3];
	md_pos[1] = ch_aMode->actual_positionsOfDummies[4];
	md_pos[2] = ch_aMode->actual_positionsOfDummies[5];
	md_pos[3] = ch_aMode->actual_positionsOfDummies[6];
	md_pos[4] = ch_aMode->actual_positionsOfDummies[7];
	// forward
	fw_pos[0] = ch_aMode->actual_positionsOfDummies[8];
	fw_pos[1] = ch_aMode->actual_positionsOfDummies[9];
	fw_pos[2] = ch_aMode->actual_positionsOfDummies[10];
	
	switch(ch_aMode->axis_number){
		case 0:
			{
				if((((ch_aMode->ball1_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
					&& (ch_aMode->ball1_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position)))
					|| ((ch_aMode->ball2_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
					&& (ch_aMode->ball2_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position))))
					&& ((ch_aMode->ball1_y <= (gk_pos + 150)) && (ch_aMode->ball1_y >= (gk_pos - 150))
					|| ((ch_aMode->ball2_y <= (gk_pos + 150)) && (ch_aMode->ball2_y >= (gk_pos - 150))))){
					aux_mode = 1;
				}else{
					aux_mode = 0;
				}
			}
			break;
		case 1:
			{
				for(i_df = 0; i_df < (int)(sizeof(df_pos)/sizeof(df_pos[0])); i_df++){
					if((((ch_aMode->ball1_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball1_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position)))
						|| ((ch_aMode->ball2_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball2_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position))))
						&& ((ch_aMode->ball1_y <= (df_pos[i_df] + 150)) && (ch_aMode->ball1_y >= (df_pos[i_df] - 150))
						|| ((ch_aMode->ball2_y <= (df_pos[i_df] + 150)) && (ch_aMode->ball2_y >= (df_pos[i_df] - 150))))){
						aux_mode = 1;
					}
				}
			}
			break;
		case 2:
			{
				for(i_md = 0; i_md < (int)(sizeof(md_pos)/sizeof(md_pos[0])); i_md++){
					if((((ch_aMode->ball1_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball1_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position)))
						|| ((ch_aMode->ball2_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball2_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position))))
						&& ((ch_aMode->ball1_y <= (md_pos[i_md] + 150)) && (ch_aMode->ball1_y >= (md_pos[i_md] - 150))
						|| ((ch_aMode->ball2_y <= (md_pos[i_md] + 150)) && (ch_aMode->ball2_y >= (md_pos[i_md] - 150))))){
						aux_mode = 1;
					}
				}
			}
			break;
		case 3:
			{
				for(i_fw = 0; i_fw < (int)(sizeof(fw_pos)/sizeof(fw_pos[0])); i_fw++){
					if((((ch_aMode->ball1_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball1_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position)))
						|| ((ch_aMode->ball2_x <= (x_posOfD[ch_aMode->axis_number] + ch_aMode->before_position))
						&& (ch_aMode->ball2_x >= (x_posOfD[ch_aMode->axis_number] + ch_aMode->behind_position))))
						&& ((ch_aMode->ball1_y <= (fw_pos[i_fw] + 150)) && (ch_aMode->ball1_y >= (fw_pos[i_fw] - 150))
						|| ((ch_aMode->ball2_y <= (fw_pos[i_fw] + 150)) && (ch_aMode->ball2_y >= (fw_pos[i_fw] - 150))))){
						aux_mode = 1;
					}
				}
			}
			break;
	}// end switch
	
	if(aux_mode == 1){
		ch_aMode->mode = aux_mode;
	}else{
		ch_aMode->mode = 0;
	}
}