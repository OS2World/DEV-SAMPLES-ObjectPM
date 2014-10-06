/*  VCS_ID
 *  $Filename:   semdemo.cpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.2  $
 *  $Date:   31 Dec 1991 12:13:00  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#define InclGraphics
#define InclOS2Objects
#include <ObjectPM.hpp>
#include <objpmres.h>
#include "semdemo.hpp"	// include the class definitions

// This demo program starts a second thread and then creates 
// a list of semaphores in which to send commands to the thread.
// Each time a menu option is selected by the user, an appropriate
// semaphore is cleared.  The second thread, which is waiting on the
// list of semaphores, is awakened and given a pointer to the
// semaphore object that was cleared.  The second thread then draws
// the appropriate text on the window created by the primary thread.
// One of the semphores in the list is used to tell the second thread
// to kill itself.
//
// Note that this demo also can be done just as easy by having the 
// second thread create a window off the object window and have 
// the primary thread post semaphore messages to it.  This way is faster 
// though. 

short MainThread :: Start()					  // Program execution starts here
{
	AppWindow  w;	    					  // Construct the top level frame window
	ThisApp->PutObject("APPWINDOW", &w);
	DrawThread t("DrawThread");               // Construct the second thread
	Exec();									  // Go to the message loop.

	// Send 'Self Destruct' cmd to second thread
	((bEventSemaphore*)((*w.semList)[CMD_QUIT]))->Post();

	// Elevate the priority of the second thread and wait up to 2 
	// seconds for it to kill itself.  This is necessary because
	// the second thread is not a 'raw' thread (it created an anchor
	// block and a message queue (Any thread that draws in a PM window
	// must have an anchor block)). Only the second thread can free
	// up these resouces

//	t.SetPriority(PRTYD_MAXIMUM);
	for (int i = 0; i < 20; i++)
	{
		if (!t.IsAlive())
			break;

		Sleep(100);		// Give up the CPU for 100ms
	}
	return 0;
}


AppWindow :: AppWindow()
{												   
	CreateWindow(OpmStdFrame);					   // Create the frame
	SetCaption("Semaphore Demo");	 			   // Set captions
	SetSwitchTitle("Semaphore Demo");
	SetIcon(icon = new wIcon(ResIcon, I_OBJPM));   // Set the app's icon

	menubar = new wMenu(this, MB_MESSAGE, "~Message\\");
	menubar->SetSubMenuItems(MB_MESSAGE, MI_FIRST, "First;Second;Third");
				
	semList = new bSemaphoreList(FALSE); 		   	// Create the sem. list
	semList->Add(new bEventSemaphore(MI_FIRST));	// and the semaphores...
	semList->Add(new bEventSemaphore(MI_SECOND));
	semList->Add(new bEventSemaphore(MI_THIRD));
	semList->Add(new bEventSemaphore(CMD_QUIT));

	semList->ResetAll();
	Show();				   // Make the frame visible
	ToTop();
}

AppWindow :: ~AppWindow()
{	
	// Destroy the semaphores and the list

	semList->RemoveAll();
	
   	delete semList;
	delete menubar;
	delete icon;
}


long AppWindow :: MenuCommand(wCommandMsg m)
{
	semList->First();
	((bEventSemaphore*)((*semList)[m.usCmd() - MI_FIRST]))->Post();
	return FALSE;
}

void AppWindow :: Paint()
{
	WindowPS()->Erase();		  // Erase the client window
}


/********* Class members running in the second thread **********/

short DrawThread :: Start()
{
	AppWindow *appWinp = (AppWindow *)ThisApp->GetObject("APPWINDOW");
	bEventSemaphore *semCmd;

	for (;;)
	{	 
		// Wait for one of the semaphores to clear. When one does,
		// the Wait method will return a pointer to the Semaphore 
		// object that actually cleared.

		semCmd = (bEventSemaphore*)(appWinp->semList->Wait());

		if ( semCmd )
		{
			if (semCmd->SemaphoreId() == CMD_QUIT)
			{
				Quit();
				return 0;
			}

			wPresSpace ps(appWinp);
			wTextPen   t(&ps);

			t.SetBackMix(BmOverPaint);
			t.Printf(20, 20, "%ld menu item chosen!    ", semCmd->SemaphoreId());
			semCmd->Reset();		// "re-arm" the semaphore
		}
	}
}
