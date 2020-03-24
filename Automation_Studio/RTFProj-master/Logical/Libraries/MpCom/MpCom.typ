
TYPE
	MpComFacilitiesEnum : 
		(
		mpCOM_FAC_UNDEFINED := -1, (*No active error*)
		mpCOM_FAC_ARCORE := 0, (*Facility for legacy error code from AR libraries in UINT format*)
		mpCOM_FAC_SAFETY1 := 1, (*Safety facility*)
		mpCOM_FAC_SAFETY2 := 2, (*Safety facility*)
		mpCOM_FAC_GMC1 := 96, (*GMC facility*)
		mpCOM_FAC_GMC2 := 97, (*GMC facility*)
		mpCOM_FAC_GMCAXIS := 98, (*GMC Axis facility*)
		mpCOM_FAC_GMCAXESGROUP := 99, (*GMC Axes group facility*)
		mpCOM_FAC_GMCARNCGROUP := 103, (*GMC Arnc group facility*)
		mpCOM_FAC_TRF := 105, (*TRF facility*)
		mpCOM_FAC_MAPP_INTERNAL := 144, (*mapp Internal Facility*)
		mpCOM_FAC_MAPP_CORE := 145, (*mapp Core Facility*)
		mpCOM_FAC_MAPP_INFRASTRUCTURE := 146, (*mapp Infrastructure Facility*)
		mpCOM_FAC_MAPP_MECHATRONIC := 147, (*mapp Mechatronics Facility*)
		mpCOM_FAC_MAPP_INDUSTRY := 148 (*mapp Industry Facility*)
		);
	MpComConfigScopeEnum : 
		(
		mpCOM_CONFIG_SCOPE_COMPONENT := 0, (*Import / Export configuration only for given component*)
		mpCOM_CONFIG_SCOPE_BRANCH := 1 (*Import / Export configuration for given component and all its sub-components*)
		);
	MpComInternalIDType : 	STRUCT 
		ID : DINT; (*Status ID*)
		Severity : MpComSeveritiesEnum; (*Status severity*)
		Facility : MpComFacilitiesEnum; (*Status facility*)
		Code : UINT; (*Status / Error code*)
	END_STRUCT;
	MpComStatusIDType : 	STRUCT 
		ID : MpComErrorEnum; (*Status ID*)
		Severity : MpComSeveritiesEnum; (*Status severity*)
		Facility : MpComFacilitiesEnum; (*Status facility*)
		Code : UINT; (*Status / Error code*)
	END_STRUCT;
	MpComDiagType : 	STRUCT 
		StatusID : MpComStatusIDType; (*StatusID diagnostic structure *)
	END_STRUCT;
	MpComConfigManagerInfoType : 	STRUCT 
		Diag : MpComDiagType; (*Diagnostic structure for the status ID*)
	END_STRUCT;
	MpComIdentType : 	STRUCT 
		Internal : ARRAY[0..1]OF UDINT; (*For internal use only*)
	END_STRUCT;
	MpComInternalDataType : 	STRUCT 
		pObject : UDINT;
		State : UDINT;
	END_STRUCT;
	MpComConfigInternalType : 	STRUCT 
		pObject : UDINT;
		State : DINT;
	END_STRUCT;
	MpComSeveritiesEnum : 
		(
		mpCOM_SEV_SUCCESS := 0, (*Success - no error*)
		mpCOM_SEV_INFORMATIONAL := 1, (*Severity: Informational*)
		mpCOM_SEV_WARNING := 2, (*Severity: Warning*)
		mpCOM_SEV_ERROR := 3 (*Severity: Error*)
		);
	MpComDumpInternalType : 	STRUCT 
		CmdOld : BOOL;
	END_STRUCT;
	MpComLoggerUISetupType : 	STRUCT 
		LoggerListSize : UINT := 20; (*Number of logger entries to be displayed on one page of the list in the HMI application*)
		LoggerScrollWindow : USINT := 0; (*Determines how many entries from the list are displayed in advance when scrolling up and down*)
	END_STRUCT;
	MpComLoggerUIConnectType : 	STRUCT 
		Status : MpComLoggerUIStatusEnum;
		List : MpComLoggerUILoggerListType; (*List of resultant logger entries*)
		Clear : BOOL; (*Clean the internal buffer*)
		SearchFilter : STRING[255]; (*Filter used to define the visibility of entries*)
	END_STRUCT;
	MpComLoggerUIStatusEnum : 
		(
		mpCOM_LOGGERUI_IDLE := 0,
		mpCOM_LOGGERUI_REFRESH := 1,
		mpCOM_LOGGERUI_ERROR := 2
		);
	MpComLoggerUILoggerListType : 	STRUCT 
		Message : ARRAY[0..19]OF STRING[255]; (*List of logger entries: message*)
		StatusID : ARRAY[0..19]OF DINT; (*List of logger entries: status ID*)
		ErrorNumber : ARRAY[0..19]OF UINT; (*List of logger entries: error code as part of Status ID*)
		Time : ARRAY[0..19]OF MpComLoggerUIDateTimeType; (*List of logger entries: date, time and microseconds*)
		Component : ARRAY[0..19]OF STRING[50]; (*List of logger entries: component name*)
		Facility : ARRAY[0..19]OF MpComFacilitiesEnum; (*List of logger entries: facility as part of Status ID*)
		Severity : ARRAY[0..19]OF MpComSeveritiesEnum; (*List of logger entries: severity as part of Status ID*)
		PageUp : BOOL; (*Jumps to the start of the current page and then scrolls up one page at a time *)
		PageDown : BOOL; (*Jumps to the end of the current page and then scrolls down one page at a time *)
		StepUp : BOOL; (*Selects the previous entry in the list*)
		StepDown : BOOL; (*Selects the next entry in the list*)
		RangeStart : REAL; (*Shows a bar indicating which part of the list is currently being displayed-Start [%]*)
		RangeEnd : REAL; (*Shows a bar indicating which part of the list is currently being displayed-End [%]*)
	END_STRUCT;
	MpComLoggerUIDateTimeType : 	STRUCT 
		DateTime : DATE_AND_TIME; (*List of logger entries: date and time: the view could be customized on VC*)
		Microseconds : UDINT; (*List of logger entries: additional information about microseconds when the event was triggered*)
	END_STRUCT;
	MpComLoggerUIInfoType : 	STRUCT 
		CurrentBufferEntries : UINT; (*Number of entries currently in the internal buffer. It is a ring buffer, it means that reached the BufferSize it doesn't increase any more*)
		Diag : MpComDiagType; (*Diagnostic structure for the status ID*)
	END_STRUCT;
END_TYPE
