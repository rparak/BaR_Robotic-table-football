
FUNCTION_BLOCK FBCamera
	VAR_INPUT
		Enable : BOOL;
		InSight : InSight_type;
		MappView : MappView_type;
		ErrorReset : BOOL;
		Search : BOOL;
	END_VAR
	VAR_OUTPUT
		Active : BOOL;
		Error : BOOL;
		Status : UINT;
		isCameraReady : BOOL;
		isSearching : BOOL;
		isBallFound : BOOL;
		Results : Results_type;
	END_VAR
	VAR
		Internal : Internal_type;
	END_VAR
END_FUNCTION_BLOCK
