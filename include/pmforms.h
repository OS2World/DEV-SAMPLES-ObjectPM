/*  VCS_ID
 *  $Filename:   pmforms.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.4  $
 *  $Date:   19 Dec 1991 15:16:38  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
/* PMForms.
 * 
 * A data form system for the OS/2 Presentation Manager
 *
 * Author: John Pompeii, 1989-1990
 */

#ifndef __PMFORMS_H
#define __PMFORMS_H

#include "cellbox.h"
				 
#if defined(__cplusplus)
    extern "C"
    {
#endif

/* field types */

#define F_STRING 0
#define F_INT    1
#define F_CHAR   2
#define F_LONG   3
#define F_DATE   4
#define F_FLOAT  5
#define F_BOOL   6
#define F_BUTTON 8
#define F_CHKBOX 9
#define F_3STBOX 10
#define F_RADIO  11
#define F_DOLLAR  16
#define F_CONTROL 17

/* field options and flags */

#define FLD_REQUIRED	0x00000001L
#define FLD_MUSTFILL    0x00000002L
#define FLD_INITBLANK   0x00000004L
#define FLD_LASTFLD		0x00000008L
#define FLD_MODIFIED    0x00000010L
#define FLD_FIXEDLEN    0x00000020L
#define FLD_REGION      0x00000040L
#define FLD_READONLY    0x00000080L
#define FLD_LSTREGFLD   0x00000100L
#define FLD_STRPZEROS   0x00000200L
#define FLD_SKIP        0x00000400L
#define FLD_NULL3STATE  0x00000800L
#define FLD_STATIC      0x00001000L
#define FLD_MULTILINE   0x00002000L
#define FLD_COMBO		0x00004000L
#define FLD_RADIOCLR	0x00008000L
#define FLD_UNREADABLE  0x00010000L
#define FLD_ALLOCFLDBUF 0x00020000L
#define FLD_NUMERIC		0x00040000L
#define FLD_VALIDATE	0x00080000L
#define FLD_FIELDTYPE	0x00100000L
#define FLD_EDITMASK	0x00200000L
#define FLD_MASKCHARS	0x00400000L
#define FLD_ALLOCFLD	0x00800000L
#define FLD_ATTRINTF	0x01000000L
#define FLD_LONGBUFFER	0x02000000L

#define REG_ENTEREXIT	0x00000001L
#define REG_ENTERENDF   0x00000002L
#define REG_NOCLEAR     0x00000004L
#define REG_MODIFIED    0x00000008L
#define REG_NODELETE    0x00000010L
#define REG_CELLBOX     0x00000020L

/* form option and status flags */

#define FM_NOESC		0x00000002L
#define FM_MODAL		0x00000004L
#define FM_MODIFIED     0x00000010L
#define FM_PGUP			0x00000020L
#define FM_PGDN			0x00000040L
#define FM_PAGING		(FM_PGUP + FM_PGDN)
#define FM_BLANK		0x00000080L
#define FM_ENDFLDP      0x00000100L 
#define FM_ENTEREXIT    0x00000200L
#define FM_NOAUTOTAB	0x00000400L

/* standard form actions (buttons) */

#define AC_FORMQUIT   	0
#define AC_FORMEXIT		1
#define AC_FORMHELP     2
#define AC_FORMUP		3
#define AC_FORMDOWN		4
#define AC_FORMSET      5
#define STDBUTTONS  	5

union fr {
	LONG  r_long;		/* range values are long integers */
	char  r_char; 		/*   "           "  characters */
	SHORT r_int;  		/*	 "			 "	integers */
  	char *r_string;		/*   "           "  strings or dates */
	double r_float;		/*   "           "  floating point numbers */
};

#define FORM_EXIT (WM_USER + 0)			/* PMForm Messages */
#define FORM_QUIT (WM_USER + 1)
#define LN_DESELECT 32001

#define DFIELD struct dfield
#define DFIELDPTR struct dfield *
#define DFORM  struct dform
#define DFORMPTR struct dform *
#define DREGION struct dregion
#define DREGIONPTR struct dregion *

#define REG_INSERT 0
#define REG_MODIFY 1
#define REG_DELETE 2
#define DIR_PREV   0
#define DIR_NEXT   1
#define DIR_UNKNOWN 2
#define MAX_REGION_FIELDS  25
#define FID_NULL  -1
#define NODISP    -1
#define NOPROC    -2
#define DISPONLY  -2
#define NULLMSG 0
#define NULLFP ((int(*)())0)
#define NULLFLDP ((DFIELDPTR)0)
#define NULLR (0L)
#define NULLBUTN { 0, 0, 0, 0 }
#define NULLHV  -1
#define NULLPM  ((MPARAM)(LONG)0)
#define FS	'@'
#define ALL_FIELDS -1
#define NULL_TOKEN -1
#define LIT_CURRENT -1

struct dform;

struct dfield 
{
	SHORT fldtype;		/* data field type */
	SHORT width;		/* number of characters in the ascii datafield */
	SHORT win_id;		/* id of the control window for this field */
	void *datap;	  	/* pointer to the object containing the data */
	char *picp;			/* pointer to the format definition string */
	SHORT (* _Optlink begfp)(DFORMPTR, DFIELDPTR);          /* pointer to the begin field function */
	SHORT (* _Optlink endfp)(DFORMPTR, DFIELDPTR);	 	  	/* pointer to the end field function */
	SHORT (* _Optlink valfp)(DFORMPTR, DFIELDPTR, char *);  /* pointer to a user validation function */
	union fr rangel;	/* lowest acceptable value */
	union fr rangeh;	/* highest acceptable value */
	LONG  flags;	  	/* flags and field options */
 	SHORT fldblank;		/* set to TRUE if field has not been specified */
	PFNWP olistp;		/* pointer to original window procedure for buttons */
	void *fldobjp;		/* pointer to the field object */
	void *maskp;		/* pointer to the edit mask object */
	char *attrName;		/* data attribute name */
};

struct regfld 
{
	SHORT width;		/* number of units wide */
	SHORT fldid;		/* id of the associated I/O data field */
	SHORT token_id;     /* id (position) of the token in the item text  */
};

struct dregion 
{
	SHORT win_id;		/* window id of the listbox */
	SHORT status;
	SHORT (* _Optlink begrp)(DFORMPTR, DREGIONPTR);							  /* pointer to the begin region function */
	SHORT (* _Optlink entrp)(DFORMPTR, DREGIONPTR);							  /* pointer to the begin region function */
	SHORT (* _Optlink endrp)(DFORMPTR, DREGIONPTR, char *, char **, SHORT);     /* pointer to the end or save region function */
	SHORT (* _Optlink qselrp)(DFORMPTR, DREGIONPTR, SHORT);
	LONG  flags;		/* flags and region options */
	SHORT indent;		/* units to indent the first column */
	SHORT regionflds;
	SHORT item;
	SHORT index;
	struct regfld rflds[MAX_REGION_FIELDS];
	SHORT tokens;       /* number of tokens contained in list string */
    SHORT nSubCols;		/* total number of sub-column definitions */
    PSUBCOLDEF pTabs;	/* pointer to sub-column def structures */
    PATTRIBDEF pAttr;  	/* pointer to special attribute definitions */
	void  *regobjp;		/* pointer to the region object */
	PFNWP olistp;		/* pointer to original window procedure for list box */
};

struct dform 
{
	SHORT dialog_id; 				  /* id of the dialog box window */
	SHORT (* _Optlink begfmp)(DFORMPTR);  /* address of the begin form function */
	SHORT (* _Optlink endfmp)(DFORMPTR);  /* address of the end form function */
	SHORT (* _Optlink valfmp)(DFORMPTR);  /* address of the form validation function */
	SHORT (* _Optlink canfmp)(DFORMPTR);  /* address of the form cancel function */
	DFIELDPTR fldp; 				  /* pointer to the data field array */
	SHORT dfields;			/* count of data fields in the array */
	DREGIONPTR regp;		/* pointer to the data regions array */
	SHORT dregions;			/* count of data regions in the array */
	SHORT msgwin_id;		/* id of the window to display error messages */
	LONG  flags;        	/* form option flags */
	SHORT stdbutt[STDBUTTONS];   /* id's of standard buttons */
	SHORT filter;			/* set to TRUE for input character filtering */
	SHORT formdir;			/* direction of last field exit */
	DFIELDPTR cfldp;		/* pointer to the current field. */
	HWND hwndFM;			/* handle of the form window */
	void *fmobjp;			/* pointer to the form object */
	PFNWP pwinProc;			/* pointer to PM's window procedure */
	LONG maxfields;			/* maximum number of fields - specified when created */
	LONG maxregs;			/* maximum number of regions - specified when created */
};

struct mle_buffer			/* data transfer block for multi-line edit fields */
{
	unsigned SHORT len;	 	/* size of the data block */
	char  data[2];			/* 1st two characters of the block itself */
};

/****** structures and constants for the Database Manager *******/

struct hostvars 
{
	void *hv_datap;		/* address of data buffer */
	SHORT *hv_nullflag; /* address of the null flag for fetches */
};

typedef struct hostvars *pHostVars;

extern SHORT VALERR;

/* Function Macros */

#define PMFormCurrRegItem(r) (r->status == REG_MODIFY? r->item: -1)
#define PMFormSetBlank(f, s) (f->fldblank = s)
#define PMFormIsRegModified(r) (r->flags & REG_MODIFIED) 


/* Function Prototypes: */
#ifndef CALLBACK
#define CALLBACK EXPENTRY /* v1.3 backward compatiblity */
#endif

SHORT cdecl PMFormInstall(HAB hab, HMQ hmq);

#ifdef BUILDLIB

char * cdecl PMFormExtractColumnText(char *pzText, char *pBuf, SHORT nColumn, SHORT fTags);
char * cdecl PMFormSetColumnText(char *pzText, char *pBuf, SHORT nColumn);
SHORT  cdecl PMFormPrep(HWND, DFORMPTR);
char * cdecl PMFormDataToString(DFIELDPTR);
SHORT  cdecl PMFormValChar(DFIELDPTR, char *);
DFIELDPTR cdecl PMFormIField(DFORMPTR, SHORT);
DREGIONPTR cdecl PMFormIRegion(DFORMPTR, SHORT);
BOOL EXPENTRY PMFormProcMsg(HAB, PQMSG, USHORT);
MRESULT EXPENTRY PMFormDefDlgProc (HWND, ULONG, MPARAM, MPARAM);
DREGIONPTR cdecl PMFormFldReg(DFORMPTR, DFIELDPTR);
extern BOOL cdecl PMFormProcExit(DFORMPTR fp, SHORT ac, SHORT nextform);
char * cdecl PMFormBuildItemText(DFORMPTR, DREGIONPTR, char *);
MRESULT EXPENTRY PMFormDlgProc (HWND, ULONG, MPARAM, MPARAM);
char * cdecl PMFormQueryListItem(DFORMPTR, DREGIONPTR, SHORT, SHORT, char *);
BOOL cdecl PMFormSetField(DFORMPTR fp, DFIELDPTR fldp, char *cp);
BOOL cdecl PMFormSetIField(DFORMPTR fp, USHORT idWin, char *pText); 
BOOL cdecl PMFormQueryField(DFORMPTR fp, DFIELDPTR fldp, SHORT len, char *cp);
BOOL cdecl PMFormQueryIField(DFORMPTR fp, USHORT idWin, SHORT len, char *cp);
BOOL cdecl PMFormSetButtonFld(DFORMPTR fp, DFIELDPTR fldp, SHORT fCheck);
SHORT cdecl PMFormQueryButtonFld(DFORMPTR fp, DFIELDPTR fldp);
SHORT cdecl PMFormEnableField(DFORMPTR fp, DFIELDPTR fldp, BOOL fEnable);
SHORT cdecl PMFormNextLogField(DFORMPTR fp);
SHORT cdecl PMFormClearFields(DFORMPTR fp, SHORT count);
SHORT cdecl PMFormClearVars(DFORMPTR fp);
void cdecl PMFormSetFocus(DFORMPTR fp);
BOOL cdecl PMFormConvert(DFORMPTR fp);
void cdecl PMFormReadHV(DFORMPTR fp, SHORT table_id);
void cdecl PMFormWriteHV(DFORMPTR fp, SHORT table_id);
void cdecl PMFormForceExit(DFORMPTR fp, SHORT ac, SHORT nextform);
BOOL cdecl PMFormProcQuit(DFORMPTR fp);
void cdecl PMFormSetPaging(DFORMPTR fp, LONG type, BOOL fselect);
void cdecl PMFormSetFormExit(DFORMPTR fp, BOOL fselect);
void cdecl PMFormSetFormHelp(DFORMPTR fp, BOOL fselect);
void cdecl PMFormSetFormQuit(DFORMPTR fp, BOOL fselect);
BOOL cdecl PMFormChangeField(DFORMPTR fp, DFIELDPTR fldp);
void cdecl PMFormClearFieldBuf(DFIELDPTR fldp);
void cdecl PMFormFldModified(DFORMPTR fp, DFIELDPTR fldp);
SHORT cdecl PMFormReadHVField(DFIELDPTR fldp);
SHORT cdecl PMFormWriteHVField(DFIELDPTR fldp);
BOOL cdecl PMFormConvertField(DFORMPTR fp, DFIELDPTR fldp);
char * cdecl PMFormDataToString(DFIELDPTR fldp);
BOOL cdecl PMFormConvertItemText(DFORMPTR fp, DREGIONPTR regp, SHORT item);
void cdecl PMFormClrRegModified(DFORMPTR fp, DREGIONPTR regp);
SHORT cdecl PMFormClearRegion(DFORMPTR fp, DREGIONPTR regp);

BOOL cdecl PMFormAddChoiceItem(DFORMPTR fp, DFIELDPTR fldp, char *itemtext, SHORT sort);
BOOL cdecl PMFormAddIChoiceItem(DFORMPTR fp, SHORT idWin, char *itemtext, SHORT sort);
SHORT cdecl PMFormDrawListItem(DREGIONPTR regp, USHORT id, POWNERITEM op);
SHORT cdecl PMFormSplitText(char *datap, char **tp, SHORT fields);
SHORT cdecl PMFormClearRegion(DFORMPTR fp, DREGIONPTR regp);
SHORT cdecl PMFormStdButton(DFORMPTR fp, SHORT win_id);
void cdecl PMFormClearError(DFORMPTR fp);
SHORT cdecl PMFormEndField(DFORMPTR fp, SHORT dir);
void cdecl MeasureFontMetrics(HWND hwnd);
BOOL cdecl PMFormEndRegion(DFORMPTR fp, DREGIONPTR regp, SHORT noproc);
BOOL cdecl PMFormValField(DFIELDPTR fldp, char *datap);
void cdecl PMFormValError(DFORMPTR fp);
BOOL cdecl PMFormFormatField(DFORMPTR fp, DFIELDPTR fldp, char *ptext);
BOOL cdecl PMFormValReq(DFIELDPTR fldp, char *datap);
BOOL cdecl PMFormStringToData(DFIELDPTR fldp, char *fldbuf);
BOOL cdecl PMFormCheckRange(DFIELDPTR fldp);
BOOL cdecl PMFormMessage(DFORMPTR fp, char *msg);
BOOL cdecl PMFormUpdateField(DFORMPTR fp, DFIELDPTR fldp);

#endif // BUILDLIB

#if defined(__cplusplus)
    }
#endif

#endif // __PMFORMS_H
