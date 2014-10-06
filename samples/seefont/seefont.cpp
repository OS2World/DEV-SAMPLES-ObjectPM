/*  VCS_ID
 *  $Filename:   seefont.cpp
 *  $Author  :   John Pompeii & Mike Flis
 *  $Revision:   1.2  $
 *  $Date:   03 Jan 1992 00:26:10  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#define InclForms
#define InclGraphics
#define InclFixedMath
#include <ObjectPM.hpp>
#include <objpmres.h>
#include "seefont.hpp"

#include <stdlib.h>

short MainThread :: Start()		// Program execution starts here
{
	AppWindow w;	    // Contstruct the top level frame window
	Exec();				// Go to the message loop.

	return 0;
}

AppWindow :: AppWindow()
{												   
	CreateWindow(FaTaskList | FaTitleBar | FaSysMenu | FaSizeBorder | FaMinMax);
	SetCaption("Outline Font Viewer");	  
	SetSwitchTitle("Outline wFont Viewer");
	SetIcon(icon = new wIcon(ResIcon, I_OBJPM));   // Set the app's icon

	fontDialog =  new OutlineFontDialog();
	fontDialog -> FormUp(this);
	fontDialog -> ChangePosition(wPointl(0, 0));

	ChangeFrameSize(fontDialog);
 	SetMaximumSize(GetSize());
	ChangePosition(PosCenter);

	Show();				   // Make the frame visible
}

AppWindow :: ~AppWindow()
{ 
	delete fontDialog;				   
	delete icon;
}

OutlineFontDialog :: OutlineFontDialog() : wFormWindow(D_FONTINFO, 4, 1, DlgModeless)
{
	wPushButtonField *bp;

	AddField( pt = new wEditField(FtDouble, 5, E_POINTSZ, &pointSize,"%d2", FsInitBlank) );
	AddField( pi = new wEditField(FtDouble, 4, E_PITCH, &pitch, "%d1", FsInitBlank) );
	AddField( bp = new wPushButtonField(BUT_SHOW) );
	bp->SetFieldClickFn(FORMMETHOD(OutlineFontDialog,ShowFont));

	AddListRegion( pLReg = new wListRegion(L_FONTS, LrNoDelete + LrNoClear) );
	pLReg->SetIndent(8);
}

OutlineFontDialog :: ~OutlineFontDialog()
{
	if (appFont)
		delete appFont;
}

short OutlineFontDialog :: Init()
{
 	wPresSpace ps (this, PuLoEnglish);
	flist = ps.EnumFontFaces(FfPublic | FfOutline);

	for (flist->First(); flist->Current(); flist->Next())
		pLReg->InsertItemText(*(flist->Current()));
	
	pLReg->SelectItem(0);

	pointSize = 0.0;
	pitch = 0.0;

	fname = "";
	appFont = 0;

	return TRUE;
}

void OutlineFontDialog :: Paint()
{
	wRectl	rct(wPointl(16,6,DlgUnits), wDimension(251,36,DlgUnits));
	wRegion	reg(WindowPS(), &rct, 1);

	reg.SetAsClipRegion();

	if (appFont)
	{
		appFont->ConnectTo(WindowPS());
		if (pointSize)
			appFont->ChangePointSize(wFixed(pointSize));
		if (pitch)
			appFont->ChangePitch(wFixed(pitch));

		wTextPen	tp(WindowPS());
		tp.PenDown(appFont);

		wPointl p(18,12,DlgUnits);
		tp.Display(p, "ABCDEFabcdef12345");
	}
}

short OutlineFontDialog :: ShowFont()
{
	bString sel = pLReg->GetCurrentItemText();	// GET CHOSEN ONE

	if (sel != fname)							// NEW FACENAME
	{
		wPresSpace	ps(this);
		wFontDefList *falist = ps.EnumFonts(sel, FfOutline);
		fname = sel;

		if (falist->First())
		{	
			delete appFont;
			appFont = new wFont(falist->Current(), NULL);
		}
	}

	// WRITE THE POINT SIZE AND PITCH FIELD BUFFERS

	pt->Convert();
	pi->Convert();
	
	RePaint(wRectl(wPointl(16,6,DlgUnits), wDimension(251,36,DlgUnits)));

	return TRUE;
}
