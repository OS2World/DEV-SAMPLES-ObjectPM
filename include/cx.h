/*  VCS_ID
 *  $Filename:   cx.h
 *  $Author  :   John Pompeii  
 *  $Revision:   1.2  $
 *  $Date:   16 Jan 1992 19:28:40  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __CX_H
#define __CX_H 

#if defined(__cplusplus)
extern "C" {
#endif

/* general purpose c modules */

char * cdecl strend(const char *);
char * cdecl strnccp(char *, const char *, int);
int    cdecl stridx(const char *, unsigned char);
int    cdecl strblank(const char *);
char * cdecl strsetn(char *, unsigned char, int);
int    cdecl strcnt(const char *, unsigned char);
char * cdecl strstrip(char *);
char * cdecl strestrip(char *);
char * cdecl strdel(char *, int);
char * cdecl strins(char *, const char *);
char * cdecl strpad(char *, int);
int    cdecl strlist(char **, const char *, int);
int    cdecl strval(const char *, unsigned char);
char * cdecl strpad(char *, int);
char * cdecl strzstrip(char *cp);	
char * cdecl strcstrp(char *s, char c);
char * cdecl strccpy(char *s1, register const char *s2, register char n);
char * cdecl strcpytok(register char *s1, register const char *s2, const char *tok);
char * cdecl strchrn(register const char *string, int c, register int cnt);
int    cdecl stridxs(const char *s, const char *t);
char * cdecl strtoken(char** source, const char *seperators);

void * cpp_malloc(unsigned short siz);
void   cpp_free(void *mem);
char * cpp_strdup(const char *string);

/* system stuff.... */

short  cdecl getdrive(void);
char * cdecl getdir(short drive, char *cp);
char * cdecl getpath(short drv, char *cp);
char * cdecl getdirpath(char *dir, char *dest); 
char * cdecl get_fname(const char *cp);
short  cdecl setdrive(short drive);
short  cdecl setpath(char *dir);
char * cdecl getext(const char *fn);

#define SW_SET 0
#define SW_READ 1

#include <ctype.h>

/* Zortech */
#ifdef _DIG
#define _DIGIT _DIG
#define _UPPER _UC
#define _LOWER _LC
#define _SPACE _SP
#define _PUNCT _PNC
#endif

/* Borland */
#ifdef _IS_DIG
#define _DIGIT _IS_DIG
#define _UPPER _IS_UPP
#define _LOWER _IS_LOW 
#define _SPACE _IS_SP
#define _PUNCT _IS_PUN
#endif

/* IBM CSet++ compiler */
#ifdef __D
#define _DIGIT __D
#define _UPPER __U
#define _LOWER __L 
#define _SPACE __S
#define _PUNCT __P
#endif

/* IBM Visual Age compiler */
#ifdef __ISDIGIT
#define _DIGIT __ISDIGIT
#define _UPPER __ISUPPER
#define _LOWER __ISLOWER
#define _SPACE __ISSPACE
#define _PUNCT __ISPUNCT
#endif

/* MetaWare & Watcom */
#ifndef _LETTER
#define _LETTER (_UPPER|_LOWER) 
#endif
#ifndef _ALNUM
#define _ALNUM (_UPPER|_LOWER|_DIGIT) 
#endif
#ifndef _PRINT
#define _PRINT (_SPACE|_PUNCT|_UPPER|_LOWER|_DIGIT) 
#endif
#ifndef _GRAPH
#define _GRAPH (_PUNCT|_UPPER|_LOWER|_DIGIT) 
#endif

#if defined(__cplusplus)
}
#endif

#endif // __CX_H
