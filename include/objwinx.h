/*  VCS_ID
 *  $Filename:   objwinx.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   10 Dec 1991 17:57:58  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef _OBJPMWINX_H
#define _OBJPMWINX_H

#ifdef BUILDLIB
VOID  EXPENTRY WinxConvertDialogUnits(PPOINTL, unsigned);
BOOL  EXPENTRY WinxRegisterCellClass(HAB hab);
VOID  EXPENTRY WinxDisplayWindow(HWND hwnd);
HWND  EXPENTRY WinxCreateCellWindow(HWND hwndParent, ULONG fStyle, SHORT x, SHORT y, SHORT cx,
            SHORT cy, HWND hwndOwner, USHORT id, USHORT maxcols, USHORT maxattrs);
BOOL  EXPENTRY WinxPtInRect(PRECTL prcl, PPOINTL pptl);
BOOL  EXPENTRY WinxPtsInRect(PRECTL prcl, PPOINTL pptl, unsigned nPts);
SHORT EXPENTRY WinxSplitCellText(CHAR *datap, CHAR **tp, SHORT fields, char tagchar);
PCHAR EXPENTRY WinxExtractColumnText(PCHAR pzText, PCHAR pBuf, SHORT nColumn, SHORT fTags, char tagchar);
VOID* EXPENTRY WinxSubclassWindow(HWND hwnd, VOID *pfnwp);
VOID  EXPENTRY StdFaceInfo(SHORT stdFont, char *name, SHORT *size, LONG *match);
BOOL  EXPENTRY WinxChangePresColor(HWND hwnd, ULONG attr, LONG c, BOOL fRGB);
BOOL  EXPENTRY WinxChangePresFont(HWND hwnd, USHORT f);
BOOL  EXPENTRY WinxIsWindowClass(PSZ windowClass, PSZ classname);
char* EXPENTRY WinxSetColumnText( char *pzText, char *pBuf, SHORT nColumn, BOOL repltags, char tagchar);
#endif

#endif // _OBJPMWINX_H
