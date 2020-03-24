
FUNCTION_BLOCK Light
	VAR_INPUT
		Enable : BOOL;
		DO9322 : DO9322_type;
		PowerOn : BOOL;
		DutyCycle : USINT; (*Power of Light in % [0-100]*)
		Blinking : Blink_type;
	END_VAR
	VAR_OUTPUT
		Active : BOOL;
		Error : BOOL;
		Status : UINT;
		isPWMEnabled : BOOL;
		isPowerOn : BOOL;
	END_VAR
	VAR
		internal : internal_type;
	END_VAR
END_FUNCTION_BLOCK
