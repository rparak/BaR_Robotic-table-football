(********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * File: Global.typ
 * Author: Bernecker + Rainer
 * Created: June 02, 2008
 ********************************************************************
 * Global data types of project LibAsUDP
 ********************************************************************)

TYPE
	LibAsUDP1_ST_typ : 	STRUCT  (*Datatyp for global Variables*)
		receive_data : STRING[500]; (*adress arguments*)
		send_data : STRING[500]; (*Data which should be sent*)
	END_STRUCT;
END_TYPE
