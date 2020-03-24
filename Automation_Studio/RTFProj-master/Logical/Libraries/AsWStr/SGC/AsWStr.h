/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _ASWSTR_
#define _ASWSTR_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#ifndef _IEC_CONST
#define _IEC_CONST _WEAK const
#endif

/* Constants */
#ifdef _REPLACE_CONST
 #define UCtoU8 1U
 #define U8toUC 0U
#else
 _IEC_CONST unsigned char UCtoU8 = 1U;
 _IEC_CONST unsigned char U8toUC = 0U;
#endif







/* Prototyping of functions and function blocks */
unsigned long wcsconv(unsigned char* pDestination, unsigned char* pSource, unsigned char level);
unsigned long wcsncpy(unsigned short* pDestination, unsigned short* pSource, unsigned long n);
unsigned long wcsncat(unsigned short* pDestination, unsigned short* pSource, unsigned long n);
unsigned long wcscat(unsigned short* pDestination, unsigned short* pSource);
signed long wcscmp(unsigned short* pUcstr1, unsigned short* pUcstr2);
unsigned long wcslen(unsigned short* pwcString);
unsigned long wcsset(unsigned short* pDestination, unsigned long len, unsigned short symbol);
signed long wcsncmp(unsigned short* pwcString1, unsigned short* pwcString2, unsigned long n);
unsigned long wcscpy(unsigned short* pDestination, unsigned short* pSource);
unsigned long wcsrchr(unsigned short* pDestination, unsigned short symbol);
unsigned long wcschr(unsigned short* pDestination, unsigned short symbol);


#ifdef __cplusplus
};
#endif
#endif /* _ASWSTR_ */

                                                           
