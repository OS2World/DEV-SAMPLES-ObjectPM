/*  VCS_ID
 *  $Filename:   spindemo.hpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:52:46  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
class DemoFrame : public wFrameWindow	// DEMO WINDOW
{
	private:
		wSpinButton	*sbmm, *sbdd, *sbyy, *sbstr, *sbnum;	// THE SPIN BUTTONS
		long		prevmm, prevdd;
		wIcon		*icon;

	public:
		DemoFrame();
	   ~DemoFrame();
		void Paint();
		long Control(wControlMsg);
};


// notfiers  (from pmstddlg.h)

#define SPBN_UPARROW	0x20A
#define SPBN_DOWNARROW	0x20B
#define SPBN_CHANGE		0x20D
