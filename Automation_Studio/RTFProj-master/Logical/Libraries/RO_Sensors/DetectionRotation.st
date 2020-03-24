
(* LOGIC PREDICTION OF ROTATION ALL AXES *)
FUNCTION_BLOCK DetectionRotation
		
	// Checking the status of reflex sensor 
	FOR InternalRot.IndexR[0] := 0 TO 3 DO
	
		// Reflex sensor works & Modul set TRUE to output
		IF (ReflexSensStatusRS[InternalRot.IndexR[0]] = TRUE) AND (ErrorReflSensRS[InternalRot.IndexR[0]] = FALSE) THEN
			ActReflRotRS[InternalRot.IndexR[0]] := ReflexSensStatusRS[InternalRot.IndexR[0]];
		
		// Reflex sensor works but Modul set FALSE to output	
		ELSIF (ReflexSensStatusRS[InternalRot.IndexR[0]] = FALSE) AND (ErrorReflSensRS[InternalRot.IndexR[0]] = FALSE) THEN
				ActReflRotRS[InternalRot.IndexR[0]] := ReflexSensStatusRS[InternalRot.IndexR[0]];
		
			// Reflex sensor doesn't works 	
		ELSIF (ErrorReflSensRS[InternalRot.IndexR[0]] = TRUE) THEN
			ActReflRotRS[InternalRot.IndexR[0]] := FALSE;
		
		// 	Set the status of Actual position of Rotation by the ModulOK status
		ELSE
			ActReflRotRS[InternalRot.IndexR[0]] := ReflexSensStatusRS[InternalRot.IndexR[0]];
		END_IF       
	END_FOR
	

END_FUNCTION_BLOCK
