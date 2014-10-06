/*	VCS_ID
 *	$Filename:	 Windows.hpp
 *	$Author  :	 John Pompeii
 *	$Revision:	 1.8  $
 *	$Date:	 16 Jan 1992 17:14:08  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __WINDOWS_HPP
#define __WINDOWS_HPP

#include "windefs.h"

#if defined(BUILDLIB)
extern "C" {
	#include "objwinx.h"
#ifndef ObjectPMLite
	#include "cellbox.h"
#endif
}
#endif
#include "pmtypes.hpp"

/*****************************************************************************
 * 
 * Primary data types and constructs 
 * 
 *****************************************************************************/


class	wCoord
{
	protected:
		long a;
		long b;
	public:
		wCoord () { a = 0; b = 0; }
		wCoord (long A, long B) {	a = A;	b = B;	}
};

class _EXPORT_ wPointl : public wCoord
{
	public:
		wPointl ( ) { }
		wPointl (long X, long Y, wWinCoordUnit type = DevUnits);
		wPointl (long X, long Y, wPresSpace *ps);

		long xSet(long X, wWinCoordUnit type = DevUnits);
		long ySet(long Y, wWinCoordUnit type = DevUnits);
		long xSet(long X, wPresSpace *ps);
		long ySet(long Y, wPresSpace *ps);

		long& x() { return	a; }
		long& y() { return	b; }

		wPointl operator+(wPointl p2)
			{ return wPointl(x()+p2.x(), y()+p2.y()); }
		wPointl& operator+=(wPointl p2)
			{ x()+=p2.x(); y()+=p2.y(); return *this; }
		wPointl operator-(wPointl p2)
			{ return wPointl(x()-p2.x(), y()-p2.y()); }
		wPointl& operator-=(wPointl p2)
			{ x()-=p2.x(); y()-=p2.y(); return *this; }
		int operator==(wPointl p2)
			{ return x()==p2.x() && y()==p2.y(); }
		int operator!=(wPointl p2)
			{ return x()!=p2.x() || y()!=p2.y(); }
};

class _EXPORT_ wDimension	: public wCoord
{
	public:
		wDimension ( ) { }
		wDimension (long X, long Y, wWinCoordUnit type = DevUnits);
		wDimension (long X, long Y, wPresSpace *ps);

		long SetxWidth(long X, wWinCoordUnit type = DevUnits);
		long SetyHeight(long Y, wWinCoordUnit type = DevUnits);

		long SetxWidth(long X, wPresSpace *ps);
		long SetyHeight(long Y, wPresSpace *ps);

		long& xWidth()	{ return a; }
		long& yHeight() { return b; }

		wDimension operator+(wDimension d2)
			{ return wDimension(xWidth()+d2.xWidth(), yHeight()+d2.yHeight()); }
		wDimension& operator+=(wDimension d2)
			{ xWidth()+=d2.xWidth(); yHeight()+=d2.yHeight(); return *this; }
		wDimension operator-(wDimension d2)
			{ return wDimension(xWidth()-d2.xWidth(), yHeight()-d2.yHeight()); }
		wDimension& operator-=(wDimension d2)
			{ xWidth()-=d2.xWidth(); yHeight()-=d2.yHeight(); return *this; }
		int operator==(wDimension d2)
			{ return xWidth()==d2.xWidth() && yHeight()==d2.yHeight(); }
		int operator!=(wDimension d2)
			{ return xWidth()!=d2.xWidth() || yHeight()!=d2.yHeight(); }
};

class _EXPORT_ wRange : public wCoord
{
	public:
		wRange(long l=0, long h=0) : wCoord (l,h) {};
		long& Low()  { return a; }
		long& High() { return b; }
};

class _EXPORT_ wRectl 
{
	private:
		long xL, yB, xR, yT;
	public:
		wRectl() { xL = 0L; yB = 0L; xR = 0L; yT = 0L; }
		wRectl(long XL, long YB, long XR, long YT, wWinCoordUnit type = DevUnits);
		wRectl(long XL, long YB, long XR, long YT, wPresSpace *ps);
		wRectl(wPointl o, wDimension s);			  

		long SetxLeft(long XL, wWinCoordUnit type = DevUnits);
		long SetyBottom(long YB, wWinCoordUnit type = DevUnits);
		long SetxRight(long XR, wWinCoordUnit type = DevUnits); 
		long SetyTop(long YT, wWinCoordUnit type = DevUnits);	

		long SetxLeft(long XL, wPresSpace *ps);
		long SetyBottom(long YB, wPresSpace *ps);
		long SetxRight(long XR, wPresSpace *ps); 
		long SetyTop(long YT, wPresSpace *ps);	 

		long& xLeft() { return	xL; }
		long& yBottom() { return yB; }
		long& xRight() { return xR; }
		long& yTop() { return yT; }
		wPointl Position() { return wPointl(xL, yB); }
		wPointl Corner() { return wPointl(xR, yT); }
		wDimension Size()  { return wDimension(xR - xL, yT - yB); }
		bool   PtInRectangle(wPointl p);
		wRectl &Normalize();
		wRectl Stretch(long amt) { xL-=amt; yB-=amt; xR+=amt; yT+=amt; return *this; }
		bool   IsEmpty() { return (xR<=xL || yT<=yB); }

		int operator==(wRectl &r2)
			{ return xL==r2.xL && yB==r2.yB && xR==r2.xR && yT==r2.yT; }
		int operator!=(wRectl &r2)
			{ return xL!=r2.xL || yB!=r2.yB || xR!=r2.xR || yT!=r2.yT; }

		wRectl& operator+=(wPointl &p)	
			{ xL+=p.x(); xR+=p.x(); yB+=p.y(); yT+=p.y(); return *this; }
		wRectl& operator-=(wPointl &p)	
			{ xL-=p.x(); xR-=p.x(); yB-=p.y(); yT-=p.y(); return *this; }
		wRectl& operator+=(wDimension &d)	
			{ xR+=d.xWidth(); yT+=d.yHeight(); return *this; }
		wRectl& operator-=(wDimension &d)	
			{ xR-=d.xWidth(); yT-=d.yHeight(); return *this; }
		wRectl &operator |= (wRectl r);
		wRectl &operator &= (wRectl r);
};

class _EXPORT_ wColor
{
	private:
		long clr;

	public:
		wColor()				{ clr = 0; }
		wColor(long index)	{ clr = index; }
		wColor(uchar red, uchar green, uchar blue)	{ clr = 0;
													 ((RGB *)&clr)->bRed = red;
													 ((RGB *)&clr)->bGreen = green;
													 ((RGB *)&clr)->bBlue = blue;
												   }
		wColor(RGB *color)	{ clr=0; *((RGB *)&clr) = *color; }
		wColor(wColor& c)		{ clr = c.clr; } 
		operator long() 	{ return clr; }
		uchar& Red()		{ return (uchar &)((RGB *)&clr)->bRed;	 } 
		uchar& Green()		{ return (uchar &)((RGB *)&clr)->bGreen; } 
		uchar& Blue()		{ return (uchar &)((RGB *)&clr)->bBlue;  } 
};


/*****************************************************************************
 * 
 * Message event classes 
 * 
 *****************************************************************************/


#define SUBCLASSEDMSG 0x8000
#define NOTIFIERMSG    0x4000

class _EXPORT_ wMessage
{
	public:
		wWindow *pwin;
		ulong msg;		// the message type
		MPARAM mp1; 
		MPARAM mp2;
		ushort msgf;

		wMessage(ulong _msg, MPARAM _mp1, MPARAM _mp2, wWindow *pw = 0) 
				 { pwin = pw; msg = _msg; mp1 = _mp1; mp2 = _mp2; msgf = 0; }

		wMessage() {}
		ushort	GetId() const;
		bool	IsControl() const;
};

class _EXPORT_ wCommandMsg : public wMessage
{
	public:
		ushort& usCmd() 	{ return SHORT1FROMMP(mp1); } 
		ushort& isDown()	{ return SHORT2FROMMP(mp1); }
		ushort& cmdSource() { return SHORT1FROMMP(mp2); }
		ushort& fPointer()	{ return SHORT2FROMMP(mp2); }
};		 

class _EXPORT_ wControlMsg : public wMessage
{
	public:
		ushort& id()		   { return SHORT1FROMMP(mp1); }
		ushort& usNotifyCode() { return SHORT2FROMMP(mp1); }
		ulong&	usData()	   { return LONGFROMMP(mp2); }
};

class _EXPORT_ wSizeMsg : public wMessage
{
	public:
		ushort& cxOld()   { return SHORT1FROMMP(mp1); } 
		ushort& cyOld()   { return SHORT2FROMMP(mp1); } 
		ushort& cxNew()   { return SHORT1FROMMP(mp2); } 
		ushort& cyNew()   { return SHORT2FROMMP(mp2); } 

		wDimension sizeOld() { wDimension d(cxOld(), cyOld()); return d; }
		wDimension sizeNew() { wDimension d(cxNew(), cyNew()); return d; }
};

class _EXPORT_ wTimerMsg : public wMessage
{
	public:
		ushort& idTimer() { return SHORT1FROMMP(mp1); }
};

class _EXPORT_ wCreateMsg : public wMessage
{
	public:
		void *pCtlData()	   { return (void *) mp1; }
		WINTYPE pcrst() 	   { return (WINTYPE) mp2; }
		ushort GetId();
		wWindow *GetOwnerWindow();
		wWindow *GetParentWindow();
		wPointl GetPosition();
		wDimension GetSize();
		ulong GetStyle();
		bString GetWindowText();
		bString GetClassName();
};

class _EXPORT_ wInitDlgMsg : public wMessage
{
	public:
		HWND hwndFocus()	   { return (HWND) mp1; }
		void *pCreateParams() { return (void *) mp2; }
};

class _EXPORT_ wActivateMsg : public wMessage
{
	public:
		ushort& fActive() { return SHORT1FROMMP(mp1); }
		HWND& hwnd()	{ return HWNDFROMMP(mp2); }
};

#ifndef ObjectPMLite
class _EXPORT_ wMenuActionMsg : public wMessage
{
	private:
		short fmsgType;
										
	public:
		wMenuActionMsg(ulong _msg, MPARAM _mp1, MPARAM _mp2, wWindow *pw = 0); 
		ushort& usId() { return SHORT1FROMMP(mp1); }
		HWND&	hwndMenu() { return HWNDFROMMP(mp2); }
		short&	actionType() { return fmsgType; }
		ushort& fPost() { return SHORT2FROMMP(mp2); }
};
#endif

#define HORIZONTAL	0
#define VERTICAL	1

class _EXPORT_ wScrollBarMsg : public wMessage
{
	public:
		ushort& id()			   { return SHORT1FROMMP(mp1); }
		ushort& sPos()			   { return SHORT1FROMMP(mp2); }
		ushort& usCmd() 		   { return SHORT2FROMMP(mp2); }
		wScrollBarType direction() { return msg == WM_VSCROLL? Vertical: Horizontal; }
};

class _EXPORT_ wKeyStrokeMsg : public wMessage
{
	public:
		uchar  &RepeatCount()		{ return ((uchar *)(&mp1))[2]; }
		uchar  &ScanCode()			{ return ((uchar *)(&mp1))[3]; }
		ushort &KeyFlags()			{ return ((ushort *)(&mp1))[0]; }
		ushort &VirtualKeyCode()	{ return ((ushort *)(&mp2))[1]; }
		ushort &CharKeyCode()		{ return ((ushort *)(&mp2))[0]; }
		void  SetOptions(ushort fsOptions = (KOP_NUMPADKEYS + KOP_CTRLKEYS));
		bool  IsCharKey()			{ return KeyFlags() & KC_CHAR; }
		bool  IsVirtualKey()		{ return KeyFlags() & KC_VIRTUALKEY; }
		bool  IsShifted()			{ return KeyFlags() & KC_SHIFT; }
		bool  IsCtrlKeyDown()		{ return KeyFlags() & KC_CTRL; }
		bool  IsAltKeyDown()		{ return KeyFlags() & KC_ALT; }
		bool  IsKeyUp() 			{ return KeyFlags() & KC_KEYUP; }
		bool  IsLoneKey()			{ return KeyFlags() & KC_LONEKEY; }
}; 

class _EXPORT_ wFocusChangeMsg : public wMessage
{
	public:
		HWND& hwnd()		 { return HWNDFROMMP(mp1);	 }
		ushort& fFocus()	 { return SHORT1FROMMP(mp2); }
};

#ifndef ObjectPMLite
class _EXPORT_ wFormActionMsg : public wMessage
{
	public:
		ushort &ActionCode()	{ return SHORT1FROMMP(mp1); }
		ushort &NextForm()		{ return SHORT2FROMMP(mp1); }
};
#endif

class _EXPORT_ wSemaphoreMsg : public wMessage
{
	private:
		ushort priority;
	public:
		wSemaphoreMsg(ulong _msg, MPARAM _mp1, MPARAM _mp2, wWindow *pw = 0);
		ushort& usPriority()   { return priority; }
		ulong &flFlags()	   { return LONGFROMMP(mp1); }
};

class _EXPORT_ wIPFHelpMsg : public wMessage
{
	public:
		ushort &id()			{ return SHORT1FROMMP(mp1); }
		ulong  &ulError()		{ return LONGFROMMP(mp1);	}
		ushort &usMode()		{ return SHORT1FROMMP(mp1); }
		ushort &idTopic()		{ return SHORT1FROMMP(mp2); }
		ushort &idSubTopic()	{ return SHORT2FROMMP(mp2); }
};

class _EXPORT_ wButtonClickMsg : public wMessage
{
	private:
		ushort	bnum;
		ushort	activity;
	public:
		wButtonClickMsg(ulong _msg, MPARAM _mp1, MPARAM _mp2, wWindow *pw = 0);
		ushort& usButtonNum() {return bnum;}
		ushort& usActivity() {return activity;}
		ushort& x() { return SHORT1FROMMP(mp1); }
		ushort& y() { return SHORT2FROMMP(mp1); }
		ushort& keyFlags() { return SHORT2FROMMP(mp2); }
		wPointl Position() { return wPointl((long)x(), (long)y()); }
};

class _EXPORT_ wMouseMoveMsg : public wMessage
{
	public:
		ushort& x() { return SHORT1FROMMP(mp1); }
		ushort& y() { return SHORT2FROMMP(mp1); }
		ushort& usHit() { return SHORT1FROMMP(mp2); }
		ushort& keyFlags() { return SHORT2FROMMP(mp2); }
		wPointl Position() { return wPointl((long)(short)x(), (long)(short)y()); }
};


/*****************************************************************************
 * 
 * High level image classes 
 * 
 *****************************************************************************/

#define ResPointer (-1)
#define ResIcon (-1)

class _EXPORT_ wIcon
{
	protected:
		HPOINTER hptr;

	public:
		wIcon() { hptr = NULL; }
		wIcon(short iptr, ushort resId = 0);		
		~wIcon();

		HPOINTER& hIcon() { return hptr; }
		bool Draw(wPresSpace *ps, wPointl pos, ushort drawFlags = 0);
		bool Draw(wPresSpace *ps, wRectl r);
};

#ifndef ObjectPMLite
class _EXPORT_ wFileIcon : public wIcon
{
	private:
		bString filename;
		bool priv;

	protected:
		wIcon::hptr;

	public:
		wFileIcon(const char *fn, bool isprivate=FALSE);
		~wFileIcon();

		bool IsPrivate() { return priv; }
		bString Filename() { return filename; }
};
#endif

class _EXPORT_ wPointer : public wIcon
{
	public:
		wPointer() {}
		wPointer(short iptr, ushort resId = 0) : wIcon (iptr, resId) {} 	

		HPOINTER& hPointer() { return hptr; }
		wPointl GetPosition();
		bool	Move(wPointl);
		void	Hide();
		void	Show();
};

class _EXPORT_ wCursor
{
	private:
		HWND hwnd;

	public:
		wCursor(wWindow *parent, wPointl pos, wDimension sz, ushort fs = CsCursorFlash);
		~wCursor();

		void		Hide();
		void		Show();
		wDimension	GetSize();
		bool		ChangeSize(wDimension szCursor);
		wPointl 	GetPosition();
		bool		ChangePosition(wPointl pos);
		ushort		GetStyle();
		bool		ChangeStyle(ushort fs);
		bool		SetClipRectangle(wRectl *clp);
		wRectl		GetClipRectangle();
};


/*****************************************************************************
 * 
 * Base window & workplace classes
 * 
 *****************************************************************************/

// structure used by internal window procedures
// for sizing and MDI functions

struct SubWin
{
	PFNWP pWindowProc;
	SIZEL maxFrameSize;
	SIZEL minFrameSize;
};

/* Standard wWindow Types */

#define OBJPM_DESKTOP		0x00000001L
#define OBJPM_OBJECT		0x00000002L 				 
#define OBJPM_FRAME 		0x00000004L
#define OBJPM_DIALOG		0x00000008L
#define OBJPM_FORM			0x00000010L
#define OBJPM_NONREG		0x00000020L
#define OBJPM_MDIDOCUMENT	0x00000040L
#define OBJPM_MDIDESKTOP	0x00000080L
#define OBJPM_CONTROL		0x00000100L
#define OBJPM_PAGE			0x00000200L
#define OBJPM_FILEDIALOG	0x00000400L
#define OBJPM_FILEOPENDIALOG	0x00000800L
#define OBJPM_FILESAVEASDIALOG	0x00001000L
#define OBJPM_SHADOWCONTROL 0x00002000L

#define ENUM_ALL			0x40000000L

/* Process level (common-thread) global variables */

#if defined(BUILDLIB)
    extern wWindow *pDesktopWindow;
    extern wWindow *pObjectWindow;
    extern HMODULE rscHMODULE;
#endif

wWindow **GetDesktopWindow();
wWindow **GetObjectWindow();
#define DesktopWindow (*GetDesktopWindow())
#define ObjectWindow (*GetObjectWindow())

class _EXPORT_ wWindowClass 
{
    protected:
        tNameNode<wWindowClass> link;

	public:
		wWindowClass(const char *classname, ulong style);
        void    Alias(const char* alias);
        bool    isAlias() const { return link.What()!=this; }

		virtual wWindow *Create(HWND hwnd);
		virtual void Destroy(wWindow *);

        static wWindowClass* FindClass(HWND hwnd);
};

/* window indicator */
#define isWindow			0x00000001
#define separateClient		0x00000002

/* drag capabilities */
#define NoDragCaps			0x00000000
#define Dragable			0x00000002
#define DragTarget			0x00000004

/* supported operations */
#define Moveable			0x00000010
#define Copyable			0x00000020
#define Linkable			0x00000040

/* source control flags */
#define DCOpen				0x00000100
#define DCRef				0x00000200
#define DCGroup 			0x00000400
#define DCContainer 		0x00000800
#define DCPrepare			0x00001000
#define DCRemoveableMedia	0x00002000

/* message support flags */
#define RedirectCtlMsgs 	0x00004000

/* container item record core type */
#define MiniRecordCore		0x00008000

/* drag image usage options */
enum DragImageUseOpt
{
	UseDragImage = 0,
	NoDragImage = 0x00010000,
	UseShadowIcon = 0x00020000
};
		
/* status flags */
#define RelativeDragImage	0x00040000


class _EXPORT_ wObjectExchange
{
	private:
		bString mech, fmt;

	public:
		wObjectExchange() {};
		wObjectExchange(const char *m, const char *f);
		~wObjectExchange();

		void	SetMechanism(const char *m) { mech = m;    }
		bString GetMechanism(void)			{ return mech; }
		void	SetFormat(const char *f)	{ fmt = f;	   }
		bString GetFormat(void) 			{ return fmt;  }
		bString BuildElement(void); 	
		bool	Parse(const char *);

};

class _EXPORT_ wObjectExchangeList : public tDList<wObjectExchange>
{
	public:
		wObjectExchangeList();

		wObjectExchange *NativeRMF();
		bString BuildElementString();
		bool Parse(const char *);
};

class _EXPORT_ wBeginDragMsg : public wMessage
{
	public:
		ushort &usPointer() { return SHORT1FROMMP(mp1); }
		wPointl GetPosition() { return wPointl(SHORT1FROMMP(mp2), SHORT2FROMMP(mp2)); }
		void SetPosition(wPointl p);
};

class _EXPORT_ wDragImage
{
	private:
		ulong	type;
		ushort	cnt;
		LHANDLE handle;
		wDimension size;
		friend class wWorkplaceObject;

	public:
		wDragImage(wIcon *p, bool fTransparent = FALSE);
		wDragImage(wBitmap *p);
		wDragImage(wPointl *p, ushort countPts, bool fClose = FALSE);
	   ~wDragImage();

		wDragImageType GetType();
		void SetImageSize(wDimension siz);
		wDimension GetImageSize()				{ return size;	 }

		LHANDLE hDragImage()					{ return handle; }
		ushort	GetPointCount() 				{ return cnt;	 }
};

#define WORKPLACEOBJECTLIST "__WorkplaceObjectList"

class _EXPORT_ wDragInfo
{
	private:
		ulong	*arr;
		ushort	count;
		bool	created;
		wPointl loc;

	public:
		wDragInfo(DRAGINFO *pdi, wWorkplaceObject *wpo);
	   ~wDragInfo();

		wWorkplaceObject **Objects() { return (wWorkplaceObject**)arr; }
		ushort	Count() 			 { return count;}	
		wPointl &Location() 		 { return loc; }
};

class _EXPORT_ wRenderRequest
{
	private:
		wWorkplaceObject	*obj, *target;
		wObjectExchange em;
		bString 		targetname;
		bool			created;
		long			lparam;
		ushort			operation;

	public:
		wRenderRequest(DRAGTRANSFER *);
		~wRenderRequest();

		wWorkplaceObject *RenderWorkplaceObject()	{ return obj; }
		wWorkplaceObject *TargetWorkplaceObject()	{ return target; }
		wObjectExchange  *ExchangeMethod()			{ return &em; }
		bString TargetName()	{ return targetname; }
		long   LParam() 		{ return lparam; }	
		ushort Operation()		{ return operation; }
		
};

class _EXPORT_ wWorkplaceObject : public bEventListener
{
	private:

		friend class wDragInfo;
		friend class wRenderRequest;

		class ddinfo 
		{
			public:
				bString 			type, trueType, target, cntrName;
				wObjectExchangeList exl;
				wPointl 			imgOffset;
				wDragImage			*dimg;
				ulong				dragid;
				DRAGTRANSFER		*xfer;
				DRAGITEM			*pdi;

				ddinfo() {dimg = NULL; dragid = 0; xfer = NULL; pdi = NULL;}
				~ddinfo() {};
		};

		wWorkplaceObject *parent;
		ddinfo *dd;
		bString name;

		void SetupStruct();

	protected:
		HWND  hwnd;
		ulong flags;

	public:
		wWorkplaceObject(bool _isWindow);
		wWorkplaceObject(DRAGITEM *pdi, bool);	// bool to differentiate it
		virtual ~wWorkplaceObject();

		HWND&	hWindow()	{ return hwnd; }

		void	SetType(const char *s);
		void	SetTrueType(const char *s);
		void	SetName(const char *s);
		void	SetTargetName(const char *s);
		void	SetContainerName(const char *s);
		void	SetDragImage(wDragImage *img);
		void	SetDragImagePosition(wPointl pos, bool fRelative = FALSE);	// JOHN
		void	SetParent(wWorkplaceObject *p)	{ parent = p; }
		void	SetDragCapabilities(ushort caps);
		void	SetDragImageUse(DragImageUseOpt opt);

		bString GetType();
		bString GetTrueType();
		bString GetName();
		bString GetTargetName();
		bString GetContainerName();
		ulong	GetDragID();
		wDragImage *GetDragImage();
		wPointl 	GetDragImagePosition();  // JOHN
		wWorkplaceObject *GetParent()	{ return parent;	}
		ulong	GetDragCapabilities()	{ return flags; 	}

		wObjectExchangeList *ExchangeMethods();
		bool	AddExchangeMethod(wObjectExchange *oexp);

		virtual bool GetItemsToDrag(tDList<wWorkplaceObject> *wpol, wPointl ppos);
		virtual bool FormatDragItem(DRAGITEM *Dragitem);

		virtual long BeginDrag(wBeginDragMsg m);	// JOHN
		virtual long DragOver(wDragInfo *arr);
		virtual long DragLeave(wDragInfo *arr);
		virtual long Drop(wDragInfo *arr);
		virtual long DropHelp(wDragInfo *arr);
		virtual long Render(wRenderRequest *req);
		virtual void RenderComplete(wWorkplaceObject *obj, ushort result);
		virtual long EndConversation(ulong dragid);

		long SendRenderRequest(wWorkplaceObject *obj, wObjectExchange *reqMeth, 
							   const char *targetName, long lparam, ushort operation); 
		 
		bool PostRenderComplete(wRenderRequest *rr, ushort result, bool retry=TRUE);
		long SendEndConversation(wWorkplaceObject *wpo);
		bool FreeDragInfoResources();
		bool FreeDragTransferResources();

		// *NEW* JOHN 
		bool VerifyNativeExchangeMethod(wObjectExchangeList *exList);
		bool VerifyExchangeMethod(wObjectExchangeList *exList);
		bool VerifyType(bString type);
		bool VerifyTrueType(bString type);

		void SetDragOptions(ulong opt);
	
		bool IsWindow() 		   { return flags & isWindow;	}
		bool IsDragTarget() 	   { return flags & DragTarget; }
		bool IsDragable()		   { return flags & Dragable;	}
		bool IsMoveable()		   { return flags & Moveable;	}
		bool IsCopyable()		   { return flags & Copyable;	}
		bool IsLinkable()		   { return flags & Linkable;	}

		virtual bool Emphasize(bool emph, bool target=TRUE);
		virtual long Print(wPrinterSetup *prDest);	  // dragged to printer
		virtual long Shred(wDragInfo *arr); 		  // dragged to shredder
};

typedef tDList<wWorkplaceObject> wWorkplaceObjectList;

class _EXPORT_ wWindow : public wWorkplaceObject
{
	protected:
		struct SubWin subWin;
		HPS hps;
		HPOINTER hlptr;
		wDispatchTable *dt;
		wWindow *pNextWin, *parent, *owner, *pCurrEnum;
		wPresSpace *pWinPS;
		wPointer *waitptr, *oldptr;
		wRectl invRect;
		ulong fType, enumTypes;
#ifndef ObjectPMLite
		wMenu *menuPtr;
#endif
		wWorkplaceObject::hwnd;
		wWorkplaceObject::flags;

	public:
		wWindow(bool fRegister = TRUE);
		~wWindow();
		virtual long Dispatch( wMessage );
		virtual long Default( wMessage );

		HPS&	 hPS()				{ return hps; }
#ifndef ObjectPMLite
		wMenu *&   MenuBar()		{ return menuPtr; }
#endif
		wWindow * NextWindow()		{ return pNextWin; }
		wWindow *& ParentWindow()	{ return parent; }
		wWindow *& OwnerWindow()	{ return owner;  }
		wPresSpace *& WindowPS()	{ return pWinPS; }
		wRectl		InvalidRectangle() { return invRect; }
		ulong&	WindowType()	   { return fType;	 }
		SubWin *SubclassStruc()    { return &subWin; }

		bool	CreateWindow(wWindow *pwin, ushort id, wPointl p, wDimension d, ulong style = WsVisible);
		bool	DestroyWindow();
		bool	ChangeSize(wDimension d);
		wDimension GetSize();
		bool	HitTest(wPointl p);
		wRectl	WindowRectangle(short RelPos = PosRelSelf);
		bool	ChangePosition(wPointl p);
		bool	ChangePosition(ushort pos, wWindow *pwin = NULL, wDimension *margin = NULL);
		wPointl GetPosition(); 
		wPointl GetPointerPosition(short RelPos = PosRelSelf);
		bool	SetID(ushort id);
		ushort	GetID();

		bool	PositionBehind(wWindow *w);
		bool	PositionInFrontOf(wWindow *w);

		bool	ChangeColor(wControlType type, wWindowColor attr, wColor c, bool fRGB = FALSE);
		bool	ChangeColor(wWindowColor attr, wColor c, bool fRGB = FALSE);
		bool	GetColor(wWindowColor attr, wColorAttrType t, wColor *pc, wColorAttrType *pret);
		bool	ChangeFont(wControlType type, wStdFont f);
		bool	ChangeFont(wStdFont f);
		bool	ChangeParent(wWindow *p, bool fRedraw = FALSE, bool fFrame = FALSE);
		bool	ChangeOwner(wWindow *p, bool fFrame = FALSE);
#ifndef ObjectPMLite
		wMenu  *ChangeMenu(wMenu *);
#endif
		bool	CaptureMouse();
		void	ReleaseMouseCapture();
		bool	IsMouseCaptured(bool fSpecific = FALSE);
		bool	IsEnabled();
		bool	IsVisible();
		bool	IsFocusWindow(bool checkChildren=TRUE);
		bool	IsDestroyed();
		void	ToTop();
		bool	ConvertWindowPoint(wPointl *pt, wWindow *towin, short count = 1);
		ulong	PostMessage(wMessage m);
		void	Enable(bool enable=TRUE);
		void	Disable();
		void	EnableUpdate(bool enable=TRUE);
		void	DisableUpdate();
		ulong	GetStyle();
		void	ChangeStyle(ulong style, bool fSet = TRUE);
		bool	SetFocus();
		void	RePaint(bool fPaintNow = FALSE);
		void	RePaint(wRectl r, bool fPaintNow = FALSE);
		void	BeginPaint();
		void	EndPaint();
		short	Scroll(wDimension xyAmt);
		short	Scroll(wDimension xyAmt, wRectl scroll, wRectl *clip = NULL, 
					   wRegion *update = NULL, wRectl *invalid = NULL, ushort fs = SwInvalidateRgn);
		void	StartTimer(ushort DelayMs, ushort id = 0);
		void	StopTimer(ushort id = 0);
		static bool Alarm(AlarmType typ);
		bool	Flash(bool flash=TRUE);

		wPointer *ChangePointer(wPointer *);
		short	HourGlass();			 
		void	EnumChildWindows(ulong lSortFlags);
		wWindow *NextChildWindow();

		/* wMessage handlers */
		virtual long Create(wCreateMsg);
		virtual long Destroy(wMessage);
		virtual long InitDlg(wInitDlgMsg);
		virtual void Paint()  {}
		virtual long MenuCommand(wCommandMsg);
		virtual long PushButtonCommand(wCommandMsg);
		virtual long Control(wControlMsg);
		virtual long Size(wSizeMsg);
		virtual long Move(wMessage);
		virtual long TimeOut(wTimerMsg);
		virtual long ButtonClick(wButtonClickMsg);
		virtual long Activate(wActivateMsg);
		virtual long Close(wMessage);
#ifndef ObjectPMLite
		virtual long MenuAction(wMenuActionMsg);
		virtual void FormAction(wFormActionMsg);
#endif
		virtual long MouseMove(wMouseMoveMsg);
		virtual long ScrollBarChange(wScrollBarMsg);
		virtual long SaveApplication(wMessage);
		virtual long KeyStroke(wKeyStrokeMsg);
		virtual long FocusChange(wFocusChangeMsg);
		virtual long SemSignal(wSemaphoreMsg);
		virtual long Help(wIPFHelpMsg);

		virtual void Show();
		virtual void Hide();

		bool AddMessageHandler(bEventListener *obj, bEventMethod mt, long msg, ushort id = 0);	
		bool AddMessageHandler(bEventListener *obj, bEventMethod mt, long msg, ushort idFrom, ushort idTo); 
		bool RemoveMessageHandler(long msg, ushort id);
};


#ifndef ObjectPMLite

#define OpmStdFrame (FaShellPosition | FaTaskList | FaSysMenu | FaMinMax | FaTitleBar | FaSizeBorder)

class _EXPORT_ wFrameControl : public wWindow
{
	private:
		FrameControlType typ;

	public:
		wFrameControl(FrameControlType t);
		~wFrameControl();
		bool CreateWindow(wFrameWindow *par, ushort id, wPointl p, wDimension d, ulong style=0);

		FrameControlType	Type() { return typ; }
};

class _EXPORT_ wFrameControlList : public tDList<wFrameControl>
{
	private:
		wFrameWindow	*framewin;
		virtual bNode*	doRemoveNode( bIterator* it=NULL );
		virtual void	doInsertNode( bNode* n, short pos, bIterator* it = NULL );
	public:
		wFrameControlList( wFrameWindow *fr, CompareFunc, bool _fPurge=FALSE );
		wFrameControlList( wFrameWindow *fr, bool _fPurge=FALSE );
		wFrameControlList( const wFrameControlList& other );

		wFrameWindow*	ParentFrameWindow() 	const { return framewin; }
};

class _EXPORT_ wFrameWindow : public wWindow
{
	private:
		HWND hwndFrame, hwndsys, hwndtitle, hwndminmax, hwndmenu;
		wScrollBar *horzScrlBar, *vertScrlBar;
		bString caption;
		wPageWindow *currPage;
		wFrameControlList	*fcl;

		friend class wPageWindow;
		friend void DestroyMdiControls(wFrameWindow *pFrame);

	public:
		wFrameWindow(); 
		~wFrameWindow();

		bool CreateWindow(wWindow *parent, ulong frameAttrib = OpmStdFrame, wWindow *client=NULL);
		bool CreateWindow(ulong frameAttrib = OpmStdFrame, wWindow *client=NULL);
		bool DestroyWindow();
		HWND& hFrame()			 { return hwndFrame; }
		void	SetCaption(const char *caption);
		bString GetCaption();
		void	SetSwitchTitle(const char *);
		bool	SetFrameID(ushort id);
		ushort	GetFrameID();
		bool CreateFrameControls(ulong frameAttrib);
		bool DestroyFrameControls(ulong frameAttrib);
		bool HideFrameControls(ulong frameAttrib);
		bool ShowFrameControls(ulong frameAttrib);
		wScrollBar *HorzScrollBar() { return horzScrlBar; }
		wScrollBar *VertScrollBar() { return vertScrlBar; }
		void Maximize();
		void Minimize();
		void Restore();
		bool AssociateHelp();
		bool IsMinimized();
		bool IsMaximized();
		bool IsActive();
		bool SetIcon(wIcon *);
		void Show();
		void Hide();
		wDimension GetFrameSize();
		wDimension CalcFrameSize(wDimension d); 	// d Is wDimension of a Client Wnd
		wDimension CalcClientSize(wDimension d);	// d Is wDimension of a Frame
		bool ChangeFrameSize(wDimension d);
		bool ChangeFrameSize(wWindow *p);
		bool SetMinimumSize(wDimension d);
		bool SetMaximumSize(wDimension d);
		bool ChangeParent(wWindow *p, bool fRedraw = FALSE);
		bool ChangeOwner(wWindow *p);
		wRectl FrameRectangle(bool RelPos = PosRelSelf);
		bool  ChangePosition(wPointl p);
		bool  ChangePosition(ushort pos, wWindow *pwin = NULL, wDimension *margin = NULL);
		wPointl GetPosition();
		bool ChangeColor(wWindowColor attr, wColor c, bool fRGB);
		bool ChangeFont(wStdFont f);
 
		wPageWindow *CurrentPage()	{ return currPage; }
		bool ChangePage(wPageWindow *);

		wFrameControlList	*FrameControls() { return fcl; }
};

class _EXPORT_ wPageWindow : public wWindow
{
	private:
		tDList<wPageWindow> *childPages;
		wPageWindow *parent;
		wWindow *setWindow;
		friend class wFrameWindow;
	
	public:
		wPageWindow(const char *name);
		wPageWindow(wFrameWindow *frame);
		~wPageWindow();

		bool AddChildPage(wPageWindow *newPage);
		bool RemoveChildPage(wPageWindow *);
		wPageWindow *RemoveChildPage(const char *name);
		wPageWindow *ChildPage(const char *name);
		wPageWindow *OwnerPage()  { return parent;	  }
		wWindow *ViewPortWindow() { return setWindow; }
		bool IsPageSet()		 { return setWindow != 0; }

		virtual short PageIn();
		virtual short PageOut();
};

// create the DList class that will contain pageWindows
typedef tDList<wPageWindow> wPageWindowList;

#define DlgModal	1
#define DlgModeless 0

class _EXPORT_ wDialogWindow : public wPageWindow
{
	protected:
		ushort rc, id;
		short mode;
	public:
		wDialogWindow(ushort i, short m = DlgModal, const char *name = 0);
		~wDialogWindow();
		ushort	CreateWindow(wWindow *owner, void *pCreatParams = 0);
		long	Default(wMessage);
		void	Dismiss(ushort result = 0);
		ushort	GetResult() { return rc; }
		void	SetCaption(const char *szTitleText);
		bString GetCaption();
};

#endif		// ObjectPMLite


/*****************************************************************************
 * 
 * Menu and accelerator classes
 * 
 *****************************************************************************/

#ifndef ObjectPMLite

class _EXPORT_ wMenu 
{
	protected:
		HWND hwndParent;
		HWND hwndMenu;
		wWindow *pParent;

		void MakeMenu(HWND parent, ushort stId, const char *szMenuItems, ushort incr = 100); 
		void MakeMenu(HWND parent, ushort ResID);

	private:
		bool TestAttrib(ushort id, short attrib);
		bool SetAttrib(ushort id, short attrib, short mask);

	public:
		wMenu();
		wMenu(wWindow *pOwner, ushort stId, const char *szMenuItems, ushort incr = 100); 
		wMenu(wWindow *pOwner, ushort ResID);
		~wMenu();
		HWND& hMenu()  {return hwndMenu;}
		HWND& hFrame() {return hwndParent;}

		bool ChangeParent(wWindow *p, bool fRedraw = FALSE);
		bool ChangeOwner(wWindow *p, bool fFrame = FALSE);
		bool SetSubMenuItems(ushort idMenu, ushort stId, const char *szMenuItems);
		bool AppendSubMenu(ushort id, const char *szItemText, bool conditional=FALSE);
		bool AppendSubMenu(ushort idMenu, ushort id, const char *szItemText, bool conditional=FALSE);
		bool InsertSubMenu(ushort id, const char *szItemText, short pos, bool conditional=FALSE);
		bool InsertSubMenu(ushort idMenu, ushort id, const char *szItemText, short pos, bool conditional=FALSE);

		bool AppendItem(ushort id, const char *szItemText, ushort style = MsText, ulong hnd = NULL);
		bool AppendItem(ushort idMenu, ushort id, const char *szItemText, ushort style = MsText, ulong hnd = NULL);
		bool AppendItem(ushort id, wBitmap *bmp);
		bool AppendItem(ushort idMenu, ushort id, wBitmap *bmp);
		bool InsertItem(ushort id, const char *szItemText, short pos, ushort style = MsText, ulong hnd = NULL);
		bool InsertItem(ushort idMenu, ushort id, const char *szItemText, short pos, ushort style = MsText, ulong hnd = NULL);
		bool InsertItem(ushort id, wBitmap *bmp, short pos);
		bool InsertItem(ushort idMenu, ushort id, wBitmap *bmp, short pos);
		bool DeleteItem(ushort id);
		bool ChangeItem(ushort id, const char *szItemText);
		bool ChangeItem(ushort id, wBitmap *bmp);
		bool AppendSeparator(ushort idMenu);
		bool InsertSeparator(ushort idMenu, short pos);
		bool EnableItem(ushort id, bool set=TRUE);
		bool DisableItem(ushort id);
		bool ToggleEnableItem(ushort id);
		bool CheckItem(ushort id, bool set=TRUE);
		bool UnCheckItem(ushort id);
		bool ToggleCheckItem(ushort id);
		bool SetItemCheckMark(wBitmap *bmp, ushort id, bool checked=TRUE);
		bool HiliteItem(ushort id, bool set=TRUE);
		bool UnHiliteItem(ushort id);
		bool ToggleHiliteItem(ushort id);
		bool FrameItem(ushort id, bool set=TRUE);
		bool UnFrameItem(ushort id);
		bool ToggleFrameItem(ushort id);
		bool SelfDismiss(ushort id, bool set = TRUE);
		bool NoSelfDismiss(ushort id);
		bool ToggleSelfDismiss(ushort id);
		bool IsItemEnabled(ushort id);
		bool IsItemChecked(ushort id);
		bool IsItemHilited(ushort id);
		bool IsItemFramed(ushort id);
		bool IsSelfDismiss(ushort id);
		ushort GetItemCount();
		bool ChangeColor(wWindowColor attr, wColor c, bool fRGB);
		bool ChangeFont(wStdFont f);
		bool SetSubMenuConditionalCascade(ushort idMenu, bool fSet = TRUE);
};

class _EXPORT_ wSysMenu : public wMenu
{
	private:
		ushort	idSysMenu;
	public:
		wSysMenu(wWindow *);
		~wSysMenu();
		ushort	SysMenuId() {return idSysMenu;}
		bool AppendSubMenu(ushort id, const char *szItemText);
		bool InsertSubMenu(ushort id, const char *szItemText, short pos);

		bool AppendItem(ushort id, const char *szItemText, ushort style = MsText);
		bool AppendItem(ushort id, wBitmap *bmp);
		bool InsertItem(ushort id, const char *szItemText, short pos, ushort style = MsText);
		bool InsertItem(ushort id, wBitmap *bmp, short pos);
		bool AppendSeparator();
		bool InsertSeparator(short pos);
};

class _EXPORT_ wPopupMenu : public wMenu
{
	private:
		wPointl pnt;
		ulong	itemid;
		ushort	opt;

	public:
		wPopupMenu(wWindow *pOwner, ushort stId, const char *szMenuItems, ushort incr = 100); 
		wPopupMenu(wWindow *pOwner, ushort ResID);
		wPointl &Position() { return pnt; }
		ulong	&ItemID()	{ return itemid; }
		ushort	&Options()	{ return opt; }
		bool	Go();
};

#pragma pack(2) /* force structure alignment packing */

struct Accel
{
	ushort fs;
	ushort	key;
	ushort	cmd;
};
#pragma pack()


typedef tDList<Accel> AccelKeyList; // list of accel structures

class _EXPORT_ wAccelTable
{
	protected:
		HACCEL	HAccel;
		HWND	hwnd;
		ACCELTABLE *keybuf;

		ACCELTABLE	*GetAcc();
		bool SetAcc(ACCELTABLE*);

	public:
		wAccelTable(wFrameWindow *parent);
		wAccelTable(wFrameWindow *parent, ushort resId);
		wAccelTable(wFrameWindow *parent, Accel *data, ushort nKeys);
		~wAccelTable();
		HACCEL hAccel() { return HAccel; }
		bool Set(ushort resId); 				// LOAD FROM RESOURCE
		bool Set(AccelKeyList *kl); 			// LIST OF ACCEL STRUCTS
		bool Set(Accel *data, ushort nKeys);	// ARRAY OF ACCEL STRUCTS
		bool Set(ushort key, ushort cmd, ushort fs);	// ONE ACCEL STRUCT
		bool Delete(ushort key, ushort fs);
		AccelKeyList *GetKeyList(); 			// GET CURRENT ACCEL KEYS
};

class _EXPORT_ wSysAccelTable : public wAccelTable
{
	public:
		wSysAccelTable() : wAccelTable ((wFrameWindow *)DesktopWindow) { hwnd = NULL; }
};

#endif		// ObjectPMLite

/*****************************************************************************
 * 
 * Control window classes
 * 
 *****************************************************************************/

extern "C" wWindowClass* _EXPORT_ PASCAL wpControlRegistered(const char *cname);

class _EXPORT_ wControlWindow : public wWindow
{
	protected:
		bool fConstCreated;
		wWindow :: hwnd;
		wWindow :: owner;
		wWindow :: parent;

		long ReturnToOwner(wControlMsg m);

	public:
		wControlWindow();
		wControlWindow(wWindow *parent);
		wControlWindow(wWindow *parent, ushort winId);
	   ~wControlWindow();

		bool	EnableSubclassedEvents();
		void	SetText(const char *pText);
		short	TextLength();
		bString GetText();
		short	GetText(char *dest, ushort bufLen);
		long	Dispatch( wMessage );
};			  

#if defined(InclControls) || defined(ObjectPMLite)

class _EXPORT_ wEntry : public wControlWindow
{
	private:
		short	len;

	protected:
		wControlWindow :: ReturnToOwner;

	public:
		wEntry(wWindow *parent) : wControlWindow (parent) {};
		wEntry(wWindow *parent, ushort id, wPointl p, wDimension size, ulong Flags);
		wEntry(wWindow *parent, ushort winId) : wControlWindow (parent, winId) { len=32; };

		bool	ClearSelection();
		bool	CopySelection();
		bool	CutSelection();
		bool	PasteSelection();
		bool	IsModified();
		ulong	GetFirstChar();
		wRange	GetSelection();
		bool	SetSelection(wRange ts);
		bString GetSelectedText();
		bool	SetFirstChar(ushort index);
		bool	SetMaxLength(short length);
		short	GetMaxLength() { return len; }
		bool	SetInsertMode(bool inserting=TRUE);

		long	Dispatch(wMessage m);
		virtual void Changed(wControlMsg m);
		virtual void InsertModeToggle(wControlMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual bool Overflow(wControlMsg m);
		virtual void Scroll(wControlMsg m);
};

class _EXPORT_ wScrollBar : public wControlWindow
{
	private:
		ushort itemSize, pageSize, itemsVisible, itemsTotal, thumbPos;
		wRange	sbRange;
	public:
		wScrollBar(wWindow *parent, ushort id, wPointl p, wDimension size, wScrollBarType type, ulong style = 0);
		wScrollBar(wWindow *parent, ushort winId);
		void	SetRange(wRange);
		wRange	GetRange()					{ return sbRange;	}
		void	SetItemSize(ushort size)	{ itemSize = size;	}
		ushort	GetItemSize()				{ return itemSize;	}
		void	SetPageSize(ushort size)	{ pageSize = size;	}
		ushort	GetPageSize()				{ return pageSize;	}
		void	SetVisible(ushort n);
		ushort	GetVisible()				{ return itemsVisible; }
		void	SetTotalItems(ushort total);
		ushort	GetTotalItems() 			{ return itemsTotal;   }
		short	CalcPosition(ushort cmd, ushort pos, short *pIncr = NULL);
		void	SetThumbPosition(ushort pos);
		ushort	GetThumbPosition();
		bool	SetThumbSize(short visible, short total);

		long Dispatch(wMessage m);
		long ScrollBarChange(wScrollBarMsg m);
};		

#endif

#define OFF 	0
#define ON		1
#define INDET	2

class _EXPORT_ wCheckBox : public wControlWindow
{
	public:
		wCheckBox(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style = 0, char *text="");
		wCheckBox(wWindow *parent, ushort winId);
		void Click();
		short SetCheck(short state = OFF);
		short CheckState();

		long Dispatch(wMessage m);
		virtual void Clicked(wControlMsg);
		virtual void DoubleClicked(wControlMsg);
};		

class _EXPORT_ wPushButton : public wControlWindow
{
	private:
		bool	_SetImage(LHANDLE h);
	public:
		wPushButton(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style=0, char *text="");
		wPushButton(wWindow *parent, ushort winId);
		void Click();
		bool SetHilite(bool state=FALSE);
		bool GetHilite();
		bool SetDefault(bool state=FALSE);
		bool SetImage(wIcon *icon, bool text= FALSE, bool mini=FALSE);
		bool SetImage(wBitmap *bitmap, bool text= FALSE);

		long  Dispatch( wMessage m);
		virtual void Clicked(wCommandMsg m);
};

class _EXPORT_ wRadioButton : public wControlWindow
{
	public:
		wRadioButton(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style=0, char *text="");
		wRadioButton(wWindow *parent, ushort winId);
		void Click();
		bool IsClicked();
		short GetIndex();

		long Dispatch(wMessage m);
		virtual void Clicked(wControlMsg m);
		virtual void DoubleClicked(wControlMsg m);
};

class _EXPORT_ wImageButton : public wControlWindow
{
	private:
		wBitmap *bmp[3];
		wIcon	*icn[3];

		bool _SetImages();

	public:
		wImageButton(wWindow *parent, ushort id, wPointl p, wDimension d, 
			ulong style=IbTextOnBtn);
		wImageButton(wWindow *parent, ushort id);
		~wImageButton();

		void Click();
		void DoubleClick();
		bool SetImages(wBitmap *up, wBitmap *down, wBitmap *disabled);
		bool SetImages(wIcon *up, wIcon *down, wIcon *disabled);
		wBitmap *GetBitmap(wImageButtonImage ndx);
		wIcon	*GetIcon(wImageButtonImage ndx);
		bool IsClicked();

		long  Dispatch( wMessage m);
		virtual void Clicked(wCommandMsg m);
		virtual void DoubleClicked(wControlMsg);
};

class _EXPORT_ wStaticControl : public wControlWindow
{
	public:
		wStaticControl(wWindow *parent, ushort id, wPointl p, wDimension d, const char *text, ulong style=0);
		wStaticControl(wWindow *parent, ushort winId);
};

class _EXPORT_ wTextBox : public wStaticControl
{
	public:
		wTextBox(wWindow *parent, ushort id, wPointl p, wDimension d, const char *text, ulong style = 0);
};			   

#ifdef InclControls

class _EXPORT_ wGroupBox : public wStaticControl
{
	public:
		wGroupBox(wWindow *parent, ushort id, wPointl p, wDimension d, const char *capt, ulong style = 0);
};

class _EXPORT_ wStaticFrame : public wStaticControl
{
	public:
		wStaticFrame(wWindow *parent, ushort id, wPointl p, wDimension d, wSFrameType typ, ulong style = 0);
};

class _EXPORT_ wStaticRectl : public wStaticControl
{
	public:
		wStaticRectl(wWindow *parent, ushort id, wPointl p, wDimension d, wSFrameType typ, ulong style = 0);
};

class _EXPORT_ wStaticBitmap : public wStaticControl
{
	public:
		wStaticBitmap(wWindow *parent, ushort id, wPointl p, wDimension d, ushort resId, ulong style = 0);
		wStaticBitmap(wWindow *parent, ushort id, wPointl p, wDimension d, wBitmap *bmp, ulong style = 0);

		void ChangeBitmap(wBitmap *bmp);
};

class _EXPORT_ wStaticIcon : public wStaticControl
{
	public:
		wStaticIcon(wWindow *parent, ushort id, wPointl p, wDimension d, short iptr, ushort resId = 0, ulong style = 0);
		wStaticIcon(wWindow *parent, ushort id, wPointl p, wDimension d, wIcon *icon, ulong style = 0);

		void ChangeIcon(wIcon *icon);
};

class _EXPORT_ wIconWindow : public wControlWindow	   
{
	private:
		bool fMyIcon;
		wIcon *icon;

	public:
		wIconWindow(wWindow *parent, ushort usrId, wPointl p, wIcon *, const char *caption, ulong style = 0);
		wIconWindow(wWindow *parent, ushort usrId, wPointl p, ushort iconResId, const char *caption, ulong style = 0);
		void ChangeIcon(wIcon *);
		void ChangeIcon(ushort iconResId);
		wIcon *GetIcon()   { return icon; }
		void ChangePen(wTextPen *t, ushort idPen = IwNoFocusPen);
		void Click(void);
		void DoubleClick(void);

		long Dispatch(wMessage m);
		virtual void Clicked(wControlMsg m);
		virtual void DoubleClicked(wControlMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
};

class _EXPORT_ wListBox : public wControlWindow
{
	public:
		wListBox(wWindow *parent) : wControlWindow (parent) {};
		wListBox(wWindow *parent, ushort id, wPointl p, wDimension size, ulong Flags);
		wListBox(wWindow *parent, ushort winId);

		short	 AddString(const char *str, short index = LiEnd);
		short	 SetString(const char *str, short index);
		short	 SelectItem(short index, short select = TRUE);
		short	 DeleteItem(short index);
		bool	 DeleteAll();
		short	 GetItemCount();
		short	 GetItemTextLength(short index);
		short	 GetItemText(short index, char *buf, short szbuf);
		bString  GetItemText(short index = LiFirst);
		short	 GetSelectedIndex(short index = LiFirst);
		bString  GetCurrentString();
		bool	 GetCurrentString(char *buf, short szbuf);
		short	 GetTopIndex();
		short	 SetTopIndex(short index);
		ulong	 GetItemHandle(short index);
		short	 SetItemHandle(short index, ulong handle);
		short	 SearchString(const char *buf, ushort fo = LfCaseSensitive, short index=LiFirst);
		short	 SetItemHeight(short height);

		long	 Dispatch( wMessage );
		virtual  void Select(wControlMsg m);
		virtual  void Enter(wControlMsg m);
		virtual  void FocusGained(wControlMsg m);
		virtual  void FocusLost(wControlMsg m);
		virtual  void Scroll(wControlMsg m);
};

class _EXPORT_ wCellBox : public wControlWindow
{
	private:
		short iAttr;
		bool firstadd;
		void SetSubColumns(void *, short, short);
		void SetAttributes(void *, short, short);
		void GetCtlData(void *);

	protected:
		wCellBox(wWindow *parent) : wControlWindow(parent) { iAttr = -1; firstadd = TRUE; }

	public:
		wCellBox(wWindow *parent, ushort id, wPointl p, wDimension size, 
				ulong style, ushort maxcols=20, ushort maxattrs=10);
		wCellBox(wWindow *parent, ushort winId);
	   ~wCellBox();

		short	 AddString(const char *str, short index = LiEnd, short grp=0);
		short	 SetString(const char *str, short index, bool invalidateFlag = TRUE);
		short	 SelectItem(short index, bool select=TRUE, bool fClearMulti = FALSE);
		void	 SetCellWidth(short width, wWinCoordUnit type = DevUnits);
		short	 DeleteItem(short index);
		bool	 DeleteAll();
		short	 GetItemCount();
		short	 GetSelectedCount();
		short	 GetSelectedIndex(short index = LiFirst);
		short	 GetItemTextLength(short index);
		short	 GetItemText(short index, char *buf, short szbuf, bool fStripFmt = FALSE);
		bString  GetItemText(short index = LiFirst, bool fStripFmt = FALSE);
		bool	 GetCurrentString(char *buf, short szbuf);
		bString  GetCurrentString();
		bool	 SetTopIndex(short index);
		short	 GetTopIndex();
		short	 SplitText(char *datap, char **tp, short fields);
		char	*ExtractColumnText(const char *pText, char *pBuf, short nColumn, bool fTags);
		bool	 AddSubColGroup(short maxcols);
		ushort	 GetSubColGroupCount();
		bool	 AddSubCol(short width, wColor clr, long flags, short grp=0);
		short	 NumSubCol(short grp=0);
		bool	 DeleteSubCol(short index, short grp=0);
		void	 DeleteAllSubCol(short grp=0);
		bool	 GetSubCol(short index, short *width, long *clr, long *flags, short grp=0);
		bool	 ChangeSubCol(short index, short width, long clr, long flags, short grp=0);
		short	 SearchString(const char *buf, ushort cmd = LfCaseSensitive, 
							  short index=LiFirst, short col=0);
		bool	 SetIndent(short i);
		short	 GetIndent();

		short	 MaxSubCol(short grp=0);
		short	 MaxAttr();

		bool	 AddAttr(wColor clr, bool foreground=TRUE);
		bool	 AddAttr(wBitmap *bmp);
		bool	 AddAttr(wIcon *icon);
		bool	 AddAttr(ushort stdFont, ushort attrs, wColor *clr = 0);
		bool	 AddAttr(wShadePattern p, wColor *c=NULL);
		short	 NumAttr()								{return iAttr + 1;}
		bool	 DeleteAttr(short index);
		void	 DeleteAllAttr()						{iAttr = -1;}
		bool	 ChangeAttr(short index, wColor clr, bool foreground=TRUE);
		bool	 ChangeAttr(short index, ushort stdFont, ushort attr, wColor *clr = 0);
		bool	 ChangeAttr(short index, wBitmap *bmp);
		bool	 GetAttr( short index, long *attr, long *clr, long *flags );

		bool	 SetItemHandle(short index, ulong handle);
		ulong	 GetItemHandle(short index);
		short	 GetItemIndex(ulong handle);

		bool	 SetItemSubColGroup(short index, short grp, bool inv=TRUE);
		ushort	 GetItemSubColGroup(short index);

		short	 InvalidateCell(short index, short column);
		bool	 SetItemHeight(short height); 
		char	*SetColumnText(char *pText, char *pBuf, short nColumn );
		bool	 SetCellText(char *text, short index, short column, bool invalidate=TRUE);

		bool	 SetTitleText( char *t );
		bString  GetTitleText();
		bool	 SetTitleHeight(short h);
		short	 GetTitleHeight();
		char	 SetTagCharacter(char tagchar);
		char	 GetTagCharacter();

		bool	 SetItemEmphasis(ushort index, ushort emph, bool fSet);
		ushort	 QueryItemEmphasis(ushort index);

		long	 Dispatch(wMessage m);
		virtual  void Select(wControlMsg m);
		virtual  void Enter(wControlMsg m);
		virtual  void FocusGained(wControlMsg m);
		virtual  void FocusLost(wControlMsg m);
		virtual  void Scroll(wControlMsg m);
		virtual  void CellSelect(wControlMsg m);
		virtual  void CellEnter(wControlMsg m);
		virtual  void ContextMenu(wControlMsg m);
		virtual  void Delete(wControlMsg m);
};					   

bool RegisterCellClass(HAB);


class _EXPORT_ wComboBox : public wEntry
{
	private:
		PFNWP	oldproc;

	public:
		wComboBox(wWindow *parent) : wEntry(parent) {};
		wComboBox(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style);
		wComboBox(wWindow *parent, ushort winId);

		short	 AddString(const char *str, short index = LiEnd);
		short	 AddStrings(const char **str, short count);
		short	 SetString(const char *str, short index);
		short	 SelectItem(short index, short select = TRUE);
		short	 DeleteItem(short index);
		bool	 DeleteAll();
		short	 GetItemCount();
		short	 GetItemTextLength(short index);
		short	 GetItemText(short index, char *buf, short szbuf);
		bString  GetItemText(short index = LiFirst);
		short	 GetSelectedIndex();
		bool	 GetCurrentString(char *buf, short szbuf);
		bString  GetCurrentString();
		short	 GetTopIndex();
		short	 SetTopIndex(short index);
		short	 SearchString(const char *buf, ushort fo = LfCaseSensitive, short index=LiFirst);
		ulong	 GetItemHandle(short index);
		short	 SetItemHandle(short index, ulong handle);
		bool	 ShowList();
		bool	 HideList();
		bool	 IsListShowing();

		long	 Dispatch(wMessage m);
		virtual  void Changed(wControlMsg m);
		virtual  void EntryScroll(wControlMsg m);
		virtual  void ListScroll(wControlMsg m);
		virtual  void Select(wControlMsg m);
		virtual  void Enter(wControlMsg m);
		virtual  void ListBeingShown(wControlMsg m);
		virtual  void FocusGained(wControlMsg m);
		virtual  void FocusLost(wControlMsg m);

		PFNWP	OriginalProc() { return oldproc; }
};

class _EXPORT_ wMLEOverflowMsg : public wControlMsg
{
	public:
		wOverflowType	Type();

		ushort			Reason();
		ulong			CharExceeded();
		long			HPixelsExceeded();
		long			VPixelsExceeded();
};

class _EXPORT_ wMLEMarginMsg : public wControlMsg
{
	public:
		wMLEMargin	Margin();
		long		InsertionPoint();
};

class _EXPORT_ wMLEntry : public wControlWindow
{
	public:
		wMLEntry(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style);
		wMLEntry(wWindow *parent, ushort winId) : wControlWindow (parent, winId) {}

		bool	AddString(const char *s);
		long	DeleteString(wRange ts);
		bool	DeleteChar(long ndx);
		ulong	GetNumLines();
		ulong	GetNumChars();

		ulong	ClearSelection();
		ulong	CopySelection();
		ulong	CutSelection();
		ulong	PasteSelection();

		bool	SetCursorPosition(long ndx);
		ulong	GetCursorPosition();
		bool	SetFirstChar(long ndx);
		ulong	GetFirstChar();
		bool	SetTopLine(long line);
		long	GetTopVisibleLine();
		long	GetTopLine();
		bool	SetSelection(wRange ts);
		wRange	GetSelection();
		bString GetSelectedText();
		long	GetLineLength(long ndx);
		bool	SetFormatRect(wPointl p, ulong flags);
		wPointl GetFormatRect(ulong *flags=NULL);

		ushort	Search(const char *find, long start = PosFirst, long stop = PosLast,
				ushort = MlSelectMatch);					
		ushort	SearchReplace(const char *find, const char *replace, long start = PosFirst, 
				long stop = PosLast, ushort = MlNone);

		ulong	Import(bString str, wMlTextFormat fmt = MlNoTranslate);
		ulong	Import(bString str, long *pos, wMlTextFormat fmt = MlNoTranslate);
		ulong	Export(bString& str, wMlTextFormat fmt = MlNoTranslate);
		ulong	Export(bString& str, long *pos, wMlTextFormat fmt = MlNoTranslate);

		bool	Undo();
		bool	ResetUndo();
		long	GetUndoStatus();

		ulong	LineFromChar(long ndx);
		ulong	CharFromLine(long line);
		long	SetMaxLength(long maxlen = MlNoLimit);
		long	GetMaxLength();
		ushort	SetTabStop(ushort dist, wWinCoordUnit type = DevUnits);
		ushort	GetTabStop();
		bool	SetModified(bool state = TRUE);
		bool	GetModified();
		bool	SetReadOnly(bool state = ON);
		bool	GetReadOnly();
		bool	SetWrap(bool state = ON);
		bool	GetWrap();
		wColor	SetForeground(wColor fg);
		wColor	GetForeground();
		wColor	SetBackground(wColor bg);
		wColor	GetBackground();
		bool	SetFont(wFont *f);
		wFont  *GetFont();
		bool	EnableUpdate(bool enable=TRUE);
		bool	DisableUpdate();
		bool	SetFormatRect(wPointl *p, ulong flags);
		wPointl GetFormatRect(ulong flags);

		long	Dispatch(wMessage m);
		virtual void Changed(wControlMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual bool Overflow(wMLEOverflowMsg m);
		virtual void Scroll(wControlMsg m, short direction);
		virtual bool SearchPause(wControlMsg m, long SearchedTo);
		virtual bool MouseOnMargin(wMLEMarginMsg m);
};

class _EXPORT_ wSpinButton : public wControlWindow
{
	private:
		ushort	len;
		wSbUpdateMethod updateflg;
		wRange	range;

	public:
		wSpinButton(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style);
		wSpinButton(wWindow *parent, ushort winId);

		bool	SetRange(wRange r);
		bool	OverrideRange(wRange r);
		wRange	GetRange();
		bool	SetStrings(const char **arr, long count);
		bool	SetStrings(bStringList *sl);
		bool	SetValue(long val);
		long	GetValue(wSbUpdateMethod flg = SbAlwaysUpdate);
		bString GetText(wSbUpdateMethod flg);
		bool	SetMaxLength(ushort length);
		ushort	GetMaxLength() { return len; }
		bool	SpinUp(ulong count=1);
		bool	SpinDown(ulong count=1);
		bool	SetMaster(wSpinButton *);
		bool	IsValid();
		bool	UpdateIfValid();
		bool	Update();

		long Dispatch(wMessage m);
		virtual void Changed(wControlMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual void AboutToSpinUp(wControlMsg m);
		virtual void AboutToSpinDown(wControlMsg m);
		virtual void EndSpin(wControlMsg m);
};

#ifndef SLN_SLIDERTRACK
class SLDCDATA;
#endif	

class _EXPORT_ wSliderPositionMsg : public wControlMsg
{
	public:
		ulong ulPixelsFromHome() { return (ulong)mp2; }
};

class _EXPORT_ wSlider : public wControlWindow
{
	private:
		SLDCDATA	*data;
		bool SetCtlData();

	public:
		wSlider(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style,
			ushort Increments1, ushort Spacing1 = 0, ushort Increments2 = 0, ushort Spacing2 = 0);
		wSlider(wWindow *parent, ushort winId);
	   ~wSlider();

		bool	SetTickSize(ushort size);				// SETS ALL TICKS TO SAME SIZE
		bool	SetTickSize(ushort ndx, ushort size);	// SETS SPECIFIC TICK SIZE
		ushort	GetTickSize(ushort ndx);					// RETURNS SPECIFIC TICK SIZE
		wPointl GetTickPosition(ushort ndx);			// RETURNS SPECIFIC TICK POSITION

		bool	SetScaleIncrements(wSliderScale ss, ushort increments);
		bool	SetScaleSpacing(wSliderScale ss, ushort spacing);
		ushort	GetScaleIncrements(wSliderScale ss = ScaleOne);
		ushort	GetScaleSpacing(wSliderScale ss = ScaleTwo);

		ulong	AddDetent(ushort pos);
		ulong	AddDetent(double pos);
		ushort	GetDetent(ushort id);
		bool	RemoveDetent(ulong id);

		bool	SetScaleText(ushort ndx, const char *text);
		bool	SetScaleText(bStringList *l, ushort increment = 1, ushort start = 0);
		bString GetScaleText(ushort ndx);

		bool	SetShaftSize(ushort sz);
		bool	SetShaftPosition(wPointl p);
		bool	SetSliderSize(wDimension d);
		bool	SetSliderPosition(ushort p, bool pixels = FALSE);

		wDimension GetShaftSize();
		wPointl GetShaftPosition();
		wDimension GetSliderSize();
		ulong GetSliderPosition(bool pixels = FALSE);

		void SetPrimaryScale(wSliderScale ss = ScaleOne);
		wSliderScale GetPrimaryScale();

		bool	ChangeSize(wDimension d);

		long	Dispatch(wMessage m);
		virtual void Changed(wSliderPositionMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual void SliderDrag(wSliderPositionMsg m);
};

class _EXPORT_ wCircularSlider : public wControlWindow
{
	private:
		wBitmap *bmp[4];
	public:
		wCircularSlider(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style,
			wRange r);
		wCircularSlider(wWindow *parent, ushort winId);
	   ~wCircularSlider();

		bool	SetValue(ushort val);
		bool	SetRange(wRange r);
		bool	SetTickIncrement(ushort inc);
		bool	SetScrollIncrement(ushort inc);

		wRange	GetRange();
		ushort	GetValue();
		ushort	GetRadius();
		ushort	GetTickIncrement();
		ushort	GetScrollIncrement();

		bool	SetBitmaps(wBitmap *lu, wBitmap *ld, wBitmap *ru, wBitmap *rd);
		wBitmap *GetBitmap(CircSliderBitmap ndx) { return bmp[(long)ndx]; }

		long Dispatch(wMessage m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual void Changed(wControlMsg m);
		virtual void Tracking(wControlMsg m);
		virtual wColor QueryBackgroundColor(wControlMsg m);
};

#ifndef VS_BITMAP
struct _VSCDATA;
typedef _VSCDATA VSCDATA;
#endif


class _EXPORT_ wValueSetItem : public wWorkplaceObject
{
	private:
		ushort attrib;
		void   *contents;
		bPosition	rc;
		wValueSet * pvs;
		ulong handle;

		friend class wValueSet;

		bool SetAttribute(ushort attr, bool set=TRUE);

	public:
		wValueSetItem(const char *text, ulong hndl = 0, ushort attr = VlNone);
		wValueSetItem(wColor color, bool fRGB = FALSE, ulong hndl = 0, ushort attr = VlNone);
		wValueSetItem(wBitmap *pbm, ulong hndl = 0, ushort attr = VlNone);
		wValueSetItem(wIcon *pic, ulong hndl = 0, ushort attr = VlNone);
	   ~wValueSetItem();

		bool		Enable(bool enable=TRUE);
		bool		Disable();
		bool		IsEnabled();
		void		SetDragCapabilities(ushort caps);

		wColor		GetColorValue();
		bString 	GetTextValue();
		wBitmap    *GetBitmapValue();
		wIcon	   *GetIconValue();

		bool		SetValue(const char *text);
		bool		SetValue(wColor color, bool fRBG = FALSE);
		bool		SetValue(wBitmap *bmp);
		bool		SetValue(wIcon *icon);

		void		SetHandle(ulong h) { handle=h; }
		ulong		GetHandle() 	   { return handle; }

		bPosition	GetPosition()	{ return rc; }
		ushort		GetImageType();
};

class _EXPORT_ wVSItemMsg : public wControlMsg
{
	public:
		wValueSetItem	*Item();
};

class _EXPORT_ wValueSet : public wControlWindow
{
	private:
		VSCDATA    *data;
		wDimension	rc;
		void	  **items;
		PFNWP		oldproc;

		void	DeleteArray();
		void   *GetArray(bPosition r);
		bool	SetArray(bPosition r, wValueSetItem *p);
		bool	IsPositionValid(bPosition r);

	public:
		wValueSet(wWindow *parent, ushort id, wPointl pos, wDimension size, 
				  wDimension rcCount, ulong style);

		wValueSet(wWindow *parent, ushort winId);
	   ~wValueSet();

		bool SelectItem(bPosition item);
		bool SelectItem(ulong handle);
		bool SelectItem(wValueSetItem *item);

		bool SetItemSize(wDimension size);
		bool SetItemSpacing(wDimension size);
		bool SetRowNColumnCount(wDimension rcCount);
		bool SetItem(bPosition pos, wValueSetItem *item);

		wValueSetItem *GetSelectedItem();
		ulong		   GetSelectedHandle();
		bPosition	   GetSelectedPosition();
		wValueSetItem *GetItem(bPosition pos);
		wDimension	   GetItemSize();
		wDimension	   GetItemSpacing();
		wDimension	   GetRowNColumnCount() 		{ return rc; }

		long	Dispatch(wMessage);
		virtual void Select(wVSItemMsg m);
		virtual void Enter(wVSItemMsg m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual void ItemHelp(wControlMsg m);

		PFNWP	OriginalProc() { return oldproc; }
};

// PAGES THAT ARE INSERTED INTO A NOTEBOOK

class _EXPORT_ wNoteBookPage : public wWorkplaceObject
{
	private:
		friend class wNoteBook;
		friend class wNoteBookPageList;

		wWindow *pwin;
		ulong	pageid, handle;
		ushort	style;
		bString statusline, tab;
		wBitmap *pbm;
		wNoteBook *nb;
		bool purge;
		   
	public:
		wNoteBookPage(wWindow *pw, ushort st, const char *txt = NULL, bool purgewin=TRUE);
		~wNoteBookPage();

		ulong	GetPageID() 				{ return pageid; }
		ushort	GetStyle()					{ return style;  }
		void	SetPageHandle(ulong h)		{ handle = h;	 }
		ulong	GetPageHandle() 			{ return handle; }
		wNoteBook *GetNoteBook()			{ return nb; }

		bool	SetWindow(wWindow *pw);
		wWindow *GetWindow()	{ return pwin; }
		bool	SetStatusLine(const char *txt);
		bString GetStatusLine();
		bool	SetTab(const char *t);
		bool	SetTab(wBitmap *t);
		bString GetTabText();
		wBitmap *GetTabBitmap() 			{ return pbm; }

		bool	&PurgeWindow() { return purge; }
};

class _EXPORT_ wNoteBookPageList : private tDList<wNoteBookPage>
{
private:
	friend class wNoteBook;

	wNoteBook	*nb;

	void DoInsert(wNoteBookPage *p, ulong pgid, short place);

public:
	wNoteBookPageList(){}
	~wNoteBookPageList();

	void InsertPage(wNoteBookPage *p, short pos, tIterator<wNoteBookPage> *it = NULL);
	void InsertPageAtHead(wNoteBookPage *p);
	bool InsertPage(wNoteBookPage *p);
	wNoteBookPage *RemovePage(tIterator<wNoteBookPage> *it=NULL);
	wNoteBook *GetNoteBook()		{ return nb; }

	typedef tDList<wNoteBookPage> PageList;
	typedef tIterator<wNoteBookPage> PageIter;

	bool	First( bIterator* it=NULL ) { return PageList::First(it); };
	bool	Last( bIterator* it=NULL )	{ return PageList::Last(it); }
	bool	Next( bIterator* it=NULL )	{ return PageList::Next(it); }
	bool	Prev( bIterator* it=NULL )	{ return PageList::Prev(it); }
	wNoteBookPage* Current( PageIter* it=NULL ) { return PageList::Current(it); }

	bool			IsEmpty()			{ return PageList::IsEmpty(); }
	ulong			Entries() const 	{ return PageList::Entries(); }
	wNoteBookPage*	Subscript(ulong n)	{ return PageList::Subscript(n); }
	wNoteBookPage*	operator*() 		{ return PageList::Current(); }
	wNoteBookPage*	operator()()		{ return PageList::Current(); }
	wNoteBookPage*	operator[](ulong n) { return PageList::Subscript(n); }

	bool	Find( wNoteBookPage* item, PageIter* it=NULL )
										{ return PageList::Find(item, it); }
	wNoteBookPage*	Search( const wNoteBookPage* key, CompareFunc f=NULL, PageIter* it=NULL )
										{ return PageList::Search(key, f, it); }
	void*	Apply(IterFunc f)			{ return PageList::Apply(f); } 
	void*	Apply(IterFunc1 f, void* p) { return PageList::Apply(f, p); }
};

class _EXPORT_ wNBPageMsg : public wControlMsg
{
	private:
		wNoteBookPage	*GetPage(ulong id); 

	public:
		wNoteBookPage	*CurrentTopPage();
		wNoteBookPage	*NewTopPage();
		wNoteBookPage	*DeletedPage();
};

class _EXPORT_ wNoteBook : public wControlWindow
{
	private:
		wNoteBookPageList	*nbplist;
		wDimension	major, minor, pagebutton;

		friend class wNoteBookPageList;
		friend class wNBDeletePageMsg;
		friend class wNBSelectPageMsg;

		bool SetDimension(wDimension d, ushort type);

	public:
		wNoteBook(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style);
		wNoteBook(wWindow *parent, ushort winId);
		~wNoteBook();

		wNoteBookPageList	*Pages()	{ return nbplist; }

		wRectl CalcAppPageRectl();
		wRectl CalcNBPageRectl(wRectl r);
		bool   SetNotebookColor(wNoteBookAttrib attr, wColor c, bool fRGB=FALSE);
		bool   GotoPage(wNoteBookPage *pg);
		bool   GotoPage(ushort pg);
		bool   InvalidateTabs();
		bool   SetMajorTabDimension(wDimension d);
		bool   SetMinorTabDimension(wDimension d);
		bool   SetPageButtonDimension(wDimension d);
		wNoteBookPage *GetTopPage();

		long	Dispatch(wMessage m);
		virtual void NewPageSize(wControlMsg m);
		virtual void PageDeleted(wNBPageMsg m);
		virtual void PageSelected(wNBPageMsg m);
		virtual void ItemHelp(wControlMsg m);
};	   

// the container class
#include "containr.hpp"

class _EXPORT_ wPanel3D : public wControlWindow
{
	public:
		wPanel3D(wWindow *parent, ushort id, wPointl p, wDimension d, 
			ulong style=0, ushort bevelw=2, ushort borderw=0);
		wPanel3D(wWindow *parent, ushort id);
		~wPanel3D();
	
		bool SetBevelWidth(ushort w);
		ushort GetBevelWidth();

		bool SetBorderWidth(ushort w);
		ushort GetBorderWidth();
};

#endif		// InclControls

class _EXPORT_ wMessageBox
{
	private:
		ushort	retval;
	public:
		wMessageBox(wWindow *parent, const char *txt, const char *title, ulong flags = 0, ushort id = 0);
		wMessageBox(wWindow *parent = DesktopWindow, wStdMsgBox type = MbxLastError);  
		ushort MessBoxVal() {return retval;}
}; 

class _EXPORT_ wTrackRectangle
{
	private:
		wWindow *	tw;
		wPresSpace *twps;
		wDimension	border, grid, keygrid;
		wRectl		trackrect, boundary;
		wPointl 	minpt, maxpt;
		ushort		options;

	public:
		wTrackRectangle(wWindow *trackwin, wPresSpace *ps = NULL);

		wDimension &BorderSize() { return border; }
		wDimension &GridSize() { return grid; } 			
		wDimension &KeyGridSize() { return keygrid; }
		wRectl	&InitialRectl() { return trackrect; }	
		wRectl	&AbsoluteBoundary() { return boundary; }
		wPointl &MinPt() { return minpt; }
		wPointl &MaxPt() { return maxpt; }
		ushort	&Options() { return options; }

		bool	DoTracking();
		wRectl	GetTrackingRect()	{ return trackrect; }

		bool	Show();
		bool	Hide();
};

#endif		// __WINDOWS_HPP

