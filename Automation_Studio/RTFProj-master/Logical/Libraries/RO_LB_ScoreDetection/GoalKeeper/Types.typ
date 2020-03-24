
TYPE
	DI9371_type : 	STRUCT 
		ModuleOk : BOOL;
		DigitalInput_1 : BOOL;
		DigitalInput_2 : BOOL;
	END_STRUCT;
	InternalG_type : 	STRUCT 
		init : BOOL;
		DisableTimer1 : TON_10ms;
		DisableTimer2 : TON_10ms;
	END_STRUCT;
END_TYPE
