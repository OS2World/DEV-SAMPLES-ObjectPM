/*  VCS_ID
 *  $Filename:   objectpm.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.8  $
 *  $Date:   16 Jan 1992 17:14:08  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

/* ObjectPM C++ Class Library * Main header file.  
   Any or all sections of the ObjectPM library may be
   included by defining one or more pre-processor variables: 


	InclGraphics
	InclControls
	InclFixedMath
	InclHelp
	InclForms
	InclFiles
	InclProfiles
	InclOS2Objects
	InclPaperForms
	InclMisc
	InclComm
	InclMdi
	InclObjectPM
	InclCFunctions
	InclPrinters
	InclNoWindows
	InclStdDialogs
    InclIconWin
    InclImgBtn
    InclPanel3d
    InclSpreadSheet

	ObjectPMLite
*/

#ifdef InclNoWindows
#undef NoWindows
#define NoWindows
#else
#define InclObjectPMBase
#endif

#if defined(__IBMCPP__) && !(defined(BUILDLIB) || defined(STATICLIB) || defined(_EXEENTRY) )
    #define _EXEENTRY
    extern int _exeentry;
    static int* __force_main__= &_exeentry;
#endif

#include "baseset.hpp"

#ifdef ObjectPMLite
#undef InclControls
#undef InclHelp
#undef InclForms
#undef InclMdi
#undef InclStdDialogs
#endif

#ifndef NoWindows  // Include the wWindow Manager classes?
#include "windows.hpp"
#endif

#ifdef InclGraphics
#include "graphics.hpp"
#endif

#ifdef InclPrinters
#include "print.hpp"
#endif

#ifdef InclHelp
#include "help.hpp"
#endif

#ifdef InclForms
#include "forms.hpp"
#endif

#ifdef InclMdi
#include "mdi.hpp"
#endif

#ifdef InclFixedMath
#include "fixed.hpp"
#endif

#ifdef InclStdDialogs
#include "fixed.hpp"
#include "graphics.hpp"
#include "stddlg.hpp"
#endif

#ifdef InclIconWin
#include "iconwin.hpp"
#endif

#ifdef InclImgBtn
#include "imgbtnwn.hpp"
#endif

#ifdef InclPanel3d
#include "panl3dwn.hpp"
#endif

