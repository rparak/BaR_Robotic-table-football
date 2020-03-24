/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _ASWSTR_
#define _ASWSTR_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Constants */
#ifdef _REPLACE_CONST
 #define U8toUC 0U
 #define UCtoU8 1U
#else
 #ifndef _GLOBAL_CONST
   #define _GLOBAL_CONST _WEAK const
 #endif
 _GLOBAL_CONST unsigned char U8toUC;
 _GLOBAL_CONST unsigned char UCtoU8;
#endif







/* Prototyping of functions and function blocks */
_BUR_PUBLIC unsigned long wcsconv(unsigned char* pDestination, unsigned char* pSource, unsigned char level);
_BUR_PUBLIC unsigned long wcsncpy(unsigned short* pDestination, unsigned short* pSource, unsigned long n);
_BUR_PUBLIC unsigned long wcsncat(unsigned short* pDestination, unsigned short* pSource, unsigned long n);
_BUR_PUBLIC unsigned long wcscat(unsigned short* pDestination, unsigned short* pSource);
_BUR_PUBLIC signed long wcscmp(unsigned short* pUcstr1, unsigned short* pUcstr2);
_BUR_PUBLIC unsigned long wcslen(unsigned short* pwcString);
_BUR_PUBLIC unsigned long wcsset(unsigned short* pDestination, unsigned long len, unsigned short symbol);
_BUR_PUBLIC signed long wcsncmp(unsigned short* pwcString1, unsigned short* pwcString2, unsigned long n);
_BUR_PUBLIC unsigned long wcscpy(unsigned short* pDestination, unsigned short* pSource);
_BUR_PUBLIC unsigned long wcsrchr(unsigned short* pDestination, unsigned short symbol);
_BUR_PUBLIC unsigned long wcschr(unsigned short* pDestination, unsigned short symbol);


#ifdef __cplusplus
};
#endif
#endif /* _ASWSTR_ */

