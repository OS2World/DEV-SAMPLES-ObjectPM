/*  VCS_ID
 *  $Filename:   errhandl.cpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:20:32  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define InclMdi
#define InclOS2Objects
#define InclFiles
#define InclStdDialogs
#include <ObjectPM.hpp>

#include "errdemo.h"
#include "errhandl.hpp"

#include <process.h>

AppErrorHandler :: AppErrorHandler(char *_appName, long condType, char *)
				 : bConditionHandler(condType, this, EVENTMETHOD(AppErrorHandler, ProcConditions)),
				   appName(_appName)
{
}


AppErrorHandler :: ~AppErrorHandler()
{
}

/* this method is invoked when one or more conditions are asserted */

short AppErrorHandler :: ProcConditions(bCondition *c)
{
	// get the pointer to the application frame window
	wWindow* dialogParent = (wWindow *)(ThisApp->GetObject("AppFrame"));
	if (!dialogParent)
		dialogParent = DesktopWindow;

	wStdErrorDialog errDlg(dialogParent, c);
	if (!errDlg.GetResult())
		exit(0);

	return TRUE;
}

