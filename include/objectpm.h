/*  VCS_ID						  
 *  $Filename:   ObjectPM.h
 *  $Author  :   chas 
 *  $Revision:   1.5  $
 *  $Date:   10 Jan 1995   14:01:30  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_WINERRORS
#define INCL_32
#include <os2.h>

#include "basedefs.h"
#include "objpmres.h"
#include "objwinx.h"
#include "pmlist.h"
#include "pmforms.h"
#include "cx.h"
#include "cellproc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(__BORLANDC__) || defined(__WATCOMC__)
	#include <mem.h>
#else
	#include <memory.h>
#endif
