/*  VCS_ID
 *  $Filename:   forms.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __FORMS_HPP
#define __FORMS_HPP

#if defined(BUILDLIB)
extern "C"
{
	#include "pmforms.h"
}
#else
class dform;
class dregion;
class dfield; 
#endif

#include "dtype.hpp"

class wFormsManager;
class wFormWindow;
class wField;
class wListRegion;
class wEditField;
class wButtonField;
class wComboField;

// Object manager hook interface
class wAttrInterface;
void PMFormSetAttrInterface(wAttrInterface *attip);


class  wFieldRange 
{
	private:
		fDataType *low, *high;

	public:
		wFieldRange(fDataType *l, fDataType *h) {}
	    wFieldRange(wFieldRange &)              {}
	   ~wFieldRange()                           {}

		const fDataType *GetLow()	{ return low;  } 
		const fDataType *GetHigh()  { return high; }
};

/*****************************************************************************
 *
 * FormWindow
 *
 *****************************************************************************/

/* Form options */

#define FmNoEsc			0x00000002L
#define FmPageUp		0x00000020L
#define FmPageDown		0x00000040L
#define FmPaging		(FmPageUp + FmPageDown)
#define FmObjectTypes   0x00000080L
#define FmFreeMovement  0x00000100L
#define FmEnterExit		0x00000200L
#define FmNoAutoTab		0x00000400L

/* action code constants */

enum wFmAction
{
	AcFormQuit,
    AcFormExit,
	AcFormHelp,
	AcFormUp,
    AcFormDown,
    AcFormSet
};

extern "C" 
{
    short _Optlink FormSysFormInit(dform*);
    short _Optlink FormSysFormValidate(dform*);
    short _Optlink FormSysFormSave(dform*);
    short _Optlink FormSysFormQuit(dform*);
};

class _EXPORT_ wFormWindow : public wDialogWindow
{
	private:
		dform* fp;
		wField *firstField;
		wListRegion *firstRegion;
		friend short _Optlink FormSysFormInit(dform*);
		friend short _Optlink FormSysFormValidate(dform*);
		friend short _Optlink FormSysFormSave(dform*);
		friend short _Optlink FormSysFormQuit(dform*);
		friend class wField;
		friend class wListRegion;

	public:
		wFormWindow(ushort dlg_id, short nFields, short nListRegions, short type = DlgModal);
		~wFormWindow();

		ulong    GetOptions();
		void     SetOptions(ulong option, bool fSet = TRUE);
#if defined(BUILDLIB)
		dform* FormStructure() { return fp; }	   /* private to implementation */
#endif
		ushort   GetWindowID();
		void     SetActionButtons(ushort aEsc, ushort aOK, ushort aHelp = 0, ushort aFormUp = 0, ushort aFormDn = 0);
		void     SetMessageWindow(ushort win_id);
		short    InitFields();
		short    InitListRegions();
		void     FormUp(wWindow *owner);
		long     Default(wMessage);
		wField * GetField(ushort win_id);
		wListRegion *GetListRegion(ushort win_id);

	    void     SetNextLogicalField();
        short    ClearFields(short count);
		void     ClearFieldBuffers();
        bool     Convert();
        void     SetModified(bool state = TRUE);
        bool     IsModified();
		bool     IsBlank();
        void     EnableActionButton(wFmAction ac = AcFormExit);
        void     DisableActionButton(wFmAction ac = AcFormExit);
		void     SetValError(ushort error);
		bool     DisplayMessage(const char *msg);
		bool     Exit(wFmAction ac, short nextform);
		void     ForceExit(wFmAction ac, short nextform);
		bool     Quit();

		virtual  short Init();    
		virtual  short Validate();
		virtual  short Save();
		virtual  short ConfirmQuit();

		wField  *FirstField();
		short	 GetFieldCount();
		bool	 AddField(wField *fld);
		bool	 AddListRegion(wListRegion *lregp); 
		wField	*GetCurrentField();
};

typedef long (wFormWindow::*FormEventMethod)();
#define FORMMETHOD(cl,mt) ((FormEventMethod)&cl::mt)

/*****************************************************************************
 *
 * Field classes
 *
 *****************************************************************************/

/* General field options */

#define FsLastField   	0x00000008L
#define FsRegion        0x00000040L
#define FsLastRegFld    0x00000100L
#define FsAttrIntf		0x01000000L

enum wFieldType
{
	FtEdit,
    FtCombo,
	FtPushButton,
    FtCheckBox, 
	FtRadioButton,
  	FtControl
};

extern "C" 
{
	short _Optlink FormSysFieldValidate(dform* fp, dfield* dfp, char *fldbuf);
	short _Optlink FormSysFieldEnter(dform* fp, dfield* dfp);
	short _Optlink FormSysFieldExit(dform* fp, dfield* dfp);
};

class _EXPORT_ wField
{
	private:
		wField *nextField;
		short (wFormWindow::*enterfn)(wField *fld);
		short (wFormWindow::*exitfn)(wField *fld);
		friend short _Optlink FormSysFieldValidate(dform* fp, dfield* dfp, char *fldbuf);
		friend short _Optlink FormSysFieldEnter(dform* fp, dfield* dfp);
		friend short _Optlink FormSysFieldExit(dform* fp, dfield* dfp);
		friend class wFormWindow;

	protected:
		short (wFormWindow::*valfn)(wField *fld, char *fldbuf);
		short (wFormWindow::*clkfn)(wField *fld, short status);
		dfield* fldp;
		wFormWindow *fp;
		wFieldType fldType;
		ushort dataType;

	public:
		wField(short width, short win_id, ulong options);
		virtual ~wField();

#if defined(BUILDLIB)
		dfield* FieldStructure() { return fldp;  }
#endif
		ulong  GetOptions();
		void   SetOptions(ulong option, bool fSet = TRUE);
		wFormWindow *GetForm() 	   { return fp; }
		void  *GetFieldBuffer();
		void   SetFieldBuffer(void *datap);
		ushort GetWindowID();
		short  GetDataType()	   { return dataType; }
		wFieldType GetFieldType();

		void   SetFocus();
		void   Enable();
		void   Disable();
		bool   Convert();
		bool   Update();
		void   ClearFieldBuffer();
		void   SetModified(bool state = TRUE);
        bool   IsModified();
		bool   IsBlank();
		void   SetFieldEnterFn(FormEventMethod entf)  { enterfn = (short (wFormWindow::*)(wField *))entf; }
		void   SetFieldExitFn(FormEventMethod extf)   { exitfn  = (short (wFormWindow::*)(wField *))extf; }
		bool   ChangeColor(wWindowColor attr, wColor c, bool fRGB = FALSE);
		bool   ChangeFont(wStdFont f);

		virtual short Init();
		virtual short Enter();   
		virtual short Exit();	 

		wField *NextField();
};


/* Edit field options */

#define FsRequired	    0x00000001L	  
#define FsMustFill      0x00000002L
#define FsInitBlank     0x00000004L
#define FsFixedLen      0x00000020L
#define FsReadOnly      0x00000080L
#define FsStripZeros    0x00000200L
#define FsUnReadable    0x00010000L
#define FsFieldType     0x00100000L
#define FsAutoMask		0x00000400L

enum wMaskOption
{
	MkDefault,
	MkWithMaskChars,
	MkWithoutMaskChars
};

class _EXPORT_ wEditField	: public wField
{
	protected:
		wField::fldType;

	public:
		wEditField(ushort dataTypeID, short width, short winId, void *datap, const char *pPic = NULL, ulong options = 0L);
		wEditField(ushort dataTypeID, short width, short winId, const char *attrName, void **objptr, const char *pPic, ulong options);

		void    SetInputRange(wFieldRange);
		void    SetFieldValidateFn(FormEventMethod valf)  { valfn = (short (wFormWindow::*)(wField *, char*))valf; }
		bool    SetText(const char *pzText, wMaskOption = MkDefault);
		bString GetText(wMaskOption = MkDefault);
		void    Clear();
		void	SetEditMask(const char *mask, bool fInclMask = TRUE);

		virtual short Validate(char *);
};

class _EXPORT_ wComboField : public wEditField
{
	public:
		wComboField(ushort dataTypeID, short width, short win_id, void *datap, const char *picp = NULL, ulong options = 0L);
		wComboField(ushort dataTypeID, short width, short win_id, const char *attrName, void **objptr, const char *picp, ulong options);
		short AddString(const char *str, short index = LiEnd);
		short SetString(const char *str, short index);
		short SelectItem(short index, short select);
		short DeleteString(short index);
		bool  DeleteAll();
		short GetItemCount();
};


class _EXPORT_ wButtonField : public wField
{
	protected:
		wField::fldp;
		wField::dataType;

	public:
		wButtonField(wFieldType fldType, short width, short win_id, short *datap, ulong options);

		void    SetFieldClickFn(FormEventMethod valf)  { clkfn = (short (wFormWindow::*)(wField *, short))valf; }
		virtual short Click(short newValue);
};

class _EXPORT_ wPushButtonField : public wButtonField
{
	public: 
		wPushButtonField(ushort win_id);

		bool SetImage(wIcon *icon);
		bool SetImage(wBitmap *bitmap);
};

/* CheckBox field options */

#define FsNull3State    0x00000800L
#define Fs3State		0x00000400L
#define FsLongBuffer	0x02000000L

class _EXPORT_ wCheckBoxField : public wButtonField
{
	public:
		wCheckBoxField(ushort win_id, short *datap, ulong options = 0);
		wCheckBoxField(ushort win_id, long *datap, ulong options = 0);
		wCheckBoxField(ushort win_id, const char *attrName, void **objptr, ulong options = 0);

		short GetValue();
		bool  SetValue(short fldval);
		void  Clear();
};

/* RadioButton field options */

#define FsRadioClear    0x00008000L

class _EXPORT_ wRadioButtonField : public wButtonField
{
	public:
		wRadioButtonField(ushort win_id, ushort nBtns, short *datap, ulong options = 0);
		wRadioButtonField(ushort win_id, ushort nBtns, long *datap, ulong options = 0);
		wRadioButtonField(ushort win_id, ushort nBtns, const char *attrName, void **objptr, ulong options = 0);

		short GetValue();
		bool  SetValue(short fldval);
		void  Clear();
};

class _EXPORT_ wControlField : public wField
{
	public:
		wControlField(ushort win_id);
};


/*****************************************************************************
 *
 * List Region
 *
 *****************************************************************************/

/* List region options */

#define LrEnterExit	 0x00000001L
#define LrNoClear    0x00000004L
#define LrNoDelete   0x00000010L

#define LrNoProc	 (-2)

#define RegInsert	0
#define RegModify   1
#define RegDelete	2

extern "C"
{
	short _Optlink FormSysRegionSelect(dform*, dregion*);
	short _Optlink FormSysRegionEnter(dform*, dregion*);
	short _Optlink FormSysRegionProcItem(dform*, dregion*, char *, char **, short);
	short _Optlink FormSysRegionQuerySelect(dform*, dregion*, short);
};

class _EXPORT_ wListRegion 
{
	private:
		wFormWindow *fp;
		wListRegion *nextRegion;
		dregion* regp;
		short (wFormWindow::*selectfn)(wListRegion *reg, short item);
		short (wFormWindow::*enterfn)(wListRegion *reg, short item);
		short (wFormWindow::*procfn)(wListRegion *reg, char *itemtext, char **prevdata, short cmd);
		short (wFormWindow::*qselfn)(wListRegion *reg, short item);
		friend short _Optlink FormSysRegionSelect(dform*, dregion*);
		friend short _Optlink FormSysRegionEnter(dform*, dregion*);
		friend short _Optlink FormSysRegionProcItem(dform*, dregion*, char *, char **, short);
		friend short _Optlink FormSysRegionQuerySelect(dform*, dregion*, short);
		friend class wFormWindow;

	public:
		wListRegion(ushort idListBox, ulong options = 0L);

#if defined(BUILDLIB)
		dregion* RegionStructure()   { return regp; }
#endif
		wFormWindow *GetForm()   	       { return fp; }
		ulong        GetOptions();
		void         SetOptions(ulong option, bool fSet = TRUE);
		ushort 	     GetWindowID();

		bool    AddGroupObject(ushort win_id, short width, ulong colOptions = ColLeft);
        bool    AddGroupObject(ushort win_id);
        void    SetIndent(short i);
        void    SetInsertIndex(short iItem); 
	  	short   SplitColumnText(char *pzText, char **pDest, short cFields);
		char   *ExtractColumnText(char *pzText, char *pBuf, short nColumn, short fTags = FALSE);
		char   *SetColumnText(char *pzText, char *pBuf, short nColumn);
		char   *BuildItemText(char *pzBuf);
        bool    ConvertItemText(short item);
		bString GetItemText(short item);
	  	bString GetCurrentItemText();
	  	short   GetCurrentItem();
		short   InsertItemText(const char *itemText, short item = LiEnd);
		bool    ChangeItemText(const char *itemText, short item);
		bool    SelectItem(short item, bool fSelect = TRUE);
	  	short   DeleteItem(short item);
	  	bool    DeleteAllItems();
        void    ClearModified();
		short   GetItemCount();
		bool    ChangeColor(wWindowColor attr, wColor c, bool fRGB = FALSE);
		bool    ChangeFont(wStdFont f);
		wListRegion *NextRegion()			 { return nextRegion; }

		void  SetSelectFn(FormEventMethod fn)  		{ selectfn = (short (wFormWindow::*)(wListRegion *, short))fn; }
		void  SetEnterFn(FormEventMethod fn)   		{ enterfn = (short (wFormWindow::*)(wListRegion *, short))fn; }
		void  SetProcItemFn(FormEventMethod fn)   	{ procfn = (short (wFormWindow::*)(wListRegion *, char*, char**, short))fn; }
		void  SetQuerySelectFn(FormEventMethod fn)  { qselfn = (short (wFormWindow::*)(wListRegion *, short))fn; }

		virtual short Init();
        virtual short Select(short item);   
		virtual short ProcItem(char *itemtext, char **prevdata, short cmd);
	  	virtual short Enter(short item);
	  	virtual short QuerySelect(short item);
};

#endif // __FORMS_HPP
