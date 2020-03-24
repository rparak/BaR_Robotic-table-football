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
* Implementation OF PROGRAM Test(Real_Game/Technolog/Test/Structures/test_str.h)
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

// auxiliary structures
typedef struct axesAcopos{ 
    UDINT linear; 
    UDINT rotary; 
}axesAcopos;

/**********************************************************************************************************/
/**************************************** GLOBAL VARIABLES ************************************************/
/**********************************************************************************************************/
// my structures
_GLOBAL mappAlarmX_STR mp_alarmX;
_GLOBAL mappAxisBasic_STR mp_Axis;
_GLOBAL axesAcopos axis_acopos;

// axis type -> ACOPOS
// goalkeeper
_GLOBAL ACP10AXIS_typ gkLinearW;
_GLOBAL ACP10AXIS_typ gkRotaryW;
// defender
/*
_GLOBAL ACP10AXIS_typ dfLinearX;
_GLOBAL ACP10AXIS_typ dfRotaryX;
// midfielder
_GLOBAL ACP10AXIS_typ mdLinearY;
_GLOBAL ACP10AXIS_typ mdRotaryY;
// forward
_GLOBAL ACP10AXIS_typ fwLinearZ;
_GLOBAL ACP10AXIS_typ fwRotaryZ;
*/
// axis type -> MAPP
_GLOBAL struct MpComIdentType gLinkAxes_rotary[4];
_GLOBAL struct MpComIdentType gLinkAxes_linear[4];

/**********************************************************************************************************/
/************************************** FUNCTIONS & FUNCTIONS BLOCKS **************************************/
/**********************************************************************************************************/
void start_axesBasic(USINT num_ofAxes,struct MpAxisBasic* axis_linear,struct MpAxisBasic* axis_rotary);
void start_axesCyclic(USINT num_ofAxes,struct MpAxisCyclicSet* cyclic_linear,struct MpAxisCyclicSet* cyclic_rotary);
struct axesAcopos get_axisParam(int idx_ofIteration);
