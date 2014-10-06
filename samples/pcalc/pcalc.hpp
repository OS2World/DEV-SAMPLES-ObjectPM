/*  VCS_ID
 *  $Filename:   pcalc.hpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:36:06  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
// PROGRAMMERS CALCULATOR

#define INCL_WINSYS
#define InclControls
#include <ObjectPM.hpp>
#include "pcalcdlg.h"

#define OP	0
#define NUM	1
#define BnClicked 1

class stknode
{
	public:
		short	type;
		long	value;

	stknode(short t, long v) {type=t, value=v;}
};

typedef tStack<stknode> Stack;

class PCalc : public wDialogWindow
{
	private:
		wPushButton    *BNum[16];
		wRadioButton   *BMode[4];
		wStaticControl *answer;
		short		Mode,
					Base,
					inNum,
					lastop;	// =1 IF PREVIOUS OP WAS HIGH ORDER OF OPERATIONS
		long		total;
		Stack		stk;

		void SetMode(short);
		void SetAnswer(long);
		long DoCalc();
		long PopStk();
	public:
		PCalc(wWindow *parent, ushort id) : 
			wDialogWindow(id, DlgModeless), stk(TRUE) 
			{ CreateWindow(parent); }

		long InitDlg(wInitDlgMsg);
		long PushButtonCommand(wCommandMsg);
		long Control(wControlMsg);
};

class CalcWin : public wFrameWindow
{
	public:
		PCalc		*pc;
		wSysMenu	*psys;
		CalcWin();
		long MenuCommand(wCommandMsg m);
};


class AboutDialog : public wDialogWindow
{
	public:
		AboutDialog(wWindow *owner) : 
			wDialogWindow(ID_ABOUT) { CreateWindow(owner); }
		long InitDlg(wInitDlgMsg)               { ChangePosition(PosCenter, OwnerWindow()); return FALSE; }
		long PushButtonCommand(wCommandMsg)     { Dismiss(); return FALSE; }
};
