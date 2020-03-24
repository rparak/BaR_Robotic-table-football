#include <bur/plctypes.h>
#include <math.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define NaN sqrt(-1)
#define CAM_OFFLINE_MASK 128												//1000 0000b
#define CAM_ONLINE_MASK 0xFFFFFF7F

#define CAM_USER_DATA 0x10004												//Mask for user data ack	
#define CAM_FIND_WHOLE_ZONE 0xFFFFFFFF										//Mask for finding at whole playground

#define MAX_DIFF_PER 0.15													//Max diffrence between old and actual value in %


#define ABS_F(X) ((X) < (0) ? -(X) : (X)) 									//ABS funkcion
							//		  |							9800
#define X1_REF_PLGND 800.0	//(UNITS) |				   3800 6800  | 11300
#define X2_REF_PLGND 11300.0//(UNITS) |				 _____|___|___|_|_
#define X1_REF_CAM 1215.0	//(PIXELS)|				| | | O O O O | | |		SCHEME OF X AXIS
#define X2_REF_CAM 82.0		//(PIXELS)|				| | O | O O | O | |		AND PLAYGROUND WITH
 							//		  |		    	| O | O O O O | O |		DISTANCE OF PLAYERS
#define Y1_REF_PLGND 820.0	//(UNITS) |	 	  		| | O | O O | O | |		IN UNITS
#define Y2_REF_PLGND -950.0 //(UNITS) |				|_|_|_O_O_O_O_|_|_|		(10 UNITS = 1 MM)
#define Y1_REF_CAM 414.0	//(PIXELS)| 		      | |   |   |
#define Y2_REF_CAM 604.0	//(PIXELS)|			 	800 | 5300 8300
							//		  |		    	   2300

#define X_LIN_EQ_K ((X1_REF_PLGND-X2_REF_PLGND)/(X1_REF_CAM-X2_REF_CAM)) 		//Define K-parameter of line equaton for X axis
#define X_LIN_EQ_Q (X1_REF_PLGND-(X1_REF_CAM*X_LIN_EQ_K))				 		//Define Q-parameter of line equaion for X axis

#define Y_LIN_EQ_K ((Y1_REF_PLGND-Y2_REF_PLGND)/(Y1_REF_CAM-Y2_REF_CAM))		//Define K-parameter of line equaton for Y axis
#define Y_LIN_EQ_Q (Y1_REF_PLGND-(Y1_REF_CAM*Y_LIN_EQ_K))						//Define Q-parameter of line equaton for Y axis

#define X_MAX_DIFF ABS_F((X_LIN_EQ_K+X_LIN_EQ_Q)-((2*X_LIN_EQ_K)+X_LIN_EQ_Q))	//Line equation for X axis
#define Y_MAX_DIFF ABS_F((Y_LIN_EQ_K+Y_LIN_EQ_Q)-((2*Y_LIN_EQ_K)+Y_LIN_EQ_Q))	//Line equation for Y axis

void setError(struct FBCamera *inst,unsigned int status);
void initFB(struct FBCamera *inst);
void resetFB(struct FBCamera *inst);
void getRealAxes(struct FBCamera *inst);
void cleanFB(struct FBCamera *inst);
REAL RctToReal_ms (struct RTCtime_typ RTCtime);

void FBCamera(struct FBCamera *inst)
{	
	if ((!inst->Enable) && (!inst->Internal.disableBit))
		cleanFB(inst);

	switch (inst->Internal.MainSwitch){										//Main switch, DISABLED FB, INITialising FB, ENABLED FB and ERROR case
		/******************************************************************/
		/*							FB is DISABLED					 	  */
		/******************************************************************/
		
		case DISABLED:														//FB is disabled
			if (inst->Internal.disableBit){
				cleanFB(inst);
				inst->Internal.disableBit = 1;
			}
			if (inst->Enable){												//Wait for Enable = TRUE, else do nothing
				inst->Internal.MainSwitch = ENABLED;						//Go to ENABLED case
				inst->Internal.disableBit = 0;	
			}
			else
				inst->Status = ERR_FUB_ENABLE_FALSE;						//Status 65534, FB is called but not enabled
			break;
		
		/******************************************************************/
		/*				FB is ENABLED but Camera is not ready		 	  */
		/******************************************************************/
		
		case ENABLED:														//FB is enabled and working
			inst->Status = ERR_OK;											//No error in enable case
			inst->Active = 1;												//variable indicating active FB
			if (!inst->InSight.ModuleOk){									//InSight Camera is not connected properly
				inst->isCameraReady = 0;									//Bit for user that Camera is not working
				if (inst->Search)											//If user allow searching for ball, change case to ERROR because you cannot find while there is no camera
					setError(inst,ERR_CAM_NOTFOUND);						//Error, Status 65533 - camera not found	
			}
			else {
				inst->isCameraReady = 1;									//Bit for user that Camera is working
				inst->Internal.MainSwitch = RUN;							//Change state to RUN								
			}
			break;
		
		/******************************************************************/
		/*						FB and Camera are ready				 	  */
		/******************************************************************/
		case RUN:															//FB is enabled and camera communicating
			if (!(inst->InSight.ModuleOk))									//if camera is disconnected change state to ENABLE where waiting for connect
				inst->Internal.MainSwitch = ENABLED;
			if (inst->Search){
				inst->isSearching = 1;
				inst->InSight.Control_I2000_S01 &= CAM_ONLINE_MASK;			//Disable control bit for cammera offline mode
				switch (inst->Internal.ChangeZone){	
					case CHANGE:
						if ((inst->InSight.Control_I2000_S01 & CAM_USER_DATA) == CAM_USER_DATA){
							if ((inst->InSight.Status_I2001_S01 & 0x10000) == 0x10000) {
								if (inst->Internal.oldState == ONE_ZONE)
									inst->Internal.ChangeZone = WHOLE_ZONE;
								else
									inst->Internal.ChangeZone = ONE_ZONE;
								inst->InSight.Control_I2000_S01 &= 0xFFFEFFFB;
							}
						}
						else inst->Internal.ChangeZone = WHOLE_ZONE;							
						break;
					
					case ONE_ZONE:
						getRealAxes(inst);
						inst->Internal.oldState = ONE_ZONE;
						if (((isnan(inst->Results.AxisX)) || isnan(inst->Results.AxisY)) && (inst->Results.NewVal)){
							inst->Internal.ChangeZone = CHANGE;
							inst->InSight.Control_I2000_S01 |= CAM_USER_DATA;
							inst->InSight.UserData_I2021_S01 = 65535;
						}
						switch (inst->Internal.Zone){
							case ZONE1:
								strcpy(inst->MappView.ZoneString,"Zone 1");
								break;
							
							case ZONE2:
								strcpy(inst->MappView.ZoneString,"Zone 2");
								break;
							
							case ZONE3:
								strcpy(inst->MappView.ZoneString,"Zone 3");
								break;
													
							case ZONE4:
								strcpy(inst->MappView.ZoneString,"Zone 4");
								break;
													
							case ZONE5:
								strcpy(inst->MappView.ZoneString,"Zone 5");
								break;
													
							case ZONE6:
								strcpy(inst->MappView.ZoneString,"Zone 6");
								break;
													
							case ZONE7:
								strcpy(inst->MappView.ZoneString,"Zone 7");
								break;
						
							case ZONE8:
								strcpy(inst->MappView.ZoneString,"Zone 8");
								break;
						
							case WHOLE:
								
								break;
						}
						break;

					case WHOLE_ZONE:
						getRealAxes(inst);
						inst->Internal.Zone = WHOLE;
						inst->Internal.oldState = WHOLE_ZONE;
						strcpy(inst->MappView.ZoneString,"Whole");
						if(inst->isBallFound){
							inst->Internal.ChangeZone = CHANGE;
							inst->InSight.Control_I2000_S01 |= CAM_USER_DATA;
							if (inst->Results.AxisX > 10300){
								inst->InSight.UserData_I2021_S01 = 1;
								inst->Internal.Zone = ZONE1;}
							else if (inst->Results.AxisX > 9050){
								inst->InSight.UserData_I2021_S01 = 2;
								inst->Internal.Zone = ZONE2;}
							else if (inst->Results.AxisX > 7350){
								inst->InSight.UserData_I2021_S01 = 4;
								inst->Internal.Zone = ZONE3;}
							else if (inst->Results.AxisX > 6250){
								inst->InSight.UserData_I2021_S01 = 8;
								inst->Internal.Zone = ZONE4;}
							else if (inst->Results.AxisX > 4400){
								inst->InSight.UserData_I2021_S01 = 16;
								inst->Internal.Zone = ZONE5;}
							else if (inst->Results.AxisX > 3850){
								inst->InSight.UserData_I2021_S01 = 32;
								inst->Internal.Zone = ZONE6;}
							else if (inst->Results.AxisX > 1260){
								inst->InSight.UserData_I2021_S01 = 64;
								inst->Internal.Zone = ZONE7;}
							else if(inst->Results.AxisX > 0){
								inst->InSight.UserData_I2021_S01 = 128;
								inst->Internal.Zone = ZONE8;}
							else{
								inst->Internal.ChangeZone = WHOLE_ZONE;
								inst->InSight.Control_I2000_S01 &= 0xFFFEFFFB;
								inst->InSight.UserData_I2021_S01 = 0xFFFF;
							}
						}
						break;
					
				}
			}
			else{
				inst->InSight.Control_I2000_S01 |= CAM_OFFLINE_MASK;
				inst->isSearching = 0;
			}
			break;
		
		case ERROR:															//error case, to change state is needed error Reset variable or disable FB
			inst->Error = 1;												//Change Error variable
			inst->Internal.CameraControl.ControlSwitch = WAIT_CMD;			//Reset camera trigger state
			inst->isSearching = 0;											//FB cannot searching in error case
			if (inst->ErrorReset){											//waiting on ErrorReset
				inst->Error = 0;
				inst->Status = ERR_OK;
				resetFB(inst);
				inst->Internal.MainSwitch = ENABLED;						//change state
			}
			break;
	}
		
	if (inst->ErrorReset)										
		resetFB(inst);
		
	if (inst->Error == 1)						
		inst->Internal.MainSwitch = ERROR;
	
}

void initFB(struct FBCamera *inst)
{
	inst->Active = 0;
	inst->Error = 0;
	inst->ErrorReset = 0;
	inst->isCameraReady = 0;
	inst->isBallFound = 0;
	inst->isSearching = 0;
	inst->Search = 0;
	inst->Status = ERR_OK;
	inst->Internal.CameraControl.ControlSwitch = WAIT_CMD;
	inst->Internal.MainSwitch = DISABLED;
	inst->Internal.Search_tmp = 0;
	inst->Internal.disableBit = 1;
	inst->InSight.Control_I2000_S01 |= CAM_OFFLINE_MASK;					
	memset(&inst->Results.ActTime,0,sizeof(inst->Results.ActTime));
	inst->Results.AxisXOld = NaN;
	inst->Results.AxisYOld = NaN;
	inst->InSight.Control_I2000_S01 |= CAM_USER_DATA;
	inst->InSight.UserData_I2021_S01 = 65535;
	inst->Internal.ChangeZone = CHANGE;
}

void resetFB(struct FBCamera *inst)
{
	inst->ErrorReset = 0;							//Reset error reset
	inst->Error = 0;								//Reset Error
	inst->Status = ERR_OK;	
}

void cleanFB(struct FBCamera *inst)
{
	initFB(inst);
	resetFB(inst);
}

void setError(struct FBCamera *inst,unsigned int status) {
	inst->Error = 1;
	inst->Status = status;
}

void getRealAxes(struct FBCamera *inst)
{
	if (inst->Internal.SuccesCount != inst->InSight.InspectionResults_I2011_S03){
		inst->Results.NewVal = 1;
		REAL AxisXnew = ((inst->InSight.InspectionResults_I2011_S01*X_LIN_EQ_K)+X_LIN_EQ_Q);
		REAL AxisYnew = ((inst->InSight.InspectionResults_I2011_S02*Y_LIN_EQ_K)+Y_LIN_EQ_Q);
		
		if (((AxisXnew >= 0) && (AxisXnew < 12100)) && ((AxisYnew < 3515) && (AxisYnew > -3515))){
			
			if (isnan(inst->Results.AxisX) || isnan(inst->Results.AxisY)){
				inst->Results.AxisX = AxisXnew;
				inst->Results.AxisY = AxisYnew;
			}
			else if(((ABS_F(AxisXnew - (inst->Results.AxisX))) < (X_MAX_DIFF * 2)) && (((ABS_F(AxisYnew - (inst->Results.AxisY))) < (Y_MAX_DIFF * 2)))) {
				inst->Results.AxisXOld = inst->Results.AxisX = ((AxisXnew + inst->Results.AxisX)/2);
				inst->Results.AxisYOld = inst->Results.AxisY = ((AxisYnew + inst->Results.AxisY)/2);
			}
			else{
				inst->Results.AxisXOld = inst->Results.AxisX;
				inst->Results.AxisYOld = inst->Results.AxisY;
				inst->Results.AxisX = AxisXnew;
				inst->Results.AxisY = AxisYnew;
			}
			memcpy((UDINT)&inst->Results.ActTimeOld,(UDINT)&inst->Results.ActTime,sizeof(inst->Results.ActTime));
			RTC_gettime(&inst->Results.ActTime);
			inst->Results.TimeDiff_ms = ((RctToReal_ms(inst->Results.ActTime)) - (RctToReal_ms(inst->Results.ActTimeOld)));
			inst->isBallFound = 1;
			inst->Status = ERR_OK;
			inst->Internal.SuccesCount = inst->InSight.InspectionResults_I2011_S03;
		}
		else{
			inst->Status = ERR_BALL_OUTRANGE;
			inst->isBallFound = 0;
		}
	}
	else if (inst->Internal.FailCount != inst->InSight.InspectionResults_I2011_S04){ 
		inst->Results.NewVal = 1;
		if (!isnan(inst->Results.AxisX) || !isnan(inst->Results.AxisY)){
			inst->Results.AxisXOld = inst->Results.AxisX;
			inst->Results.AxisYOld = inst->Results.AxisY;
		}
		inst->Results.AxisX = inst->Results.AxisY = NaN;
		inst->Internal.FailCount = inst->InSight.InspectionResults_I2011_S04;
		inst->isBallFound = 0;
		memcpy((UDINT)&inst->Results.ActTimeOld,(UDINT)&inst->Results.ActTime,sizeof(inst->Results.ActTime));
		RTC_gettime(&inst->Results.ActTime);
		inst->Results.TimeDiff_ms = ((RctToReal_ms(inst->Results.ActTime)) - (RctToReal_ms(inst->Results.ActTimeOld)));
	}
	else{
		inst->isBallFound = 0;
		inst->Results.NewVal = 1;
	}
}

REAL RctToReal_ms (struct RTCtime_typ RTCtime){
	return(((REAL)RTCtime.hour*3600000)+((REAL)RTCtime.minute*60000)+((REAL)RTCtime.second*1000)+((REAL)RTCtime.millisec)+((REAL)RTCtime.microsec/1000));
}

