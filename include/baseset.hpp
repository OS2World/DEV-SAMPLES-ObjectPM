/*  VCS_ID
 *  $Filename:   baseset.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   
 *  $Date:   
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

/* ObjectPM C++ BasetSet Class Library * Main header file.  
   Any or all sections of the BaseSet library may be may be
   included by defining one or more pre-processor variables: 

   	InclCollections
*/

#ifndef __BASESET_HPP
#define __BASESET_HPP


#define OPM4OS2   1	 	// platforms
//define OPM4WIN32 1
//define OPM4MOTIF 1

/*
 *	ObjectPM defines
 */

#ifdef  InclObjectPM	// Include all of ObjectPM?
#define InclFieldTypes
#define InclFixedMath
#define InclForms
#define InclGraphics
#define InclHelp
#define InclMisc
#define InclControls
#define InclMdi
#define InclBaseSet
#define InclPrinters
#define InclStdDialogs
#define InclIconWin
#define InclImgBtn
#define InclPanel3d
#define InclSpreadSheet
#define InclCFunctions
#endif

#if !defined(InclGraphics) &&\
    !defined(InclFixedMath) &&\
    !defined(InclForms) &&\
    !defined(InclHelp) &&\
    !defined(InclMisc) &&\
    !defined(InclControls) &&\
    !defined(InclMdi) &&\
 	!defined(InclObjectPMBase)
#define NoObjectPM
#endif

#ifdef ObjectPMCore
#define ObjectPMLite
#define BaseSetLite
#endif

#ifndef NoObjectPM
#ifdef InclMdi
#undef  InclGraphics
#undef  InclControls
#define InclGraphics
#define InclControls
#endif
#ifdef  InclPrinters
#undef  InclGraphics
#define InclGraphics
#endif

#if defined(BUILDLIB) && defined(OPM4OS2)

#if !defined (NoWindows) && !defined(INCL_WIN) 
#define INCL_WIN
#endif

#ifdef  InclPrinters
#define INCL_DEV
#endif

#if defined (InclGraphics) && !defined(INCL_GPI)
#define INCL_GPI
#endif

#if defined (InclControls) && !defined (INCL_WINSTDSPIN)
#define INCL_WINSTDSPIN
#endif

#ifndef INCL_DOSMODULEMGR
#define INCL_DOSMODULEMGR
#endif

#ifndef INCL_DOSMISC
#define INCL_DOSMISC
#endif

#endif // defined(BUILDLIB) && defined(OPM4OS2)

#endif // NoObjectPM


/*
 *	ObjectComm defines
 */

#ifdef InclComm         // Include all of ObjectComm?
#define InclCommMsgBoxes
#define InclCommQueues
#define InclCommNamedPipes
#define InclCommServers
#endif

#if !defined(InclCommMsgBoxes) &&\
    !defined(InclCommQueues) &&\
    !defined(InclCommNamedPipes) &&\
    !defined(InclCommServers)
#define NoObjectComm
#endif

#ifndef NoObjectComm

#ifdef InclCommQueues
#define InclCommMsgBoxes
#endif

// define ObjComm common stuff
#ifndef InclOS2Objects
#define InclOS2Objects
#endif

#endif // NoObjectComm


/*
 *	BaseSet defines
 */

#ifdef  InclBaseSet	    // Include the whole base set?
#define InclFiles
#define InclProfiles
#define InclOS2Objects
#define InclPaperForms
#endif


#if defined(BUILDLIB) && defined(OPM4OS2)

#if defined (InclFiles) || defined (InclProfiles) || \
    defined (InclOS2Objects) || defined (InclPaperForms)
#ifndef INCL_DOS
#define INCL_DOS
#endif
#ifndef INCL_ERRORS
#define INCL_ERRORS
#endif
#ifndef INCL_DOSMISC
#define INCL_DOSMISC
#endif
#endif

#ifdef InclProfiles
#define INCL_WINSHELLDATA
#endif

#ifndef INCL_TYPES
#define INCL_TYPES
#endif
#define INCL_32

#include <os2.h>

#if defined(__BORLANDC__) || defined(__WATCOMC__)
	#include <mem.h>
#else
	#include <memory.h>
#endif
#include <string.h>

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef BaseSetLite
#include <iostream.h>
#include <fstream.h>
#endif

#endif // defined(BUILDLIB) && defined(OPM4OS2)

#include "basedefs.h"

/*
 *	Common header files
 */

#include "bsetypes.hpp"
#include "collect.hpp"
#include "string.hpp"
#include "slist.hpp"
#include "ipc.hpp"
#include "event.hpp"
#include "thread.hpp"
#include "country.hpp"
#include "app.hpp"
#include "timestmp.hpp"
#include "position.hpp"
#include "money.hpp"

#endif // __BASESET_HPP

#ifdef InclFieldTypes
#include "dtype.hpp"
#endif

#ifdef InclFiles
#include "file.hpp"
#endif

#ifdef InclProfiles
#include "profile.hpp"
#endif

#ifdef InclCFunctions
#include "cx.h"
#include "msc.h"
#endif
