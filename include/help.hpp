/*  VCS_ID
 *  $Filename:   help.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   10 Dec 1991 17:19:54  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __HELP_HPP
#define __HELP_HPP

class _EXPORT_ wHelpManager
{
	private:
		bString helpLibrary;
		HWND	hwndHelp;
		ushort  keysHelp, generalHelp;
 		wWindow *activeFrame;

	public:
		wHelpManager(const char *helpLibraryName, ushort idActionBar = 0, ushort idAccel = 0);
		~wHelpManager();

		HWND     hHelpManager() 			{ return hwndHelp;    }
		bool     SetHelpTable(ushort htab);
		void     SetKeysHelpPanel(ushort panelId);
		ushort   GetKeysHelpPanel() 		{ return keysHelp;    }
		void     SetGeneralHelpPanel(ushort panelId);
		ushort   GetGeneralHelpPanel()		{ return generalHelp; }
		ushort   SetActiveWindow(wWindow *win);
		wWindow *GetActiveWindow()			{ return activeFrame; }

		ushort   SetHelpLibrary(const char *libname);
		bString  GetHelpLibrary()			{ return helpLibrary; }
		void     SetHelpWindowTitle(const char *name);
		ushort   ShowHelp(ushort panelId = 0);
		ushort   ShowGeneralHelp();
		ushort   ShowIndex();
		ushort   ShowKeysHelp();
		ushort   ShowTableOfContents();
		bool     CloseHelpWindow();
		void     ShowPanelIDs(bool state = FALSE);
};

#endif // __HELP_HPP
