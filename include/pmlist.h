/*  VCS_ID
 *  $Filename:   pmlist.h
 *  $Author  :   John Pompeii
 *  $Revision:   1.0  $
 *  $Date:   03 Jul 1991 12:37:40  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
/*
 * pmlist.h
 * 
 * Structure definitions for linked lists using the PM's heap functions
 */

#ifndef __PMLIST_H
#define __PMLIST_H

#define LL_FRONT  (-4)
#define LL_BACK   (-1)
#define LL_USIZE  (-1)

#ifndef NULLP
#define NULLP ((char *)0)
#endif
#ifndef NULLFP
#define NULLFP ((int(*)())0)
#endif

typedef struct _LHEADER {
	char   l_flags;
	char   l_sig;
	struct _LHEADER FAR *next_link;
	struct _LHEADER FAR *prev_link;
} LHEADER;

typedef LHEADER FAR *PLHEADER;
#define LHEADERSIZE sizeof(LHEADER)

typedef struct _LINK 
{
	PLHEADER first_link;
	PLHEADER last_link;
	short  (*cmpfn)();
	short  usrsize;
	short  listsize;
	short  flags;
} LINK;

typedef LINK FAR *PLINK;

#define WinxListItems(lp) (lp->listsize)
#define WinxListFirstItem(lp) (lp->first_link)
#define WinxListLastItem(lp) (lp->last_link)
#define WinxListNextItem(hp) (((PLHEADER)hp)->next_link)
#define WinxListPrevItem(hp) (((PLHEADER)hp)->prev_link)

PLINK    WinxListCreate(short (*cmpf)(), short usize);
void     WinxListDump(PLINK lp);
PLHEADER WinxListAddItem(PLINK lp, void *datap, short pos, short usize);
PLHEADER WinxListInsertItem(PLINK lp, PLHEADER rhd, void *datap, short usize);
void     WinxListDeleteItem(PLINK lp, PLHEADER hd);
PLHEADER WinxListSeekItem(PLINK lp, register short i);

#endif // __PMLIST_H

