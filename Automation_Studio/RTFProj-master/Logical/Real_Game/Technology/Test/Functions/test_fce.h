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
* Implementation OF PROGRAM Test(Real_Game/Technolog/table_football/Functions/test_mapp_fce.h)
**********************************************************************************************/

/*************************** LIBRARIES *********************************/
#include <bur/plc.h>
#include <bur/plctypes.h>
#include <AsString.h>
#include <standard.h>
#include <AsWStr.h>
#include <stdio.h>
#include <math.h>

#ifdef _DEFAULT_INCLUDES
    #include <AsDefault.h>
#endif

/**********************************************************************************************************/
/************************************** FUNCTIONS & FUNCTIONS BLOCKS **************************************/
/**********************************************************************************************************/
void start_axesBasic(USINT num_ofAxes,struct MpAxisBasic* axis_linear,struct MpAxisBasic* axis_rotary){ 
    int i;
    // Axis Basic
    // function to start the individual axes
    // the cycle is carried out through number of axes
    for(i = 0; i <= num_ofAxes - 1; i++){
        // mapp axis basic
        MpAxisBasic(&axis_linear[i]);
        MpAxisBasic(&axis_rotary[i]);
    }
}

void start_axesCyclic(USINT num_ofAxes,struct MpAxisCyclicSet* cyclic_linear,struct MpAxisCyclicSet* cyclic_rotary){
    int i;
    // Axis Cyclic Set
    // function to start the individual axes
    // the cycle is carried out through number of axes
    for(i = 0; i <= num_ofAxes - 1; i++){
        // mapp axis cyclic set
        MpAxisCyclicSet(&cyclic_linear[i]);
        MpAxisCyclicSet(&cyclic_rotary[i]);
    }
}

struct axesAcopos get_axisParam(int idx_ofIteration){
    // input into the function is number of iteration(in the init part)
    // create auxiliary structures and enumeration type(for state machine)
    struct axesAcopos a;
    typedef enum {aNUM1 = 0, aNUM2, aNUM3, aNUM4}wState_ofAxes;
    wState_ofAxes new_idx; // initialize state machine
    new_idx = idx_ofIteration;
    // gradually into the state machine loading indexes from initialization part
    // and this run the function blocks
    // each state of machine has initialization both engines linear and rotary, on its own axis
    // output of this function is structure, that has two parameters(linear,rotary axis)
    switch(new_idx){
        case aNUM1:
			// Name real axes
			/*
            // goalkeeper
            a.linear = &gkLinearW;
            a.rotary = &gkRotaryW;
            return a;
            break;
        case aNUM2:
            // defender
            a.linear = &dfLinearX;
            a.rotary = &dfRotaryX;
            return a;
            break;
        case aNUM3:
            // midfielder
            a.linear = &mdLinearY;
            a.rotary = &mdRotaryY;
            return a;
            break;
        case aNUM4:
            // forward
            a.linear = &fwLinearZ;
            a.rotary = &fwRotaryZ;
            break;
        */
    }  
}


