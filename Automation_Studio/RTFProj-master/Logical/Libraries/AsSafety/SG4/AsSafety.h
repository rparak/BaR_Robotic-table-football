/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _ASSAFETY_
#define _ASSAFETY_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#include <runtime.h>
#include <standard.h>
#include <astime.h>
#include <FileIO.h>
#include <AsXml.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Constants */
#ifdef _REPLACE_CONST
 #define safeERR_COT_READING_FILE 36131U
 #define safeERR_COT_TYPE_ERR 36130U
 #define safeERR_DLDATA_ERR_DATA 36129U
 #define safeERR_DLDATA_TYPE_ERR 36128U
 #define safeERR_DL_COMPARE_FAILED 36127U
 #define safeERR_DL_STATIC_UNLOCK 36126U
 #define safeERR_DL_UNLOCK_WRITE 36125U
 #define safeERR_DL_UNLOCK_READ 36124U
 #define safeERR_DL_UNLOCK_FILE_INFO 36123U
 #define safeERR_DL_NO_RIGHTS_TO_WRITE 36122U
 #define safeERR_DL_WRONG_FILE_SIZE 36121U
 #define safeERR_DL_UDID 36120U
 #define safeERR_DL_CHECKSUM 36119U
 #define safeERR_DL_STREAM 36118U
 #define safeERR_DL_WRITE 36117U
 #define safeERR_DL_FILE_TOO_BIG 36116U
 #define safeERR_DL_FILE_INVALID 36115U
 #define safeERR_DL_FILE_OPEN 36114U
 #define safeERR_DL_PROTOCOL 36113U
 #define safeERR_DL_NO_PASSWORD 36112U
 #define safeERR_RC_DATA_LENGTH 36111U
 #define safeERR_RC_STATUS_DATA 36110U
 #define safeERR_RC_ENTER_SK_PW 36109U
 #define safeERR_RC_ENTER_PW 36108U
 #define safeERR_RC_ENTER_DATA 36107U
 #define safeERR_RC_CMD 36106U
 #define safeERR_TIMEOUT 36105U
 #define safeERR_INTERNAL_ERROR 36104U
 #define safeERR_ALLOC_MEM 36103U
 #define safeERR_UDID 36102U
 #define safeERR_PW_LENGTH 36101U
 #define safeERR_VERSION 36100U
 #define safeCMD_CLEAR_DATA 32768U
 #define safeCMD_RESET 28672U
 #define safeCMD_SK_FORMAT 24576U
 #define safeCMD_SK_PW 20480U
 #define safeCMD_SCAN 8192U
 #define safeCMD_TEST 4096U
 #define safeCMD_SK_XCHG 512U
 #define safeCMD_FW_ACKN 256U
 #define safeCMD_1_UDID_ACKN 96U
 #define safeCMD_2_UDID_ACKN 80U
 #define safeCMD_3_UDID_ACKN 64U
 #define safeCMD_4_UDID_ACKN 48U
 #define safeCMD_N_UDID_ACKN 32U
 #define safeCMD_STATUS_SL 0U
 #define safeCMD_STATUS 512U
 #define safeCMD_ENTER 256U
 #define safeDATA_TYPE_ADDPARA 1024U
 #define safeDATA_TYPE_TABLE 768U
 #define safeDATA_TYPE_EXTMAOP 512U
 #define safeDATA_TYPE_MAOP 256U
 #define safeVERSION_R107 263U
#else
 #ifndef _GLOBAL_CONST
   #define _GLOBAL_CONST _WEAK const
 #endif
 _GLOBAL_CONST unsigned short safeERR_COT_READING_FILE;
 _GLOBAL_CONST unsigned short safeERR_COT_TYPE_ERR;
 _GLOBAL_CONST unsigned short safeERR_DLDATA_ERR_DATA;
 _GLOBAL_CONST unsigned short safeERR_DLDATA_TYPE_ERR;
 _GLOBAL_CONST unsigned short safeERR_DL_COMPARE_FAILED;
 _GLOBAL_CONST unsigned short safeERR_DL_STATIC_UNLOCK;
 _GLOBAL_CONST unsigned short safeERR_DL_UNLOCK_WRITE;
 _GLOBAL_CONST unsigned short safeERR_DL_UNLOCK_READ;
 _GLOBAL_CONST unsigned short safeERR_DL_UNLOCK_FILE_INFO;
 _GLOBAL_CONST unsigned short safeERR_DL_NO_RIGHTS_TO_WRITE;
 _GLOBAL_CONST unsigned short safeERR_DL_WRONG_FILE_SIZE;
 _GLOBAL_CONST unsigned short safeERR_DL_UDID;
 _GLOBAL_CONST unsigned short safeERR_DL_CHECKSUM;
 _GLOBAL_CONST unsigned short safeERR_DL_STREAM;
 _GLOBAL_CONST unsigned short safeERR_DL_WRITE;
 _GLOBAL_CONST unsigned short safeERR_DL_FILE_TOO_BIG;
 _GLOBAL_CONST unsigned short safeERR_DL_FILE_INVALID;
 _GLOBAL_CONST unsigned short safeERR_DL_FILE_OPEN;
 _GLOBAL_CONST unsigned short safeERR_DL_PROTOCOL;
 _GLOBAL_CONST unsigned short safeERR_DL_NO_PASSWORD;
 _GLOBAL_CONST unsigned short safeERR_RC_DATA_LENGTH;
 _GLOBAL_CONST unsigned short safeERR_RC_STATUS_DATA;
 _GLOBAL_CONST unsigned short safeERR_RC_ENTER_SK_PW;
 _GLOBAL_CONST unsigned short safeERR_RC_ENTER_PW;
 _GLOBAL_CONST unsigned short safeERR_RC_ENTER_DATA;
 _GLOBAL_CONST unsigned short safeERR_RC_CMD;
 _GLOBAL_CONST unsigned short safeERR_TIMEOUT;
 _GLOBAL_CONST unsigned short safeERR_INTERNAL_ERROR;
 _GLOBAL_CONST unsigned short safeERR_ALLOC_MEM;
 _GLOBAL_CONST unsigned short safeERR_UDID;
 _GLOBAL_CONST unsigned short safeERR_PW_LENGTH;
 _GLOBAL_CONST unsigned short safeERR_VERSION;
 _GLOBAL_CONST unsigned short safeCMD_CLEAR_DATA;
 _GLOBAL_CONST unsigned short safeCMD_RESET;
 _GLOBAL_CONST unsigned short safeCMD_SK_FORMAT;
 _GLOBAL_CONST unsigned short safeCMD_SK_PW;
 _GLOBAL_CONST unsigned short safeCMD_SCAN;
 _GLOBAL_CONST unsigned short safeCMD_TEST;
 _GLOBAL_CONST unsigned short safeCMD_SK_XCHG;
 _GLOBAL_CONST unsigned short safeCMD_FW_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_1_UDID_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_2_UDID_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_3_UDID_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_4_UDID_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_N_UDID_ACKN;
 _GLOBAL_CONST unsigned short safeCMD_STATUS_SL;
 _GLOBAL_CONST unsigned short safeCMD_STATUS;
 _GLOBAL_CONST unsigned short safeCMD_ENTER;
 _GLOBAL_CONST unsigned short safeDATA_TYPE_ADDPARA;
 _GLOBAL_CONST unsigned short safeDATA_TYPE_TABLE;
 _GLOBAL_CONST unsigned short safeDATA_TYPE_EXTMAOP;
 _GLOBAL_CONST unsigned short safeDATA_TYPE_MAOP;
 _GLOBAL_CONST unsigned short safeVERSION_R107;
#endif




/* Datatypes and datatypes of function blocks */
typedef struct RemoteControlCmdTypeV1
{	unsigned short Version;
	unsigned short Command;
	unsigned short Number;
	unsigned short Data;
	plcstring Password[17];
	plcstring NewPassword[17];
} RemoteControlCmdTypeV1;

typedef struct DownloadCmdMaOpTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long UDID_Low;
	unsigned short UDID_High;
	unsigned char Unlock;
	unsigned long pDeviceListInput;
	unsigned short NumberDevicesInput;
	unsigned long pMachineOptionsInput;
	unsigned long pModuleFlagsInput;
	unsigned long pAcknMachineOptions;
	unsigned long pDeviceListOutput;
	unsigned short NumberDevicesOutput;
	unsigned long pMachineOptionsOutput;
	unsigned long pModuleFlagsOutput;
} DownloadCmdMaOpTypeV1;

typedef struct DownloadDeviceTypeV1
{	unsigned short SADR;
	unsigned long UDID_Low;
	unsigned short UDID_High;
} DownloadDeviceTypeV1;

typedef struct ConfigurationDeviceTypeV1
{	unsigned short SADR;
	unsigned char UDID[6];
} ConfigurationDeviceTypeV1;

typedef struct ConfigurationBitOptionsTypeV1
{	unsigned char BitData[64];
} ConfigurationBitOptionsTypeV1;

typedef struct ConfigurationModuleFlagsTypeV1
{	unsigned char Optional[128];
	unsigned char Startup[128];
	unsigned char NotPresent[128];
} ConfigurationModuleFlagsTypeV1;

typedef struct DownloadCmdExtMaOpTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long UDID_Low;
	unsigned short UDID_High;
	unsigned char Unlock;
	unsigned long pIntDataInput;
	unsigned short NumberIntInput;
	unsigned long pUintDataInput;
	unsigned short NumberUintInput;
	unsigned long pDintDataInput;
	unsigned short NumberDintInput;
	unsigned long pUdintDataInput;
	unsigned short NumberUdintInput;
	unsigned long pAcknMachineOptions;
	unsigned long pIntDataOutput;
	unsigned short NumberIntOutput;
	unsigned long pUintDataOutput;
	unsigned short NumberUintOutput;
	unsigned long pDintDataOutput;
	unsigned short NumberDintOutput;
	unsigned long pUdintDataOutput;
	unsigned short NumberUdintOutput;
} DownloadCmdExtMaOpTypeV1;

typedef struct ConfigurationIntOptionsTypeV1
{	unsigned short ID;
	signed short Value;
} ConfigurationIntOptionsTypeV1;

typedef struct ConfigurationUintOptionsTypeV1
{	unsigned short ID;
	unsigned short Value;
} ConfigurationUintOptionsTypeV1;

typedef struct ConfigurationDintOptionsTypeV1
{	unsigned short ID;
	signed long Value;
} ConfigurationDintOptionsTypeV1;

typedef struct ConfigurationUdintOptionsTypeV1
{	unsigned short ID;
	unsigned long Value;
} ConfigurationUdintOptionsTypeV1;

typedef struct DownloadCmdTableTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long UDID_Low;
	unsigned short UDID_High;
	unsigned char Unlock;
	unsigned long pTableDataInput;
	unsigned short NumberTablesInput;
	unsigned long pTableDataOutput;
	unsigned short NumberTablesOutput;
} DownloadCmdTableTypeV1;

typedef struct DownloadCmdAddParaTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long UDID_Low;
	unsigned short UDID_High;
	unsigned char Unlock;
	unsigned long pParaListInput;
	unsigned short NumberParaSetsInput;
	unsigned long pParaDataOutput;
	unsigned short NumberParaSetsOutput;
} DownloadCmdAddParaTypeV1;

typedef struct DownloadTableTypeV1
{	plcstring Device[81];
	plcstring File[81];
} DownloadTableTypeV1;

typedef struct ConfigurationTableTypeV1
{	unsigned short ID;
	unsigned char Type;
	unsigned short NumberOfCRCs;
	unsigned long pCRCData;
} ConfigurationTableTypeV1;

typedef struct DownloadAddParaTypeV1
{	unsigned short SADR;
	unsigned char ID;
	unsigned long pParaData;
	unsigned long Length;
	unsigned long pAcknAddPara;
} DownloadAddParaTypeV1;

typedef struct ConfigurationAddParaTypeV1
{	unsigned short SADR;
	unsigned char ID;
	unsigned long pParaData;
	unsigned long Length;
	unsigned long CRC;
	unsigned long Timestamp;
} ConfigurationAddParaTypeV1;

typedef struct DownloadCmdApplicationTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long UDID_Low;
	unsigned short UDID_High;
	unsigned short ApplicationID;
	plcstring Device[81];
	plcstring File[81];
	unsigned char Unlock;
} DownloadCmdApplicationTypeV1;

typedef struct ConfigurationCmdMaOpTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long pDeviceListOutput;
	unsigned short NumberDevicesOutput;
	unsigned long pMachineOptionsOutput;
	unsigned long pModuleFlagsOutput;
} ConfigurationCmdMaOpTypeV1;

typedef struct ConfigurationCmdExtMaOpTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long pIntDataOutput;
	unsigned short NumberIntOutput;
	unsigned long pUintDataOutput;
	unsigned short NumberUintOutput;
	unsigned long pDintDataOutput;
	unsigned short NumberDintOutput;
	unsigned long pUdintDataOutput;
	unsigned short NumberUdintOutput;
} ConfigurationCmdExtMaOpTypeV1;

typedef struct ConfigurationCmdTableTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long pTableDataOutput;
	unsigned short NumberTablesOutput;
} ConfigurationCmdTableTypeV1;

typedef struct ConfigurationCmdAddParaTypeV1
{	unsigned short Version;
	plcstring Password[17];
	unsigned long pParaDataOutput;
	unsigned short NumberParaSetsOutput;
} ConfigurationCmdAddParaTypeV1;

typedef struct RemoteControlStatusTypeV1
{	unsigned short Command;
	unsigned short Number;
	unsigned short Status;
	unsigned short State;
	unsigned short EnterData;
	unsigned short EnterNumber;
	unsigned short EnterExecuteStatus;
	unsigned char SafeOSState;
	unsigned char SafeKEYChanged;
	unsigned char LedTestActive;
	unsigned char Scanning;
	unsigned char openSAFETYstate;
	unsigned char FailSafe;
	unsigned short NumberOfMissingModules;
	unsigned short NumberOfUDIDMismatches;
	unsigned short NumberOfDifferentFirmware;
	unsigned short SADR[101];
	unsigned char MissingModules[16];
	unsigned char UDIDMismatches[16];
	unsigned char DifferentFirmware[16];
} RemoteControlStatusTypeV1;

typedef struct DownloadAcknMaOpTypeV1
{	unsigned char AcknBitOptions[64];
} DownloadAcknMaOpTypeV1;

typedef struct DownloadAcknAddParaTypeV1
{	unsigned char AcknBitAddPara[64];
} DownloadAcknAddParaTypeV1;

typedef struct DownloadAcknExtMaOpTypeV1
{	plcbit AcknIntOptions[64];
	plcbit AcknUintOptions[64];
	plcbit AcknDintOptions[64];
	plcbit AcknUdintOptions[64];
} DownloadAcknExtMaOpTypeV1;

typedef struct safeRemoteControl
{
	/* VAR_INPUT (analog) */
	unsigned short SafeLOGICID;
	unsigned long pCommandData;
	/* VAR_OUTPUT (analog) */
	unsigned short StatusID;
	struct RemoteControlStatusTypeV1 SafeLOGICStatus;
	/* VAR (analog) */
	unsigned short i_state;
	unsigned short i_result;
	unsigned long i_tmp;
	unsigned long i_handle;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} safeRemoteControl_typ;

typedef struct safeDownloadApplication
{
	/* VAR_INPUT (analog) */
	unsigned short SafeLOGICID;
	unsigned long pCommandData;
	/* VAR_OUTPUT (analog) */
	unsigned short StatusID;
	unsigned long ApplicationCRC;
	/* VAR (analog) */
	unsigned short i_state;
	unsigned short i_result;
	unsigned long i_tmp;
	unsigned long i_handle;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
	plcbit UnlockRequired;
} safeDownloadApplication_typ;

typedef struct safeDownloadData
{
	/* VAR_INPUT (analog) */
	unsigned short SafeLOGICID;
	unsigned short Type;
	unsigned long pCommandData;
	/* VAR_OUTPUT (analog) */
	unsigned short StatusID;
	unsigned long Timestamp;
	/* VAR (analog) */
	unsigned short i_state;
	unsigned short i_result;
	unsigned long i_tmp;
	unsigned long i_handle;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
	plcbit UnlockRequired;
} safeDownloadData_typ;

typedef struct safeConfigurationOnTarget
{
	/* VAR_INPUT (analog) */
	unsigned short SafeLOGICID;
	unsigned short Type;
	unsigned long pCommandData;
	/* VAR_OUTPUT (analog) */
	unsigned short StatusID;
	unsigned long Timestamp;
	/* VAR (analog) */
	unsigned short i_state;
	unsigned short i_result;
	unsigned long i_tmp;
	unsigned long i_handle;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} safeConfigurationOnTarget_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void safeRemoteControl(struct safeRemoteControl* inst);
_BUR_PUBLIC void safeDownloadApplication(struct safeDownloadApplication* inst);
_BUR_PUBLIC void safeDownloadData(struct safeDownloadData* inst);
_BUR_PUBLIC void safeConfigurationOnTarget(struct safeConfigurationOnTarget* inst);
_BUR_PUBLIC unsigned short safeLibraryVersion(void);


#ifdef __cplusplus
};
#endif
#endif /* _ASSAFETY_ */

