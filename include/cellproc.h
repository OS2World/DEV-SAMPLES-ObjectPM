/*  VCS_ID
 *  $Filename:   cellproc.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.3  $
 *  $Date:   10 Dec 1991 17:11:26  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#ifndef __CELLPROC_H
#define __CELLPROC_H

SHORT cdecl CellDrawItem(HPS hps, PCELLBOX pCI, PCELLITEM pCell, PRECTL prclItem, 
	PPOINTL dLimits, LONG *lclid, BOOL title);
VOID  cdecl CellEraseRect(HPS hps, PRECTL prclItem, LONG clr);
SHORT cdecl CellInvalidateItem(PCELLBOX pCI, PCELLITEM pCellItem);
SHORT cdecl CellInvalidate(PCELLBOX pCI, PCELL pCell);
SHORT cdecl CellRectangleOf(PCELLBOX pCI, PCELL pCell, PRECTL prcl);
PCELLITEM cdecl CellFindOccupant(PCELLBOX pCI, PCELL pCell);
SHORT cdecl CellOfItem(PCELLBOX pCI, PCELLITEM pCellItem, PCELL pCell);
SHORT cdecl CellQuerySelState(PCELLBOX pCI, PCELL pCell);
SHORT cdecl CellHitTest(register PCELLBOX pCI, PCELL pCell, SHORT x, SHORT y);
SHORT cdecl CellItemSetFlags(PCELLITEM pCellItem, USHORT fsData, USHORT fsMask);
SHORT cdecl CellItemSetFlagsAll(PCELLBOX pCI, USHORT fsData, USHORT fsMask);
SHORT cdecl CellItemNumber(PCELLBOX pCI, PCELL pCell);
SHORT cdecl CellOfItemNumber(PCELLBOX pCI, SHORT item, PCELL pCell);
SHORT cdecl CellFindHandle(PCELLBOX pCI, ULONG handle);
VOID  cdecl CellInvalidateThru(PCELLBOX pCI, PCELLITEM pCellItem);
void  cdecl SendMsgToOwner(HWND hwnd, SHORT usNotifyCode, ULONG usData);
void  cdecl SetCellOne(PCELLBOX pCI, SHORT i);
void  cdecl CalcHorzScrollVals(CELLBOX *pCI, SHORT fRePos);
void  cdecl CalcVertScrollVals(CELLBOX *pCI, SHORT fRePos);
SHORT cdecl ScrollCellWindow(CELLBOX *pCI, HWND hwnd, SHORT dx, SHORT dy);
SHORT cdecl ItemIndex(PCELLBOX pCI, PCELLITEM pCell);
void  cdecl SetCellCounts(CELLBOX *pCI);
SHORT cdecl CellInvalidateCellColumn( CELLBOX *pCB, USHORT row, USHORT column );
SHORT cdecl CellColumnRectangleOf( CELLBOX *pCB, USHORT row, USHORT col, RECTL *prcl );
SHORT cdecl CellColumnNumber(PCELLBOX pCI, short xpos, short grp);
void  cdecl CellBoxEmphasize(PCELLBOX pCI, BOOL targ, BOOL set);

#endif // __CELLPROC_H
