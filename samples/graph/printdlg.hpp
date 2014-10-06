/*  VCS_ID
 *  $Filename:   printdlg.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:18:38  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#include "printdlg.h"

class PrintDlg : public wFormWindow
{
	private:
		wPrinterSetup *currSetup, *origSetup;
		wPrinterList  *prlist;
		bool fChanged;
		wListRegion *prLReg;
		short currPrinter;

		short Init();	
        short Save();
		short ConfirmQuit();
		short ProcJobProperties(wButtonField *);

	public:
		PrintDlg(wWindow *parent, wPrinterSetup *origSetup);
		~PrintDlg();

		wPrinterSetup *GetSetup() 	{ return currSetup; }
		bool IsChanged()         	{ return fChanged; }
};


