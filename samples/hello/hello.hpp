/*  VCS_ID
 *  $Filename:   hello.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:20:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

// Hello application class definitions....

#include "hello.h"
#include "about.h"

// class definition for the main frame window

class HelloWindow : public wFrameWindow
{
	private:
		wMenu *menubar;
		wIcon *icon;
		wAccelTable *acceltab;
	 	short msg;

	public:
		HelloWindow();
		~HelloWindow();
		long Close(wMessage);
		long ProcNextPrev(wMessage);
		long ProcAbout(wMessage);
		void Paint();
};

// class definition for the "about" dialog window.  Note that this 
// class definition contains all the code necessary to process this dialog
// box

class AboutDialog : public wDialogWindow
{
	public:
		AboutDialog(wWindow *owner) : wDialogWindow (D_ABOUT) { CreateWindow(owner); }
		long InitDlg(wInitDlgMsg)               { ChangePosition(PosCenter, OwnerWindow()); return FALSE; }
		long PushButtonCommand(wCommandMsg)     { Dismiss(); return FALSE; }
};


