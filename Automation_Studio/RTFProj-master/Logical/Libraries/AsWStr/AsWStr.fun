(********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: AsWStr
 * File: AsWStr.fun
 * Author: B+R
 ********************************************************************
 * Functions and function blocks of library AsWStr
 ********************************************************************)
                                                                      
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsconv : UDINT						(*converts one string to a different format*)
	VAR_INPUT	
		pDestination	:REFERENCE TO USINT;	(*string to be appended to, given as a pointer*)
		pSource	:REFERENCE TO USINT;			(*string to be appended, given as a pointer*)
		level	:USINT;							(*U8toUC (= 0) if converting from U8 to UC; UCtoU8 (= 1) if converting from UC to U8*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsncpy : UDINT						(*copies a maximum of n characters from the pSource WC string to the pDestination address*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*pointer to the target memory for the string*)
		pSource	:REFERENCE TO UINT;				(*string to be copied, given as a pointer*)
		n	:UDINT;								(*max. number of characters to be copied*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsncat : UDINT						(*appends a maximum of n characters from the pSource string to the pDestination string*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*string to be appended to, given as a pointer*)
		pSource	:REFERENCE TO UINT;				(*string to be appended, given as a pointer*)
		n	:UDINT;								(*maximum number of characters to be added from pSource to pDestination*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcscat : UDINT							(*connects two WC strings to each other (concatenation)*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*string to be appended to, given as a pointer*)
		pSource	:REFERENCE TO UINT;				(*string to be appended, given as a pointer*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcscmp : DINT							(*compares two 16-bit character strings*)
	VAR_INPUT
		pUcstr1	:REFERENCE TO UINT;				(*first string, given as a pointer*)
		pUcstr2	:REFERENCE TO UINT;				(*second string, given as a pointer*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcslen : UDINT							(*determines the length of a WC string*)
	VAR_INPUT
		pwcString	:REFERENCE TO UINT;			(*string whose length should be determined, given as a pointer*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsset : UDINT							(*appends the pSource string to the pDestination string*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*string being written, given as a pointer*)
		len	:UDINT;								(*number of characters to be written*)
		symbol	:UINT;							(*character used to overwrite*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsncmp : DINT							(*compares two 16-bit strings*)
	VAR_INPUT
		pwcString1	:REFERENCE TO UINT;			(*first string given as a pointer*)
		pwcString2	:REFERENCE TO UINT;			(*second string given as a pointer*)
		n	:UDINT;								(*max. number of characters from pUcstr1 to be compared with pUcstr2*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcscpy : UDINT							(*copies a WC string*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*pointer to the target memory for the string*)
		pSource	:REFERENCE TO UINT;				(*string to be copied, given as a pointer*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcsrchr : UDINT						(*searches for the last occurrence of a certain character in a WC string*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*character string being searched, given as a pointer*)
		symbol	:UINT;							(*character being looked for*)
	END_VAR
END_FUNCTION
{REDUND_OK} {REDUND_UNREPLICABLE} FUNCTION wcschr : UDINT							(*searches for the first occurrence of a certain character*)
	VAR_INPUT
		pDestination	:REFERENCE TO UINT;		(*string given as a pointer*)
		symbol	:UINT;							(*character being looked for*)
	END_VAR
END_FUNCTION
