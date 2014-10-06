/*  VCS_ID
 *  $Filename:   containr.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
//+*****************************************************************************
//
//	VERSION:  $Revision$
//	          $Date$
//
//	MODULE:   containr.hpp
//	AUTHOR:   Mike Flis, John Pompeii
//	FACILITY: WindowManager library
//
//	Copyright (c)	1995 by Secant Technologies
//
//
//	DESCRIPTION:
//
//		This module contains the class definitions, enumerations, and 
//		constants used for the OS/2 container control. 
//
//-*****************************************************************************

#ifndef __CONTAINR_HPP
#define __CONTAINR_HPP

#define CfaLeft			 0x0001
#define CfaRight		 0x0002
#define CfaCenter		 0x0004
#define CfaTop			 0x0008
#define CfaVCenter		 0x0010
#define CfaBottom		 0x0020
#define CfaInvisible	 0x0040
#define CfaVertSeparator 0x0200
#define CfaHorzSeparator 0x0400
#define CfaReadOnly		 0x8000
#define CfaNativeType	 0x4000
#define CfaFieldType	 0x2000

#define CtaLeft		0x0001
#define CtaRight	0x0002
#define CtaCenter	0x0004
#define CtaTop		0x0008
#define CtaVCenter	0x0010
#define CtaBottom	0x0020
#define CtaReadOnly	0x8000


#ifndef CV_TEXT
struct _FIELDINFO;
typedef _FIELDINFO FIELDINFO;
struct _RECORDCORE;
typedef _RECORDCORE RECORDCORE;
struct _CNRINFO;
typedef _CNRINFO CNRINFO;
#endif

typedef void *(*CntrFldFnp)(wContainerItem*);

class _EXPORT_ wContainerField
{
	private:
		wContainer	*cntr;
		FIELDINFO	*fld;
		ushort 		dataType;
		short		offset;
		CntrFldFnp  accFn, mutFn;
		bString 	fmt;

		void SetupBase(wContainer *p, ushort dtype, ushort attr, ulong width);
		void UpdateMemberData(wContainerItem*, const char *);
		void UpdateCoreData(wContainerItem*);

		friend class wContainerFieldList;
		friend class wContainer;
		friend class wContainerItem;

	public:
		wContainerField(wContainer *p, ushort dtype, const char *heading, ushort attr, ulong width = 0);
		wContainerField(wContainer *p, ushort dtype, wBitmap *heading, ushort attr, ulong width = 0);
		wContainerField(wContainer *p, const char *heading, ushort attr, ulong width = 0);
		wContainerField(wContainer *p, wBitmap *heading, ushort attr, ulong width = 0);
	   ~wContainerField();												

		void SetFieldAttribute(ushort attr, bool fSet);								
		void SetTitleAttribute(ushort attr, bool fSet);
		void SetAccessFns(CntrFldFnp accfn, CntrFldFnp mutfn = NULL);
		void SetDataFormat(const char *f);
		void SetDataType(ushort type);		
		void SetTitle(const char *t);											
		void SetTitle(wBitmap *bmp);
		void SetWidth(ulong w);											

		ushort GetFieldAttributes();								
		ushort GetTitleAttributes();
		bString		  GetDataFormat();
		ushort		  GetDataType();		
		ulong 		  GetWidth();
};

class _EXPORT_ wContainerFieldList : private tDList<wContainerField>
{
private:
	wContainer	*cntr;
	short		maxoffset;
	bool		insertInvalidate;
	
	void UpdateCoreData(wContainerItem*);

	friend class wContainerItemCltn;
	friend class wContainerItem;

public:
    typedef tDList<wContainerField> ConList;
    typedef tIterator<wContainerField> ConIter;

	wContainerFieldList(wContainer *p);								
	~wContainerFieldList();
										
	bool 	Insert(const wContainerField *p);
	bool	InsertAtHead(const wContainerField *p);
	bool	InsertAfter(const wContainerField *p, wContainerField *ref);			
	void 	SetInvalidateOnInsert(bool state=TRUE) { insertInvalidate = state; }

	wContainerField *Remove(ConIter *it = NULL, bool invalidate=TRUE);
	bool	Remove(wContainerField *fldp, bool invalidate=TRUE);
	bool	Invalidate();
	short	MaxSize() { return maxoffset; }

	bool    First( bIterator* it=NULL ) { return ConList::First(it); }
	bool    Last( bIterator* it=NULL )  { return ConList::Last(it); }
	bool    Next( bIterator* it=NULL )  { return ConList::Next(it); }
	bool    Prev( bIterator* it=NULL )  { return ConList::Prev(it); }
	wContainerField* Current( ConIter* it=NULL ) { return ConList::Current(it); }

	ulong   Entries() const                 { return ConList::Entries(); }
	wContainerField*  Subscript( ulong n )  { return ConList::Subscript(n); }
	wContainerField*  operator*()           { return ConList::Current(); }
	wContainerField*  operator()()          { return ConList::Current(); }
	wContainerField*  operator[]( ulong n ) { return ConList::Subscript(n); }

	wContainerField*  Search( const wContainerField* key, CompareFunc f=NULL, ConIter* it=NULL )
                                        { return ConList::Search(key, f, it); }
};

/*****************************************************************************
 *
 * Container Items
 *
 *****************************************************************************/

enum wCntrUpdateOpt
{
	CuReposition,
	CuNoReposition,
	CuTextChanged
};

#define InUseEmph			0x00000008L
#define SelectedEmph		0x00000001L
#define TargetEmph			0x00000002L
#define HighlightEmph		0x00000004L
#define SourceEmph			0x00004000L

#define CcIcon				0x0800
#define CcText				0x1000
#define CcTreeIcon			0x0400

class _EXPORT_ wContainerItem : public wWorkplaceObject
{
	private:
		friend class wContainer;
		friend class wContainerItemCltn;
		friend class wContainerField;
		friend class wContainerFieldList;
		friend class tDList<wContainerItem>;

		void *recp;
		wContainerItemCltn *recs;
		ushort helpId;

		RECORDCORE *GetRC();
		void SetInserted(bool fInserted);

	public:
		wContainerItem(wContainer *p, const char *text);
	   ~wContainerItem();

	    bool IsColapsed();
		bool IsExpanded();
		bool IsSelected();
		bool IsInUse();
		bool IsCursored();
		bool IsReadOnly();
		bool IsVisible();
		bool IsInserted();
		bool IsMini()			{ return flags & MiniRecordCore; }

		bool SetEmphasis(ushort emph, bool fSet);
		void SetReadOnly(bool fSet = TRUE);
	   	void Hide();
		void Show();
	   	bool Expand();
		bool Colapse();
	   
		wContainer *GetContainer();
		bString GetIconViewText();
		bString GetTextViewText();
		bString GetNameViewText();
		bString GetTreeViewText();

		bool    SetIconViewText(const char *txt);
		bool    SetTextViewText(const char *txt);
		bool    SetNameViewText(const char *txt);
		bool    SetTreeViewText(const char *txt);
		bool    SetTextAll(const char *txt);

		wPointl	GetPosition();
		bool    ChangePosition(wPointl pos);
		wContainerItemCltn *GetChildItems();					

		bool    SetImage(wIcon *p); 							
		bool    SetMiniImage(wIcon *p); 						
		bool    SetImage(wBitmap *p); 							
		bool    SetMiniImage(wBitmap *p);						

		bool    SetTreeNameImage(wIcon *expanded, wIcon *collapsed);
		bool    SetTreeNameImage(wBitmap *expanded, wBitmap *collapsed);
		bool    Invalidate(wCntrUpdateOpt opt = CuNoReposition, bool fErase = FALSE);		
		wRectl  GetRectangle(ushort extent, bool fRightWindow = FALSE);
		bool    EraseItem();
		ushort  GetFieldData();
		bool    OpenEdit(wContainerField *fld);
		bool 	CloseEdit();
		
		void    SetDragCapabilities(ushort caps);
		bool    GetItemsToDrag(wWorkplaceObjectList *wpol, wPointl ppos);

		bool Emphasize(bool emph, bool target);
};


/*****************************************************************************
 *
 * ContainerItem Collection
 *
 *****************************************************************************/

typedef tDList<wContainerItem> wContainerItemList;

class _EXPORT_ wContainerItemCltn : public bCltn
{
	private:
		bCltn           *cltn;
		wContainer		*cntr;
		wContainerItem  *treeparent;
		bool			insertInvalidate;

		bool DoInsert(wContainerItem *p, RECORDCORE *order);
		wContainerItem	*DoSearch(ushort emph, RECORDCORE *order);
		wContainerItem	*DoSearch(const char *str, bool fCaseSen, bool fPrefix,
			RECORDCORE *order);

		void *getCurrent( bIterator *it=NULL ) { return cltn->Current(it); }
    	void *getSubscript( ulong n )	{ return cltn->Subscript(n); }
//		void *getSearch( const void *key, CompareFunc f=NULL, bIterator *it=NULL )
//			{ return cltn->Search(key, f, it); }

	public:
		wContainerItemCltn(wContainer *p, bCltn *cl = NULL, 
			wContainerItem *parent = NULL);
	   ~wContainerItemCltn();								   
	   
		bool  Insert(wContainerItem *p);
		bool  InsertAtHead(wContainerItem *p);
		bool  InsertAfter(wContainerItem *p, wContainerItem *ref);			
		void  SetInvalidateOnInsert(bool state=TRUE) { insertInvalidate=state; }

		bool  				Remove(wContainerItem *p);
		wContainerItem     *Remove(bIterator *it = NULL);
		wContainerItem     *GetFirstItemWithEmphasis(ushort emph);
		wContainerItemList *GetItemsWithEmphasis(ushort emph);
		ulong				GetItemCountWithEmphasis(ushort emph);
		wContainerItem     *GetFirstItemMatchingString(const char *str, bool fCaseSen = TRUE, bool fPrefix = FALSE);
		wContainerItemList *GetItemsMatchingString(const char *str, bool fCaseSen = TRUE, bool fPrefix = FALSE);

		bool  IsEmpty()			{ return cltn->IsEmpty(); }
		bool  IsNotEmpty()		{ return cltn->IsNotEmpty(); }
		ulong Entries() const   { return cltn->Entries(); }
		bCltn *GetCollection()	{ return cltn; }
		bool  SetCollection(bCltn *cl);

		bool  First( bIterator *it =NULL )	{ return cltn->First(it); }
		bool  Last( bIterator *it =NULL )	{ return cltn->Last(it); }
		bool  Next( bIterator *it =NULL )	{ return cltn->Next(it); }
		bool  Prev( bIterator *it =NULL )	{ return cltn->Prev(it); }

		bool  operator++( int )	            { return cltn->Next(); }
		bool  operator--( int )	            { return cltn->Prev();	 }

		bool  Find( const void *item, bIterator *it=NULL ) { return cltn->Find(item,it); }
		bool  Insert( const void *p ) { return cltn->Insert(p); }
    	void  Clear(); 		  
		bool  Invalidate(wCntrUpdateOpt flags=CuReposition, bool fErase=FALSE);
};


/*****************************************************************************
 *
 * wContainer
 *
 *****************************************************************************/

// container styles

#define CsExtendedSelect	  0x00000001L
#define CsMultipleSelect	  0x00000002L
#define CsSingleSelect		  0x00000004L
#define CsAutoPosition		  0x00000008L
#define CsVerifyPointers	  0x00000010L
#define CsReadOnly			  0x00000020L
#define CsMiniRecords		  0x00000040L

enum wCntrView
{
 	IconView		= 0x00000004L,
	NameView		= 0x00000002L,
	TextView		= 0x00000001L,
	DetailsView		= 0x00000008L
};

enum wCntrViewMod
{
	ViewStd			= 0x00000000L,
	FlowView		= 0x00000010L,
	TreeView		= 0x00000040L
};

#define CaDrawIcon			  0x00040000L
#define CaDrawBitmap		  0x00020000L
#define CaOrderedTargetEmph	  0x00010000L
#define CaMixedTargetEmph	  0x00200000L
#define CaTreeLine			  0x00400000L
#define CaDetailsViewTitles   0x00008000L
#define CaSortItems			  0x00000001L

enum wCntrTitleJust
{
	CtLeft	 = 0x0800,
	CtRight  = 0x1000,
	CtCenter = 0x2000
};

#define CtTitleReadOnly		  0x00080000L
#define CtTitleSeparator	  0x00000400L

#define CtmDefault (-1)

enum wCntrWind
{
	CwLeft  = 4,
	CwRight = 8
};

#define CdDeltaTop         0x0001       /* Industrial - top delta   */
#define CdDeltaBottom      0x0002       /* Industrial - bottom delta*/
#define CdDeltaHome        0x0004       /* Industrial - top of list */
#define CdDeltaEnd         0x0008       /* Industrial - end of list */

#define CiLeftColTitleWin     0x7FF0   /* column title (left)       */
#define CiRightColTitleWin    0x7FF1   /* right column title        */
#define CiCntrTitleWin        0x7FF5   /* Container title window    */
#define CiRightScroll         0x7FF4   /* right horz scroll bar     */
#define CiLeftDetailsWin      0x7FF7   /* Left Details View window  */
#define CiRightDetailsWin     0x7FF8   /* Right Details View window */
				  
class _EXPORT_ wContainerEnterMsg : public wControlMsg
{
	public:
		wContainerItem	*Item();
		bool			fKey();
};

class _EXPORT_ wContainerEmphasisMsg : public wControlMsg
{
	public:
		wContainerItem	*Item();
		ulong			Emphasis();
};

class _EXPORT_ wContainerItemMsg	: public wControlMsg
{
	public:
		wContainerItem	*Item();
};

class _EXPORT_ wContainerEditMsg : public wControlMsg
{
	public:
		wContainerItem	*Item();
		wContainerField	*Field();
		bString			Text();
		ulong			ID();
		ulong			NewSize();
};

class _EXPORT_ wContainer : public wControlWindow
{
	private:
		wContainerItemCltn	 *recs;
		wContainerFieldList	 *flds;

		void	GetInfo(CNRINFO *i);
		bool	SetInfo(CNRINFO *i, ulong flags);
		PFNWP 	oldproc;

		friend  bool FilterFn(RECORDCORE *p, void *user);

	public:
		wContainer(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style);
		wContainer(wWindow *parent, ushort winId);
	   ~wContainer();

		bool IsMini();

	    // attribute set/get methods
 
		wContainerItemCltn	*GetItemCltn() 		{ return recs; }				
		wContainerFieldList	*GetFieldList()  	{ return flds; }				

		bool SetView(ulong v, bool fMiniImage = FALSE);
		bool SetAttributes(ulong attr, bool fSet = TRUE);
		bool SetTitle(const char *title, wCntrTitleJust just = CtCenter, ulong opts = CtTitleReadOnly | CtTitleSeparator);
		bool SetSplitBar(long pos, wContainerField *rightMostCol);
		bool SetWorkspaceOrigin(wPointl p);
		bool SetDelta(ulong d);

		bool SetImageSize(wDimension sz);
		bool SetTreeImageSize(wDimension sz);
		bool SetTreeImages(wIcon *expanded, wIcon *collapsed);
		bool SetTreeImages(wBitmap *expanded, wBitmap *collapsed);

		bool SetTreeLineSpacing(long n);
		bool SetTreeLineWidth(long n);
		bool SetTreeIndent(long n);

		ulong	   GetView();
		ulong	   GetAttributes();
		bString    GetTitle();
		long	   GetSplitBarPosition();
		wPointl	   GetWorkspaceOrigin();	
		ulong	   GetDelta();
		ulong	   GetItemCount()	{ return recs->Entries(); }
		ulong	   GetColumnCount()	{ return flds->Entries(); }
		wContainerField *GetSplitBarField();

		wDimension GetImageSize();
		wDimension GetTreeImageSize();
		long	   GetTreeLineSpacing();
		long       GetTreeLineWidth();
		long	   GetTreeIndent();
		wRectl     GetViewportRectl(bool relOrigin=FALSE, bool rightWindow=FALSE);

		// passthru methods for adding/removing/querying items 
		// to and from top level cltn

		bool   Insert(wContainerItem *p);
		bool   InsertAtHead(wContainerItem *p);
		bool   InsertAfter(wContainerItem *p, wContainerItem *ref);			

		bool   Remove(wContainerItem *p);
		wContainerItem     *Remove(bIterator *it = NULL);
		wContainerItem     *GetFirstItemWithEmphasis(ushort emph);
		wContainerItemList *GetItemsWithEmphasis(ushort emph);
		ulong				GetItemCountWithEmphasis(ushort emph);
		wContainerItem     *GetFirstItemMatchingString(const char *str, bool fCaseSen = TRUE, bool fPrefix = FALSE);
		wContainerItemList *GetItemsMatchingString(const char *str, bool fCaseSen = TRUE, bool fPrefix = FALSE);

		// overloaded update methods-changes the invalidate collection flag too

		void	EnableUpdate(bool enable=TRUE);
		void	DisableUpdate();

		// Action methods

		bool   Arrange();
		bool   FilterItems(void *user);
		bool   ShowAllItems();
		bool   ScrollContainer(ushort dir, long incr);
		bool   ScrollSplitWindow(wCntrWind win, long incr);
		bool   InvalidateItems(wCntrUpdateOpt opt = CuNoReposition, bool fErase = FALSE);		
		bool   InvalidateColumns();
		
		wContainerItemList *GetItemsInRectl(wRectl r, bool fComplete, bool fZorder);

		// callbacks and notifier methods

		virtual bool  FilterCompare(wContainerItem *i, void *param);
		
		long	Dispatch(wMessage m);
		virtual void FocusGained(wControlMsg m);
		virtual void FocusLost(wControlMsg m);
		virtual void Enter(wContainerEnterMsg m);
		virtual void ItemHelp(wControlMsg m);
		virtual void Emphasis(wContainerEmphasisMsg m);
		virtual void Scroll(wControlMsg m, ushort direction, long amt, bool rightWindow);
		virtual void Delta(wControlMsg m, ulong delta);
		virtual void CollapseTree(wContainerItemMsg m);
		virtual void ExpandTree(wContainerItemMsg m);
		virtual void ContextMenu(wContainerItemMsg m);
		virtual void BeginEdit(wContainerEditMsg m);
		virtual void EndEdit(wContainerEditMsg m);
		virtual bool ReallocString(wContainerEditMsg m);

		PFNWP	OriginalProc() { return oldproc; }
};

#endif // __CONTAINR_HPP
