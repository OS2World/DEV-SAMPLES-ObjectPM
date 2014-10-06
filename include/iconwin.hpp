/*  VCS_ID
 *  $Filename:   iconwin.hpp
 *  $Author  :   John Pompeii 
 *  $Revision:   1.1  $
 *  $Date:   10 Dec 1991 17:22:24  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __ICONWIN_HPP
#define __ICONWIN_HPP

#define WC_ICONWIN "ICONWINDOW"

#define BN_SETFOCUS		100
#define BN_KILLFOCUS	101

class IconWindow_Imp : public wWindow
{
	private:
		wIcon *icon;
		bool fFocus, fKeyArm;
		wTextPen tpen, ftpen;
		wFont *fp;
		wDimension sizIcon;
		wRectl textRectl;
		wPointl iconPos, setPos;
		char iconText[40];
		ulong style;
		HWND owner;
		ushort id;

	public:
		IconWindow_Imp(HWND _hwnd);
		~IconWindow_Imp();
		void FormatWindow();
		long Dispatch(wMessage);
		void Paint();
        long ButtonClick(wButtonClickMsg);
		long Create(wCreateMsg);
		long FocusChange(wFocusChangeMsg);
		long KeyStroke(wKeyStrokeMsg);
};

class IconWindowClass : public wWindowClass
{
	public:
		IconWindowClass();
		wWindow *Create(HWND _hwnd);
		void Destroy(wWindow *p);
};

#endif // __ICONWIN_HPP
