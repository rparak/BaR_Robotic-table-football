
TYPE
	MTPIDParametersType : 	STRUCT 
		Gain : REAL; (*Proportional gain. Valid value range: Gain > 0.*)
		IntegrationTime : REAL; (*Integral time constant for the integral component. Unit: [s]. Valid value range: IntegrationTime >= 0.*)
		DerivativeTime : REAL; (*Differential time constant for the derivative component. Unit: [s]. Valid value range: DerivativeTime >= 0.*)
		FilterTime : REAL; (*Filter time constant for the derivative component. Unit: [s]. Valid value range: FilterTime >= 0.*)
	END_STRUCT;
	MTBodeType : 	STRUCT  (*Bode diagram data.*)
		FrequencyVector : ARRAY[0..160]OF REAL; (*Vector of frequency axis in Hz.*)
		MagnitudeVector : ARRAY[0..160]OF REAL; (*Vector of magnitude axis in dB.*)
		PhaseVector : ARRAY[0..160]OF REAL; (*Vector of phase axis in degrees.*)
		MinFrequency : REAL; (*Used minimum frequency in Hz.*)
		MaxFrequency : REAL; (*Used maximum frequency in Hz.*)
		MinMagnitude : REAL; (*Minimum magnitude within the specified range of frequency in dB.*)
		MaxMagnitude : REAL; (*Maximum magnitude within the specified range of frequency in dB.*)
		MinPhase : REAL; (*Minimum phase within the specified range of frequency in degrees.*)
		MaxPhase : REAL; (*Maximum phase within the specified range of frequency in degrees.*)
	END_STRUCT;
	MTCommType : 	STRUCT  (*Datatype for internal use.*)
		ID : DINT;
		Valid : BOOL;
		Counter : UDINT;
	END_STRUCT;
	MTTransferFcnType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType;
		Numerator : ARRAY[0..5]OF REAL;
		Denominator : ARRAY[0..5]OF REAL;
		SampleTime : REAL;
		CheckID : DINT := -45012;
	END_STRUCT;
	MTFrequencyResponseType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType;
		Frequency : ARRAY[0..160]OF REAL;
		Magnitude : ARRAY[0..160]OF REAL;
		Phase : ARRAY[0..160]OF REAL;
		MinFrequency : REAL;
		MaxFrequency : REAL;
		MinMagnitude : REAL;
		MaxMagnitude : REAL;
		MinPhase : REAL;
		MaxPhase : REAL;
		CheckID : DINT := -20583;
	END_STRUCT;
	MTStateSpaceType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType;
		A : REFERENCE TO LREAL;
		B : REFERENCE TO LREAL;
		C : REFERENCE TO LREAL;
		D : REFERENCE TO LREAL;
		NbStates : USINT;
		NbInputs : USINT;
		NbOutputs : USINT;
		SampleTime : REAL;
		CheckID : DINT := -52417;
	END_STRUCT;
	MTPIDIntegrationEnum : 
		(
		mtINTEGRATION_FREE := 0, (*PID integration part can increase or decrease.*)
		mtHOLD_INTEGRATION_POSITIVE := +1, (*Stops the PID integration part if the control error is positive.*)
		mtHOLD_INTEGRATION_NEGATIVE := -1 (*Stops the PID integration part if the control error is negative.*)
		);
END_TYPE
