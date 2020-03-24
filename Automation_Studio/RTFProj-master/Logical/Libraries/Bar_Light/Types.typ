
TYPE
	MainControlBarLight_enum : 
		(
		INIT_BARLIGHT := 0,
		DISABLED_BARLIGHT := 1,
		ENABLED_BARLIGHT := 2,
		ERROR_BARLIGHT := 100
		);
	DO9322_type : 	STRUCT 
		ModuleOK : BOOL;
		DigitalOutput : BOOL;
	END_STRUCT;
	PWM_type : 	STRUCT 
		PWMEnabled : BOOL;
		PWM : MTBasicsPWM;
	END_STRUCT;
	internal_type : 	STRUCT 
		init : BOOL;
		TaskClass : TaskClass_type;
		PWM : PWM_type;
		BlinkTime : UINT;
		MainControlBarLight : MainControlBarLight_enum;
		BlinkingCounter : UINT;
		BlinkCounter : UINT;
	END_STRUCT;
	Blink_type : 	STRUCT 
		StartBlinking : BOOL;
		BlinkPeriod_ms : UINT;
		BlinkingTime_ms : UINT;
	END_STRUCT;
	TaskClass_type : 	STRUCT 
		CyclicTime : UINT;
		RTInfo_0 : RTInfo;
	END_STRUCT;
END_TYPE
