
TYPE
	MainSwitch_enum : 
		(
		DISABLED := 0,
		ENABLED := 1,
		RUN := 2,
		ERROR := 255
		);
	FTPSwitch_enum : 
		(
		DEVLINK := 1,
		FILECOPY := 2,
		DEVUNLINK := 3
		);
	ControlSwitch_enum : 
		(
		WAIT_CMD := 0,
		TRIGGER_RDY := 1,
		TRIGGER := 2,
		ACQ := 3,
		INSP := 4
		);
	InSight_type : 	STRUCT 
		ModuleOk : BOOL;
		Control_I2000_S01 : UDINT; (*Camera control including trigger*)
		Status_I2001_S01 : UDINT;
		InspectionResults_I2011_S01 : UDINT; (*X Axis*)
		InspectionResults_I2011_S02 : UDINT; (*Y Axis*)
		InspectionResults_I2011_S03 : UDINT; (*Succes*)
		InspectionResults_I2011_S04 : UDINT; (*Fail*)
		UserData_I2021_S01 : UDINT; (*Change zone*)
	END_STRUCT;
	Internal_type : 	STRUCT 
		NaN : REAL;
		CameraControl : CameraControl_type;
		MainSwitch : MainSwitch_enum;
		FTP : FTP_type;
		SuccesCount : UDINT;
		FailCount : UDINT;
		disableBit : USINT;
		Search_tmp : BOOL;
		Zone : Zone_enum;
		ChangeZone : ChangeZone_enum;
		oldState : ChangeZone_enum;
	END_STRUCT;
	Zone_enum : 
		(
		ZONE1 := 0,
		ZONE2 := 1,
		ZONE3 := 2,
		ZONE4 := 3,
		ZONE5 := 4,
		ZONE6 := 5,
		ZONE7 := 6,
		ZONE8 := 7,
		WHOLE := 500
		);
	ChangeZone_enum : 
		(
		CHANGE := 2,
		ONE_ZONE := 1,
		WHOLE_ZONE := 0
		);
	Results_type : 	STRUCT 
		AxisX : REAL;
		AxisY : REAL;
		ActTime : RTCtime_typ;
		AxisXOld : REAL;
		AxisYOld : REAL;
		TimeDiff_ms : REAL;
		ActTimeOld : RTCtime_typ;
		NewVal : BOOL;
	END_STRUCT;
	CameraControl_type : 	STRUCT 
		ControlSwitch : ControlSwitch_enum;
	END_STRUCT;
	MappView_type : 	STRUCT 
		ZoneString : STRING[80];
		PicEnable : BOOL;
		Y : ARRAY[0..1000]OF INT;
		X : ARRAY[0..1000]OF INT := [11(5),0,996(0)];
		LoadImage : BOOL;
	END_STRUCT;
	FTP_type : 	STRUCT 
		FileCopy_0 : FileCopy;
		DevLink_0 : DevLink;
		DevUnlink_0 : DevUnlink;
		Status : USINT;
		FTPSwitch : FTPSwitch_enum;
		pParam : STRING[200];
		handle : UDINT;
		pDevice : STRING[20];
		pDest : STRING[80];
		pSrc : STRING[80];
		pDestDev : STRING[20];
	END_STRUCT;
END_TYPE
