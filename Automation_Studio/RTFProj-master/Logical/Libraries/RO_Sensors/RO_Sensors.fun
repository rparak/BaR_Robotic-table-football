
FUNCTION_BLOCK DetectionPositionAxis
	VAR_INPUT
		ActPosSens : ARRAY[0..3] OF INT; (*Input value from sensors [SU].*)
		ErrorOptSens : ARRAY[0..3] OF BOOL; (*Error status of optical sensors.*)
		ReflexSensStatus : ARRAY[0..3] OF BOOL; (*Stauts of reflex sensors.*)
	END_VAR
	VAR_OUTPUT
		ActPosHumFig : ARRAY[0..10] OF INT; (*Actual position of every figure of EACH AXIS (displacement of actual position of human axis).*)
		ActPosHumAxis : ARRAY[0..3] OF INT; (*Actual computed value of EACH AXIS with CORRECTIONS.*)
	END_VAR
	VAR
		ActPosHumBasic : ARRAY[0..3] OF INT; (*Value of actual computed value of position of EACH AXIS without CORRECTIONS.*)
		CorrectionPos : Struct_CorrectionFun;
	END_VAR
	VAR_OUTPUT
		ExternalReflexSensStatus : ARRAY[0..3] OF BOOL; (*Status of reflex sensor, which determines two rotation positions.*)
	END_VAR
	VAR
		InternalPos : Stuct_OptSensInternal; (*Internal position determine a position one step before an actual state of actual human (figure) axis.*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK DetectionRotation
	VAR_INPUT
		ErrorReflSensRS : ARRAY[0..3] OF BOOL;
		ReflexSensStatusRS : ARRAY[0..3] OF BOOL;
	END_VAR
	VAR_OUTPUT
		ExternalReflexSensStatusRS : ARRAY[0..3] OF BOOL;
		ActReflRotRS : ARRAY[0..3] OF BOOL;
	END_VAR
	VAR
		InternalRot : Stuct_RexlSensInternal;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK DetPos_Figure
	VAR_INPUT
		ActPosHumAxisDP : ARRAY[0..3] OF INT;
	END_VAR
	VAR_OUTPUT
		ActPosHumFigDP : ARRAY[0..10] OF INT;
	END_VAR
	VAR
		InternalPosFig : Struct_OptSensFigInternal;
	END_VAR
END_FUNCTION_BLOCK
