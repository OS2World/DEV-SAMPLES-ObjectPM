/*  VCS_ID
 *  $Filename:   spindemo.cpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.2  $
 *  $Date:   03 Jan 1992 01:16:00  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
// PROGRAM TO DEMONSTRATE THE USE OF SPINBUTTON OBJECTS

#define InclControls
#define InclGraphics
#define InclFiles
#include <ObjectPM.hpp>
#include <objpmres.h>
#include "spindemo.hpp"

short MainThread :: Start()	// THE START OF OUR APP
{
	DemoFrame	tf;
	Exec();

	return 0;
}

// IDS OF THE SPIN BUTTONS
#define MONTH	0
#define DAY		1
#define YEAR 	2
#define STR		3
#define NUM		4

DemoFrame :: DemoFrame()
{
	// CHARACTER ARRAY FOR THE MONTH SPIN BUTTON OBJECT
	static const char *months[] = {"January","February","March","April","May","June",
		"July","August","September","October","November","December"};

	CreateWindow(FaTaskList | FaTitleBar | FaSysMenu | FaDlgBorder | FaMinButton);
	SetCaption("Spin Button Demo");
	SetSwitchTitle("Spin Button Demo");
	SetIcon(icon = new wIcon(ResIcon, I_OBJPM));   // SET THE APP'S ICON
	
	// THE STRING SPIN BUTTON
	bStringList	sl(TRUE);
	sl.Insert(new bString("Apple"));
	sl.Insert(new bString("Banana"));
	sl.Insert(new bString("Cherry"));

	sbstr = new wSpinButton(this, STR, wPointl(10,40,DlgUnits), wDimension(60,20,DlgUnits),
		                    SbMaster | SbAllCharacters | WsVisible);
	sbstr->SetStrings(&sl);

	// THE NUMERIC SPIN BUTTON
	sbnum = new wSpinButton(this, NUM, wPointl(75,40,DlgUnits), wDimension(50,20,DlgUnits),
		                    SbMaster | SbNumericOnly | SbFastSpin | WsVisible);

	sbnum->SetRange(wRange(-9999,9999));

	// THE DATE SPIN BUTTONS
	sbmm = new wSpinButton(this, MONTH, wPointl(10,10,DlgUnits), wDimension(55,20,DlgUnits),
		SbServant | SbReadOnly | WsVisible);
	sbdd = new wSpinButton(this, DAY, wPointl(65,10,DlgUnits), wDimension(20,20,DlgUnits),
		SbServant | SbReadOnly | SbPadWithZeros | WsVisible);
	sbyy = new wSpinButton(this, YEAR, wPointl(85,10,DlgUnits), wDimension(40,20,DlgUnits),
		SbMaster | SbReadOnly | WsVisible);

	// SET UP THE MONTH SPIN BUTTON
	sbmm->SetStrings(months, 12);

	// SET UP THE DAY SPIN BUTTON
	sbdd->SetMaxLength(2);
	sbdd->SetRange(wRange(1,31));
	sbdd->SetValue(1);

	// SET UP THE YEAR SPIN BUTTON
	sbyy->SetRange(wRange(1600, 2100));
	sbyy->SetValue(1991);

	// SET THE YEAR AS THE MASTER OF DAY AND MONTH
	sbdd->SetMaster(sbyy);
	sbmm->SetMaster(sbyy);

	// SET UP PREVIOUS VALUES
	prevmm = 0;
	prevdd = 1;

	// SIZE AND POSITION OUR TEST FRAME
	ChangeFrameSize(wDimension(145,80,DlgUnits));
	ChangePosition(PosCenter);

	// SHOW EVERYTHING
	sbstr->SetFocus();
	Show();
	ToTop();
}

DemoFrame :: ~DemoFrame()
{
	delete sbmm;
	delete sbdd;
	delete sbyy;
	delete sbstr;
	delete sbnum;
	delete icon;
}

void DemoFrame :: Paint()
{
	wTextPen	t(WindowPS());
	
	WindowPS()->Erase();

	t.Display(wPointl(10,24,DlgUnits), "Master-Slave Spin Buttons");
	t.Display(wPointl(10,54,DlgUnits), "Strings");
	t.Display(wPointl(75,54,DlgUnits), "Numeric");
}

long Leap(int y) { return !(y%4) && (y%100) || !(y%400); }

long DemoFrame :: Control(wControlMsg m)
{
	long	yy, mm;
	static	bool skip=FALSE;

	// CHECK IF DAY WRAPPED
	if (m.id() == DAY && m.usNotifyCode() == SPBN_CHANGE && !skip)
	{
		long	dd = sbdd->GetValue();
		wRange	r = sbdd->GetRange();
	
		if (dd == 1 && prevdd == r.High())
			sbmm->SpinUp();
		if (dd == r.High() && prevdd == 1)
		{
			sbmm->SpinDown();
			skip = TRUE;	// PREVENT RECURSION
			sbdd->SetValue(dd = r.High());
			skip = FALSE;
		} 
		prevdd = dd; 
		return FALSE;
	}

	// ADJUST DAY RANGE BASED ON MONTH AND CHECK IF MONTH WRAPPED
	if (m.id() == MONTH && m.usNotifyCode() == SPBN_CHANGE)
	{
		skip = TRUE;	// PREVENT RECURSION WHEN CHANGING RANGES
		switch (mm = sbmm->GetValue())	
		{
			case 1:	
				yy = sbyy->GetValue();
				sbdd->SetRange(wRange(1,28 + Leap(yy)) );
				break;
			case 0:
				if (prevmm == 11)
					sbyy->SpinUp();
			case 2:
			case 4:
			case 6:
			case 7:
			case 9:
				sbdd->SetRange(wRange(1,31));
				break;
			case 11: 
				if (prevmm == 0)
					sbyy->SpinDown();
				sbdd->SetRange(wRange(1,31));
				break;
			default:
				sbdd->SetRange(wRange(1,30));
				break;
		}
		prevmm = mm;
		skip = FALSE;
		return FALSE;
	}

	// ADJUST DAY RANGE IF LEAP YEAR
	if (m.id() == YEAR && (m.usNotifyCode() == SPBN_UPARROW || 
		m.usNotifyCode() == SPBN_DOWNARROW)	&& sbmm->GetValue())
	{
		skip = TRUE;
	 	yy = sbyy->GetValue();

		sbdd->SetRange(wRange(1,27 + Leap(yy)) );
		skip = FALSE;
		return FALSE;
	}	
	return FALSE;
}
