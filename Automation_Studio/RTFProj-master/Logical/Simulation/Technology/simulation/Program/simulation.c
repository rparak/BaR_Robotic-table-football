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
* Implementation OF PROGRAM simulation(Simulation/Technology/simulation/Program/simulation.c)
**********************************************************************************************/

/*************************** LIBRARIES *********************************/
#include <bur/plc.h>
#include <bur/plctypes.h>
#include <astime.h>
#include <math.h>

#include "rp_funcx1.h"
#include "Structures/simulation_str.h"
#include "Functions/sim_mapp.h"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

/*************************** DEFINITIONS *******************************/
#define EACH_FORMATION 1;

/************************ LOCAL VARIABLES ******************************/

// struct - rp_funcx1
_LOCAL struct forecast_direction f_d;
_LOCAL struct calculation_posDummies c_ppd;
_LOCAL struct calculation_crossingBall c_cb[2];
_LOCAL struct calculation_displacementOfAxes c_doa;
_LOCAL struct start_rotaryAxis start_rotaryAxis_0;
_LOCAL struct control_temperature c_temp;
_LOCAL struct axes_control axes_control_0[4];
_LOCAL struct ball_shooting ball_s;
_LOCAL struct check_attack_mode check_attack_mode_0;
_LOCAL struct start_virtualAxis s_virtualA;
// struct - MpAlarmX
_LOCAL MpAlarmXListUIConnectType AlarmListUI_ConnectType;
_LOCAL MpAlarmXHistoryUIConnectType AlarmHistoryUI_ConnectType;
// udint
_LOCAL UDINT alarm_device_address, specific_directionOfBall;
// usint
_LOCAL USINT max_numberOfFormation;
_LOCAL USINT i_axisNum;
_LOCAL USINT i_bs;
_LOCAL USINT i_ppd, i_ccd, i_ccdCPU, i_ccdHUM, i_cdoa1, i_cdoa2, i_cdoa3;
_LOCAL USINT c_dp;
_LOCAL USINT i_def, i_dp1, i_dp2;
_LOCAL USINT c_bState;
// bool
_LOCAL BOOL ESTOP,error_s,reset_safetyESTOP;
_LOCAL BOOL start_game;
// real
_LOCAL REAL x_posOfCPU[4];
_LOCAL REAL x_posOfHUM[4];
// OUPTUT from the SENSOR & CAMERA
_LOCAL REAL ball1[2], ball2[2], time_B2B;
_LOCAL REAL optical_sensor[4];
_LOCAL REAL reflex_sensor[4];
// state machine
_LOCAL soccer_table_ENUM SOCCER_TABLE_STEP;
_LOCAL soccer_table_ENUM BEFORE_STATE;


/**********************************************************************************************************/
/********************************************** INIT PROGRAM **********************************************/
/**********************************************************************************************************/
void _INIT ProgramInit(void)
{
    /*********************************** declaration variables **********************************/
    // generally
    max_numberOfFormation = 4;
    // axis type -> MAPP
    // linear
	gLinkAxes_linear[0] = gk_mappAxisLS;
    gLinkAxes_linear[1] = df_mappAxisLS;
    gLinkAxes_linear[2] = md_mappAxisLS;
    gLinkAxes_linear[3] = fw_mappAxisLS;
    // rotary
    gLinkAxes_rotary[0] = gk_mappAxisRS;
    gLinkAxes_rotary[1] = df_mappAxisRS;
    gLinkAxes_rotary[2] = md_mappAxisRS;
    gLinkAxes_rotary[3] = fw_mappAxisRS;
    
    /************************************ control of AlarmX ************************************/
    // adjustment device name
    alarm_device_address = (UDINT) strcpy(mp_alarmX.deviceName_no1_exp,"EXPORT_HISTORY");
    // MpAlarmX Core
    mp_alarmX.mp_core.MpLink         = &gAlarmXCoreS;
    mp_alarmX.mp_core.Enable         = 1;
    // MpAlarmX ListUI
    mp_alarmX.mp_listUI.MpLink       = &gAlarmXCoreS;
    mp_alarmX.mp_listUI.Enable       = 1;
    mp_alarmX.mp_listUI.UIConnect    = &AlarmListUI_ConnectType;
    // MpAlarmX History
    mp_alarmX.mp_history.MpLink      = &gAlarmXHistoryS;
    mp_alarmX.mp_history.Enable      = 1;
    mp_alarmX.mp_history.DeviceName  = &mp_alarmX.deviceName_no1_exp;
    // MpAlarmX HistoryUI
    mp_alarmX.mp_historyUI.MpLink    = &gAlarmXHistoryS;
    mp_alarmX.mp_historyUI.Enable    = 1;
    mp_alarmX.mp_historyUI.UIConnect = &AlarmHistoryUI_ConnectType;
    
    /************************************* control of axes **************************************/
    for(i_axisNum = 0; i_axisNum <= max_numberOfFormation - 1; i_axisNum++){
        // initialization ACOPOS variables through function(get_axisParam), that returns two variables type of UDINT
        // into the structure -> axesAcopos(have two parameters : linear, rotary)
        axis_acopos = get_axisParam(i_axisNum);	
        // linear -> LinMot
        // linear axis basic
        mp_Axis.mp_axisLinear[i_axisNum].Enable     = 1;
        mp_Axis.mp_axisLinear[i_axisNum].MpLink     = &gLinkAxes_linear[i_axisNum];
        mp_Axis.mp_axisLinear[i_axisNum].Parameters = &mp_Axis.param_axisLinear[i_axisNum];
        mp_Axis.mp_axisLinear[i_axisNum].Axis       = axis_acopos.linear;
        // linear cyclic set
        mp_Axis.mp_cyclicSetLinear[i_axisNum].Enable     = 1;
        mp_Axis.mp_cyclicSetLinear[i_axisNum].MpLink     = &gLinkAxes_linear[i_axisNum];
        mp_Axis.mp_cyclicSetLinear[i_axisNum].Parameters = &mp_Axis.param_cyclicSetLinear[i_axisNum];
		// adjustment max velocity
		mp_Axis.param_cyclicSetLinear[i_axisNum].PositionModeMaxVelocity = 30000;
		// config
		mp_Axis.mp_configAxisLinear[i_axisNum].Enable 		 = 1;
		mp_Axis.mp_configAxisLinear[i_axisNum].MpLink 		 = &gLinkAxes_linear[i_axisNum];
		mp_Axis.mp_configAxisLinear[i_axisNum].Configuration = &mp_Axis.param_configAxisLinear[i_axisNum];
        // rotary -> EnDat
        // rotary axis basic
        mp_Axis.mp_axisRotary[i_axisNum].Enable     = 1;
        mp_Axis.mp_axisRotary[i_axisNum].MpLink     = &gLinkAxes_rotary[i_axisNum];
        mp_Axis.mp_axisRotary[i_axisNum].Parameters = &mp_Axis.param_axisRotary[i_axisNum];
        mp_Axis.mp_axisRotary[i_axisNum].Axis       = axis_acopos.rotary;
        // rotary cyclic set
        mp_Axis.mp_cyclicSetRotary[i_axisNum].Enable     = 1;
        mp_Axis.mp_cyclicSetRotary[i_axisNum].MpLink     = &gLinkAxes_rotary[i_axisNum];
        mp_Axis.mp_cyclicSetRotary[i_axisNum].Parameters = &mp_Axis.param_cyclicSetRotary[i_axisNum];
		// adjustment max velocity
		mp_Axis.param_cyclicSetRotary[i_axisNum].PositionModeMaxVelocity = 85000;
		// config
		mp_Axis.mp_configAxisRotary[i_axisNum].Enable 		 = 1;
		mp_Axis.mp_configAxisRotary[i_axisNum].MpLink 		 = &gLinkAxes_rotary[i_axisNum];
		mp_Axis.mp_configAxisRotary[i_axisNum].Configuration = &mp_Axis.param_configAxisRotary[i_axisNum];
		// temperature - linear
		mp_Axis.param_axisLinear[i_axisNum].CyclicRead.MotorTempMode = mpAXIS_READ_POLLING_5s;
		// temperature - rotary
		mp_Axis.param_axisRotary[i_axisNum].CyclicRead.MotorTempMode = mpAXIS_READ_POLLING_5s;
    }
    // initialization switch
    SOCCER_TABLE_STEP = RST_EMPTY;
    // initialization x axes for CPU
    x_posOfCPU[0] = 800;
    x_posOfCPU[1] = 2300;
    x_posOfCPU[2] = 5300;
    x_posOfCPU[3] = 8300;
    // initialization x axes for HUMAN
    x_posOfHUM[0] = 3800;
    x_posOfHUM[1] = 6800;
    x_posOfHUM[2] = 9800;
    x_posOfHUM[3] = 11300;
    // OUPTUT from the SENSOR & CAMERA
    // CAMERA
    ball1[0] = 0;
    ball1[1] = 0;
    ball2[0] = 0;
    ball2[1] = 0;
    time_B2B = 0;
    // SENSOR
    optical_sensor[0] = 0;
    optical_sensor[1] = 0;
    optical_sensor[2] = 0;
    optical_sensor[3] = 0;
    
    reflex_sensor[0] = 1;
    reflex_sensor[1] = 1;
    reflex_sensor[2] = 1;
    reflex_sensor[3] = 1;
	// init safety
	ESTOP = 1;
	// axes control
	// FB for linear and fotary axes -> Control
	axes_control_0[0].Enable			 = 1;
	axes_control_0[0].linear_axis_cyclic = &mp_Axis.mp_cyclicSetLinear[0];
	axes_control_0[0].linear_axis_param  = &mp_Axis.param_cyclicSetLinear[0];
	axes_control_0[0].rotary_axis_cyclic = &mp_Axis.mp_cyclicSetRotary[0];
	axes_control_0[0].rotary_axis_param  = &mp_Axis.param_cyclicSetRotary[0];
	
	s_virtualA.Enable 	  = 1;
	s_virtualA.axis_name  = &mp_Axis.mp_axisLinear[0];
	s_virtualA.axis_param = &mp_Axis.param_axisLinear[0];
}// end _INIT

/**********************************************************************************************************/
/********************************************** MAIN PROGRAM **********************************************/
/**********************************************************************************************************/
void _CYCLIC ProgramCyclic(void)
{  
    switch(SOCCER_TABLE_STEP){
		case RST_EMPTY:
			{
				
			}
			break;
		case RST_INITIALIZATION_1:
			{
				// home virtual linear axis
				s_virtualA.start_btn = 1;
				start_virtualAxis(&s_virtualA);
				
				if(s_virtualA.succesfully == 1 && (mp_Axis.mp_axisLinear[0].PowerOn == 1 && mp_Axis.mp_axisLinear[0].IsHomed == 1)){
					SOCCER_TABLE_STEP = RST_INITIALIZATION_2;
				}
			}
			break;
		case RST_INITIALIZATION_2:
			{
				
			}
			break;
		case RST_INITIALIZATION_3:
			{
				
			}
			break;
		case RST_INITIALIZATION_4:
			{	
				check_attack_mode_0.ball1_x = ball1[0];
				check_attack_mode_0.ball1_y = ball1[1];
				check_attack_mode_0.ball2_x = ball2[0];
				check_attack_mode_0.ball2_y = ball2[1];
				
				check_attack_mode_0.act_displacement_cpu[2] = 112;
				check_attack_mode_0.angle_ofRotation[2]     = -250;
				// call function
				check_attack_mode(&check_attack_mode_0);
			}
			break;
        case RST_CALCULATION_DEFENSE:
            {
                // calculation forecast direction
                f_d.ball1_x = ball1[0];
                f_d.ball1_y = ball1[1];
                f_d.ball2_x = ball2[0];
                f_d.ball2_y = ball2[1];
                forecast_direction(&f_d);
                // calculation pos dummies opponent
				// maximum displacement of individual axes
				c_ppd.max_disp[0] = 1000;
				c_ppd.max_disp[0] = 1850;
				c_ppd.max_disp[0] = 650;
				c_ppd.max_disp[0] = 955;
				// minimum displacement of individual axes
				c_ppd.min_disp[0] = -1000;
				c_ppd.min_disp[0] = -1850;
				c_ppd.min_disp[0] = -650;
				c_ppd.min_disp[0] = -955;
                for(i_ppd = 0; i_ppd < (int)(sizeof(optical_sensor)/sizeof(optical_sensor[0])); i_ppd++){
                    c_ppd.displacement[i_ppd] = optical_sensor[i_ppd];
                }

                calculation_posDummies(&c_ppd);
                // calculation crossing ball
                for(i_ccd = 0; i_ccd < (int)(sizeof(ball1)/sizeof(ball1[0])); i_ccd++){
                    c_cb[i_ccd].ball1_x = ball1[0];
                    c_cb[i_ccd].ball1_y = ball1[1];
                    c_cb[i_ccd].ball2_x = ball2[0];
                    c_cb[i_ccd].ball2_y = ball2[1];
                    c_cb[i_ccd].first_reflection_x  = f_d.first_reflectionX;
                    c_cb[i_ccd].first_reflection_y  = f_d.first_reflectionY;
                    c_cb[i_ccd].second_reflection_x = f_d.second_reflectionX;
                    c_cb[i_ccd].second_reflection_y = f_d.second_reflectionY;
                    c_cb[i_ccd].tilted   = f_d.tilted;
                    c_cb[i_ccd].time_B2B = time_B2B;
                    
                    if(i_ccd == 0){
                        for(i_ccdCPU = 0; i_ccdCPU < (int)(sizeof(x_posOfCPU)/sizeof(x_posOfCPU[0])); i_ccdCPU++){
                            c_cb[i_ccd].x_positions[i_ccdCPU] = x_posOfCPU[i_ccdCPU];
                        }
                    }else if(i_ccd == 1){
                        for(i_ccdHUM = 0; i_ccdHUM < (int)(sizeof(x_posOfHUM)/sizeof(x_posOfHUM[0])); i_ccdHUM++){
                            c_cb[i_ccd].x_positions[i_ccdHUM] = x_posOfHUM[i_ccdHUM];
                        }
                    }              
                    calculation_crossingBall(&c_cb[i_ccd]);
                }
                // calculation displacement
                c_doa.tilted             = f_d.tilted;
                specific_directionOfBall = (UDINT) strcpy(c_doa.specific_direction,f_d.specific_direction);
                for(i_cdoa1 = 0; i_cdoa1 < (int)(sizeof(c_cb[1].count_axesIntersection)/sizeof(c_cb[1].count_axesIntersection[0])); i_cdoa1++){
                    c_doa.count_axesIntersectionHUM[i_cdoa1] = c_cb[1].count_axesIntersection[i_cdoa1];
                }
                for(i_cdoa2 = 0; i_cdoa2 < (int)(sizeof(c_cb[0].act_posOfAxesY)/sizeof(c_cb[0].act_posOfAxesY[0])); i_cdoa2++){
                    c_doa.act_posOfAxesCPU_Y[i_cdoa2]    = c_cb[0].act_posOfAxesY[i_cdoa2];
                    c_doa.time_axisIntersection[i_cdoa2] = c_cb[0].time_axisIntersection[i_cdoa2];
                    c_doa.act_displacementCPU[i_cdoa2]   = 0; // actual displacement
                    c_doa.reversed_HUM[i_cdoa2]          = reflex_sensor[i_cdoa2];
                }
                c_doa.act_posOfAxesHUM_Y[0] = c_cb[1].act_posOfAxesY[3];
                c_doa.act_posOfAxesHUM_Y[1] = c_cb[1].act_posOfAxesY[2];
                c_doa.act_posOfAxesHUM_Y[2] = c_cb[1].act_posOfAxesY[1];
                c_doa.act_posOfAxesHUM_Y[3] = c_cb[1].act_posOfAxesY[0];
                for(i_cdoa3 = 0; i_cdoa3 < (int)(sizeof(c_ppd.actual_positionsOfDummies)/sizeof(c_ppd.actual_positionsOfDummies[0])); i_cdoa3++){
                    c_doa.act_posOfDummiesH[i_cdoa3] = c_ppd.actual_positionsOfDummies[i_cdoa3];
                }
                c_doa.x_posOfBall[0] = ball1[0];
                c_doa.x_posOfBall[1] = ball2[0];
                calculation_displacementOfAxes(&c_doa);
				
				for(i_def = 0; i_def <= max_numberOfFormation - 1; i_def++){
					if(!isnan(c_doa.velocity[i_def])){
						axes_control_0[i_def].linear_param.acceleration = c_doa.acceleration[i_def];
						axes_control_0[i_def].linear_param.deceleration = c_doa.deceleration[i_def];
						axes_control_0[i_def].linear_param.velocity     = c_doa.velocity[i_def];
						axes_control_0[i_def].linear_param.displacement = c_doa.displacement[i_def];
					}
				}
				
				/*
				if(ESTOP == 0){
					SOCCER_TABLE_STEP = RST_SAFETY;
				}else{
					c_dp = 0;
					
					if(c_dp == 0){
						SOCCER_TABLE_STEP = RST_MOVE_INTO_DEFENSE_POS1;
					}
				}
				*/
            }
            break;
		case RST_MOVE_INTO_DEFENSE_POS1:
			{
				for(i_dp1 = 0; i_dp1 <= max_numberOfFormation - 1; i_dp1++){
					axes_control_0[i_dp1].start_move = 1;
				}
				
				if(ESTOP == 0){
					SOCCER_TABLE_STEP = RST_SAFETY;
				}else{
					SOCCER_TABLE_STEP = RST_MOVE_INTO_DEFENSE_POS2;
				}
			}
			break;
		case RST_MOVE_INTO_DEFENSE_POS2:
			{
				for(i_dp2 = 0; i_dp2 <= max_numberOfFormation - 1; i_dp2++){
					if(axes_control_0[i_dp2].successfully == 1){
						axes_control_0[i_dp2].start_move = 0;
						c_dp++;
					}
				}
				
				if(ESTOP == 0){
					SOCCER_TABLE_STEP = RST_SAFETY;
				}else{
					if(c_dp == max_numberOfFormation){
						SOCCER_TABLE_STEP = RST_INITIALIZATION_4;
					}
				}
			}
		case RST_SAFETY:
			{
			}
			break;
		case RST_AFTER_SAFETY:
			{

			}
			break;
    }// end switch
    
    /************************** call function & function blocks **************************/
    // AlarmX
    MpAlarmXCore(&mp_alarmX.mp_core);
    MpAlarmXListUI(&mp_alarmX.mp_listUI);
    MpAlarmXHistory(&mp_alarmX.mp_history);
    MpAlarmXHistoryUI(&mp_alarmX.mp_historyUI);
    // Active AxisBasic & AxisCyclicSet -> through the individual functions
    start_axesBasic(max_numberOfFormation,&mp_Axis.mp_axisLinear,&mp_Axis.mp_axisRotary);
    start_axesCyclic(max_numberOfFormation,&mp_Axis.mp_cyclicSetLinear,&mp_Axis.mp_cyclicSetRotary);
	
	// control temperature
	//control_temperature(&c_temp);
	if(SOCCER_TABLE_STEP >= 3){
		axes_control(&axes_control_0[0]);
	}
    
}// end _CYCLIC





