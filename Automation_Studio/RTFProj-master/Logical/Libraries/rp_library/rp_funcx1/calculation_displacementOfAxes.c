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
* Implementation OF PROGRAM simulation(rp_library/rp_funcx1/rp_functions.c)
**********************************************************************************************/

/************************************* LIBRARIES *********************************************/
#include <bur/plctypes.h>
#include <math.h>
#include <string.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif

void calculation_displacementOfAxes(struct calculation_displacementOfAxes* c_dOA)
{
	REAL max_dispOfD[4], min_dispOfD[4], max_posOfD[4], min_posOfD[4], matrix_posOfCPU[4][5], real_disp[4];
	REAL velocity[4], acceleration[4], deceleration[4];
	REAL aux_velocity[4], aux_acceleration[4];
	REAL aux_time;
	UDINT auxiliary_str;
	USINT i_rC, i_rCn, i, j, i_out, i_chRD, i_chRDn, i_chRDnn;
	
	struct calculation_realCrossing calc_rC;
	struct choosing_rightDummy ch_rightD;
	
	// Ceilings of the axes
	// Axes
	max_posOfD[0] = 820;
	max_posOfD[1] = 3050;
	max_posOfD[2] = 3050;
	max_posOfD[3] = 3055;
	
	min_posOfD[0] = -930;
	min_posOfD[1] = -3050;
	min_posOfD[2] = -3050;
	min_posOfD[3] = -3055;
	// Dummies {-50 units, without GK}
	max_dispOfD[0] = 800;
	max_dispOfD[1] = 1030;
	max_dispOfD[2] = 520;
	max_dispOfD[3] = 830;
	
	min_dispOfD[0] = -910;
	min_dispOfD[1] = -930;
	min_dispOfD[2] = -500;
	min_dispOfD[3] = -770;
	// Actual positions of dummies CPU
	// goalkeeper
	matrix_posOfCPU[0][0] = 0 + c_dOA->act_displacementCPU[0];
	// defender
	matrix_posOfCPU[1][0] = -1200 + c_dOA->act_displacementCPU[1];
	matrix_posOfCPU[1][1] = 1200 + c_dOA->act_displacementCPU[1];
	// midfielder
	matrix_posOfCPU[2][0] = -2400 + c_dOA->act_displacementCPU[2];
	matrix_posOfCPU[2][1] = -1200 + c_dOA->act_displacementCPU[2];
	matrix_posOfCPU[2][2] = 0 + c_dOA->act_displacementCPU[2];
	matrix_posOfCPU[2][3] = 1200 + c_dOA->act_displacementCPU[2];
	matrix_posOfCPU[2][4] = 2400 + c_dOA->act_displacementCPU[2];
	// forward
	matrix_posOfCPU[3][0] = -2100 + c_dOA->act_displacementCPU[3];
	matrix_posOfCPU[3][1] = 0 + c_dOA->act_displacementCPU[3];
	matrix_posOfCPU[3][2] = 2100 + c_dOA->act_displacementCPU[3];
	
	// function block -> output is a array of real crossing
	calc_rC.tilted = c_dOA->tilted;
	auxiliary_str = (UDINT) strcpy(calc_rC.specific_direction,c_dOA->specific_direction);
	for(i_rC = 0; i_rC < (int)(sizeof(max_posOfD)/sizeof(max_posOfD[0])); i_rC++){
		calc_rC.act_posOfAxesCPU_Y[i_rC]		 = c_dOA->act_posOfAxesCPU_Y[i_rC];
		calc_rC.act_posOfAxesHUM_Y[i_rC]		 = c_dOA->act_posOfAxesHUM_Y[i_rC];
		calc_rC.count_axesIntersectionHUM[i_rC]  = c_dOA->count_axesIntersectionHUM[i_rC];
		calc_rC.reversed_HUM[i_rC]				 = c_dOA->reversed_HUM[i_rC];
	}
	for(i_rCn = 0; i_rCn < (int)(sizeof(c_dOA->act_posOfDummiesH)/sizeof(c_dOA->act_posOfDummiesH[0])); i_rCn++){
		calc_rC.act_posOfDummiesH[i_rCn] = c_dOA->act_posOfDummiesH[i_rCn];
	}
	calc_rC.x_posOfBall[0] = c_dOA->x_posOfBall[0];
	calc_rC.x_posOfBall[1] = c_dOA->x_posOfBall[1];
	calculation_realCrossing(&calc_rC);

	for(i = 0; i < (int)(sizeof(calc_rC.real_cross)/sizeof(calc_rC.real_cross[0])); i++){
		if(calc_rC.real_cross[i] > max_dispOfD[i]){
			real_disp[i] = max_dispOfD[i];
		}else if(calc_rC.real_cross[i] < min_dispOfD[i] && calc_rC.real_cross[i] < max_dispOfD[i]){
			real_disp[i] = min_dispOfD[i];
		}else {
			ch_rightD.index      = i;
			ch_rightD.real_cross = calc_rC.real_cross[i];
				
			for(i_chRD = 0; i_chRD < (int)(sizeof(max_dispOfD)/sizeof(max_dispOfD[0])); i_chRD++){
				ch_rightD.max_dispOfD[i_chRD] = max_dispOfD[i_chRD];
				ch_rightD.min_dispOfD[i_chRD] = min_dispOfD[i_chRD];
			}
			
			for(i_chRDn = 0; i_chRDn < (int)(sizeof(max_dispOfD)/sizeof(max_dispOfD[0])); i_chRDn++){
				for(i_chRDnn = 0; i_chRDnn <= (int)(sizeof(max_dispOfD)/sizeof(max_dispOfD[0]));i_chRDnn++){
					ch_rightD.matrix_posOfCPU[i_chRDn][i_chRDnn] = matrix_posOfCPU[i_chRDn][i_chRDnn];
				}
			}
			choosing_rightDummy(&ch_rightD);
				
			real_disp[i] = ch_rightD.actual_displacement;
		}
	}// end for{i}
	
	for(i_out = 0; i_out < (int)(sizeof(calc_rC.real_cross)/sizeof(calc_rC.real_cross[0])); i_out++){
		// max velocity = 29000, max acceleration = 489 000
		aux_time = 0.07;
		aux_velocity[i_out] = fabs(fabs(real_disp[i_out]) - fabs(c_dOA->act_displacementCPU[i_out]))/c_dOA->time_axisIntersection[i_out];
			
		if(aux_velocity[i_out] > 29000){
			velocity[i_out] 		= fabs(fabs(real_disp[i_out]) - fabs(c_dOA->act_displacementCPU[i_out]))/aux_time;
			aux_acceleration[i_out] = velocity[i_out]/c_dOA->time_axisIntersection[i_out];
				
			if(aux_acceleration[i_out] > 489000){
				acceleration[i_out] = 489000;
				deceleration[i_out] = 489000;
			}else{
				acceleration[i_out] = aux_acceleration[i_out];
				deceleration[i_out] = aux_acceleration[i_out];
			}
		}else{
			velocity[i_out] 		= aux_velocity[i_out];
			aux_acceleration[i_out] = velocity[i_out]/c_dOA->time_axisIntersection[i_out];
				
			if(aux_acceleration[i_out] > 489000){
				acceleration[i_out] = 489000;
				deceleration[i_out] = 489000;
			}else{
				acceleration[i_out] = aux_acceleration[i_out];
				deceleration[i_out] = aux_acceleration[i_out];
			}
		}
		
		if(real_disp[i_out] > max_dispOfD[i_out]){
			c_dOA->displacement[i_out] = max_dispOfD[i_out];
		}else if(real_disp[i_out] < min_dispOfD[i_out] && real_disp[i_out] < max_dispOfD[i_out]){
			c_dOA->displacement[i_out] = min_dispOfD[i_out];
		}else{
			c_dOA->displacement[i_out] = real_disp[i_out];
		}
		c_dOA->velocity[i_out] 	   = velocity[i_out];
		c_dOA->acceleration[i_out] = acceleration[i_out];
		c_dOA->deceleration[i_out] = deceleration[i_out];
	}// end for{i_out}
	
}// end function

void calculation_realCrossing(struct calculation_realCrossing* c_rC)
{
	REAL matrix_posOfHUM[4][5], matrix_crossH_Iter[0][5], matrix_crossH_Pos[0][5];
	REAL predicted_pos;
	USINT number_ofD[4], count_crossH, count_calcH;
	USINT iteration, iteration_positionH;
	USINT j, j_null, i_yC, i_yCn, i_cNC, i_out, r;
	BOOL auxiliary_bool,auxiliary_boolNo2;
	UDINT auxiliary_str;
	
	struct calculation_newCrossing calc_newC;
	
	auxiliary_bool 	  = 0;
	auxiliary_boolNo2 = 0;
	// Actual positions of dummies HUMAN
	// goalkeeper
	matrix_posOfHUM[0][0] = c_rC->act_posOfDummiesH[0];
	// defender
	matrix_posOfHUM[1][0] = c_rC->act_posOfDummiesH[1];
	matrix_posOfHUM[1][1] = c_rC->act_posOfDummiesH[2];
	// midfielder
	matrix_posOfHUM[2][0] = c_rC->act_posOfDummiesH[3];
	matrix_posOfHUM[2][1] = c_rC->act_posOfDummiesH[4];
	matrix_posOfHUM[2][2] = c_rC->act_posOfDummiesH[5];
	matrix_posOfHUM[2][3] = c_rC->act_posOfDummiesH[6];
	matrix_posOfHUM[2][4] = c_rC->act_posOfDummiesH[7];
	// forward
	matrix_posOfHUM[3][0] = c_rC->act_posOfDummiesH[8];
	matrix_posOfHUM[3][1] = c_rC->act_posOfDummiesH[9];
	matrix_posOfHUM[3][2] = c_rC->act_posOfDummiesH[10];
	
	number_ofD[0] = 1;
	number_ofD[1] = 2;
	number_ofD[2] = 5;
	number_ofD[3] = 3;
	
	calc_newC.reversed_HUM = 1;
	
	count_crossH   = c_rC->count_axesIntersectionHUM[0];	
	count_calcH    = 5 - count_crossH;
	
	if(count_calcH == 0){
		iteration = 1;
	}else{
		iteration = count_calcH;
	}
	
	if(count_calcH < 5){
		for(j = 0; j < number_ofD[count_calcH - 1]; j++){
			if(c_rC->reversed_HUM[count_calcH - 1] == 0){
				if(((matrix_posOfHUM[count_calcH - 1][j] <= c_rC->act_posOfAxesHUM_Y[count_calcH - 1] + 100) && (matrix_posOfHUM[count_calcH - 1][j] >= c_rC->act_posOfAxesHUM_Y[count_calcH - 1])) && (matrix_posOfHUM[count_calcH - 1][j] != c_rC->act_posOfAxesHUM_Y[count_calcH - 1])){
					matrix_crossH_Iter[0][j] = count_calcH;
					matrix_crossH_Pos[0][j]  = fabs(fabs(matrix_posOfHUM[count_calcH - 1][j]) - fabs(c_rC->act_posOfAxesHUM_Y[count_calcH - 1]));
				}else if(((matrix_posOfHUM[count_calcH - 1][j] >= c_rC->act_posOfAxesHUM_Y[count_calcH - 1] - 100) && (matrix_posOfHUM[count_calcH - 1][j] <= c_rC->act_posOfAxesHUM_Y[count_calcH - 1])) && (matrix_posOfHUM[count_calcH - 1][j] != c_rC->act_posOfAxesHUM_Y[count_calcH - 1])){
					matrix_crossH_Iter[0][j] = count_calcH;
					matrix_crossH_Pos[0][j]  = (-1)*fabs(fabs(matrix_posOfHUM[count_calcH - 1][j]) - fabs(c_rC->act_posOfAxesHUM_Y[count_calcH - 1]));					
				}else if(matrix_posOfHUM[count_calcH - 1][j] == c_rC->act_posOfAxesHUM_Y[count_calcH - 1]){
					matrix_crossH_Iter[0][j] = count_calcH;
					matrix_crossH_Pos[0][j]  = 0;
				}else{
					matrix_crossH_Iter[0][j] = 0;
					matrix_crossH_Pos[0][j]  = 0;
				}
			}else{
				matrix_crossH_Iter[0][j] = 0;
				matrix_crossH_Pos[0][j]  = 0;
			}
		}
		
		for(r = 0; r < number_ofD[count_calcH - 1]; r++){
			if(matrix_crossH_Iter[0][r] != 0){
				calc_newC.reversed_HUM = 0;
			}
		}
		for(j_null = 0; j_null < number_ofD[count_calcH - 1]; j_null++){
			if(matrix_crossH_Iter[0][j_null] != 0){
				auxiliary_bool 		= 1;
				predicted_pos  		= matrix_crossH_Pos[0][j_null];
				iteration_positionH = matrix_crossH_Iter[0][j_null];
			}
		}
		
		if(auxiliary_bool == 0){
			if(c_rC->tilted == 0){
				predicted_pos 		= 0;
				iteration_positionH = iteration;
			}else{
				auxiliary_boolNo2 = 1;
				for(i_yCn = 0; i_yCn < (int)(sizeof(c_rC->act_posOfAxesCPU_Y)/sizeof(c_rC->act_posOfAxesCPU_Y[0])); i_yCn++){
					c_rC->real_cross[i_yCn] = c_rC->act_posOfAxesCPU_Y[i_yCn];
				}
			}
		}
		
	}else{
		if(c_rC->tilted == 0){
			calc_newC.reversed_HUM = 0;
			predicted_pos 		   = 0;
			iteration_positionH    = count_calcH;
		}else{
			auxiliary_boolNo2 = 1;
			for(i_yC = 0; i_yC < (int)(sizeof(c_rC->act_posOfAxesCPU_Y)/sizeof(c_rC->act_posOfAxesCPU_Y[0])); i_yC++){
				c_rC->real_cross[i_yC] = c_rC->act_posOfAxesCPU_Y[i_yC];
			}
		}
	}// end : if(count_calcH < 5)
	
	if(auxiliary_boolNo2 != 1){
		auxiliary_str = (UDINT) strcpy(calc_newC.specific_direction,c_rC->specific_direction);
		calc_newC.iteration 		 = iteration_positionH;
		calc_newC.predicted_position = predicted_pos;
		for(i_cNC = 0; i_cNC < (int)(sizeof(c_rC->act_posOfAxesCPU_Y)/sizeof(c_rC->act_posOfAxesCPU_Y[0])); i_cNC++){
			calc_newC.act_posOfAxesCPU_Y[i_cNC] = c_rC->act_posOfAxesCPU_Y[i_cNC];
			calc_newC.act_posOfAxesHUM_Y[i_cNC] = c_rC->act_posOfAxesHUM_Y[i_cNC];
		}
		calc_newC.x_posOfBall[0] = c_rC->x_posOfBall[0]; 
		calc_newC.x_posOfBall[1] = c_rC->x_posOfBall[1]; 
		calculation_newCrossing(&calc_newC);
	
		for(i_out = 0; i_out < (int)(sizeof(c_rC->act_posOfAxesCPU_Y)/sizeof(c_rC->act_posOfAxesCPU_Y[0])); i_out++){
			c_rC->real_cross[i_out] = calc_newC.new_cross[i_out];
		}
	}// end if(auxiliary_boolNo2 != 1)
}// end function

void calculation_newCrossing(struct calculation_newCrossing* c_nC)
{
	INT gk_max, gk_min, value;
	SINT iteration;
	DINT resultUP, resultLF, resultDOWN, resultRH;
	REAL y_crossGK, y_crossDF, y_crossMD, y_crossFW;
	
	// initial max goalkeeper
	gk_max = 800;
	gk_min = -910;
	
	resultUP   = strcmp(c_nC->specific_direction, "up_backward");
	resultLF   = strcmp(c_nC->specific_direction, "left");
	resultDOWN = strcmp(c_nC->specific_direction, "down_backward");
	resultRH   = strcmp(c_nC->specific_direction, "right");
	
	if(resultUP == 0 || resultLF == 0){
		value = 200;
	}else if(resultDOWN == 0 || resultRH == 0){
		value = -200;
	}else{
		value = 200;
	}
	
	if(c_nC->iteration > 4){
		iteration = 4;
	}else{
		iteration = c_nC->iteration;
	}
	
	switch(iteration){
		case 1:
			{
				y_crossFW = c_nC->act_posOfAxesCPU_Y[4];
				y_crossMD = y_crossFW + value;
				y_crossDF = y_crossMD + value;
				y_crossGK = y_crossDF + value;
			
				if(fabs(y_crossGK) > fabs(y_crossFW)){
					y_crossGK = y_crossFW - value;
				}
			
				if(fabs(y_crossMD) < fabs(y_crossFW)){
					y_crossMD = y_crossFW - value;
					y_crossDF = y_crossMD - value;
				}
			}
			break;
		case 2:
			{
				if(c_nC->x_posOfBall[0] >= 9800){
					y_crossFW = c_nC->act_posOfAxesHUM_Y[iteration] - c_nC->predicted_position;
					y_crossMD = y_crossFW + value;
					y_crossDF = y_crossMD + value;
					y_crossGK = y_crossDF + value;
			
					if(fabs(y_crossGK) > fabs(y_crossFW)){
						y_crossGK = y_crossFW - value;
					}
			
					if(fabs(y_crossMD) < fabs(y_crossFW)){
						y_crossMD = y_crossFW - value;
						y_crossDF = y_crossMD - value;
					}
				}else{
					y_crossFW = c_nC->act_posOfAxesHUM_Y[3] - c_nC->predicted_position;
					y_crossMD = y_crossFW + value;
					y_crossDF = y_crossMD + value;
					y_crossGK = y_crossDF + value;
			
					if(fabs(y_crossGK) > fabs(y_crossFW)){
						y_crossGK = y_crossFW - value;
					}
			
					if(fabs(y_crossMD) < fabs(y_crossFW)){
						y_crossMD = y_crossFW - value;
						y_crossDF = y_crossMD - value;
					}
				}
			}
			break;
		case 3:
			{
				if(c_nC->reversed_HUM == 1){
					y_crossFW = c_nC->act_posOfAxesHUM_Y[3] - c_nC->predicted_position;
					y_crossMD = y_crossFW + value;
				}else{
					y_crossFW = c_nC->act_posOfAxesHUM_Y[3] - c_nC->predicted_position;
					y_crossMD = y_crossFW + value;
				}
				
				y_crossDF = y_crossMD + value;
				y_crossGK = y_crossFW + value;
			
				if(fabs(y_crossGK) > fabs(y_crossFW)){
					y_crossGK = y_crossFW - value;
				}
			
				if(fabs(y_crossMD) < fabs(y_crossFW)){
					y_crossMD = y_crossFW - value;
					y_crossDF = y_crossMD - value;
				}
			}
			break;
		case 4:
			{
				if(c_nC->x_posOfBall[0] >= 5300){
					if(c_nC->reversed_HUM == 1){
						y_crossFW = c_nC->act_posOfAxesCPU_Y[3] - c_nC->predicted_position;
						y_crossMD = c_nC->act_posOfAxesCPU_Y[2] - c_nC->predicted_position;
						y_crossDF = y_crossMD + value;
						y_crossGK = y_crossFW + value;
					}else{
						y_crossFW = c_nC->act_posOfAxesCPU_Y[3] - c_nC->predicted_position;
						y_crossMD = c_nC->act_posOfAxesCPU_Y[2] - c_nC->predicted_position;
						y_crossDF = y_crossMD - c_nC->predicted_position;
						y_crossGK = y_crossFW + value;
					
					}
            
					if(fabs(y_crossGK) > fabs(y_crossFW)){
						y_crossGK = y_crossFW - value;
					}
					if(fabs(y_crossMD) < fabs(y_crossFW)){
						y_crossDF = y_crossMD - value;
					}
				}else{
					y_crossFW = c_nC->act_posOfAxesCPU_Y[3] - c_nC->predicted_position;
					y_crossMD = c_nC->act_posOfAxesCPU_Y[2] - c_nC->predicted_position;
					y_crossDF = y_crossMD - c_nC->predicted_position;
					y_crossGK = y_crossFW + value;
				}
			
				if(c_nC->x_posOfBall[0] <= 2300){
					y_crossGK = c_nC->act_posOfAxesCPU_Y[0];
				}
			}
			break;
	}// end switch
	
	
	if(y_crossGK > gk_max){
		y_crossGK = y_crossDF - 200;
	}else if(y_crossGK < gk_min){
		y_crossGK = y_crossDF + 200;
	}
	
	//c_nC->new_cross[0] = y_crossGK;
	
	if(c_nC->act_posOfAxesCPU_Y[0] > gk_max){
		c_nC->new_cross[0] = gk_max;
	}else if(c_nC->act_posOfAxesCPU_Y[0] < gk_min){
		c_nC->new_cross[0] = gk_min;
	}else{
		c_nC->new_cross[0] = c_nC->act_posOfAxesCPU_Y[0];
	}
	
	c_nC->new_cross[1] = y_crossDF;
	c_nC->new_cross[2] = y_crossMD;
	c_nC->new_cross[3] = y_crossFW;
	
}// end function

void choosing_rightDummy(struct choosing_rightDummy* ch_rD)
{
	REAL real_cross;
	REAL d_DFD[2],d_MDD[5], d_FWD[3];
	USINT i_df, i_md, i_fw;
	struct calculete_min calc_m;
	
	switch(ch_rD->index){
		case 0:
			{
				real_cross 				   = ch_rD->real_cross;
				ch_rD->actual_displacement = real_cross;
			}
			break;
		case 1:
			{
				d_DFD[0] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][0]) + ch_rD->real_cross));
				d_DFD[1] = fabs((ch_rD->matrix_posOfCPU[ch_rD->index][1] - ch_rD->real_cross));
				
				for(i_df = 0; i_df < (int)(sizeof(calc_m.cmp_num)/sizeof(calc_m.cmp_num[0])); i_df++){
					if(i_df < ((int)(sizeof(d_DFD)/sizeof(d_DFD[0])))){
						calc_m.cmp_num[i_df] = d_DFD[i_df];
					}else{
						calc_m.cmp_num[i_df] = 5000;
					}
				}
			}
			break;
		case 2:
			{
				d_MDD[0] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][0]) + ch_rD->real_cross));
				d_MDD[1] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][1]) + ch_rD->real_cross));
				d_MDD[2] = fabs((ch_rD->real_cross));
				d_MDD[3] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][3]) - ch_rD->real_cross));
				d_MDD[4] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][4]) - ch_rD->real_cross));
			
				for(i_md = 0; i_md < (int)(sizeof(calc_m.cmp_num)/sizeof(calc_m.cmp_num[0])); i_md++){
					calc_m.cmp_num[i_md] = d_MDD[i_md];
				}
			}
			break;
		case 3:
			{
				d_FWD[0] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][0]) + ch_rD->real_cross));
				d_FWD[1] = fabs((ch_rD->real_cross));
				d_FWD[2] = fabs((fabs(ch_rD->matrix_posOfCPU[ch_rD->index][2]) - ch_rD->real_cross));
			
				for(i_fw = 0; i_fw < (int)(sizeof(calc_m.cmp_num)/sizeof(calc_m.cmp_num[0])); i_fw++){
					if(i_fw < ((int)(sizeof(d_FWD)/sizeof(d_FWD[0])))){
						calc_m.cmp_num[i_fw] = d_FWD[i_fw];
					}else{
						calc_m.cmp_num[i_fw] = 5000;
					}
				}
			}
			break;
	}// end switch
	
	if(ch_rD->index != 0){
		calculete_min(&calc_m);
		
		if(calc_m.number > ch_rD->max_dispOfD[ch_rD->index]){
			real_cross = ch_rD->max_dispOfD[ch_rD->index];
		}else if(calc_m.number < ch_rD->min_dispOfD[ch_rD->index]){
			real_cross = ch_rD->min_dispOfD[ch_rD->index];
		}else{
			real_cross = calc_m.number;
		}
			
		if(ch_rD->real_cross > ch_rD->matrix_posOfCPU[ch_rD->index][calc_m.index]){
			ch_rD->actual_displacement = real_cross;
		}else{
			ch_rD->actual_displacement = (-1)*real_cross;
		}
	}
}// end function

void calculete_min(struct calculete_min* c_m)
{
	REAL min;
	USINT i, idx;
	
	min = 30000;
	for(i = 0; i < (int)(sizeof(c_m->cmp_num)/sizeof(c_m->cmp_num[0])); i++){
		if(c_m->cmp_num[i] < min){
			min = c_m->cmp_num[i];
			idx = i;
		}
	}
	
	c_m->index  = idx;
	c_m->number = min;
}// end function