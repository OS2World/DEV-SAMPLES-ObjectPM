/*  VCS_ID
 *  $Filename:   msc.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.0  $
 *  $Date:   03 Jul 1991 12:37:18  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __MSC_H
#define __MSC_H

#if defined(__BORLANDC__)
    #if defined(__cplusplus)
        #ifndef __MINMAX_DEFINED
            #define __MINMAX_DEFINED
            template <class T> inline const T& min(const T& t1, const T& t2 )
            {
                return t1>t2 ? t2 : t1;
            }

            template <class T> inline const T& max(const T& t1, const T& t2 )
            {
                return t1>t2 ? t1 : t2;
            }
        #endif
    #else  // !defined(__cplusplus)
        #ifndef max
            #define max(a,b)    (((a) > (b)) ? (a) : (b))
            #define min(a,b)    (((a) < (b)) ? (a) : (b))
        #endif // max
    #endif // !defined(__cplusplus)
#elif defined(__IBMC__) || defined(__IBMCPP__)
    #ifndef max
        #define max(a,b)    (((a) > (b)) ? (a) : (b))
        #define min(a,b)    (((a) < (b)) ? (a) : (b))
    #endif // max
#elif defined(__HIGHC__)
    #ifndef max
        #define max(a,b) _max(a,b)
        #define min(a,b) _min(a,b)
    #endif // max
#elif defined(__WATCOMC__)
    #ifndef max
        #define max(a,b)    (((a) > (b)) ? (a) : (b))
        #define min(a,b)    (((a) < (b)) ? (a) : (b))
    #endif // max
#endif

#endif // __MSC_H
