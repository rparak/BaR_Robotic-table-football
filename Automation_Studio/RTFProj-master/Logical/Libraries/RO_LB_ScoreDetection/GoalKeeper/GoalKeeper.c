#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif


void GoalKeeper(struct GoalKeeper *inst){
	
	if (inst->enable){
		if (!inst->Internal.init){
			inst->Internal.DisableTimer1.PT = inst->Internal.DisableTimer2.PT = 100;
			inst->Internal.init = 1;
		}
	
	
		if (!inst->DI9371.ModuleOk)
			inst->status = ERR_DI_NOTFOUND;
		else{
			inst->status = ERR_OK;
	
			TON_10ms(&inst->Internal.DisableTimer1);
		
			if ((inst->Internal.DisableTimer1.IN == 1) && (inst->Internal.DisableTimer1.Q))
				inst->Internal.DisableTimer1.IN = 0;
			else if ((!inst->DI9371.DigitalInput_1) && (!inst->isGoal1) && (!inst->Internal.DisableTimer1.IN)) {
				inst->isGoal1 = 1;
				inst->Internal.DisableTimer1.IN = 1;
			}			
			else inst->isGoal1 = 0;
		
			TON_10ms(&inst->Internal.DisableTimer2);
		
			if ((inst->Internal.DisableTimer2.IN == 1) && (inst->Internal.DisableTimer2.Q))
				inst->Internal.DisableTimer2.IN = 0;
			else if ((!inst->DI9371.DigitalInput_2) && (!inst->isGoal2) && (!inst->Internal.DisableTimer2.IN)) {
				inst->isGoal2 = 1;
				inst->Internal.DisableTimer2.IN = 1;
			}			
			else inst->isGoal2 = 0;
		}
	}
	else
		inst->status = ERR_FUB_ENABLE_FALSE;
}
