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
* Implementation OF PROGRAM simulation(Simulation/Technology/simulation/Structures/simulation_str.h)
**********************************************************************************************/

/*************************** LIBRARIES *********************************/
#include <bur/plc.h>
#include <bur/plctypes.h>
#include <AsString.h>
#include <AsWStr.h>

#ifdef _DEFAULT_INCLUDES
    #include <AsDefault.h>
#endif

/**********************************************************************************************************/
/************************************** STRUCTURE TYPE ****************************************************/
/**********************************************************************************************************/

/***************************************** sim_mapp.h *****************************************************/
/***************************** ALARM ***********************************/
typedef struct mappAlarmX_STR{	
    // list
    struct MpAlarmXCore   mp_core;
    struct MpAlarmXListUI mp_listUI;
    // history
    struct    MpAlarmXHistory mp_history;
    struct    MpAlarmXHistoryUI mp_historyUI;
    plcstring deviceName_no1_exp[21];
} mappAlarmX_STR;

/***************************** AXIS ************************************/
typedef struct mappAxisBasic_STR{
	// === Linear Axes === //
	// axis basic
	struct MpAxisBasic        mp_axisLinear[4];
	struct MpAxisBasicParType param_axisLinear[4];	
	// cyclic set
	struct MpAxisCyclicSet        mp_cyclicSetLinear[4];
	struct MpAxisCyclicSetParType param_cyclicSetLinear[4];
	// config
	struct MpAxisBasicConfig mp_configAxisLinear[4];
	struct MpAxisBasicConfigType param_configAxisLinear[4];
	// === Rotary Axes === //
	// axis basic
	struct MpAxisBasic        mp_axisRotary[4];
	struct MpAxisBasicParType param_axisRotary[4];	
	// cyclic set
	struct MpAxisCyclicSet        mp_cyclicSetRotary[4];
	struct MpAxisCyclicSetParType param_cyclicSetRotary[4];
	// config
	struct MpAxisBasicConfig mp_configAxisRotary[4];
	struct MpAxisBasicConfigType param_configAxisRotary[4];
} mappAxisBasic_STR;


/***************************** GET AXIS PARAM. ************************************/
typedef struct axesAcopos{ 
    UDINT linear; 
    UDINT rotary; 
}axesAcopos;

/*********************************** sim_forecast_direction.h *********************************************/
/***************************** FORECAST DIR.. ************************************/
typedef struct forecastDirection{
	BOOL direction;
	INT first_reflectX;
	INT first_reflectY;
	INT second_reflectX;
	INT second_reflectY;
	plcstring specific_direction[30];
}forecastDirection;
/***************************** CALC. DIR. OF TILT **********************************/
typedef struct tiltDirection{
	INT first_reflectX;
	INT first_reflectY;
	INT state_ofDirection;
    plcstring specific_direction[10];
}tiltDirection;
/***************************** CALC. NEXT DIR. *************************************/
typedef struct nextDirection{
	INT second_reflectX;
	INT second_reflectY;
}nextDirection;

/**********************************************************************************************************/
/**************************************** GLOBAL VARIABLES ************************************************/
/**********************************************************************************************************/

/***************************************** sim_mapp.h *****************************************************/
// my structures
_GLOBAL mappAlarmX_STR mp_alarmX;
_GLOBAL mappAxisBasic_STR mp_Axis;
_GLOBAL axesAcopos axis_acopos;

// axis type -> ACOPOS
// goalkeeper
_GLOBAL ACP10AXIS_typ gkLinS;
_GLOBAL ACP10AXIS_typ gkRotS;
// defender
_GLOBAL ACP10AXIS_typ dfLinS;
_GLOBAL ACP10AXIS_typ dfRotS;
// midfielder
_GLOBAL ACP10AXIS_typ mdLinS;
_GLOBAL ACP10AXIS_typ mdRotS;
// forward
_GLOBAL ACP10AXIS_typ fwLinS;
_GLOBAL ACP10AXIS_typ fwRotS;
// axis type -> MAPP
_GLOBAL struct MpComIdentType gLinkAxes_rotary[4];
_GLOBAL struct MpComIdentType gLinkAxes_linear[4];

/**********************************************************************************************************/
/************************************** FUNCTIONS & FUNCTIONS BLOCKS **************************************/
/**********************************************************************************************************/
void start_axesBasic(USINT num_ofAxes,struct MpAxisBasic* axis_linear,struct MpAxisBasic* axis_rotary);
void start_axesCyclic(USINT num_ofAxes,struct MpAxisCyclicSet* cyclic_linear,struct MpAxisCyclicSet* cyclic_rotary);
struct axesAcopos get_axisParam(int idx_ofIteration);
