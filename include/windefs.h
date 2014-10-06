/*  VCS_ID
 *  $Filename:   windefs.h
 *  $Author  :   John Pompeii
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


//+*****************************************************************************
//
//	DESCRIPTION:
//
//		This module contains all the base defines needed so that the
//		win* header files will not need to be included by apps 
//
//-*****************************************************************************

#ifndef __WINDEFS_H
#define __WINDEFS_H

/*****************************************************************************
 *
 * Graphics System
 *
 *****************************************************************************/

typedef long FIXED;

#ifndef INCL_GPIBITMAPS
typedef struct _RGB {           /* rgb */
    byte bBlue;
    byte bGreen;
    byte bRed;
} RGB;
#endif


enum wTransformAddOpt 
{
	TransformReplace,
	TransformAdd,
	TransformPreempt
};

enum wCoordSpace
{
	WorldSpace = 1,
	ModelSpace = 2,
	DefaultPage = 3,
	PageSpace = 4,
	DeviceSpace = 5
};

enum wPageUnits
{
	PuUserDefined = 0x0004,
	PuPels = 0x0008,
	PuLoMetric = 0x000C,
	PuHiMetric = 0x0010,
	PuLoEnglish = 0x0014,
	PuHiEnglish = 0x0018,
	PuTwips = 0x001C
};

#define PcNormal 		0
#define PcReAssociate 	1
#define PcRetain 		2
#define PcPersistent	4

enum FrameControlType {
	TitleBarLeft,
	TitleBarRight,
	ClientTop,
	ClientLeft,
	ClientRight,
	ClientBottom
};

enum wGraphicsDevice
{
	OdNoDevice = 0,
	OdQueued = 2,
	OdDirect = 5,
	OdInfo = 6,
	OdMetafile = 7,
	OdMemory = 8,
	OdPrinter = 100,
	OdRawPrinter = 101,
	OdWindow = 102
};

// colors

#define ClrWhite                     (-2L)
#define ClrBlack                     (-1L)
#define ClrBackground                  0L
#define ClrBlue                        1L
#define ClrRed                         2L
#define ClrPink                        3L
#define ClrGreen                       4L
#define ClrCyan                        5L
#define ClrYellow                      6L
#define ClrNeutral                     7L
#define ClrDarkGray                    8L
#define ClrDarkBlue                    9L
#define ClrDarkRed                    10L
#define ClrDarkPink                   11L
#define ClrDarkGreen                  12L
#define ClrDarkCyan                   13L
#define ClrBrown                      14L
#define ClrPaleGray                   15L
#define SysClrShadowHiliteBgnd         (-50L)
#define SysClrShadowHiliteFgnd         (-49L)
#define SysClrShadowText               (-48L)
#define SysClrEntryField               (-47L)
#define SysClrMenuDisabledText         (-46L)
#define SysClrMenuHiLite               (-45L)
#define SysClrMenuHiLitebgnd           (-44L)
#define SysClrPageBackground           (-43L)
#define SysClrFieldBackground          (-42L)
#define SysClrButtonLight              (-41L)
#define SysClrButtonMiddle             (-40L)
#define SysClrButtonDark               (-39L)
#define SysClrButtonDefault            (-38L)
#define SysClrTitleBottom              (-37L)
#define SysClrShadow                   (-36L)
#define SysClrIconText                 (-35L)
#define SysClrDialogBackground         (-34L)
#define SysClrHiliteForeground         (-33L)
#define SysClrHiliteBackground         (-32L)
#define SysClrInactiveTitleTextBgnd    (-31L)
#define SysClrActiveTitleTextBgnd      (-30L)
#define SysClrInactiveTitleText        (-29L)
#define SysClrActiveTitleText          (-28L)
#define SysClrOutputText               (-27L)
#define SysClrWindowStaticText         (-26L)
#define SysClrScrollbar                (-25L)
#define SysClrBackground               (-24L)
#define SysClrActiveTitle              (-23L)
#define SysClrInactiveTitle            (-22L)
#define SysClrMenu                     (-21L)
#define SysClrWindow                   (-20L)
#define SysClrWindowFrame              (-19L)
#define SysClrMenuText                 (-18L)
#define SysClrWindowText               (-17L)
#define SysClrTitleText                (-16L)
#define SysClrActiveBorder             (-15L)
#define SysClrInactiveBorder           (-14L)
#define SysClrAppWorkspace             (-13L)
#define SysClrHelpBackground           (-12L)
#define SysClrHelpText                 (-11L)
#define SysClrHelpHilite               (-10L)

enum wColorTabCmd
{
	ColorTabReset = 0,
	ColorTabRGB = 1
};

// Fonts

#define FACESIZE 32

#define FfPublic 		0x0001		 // font find attributes
#define FfPrivate 		0x0002
#define FfOutline 		0x0004
#define FfImage 		0x0008
#define FfProp 			0x0010
#define FfFixed 		0x0020
#define FfMatchDev 		0x0040

enum wStdFont		/* The list of standard fonts */
{
	SystemProp,
	Courier8,
	Courier10,
	Courier12,
	CourierOL,
	CourierOLI,
	CourierOLB,
	CourierOLBI,
	Helv8,
	Helv10,
	Helv12,
	Helv14,
	Helv18,
	Helv24,
	HelvOL,
	HelvOLI,
	HelvOLB,
	HelvOLBI,
	TmsRmn8,
	TmsRmn10,
	TmsRmn12,
	TmsRmn14,
	TmsRmn18,
	TmsRmn24,
	TmsRmnOL,
	TmsRmnOLI,
	TmsRmnOLB,
	TmsRmnOLBI,
	SysMono10,
	SysMono12,
	SymbolOL
};

// font attributes

#define NormalFont     		0
#define ItalicFont     		0x0001      
#define UnderscoreFont 		0x0002  
#define HollowFont     		0x0008     
#define StrikeThruFont 		0x0010   
#define BoldFont       		0x0020


// Clipping

#define ClpClipPath     1
#define ClpClipRegion   2
#define ClpAll         	3


enum wRegCombineMethod
{
	RcOR = 1,
	RcCopy = 2,
	RcXOR = 4,
	RcAND = 6,
	RcDiff = 7
};

// Bitmaps

#define DbmNormal                 0x0000	// mono draw modes
#define DbmInvert                 0x0001
#define DbmHalfTone               0x0002
#define DbmStretch                0x0004
#define DbmImageAttrs             0x0008

#define RopSrcCopy                0x00CCL
#define RopSrcPaint               0x00EEL
#define RopSrcAND                 0x0088L
#define RopSrcInvert              0x0066L
#define RopSrcErase               0x0044L
#define RopNotSrcCopy             0x0033L
#define RopNotSrcErase            0x0011L
#define RopMergeCopy              0x00C0L
#define RopMergePaint             0x00BBL
#define RopPatCopy                0x00F0L
#define RopPatPaint               0x00FBL
#define RopPatInvert              0x005AL
#define RopDstInvert              0x0055L
#define RopZero                   0x0000L
#define RopOne                    0x00FFL

#define BboTargetWorld            0x00000100L
#define BboOR                     0L
#define BboAND                    1L
#define BboIgnore                 2L
#define BboPalColors              4L
#define BboNoColorInfo            8L


// Tool structures

enum wForgroundMix
{
	FmDefault     = 0,
	FmOR          = 1,
	FmOverPaint   = 2,
	FmLeaveAlone  = 5,
	FmXOR         = 4,
	FmAND         = 6,
	FmSubtract    = 7,
	FmMaskSrcNOT  = 8,
	FmZero        = 9,
	FmNOTMergeSrc = 10,
	FmNOTXORSrc   = 11,
	FmInvert      = 12,
	FmMergeSrcNOT = 13,
	FmNOTCopySrc  = 14,
	FmMergeNOTSrc = 15,
	FmNOTMaskSrc  = 16,
	FmOne         = 17
};

enum wBackgroundMix
{
	BmDefault         = 0,
	BmOR              = 1,
	BmOverPaint       = 2,
	BmLeaveAlone      = 5,
	BmXOR             = 4,
	BmAND             = 6,
	BmSubtract        = 7,
	BmMaskSrcNOT      = 8,
	BmZero            = 9,
	BmNOTMergeSrc     = 10,
	BmNOTXORSrc       = 11,
	BmInvert          = 12,
	BmMergeSrcNOT     = 13,
	BmNOTCopySrc      = 14,
	BmMergeNOTSrc     = 15,
	BmNOTMaskSrc      = 16,
	BmOne             = 17,
	BmSrcTransparent  = 18,
	BmDestTransparent = 19
};

enum wShadePattern
{
	PatDefault   = 0,
	PatDense1    = 1,
	PatDense2    = 2,
	PatDense3    = 3,
	PatDense4    = 4,
	PatDense5    = 5,
	PatDense6    = 6,
	PatDense7    = 7,
	PatDense8    = 8,
	PatVert      = 9,
	PatHoriz     = 10,
	PatDiag1     = 11,
	PatDiag2     = 12,
	PatDiag3     = 13,
	PatDiag4     = 14,
	PatNoShade   = 15,
	PatSolid     = 16,
	PatHalftone  = 17,
	PatHatch     = 18,
	PatDiagHatch = 19,
	PatBlank     = 64
};

enum wTextDirection 
{
	TdDefault      = 0,
	TdLeftToRight  = 1,
	TdTopToBottom  = 2,
	TdRightToLeft  = 3,
	TdBottomToTop  = 4
};

// Drawing format constants
// (used by textpen's and static text controls) 

#define DfLeft            		0x0000
#define DfQueryExtent     		0x0002
#define DfUnderscore      		0x0010
#define DfStrikeOut       		0x0020
#define DfTextAttrs       		0x0040
#define DfExternalLeading 		0x0080
#define DfCenter          		0x0100
#define DfRight           		0x0200
#define DfTop             		0x0000
#define DfVCenter         		0x0400
#define DfBottom          		0x0800
#define DfHalftone        		0x1000
#define DfMnemonic        		0x2000
#define DfWordBreak       		0x4000
#define DfEraseRect       		0x8000

enum wLineType
{
	LtDefault,
	LtDot,
	LtShortDash,
	LtDashDot,
	LtDoubleDot,
	LtLongDash,
	LtDashDoubleDot,
	LtSolid,
	LtInvisible,
	LtAlternate
};

enum wLineEndStyle
{
	LeDefault,
	LeFlat,
	LeSquare,
	LeRound
};

enum wLineJoinStyle
{
	LjDefault,
	LjBevel,
	LjRound,
	LjMitre
};

enum wPenDrawOption 
{
	DoFill = 1,
	DoOutline = 2,
	DoOutlineFill = 3
};


enum wPathClipMode
{
	PcAlternate = 0,
	PcWinding	= 2,
	PcAND	    = 4
};

enum wPathDrawOption 
{
	PdAlternate = 0,
	PdWinding	= 2
};

enum wMarkerSymbol
{
   MarkSymError			 = -1,
   MarkSymDefault        =  0,
   MarkSymCross          =  1,
   MarkSymPlus           =  2,
   MarkSymDiamond        =  3,
   MarkSymSquare         =  4,
   MarkSymSixPointStar   =  5,
   MarkSymEightPointStar =  6,
   MarkSymSolidDiamond   =  7,
   MarkSymSolidSquare    =  8,
   MarkSymDot            =  9,
   MarkSymSmallCircle    = 10,
   MarkSymBlank          = 64
};

// Pictures

#define AttrError                    (-1L)
#define AttrDetectable                 1L
#define AttrVisible                    2L
#define AttrChained                    6L
#define AttrDynamic                    8L
#define AttrFastChain                  9L
#define AttrPropDetectable            10L
#define AttrPropVisible               11L

// Devices 

#define DevEscAbortDoc 		  	8153L
#define DevEscBreakExtra      	16999L
#define DevEscCharExtra       	16998L
#define DevEscDraftMode       	16301L 
#define DevEscEndDoc   		  	8151L
#define DevEscFlushOutput      	16302L
#define DevEscGetScalingFactor 	1L
#define DevEscNewFrame 			16300L
#define DevEscNextBand 			8152L
#define DevEscQueryEscSupport  	0L
#define DevEscRawData  			16303L
#define DevEscStartDoc 			8150L

#define PmfLoadType    		1
#define PmfLcIds       		3
#define PmfReset       		4
#define PmfSuppress    		5
#define PmfcolorTables 		6
#define PmfcolorRealizable 	7

#define LtNoModify     	   	1L
#define LtOriginalView 		4L
#define LcNoLoad       		1L
#define LcLoadDisc     		3L
#define ResNoReset     		1L
#define ResReset       		2L
#define SupNoSuppress  		1L
#define SupSuppress    		2L
#define CtabNoModify   		1L
#define CtabReplace    		3L
#define CreaRealize    		1L
#define CreaNoRealize  		2L

// Regions

#define RRgnError      0L
#define RRgnOutside    1L
#define RRgnPartial    2L
#define RRgnInside     3L
#define RgnError       0L
#define RgnNull        1L
#define RgnRect        2L
#define RgnComplex     3L

// Printers...

#ifndef HCAPS_CURRENT
class HCINFO;
#endif
#ifndef	OS2DEF_INCLUDED
class DRIVDATA;
#endif
#ifndef SPL_PR_QUEUE
class _PRQINFO6;
typedef _PRQINFO6 PRQINFO6;
#endif
   
/*****************************************************************************
 *
 * wWindow System
 *
 *****************************************************************************/

#ifndef WIN_INCLUDED
typedef void *MPARAM;
typedef void *MRESULT;
typedef LHANDLE HPOINTER;
typedef LHANDLE HACCEL;
#endif

#ifndef	OS2DEF_INCLUDED
typedef struct _POINTL
{
   long  x;
   long  y;
} POINTL;
typedef POINTL *PPOINTL;

typedef struct _RECTL
{
   long  xLeft;
   long  yBottom;
   long  xRight;
   long  yTop;
} RECTL;
typedef RECTL *PRECTL;

typedef MRESULT (EXPENTRY FNWP)(HWND, ulong, MPARAM, MPARAM);
typedef FNWP *PFNWP;

#endif

// Drag'n Drop

enum wDragImageType
{
	DimIcon = 1,
	DimBitmap = 2,
	DimPolygon = 4
};

#ifndef DM_DROP
struct _DRAGTRANSFER;
typedef _DRAGTRANSFER DRAGTRANSFER;

struct _DRAGITEM;
typedef _DRAGITEM DRAGITEM;

struct _DRAGINFO;
typedef _DRAGINFO DRAGINFO;
#endif

#define DrNoDrop			0x0000		// cannot drop here
#define DrDrop				0x0001		// can drop here
#define DrNoDropOp			0x0002 		// cannot drop with current op here
#define DrNeverDrop			0x0003 		// can never drop in window
#define DoDefault			0xBFFE0000L	// Default operation
#define DoUnknown           0xBFFF0000L // Unknown operation
#define DoCopy              0x00100000L
#define DoMove              0x00200000L
#define DoLink              0x00180000L
#define DoCreate            0x00400000L

#define DrrSource            1L
#define DrrTarget            2L
#define DrrAbort             3L

#ifndef WM_CHAR
#define KC_CHAR                    0x0001
#define KC_VIRTUALKEY              0x0002
#define KC_SCANCODE                0x0004
#define KC_SHIFT                   0x0008
#define KC_CTRL                    0x0010
#define KC_ALT                     0x0020
#define KC_KEYUP                   0x0040
#define KC_PREVDOWN                0x0080
#define KC_LONEKEY                 0x0100
#define KC_DEADKEY                 0x0200
#define KC_COMPOSITE               0x0400
#define KC_INVALIDCOMP             0x0800
#endif

#define KOP_NUMPADKEYS	1
#define KOP_CTRLKEYS	2

#ifndef WM_CONTROL
#define WM_VSCROLL 0x0031
#endif

typedef void *WINTYPE;


#ifndef GPI_INCLUDED
typedef struct _SIZEL
{
   long cx;
   long cy;
} SIZEL;
typedef SIZEL *PSIZEL;
#endif

enum wWinCoordUnit
{
	DevUnits = 0,
	WorldUnits = 0,
	DlgUnits = 1
};

// cursor styles

#define CsCursorSolid 		0x0000
#define CsCursorHalfTone 	0x0001
#define CsCursorFrame 		0x0002
#define CsCursorFlash 		0x0004

// scroll styles

#define SwNone				0x0000
#define SwScrollChildren 	0x0001
#define SwInvalidateRgn 	0x0002

// Frame wWindow Attributes...

#define	FaTitleBar         0x00000001L
#define FaSysMenu  	 	   0x00000002L
#define FaMinButton		   0x00000010L
#define FaMaxButton		   0x00000020L
#define FaMinMax		   0x00000030L
#define FaSizeBorder	   0x00000008L
#define FaVertScroll	   0x00000040L
#define FaHorzScroll	   0x00000080L
#define FaDlgBorder		   0x00000100L
#define FaBorder		   0x00000200L
#define FaShellPosition	   0x00000400L
#define FaTaskList		   0x00000800L
#define FaNoByteAlign	   0x00001000L
#define FaNoMoveWithOwner  0x00002000L
#define FaSysModal		   0x00010000L
#define FaScreenAlign	   0x00020000L
#define FaMouseAlign	   0x00040000L
#define FaHideButton	   0x01000000L
#define FaHideMax		   0x01000020L

// General wWindow Styles

#define WsVisible         0x80000000L
#define WsDisabled        0x40000000L
#define WsClipChildren    0x20000000L
#define WsClipSiblings    0x10000000L
#define WsParentClip      0x08000000L
#define WsSaveBits        0x04000000L
#define WsSyncPaint       0x02000000L
#define WsMinimized       0x01000000L
#define WsMaximized       0x00800000L
#define WsAnimate         0x00400000L

#define WsGroup           0x00010000L
#define WsTabStop         0x00020000L
#define WsMultiSelect     0x00040000L

// wMenu Styles

#define MsText 			  0x0001
#define MsSeparator 	  0x0004
#define MsOwnerDraw 	  0x0008
#define MsSysCommand 	  0x0040
#define MsHelp 			  0x0080
#define MsStatic 		  0x0100
#define MsButtonSeparator 0x0200
#define MsBreak 		  0x0400
#define MsBreakSeparator  0x0800
#define MsGroup 		  0x1000
#define MsSingle 		  0x2000

#define MiEnd  (-1)

// menu actions
#define MENUINIT 	0
#define MENUEND  	1
#define MENUSELECT	2

#define MenuInit 	0
#define MenuEnd  	1
#define MenuSelect	2

// System menu id's

#define ScSize                    0x8000
#define ScMove                    0x8001
#define ScMinimize                0x8002
#define ScMaximize                0x8003
#define ScClose                   0x8004
#define ScNext                    0x8005
#define ScAppMenu                 0x8006
#define ScSysMenu                 0x8007
#define ScRestore                 0x8008


// Accelerators

#ifndef INCL_WINACCELERATORS
#pragma pack(2)
struct ACCEL
{
    ushort fs;
    ushort  key;
    ushort  cmd;
};

typedef struct _ACCELTABLE
{
    ushort  cAccel;
    ushort  codepage;
    ACCEL   aaccel[1];
} ACCELTABLE;
#pragma pack()
#endif

// accelerator key styles

#define AsChar 			  	0x0001
#define AsVirtualKey 		0x0002
#define AsShift 			0x0008
#define AsControl 			0x0010
#define AsAlt 			  	0x0020
#define AsLoneKey 			0x0040
#define AsSysCommand 		0x0100
#define AsHelp 			  	0x0200

// virtual keystrokes

#define VkButton1                 0x01
#define VkButton2                 0x02
#define VkButton3                 0x03
#define VkBreak                   0x04
#define VkBackspace               0x05
#define VkTab                     0x06
#define VkBacktab                 0x07
#define VkNewline                 0x08
#define VkShift                   0x09
#define VkCtrl                    0x0A
#define VkAlt                     0x0B
#define VkAltgraf                 0x0C
#define VkPause                   0x0D
#define VkCapslock                0x0E
#define VkEsc                     0x0F
#define VkSpace                   0x10
#define VkPageup                  0x11
#define VkPagedown                0x12
#define VkEnd                     0x13
#define VkHome                    0x14
#define VkLeft                    0x15
#define VkUp                      0x16
#define VkRight                   0x17
#define VkDown                    0x18
#define VkPrintscrn               0x19
#define VkInsert                  0x1A
#define VkDelete                  0x1B
#define VkScrllock                0x1C
#define VkNumlock                 0x1D
#define VkEnter                   0x1E
#define VkSysrq                   0x1F
#define VkF1                      0x20
#define VkF2                      0x21
#define VkF3                      0x22
#define VkF4                      0x23
#define VkF5                      0x24
#define VkF6                      0x25
#define VkF7                      0x26
#define VkF8                      0x27
#define VkF9                      0x28
#define VkF10                     0x29
#define VkF11                     0x2A
#define VkF12                     0x2B
#define VkF13                     0x2C
#define VkF14                     0x2D
#define VkF15                     0x2E
#define VkF16                     0x2F
#define VkF17                     0x30
#define VkF18                     0x31
#define VkF19                     0x32
#define VkF20                     0x33
#define VkF21                     0x34
#define VkF22                     0x35
#define VkF23                     0x36
#define VkF24                     0x37
#define VkEndDrag                 0x38
#define VkMenu                    VkF10
#define VkDbcsFirst               0x0080
#define VkDbcsFast                0x00ff
#define VkUserFirst               0x0100
#define VkUserFast                0x01ff

// System Icons/Pointers

#define PtArrow                 1
#define PtText                  2
#define PtWait                  3
#define PtSize                  4
#define PtMove                  5
#define PtSizeNWSE              6
#define PtSizeNESW              7
#define PtSizeWE                8
#define PtSizeNS                9
#define PtAppIcon               10
#define PtIconInformation       11
#define PtIconQuestion          12
#define PtIconError             13
#define PtIconWarning           14
#define PtIllegal               18
#define PtFile                  19
#define PtFolder                20
#define PtMultfile              21
#define PtProgram               22

// System Bitmaps

#define SbOldSysmenu            1
#define SbOldSbUpArrow          2
#define SbOldSbDnArrow          3
#define SbOldSbRgArrow          4
#define SbOldSbLfArrow          5
#define SbMenuCheck             6
#define SbOldCheckBoxes         7
#define SbBtnCorners            8
#define SbOldMinButton          9
#define SbOldMaxButton          10
#define SbOldRestoreButton      11
#define SbOldChildSysMenu       12
#define SbDrive                 15
#define SbFile                  16
#define SbFolder                17
#define SbTreePlus              18
#define SbTreeMinus             19
#define SbProgram               22
#define SbMenuAttached          23
#define SbSizeBox               24
#define SbSysMenu               25
#define SbMinButton             26
#define SbMaxButton             27
#define SbRestoreButton         28
#define SbChildSysMenu          29
#define SbSysMenuDep            30
#define SbMinButtonDep          31
#define SbMaxButtonDep          32
#define SbRestoreButtonDep      33
#define SbChildSysMenuDep       34
#define SbSbUpArrow             35
#define SbSbDnArrow             36
#define SbSbLfArrow             37
#define SbSbRgArrow             38
#define SbSbUpArrowDep          39
#define SbSbDnArrowDep          40
#define SbSbLfArrowDep          41
#define SbSbRgArrowDep          42
#define SbSbUpArrowDis          43
#define SbSbDnArrowDis          44
#define SbSbLfArrowDis          45
#define SbSbRgArrowDis          46
#define SbComboDown             47
#define SbCheckBoxes            48

// Control Windows...

enum wControlType
{
	CtEntry,
	CtComboBox,
	CtStatic,
	CtButton,
	CtMLE,
	CtListBox,
	CtCellBox,
	CtIconButton,
	CtContainer,
	CtNotebook,
	CtSlider,
	CtValueSet
};

// Check box styles

#define BsAuto				0x0002L
#define BsThreeState		0x0004L
#define BsNoPointerFocus	0x0800L

// Radio Button styles

//      BsAuto
//      BsNoPointerFocus
#define BsNoCursorSelect	0x2000L

// Push Button styles

#define BsHelp				0x0100L
#define BsSysCommand		0x0200L
#define BsDefault			0x0400L
#define BsNoBorder			0x1000L
#define BsAutoSize			0x4000L
//      BsNoPointerFocus

// Scroll Bar types

enum wScrollBarType
{
	Horizontal,
 	Vertical
};

#define SbmLineUp			1
#define SbmLineDown			2
#define SbmLineLeft			1
#define SbmLineRight		2
#define SbmPageUp			3
#define SbmPageDown			4
#define SbmPageLeft			3
#define SbmPageRight		4
#define SbmSliderTrack		5
#define SbmSliderPosition	6
#define SbmEndScroll		7

#define SbsAutoTrack		4
#define SbsAutoSize			0x2000

// ListBoxes
							
#define LiNone			 (-1)
#define LiFirst			 (-1)
#define LiEnd			 (-1)
#define LiSortAscending	 (-2)
#define LiSortDecending	 (-3)
#define LiCursor		 (-4)
#define LiBegining		 (-8)
#define LiInsert		 (-9)

#define LsMultipleSelect  0x0001L
#define LsOwnerDraw	      0x0002L
#define LsNoAdjustPos	  0x0004L
#define LsHorzScroll      0x0008L
#define LsExtendedSelect  0x0010L

// listbox find options

#define LfSubString 	  0x0001
#define LfPrefix 		  0x0002
#define LfCaseSensitive   0x0004

// Edit controls

#define EsLeftJust    0x00000000L
#define EsCenter      0x00000001L
#define EsRightJust   0x00000002L
#define EsAutoScroll  0x00000004L
#define EsMargin      0x00000008L
#define EsAutoTab     0x00000010L
#define EsReadOnly    0x00000020L
#define EsCommand     0x00000040L
#define EsUnReadable  0x00000080L
#define EsAutoSize    0x00000200L
#define EsAny         0x00000000L
#define EsSbcs        0x00001000L
#define EsDbcs        0x00002000L
#define EsMixed       0x00003000L

// Multi-line edit controls

#define MlWordWrap      0x00000001L		// Styles
#define MlBorder        0x00000002L
#define MlVscroll       0x00000004L
#define MlHscroll       0x00000008L
#define MlReadOnly      0x00000010L
#define MlIgnoreTab     0x00000020L
#define MlDisableUndo   0x00000040L

// multi-line edit search options

#define MlNone			0
#define MlCaseSensitive 1
#define MlSelectMatch 	2
#define MlChangeAll 	4

enum wMlTextFormat
{
	MlCfText,
	MlNoTranslate,
	MlWinFormat,
	MlRTF
};

#define MlNoLimit	(-1)	// text limit

// multi-line format rectangle options
#define MlLimitHorizontal	0x00000001L
#define MlLimitVertical		0x00000002L
#define MlLimitMatchWindow	0x00000004L

// Spin Buttons

#define SbAllCharacters 0x00000000L 	 // Styles
#define SbNumericOnly   0x00000001L 
#define SbReadOnly      0x00000002L 
#define SbMaster        0x00000010L
#define SbServant       0x00000000L 
#define SbJustDefault   0x00000000L 
#define SbLeftJust      0x00000008L
#define SbRightJust     0x00000004L
#define SbCenter        0x0000000CL
#define SbNoBorder      0x00000020L 
#define SbFastSpin      0x00000100L 
#define SbPadWithZeros  0x00000080L 

enum wSbUpdateMethod
{
	SbUpdateIfValid = 0, 
	SbAlwaysUpdate = 1, 
	SbDoNotUpdate = 3  
};
 
// Sliders

#define SlHorizontal       0x00000000L /* Orient slider horizontally*/
#define SlVertical         0x00000001L /* Orient slider vertically  */
#define SlBottomLeft       0x00000002L /* Offset shaft to bottom left*/
#define SlTopRight         0x00000004L /* Offset shaft to top right */
#define SlCenter           0x00000000L /* Center shaft in window    */
#define SlSnaptoincrement  0x00000008L /* Snap to nearest increment */
#define SlBtnBottomLeft    0x00000010L /* Add buttons at shaft bot. left*/
#define SlBtnTopRight      0x00000020L /* Add buttons at shaft top  right*/
#define SlOwnerDraw        0x00000040L /* Owner draw some fields    */
#define SlReadOnly         0x00000080L /* Provide a read only slider*/
#define SlRibbonStrip      0x00000100L /* Provide a ribbon strip    */
#define SlHomeRight        0x00000200L /* Set home position at right*/
#define SlHomeTop          0x00000200L /* Set home position at right*/
#define SlPrimaryScale2    0x00000400L /* Scale 2 is primary scale  */

enum wSliderScale
{
	ScaleOne,
	ScaleTwo
};

// Combo boxes

#define CbsSimple		 0x0001L
#define CbsDropDown		 0x0002L
#define CbsDropDownList	 0x0004L

#define CbnSetFocus		90
#define CbnKillFocus	91

// Multi-select combo boxes
#define McsSimple		0x0000L
#define McsDropDownList	0x0001L

// ValueSets

// item attributes

#define VlNone 		   0
#define VlOwnerDraw	   0x0020
#define VlDisabled 	   0x0040


#define VsBitmap       0x0001   /* Default all items to bitmaps      */
#define VsIcon         0x0002   /* Default all items to icons        */
#define VsText         0x0004   /* Default all items to text strings */
#define VsRGB          0x0008   /* Default all items to color info   */
#define VsColorIndex   0x0010   /* Default all items to color indices*/
#define VsBorder       0x0020   /* Add a border around the control   */
#define VsItemBorder   0x0040   /* Add a border around each item     */
#define VsScaleBitmaps 0x0080   /* Scale bitmaps to cell size        */
#define VsRightToLeft  0x0100   /* Support right to left ordering    */
#define VsOwnerDraw    0x0200   /* Owner draws value set background  */


// Notebooks

#define BkBPgBottomRight       0x00000001  /* Bottom right          */
#define BkBPgBottomLeft        0x00000002  /* Bottom left           */
#define BkBPgTopRight          0x00000004  /* Top right             */
#define BkBPgTopLeft           0x00000008  /* Top left              */
#define BkMajorTabRight        0x00000010  /* Major tabs right      */
#define BkMajorTabLeft         0x00000020  /* Major tabs left       */
#define BkMajorTabTop          0x00000040  /* Major tabs top        */
#define BkMajorTabBottom       0x00000080  /* Major tabs bottom     */
#define BkSquareTabs           0x00000000  /* Square edged tabs     */
#define BkRoundedTabs          0x00000100  /* Round edged tabs      */
#define BkPolygonTabs          0x00000200  /* Polygon edged tabs    */
#define BkSolidBinding         0x00000000  /* Solid binding         */
#define BkSpiralBinding        0x00000400  /* Spiral binding        */
#define BkStatusTextLeft       0x00000000  /* Left justify text     */
#define BkStatusTextRight      0x00001000  /* Right justify text    */
#define BkStatusTextCenter     0x00002000  /* Center text           */
#define BkTabtExtLeft          0x00000000  /* Left justify tab text */
#define BkTabtExtRight         0x00004000  /* Right justify tab text*/
#define BkTabtExtCenter        0x00008000  /* Center tab text       */

// Page attributes

#define BpStatusTextOn	0x0001
#define BpMajor			0x0040
#define BpMinor			0x0080
#define BpAutoPageSize  0x0100

enum wNoteBookAttrib
{
	MajorTabForeground,
	MajorTabBackground,
	MinorTabForeground,
	MinorTabBackground,
	PageBackground	
};

// CellBox controls

#define ColPels				0x00000000L
#define ColDialog			0x00010000L
#define ColTwips			0x00800000L
#define ColHidden			0x00040000L
#define ColBlank			0x00200000L
#define ColLeft				0x00000000L 
#define ColRight			0x00000200L 
#define ColCenter			0x00000100L
#define ColVCenter			0x00000400L
#define ColColor			0x00100000L
#define ColRightScoreSolid	0x00800000L
#define ColRightScoreDotted	0x01000000L
#define ColCellSelect		0x02000000L
#define ColInUseEmph		0x08000000L

#define LsVertScroll	  0x0100L
#define LsNoSelect		  0x0400L
#define LsOutsideTitle	  0x0020L
#define LsInsideTitle	  0x0040L
#define LsLockColumn	  0x0080L
#define LsNoActivate	  0x1000L
#define LsAdjustAtBottom  0x2000L

#define CellInUseEmph		0x0008L
#define CellSelectedEmph	0x0001L
#define CellTargetEmph		0x0010L
#define CellSourceEmph		0x0020L

// Static Controls

// Styles
#define SsAutoSize	0x00000040L

enum wSFrameType
{
	SForegrnd,
	SHalfTone,
	SBackgrnd
};

// Message Box Options

#define MbOk                      0x0000L
#define MbOkCancel                0x0001L
#define MbRetryCancel             0x0002L
#define MbAbortRetryIgnore        0x0003L
#define MbYesNo                   0x0004L
#define MbYesNoCancel             0x0005L
#define MbCancel                  0x0006L
#define MbEnter                   0x0007L
#define MbEnterCancel             0x0008L
#define MbIconQuestion            0x0010L
#define MbIconExclamation         0x0020L
#define MbIconAsterisk            0x0030L
#define MbIconHand                0x0040L
#define MbDefButton1              0x0000L
#define MbDefButton2              0x0100L
#define MbDefButton3              0x0200L
#define MbApplModal               0x0000L
#define MbSystemModal             0x1000L
#define MbHelp                    0x2000L
#define MbMoveable                0x4000L

// Message box return codes

#define MrOK                    1
#define MrCancel                2
#define MrAbort                 3
#define MrRetry                 4
#define MrIgnore                5
#define MrYes                   6
#define MrNo                    7
#define MrHelp                  8
#define MrEnter                 9
#define MrError                 0xffff


enum wStdMsgBox
{
	MbxLastError,
	MbxExtLastError
};


enum wOverflowType
{
	TextOverflow,
	HorzPixelOverflow,
	VertPixelOverflow,
	Overflow,
	UndoOverflow
};

// Mle overflow reasons

#define OrNotApplicable		0x00000000L
#define OrReSize			0x00000001L 
#define OrTabStopChange		0x00000002L
#define OrFontChange		0x00000004L
#define OrTextChangeFormat	0x00000008L
#define OrWordWrap			0x00000010L
#define OrTextChangeBytes	0x00000020L

enum wMLEMargin
{
	LeftMargin,
	BottomMargin,
	RightMargin,
	TopMargin
};

// IDs of standard buttons
#define DidOK	 			1
#define DidCancel			2

// Standard file dialog...
#define SfdListboxSelect	0
#define SfdEntryFieldSelect	1

#define SfdOk		   		1	// return codes from Error method
#define SfdCancel			2
#define SfdRetry			4

// file dialog attributes
#define FdaCenter           0x00000001L // Center within owner wnd  
#define FdaCustom           0x00000002L // Use custom user template 
#define FdaFilterUnion      0x00000004L // Use union of filters     
#define FdaHelpButton       0x00000008L // Display Help button      
#define FdaApplyButton      0x00000010L // Display Apply button     
#define FdaPreloadVolInfo   0x00000020L // Preload volume info      
#define FdaIncludeEAs       0x00000080L // Always load EA info      
#define FdaMultipleSel      0x00000400L // Enable multiple selection
#define FdaEnableFileLB     0x00000800L // Enable SaveAs Listbox    

// file dialog errors
#define	FdeSuccessful			0
#define FdeDeallocateMemory 	1
#define FdeFilterTrunc      	2
#define FdeInvalidDialog		3
#define FdeInvalidDrive			4
#define FdeInvalidFilter		5
#define FdeInvalidPath			6
#define FdeOutOfMemory			7	
#define FdePathTooLong			8
#define FdeTooManyFileTypes		9
#define FdeInvalidVersion		10
#define FdeInvalidCustomHandle	11
#define FdeDialogLoadError		12
#define FdeDriveError			13

// file dialog static control ids for changing their text
#define   FdFilenameTxtId            257
#define   FdDriveTxtId               259
#define   FdFilterTxtId              261
#define   FdDirectoryTxtId           263
#define   FdFilesTxtId               265
#define   FdHelpPushButtonId         267
#define   FdApplyPushButtonId        268
#define   FdOKPushButtonId			 DidOK
#define   FdCancelButtonId			 DidCancel

// font dialog attributes
#define FnaCenter              0x00000001L // Center in owner dialog
#define FnaCustom              0x00000002L // Use custom template   
#define FnaOwnerDrawPreview    0x00000004L // Allow app to draw     
#define FnaHelpButton          0x00000008L // Display Help button   
#define FnaApplyButton         0x00000010L // Display Apply button  
#define FnaResetButton         0x00000020L // Display Reset button  
#define FnaModeless            0x00000040L // Make dialog modeless  
#define FnaInitFromFattrs      0x00000080L // Initialize from FATTRs
#define FnaBitmapOnly          0x00000100L // Only allow bitmap font
#define FnaVectorOnly          0x00000200L // Only allow vector font
#define FnaFixedWidthOnly      0x00000400L // Only allow monospaced 
#define FnaProportionalOnly    0x00000800L // Only proportional font
#define FnaNosynthesizedFonts  0x00001000L // Don't synthesize fonts

// font dialog static control ids for changing their text
#define FnDisplayFilerId       303
#define FnPrinterFilterId      304
#define FnOutlineId            307
#define FnUnderscoreId         308
#define FnStrikeoutId          309
#define FnHelpPushButtonId     310
#define FnApplyPushButtonId    311
#define FnResetPushButtonId    312
#define FnOKPushButtonId       DidOK
#define FnCancelPushButtonId   DidCancel
#define FnNamePrefixId         313
#define FnStylePrefixId        314
#define FnSizePrefixId         315
#define FnSampleGroupBoxId     316
#define FnEmphasisGroupBoxId   317

// font state flags   
#define FnsNoViewScreenFonts      1L
#define FnsNoViewPrinterFonts     2L
#define FnsScreenFontSelected     4L
#define FnsPrinterFontSelected    8L
   
// Filter List message string identifiers
#define FniBitmapFont         0x0001
#define FniVectorFont         0x0002
#define FniFixedWidthFont     0x0004
#define FniProportionalFont   0x0008
#define FniSynthesized        0x0010
#define FniDefaultList        0x0020
#define FniFamilyName         0x0100
#define FniStyleName          0x0200
#define FniPointSize          0x0400
   
// Error Return Codes from dialog
#define  FneSuccessful        0
#define  FneInvalidDialog     3
#define  FneAllocSharedMem    4
#define  FneInvalidParm       5
#define  FneOutOfMemory       7
#define  FneInvalidVersion    10
#define  FneDialogLoadError   12

// flType flags
#define FtItalic              0x0001
#define FtItalicDontCare      0x0002
#define FtOblique             0x0004
#define FtObliqueDontCare     0x0008
#define FtRounded             0x0010
#define FtRoundedDontCare     0x0020

// Popup menus

#define PumPositionOnItem		0x0001	
#define PumVConstrain			0x0002
#define PumHConstrain			0x0004
#define PumNone					0x0000
#define PumMouseButton1Down		0x0008
#define PumMouseButton2Down		0x0010
#define PumMouseButton3Down		0x0018
#define PumSelectItem			0x0020
#define PumMouseButton1			0x0040
#define PumMouseButton2			0x0080
#define PumMouseButton3			0x0100
#define PumKeyboard				0x0200

// Track rectangle 

#define TfLeft				0x0001
#define TfTop				0x0002
#define TfRight				0x0004
#define TfBottom			0x0008
#define TfMove				0x000F
#define TfSetPointerPos		0x0010
#define TfGrid				0x0020
#define TfStandard			0x0040
#define TfAllInBoundary		0x0080
#define TfValidateTrackRect	0x0100
#define TfPartInBoundary	0x0200

#define WmButton1Dblclk		0x0073
#define WmButton2Dblclk		0x0076
#define WmButton3Dblclk		0x0079
#define WmButton1Down		0x0071
#define WmButton2Down		0x0074
#define WmButton3Down		0x0077
#define WmButton1Up			0x0072
#define WmButton2Up			0x0075
#define WmButton3Up			0x0078
#define WmButton1Click		0x0413
#define WmButton2Click		0x0416
#define WmButton3Click		0x0419

// wImageButton

enum wImageButtonImage {
	IbUpImageIndex,
	IbDownImageIndex,
	IbDisabledImageIndex
};

#define	IbTextOnBtn				0x00000000L	// Button Style: Text on Button
#define	IbTextOffBtn			0x00000001L	// Button Style: Text off Button	
#define	IbButtonStick			0x00000002L	// Button Style: Button	stick in pos
#define IbHelp             		0x00000100L	// post WM_HELP message
#define IbSysCommand       		0x00000200L	// post WM_SYSCOMMAND
#define IbDefault          		0x00000400L	// Default button
#define IbNoPointerFocus   		0x00000800L	// No pointer focus
#define IbNoBorder		        0x00001000L	// No border on button
#define IbAutoImageBtn			0x00000004L	// Unclick others in group

#define IbTextBottom			0x00000000L	// Button Style: Text on bottom
#define IbTextTop				0x00000010L // Button Style: Text on top
#define IbTextLeft				0x00000020L	// Button Style: Text on left
#define IbTextRight				0x00000040L // Button Style: Text on right

#define IbBitmap				0x00000000L	// Button Style: Images are bitmaps
#define	IbIcon					0x00002000L // Button Style: Images are icons
#define IbAutoSize				0x00004000L	// Button Style: Auto Size

// 3D panels

#define P3OuterRaised	0x00000000L
#define P3OuterInset	0x00000001L
#define P3InnerRaised	0x00000002L
#define P3InnerInset 	0x00000000L
#define P3NoInner		0x00000004L
#define P3Border		0x00000008L
#define P3TextCenter	0x00000000L
#define P3TextLeft		0x00000010L
#define P3TextRight		0x00000020L
#define P3TextVCenter	0x00000000L
#define P3TextTop		0x00000040L
#define P3TextBottom	0x00000080L
#define P3GroupBox		0x00000100L

// drawing return values

#define GraphError		0
#define GraphOK			1
#define GraphHit		2

// spreadsheet style flags
#define SsDottedGrid	0x0000
#define SsNoGrid		0x0001
#define SsSolidGrid		0x0002
#define SsNoSelect		0x0004
#define SsNoHeaders		0x0008
#define SsDirectSize	0x0010
#define SsNoHeaderBevel	0x0020
#define SsDirectEdit	0x0000
#define SsEditNotify	0x0040
#define SsEditOverwrite	0x0000
#define SsEditInsert	0x0080

// cell style flags
#define ScProtect		0x0001

// row column style flags
#define SrcHidden		0x0001
#define SrcProtect		0x0002

// cell alignment options
enum CellAlignment {
	AlignLeft,
	AlignRight,
	AlignCenter,
	AlignGeneral,
	AlignWordWrap
};

#define CslNoButtons            0x0001
#define CslNoText               0x0002
#define CslNoNumber             0x0004
#define CslPointSelect          0x0008
#define Csl360                  0x0010
#define CslMidPoint             0x0020
#define CslProportionalTicks    0x0040
#define CslNoTicks              0x0080
#define CslCircularThumb        0x0100

enum CircSliderBitmap {
	CSBSDecrementUp,
	CSBDecrementDown,
	CSBIncrementUp,
	CSBIncrementDown
};

#endif // __WINDEFS_H
