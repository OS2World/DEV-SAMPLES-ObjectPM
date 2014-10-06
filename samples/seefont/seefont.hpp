/*  VCS_ID
 *  $Filename:   seefont.hpp
 *  $Author  :   John Pompeii & Mike Flis
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:48:20  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#include "dialogs.h"

class OutlineFontDialog : public wFormWindow
{
	private:
		bStringList	*flist;
		short 		fontSelection;
		wFont 	   *appFont;
		double 		pointSize;
		double 		pitch;
		wListRegion *pLReg;
		bString		fname;
		wEditField *pt, *pi;

		short Init();
		void Paint();

	public:
		OutlineFontDialog();
		~OutlineFontDialog();
		short ShowFont();
};

class AppWindow : public wFrameWindow
{
	private:
		wIcon *icon;
		OutlineFontDialog *fontDialog;

	public:
		AppWindow();
		~AppWindow();
};

