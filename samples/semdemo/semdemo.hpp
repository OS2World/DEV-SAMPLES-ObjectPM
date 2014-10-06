/*  VCS_ID
 *  $Filename:   semdemo.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:50:32  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#include "semdemo.h"

class AppWindow : public wFrameWindow
{
	private:
		wMenu *menubar;
		wIcon *icon;

	public:
		pbSemaphoreList semList;

		AppWindow();
		~AppWindow();
		long MenuCommand(wCommandMsg);
		void Paint();
};


class DrawThread : public bThread
{
	public:
		DrawThread(char *name) : bThread() { Init(name); }

		short Start();
};
