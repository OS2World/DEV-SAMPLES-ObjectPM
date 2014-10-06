/*  VCS_ID
 *  $Filename:   errdemo.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:20:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

// ErrorDemo application class definitions....

#include "errdemo.h"
#include "about.h"

// class definition for the main frame window

class AppWindow : public wFrameWindow
{
	private:
		wMenu *menubar;
		wIcon *icon;
		wHelpManager *help;

	public:
		AppWindow();
		~AppWindow();
		long Close(wMessage);
		long ProcError(wMessage);
		long ProcRecordTell(wMessage);
		long ProcHelp(wMessage);
		long ProcAbout(wMessage);
		void Paint();
};

// "IO" library class.  This class is not implemented properly, but is 
// used to demonstrate returning errors from a class library (or "facility").

class ObjectIO
{
	public:
		bool OpenFile(const char *fileName);
		bool Read();
};

// Record Condtion Form Class

class RecConditionForm : public wFormWindow
{
	private:
 		short type, thread;
		bString condString, argument;

	public:
		RecConditionForm();

		short Init();    
		short ProcTypeSelect(wRadioButtonField *fld, short newValue);
		void  SetCombo(short type);

		// Interface for results
		long    GetConditionCode();
		short	GetThread()				{ return thread;   }
		short	GetType()				{ return type;	   }
		bString	GetArgument()			{ return argument; }
};


// class definition for the "about" dialog window.  

class AboutDialog : public wDialogWindow
{
	public:
		AboutDialog(wWindow *owner) : wDialogWindow (D_ABOUT) { CreateWindow(owner); }
		long InitDlg(wInitDlgMsg)               { ChangePosition(PosCenter, OwnerWindow()); return FALSE; }
		long PushButtonCommand(wCommandMsg)     { Dismiss(); return FALSE; }
};


