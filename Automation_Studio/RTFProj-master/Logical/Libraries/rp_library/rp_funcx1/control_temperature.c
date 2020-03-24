
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif

void control_temperature(struct control_temperature* c_t)
{
	USINT i;
	USINT MAX_TEMPERATURE_ROTARY = 100, MAX_TEMPERATURE_LINEAR = 100;
	
	for(i = 0; i < (int)(sizeof(c_t->temperature_rotary)/sizeof(c_t->temperature_rotary[0])); i++){
		if(c_t->temperature_rotary[i] >= MAX_TEMPERATURE_ROTARY){
			c_t->high_temp_rotary[i] = 1;
		}else{
			c_t->high_temp_rotary[i] = 0;
		}
		
		if(c_t->temperature_linear[i] >= MAX_TEMPERATURE_LINEAR){
			c_t->high_temp_linear[i] 	 = 1;
			c_t->start_cooling_linear[i] = 1;
		}else{
			c_t->high_temp_linear[i] 	 = 0;
			c_t->start_cooling_linear[i] = 0;
		}
	}
}
