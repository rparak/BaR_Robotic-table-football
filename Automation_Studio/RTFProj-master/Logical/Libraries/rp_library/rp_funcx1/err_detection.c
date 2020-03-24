
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif

void err_detection(struct err_detection* e_d)
{
	USINT i, count_err;
	// initialization variables
	count_err = 0;
	// output
	e_d->err_detect = 0;
	
	for(i = 0; i < (int)(sizeof(e_d->rotary_ERR)/sizeof(e_d->rotary_ERR[0])); i++){
		if((e_d->rotary_ERR[i] == 1 || e_d->linear_ERR[i]) == 1){
			count_err = 1;
		}
	}
	
	if(count_err == 0){
		e_d->err_detect = 0;
	}else{
		e_d->err_detect = 1;
	}
}
