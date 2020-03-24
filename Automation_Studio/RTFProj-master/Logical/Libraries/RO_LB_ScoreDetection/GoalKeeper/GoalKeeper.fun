
FUNCTION_BLOCK GoalKeeper
	VAR_INPUT
		enable : BOOL;
		DI9371 : DI9371_type;
	END_VAR
	VAR_OUTPUT
		status : UINT;
		isGoal1 : BOOL;
		isGoal2 : BOOL;
	END_VAR
	VAR
		Internal : InternalG_type;
	END_VAR
END_FUNCTION_BLOCK
