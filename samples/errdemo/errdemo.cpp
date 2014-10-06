/*  VCS_ID
 *  $Filename:   hello.cpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:20:32  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#define InclGraphics
#define InclHelp
#define InclFiles
#define InclForms
#include <ObjectPM.hpp>
#include <objpmres.h>

#include "errdemo.hpp" 
#include "errhandl.hpp"

#include <stdlib.h>

short bMainThread :: Start()		// Program execution starts here
{
	// attach error handler
	AppErrorHandler defaultHandler("errdemo", CtAll, NULL);
	AddEventHandler(&defaultHandler);

	// Create the application facility
	bFacility *fac = new bFacility(FAC_ERRDEMO, "App", FAC_APPMSGFILE);
	fac->SetHelpFilename(FAC_APPHELPFILE, FAC_APPHELPOFFSET);
	ThisApp->AddFacility(fac);

	// ...and the IO library facility
	fac = new bFacility(FAC_IO, "I/O Library", FAC_IOMSGFILE);
	fac->SetHelpFilename(FAC_IOHELPFILE, FAC_IOHELPOFFSET);
	ThisApp->AddFacility(fac);

	// create help manager
	wHelpManager help("errdemo.hlp");
    help.SetHelpWindowTitle("Help for Error Demo");
   	help.SetHelpTable(MainHelpTable);

	AppWindow w;	    // Contstruct the top level frame window
	Exec();				// Go to the message loop.

	return 0;
}

AppWindow :: AppWindow()
{												   
	CreateWindow(OpmStdFrame);					   // Create the frame
	SetCaption("Errors & Conditons Sample");					   // Set captions
	SetSwitchTitle("ErrorDemo");
	SetIcon(icon = new wIcon(ResIcon, ITriangle));   // Set the app's icon

	// This section create a menu bar and then adds items to the 
	// sub menu itself.  It is also possible to construct the menu
	// from the resource file if desired

	menubar = new wMenu(this, MBarError, "~Error\\~Condition\\~Help\\");
	menubar->SetSubMenuItems(MBarError, MiFatal, "~Fatal;~Error;~Warning;");
	menubar->SetSubMenuItems(MBarCondition, MiRecord, "~Record...;~Tell...;");
	menubar->SetSubMenuItems(MBarHelp, MiHelp, "~Help for help...;~General help...;Help ~index;");

	// Create a temporary system menu object for the purposes of adding
	// a seperator and the "About..." menu item.

	wSysMenu sm(this);
	sm.AppendSeparator();
	sm.AppendItem(ScAbout, "~About...");

	// Add event handlers for the menu items.  

	AddMessageHandler(this, EVENTMETHOD(AppWindow, ProcError), 
	                  WM_COMMAND, MiFatal, MiWarning);	
	
	AddMessageHandler(this, EVENTMETHOD(AppWindow, ProcRecordTell), 
	                  WM_COMMAND, MiRecord, MiTell);	

	AddMessageHandler(this, EVENTMETHOD(AppWindow, ProcHelp), 
	                  WM_COMMAND, MiHelp, MiHelpIndex);	

	AddMessageHandler(this, EVENTMETHOD(AppWindow, ProcAbout), 
	                  WM_COMMAND, ScAbout);	

	// connect to HelpManager object

	SetFrameID(AppFrame);
	AssociateHelp();	
	help = ThisThread->HelpInstance();

	// set the address of the frame window in the app's dictionary so that
	// the error dialog can use it as its parent window.

	ThisApp->PutObject("AppFrame", this);

	Show();				   // Make the frame visible
	ToTop();
}

AppWindow :: ~AppWindow()
{				   
	delete menubar;
	delete icon;
}

// process the "Error..." message commands 

long AppWindow :: ProcError(wMessage m)
{
	switch ((int)m.mp1)
	{
		case MiFatal:
			CONDITION(FAC_ERRDEMO, CtFatal | CtError, UE_CORRUPT) 
				ATLOC (1, 0)
				<< "Data Structures" << Tell;
			
			break;

		case MiError:
			{
				ObjectIO iolib;

				if (!iolib.OpenFile("test.doc"))
				{
					CONDITIONAT(FAC_ERRDEMO, CtError,UE_INITIO) << Tell;
					break;
				}
				// ...
				// ...
			}
			break;

		case MiWarning:
			CONDITIONAT(FAC_ERRDEMO, CtWarning, UW_GUESSWHAT) 
			<< "This app does nothing of significant interest!" << Tell;
			break;

		default:
			break;
	}
	return 0;
}


long AppWindow :: ProcRecordTell(wMessage m)
{
	switch ((int)m.mp1)
	{
		case MiRecord:
			{
				RecConditionForm recForm;
				recForm.FormUp(this);

				if (recForm.GetResult() == AcFormExit) 
					switch (recForm.GetThread())
					{	
						case 0:	// Primary thread
							CONDITION(FAC_ERRDEMO, recForm.GetType()? CtWarning: CtError, 
									  recForm.GetConditionCode()) 

								ATLOC (2, 0)
								<< recForm.GetArgument() << Remember;
								
							break;
					
					}
			}
			break;

		case MiTell:
			ThisThread->ConditionNotify(CtError | CtWarning);
			break;
	}
	return 0;
}


// Process help requests

long AppWindow :: ProcHelp(wMessage m)
{
	switch ((int)m.mp1)
	{
		case MiHelp:
			help->ShowHelp();
			break;

		case MiGeneralHelp:
			help->ShowGeneralHelp();
			break;

		case MiHelpIndex:
			help->ShowIndex();
			break;
	}
	return 0;
}

// handle displaying the "About" window

long AppWindow :: ProcAbout(wMessage)
{
	AboutDialog aboutWin(this);		 // Create the "about" box
	return FALSE;
}

void AppWindow :: Paint()
{
	WindowPS()->Erase();		  // Erase the client window
}

// The Close member is called when the "Close" menu option is chosen
// from the system menu.  Returning TRUE from this function allows the
// exit process to continue.  Otherwise, a return of FALSE will prevent
// the application from being closed

long AppWindow :: Close(wMessage)
{
	// create a message box to confirm exit from the application

	wMessageBox m(this, "              Are You Sure?", "Exit", MbYesNo+MbIconQuestion+MbApplModal);
	return m.MessBoxVal() == 6;
}


// The "IO" class library.  This implementation is rather trivial in order
// demonstrate returning errors.  Normally such a subsystem would be much
// larger and would be packaged and built seperately.

bool ObjectIO :: OpenFile(const char *cp)
{
	bFile file(cp);

	if (file.Open("r"))
	{
		// file open failed...
   		CONDITIONAT(FAC_IO, CtError, UE_FILENOTFOUND) 
			<< (char *)cp << Remember;

		return FALSE;
	}

	file.Close();
	return TRUE;
}

bool ObjectIO :: Read()
{
   	CONDITIONAT(FAC_IO, CtError, UE_METHODNOTIMP) 
		<< "'Read'" << Remember;
	   
	return FALSE;
}

// Record Condtion Dialog Processing

RecConditionForm :: RecConditionForm() 
				  : wFormWindow(D_ADDCONDITION, 4, 0), argument(NULL, 80)
{
	wRadioButtonField *fp = new wRadioButtonField(R_ERROR, 2, &type); 
	AddField(fp);
	fp->SetFieldClickFn( FORMMETHOD(RecConditionForm, ProcTypeSelect) );

	AddField( new wRadioButtonField(R_THREAD1, 3, &thread) );
	AddField( new wComboField(FtString, 32, E_CONDITION, &condString, NULL, FsRequired) );
	AddField( new wEditField(FtMLString, 80, E_ARG, &argument, NULL) );
	
    SetOptions(FmEnterExit);
	SetActionButtons(B_CANCEL, B_OK, B_HELP);
}

short RecConditionForm :: Init()
{
	type = 0;
	thread = 0;
	SetCombo(type);

	return TRUE;
}

void RecConditionForm :: SetCombo(short typ)
{
	wComboField *fld = (wComboField *)GetField(E_CONDITION);
	fld->Clear();
	fld->DeleteAll();

	if (typ == 0)	// error
	{
		fld->AddString("03 - Cannot Open...");
		fld->AddString("04 - Resource...");
		fld->AddString("05 - General Failure...");
	}
	else			// warning
	{
		fld->AddString("06 - Note that...");
	}
}

short RecConditionForm :: ProcTypeSelect(wRadioButtonField *, short newValue)
{
	SetCombo(newValue);
	return TRUE;
}

long RecConditionForm :: GetConditionCode()
{
	return atol(condString);
}
