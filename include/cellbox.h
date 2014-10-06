/*  VCS_ID
 *  $Filename:   cellbox.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.2  $
 *  $Date:   07 Aug 1991 15:02:02  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#ifndef __CELLBOX_H
#define __CELLBOX_H

/* Style definitions */

#ifdef  IN_PMWIN_H
#define LS_MULTIPLESEL		0x00000001L
#define LS_OWNERDRAW		0x00000002L
#define LS_NOADJUSTPOS		0x00000004L
#define LS_HORZSCROLL		0x00000008L
#define LS_EXTENDEDSEL      0x00000010L
#endif
#define LS_VERTSCROLL 		0x00000100L
#define LS_MULTCOLUMN       0x00000200L
#define LS_NOSELECT			0x00000400L
#define LS_FIXEDLINES       0x00000800L
#define LS_OUTSIDETITLE		0x00000020L
#define LS_INSIDETITLE		0x00000040L
#define LS_LOCKCOLUMN		0x00000080L
#define LS_NOACTIVATE		0x00001000L

/* Status definitions */

#define ST_FOCUS			0x00010000L
#define ST_NOINVAL          0x00020000L
#define ST_CAPTURE          0x00040000L
#define ST_SELMODE          0x00080000L
#define ST_TIMER            0x00100000L
#define ST_CELLCAPTURE		0x00200000L
#define ST_EDITING			0x00400000L
#define SELECTMODE(p) ((SHORT)((p->fOptions & ST_SELMODE) != 0))

/* For LM_INSERTITEM msg */

#ifdef  IN_PMWIN_H
#define LIT_END 		    (-1)
#define LIT_SORTASCENDING	(-2)
#define LIT_SORTDESCENDING	(-3)
#endif
#define LIT_BEGINING        (-8)
#define LIT_INSERT          (-9)

/* This section is for reference.  The following defines are the  */
/* standard defines for PM listboxes.  They are here for reference  */
/* purposes only. */

#ifdef  PMDEFS

/* List box notification messages */

#define LN_SELECT		1
#define LN_SETFOCUS		2
#define LN_KILLFOCUS	3
#define LN_SCROLL		4
#define LN_ENTER		5

/* List box messages */

#define LM_QUERYITEMCOUNT	0x0160
#define LM_INSERTITEM		0x0161
#define LM_SETTOPINDEX		0x0162
#define LM_DELETEITEM		0x0163
#define LM_SELECTITEM		0x0164
#define LM_QUERYSELECTION	0x0165
#define LM_SETITEMTEXT		0x0166
#define LM_QUERYITEMTEXTLENGTH	0x0167
#define LM_QUERYITEMTEXT	0x0168

#define LM_SETITEMHANDLE	0x0169
#define LM_QUERYITEMHANDLE	0x016a
#define LM_SEARCHSTRING 	0x016b
#define LM_SETITEMHEIGHT	0x016c
#define LM_QUERYTOPINDEX	0x016d
#define LM_DELETEALL		0x016e

/* List box constants */

#define LIT_ERROR		(-3)
#define LIT_MEMERROR	(-2)
#define LIT_NONE		(-1)
#define LIT_FIRST		(-1)
#endif

#define LIT_HANDLE      (-1)
#define LIT_SET         (-1)
#define LIT_NULL        (-2)

#ifdef  IN_PMWIN_H
/* For LM_SEARCHSTRING msg */

#define LSS_SUBSTRING		0x0001
#define LSS_PREFIX		    0x0002
#define LSS_CASESENSITIVE	0x0004
#endif

/* Added messages for Cellboxes */

#define CELLMSGBASE 0x7F00
#define LM_SETCELLWIDTH   		(CELLMSGBASE+0x00)
#define LM_SETFIXEDLINES  		(CELLMSGBASE+0x01)
#define LM_SETFMTSTRING   		(CELLMSGBASE+0x02)
#define LM_SETCELLMETRICS 		(CELLMSGBASE+0x03)
#define LM_INSCELLITEM    		(CELLMSGBASE+0x04)
#define LM_GETITEMFLAGS   		(CELLMSGBASE+0x05)
#define LM_SETITEMFLAGS   		(CELLMSGBASE+0x06)
#define LM_SETSUBCOLUMNS  		(CELLMSGBASE+0x07)
#define LM_SETATTRIBUTES		(CELLMSGBASE+0x08)
#define LM_QUERYSELCOUNT  		(CELLMSGBASE+0x09)
#define LM_INVCELLCOLUMN  		(CELLMSGBASE+0x0a)
#define LM_SETTITLETEXT			(CELLMSGBASE+0x0b)
#define LM_QUERYTITLETEXT		(CELLMSGBASE+0x0c)
#define LM_QUERYTITLETEXTLENGTH	(CELLMSGBASE+0x0d)
#define LM_SETTITLEHEIGHT		(CELLMSGBASE+0x0e)
#define LM_QUERYTITLEHEIGHT		(CELLMSGBASE+0x0f)
#define LM_QUERYSUBCOLUMN		(CELLMSGBASE+0x10)
#define LM_QUERYATTRIBUTE		(CELLMSGBASE+0x11)
#define LM_QUERYCOLUMNCOUNT		(CELLMSGBASE+0x12)
#define LM_DELETESUBCOLUMN      (CELLMSGBASE+0x13)
#define LM_DELETEATTRIB			(CELLMSGBASE+0x14)
#define LM_DELETEALLSUBCOLUMNS	(CELLMSGBASE+0x15)
#define LM_SETSUBCOL			(CELLMSGBASE+0x16)
#define LM_ADDSUBCOLGROUP		(CELLMSGBASE+0x17)
#define LM_SETITEMCOLGROUP		(CELLMSGBASE+0x18)
#define LM_QUERYITEMCOLGROUP	(CELLMSGBASE+0x19)
#define LM_QUERYCOLGROUPCOUNT	(CELLMSGBASE+0x1a)
#define LM_SETITEMEMPHASIS		(CELLMSGBASE+0x1b)
#define LM_QUERYITEMEMPHASIS	(CELLMSGBASE+0x1c)
#define LM_SETINDENT			(CELLMSGBASE+0x1d)
#define LM_QUERYINDENT			(CELLMSGBASE+0x1e)
#define LM_SETTAGCHAR			(CELLMSGBASE+0x1f)
#define LM_QUERYTAGCHAR			(CELLMSGBASE+0x20)

#define LN_SETDRAG   	6

#define LN_CELLSELECT	7
#define LN_CELLENTER	8

#define LN_DRAGLEAVE	VN_DRAGLEAVE
#define LN_DRAGOVER		VN_DRAGOVER
#define LN_DROP			VN_DROP
#define LN_DROPHELP		VN_DROPHELP
#define LN_INITDRAG		VN_INITDRAG
#define LN_CONTEXTMENU	CN_CONTEXTMENU
#define LN_DELETE		9

/* sub-column option flags */

#define COL_PELS				0x00000000L
#define COL_DIALOG				0x00010000L
#define COL_DISABLED 			0x00020000L
#define COL_HIDDEN				0x00040000L
#define COL_NOSCROLL    		0x00080000L
#define COL_COLOR  				0x00100000L
#define COL_BLANK       		0x00200000L
#define COL_RELATIVE    		0x00000000L
#define COL_PLACELOC    		0x00400000L
#define COL_LEFT        		0x00000000L      
#define COL_RIGHT       		0x00000200L  
#define COL_CENTER      		0x00000100L
#define COL_TOP					0x00000000L
#define COL_BOTTOM      		0x00000800L
#define COL_VCENTER     		0x00000400L
#define COL_HALFTONE    		0x00001000L
#define COL_WORDBREAK   		0x00008000L
#define COL_RIGHTSCORESOLID 	0x00800000L
#define COL_RIGHTSCOREDOTTED 	0x01000000L
#define COL_CELLSELECT			0x02000000L
#define COL_DIRECTEDIT			0x04000000L
#define COL_INUSEEMPH			0x08000000L

#define ATTR_COLOR		0x0001
#define ATTR_FONT       0x0002
#define ATTR_BACKCLR    0x0004
#define ATTR_BITMAP     0x0008
#define ATTR_FILLPAT	0x0010
#define ATTR_ICON		0x0020

typedef struct _CELL
{
	SHORT row;
	SHORT col;
} CELL;

typedef CELL *PCELL;

typedef struct _CBCTLDATA
{
	LONG	cb;
	SHORT 	ndx;
	SHORT	maxtabs;
	SHORT	maxattrs;
} CBCTLDATA;

typedef CBCTLDATA *PCBCTLDATA;
#define LI_SELECTED 0x01
#define LI_HIDDEN   0x02
#define LI_SUBSEL   0x04
#define LI_INUSE	0x08
#define LI_TARGET	0x10
#define LI_SOURCE	0x20

#ifdef __PMLIST_H
typedef struct _CELLITEM 
{
	LHEADER lhdr;			/* linked list header */
	ULONG hItem;			/* user defined item handle */
	USHORT colNdx;			/* index of the subcolumn group to use */
	char ItemBuf[2];		/* 1st two bytes of the list item data */
} CELLITEM;

typedef CELLITEM *PCELLITEM;
#else
typedef void *PCELLITEM;
typedef void *PLINK;
#endif


#define WC_CELLBOX "CellBox"
#define MAXTABSTOPS 30
#define CBX_MAXTABSTOPS MAXTABSTOPS
#define MAXATTRS    10
#define CBX_MAXATTRS MAXATTRS

typedef struct _SUBCOLDEF 
{
	SHORT  colWidth;
	LONG   colColor;
	ULONG  colFlags;
} SUBCOLDEF;

typedef struct _ATTRIBDEF
{
	SHORT setFlags;		/* determines which attributes to set */
	LONG  clrAtt;		/* character color */
	LONG  fontAtt;		/* local font id */
} ATTRIBDEF; 

typedef SUBCOLDEF *PSUBCOLDEF;
typedef ATTRIBDEF *PATTRIBDEF;

typedef struct _SEARCHDEF
{
	SHORT flags;
	SHORT index;
	SHORT column;
	char *s;
} SEARCHDEF;
typedef SEARCHDEF *PSEARCHDEF;

typedef struct _CBCTLDATA1
{
	LONG		cb;
	short		maxtabs;
	short 		maxattrs;
	char		tagchar;
	long		colcount;
	SUBCOLDEF	tabs[100];
	char		title[255];
} CBCTLDATA1;

typedef CBCTLDATA1 *PCBCTLDATA1;

typedef struct _CELLBOX 
{
	ULONG fOptions;			/* option flags */
	HWND hwndCell;			/* back pointer to the window  */
	HWND hwndHscroll;		/* window handle of the horz scroll bar */
	HWND hwndVscroll;		/* window handle of the vert scroll bar */
	PLINK itemlist;			/* pointer to linked list header structure */
	RECTL BoxRect;			/* rectange of the drawing area */
	POINTL CellOne;			/* window coordinates of the first cell */
    SHORT cxChar;			/* current font metrics */
	SHORT cxCaps;
	SHORT cyChar;
	SHORT cyDesc;
	SHORT nColumns;			/* count of column partitions (on screen) */
	SHORT nColWidth;		/* width of the column partitions  */
	SHORT nColHeight;		/* number of lines / column */
	SHORT nColStart;		/* indent width of first char position */
	SHORT nCurrCols;		/* number of columns currently occupied */
	SHORT nSelected;		/* count of selected items */
	SHORT nHeight;			/* item height */
	SHORT nLines;			/* number of items high	 (on screen) */
	SHORT nTabGroups;
	SHORT nTabStops[10];	/* count of the number of tab stops defined */
	SHORT maxTabStops[10];
	SUBCOLDEF *tabs[10];
	SHORT maxAttrs;
	ATTRIBDEF *attrs;
	SHORT sHscrollMax;		/* non-zero if horizontal scrolling is on		  */
	SHORT sVscrollMax;		/* non-zero if vertical scrolling is on */
	SHORT sHscrollPos;		/* scroll bar position variable - horizontal */
	SHORT sVscrollPos;		/* scroll bar position variable - vertical */
	SHORT AnchCellNo;		/* Current anchor cell for dragging */
	SHORT SelectCellNo;		/* Current cellselect cell row */
	SHORT SelectCellCol;	/* Current cellselect cell column */
 	SHORT CurrCellNo;		/* Current end of a selected block */
	SHORT LastQItem;		/* Last item number returned by LM_QUERYSELECTION */
	PCELLITEM pLastQ;		/* pointer to last item returned by  "      " */
	PCELLITEM pCellOne;		/* pointer to top left item */
	PCELLITEM pCursor;		/* pointer to the owner of the cursor */

	LONG	colors[5];		/* colors from presparams */

	HPOINTER	hptrArrow;	/* handle of the normal pointer to use */
	PCELLITEM	title;		/* pointer to title (as a cellitem for speed) */
	RECTL 		TitleRect;	/* rectangle for the title text	*/
	SHORT		TitleHeight;/* height of title rectangle */	
	HWND		EditWin;	/* direct editing window */
	RECTL		EditRect;	/* rectangle of direct editing window */
	SHORT 		EditCellNo;	/* row of Cell being */
	SHORT 		EditCellCol;/* column of cell being edited */
	PCELLITEM	EditItem;	/* old cell text */
	USHORT		id;			/* control id */
	HWND		owner;		/* owner window */
	char		tagchar;	/* command character - default to ! */
} CELLBOX;

typedef CELLBOX *PCELLBOX;

#endif // __CELLBOX_H
