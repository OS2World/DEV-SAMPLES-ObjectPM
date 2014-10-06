/*  VCS_ID
 *  $Filename:   pmtypes.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.6  $
 *  $Date:   03 Jan 1992 08:17:56  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __PMTYPES_HPP
#define __PMTYPES_HPP

#ifdef __cplusplus

/* wWindow Manager classes */

class wWindow;
class wFrameWindow;
class wDialogWindow;
class wPageWindow;
class wControlWindow;
class wMessage;
class wWindowClass;
class wPointl;
class wRectl;
class wDimension;
class wPointer;
class wIcon;
class wMenu;
class wSysMenu;
class wCursor;
class wAccelTable;
class wCheckBox;
class wPushButton;
class wRadioButton;
class wStaticControl;
class wTextBox;
class wGroupBox;
class wStaticFrame;
class wStaticRectl;
class wStaticBitmap;
class wStaticIcon;
class wScrollBar;
class wIconWindow;	   
class wListBox;
class wCellBox;
class wEntry;
class wMLEntry;
class wComboBox;
class wMessageBox;
class wHelpManager;
class wSpinButton;
class wMdiDocument;
class wMdiDesktop;
class wWorkplaceObject;
class wDispatchTable;
class wValueSet;
class wValueSetItem;
class wSlider;
class wValueSet;
class wNoteBook;
class wNoteBookPageList;
class wNoteBookPage;
class wContainerField;
class wContainerFieldList;
class wContainerItem;
class wContainerItemCltn;
class wContainerEnterMsg;
class wContainerEmphasisMsg;
class wContainerItemMsg;
class wContainerEditMsg;
class wContainer;

#ifdef OPMPTRTYPES
typedef wWindow *pwWindow;
typedef wFrameWindow *pwFrameWindow;
typedef wPageWindow *pwPageWindow;
typedef wDialogWindow *pwDialogWindow;
typedef wControlWindow *pwControlWindow;
typedef wMessage *pwMessage;
typedef wWindowClass *pwWindowClass;
typedef wPointl *pwPointl;
typedef wRectl *pwRectl;
typedef wDimension *pwDimension;
typedef wPointer *pwPointer;
typedef wIcon *pwIcon;
typedef wMenu *pwMenu;
typedef wSysMenu *pwSysMenu;
typedef wCursor *pwCursor;
typedef wAccelTable *pwAccelTable;
typedef wCheckBox *pwCheckBox;
typedef wPushButton *pwPushButton;
typedef wRadioButton *pwRadioButton;
typedef wStaticControl *pwStaticControl;
typedef wScrollBar *pwScrollBar;
typedef wIconWindow *pwIconWindow;
typedef wListBox *pwListBox;
typedef wCellBox *pwCellBox;
typedef wMessageBox *pMessBox;
typedef wHelpManager *pwHelpManager;
typedef wSpinButton *pwSpinButton;
typedef wMdiDocument *pwMdiDocument;
typedef wMdiDesktop *pwMdiDesktop;
typedef wWorkplaceObject *pwWorkplaceObject;
typedef wEntry *pwEntry;
typedef wMLEntry *pwMLEntry;
typedef wComboBox *pwComboBox;
typedef wValueSet *pwValueSet;
typedef wValueSetItem *pwValueSetItem;
typedef wSlider *pwSlider;
typedef wValueSet *pwValueSet;
typedef wNoteBook *pwNoteBook;
typedef wNoteBookPageList *pwNoteBookPageList;
typedef wNoteBookPage *pwNoteBookPage;
typedef wContainerField	  *pwContainerField;
typedef wContainerFieldList  *pwContainerFieldList;
typedef wContainerItem		  *pwContainerItem;
typedef wContainerItemCltn	  *pwContainerItemCltn;
typedef wContainerEnterMsg	  *pwContainerEnterMsg;
typedef wContainerEmphasisMsg *pwContainerEmphasisMsg;
typedef wContainerItemMsg	  *pwContainerItemMsg;
typedef wContainerEditMsg	  *pwContainerEditMsg;
typedef wContainer			  *pwContainer;
#endif

/* graphics classes */

class wFillPattern;
class wPicture; 
class wRegion;
class wFont;
class wBitmap;
class wDevice;
class wMemoryDevice;
class wWindowDevice;
class wPrinter;
class wTextPrinter;
class wColor;
class wPicture; 
class wRegion;
class wFont;
class wPresSpace;
class wBitmap;
class wMemoryBitmap;
class wFillPattern;
class wTextPen;
class wPen;
class wConnectedGraphicsTool;
class wGraphicsTool;
class wSubPicture;
class wDynamicPicture;
class wFixed;
class wMetaFile;
class wPrinterSetup;
class wPrinterForm;
class wPrinterFormList;
class wPrinterList;
class wPrinterInfo;

#ifdef PTRTYPES
typedef wFillPattern *pwFillPattern;
typedef wPicture *pwPicture;
typedef wRegion *pwRegion;
typedef wFont *pwFont;
typedef wBitmap *pwBitmap;
typedef wMemoryBitmap *pwMemoryBitmap;
typedef wDevice *pwDevice;
typedef wMemoryDevice *pwMemoryDevice;
typedef wWindowDevice *pwWindowDevice;
typedef wPrinter *pwPrinter;
typedef wColor *pwColor;
typedef wPicture *pwPicture; 
typedef wRegion *pwRegion;
typedef wFont *pwFont;
typedef wPresSpace *pwPresSpace;
typedef wTextPrinter *pwTextPrinter;
typedef wBitmap *pwBitmap;
typedef wFillPattern *pwFillPattern;
typedef wPen *pwPen;
typedef wTextPen *pwTextPen;
typedef wDynamicPicture *pwDynamicPicture;
typedef wSubPicture *pwSubPicture;
typedef wConnectedGraphicsTool *pwConnectedGraphicsTool;
typedef wGraphicsTool *pwGraphicsTool;
typedef wMetaFile *pwMetaFile;
#endif

#endif

/* standard defines and enumerations */

#ifndef CALLBACK
#define CALLBACK EXPENTRY /* v1.3 backward compatiblity */
#endif
/* redefine SHORTnFROMMP to a version that allows the  */
/* derived ushort to be returned as a reference from C++  */
#undef SHORT1FROMMP
#undef SHORT2FROMMP
#define SHORT1FROMMP(m) (((ushort *)(&m))[0])
#define SHORT2FROMMP(m) (((ushort *)(&m))[1])
#undef LONGFROMMP
#define LONGFROMMP(m)   (((ulong *)(&m))[0])
#undef HWNDFROMMP
#define HWNDFROMMP(m)   (((HWND *)(&m))[0])

/* redefine M?FROMSHORT to allow for zortech compatibility */
#undef MPFROMSHORT
#undef MRFROMSHORT
#define MPFROMSHORT(s) ((MPARAM)(ulong)(ushort)(s))
#define MRFROMSHORT(s) ((MRESULT)(ulong)(ushort)(s))

#define PosCenter			0
#define PosTopLeft			1
#define PosTopRight			2
#define PosBottomLeft		3
#define PosBottomRight		4

#define PosRelSelf			0
#define PosRelParent		1

#define CmdSrcPushButton	1
#define CmdSrcMenu			2
#define CmdSrcAccelerator	3
#define CmdSrcOther			0

#define FORM_CALLBACK(a)	((short(*)())&a)
#define NULLWP ((wWindow *)0)
#define NULLCWP ((wControlWindow *)0)

#define BUTTONUP  	0 			/* buttom message types (OLD)*/
#define BUTTONDOWN	1
#define BUTTONDBL	2
#define BUTTONCLICK	3
#define ButtonUp  	0 			/* buttom message types */
#define ButtonDown	1
#define ButtonDbl	2
#define ButtonClk	3

#define OBJPM_DELDEV  0x10000000L
#define OBJPM_WINPS   0x20000000L
#define OBJPM_TEMPPS  0x40000000L
#define OBJPM_DRAGPS  0x80000000L
#define OBJPM_MAXLCID 0x08000000L

#define IW_FOCUSPEN   1
#define IW_NOFOCUSPEN 2
#define IwFocusPen    1
#define IwNoFocusPen  2

/* Graphics Tool Types */

#define TT_CONNECTED 	0x00000001L
#define TT_TEXTPEN		0x00000002L
#define TT_PEN			0x00000004L
#define TT_BITMAP		0x00000008L
#define TT_FILLPAT		0x00000010L
#define TT_FONT         0x00000020L
#define TT_REGION       0x00000040L
#define TT_SUBPICTURE   0x00000080L
#define TT_LCID         0x00000100L
#define TT_PICTURE      0x00000200L
#define TT_DYNPICTURE   0x00000400L
#define TT_MARKER		0x00000800L

#define OD_WINDOW       100
#define OD_PRINTER      101
#define	OD_RAWPRINTER   102

/* Dragging notification message for cellboxes */
#define LN_SETDRAG		6

enum wWindowColor 
{
	ForegndClr = 1,
	BackgndClr = 3,
	HiliteForegndClr = 5,
	HiliteBackgndClr = 7,
	DisabledForegndClr = 9,
	DisabledBackgndClr = 11,
	BorderClr = 13,
	ActiveClr = 18,
	InactiveClr = 20,
	ActiveTextForegndClr = 22,
	ActiveTextBackgndClr = 24,
	InactiveTextForegndClr = 26,
	InactiveTextBackgndClr = 28,
	ShadowClr = 30
};

enum wColorAttrType 
{
	AttrRGB,
	AttrPureRGB,
	AttrIndex,
	AttrRGBOrIndex
};

#endif // PMTYPES_HPP
