
{REDUND_OK} FUNCTION_BLOCK MTBasicsDT1 (*First-order derivative action element.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Gain : REAL; (*Gain factor.*)
		TimeConstant : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsDT1InternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsDT2 (*Second-order derivative action element.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Gain : REAL; (*Gain factor.*)
		TimeConstant1 : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant1 >= 0.*)
		TimeConstant2 : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant2 >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsDT2InternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsIntegrator (*Integrator.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Gain : REAL; (*Gain factor. Valid value range: Gain >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
		OutPresetValue : REAL; (*Preset value for Out output.*)
		SetOut : BOOL; (*Sets Out to OutPresetValue on rising edge.*)
		HoldOut : BOOL; (*Freezes the function block.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsIntegratorInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsLevelController (*Level controller.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Parameter : MTBasicsLevelCtrlParType; (*3-step controller parameters.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
	END_VAR
	VAR
		Internal : MTBasicsLevelCtrlInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsLimiter (*Limiter.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		MinOut : REAL; (*Lower output variable limit. Valid value range: MinOut < MaxOut.*)
		MaxOut : REAL; (*Upper output variable limit. Valid value range: MaxOut > MinOut.*)
		MaxPosSlewRate : REAL; (*Maximum output variable ramp for ramp-up. Unit: [1/s]. Valid value range: MaxPosSlewRate >= 0.*)
		MaxNegSlewRate : REAL; (*Maximum output variable ramp for the ramp-down. Unit: [1/s]. Valid value range: MaxNegSlewRate >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
		OutPresetValue : REAL; (*Preset value for Out output.*)
		SetOut : BOOL; (*Sets Out to OutPresetValue on rising edge.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
	END_VAR
	VAR
		Internal : MTBasicsLimiterInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsOscillationTuning (*Oscillation tuning for PID.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		SetValue : REAL; (*Reference variable (setpoint).*)
		MinOut : REAL; (*Lower manipulated variable limit. Valid value range: MinOut < MaxOut.*)
		MaxOut : REAL; (*Upper manipulated variable limit. Valid value range: MaxOut > MinOut.*)
		Invert : BOOL; (*Inverts the direction of the controller.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		ActValue : REAL; (*Actual measured value.*)
		Start : BOOL; (*Starts the tuning (on positive edge).*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value (manipulated variable). Value range: MinOut <= Out <= MaxOut.*)
		TuningActive : BOOL; (*Tuning is active.*)
		TuningDone : BOOL; (*Tuning completed.*)
		Quality : REAL; (*Quality of the oscillation tuning. Unit: [%]. Value range: 0 (low) ... 100 (high).*)
		PIDParameters : MTPIDParametersType; (*PID parameters.*)
	END_VAR
	VAR
		Internal : MTBasicsOscTuningInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsPFM (*Pulse frequency modulator.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		PulseWidth : REAL; (*Pulse width at the output. Unit: [s]. Valid value range: PulseWidth >= task cycle time.*)
		MinPause : REAL; (*Minimum pause between the pulses at the output. Unit: [s]. Valid value range: MinPause >= task cycle time.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		DutyCycle : REAL; (*Input value.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : BOOL; (*Output value.*)
	END_VAR
	VAR
		Internal : MTBasicsPFMInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsPID (*PID controller.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		PIDParameters : MTPIDParametersType; (*PID parameters.*)
		MinOut : REAL;
		MaxOut : REAL;
		Invert : BOOL;
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		SetValue : REAL; (*Set value (reference variable).*)
		ActValue : REAL; (*Actual value (controlled variable).*)
		IntegrationPartPresetValue : REAL; (*Preset value for the integral component IntegrationPart.*)
		SetIntegrationPart : BOOL; (*A positive edge on SetIntegrationPart sets the integral component IntegrationPart of the PID controller to IntegrationPartPresetValue.*)
		HoldOut : BOOL; (*Freezes the function block.*)
		TrackingValue : REAL; (*Preset value for the integral component IntegrationPart.*)
		EnableTracking : BOOL; (*A positive edge on SetIntegrationPart sets the integral component IntegrationPart of the PID controller to IntegrationPartPresetValue.*)
		HoldIntegration : MTPIDIntegrationEnum; (*PID parameters.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Controller output. Value range: MinOut <= Out <= MaxOut.*)
		ControlError : REAL; (*Control error.*)
		ProportionalPart : REAL; (*Proportional component.*)
		IntegrationPart : REAL; (*Integral component.*)
		DerivativePart : REAL; (*Derivative component.*)
		TrackingActive : BOOL; (*Derivative component.*)
		IntegrationStatus : MTPIDIntegrationEnum; (*Derivative component.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsPIDInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsPT1 (*First-order delay element.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Gain : REAL; (*Gain factor.*)
		TimeConstant : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
		OutPresetValue : REAL; (*Preset value for Out output.*)
		SetOut : BOOL; (*Sets Out to OutPresetValue on rising edge.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsPT1InternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsPT2 (*Second-order delay element.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Gain : REAL; (*Gain.*)
		TimeConstant1 : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant1 >= 0.*)
		TimeConstant2 : REAL; (*Time constant. Unit: [s]. Valid value range: TimeConstant2 >= 0.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		In : REAL; (*Input value.*)
		OutPresetValue : REAL; (*Preset value for Out output.*)
		SetOut : BOOL; (*Sets Out to OutPresetValue on rising edge.*)
	END_VAR
	VAR_OUTPUT
		Busy : BOOL; (*Function block is busy.*)
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value.*)
		SystemReference : {REDUND_UNREPLICABLE} UDINT; (*System reference.*)
	END_VAR
	VAR
		Internal : MTBasicsPT2InternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsPWM (*Pulse width modulator.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Mode : MTBasicsPWMModeEnum; (*Pulse mode.*)
		MinPulseWidth : REAL; (*Minimum duration of the output actuator pulses and pauses. Unit: [s]. Valid value range: MinPulseWidth < Period.*)
		Period : REAL; (*Period for the output actuator pulses. Unit: [s]. Valid value range: Period > task cycle time.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		DutyCycle : REAL; (*Input value. Unit: [%]. Valid value range: 0 <= DutyCycle <= 100.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : BOOL; (*Output value.*)
	END_VAR
	VAR
		Internal : MTBasicsPWMInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} FUNCTION_BLOCK MTBasicsPWMSchedule (*Multiple pulse width modulator.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		Period : REAL; (*Period for the output actuator pulses. Unit: [s]. Permitted range: Period > Task cycle time.*)
		MinPulseWidth : REAL; (*Minimum duration of the pulses. Unit: [s]. Permitted range: Task cycle time <= MinPulseWidth < Period.*)
		MinPause : REAL; (*Minimum duration of the pauses. Unit: [s]. Permitted range: Task cycle time <= MinPause < Period.*)
		Mode : MTBasicsPWMScheduleModeEnum; (*Pulse mode.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		NumberOfInputs : UINT; (*Number of input signals. Permitted range: 0 < NumberOfInputs <= 500.*)
		DutyCycle : {REDUND_UNREPLICABLE} UDINT; (*Address of an array of real with the iput values. Unit of values of the assigned array: [%].*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : {REDUND_UNREPLICABLE} UDINT; (*Address for an array of bool with the output values.*)
	END_VAR
	VAR
		Internal : MTBasicsPWMScheduleInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_OK} FUNCTION_BLOCK MTBasicsStepTuning (*Step tuning for PID.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		SystemSettlingTime : REAL; (*System settling time.*)
		MaxTuningTime : REAL; (*Maximum tuning time*)
		MinActValue : REAL; (*Minimum value of the controlled variable.*)
		MaxActValue : REAL; (*Maximum value of the controlled variable.*)
		Update : BOOL; (*Updates the parameters listed above on a rising edge.*)
		ActValue : REAL; (*Actual measured value.*)
		StepHeight : REAL; (*Height of step to be applied.*)
		Start : BOOL; (*Starts the tuning (on positive edge).*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*Update is done.*)
		Out : REAL; (*Output value (manipulated variable). Value range: MinOut <= Out <= MaxOut.*)
		TuningActive : BOOL; (*Tuning is active.*)
		TuningDone : BOOL; (*Tuning completed.*)
		PIDParameters : MTPIDParametersType; (*PID parameters.*)
		Quality : REAL; (*Quality of the step tuning. Unit: [%]. Value range: 0 (low) ... 100 (high).*)
		TuningState : MTBasicsStepTuningStateEnum; (*Current state of the tuning procedure.*)
	END_VAR
	VAR
		Internal : MTBasicsStepTuningInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_CONTEXT} FUNCTION_BLOCK MTBasicsTimeDelay (*Delay element.*)
	VAR_INPUT
		Enable : BOOL; (*Enables/Disables the function block.*)
		DelayTime : REAL; (*Delay time. Unit: [s]. Valid value range: 0 <= DelayTime <= "10000 · task cycle time".*)
		In : REAL; (*Input value.*)
		InitialValue : REAL; (*Initial value for Out output.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is active.*)
		Error : BOOL; (*Indicates an error.*)
		StatusID : DINT; (*Status information.*)
		Out : REAL; (*Output value.*)
	END_VAR
	VAR
		Internal : MTBasicsTimeDelayInternalType; (*Data for internal use.*)
	END_VAR
END_FUNCTION_BLOCK
