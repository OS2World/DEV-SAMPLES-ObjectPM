/*  VCS_ID
 *  $Filename:   basedefs.h
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
//+*****************************************************************************
//
//	VERSION:  $Revision$
//	          $Date$
//
//	MODULE:   basedefs.h
//	AUTHOR:   John Pompeii
//	FACILITY: BaseSet class library
//
//	DESCRIPTION:
//
//		This module contains all the base defines needed so that the
//		base system header files will not need to be included by apps 
//
//-*****************************************************************************

#ifndef __BASEDEFS_H__
#define __BASEDEFS_H__

typedef unsigned char   uchar;
typedef signed char     schar;
typedef unsigned short  ushort;
typedef unsigned long   ulong;
typedef unsigned long   bool;
typedef unsigned char   byte;

#undef NULL
#define NULL (0)

#if defined(__BORLANDC__)
    #ifndef APIENTRY
        #define APIENTRY    _syscall
        #define EXPENTRY    _syscall
    #endif
    #define _Optlink
    #define _EXPORT_ 
    #define PASCAL  _pascal 
#elif defined(__IBMC__) || defined(__IBMCPP__)
    #ifndef APIENTRY
        #define APIENTRY    _System
        #define EXPENTRY    _System
    #endif
    #define cdecl _Optlink
    #define _EXPORT_	
    #define PASCAL  _Pascal 
    #define strcmpi stricmp
    #define strncmpi strnicmp
#elif defined(__HIGHC__)
	#ifndef APIENTRY
		#define APIENTRY
		#define EXPENTRY
	#endif
	#define _EXPORT_
    #define _Optlink
	#define cdecl _CC((_DEFAULT_CALLING_CONVENTION|_REVERSE_PARMS|_OVERLOADED) & ~(_CALLEE_POPS_STACK) )
	#define PASCAL _CC((_DEFAULT_CALLING_CONVENTION|_CALLEE_POPS_STACK) & ~(_REVERSE_PARMS|_OVERLOADED) )
#elif defined(__WATCOMC__)
	#ifndef APIENTRY
        #define APIENTRY    __syscall
        #define EXPENTRY    __syscall
	#endif
    #define _EXPORT_
    #define _Optlink
	#define PASCAL     __pascal
#endif

#ifndef OS2DEF_INCLUDED

#ifndef FALSE
   #define FALSE   0
#endif

#ifndef TRUE
   #define TRUE    1
#endif

typedef unsigned short   SHANDLE;
typedef unsigned long    LHANDLE;
typedef LHANDLE HAB;
typedef LHANDLE HMQ;
typedef LHANDLE TID;
typedef LHANDLE PID;
typedef LHANDLE HMODULE;
typedef LHANDLE HPS;
typedef LHANDLE HDC;
typedef LHANDLE HMF;
typedef LHANDLE HRGN;
typedef LHANDLE HBITMAP;
typedef LHANDLE HWND;
typedef LHANDLE HFILE;
typedef LHANDLE HDIR;
typedef LHANDLE HINI;

#define NULLHANDLE    ( (LHANDLE) 0)
#define NULLSHANDLE   ( (SHANDLE) 0)

#define VOID    void
#define CHAR    char
#define SHORT   short
#define LONG    long
#define INT     int

typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned int   UINT;
typedef unsigned long  ULONG;

typedef unsigned char BYTE;

typedef BYTE *PBYTE;
typedef BYTE *NPBYTE;

typedef CHAR *PCHAR;
typedef SHORT *PSHORT;
typedef LONG *PLONG;

typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG *PULONG;

typedef VOID   *PVOID;
typedef PVOID  *PPVOID;

typedef unsigned long BOOL;
typedef BOOL *PBOOL;

typedef char *PDEVOPENDATA;

#endif /* OS2DEF_INCLUDED */

// alarm options
enum AlarmType {
	WarningAlarm,
	NoteAlarm,
	ErrorAlarm
};

#endif /* __BASEDEFS_H__  */


