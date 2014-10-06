/*  VCS_ID
 *  $Filename:   fldmask.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __FLDMASK_HPP
#define __FLDMASK_HPP

#if defined(BUILDLIB)

#define MaskErrorFull	1
#define MaskErrorChar	2
#define MaskErrorUpdate	3

class wFieldMask
{
	private:
		PFNWP pWindowProc;		// original window procedure
		bString msk, 			// holds whole mask
			 	contents,		// holds non-masked text
			 	ent;	   		// holds non-literal chars
		bool 	insert;			// insert mode indicator
		HWND    hwnd;

		void SetContents(bool under);
		bool Validate(char *s);
		void SetNextPos(long pos, long dir);
		void SetEntry();
		char MaskChar(long pos);
		long MaskLength();
		long NonMaskPos(long pos);
		long MaskPos(long pos);
		bool CheckSelected();

	public:
		wFieldMask(char *mask);
		~wFieldMask();

		void	Init(HWND hwnd);
		void	SetDefaultWindowProc(PFNWP winproc);
		bool 	SetMask(char *mask, bool clear=TRUE);
		bString GetMask();
		bool 	SetText(char *txt, bool withmask=TRUE);
		bString	GetText(bool withmask=TRUE);

		wRange	GetEntrySelection();
		bool	SetEntrySelection(wRange r);
		bool	SetInsertMode(bool inserting=TRUE);
		bool 	IsFocusWindow();
		bool 	SetSelection(wRange ts);
		wRange 	GetSelection();
		bool	IsComplete();
		bool	IsBlank();
		void	SetCursorToEnd();

		long 	Error(long err, char ec, char mc);
		long 	Default(wMessage);
		long 	KeyStroke(wKeyStrokeMsg);
		long 	FocusChange(wFocusChangeMsg);
		long    ClearSelection(wMessage);
		long	CutSelection(wMessage);
		long	PasteSelection(wMessage);
};

#endif // defined(BUILDLIB)

#endif // __FLDMASK_HPP
