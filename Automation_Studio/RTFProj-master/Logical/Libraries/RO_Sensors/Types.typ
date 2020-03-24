
TYPE
	PositionStatus : 
		(
		PosCalcPos, (*1*)
		PosInitial
		);
	Stuct_OptSensInternal : 	STRUCT 
		TransConstant : ARRAY[0..3]OF INT;
		MaxPosHum : ARRAY[0..3]OF INT := [1025,1700,675,975];
		MinPosHum : ARRAY[0..3]OF INT := [-1025,-1700,-675,-975];
		RefPosHum : ARRAY[0..3]OF INT := [4(0)];
		MaxPosSens : ARRAY[0..3]OF INT := [31406,31852,32495,31208];
		MinPosSens : ARRAY[0..3]OF INT := [13652,6831,23895,12431];
		RefPosSens : ARRAY[0..3]OF INT := [22798,18167,28195,21044];
		Index : ARRAY[0..5]OF USINT;
		DR_ReflexSensStatus_0 : DetectionRotation;
		DP_Figure_0 : DetPos_Figure;
		MinAccDiff : INT := 100;
		MaxAccDiff : ARRAY[0..3]OF INT := [4(100)];
		CurrentPosition : ARRAY[0..3]OF INT;
	END_STRUCT;
	Stuct_RexlSensInternal : 	STRUCT 
		ActReflexSensStatusRS : ARRAY[0..3]OF BOOL;
		ErrorStatusRS : ARRAY[0..3]OF BOOL;
		ExternalReflexSensStatusRS : ARRAY[0..3]OF BOOL;
		ReflexSensStatusRS : ARRAY[0..3]OF BOOL;
		IndexR : ARRAY[0..1]OF USINT;
	END_STRUCT;
	Struct_OptSensFigInternal : 	STRUCT 
		MaxPosHumDP : ARRAY[0..3]OF INT;
		MinPosHumDP : ARRAY[0..3]OF INT;
		DispAxisDP : ARRAY[0..10]OF INT := [0,-1200,1200,-2400,-1200,0,1200,2400,-2100,0,2100];
		CurrentPosition : ARRAY[0..10]OF INT;
		Index : ARRAY[0..2]OF USINT;
	END_STRUCT;
	Struct_CorrectionFun : 	STRUCT 
		CorrectionPosition : ARRAY[0..3]OF INT;
		FundamentalVal : FundamentalType;
		ComputedPosition : ARRAY[0..3]OF ComputedPosType := [(Comp:=[-1130,-1056,-930,-789,-661,-498,-356,-221,-84,51,167,260,343,444,528,593,678,748,835,908,985,1021,13(5000)]),(Comp:=[-1618,-1517,-1419,-1296,-1187,-1077,-970,-863,-758,-656,-543,-454,-337,-236,-141,-36,65,163,271,381,490,606,693,791,903,1000,1120,1218,1343,1440,1541,1625,1744,1875,1945]),(Comp:=[-634,-526,-397,-259,-158,-39,55,177,278,368,479,582,698,777,21(5000)]),(Comp:=[-954,-834,-714,-620,-488,-397,-266,-163,-47,73,155,261,344,431,532,618,719,836,931,1051,1119,14(5000)])];
		RealPositionMeasured : ARRAY[0..3]OF MeasPosMesType := [(Meas:=[-1025,-925,-825,-725,-625,-525,-425,-325,-225,-125,-25,75,175,275,375,475,575,675,775,875,975,1025,13(5000)]),(Meas:=[-1700,-1600,-1500,-1400,-1300,-1200,-1100,-1000,-900,-800,-700,-600,-500,-400,-300,-200,-100,0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700]),(Meas:=[-675,-575,-475,-375,-275,-175,-75,25,125,225,325,425,525,675,21(5000)]),(Meas:=[-975,-875,-775,-675,-575,-475,-375,-275,-175,-75,25,125,225,325,425,525,625,725,825,925,975,14(5000)])];
		Index : IndexType;
		DifferenceYi : DifferenceType;
	END_STRUCT;
	DifferenceType : 	STRUCT 
		Y0 : ARRAY[0..34]OF INT; (*21 valid members of the field*)
		Y1 : ARRAY[0..34]OF INT; (*34 valid members of the field*)
		Y2 : ARRAY[0..34]OF INT; (*13 valid members of the field*)
		Y3 : ARRAY[0..34]OF INT; (*20 valid members of the field*)
	END_STRUCT;
	RealPosMesType1 : 	STRUCT 
		RealPosAxisGoalkeeper : ARRAY[0..34]OF INT := [-1025,-925,-825,-725,-625,-525,-425,-325,-225,-125,-25,75,175,275,375,475,575,675,775,875,975,1025,13(5000)];
		RealPosAxisDefender : ARRAY[0..34]OF INT := [-1700,-1600,-1500,-1400,-1300,-1200,-1100,-1000,-900,-800,-700,-600,-500,-400,-300,-200,-100,0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700];
		RealPosAxisMidfielder : ARRAY[0..34]OF INT := [-675,-575,-475,-375,-275,-175,-75,25,125,225,325,425,525,675,21(5000)];
		RealPosAxisAttaker : ARRAY[0..34]OF INT := [-975,-875,-775,-675,-575,-475,-375,-275,-175,-75,25,125,225,325,425,525,625,725,825,925,975,14(5000)];
	END_STRUCT;
	ComputedPosType1 : 	STRUCT 
		CompPosAxisGoalkeeper : ARRAY[0..34]OF INT := [-1130,-1056,-930,-789,-661,-498,-356,-221,-84,51,167,260,343,444,528,593,678,748,835,908,985,1021,13(5000)];
		CompPosAxisDefender : ARRAY[0..34]OF INT := [-1618,-1517,-1419,-1296,-1187,-1077,-970,-863,-758,-656,-543,-454,-337,-236,-141,-36,65,163,271,381,490,606,693,791,903,1000,1120,1218,1343,1440,1541,1625,1744,1875,1945];
		CompPosAxisMidfielder : ARRAY[0..34]OF INT := [-634,-526,-397,-259,-158,-39,55,177,278,368,479,582,698,777,21(5000)];
		CompPosAxisAttaker : ARRAY[0..34]OF INT := [-954,-834,-714,-620,-488,-397,-266,-163,-47,73,155,261,344,431,532,618,719,836,931,1051,1119,14(5000)];
	END_STRUCT;
	MeasPosMesType : 	STRUCT 
		Meas : ARRAY[0..34]OF INT;
	END_STRUCT;
	ComputedPosType : 	STRUCT 
		Comp : ARRAY[0..34]OF INT;
	END_STRUCT;
	IndexType : 	STRUCT 
		i0 : INT;
		i1 : INT;
		i2 : INT;
		i3 : INT;
	END_STRUCT;
	FundamentalType : 	STRUCT 
		L0 : ARRAY[0..21]OF INT;
		L1 : ARRAY[0..37]OF INT;
		L2 : ARRAY[0..13]OF INT;
		L3 : ARRAY[0..20]OF INT;
	END_STRUCT;
END_TYPE
