/*  VCS_ID
 *  $Filename:   stddlg.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.8  $
 *  $Date:   16 Jan 1992 17:14:08  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __STDDLG_HPP
#define __STDDLG_HPP

class _EXPORT_ wStdErrorDialog : public wDialogWindow
{
	private:
		bCondition *cond;
		bModule *holdModule;
		wWindow *holdHelp;
		bString  holdHelpFile;
		ushort helpId;

	public:
		wStdErrorDialog(bCondition *cd);
		wStdErrorDialog(wWindow *parent, pbCondition c);
		~wStdErrorDialog();

		long PushButtonCommand(wCommandMsg m);
		long InitDlg(wInitDlgMsg m);
		virtual bool SetDialogItems(bCondition *);
		virtual void ExitDialog(short n);
		void SetFacility(const char *fac);
		void SetConditionCode(const char *cc);
		void SetLocation(const char *loc, const char *loc2 = NULL);
		void ClearComment();
		void AddComment(const char *comment);
		void SetHelpPanel(ushort id);
};


#ifndef DID_FILE_DIALOG
struct _FILEDLG;
typedef _FILEDLG FILEDLG;
#endif

class _EXPORT_ wFileFilterMsg : public wMessage
{
	public:
		char *Filename() 		{ return (char*)mp1; }
		char *EAType()	 		{ return (char*)mp2; }
};

class _EXPORT_ wFileValidateMsg : public wMessage
{
	public:
		char   *pszPathName()	{ return (char*)mp1; }
		ushort &FieldNameID()	{ return SHORT2FROMMP(mp2); }
};

class _EXPORT_ wFileErrorMsg : public wMessage
{
	public:
		ushort	&ErrorID()	{ return SHORT2FROMMP(mp1); }
};

class _EXPORT_ wStdFileDialog : public wDialogWindow
{
	protected:
		FILEDLG	    *data;
		ulong		drivearr;
		bStringList *typelist;
		bString		title, ok, initfile, inittype;
		char		initdrv[3];
		wPointl		pnt;

	public:
		wStdFileDialog(ushort i=0, short m = DlgModal);
		~wStdFileDialog();

		ushort CreateWindow(wWindow *owner, void *pCreateParams=0);
		long Dispatch(wMessage);
		long Default(wMessage);

		virtual long Filter(wFileFilterMsg m);
		virtual long Validate(wFileValidateMsg m);
		virtual long Error(wFileErrorMsg m);

		bStringList *GetFilesChosen();
		bStringList *GetTypeList()			   { return typelist; }
		bString   GetFirstFile();
		char	  GetInitialDrive()			   { return initdrv[0]; }
	    void	  SetInitialDrive(char drv)    { initdrv[0] = drv; }
		ulong     GetDriveArray()              { return drivearr; }
		void      SetDriveArray(ulong da)	   { drivearr = da; }
		bString   GetInitialFile() 			   	   { return initfile; }
		void 	  SetInitialFile(const char *file) { initfile=file;   }
		bString   GetInitialType() 			  	   { return inittype; }
		void 	  SetInitialType(const char *type) { inittype = type; }
		bString   GetTitle() 				   	   { return title;    }
        void	  SetTitle(const char *t)		   { title = t; 	  }
		bString	  GetOKText()	  			   	   { return ok; 	  }
	    void	  SetOKText(const char *s)		   { ok = s; 		  }

		ulong     GetStyle();
		void   	  ChangeStyle(ulong style, bool fSet = TRUE);
		bool   	  ChangePosition(wPointl p)	   { pnt = p; return TRUE; }
   		wPointl   GetPosition()				   { return pnt;  }
      	void     *GetCreateParams();
		long	  Result();				// DidOK, etc
		ushort    SystemReturnCode();	// Fde*

		bool	  SetStaticText(ushort id, const char *t);
};


class _EXPORT_ wStdFileOpenDialog : public wStdFileDialog
{
	public:
		wStdFileOpenDialog(ushort i=0, short m = DlgModal);
		ushort CreateWindow(wWindow *owner, void *pCreateParams=0);
};
 
class _EXPORT_ wStdFileSaveAsDialog : public wStdFileDialog
{
	public:
		wStdFileSaveAsDialog(ushort i=0, short m = DlgModal);
		ushort  CreateWindow(wWindow *owner, void *pCreateParams=0);
	    bString GetEATypeChosen();
};

#ifndef DID_FONT_DIALOG
struct _FONTDLG;
typedef _FONTDLG FONTDLG;
#endif

class _EXPORT_ wFaceNameChangedMsg : public wMessage
{
	public:
		char *pszFacename()	{ return (char*)mp1; }
};

class _EXPORT_ wPointSizeChangedMsg : public wMessage
{
	public:
		char *pszPointsize()	{ return (char*)mp1; }
		wFixed fxPointSize()	{ return *((wFixed*)(&mp2)); }
};

class _EXPORT_ wStyleChangedMsg : public wMessage
{
	public:
      	ushort      &usWeight();
      	ushort      &usWeightOld();
      	ushort      &usWidth();
      	ushort      &usWidthOld();
      	ulong       &flType();
      	ulong       &flTypeOld();
      	ulong       &flTypeMask();
      	ulong       &flTypeMaskOld();
      	ulong       &flStyle();
      	ulong       &flStyleOld();
      	ulong       &flStyleMask();
      	ulong       &flStyleMaskOld();
};

class _EXPORT_ wUpdatePreviewMsg : public wMessage
{
	public:
		HWND	&hWndPreview() { return *((HWND*)(&mp1)); }
};


class _EXPORT_ wFontFilterMsg : public wMessage
{
	public:
		char	*pszFaceName()	{ return (char*)mp1; }
		ushort	&usFieldId()	{ return SHORT1FROMMP(mp2); }
		ushort	&usFontType()	{ return SHORT2FROMMP(mp2); }
};

class _EXPORT_ wStdFontDialog : public wDialogWindow
{
	private:
		FONTDLG	   *data;
		bString		title, preview;
		bStringList sizes;
		wPresSpace *screen, *printer;
		char		family[FACESIZE];
		wPointl		pnt;
		wFont	   *initfont;
		
	public:
		wStdFontDialog(ushort i=0, short m = DlgModal);
		~wStdFontDialog();

		ushort CreateWindow(wWindow *owner, void *pCreateParams=0);
		long Dispatch(wMessage);
		long Default(wMessage);

		virtual long FaceNameChanged(wFaceNameChangedMsg);
		virtual long Filter(wFontFilterMsg);
		virtual long PointSizeChanged(wPointSizeChangedMsg);
		virtual long StyleChanged(wStyleChangedMsg);
		virtual long UpdatePreview(wUpdatePreviewMsg);

		// noviewprinter-noviewscreen and printerselected-screenselected
		ulong 		GetStateFlags();
		void  		SetStateFlags(ulong fl);

		// fattr_type_kerning, etc, only used if ownerpreviewdraw specified
		ulong		GetFontTypeMask();
		void		SetFontTypeMask(ulong fl);

		// fattr_sel_italic, etc, only used if ownerpreviewdraw specified
		ulong		GetFontStyleMask();
		void		SetFontStyleMask(ulong fl);

		void   		ChangeStyle(ulong style, bool fSet = TRUE);
		ulong  		GetStyle();
		void		ChangePosition(wPointl p)	{ pnt = p; }
   		wPointl 	GetPosition()				{ return pnt;  }
		void		SetTitle(const char *t)		{ title=t; }
		bString		GetTitle()					{ return title; }	
		void		SetPreviewString(const char *p) 	{ preview=p; }
		bString		GetPreviewString()			{ return preview; }
		void		SetInitialFont(wFont *i)	{ initfont = i; }
		wFont	   *GetInitialFont()			{ return initfont; }
		bStringList *PointSizeList()			{ return &sizes; }
		void		SetScreenPresSpace(wPresSpace *ps)	{ screen = ps; }
		wPresSpace *GetScreenPresSpace()		{ return screen; }
		void		SetPrinterPresSpace(wPresSpace *ps)	{ printer=ps; }
		wPresSpace *GetPrinterPresSpace()		{ return printer; }
		void		SetForeground(wColor c);
		wColor		GetForeground();
		void		SetBackground(wColor c);
		wColor		GetBackground();

		wFontDef   *GetFontDef();
		wFont	   *GetFont();
      	void   	   *GetCreateParams();

		long		Result();			// DidCancel,etc
		long		SystemReturnCode();	// Fne*
		bool	  	SetStaticText(ushort id, const char *t);
};

#endif // __STDDLG_HPP
