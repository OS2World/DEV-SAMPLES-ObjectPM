/*  VCS_ID
 *  $Filename:   panl3dwn.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */



#ifndef __PANL3DWN_HPP
#define __PANL3DWN_HPP

#define WC_PANEL3D "PANEL3D"

#define P3_SETPANELINFO	SLM_SETSLIDERINFO
#define P3_QUERYPANELINFO SLM_QUERYSLIDERINFO
#define P3A_BEVELWIDTH	0x0001
#define P3A_BORDERWIDTH	0x0002

class wPanel3DClass : public wWindowClass
{
	public:
		wPanel3DClass();
		wWindow *Create(HWND _hwnd);
		void Destroy(wWindow *p);
};


class wPanel3DImp : public wWindow
{
	private:
		ushort	bevelw, borderw;
		bString	szText;
		ulong	textflags;
		wPointl	outl[7], outr[7], inl[7], inr[7];
		wRectl	textrc, bordrc, inside, iborder[4];
		ulong	style;
		ulong	id;
		wColor	aClr[5];

		long lGetPresParam(ulong ulID1, ulong ulID2, long lDefault);
		void SetDefaultColors();

		void CalcPanel(wDimension d);
		void CalcTextRectangle(wDimension d);
		void DrawBevel(wPen &pn, wFillPattern &fp, wPointl *p);

	public:
		wPanel3DImp(HWND _hwnd);
		~wPanel3DImp();
		long Dispatch(wMessage);
		long Create(wCreateMsg);
		long Size(wSizeMsg);
		void Paint();
};

#endif // __PANL3DWN_HPP

