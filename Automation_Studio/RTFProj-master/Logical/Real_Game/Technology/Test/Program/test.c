/*********************************************************************************************
* B&R Automation - Perfection in Automation (https://www.br-automation.com)
    ******************************************************************************************
    * Program 	    : Master's Thesis - Soccer Table (Table Football - real game)
    * Author  	    : Roman Parak
    * Created 	    : date ... 
	* University    : Brno University of Technology(BUT)
	* Faculty       : Faculty of Mechanical Engineering(FME)
	* Study Program : Applied Computer Science and Control
	* Institute     : Institute of Automation and Computer Science
**********************************************************************************************
* Implementation OF PROGRAM Test(Real_Game/Technology/Test/Program/test.h)
**********************************************************************************************/

/*************************** LIBRARIES *********************************/
#include <bur/plc.h>
#include <bur/plctypes.h>
#include <stdio.h>
#include <math.h>

#include "rp_funcx1.h"
#include "Structures/test_str.h"
#include "Functions/test_fce.h"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

/*************************** DEFINITIONS *******************************/
#define EACH_FORMATION 1;

/************************ LOCAL VARIABLES ******************************/
// struct - MpAlarmX
_LOCAL MpAlarmXListUIConnectType AlarmListUI_ConnectType;
_LOCAL MpAlarmXHistoryUIConnectType AlarmHistoryUI_ConnectType;
// udint
_LOCAL UDINT alarm_device_address;
// bool
_LOCAL BOOL start;
_LOCAL BOOL stop;
// usint
_LOCAL USINT max_numberOfFormation;
_LOCAL USINT i_axisNum;
// lreal
_LOCAL LREAL temp_lin;
_LOCAL LREAL temp_rot;
_LOCAL LREAL define_posRotary;
_LOCAL LREAL angle_ofRotation;
// state machine
_LOCAL rp_MainSteps soccer_step;

/**********************************************************************************************************/
/********************************************** INIT PROGRAM **********************************************/
/**********************************************************************************************************/
void _INIT ProgramInit(void)
{
    /*********************************** Declaration variables **********************************/
    // generally
    max_numberOfFormation = EACH_FORMATION;
    
    // axis type -> MAPP -> Name Mapp axes for testing
    // linear
    //gLinkAxes_linear[0] = gk_mappAxisL;
    /*
    gLinkAxes_linear[1] = df_mappAxisL;
    gLinkAxes_linear[2] = md_mappAxisL;
    gLinkAxes_linear[3] = fw_mappAxisL;
    */
    // rotary
    //gLinkAxes_rotary[0] = gk_mappAxisR;
   	/*
    gLinkAxes_rotary[1] = df_mappAxisR;
    gLinkAxes_rotary[2] = md_mappAxisR;
    gLinkAxes_rotary[3] = fw_mappAxisR;
    */
    /************************************ Control of AlarmX ************************************/
	
    // adjustment device name
    alarm_device_address = (UDINT) strcpy(mp_alarmX.deviceName_no1_exp,"EXPORT_HISTORY");
    // MpAlarmX Core
    mp_alarmX.mp_core.MpLink         = &gAlarmXCore;
    mp_alarmX.mp_core.Enable         = 1;
    // MpAlarmX ListUI
    mp_alarmX.mp_listUI.MpLink       = &gAlarmXCore;
    mp_alarmX.mp_listUI.Enable       = 1;
    mp_alarmX.mp_listUI.UIConnect    = &AlarmListUI_ConnectType;
    // MpAlarmX History
    mp_alarmX.mp_history.MpLink      = &gAlarmXHistory;
    mp_alarmX.mp_history.Enable      = 1;
    mp_alarmX.mp_history.DeviceName  = &mp_alarmX.deviceName_no1_exp;
    // MpAlarmX HistoryUI
    mp_alarmX.mp_historyUI.MpLink    = &gAlarmXHistory;
    mp_alarmX.mp_historyUI.Enable    = 1;
    mp_alarmX.mp_historyUI.UIConnect = &AlarmHistoryUI_ConnectType;
    
	
    /************************************* Control of Axes **************************************/
	
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
		// initialization parameters -> linear
		mp_Axis.param_axisLinear[i_axisNum].Home.Mode 	 		 	     = mpAXIS_HOME_MODE_BLOCK_TORQUE;
		mp_Axis.param_axisLinear[i_axisNum].Home.Position 		  	     = 900;
		mp_Axis.param_axisLinear[i_axisNum].Home.StartVelocity   		 = 350;
		mp_Axis.param_axisLinear[i_axisNum].Home.HomingVelocity  		 = 450;
		mp_Axis.param_axisLinear[i_axisNum].Home.Acceleration    		 = 350;
		mp_Axis.param_axisLinear[i_axisNum].Home.StartDirection  		 = mpAXIS_HOME_DIR_POSITIVE;
		mp_Axis.param_axisLinear[i_axisNum].Home.HomingDirection 		 = mpAXIS_HOME_DIR_NEGATIVE;
		mp_Axis.param_axisLinear[i_axisNum].Home.TorqueLimit	 		 = 0.05;
		mp_Axis.param_axisLinear[i_axisNum].Home.PositionErrorStopLimit	 = 900;
        // linear cyclic set
        mp_Axis.mp_cyclicSetLinear[i_axisNum].Enable     = 1;
        mp_Axis.mp_cyclicSetLinear[i_axisNum].MpLink     = &gLinkAxes_linear[i_axisNum];
        mp_Axis.mp_cyclicSetLinear[i_axisNum].Parameters = &mp_Axis.param_cyclicSetLinear[i_axisNum];
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
		// config
		mp_Axis.mp_configAxisRotary[i_axisNum].Enable 		 = 1;
		mp_Axis.mp_configAxisRotary[i_axisNum].MpLink 		 = &gLinkAxes_rotary[i_axisNum];
		mp_Axis.mp_configAxisRotary[i_axisNum].Configuration = &mp_Axis.param_configAxisRotary[i_axisNum];
		// temperature - linear
		mp_Axis.param_axisLinear[i_axisNum].CyclicRead.MotorTempMode = mpAXIS_READ_POLLING_1s;
		// temperature - rotary
		mp_Axis.param_axisRotary[i_axisNum].CyclicRead.MotorTempMode = mpAXIS_READ_POLLING_1s;
    }
	// initializatiom temp
	temp_lin = 0;
	temp_rot = 0;
	define_posRotary = 118520697;
	angle_ofRotation = 0;
	// initialization state machine
	soccer_step = STEP_INITIALIZATION;
}

/**********************************************************************************************************/
/********************************************** MAIN PROGRAM **********************************************/
/**********************************************************************************************************/
void _CYCLIC ProgramCyclic(void)
{    
	// initializatiom temp
	temp_lin = mp_Axis.mp_axisLinear[0].Info.CyclicRead.MotorTemperature.Value;
	temp_rot = mp_Axis.mp_axisRotary[0].Info.CyclicRead.MotorTemperature.Value;
	
	switch(soccer_step)
	{
		case STEP_INITIALIZATION:
			{
				if(mp_Axis.mp_axisLinear[0].Active == 1 && mp_Axis.mp_axisRotary[0].Active == 1){
					angle_ofRotation = get_rotationalPostition(mp_Axis.mp_axisRotary[0].Position,define_posRotary);
				
					if(labs(angle_ofRotation) <= 3600){
						mp_Axis.param_axisRotary[0].Home.Position = angle_ofRotation;
						soccer_step = STEP_INITIALIZATION0;
					}
				}
			}
			break;
		case STEP_INITIALIZATION0:
			{
				if(mp_Axis.mp_axisLinear[0].Error == 1 && mp_Axis.mp_axisRotary[0].Error == 0){
					soccer_step = STEP_ERROR1;
				}else if(mp_Axis.mp_axisLinear[0].StatusID < 0 || mp_Axis.mp_axisRotary[0].StatusID < 0){
					soccer_step = STEP_ERROR2;
				}else {
					if(mp_Axis.mp_axisLinear[0].IsHomed == 1 && mp_Axis.mp_axisRotary[0].IsHomed == 1){
						soccer_step = STEP_RUN7;
					}else{
						soccer_step = STEP_INITIALIZATION1;
					}
				}
			}
			break;
		case STEP_INITIALIZATION1:
			{
				if(start == 1){
					mp_Axis.mp_axisLinear[0].Power = 1;
					mp_Axis.mp_axisRotary[0].Power = 1;
						
					if(mp_alarmX.mp_core.ActiveAlarms == 1){
						soccer_step = STEP_ERROR1;
					}else if(stop == 1){
						soccer_step = STEP_STOP1;
					}else{
						if(mp_Axis.mp_axisLinear[0].PowerOn == 1 && mp_Axis.mp_axisRotary[0].PowerOn == 1){
							soccer_step = STEP_INITIALIZATION2;
						}
					}
				}
			}
			break;
		case STEP_INITIALIZATION2:
			{
				mp_Axis.mp_axisLinear[0].Update = 1;
				mp_Axis.mp_axisRotary[0].Update = 1;
				
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{	
					if(mp_Axis.mp_axisLinear[0].UpdateDone == 1 && mp_Axis.mp_axisRotary[0].UpdateDone == 1){
						mp_Axis.mp_axisLinear[0].Update = 0;
						mp_Axis.mp_axisRotary[0].Update = 0;
						soccer_step = STEP_INITIALIZATION3;
					}
				}
			}
			break;
		case STEP_INITIALIZATION3:
			{
				mp_Axis.mp_axisRotary[0].Home = 1;
				
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_axisRotary[0].IsHomed == 1){
						mp_Axis.mp_axisRotary[0].Home = 0;
						soccer_step = STEP_INITIALIZATION4;
					}
				}
			}
			break;
		case STEP_INITIALIZATION4:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 2000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 2000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 1000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_INITIALIZATION5;
						}
					}
				}
			}
			break;
		case STEP_INITIALIZATION5:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_INITIALIZATION6;
						}
					}
				}
			}
			break;
		case STEP_INITIALIZATION6:
			{
				mp_Axis.mp_axisLinear[0].Home = 1;
				
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_axisLinear[0].IsHomed == 1){
						mp_Axis.mp_axisLinear[0].Home = 0;
						soccer_step = STEP_START;
					}
				}
			}
			break;
		case STEP_START:
			{
				mp_Axis.param_cyclicSetLinear[0].Acceleration = 400000;
				mp_Axis.param_cyclicSetLinear[0].Deceleration = 400000;
				mp_Axis.param_cyclicSetLinear[0].PositionModeMaxVelocity = 30000;
				mp_Axis.mp_cyclicSetLinear[0].Velocity = 19000;
				mp_Axis.mp_cyclicSetLinear[0].Position = 0;
				
				mp_Axis.mp_cyclicSetLinear[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetLinear[0].Update = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN1;
						}
					}
				}
			}
			break;
		case STEP_RUN1:
			{
				mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN2;
						}
					}
				}
			}
			break;
		case STEP_RUN2:
			{					
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 125000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 125000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 10000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = -800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN3;
						}
					}
				}
			}
			break;
		case STEP_RUN3:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN4;
						}
					}
				}
			}
			break;
		case STEP_RUN4:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 125000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 125000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 10000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN5;
						}
					}
				}
			}
			break;
		case STEP_RUN5:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN6;
						}
					}
				}
			}
			break;
		case STEP_RUN6:
			{
				/*======================= END HOME =======================*/
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 125000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 125000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 10000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN7;
						}
					}
				}
			}
			break;
		case STEP_RUN7:
			{
				/*======================= START CYCLE =======================*/
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN8;
						}
					}
				}
			}
			break;
		case STEP_RUN8:
			{
				// 250000,20000
				mp_Axis.param_cyclicSetLinear[0].Acceleration = 125000;
				mp_Axis.param_cyclicSetLinear[0].Deceleration = 125000;
				mp_Axis.param_cyclicSetLinear[0].PositionModeMaxVelocity = 30000;
				mp_Axis.mp_cyclicSetLinear[0].Velocity = 10000;
				mp_Axis.mp_cyclicSetLinear[0].Position = -800;
				
				mp_Axis.mp_cyclicSetLinear[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetLinear[0].Update = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN9;
						}
					}
				}
			}
			break;
		case STEP_RUN9:
			{
				mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN10; // STEP_RUN24
						}
					}
				}
			}
			break;
		case STEP_RUN10:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 31250; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 31250;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 5000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = -800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN11;
						}
					}
				}
			}
			break;
		case STEP_RUN11:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN12;
						}
					}
				}
			}
			break;
		case STEP_RUN12:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 31250; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 31250;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 5000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN13;
						}
					}
				}
			}
			break;
		case STEP_RUN13:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN14;
						}
					}
				}
			}
			break;
		case STEP_RUN14:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 31250; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 31250;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 5000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN15;
						}
					}
				}
			}
			break;
		case STEP_RUN15:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN16; // STEP_RUN24
						}
					}
				}
			}
			break;
		case STEP_RUN16:
			{
				mp_Axis.param_cyclicSetLinear[0].Acceleration = 600;
				mp_Axis.param_cyclicSetLinear[0].Deceleration = 600;
				mp_Axis.param_cyclicSetLinear[0].PositionModeMaxVelocity = 30000;
				mp_Axis.mp_cyclicSetLinear[0].Velocity = 2500;
				mp_Axis.mp_cyclicSetLinear[0].Position = 0;
				
				mp_Axis.mp_cyclicSetLinear[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetLinear[0].Update = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN17;
						}
					}
				}
			}
			break;
		case STEP_RUN17:
			{
				mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN18;
						}
					}
				}
			}
			break;
		case STEP_RUN18:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3900000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3900000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 84000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = -800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN19;
						}
					}
				}
			}
			break;
		case STEP_RUN19:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN20;
						}
					}
				}
			}
			break;
		case STEP_RUN20:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3900000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3900000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 80000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN21;
						}
					}
				}
			}
			break;
		case STEP_RUN21:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN22;
						}
					}
				}
			}
			break;
		case STEP_RUN22:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3900000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3900000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 80000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN23;
						}
					}
				}
			}
			break;
		case STEP_RUN23:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN24;
						}
					}
				}
			}
			break;
		case STEP_RUN24:
			{
				// 250000, 20000
				mp_Axis.param_cyclicSetLinear[0].Acceleration = 281250;
				mp_Axis.param_cyclicSetLinear[0].Deceleration = 281250;
				mp_Axis.param_cyclicSetLinear[0].PositionModeMaxVelocity = 30000;
				mp_Axis.mp_cyclicSetLinear[0].Velocity = 15000;
				mp_Axis.mp_cyclicSetLinear[0].Position = 800;
				
				mp_Axis.mp_cyclicSetLinear[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetLinear[0].Update = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN25;
						}
					}
				}
			}
			break;
		case STEP_RUN25:
			{
				mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN26; // STEP_RUN8
						}
					}
				}
			}
			break;
		case STEP_RUN26:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3125000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3125000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 50000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = -800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN27;
						}
					}
				}
			}
			break;
		case STEP_RUN27:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN28;
						}
					}
				}
			}
			break;
		case STEP_RUN28:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 11300; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 11300;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 3000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN29;
						}
					}
				}
			}
			break;
		case STEP_RUN29:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN30;
						}
					}
				}
			}
			break;
		case STEP_RUN30:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 1000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 1000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 1000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN31;
						}
					}
				}
			}
			break;
		case STEP_RUN31:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN32; //STEP_RUN8
						}
					}
				}
			}
			break;
		case STEP_RUN32:
			{
				mp_Axis.param_cyclicSetLinear[0].Acceleration = 440000;
				mp_Axis.param_cyclicSetLinear[0].Deceleration = 440000;
				mp_Axis.param_cyclicSetLinear[0].PositionModeMaxVelocity = 30000;
				mp_Axis.mp_cyclicSetLinear[0].Velocity = 20000;
				mp_Axis.mp_cyclicSetLinear[0].Position = 0;
				
				mp_Axis.mp_cyclicSetLinear[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetLinear[0].Update = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN33;
						}
					}
				}
			}
			break;
		case STEP_RUN33:
			{
				mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetLinear[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetLinear[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetLinear[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetLinear[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN34;
						}
					}
				}
			}
			break;
		case STEP_RUN34:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3900000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3900000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 84000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = -800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN35;
						}
					}
				}
			}
			break;
		case STEP_RUN35:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == -800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN36;
						}
					}
				}
			}
			break;
		case STEP_RUN36:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 3900000; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 3900000;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 84000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 800;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN37;
						}
					}
				}
			}
			break;
		case STEP_RUN37:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 800){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN38;
						}
					}
				}
			}
			break;
		case STEP_RUN38:
			{
				mp_Axis.param_cyclicSetRotary[0].Acceleration = 61300; 
				mp_Axis.param_cyclicSetRotary[0].Deceleration = 61300;
				mp_Axis.param_cyclicSetRotary[0].PositionModeMaxVelocity = 85000;
				mp_Axis.mp_cyclicSetRotary[0].Velocity 	 = 7000;
				mp_Axis.mp_cyclicSetRotary[0].Position	 = 0;
				
				mp_Axis.mp_cyclicSetRotary[0].Update = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].UpdateDone == 1){
						mp_Axis.mp_cyclicSetRotary[0].Update = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN39;
						}
					}
				}
			}
			break;
		case STEP_RUN39:
			{
				mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 1;
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
					if(mp_Axis.mp_cyclicSetRotary[0].Info.SlavePosition == 0){
						mp_Axis.mp_cyclicSetRotary[0].CyclicPosition = 0;
						if(mp_Axis.mp_cyclicSetRotary[0].CommandBusy == 0 && mp_Axis.mp_cyclicSetRotary[0].CyclicSetActive == 0){
							soccer_step = STEP_RUN8;
						}
					}
				}
			}
			break;
		case STEP_RUN40:
			{
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 1){
					soccer_step = STEP_STOP1;
				}else{
				}
			}
			break;
		case STEP_STOP1:
			{
				start = 0;
				mp_Axis.mp_axisLinear[0].Stop = 1;
				mp_Axis.mp_axisRotary[0].Stop = 1;
				
				if(mp_alarmX.mp_core.ActiveAlarms == 1){
					soccer_step = STEP_ERROR1;
				}else if(stop == 0){
					mp_Axis.mp_axisLinear[0].Stop = 0;
					mp_Axis.mp_axisRotary[0].Stop = 0;
					soccer_step = STEP_INITIALIZATION0;
				}
			}
			break;
		case STEP_ERROR1:
			{
				start = 0;
				stop  = 0;
				mp_Axis.mp_axisLinear[0].Stop = 0;
				mp_Axis.mp_axisRotary[0].Stop = 0;
				mp_Axis.mp_axisLinear[0].Power = 0;
				mp_Axis.mp_axisRotary[0].Power = 0;
				
				mp_Axis.mp_axisLinear[0].ErrorReset = 1;
				mp_Axis.mp_axisRotary[0].ErrorReset = 1;
				
				if(mp_Axis.mp_axisLinear[0].Error == 0 && mp_Axis.mp_axisRotary[0].Error == 0){
					mp_Axis.mp_axisLinear[0].ErrorReset = 0;
					mp_Axis.mp_axisRotary[0].ErrorReset = 0;
					
					soccer_step = STEP_INITIALIZATION0;	
				}
				
			}
			break;
		case STEP_ERROR2:
			{
				mp_Axis.mp_axisLinear[0].ErrorReset = 1;
				mp_Axis.mp_axisRotary[0].ErrorReset = 1;
				
				if(mp_Axis.mp_axisLinear[0].StatusID >= 0 && mp_Axis.mp_axisRotary[0].StatusID >= 0){
					mp_Axis.mp_axisLinear[0].ErrorReset = 0;
					mp_Axis.mp_axisRotary[0].ErrorReset = 0;
					
					soccer_step = STEP_INITIALIZATION0;	
				}
			}
			break;
	}

    /************************** Call function & function blocks **************************/
    // AlarmX
    MpAlarmXCore(&mp_alarmX.mp_core);
    MpAlarmXListUI(&mp_alarmX.mp_listUI);
    MpAlarmXHistory(&mp_alarmX.mp_history);
    MpAlarmXHistoryUI(&mp_alarmX.mp_historyUI);
    // Active AxisBasic & AxisCyclicSet -> through the individual functions
    start_axesBasic(max_numberOfFormation,&mp_Axis.mp_axisLinear,&mp_Axis.mp_axisRotary);
    start_axesCyclic(max_numberOfFormation,&mp_Axis.mp_cyclicSetLinear,&mp_Axis.mp_cyclicSetRotary);

}






