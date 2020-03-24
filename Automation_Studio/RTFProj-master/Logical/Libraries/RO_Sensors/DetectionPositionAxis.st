
(* NUMERIC CALCULATION OF POSITION ALL AXES *)
FUNCTION_BLOCK DetectionPositionAxis
	
	// Calculate a constants
	InternalPos.TransConstant[0] := (InternalPos.MaxPosSens[0]-InternalPos.MinPosSens[0])/(InternalPos.MaxPosHum[0]-InternalPos.MinPosHum[0]);
	InternalPos.TransConstant[1] := (InternalPos.MaxPosSens[1]-InternalPos.MinPosSens[1])/(InternalPos.MaxPosHum[1]-InternalPos.MinPosHum[1]);
	InternalPos.TransConstant[2] := (InternalPos.MaxPosSens[2]-InternalPos.MinPosSens[2])/(InternalPos.MaxPosHum[2]-InternalPos.MinPosHum[2]);
	InternalPos.TransConstant[3] := (InternalPos.MaxPosSens[3]-InternalPos.MinPosSens[3])/(InternalPos.MaxPosHum[3]-InternalPos.MinPosHum[3]);
	
	// Lagrange polynomal function for CORRECTION of Computed Position Human Axis
(*	// 1.] Calculate a difference of computed value & measured value of position
	FOR CorrectionPos.Index.i0 := 0 TO 21 DO
		CorrectionPos.DifferenceYi.Y0[CorrectionPos.Index.i0] := CorrectionPos.ComputedPosition.CompPosAxisGoalkeeper[CorrectionPos.Index.i0] - CorrectionPos.RealPositionMeasured.RealPosAxisGoalkeeper[CorrectionPos.Index.i0];
	END_FOR;
	FOR CorrectionPos.Index.i1 := 0 TO 34 DO
		CorrectionPos.DifferenceYi.Y1[CorrectionPos.Index.i1] := CorrectionPos.ComputedPosition.CompPosAxisDefender[CorrectionPos.Index.i1] - CorrectionPos.RealPositionMeasured.RealPosAxisDefender[CorrectionPos.Index.i1];
	END_FOR;
	FOR CorrectionPos.Index.i2 := 0 TO 13 DO
		CorrectionPos.DifferenceYi.Y2[CorrectionPos.Index.i2] := CorrectionPos.ComputedPosition.CompPosAxisMidfielder[CorrectionPos.Index.i2] - CorrectionPos.RealPositionMeasured.RealPosAxisMidfielder[CorrectionPos.Index.i2];
	END_FOR;
	FOR CorrectionPos.Index.i3 := 0 TO 20 DO
		CorrectionPos.DifferenceYi.Y3[CorrectionPos.Index.i3] := CorrectionPos.ComputedPosition.CompPosAxisAttaker[CorrectionPos.Index.i3] - CorrectionPos.RealPositionMeasured.RealPosAxisAttaker[CorrectionPos.Index.i3];
	END_FOR;
	
	// 2.] Calculate a fundamental polynoms for EACH human axis
	FOR CorrectionPos.Index.i0 := 0 TO 21 DO
	CorrectionPos.FundamentalVal.L0[CorrectionPos.Index.i0] := (((ActPosHumBasic[0]-1)*(ActPosHumBasic[0]-2)*(ActPosHumBasic[0]-3))/((CorrectionPos.RealPositionMeasured.RealPosAxisGoalkeeper[CorrectionPos.Index.i0]-1)*(CorrectionPos.RealPositionMeasured.RealPosAxisGoalkeeper[CorrectionPos.Index.i0]-2)*(CorrectionPos.RealPositionMeasured.RealPosAxisGoalkeeper[CorrectionPos.Index.i0]-3)));
	END_FOR;
	FOR CorrectionPos.Index.i1 := 0 TO 34 DO
		CorrectionPos.FundamentalVal.L1[CorrectionPos.Index.i1] := (((ActPosHumBasic[1]-1)*(ActPosHumBasic[1]-2)*(ActPosHumBasic[1]-3))/((CorrectionPos.RealPositionMeasured.RealPosAxisDefender[CorrectionPos.Index.i1]-1)*(CorrectionPos.RealPositionMeasured.RealPosAxisDefender[CorrectionPos.Index.i1]-2)*(CorrectionPos.RealPositionMeasured.RealPosAxisDefender[CorrectionPos.Index.i1]-3)));
	END_FOR;
	FOR CorrectionPos.Index.i2 := 0 TO 13 DO
		CorrectionPos.FundamentalVal.L2[CorrectionPos.Index.i2] := (((ActPosHumBasic[2]-1)*(ActPosHumBasic[2]-2)*(ActPosHumBasic[2]-3))/((CorrectionPos.RealPositionMeasured.RealPosAxisMidfielder[CorrectionPos.Index.i2]-1)*(CorrectionPos.RealPositionMeasured.RealPosAxisMidfielder[CorrectionPos.Index.i2]-2)*(CorrectionPos.RealPositionMeasured.RealPosAxisMidfielder[CorrectionPos.Index.i2]-3)));
	END_FOR;
	FOR CorrectionPos.Index.i3 := 0 TO 20 DO
		CorrectionPos.FundamentalVal.L3[CorrectionPos.Index.i3] := (((ActPosHumBasic[3]-1)*(ActPosHumBasic[3]-2)*(ActPosHumBasic[3]-3))/((CorrectionPos.RealPositionMeasured.RealPosAxisAttaker[CorrectionPos.Index.i3]-1)*(CorrectionPos.RealPositionMeasured.RealPosAxisAttaker[CorrectionPos.Index.i3]-2)*(CorrectionPos.RealPositionMeasured.RealPosAxisAttaker[CorrectionPos.Index.i3]-3)));
	END_FOR;
	
	// 3.] Calculate a correction polynomal functions
	// Goalkeeper axis
	CorrectionPos.CorrectionPosition[0] := CorrectionPos.DifferenceYi.Y0[0]*CorrectionPos.FundamentalVal.L0[0]+CorrectionPos.DifferenceYi.Y0[1]*CorrectionPos.FundamentalVal.L0[2]+CorrectionPos.DifferenceYi.Y0[3]*CorrectionPos.FundamentalVal.L0[3]+CorrectionPos.DifferenceYi.Y0[4]*CorrectionPos.FundamentalVal.L0[4]+CorrectionPos.DifferenceYi.Y0[5]*CorrectionPos.FundamentalVal.L0[5]+CorrectionPos.DifferenceYi.Y0[6]*CorrectionPos.FundamentalVal.L0[6]+
	CorrectionPos.DifferenceYi.Y0[7]*CorrectionPos.FundamentalVal.L0[7]+CorrectionPos.DifferenceYi.Y0[8]*CorrectionPos.FundamentalVal.L0[8]+CorrectionPos.DifferenceYi.Y0[9]*CorrectionPos.FundamentalVal.L0[9]+CorrectionPos.DifferenceYi.Y0[10]*CorrectionPos.FundamentalVal.L0[10]+CorrectionPos.DifferenceYi.Y0[11]*CorrectionPos.FundamentalVal.L0[11]+CorrectionPos.DifferenceYi.Y0[12]*CorrectionPos.FundamentalVal.L0[12]+CorrectionPos.DifferenceYi.Y0[13]*CorrectionPos.FundamentalVal.L0[13]
	+CorrectionPos.DifferenceYi.Y0[14]*CorrectionPos.FundamentalVal.L0[14]+CorrectionPos.DifferenceYi.Y0[15]*CorrectionPos.FundamentalVal.L0[15]+CorrectionPos.DifferenceYi.Y0[16]*CorrectionPos.FundamentalVal.L0[16]+CorrectionPos.DifferenceYi.Y0[17]*CorrectionPos.FundamentalVal.L0[17]+CorrectionPos.DifferenceYi.Y0[18]*CorrectionPos.FundamentalVal.L0[18]+CorrectionPos.DifferenceYi.Y0[19]*CorrectionPos.FundamentalVal.L0[19]+CorrectionPos.DifferenceYi.Y0[20]*CorrectionPos.FundamentalVal.L0[20]
	+CorrectionPos.DifferenceYi.Y0[21]*CorrectionPos.FundamentalVal.L0[21];
	// Mid-fielder axis
	CorrectionPos.CorrectionPosition[1] := CorrectionPos.DifferenceYi.Y1[0]*CorrectionPos.FundamentalVal.L1[0]+CorrectionPos.DifferenceYi.Y1[1]*CorrectionPos.FundamentalVal.L1[1]+CorrectionPos.DifferenceYi.Y1[2]*CorrectionPos.FundamentalVal.L1[2]+CorrectionPos.DifferenceYi.Y1[3]*CorrectionPos.FundamentalVal.L1[3]+CorrectionPos.DifferenceYi.Y1[4]*CorrectionPos.FundamentalVal.L1[4]+CorrectionPos.DifferenceYi.Y1[5]*CorrectionPos.FundamentalVal.L1[5]
	+CorrectionPos.DifferenceYi.Y1[6]*CorrectionPos.FundamentalVal.L1[6]+CorrectionPos.DifferenceYi.Y1[7]*CorrectionPos.FundamentalVal.L1[7]+CorrectionPos.DifferenceYi.Y1[8]*CorrectionPos.FundamentalVal.L1[8]+CorrectionPos.DifferenceYi.Y1[9]*CorrectionPos.FundamentalVal.L1[9]+CorrectionPos.DifferenceYi.Y1[10]*CorrectionPos.FundamentalVal.L1[10]+CorrectionPos.DifferenceYi.Y1[11]*CorrectionPos.FundamentalVal.L1[11]+CorrectionPos.DifferenceYi.Y1[12]*CorrectionPos.FundamentalVal.L1[12]
	+CorrectionPos.DifferenceYi.Y1[13]*CorrectionPos.FundamentalVal.L1[13]+CorrectionPos.DifferenceYi.Y1[14]*CorrectionPos.FundamentalVal.L1[14]+CorrectionPos.DifferenceYi.Y1[15]*CorrectionPos.FundamentalVal.L1[15]+CorrectionPos.DifferenceYi.Y1[16]*CorrectionPos.FundamentalVal.L1[16]+CorrectionPos.DifferenceYi.Y1[17]*CorrectionPos.FundamentalVal.L1[17]+CorrectionPos.DifferenceYi.Y1[18]*CorrectionPos.FundamentalVal.L1[18]+CorrectionPos.DifferenceYi.Y1[19]*CorrectionPos.FundamentalVal.L1[19]
	+CorrectionPos.DifferenceYi.Y1[20]*CorrectionPos.FundamentalVal.L1[20]+CorrectionPos.DifferenceYi.Y1[21]*CorrectionPos.FundamentalVal.L1[21]+CorrectionPos.DifferenceYi.Y1[22]*CorrectionPos.FundamentalVal.L1[22]+CorrectionPos.DifferenceYi.Y1[23]*CorrectionPos.FundamentalVal.L1[23]+CorrectionPos.DifferenceYi.Y1[24]*CorrectionPos.FundamentalVal.L1[24]+CorrectionPos.DifferenceYi.Y1[25]*CorrectionPos.FundamentalVal.L1[25]+CorrectionPos.DifferenceYi.Y1[26]*CorrectionPos.FundamentalVal.L1[26]
	+CorrectionPos.DifferenceYi.Y1[27]*CorrectionPos.FundamentalVal.L1[27]+CorrectionPos.DifferenceYi.Y1[28]*CorrectionPos.FundamentalVal.L1[28]+CorrectionPos.DifferenceYi.Y1[29]*CorrectionPos.FundamentalVal.L1[29]+CorrectionPos.DifferenceYi.Y1[30]*CorrectionPos.FundamentalVal.L1[30]+CorrectionPos.DifferenceYi.Y1[31]*CorrectionPos.FundamentalVal.L1[31]+CorrectionPos.DifferenceYi.Y1[32]*CorrectionPos.FundamentalVal.L1[32]+CorrectionPos.DifferenceYi.Y1[33]*CorrectionPos.FundamentalVal.L1[33]
	+CorrectionPos.DifferenceYi.Y1[34]*CorrectionPos.FundamentalVal.L1[34];
	// Defender axis
	CorrectionPos.CorrectionPosition[2] := CorrectionPos.DifferenceYi.Y2[0]*CorrectionPos.FundamentalVal.L2[0]+CorrectionPos.DifferenceYi.Y2[1]*CorrectionPos.FundamentalVal.L2[1]+CorrectionPos.DifferenceYi.Y2[2]*CorrectionPos.FundamentalVal.L2[2]+CorrectionPos.DifferenceYi.Y2[3]*CorrectionPos.FundamentalVal.L2[3]+CorrectionPos.DifferenceYi.Y2[4]*CorrectionPos.FundamentalVal.L2[4]+CorrectionPos.DifferenceYi.Y2[5]*CorrectionPos.FundamentalVal.L2[5]
	+CorrectionPos.DifferenceYi.Y2[6]*CorrectionPos.FundamentalVal.L2[6]+CorrectionPos.DifferenceYi.Y2[7]*CorrectionPos.FundamentalVal.L2[7]+CorrectionPos.DifferenceYi.Y2[8]*CorrectionPos.FundamentalVal.L2[8]+CorrectionPos.DifferenceYi.Y2[9]*CorrectionPos.FundamentalVal.L2[9]+CorrectionPos.DifferenceYi.Y2[10]*CorrectionPos.FundamentalVal.L2[10]+CorrectionPos.DifferenceYi.Y2[11]*CorrectionPos.FundamentalVal.L2[11]+CorrectionPos.DifferenceYi.Y2[12]*CorrectionPos.FundamentalVal.L2[12]
	+CorrectionPos.DifferenceYi.Y2[13]*CorrectionPos.FundamentalVal.L2[13];
	// Attacker axis
	CorrectionPos.CorrectionPosition[3] := CorrectionPos.DifferenceYi.Y3[0]*CorrectionPos.FundamentalVal.L3[0]+CorrectionPos.DifferenceYi.Y3[1]*CorrectionPos.FundamentalVal.L3[1]+CorrectionPos.DifferenceYi.Y3[2]*CorrectionPos.FundamentalVal.L3[2]+CorrectionPos.DifferenceYi.Y3[3]*CorrectionPos.FundamentalVal.L3[3]+CorrectionPos.DifferenceYi.Y3[4]*CorrectionPos.FundamentalVal.L3[4]+CorrectionPos.DifferenceYi.Y3[5]*CorrectionPos.FundamentalVal.L3[5]+CorrectionPos.DifferenceYi.Y3[6]*CorrectionPos.FundamentalVal.L3[6]
	+CorrectionPos.DifferenceYi.Y3[7]*CorrectionPos.FundamentalVal.L3[7]+CorrectionPos.DifferenceYi.Y3[8]*CorrectionPos.FundamentalVal.L3[8]+CorrectionPos.DifferenceYi.Y3[9]*CorrectionPos.FundamentalVal.L3[9]+CorrectionPos.DifferenceYi.Y3[10]*CorrectionPos.FundamentalVal.L3[10]+CorrectionPos.DifferenceYi.Y3[11]*CorrectionPos.FundamentalVal.L3[11]+CorrectionPos.DifferenceYi.Y3[12]*CorrectionPos.FundamentalVal.L3[12]+CorrectionPos.DifferenceYi.Y3[13]*CorrectionPos.FundamentalVal.L3[13]
	+CorrectionPos.DifferenceYi.Y3[14]*CorrectionPos.FundamentalVal.L3[14]+CorrectionPos.DifferenceYi.Y3[15]*CorrectionPos.FundamentalVal.L3[15]+CorrectionPos.DifferenceYi.Y3[16]*CorrectionPos.FundamentalVal.L3[16]+CorrectionPos.DifferenceYi.Y3[17]*CorrectionPos.FundamentalVal.L3[17]+CorrectionPos.DifferenceYi.Y3[18]*CorrectionPos.FundamentalVal.L3[18]+CorrectionPos.DifferenceYi.Y3[19]*CorrectionPos.FundamentalVal.L3[19]+CorrectionPos.DifferenceYi.Y3[20]*CorrectionPos.FundamentalVal.L3[20];
	*)
	// Check the status of Reflex sensors if they work well (TRUE = figure block the balon; FALSE = figure open the way)
	FOR InternalPos.Index[1] := 0 TO 3 DO
				
		InternalPos.DR_ReflexSensStatus_0.ReflexSensStatusRS[InternalPos.Index[1]] := ReflexSensStatus[InternalPos.Index[1]];
	END_FOR;
	
	// Calling FB DetRot_ModulOK_0
	InternalPos.DR_ReflexSensStatus_0();
			
	// Calculation state compute an atual value of distance or set the max/min value       
	FOR InternalPos.Index[0] := 0 TO 3 DO
				
		// Set the External ModulOK value for case disfunction of
		ExternalReflexSensStatus[InternalPos.Index[0]] := InternalPos.DR_ReflexSensStatus_0.ExternalReflexSensStatusRS[InternalPos.Index[0]];
				
		// Optical sensor work well and values are in range and diference is over the minimal limit (compute a position by equation)
		IF (ErrorOptSens[InternalPos.Index[0]] = FALSE) AND ((ActPosSens[InternalPos.Index[0]] < InternalPos.MaxPosSens[InternalPos.Index[0]]) AND (ABS(ActPosSens[InternalPos.Index[0]] - InternalPos.CurrentPosition[InternalPos.Index[0]]) > InternalPos.MaxAccDiff[0])) AND ((ActPosSens[InternalPos.Index[0]] > InternalPos.MinPosSens[InternalPos.Index[0]]) AND (ABS(ActPosSens[InternalPos.Index[0]] - InternalPos.CurrentPosition[InternalPos.Index[0]]) > InternalPos.MaxAccDiff[0])) THEN
			ActPosHumBasic[InternalPos.Index[0]] := InternalPos.RefPosHum[InternalPos.Index[0]] + ((ActPosSens[InternalPos.Index[0]] - InternalPos.RefPosSens[InternalPos.Index[0]]) / InternalPos.TransConstant[InternalPos.Index[0]]); // Value of computed position without a correction
		
			(*
			// Compute a corrections for actual position
			FOR InternalPos.Index[4] := 0 TO 33 DO
				IF (CorrectionPos.ComputedPosition[InternalPos.Index[0]].Comp[InternalPos.Index[4]] < ActPosHumBasic[InternalPos.Index[0]] < CorrectionPos.ComputedPosition[InternalPos.Index[0]].Comp[InternalPos.Index[4]+1])  THEN
					InternalPos.Index[5] := InternalPos.Index[4];
					EXIT;
				END_IF;
			END_FOR;
			*)
			CorrectionPos.CorrectionPosition[InternalPos.Index[0]] := (((-1)*(CorrectionPos.ComputedPosition[InternalPos.Index[0]].Comp[InternalPos.Index[5]]-CorrectionPos.ComputedPosition[InternalPos.Index[0]].Comp[InternalPos.Index[5]+1])*(CorrectionPos.RealPositionMeasured[InternalPos.Index[0]].Meas[InternalPos.Index[5]]-ActPosHumBasic[InternalPos.Index[0]]))/(CorrectionPos.RealPositionMeasured[InternalPos.Index[0]].Meas[InternalPos.Index[5]]-CorrectionPos.RealPositionMeasured[InternalPos.Index[0]].Meas[InternalPos.Index[5]+1]));
				
			// Actual position after corrections
			ActPosHumAxis[InternalPos.Index[0]] := 	ActPosHumBasic[InternalPos.Index[0]]; // - CorrectionPos.CorrectionPosition[InternalPos.Index[0]]; // Corrected value of computed position
			InternalPos.CurrentPosition[InternalPos.Index[0]] := ActPosHumAxis[InternalPos.Index[0]]; // Last detected value is safed as previous value for case Error mode of sensor	
		
			// Optical sensor work well and values are in range and diference is in the minimal limit (set the previous value of position)
		ELSIF (ErrorOptSens[InternalPos.Index[0]] = FALSE) AND ((ActPosSens[InternalPos.Index[0]] < InternalPos.MaxPosSens[InternalPos.Index[0]]) AND (ABS(ActPosSens[InternalPos.Index[0]] - InternalPos.CurrentPosition[InternalPos.Index[0]]) < InternalPos.MaxAccDiff[0])) AND ((ActPosSens[InternalPos.Index[0]] > InternalPos.MinPosSens[InternalPos.Index[0]]) AND (ABS(ActPosSens[InternalPos.Index[0]] - InternalPos.CurrentPosition[InternalPos.Index[0]]) < InternalPos.MaxAccDiff[0])) THEN
			ActPosHumAxis[InternalPos.Index[0]]	:= InternalPos.CurrentPosition[InternalPos.Index[0]]; // Previous value of position
						
		// Optical sensor doesn't work well but values are in range
		ELSIF (ErrorOptSens[InternalPos.Index[0]] = TRUE) AND (ActPosSens[InternalPos.Index[0]] < InternalPos.MaxPosSens[InternalPos.Index[0]]) AND (ActPosSens[InternalPos.Index[0]] > InternalPos.MinPosSens[InternalPos.Index[0]]) THEN
			ActPosHumAxis[InternalPos.Index[0]] := 	InternalPos.CurrentPosition[InternalPos.Index[0]]; // Previous value of position
					
		// Optical sensor doesn't work well but values are over the maximum range
		ELSIF (ErrorOptSens[InternalPos.Index[0]] = TRUE) AND ((ActPosSens[InternalPos.Index[0]] > 500) OR (ActPosSens[InternalPos.Index[0]] < 8000))THEN
			ActPosHumAxis[InternalPos.Index[0]] := 	InternalPos.CurrentPosition[InternalPos.Index[0]]; // Previous value of position
							
		// Check if the Optical sensors are switched on (if not, sensored values are in range <-100 ; +100> _ the minimum limit sets InternalPos.MinAccDiff)
		ELSIF (ActPosSens[InternalPos.Index[0]] < InternalPos.MinAccDiff) THEN
			ActPosHumAxis[InternalPos.Index[0]] := 	InternalPos.RefPosHum[InternalPos.Index[0]]; // Due to a optical sensor fail set referent value of position by previous value of position
				
		// Check if the Reflex sensors doesn't block the ball (if does, the sensing of position is not required _ just a momentary status)
		ELSIF (ExternalReflexSensStatus[InternalPos.Index[0]] = FALSE) THEN
					ActPosHumAxis[InternalPos.Index[0]] := 	InternalPos.CurrentPosition[InternalPos.Index[0]]; // Due to a reflex sensor fail reset the actual value of position to the referent position
							
			// Actual human position is set as a last 
		ELSE
			ActPosHumAxis[InternalPos.Index[0]] := InternalPos.RefPosHum[InternalPos.Index[0]]; // Set referent position in all other cases as default
		END_IF
		
	END_FOR;
                		
	// Compute the positions all figures of opponent (by calling the function: DetPos_Figure)
	FOR InternalPos.Index[2] := 0 TO 3 DO
				
		// Set the input values into the function block
		InternalPos.DP_Figure_0.ActPosHumAxisDP[InternalPos.Index[2]] := ActPosHumAxis[InternalPos.Index[2]];
				
	END_FOR;
				
	// Call the function block
	InternalPos.DP_Figure_0();
	FOR InternalPos.Index[3] := 0 TO 10 DO
		
		// Call the output values of position all figures
 		ActPosHumFig[InternalPos.Index[3]] := InternalPos.DP_Figure_0.ActPosHumFigDP[InternalPos.Index[3]];
			
	END_FOR; 
	
END_FUNCTION_BLOCK


		(* NUMERIC CALCULATION OF POSITION ALL AXES *)
FUNCTION_BLOCK DetPos_Figure
			
	// Set the value at position of Goalman Axis by the Actual Position of Axis with Displacement of Axis
	IF (ActPosHumAxisDP[0] < InternalPosFig.MaxPosHumDP[0]) AND (ActPosHumAxisDP[0] > InternalPosFig.MinPosHumDP[0]) THEN
		ActPosHumFigDP[0] := ActPosHumAxisDP[0] + InternalPosFig.DispAxisDP[0];
		InternalPosFig.CurrentPosition[0] := ActPosHumFigDP[0];
	// 	
	ELSIF ActPosHumAxisDP[0] > InternalPosFig.MaxPosHumDP[0] THEN
		ActPosHumFigDP[0] := InternalPosFig.MaxPosHumDP[0];
		
	//	
	ELSIF ActPosHumAxisDP[0] < InternalPosFig.MinPosHumDP[0] THEN
		ActPosHumFigDP[0] := InternalPosFig.MinPosHumDP[0];
		
	// 	
	ELSE
		ActPosHumFigDP[0] := ActPosHumAxisDP[0] + InternalPosFig.DispAxisDP[0];
	END_IF
				
	FOR InternalPosFig.Index[0] := 1 TO 2 DO
		// Set the value at position of Defender Axis by the Actual Position of Axis with Displacement of Axis
		IF (ActPosHumAxisDP[1] < InternalPosFig.MaxPosHumDP[1]) AND (ActPosHumAxisDP[1] > InternalPosFig.MinPosHumDP[1]) THEN
			ActPosHumFigDP[InternalPosFig.Index[0]] := ActPosHumAxisDP[1] + InternalPosFig.DispAxisDP[InternalPosFig.Index[0]];
			InternalPosFig.CurrentPosition[InternalPosFig.Index[0]] := ActPosHumFigDP[InternalPosFig.Index[0]];
		// 	
		ELSIF ActPosHumAxisDP[1] > InternalPosFig.MaxPosHumDP[1] THEN
			ActPosHumFigDP[InternalPosFig.Index[0]] := InternalPosFig.MaxPosHumDP[1] + InternalPosFig.DispAxisDP[InternalPosFig.Index[0]];
			
		// 	
		ELSIF ActPosHumAxisDP[1] < InternalPosFig.MinPosHumDP[1] THEN
			ActPosHumFigDP[InternalPosFig.Index[0]] := InternalPosFig.MinPosHumDP[1] + InternalPosFig.DispAxisDP[InternalPosFig.Index[0]];
			
		// 	
		ELSE
			ActPosHumFigDP[InternalPosFig.Index[0]] := 	InternalPosFig.CurrentPosition[InternalPosFig.Index[0]];
		END_IF

	END_FOR;
	
	FOR InternalPosFig.Index[1] := 3 TO 7 DO
		// Set the value at position of Middle Defender Axis by the Actual Position of Axis with Displacement of Axis
		IF (ActPosHumAxisDP[2] < InternalPosFig.MaxPosHumDP[2]) AND (ActPosHumAxisDP[2] > InternalPosFig.MinPosHumDP[2]) THEN
			ActPosHumFigDP[InternalPosFig.Index[1]] := ActPosHumAxisDP[2] + InternalPosFig.DispAxisDP[InternalPosFig.Index[1]];
			InternalPosFig.CurrentPosition[InternalPosFig.Index[1]] := ActPosHumFigDP[InternalPosFig.Index[1]];
		// 	
		ELSIF ActPosHumAxisDP[2] > InternalPosFig.MaxPosHumDP[2] THEN
			ActPosHumFigDP[InternalPosFig.Index[1]] := InternalPosFig.MaxPosHumDP[2] + InternalPosFig.DispAxisDP[InternalPosFig.Index[1]];
			
		// 	
		ELSIF ActPosHumAxisDP[2] < InternalPosFig.MinPosHumDP[2] THEN
			ActPosHumFigDP[InternalPosFig.Index[1]] := InternalPosFig.MinPosHumDP[2] + InternalPosFig.DispAxisDP[InternalPosFig.Index[1]];
		
		// 
		ELSE
			ActPosHumFigDP[InternalPosFig.Index[1]] := InternalPosFig.CurrentPosition[InternalPosFig.Index[1]];
		END_IF

	END_FOR; 
	
	FOR InternalPosFig.Index[2] := 8 TO 10 DO
		// Set the value at position of Forward Axis by the Actual Position of Axis with Displacement of Axis
		IF (ActPosHumAxisDP[3] < InternalPosFig.MaxPosHumDP[3]) AND (ActPosHumAxisDP[3] > InternalPosFig.MinPosHumDP[3]) THEN
			ActPosHumFigDP[InternalPosFig.Index[2]] := ActPosHumAxisDP[3]+ InternalPosFig.DispAxisDP[InternalPosFig.Index[2]];
			InternalPosFig.CurrentPosition[InternalPosFig.Index[2]] := ActPosHumFigDP[InternalPosFig.Index[2]];
		// 	
		ELSIF ActPosHumAxisDP[3] > InternalPosFig.MaxPosHumDP[3] THEN
			ActPosHumFigDP[InternalPosFig.Index[2]] := InternalPosFig.MaxPosHumDP[3] + InternalPosFig.DispAxisDP[InternalPosFig.Index[2]];
			
		// 	
		ELSIF ActPosHumAxisDP[3] < InternalPosFig.MinPosHumDP[3] THEN
			ActPosHumFigDP[InternalPosFig.Index[2]] := InternalPosFig.MinPosHumDP[3] + InternalPosFig.DispAxisDP[InternalPosFig.Index[2]];
		
		// 
		ELSE
			ActPosHumFigDP[InternalPosFig.Index[2]] := InternalPosFig.CurrentPosition[InternalPosFig.Index[2]];
		END_IF

	END_FOR; 
	
END_FUNCTION_BLOCK 

