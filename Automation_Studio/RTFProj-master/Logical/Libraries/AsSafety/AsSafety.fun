(********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: AsSafety
 * File: AsSafety.fun
 * Author: B&R
 * Created: May 25, 2012
 ********************************************************************
 * Functions and function blocks of library AsSafety
 ********************************************************************)

{REDUND_ERROR} FUNCTION_BLOCK safeRemoteControl (*Remote Control Function Block*)
	VAR_INPUT
		SafeLOGICID : UINT; (*SafeLOGIC ID*)
		Execute : BOOL; (*execution*)
		pCommandData : UDINT; (*pointer to command data*)
	END_VAR
	VAR_OUTPUT
		Done : BOOL; (*execution done*)
		Busy : BOOL; (*execution busy*)
		Error : BOOL; (*execution error*)
		StatusID : UINT; (*execution status: ERR_OK, ERR_FUB_BUSY, 0xXXXX = see help*)
		SafeLOGICStatus : RemoteControlStatusTypeV1; (*SafeLOGIC status*)
	END_VAR
	VAR
		i_state : UINT; (*internal variable*)
		i_result : UINT; (*internal variable*)
		i_tmp : UDINT; (*internal variable*)
		i_handle : UDINT; (*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK safeDownloadApplication (*Download Application Function Block*)
	VAR_INPUT
		SafeLOGICID : UINT; (*SafeLOGIC ID*)
		Execute : BOOL; (*execution*)
		pCommandData : UDINT; (*pointer to command data*)
	END_VAR
	VAR_OUTPUT
		Done : BOOL; (*execution done*)
		Busy : BOOL; (*execution busy*)
		Error : BOOL; (*execution error*)
		StatusID : UINT; (*execution status: ERR_OK, ERR_FUB_BUSY, 0xXXXX = see help*)
		UnlockRequired : BOOL; (*unlock required*)
		ApplicationCRC : UDINT; (*application CRC*)
	END_VAR
	VAR
		i_state : UINT; (*internal variable*)
		i_result : UINT; (*internal variable*)
		i_tmp : UDINT; (*internal variable*)
		i_handle : UDINT; (*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK safeDownloadData (*Download Data Function Block*)
	VAR_INPUT
		SafeLOGICID : UINT; (*SafeLOGIC ID*)
		Execute : BOOL; (*execution*)
		Type : UINT; (*type of data: safeDATA_TYPE_MAOP, safeDATA_TYPE_EXTMAOP,... *)
		pCommandData : UDINT; (*pointer to command data*)
	END_VAR
	VAR_OUTPUT
		Done : BOOL; (*execution done*)
		Busy : BOOL; (*execution busy*)
		Error : BOOL; (*execution error*)
		StatusID : UINT; (*execution status: ERR_OK, ERR_FUB_BUSY, 0xXXXX = see help*)
		UnlockRequired : BOOL; (*unlock required*)
		Timestamp : UDINT; (*timestamp from data*)
	END_VAR
	VAR
		i_state : UINT; (*internal variable*)
		i_result : UINT; (*internal variable*)
		i_tmp : UDINT; (*internal variable*)
		i_handle : UDINT; (*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK safeConfigurationOnTarget (*Configuration On Target Function Block*)
	VAR_INPUT
		SafeLOGICID : UINT; (*SafeLOGIC ID*)
		Execute : BOOL; (*execution*)
		Type : UINT; (*type of data: safeDATA_TYPE_MAOP, safeDATA_TYPE_EXTMAOP,...*)
		pCommandData : UDINT; (*pointer to command data*)
	END_VAR
	VAR_OUTPUT
		Done : BOOL; (*execution done*)
		Busy : BOOL; (*execution busy*)
		Error : BOOL; (*execution error*)
		StatusID : UINT; (*execution status: ERR_OK, ERR_FUB_BUSY, 0xXXXX = see help*)
		Timestamp : UDINT; (*timestamp of data*)
	END_VAR
	VAR
		i_state : UINT; (*internal variable*)
		i_result : UINT; (*internal variable*)
		i_tmp : UDINT; (*internal variable*)
		i_handle : UDINT; (*internal variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION safeLibraryVersion : UINT (*Function to get current library version*)
END_FUNCTION
