/*  VCS_ID
 *  $Filename:   phbook.cpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define INCL_WIN
#include <os2.h>

#define InclControls
#define InclGraphics
#define InclForms
#define InclFiles
#define InclFixedMath
#define InclStdDialogs
#include <ObjectPM.hpp>
#include <ctype.h>
#include <stdio.h>

#include "phbook.hpp"
#include "phedit.hpp"

Define_tCMap(mNameKey, mPhoneCard)  // instantiate mPhoneCardList methods

wIcon *GetPhoneCardDetailsIcon(wContainerItem *);

/* register the name key */

bType regNameKey(
	"mNameKey",   bType::StructField, 2,
	"lastName", FIELD_OFFSET(mNameKey, lastName), 0,
	"firstName",  FIELD_OFFSET(mNameKey, firstName),  0 );


/*****************************************************************************
 * 
 * bMainThread::Start 
 *
 *****************************************************************************/

short bMainThread :: Start()
{
	PhoneBookView pb(argc, argv);
	Exec();
	return 0;
}


/*****************************************************************************
 * 
 * PhoneBook Frame Window & Container
 *
 *****************************************************************************/


PhoneBookView :: PhoneBookView(short argc, char **argv)
{
	wFrameControlList	*fcl;
	wContainerFieldList	*cfields;
	wContainerField *cfld;

	CreateWindow(OpmStdFrame);

	// set up command handlers
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, AddEntry), WM_COMMAND, MI_ADDENTRY);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, FindEntry), WM_COMMAND, MI_FINDENTRY);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, DestroyCardEditor), WmDestroyCardEditor);
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, Open), WM_COMMAND, MI_OPENFILE);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, New), WM_COMMAND, MI_NEWFILE);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, Save), WM_COMMAND, MI_SAVEFILE, MI_SAVEAS);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, UpdateCmdDescription), WM_CONTROLPOINTER);
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, ToggleFrameControls), WM_COMMAND, MI_TOGGLESTATUSBAR, MI_TOGGLETOOLBAR);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, ChangeView), WM_COMMAND, MI_SETDETAILSVIEW, MI_SETICONVIEW);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, ChangeName), WM_COMMAND, MI_SETPHONEBOOKNAME);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, OpenEntry), WM_COMMAND, MI_OPENENTRY);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, DeleteEntry), WM_COMMAND, MI_DELETEENTRY);	
	AddMessageHandler(this, EVENTMETHOD(PhoneBookView, DeleteOneEntry), WM_COMMAND, MI_DELETEONEENTRY);	

	mnu = new wMenu(this, MAINMENU);
	icon = new wIcon(ResIcon, I_PHBOOK);
	SetIcon(icon);

	// Create the container control

	cnt = new wPhoneCardContainer(this, NAMES, wPointl(0,0), wDimension(0,0), 
						 CsMiniRecords | CsExtendedSelect | CsAutoPosition | WsVisible);
	cnt->SetAttributes(CaDetailsViewTitles | CaMixedTargetEmph | CaDrawIcon);
	cnt->SetView(DetailsView);
	cnt->SetImageSize(wDimension(20,20));
	cnt->ChangeFont(Helv8);

	cnt->SetName("PhoneCardList");
	cnt->SetDragCapabilities(DragTarget);
	cnt->ExchangeMethods()->Insert( new wObjectExchange("DRM_DISCARD", DRT_UNKNOWN) );
	cnt->ExchangeMethods()->Insert( new wObjectExchange("DRM_DATAFILE", "DRF_PHONEFILE") );
	cfields = cnt->GetFieldList();

	// Setup Icon column
	cfld = new wContainerField(cnt, "Icon", CtaCenter, 0);
	cfld->SetAccessFns((CntrFldFnp)GetPhoneCardDetailsIcon);
	cfld->SetFieldAttribute(CfaCenter | CfaVertSeparator | CfaHorzSeparator, TRUE);
	cfields->Insert(cfld);

	// and the data field columns
	cfields->Insert( new wPhoneCardDataField(cnt, "Last Name", (CntrFldFnp)GetLastNameField) );
	cfields->Insert( new wPhoneCardDataField(cnt, "First Name", (CntrFldFnp)GetFirstNameField) );
	cfields->Insert( new wPhoneCardDataField(cnt, "Company", (CntrFldFnp)GetCompanyNameField) );
	cfields->Insert( new wPhoneCardDataField(cnt, "Home Phone", (CntrFldFnp)GetHomePhoneField) );
	cfields->Insert( new wPhoneCardDataField(cnt, "Work Phone", (CntrFldFnp)GetWorkPhoneField) );

	// build the custom frame controls
	fcl = FrameControls();
	fcl->Insert(toolbar = new ToolBar(this));
	fcl->Insert(stat = new StatusBar(this));
	fcl->Insert(new TitleTools(this));
	mnu->CheckItem(MI_TOGGLESTATUSBAR);
	mnu->CheckItem(MI_TOGGLETOOLBAR);

	pb = new mPhoneBook;
	fModified = FALSE;
	stat->SetNumEntries(0);

	// check if filename was supplied as an argument
	if (argc > 1)
	{
		pb->SetFilename(argv[1]);
		Open((wCommandMsg&)wMessage(WM_COMMAND, (MPARAM)MI_LOADINIT, 0));		
	}
	SetCaption();
	Show();
	ToTop();
}

PhoneBookView :: ~PhoneBookView()
{
	delete mnu;
	delete cnt;
}

void PhoneBookView :: SetCaption()
{
	bString name("Phone Book - ");
	name += pb->GetName(); 

	wFrameWindow::SetCaption(name);
	SetSwitchTitle(name);
}

long PhoneBookView :: AddEntry(wMessage)
{
	// start the editor with a new phone card object
	new wPhoneCardEditor(this, new mAppPhoneCard(NULL)); 
	return 0;
}

bool PhoneBookView :: AddNewEntry(mAppPhoneCard *card)
{
	bString name(card->GetLastName(), 45);
	name += ", ";
	name += card->GetFirstName();

	// Create the container item
	wPhoneCardItem *cntrItem = new wPhoneCardItem(cnt, name, card);

	// build the key and add the item to the phone card collection
	mPhoneCardList *cardCltn = pb->GetPhoneCards();
	mNameKey *key = new mNameKey(card->GetLastName(), card->GetFirstName());
	cardCltn->InsertAssoc(key, card);

	// determine the position of the new entry in the card collection
	// so that the container item can be inserted into the proper place
	if (card == (*cardCltn)[0])	 // first item?
		cnt->InsertAtHead(cntrItem);
	else
	{
		cardCltn->Search(key);
		cardCltn->Prev();
		cnt->InsertAfter(cntrItem, 
		     ((mAppPhoneCard *)(cardCltn->Current()))->GetContainerItem() );
	}
	stat->SetNumEntries(cardCltn->Entries());
	SetModified(TRUE);
	return TRUE;
}

bool PhoneBookView :: ModifyEntry(mAppPhoneCard *card)
{
	wPhoneCardItem *item = card->GetContainerItem();

	if (item->IsNameChanged())
	{
		// user has modified data items that make up the sort key of
		// the card collection.  As a result, we will remove the
		// card from the collection and the container, and then re-
		// insert it.

		mPhoneCardList *cardCltn = pb->GetPhoneCards();

		// set current item of the cltn to the modified item
		// and then delete it
		mNameKey *oldKey;
		cardCltn->Find(card);
		cardCltn->RemoveAssoc(&oldKey);
		delete oldKey;

		// remove and destory the container item
		cnt->Remove(item);
		delete item;
		card->SetContainerItem(NULL);

		// now, re-insert it 
		AddNewEntry(card);
	}
	else
		item->UpdateColumns();

	return TRUE;
}

bool PhoneBookView :: RemoveEntry(mAppPhoneCard *card)
{
	wPhoneCardItem *item = card->GetContainerItem();
	mPhoneCardList *cardCltn = pb->GetPhoneCards();

	// set current item of the cltn to the modified item
	// and then delete it
	mNameKey *oldKey;
	cardCltn->Find(card);
	cardCltn->RemoveAssoc(&oldKey);
	delete oldKey;

	// remove and destory the container item and card
	cnt->Remove(item);
	delete item;
	cardCltn->Remove();
	card->SetContainerItem(NULL);
	delete card;

	return TRUE;
}

void PhoneBookView :: DestroyCardEditor(wMessage m)
{
	wPhoneCardEditor *ed = (wPhoneCardEditor *)m.mp1;
	wPhoneCardItem *item = ed->GetPhoneCard()->GetContainerItem();

	if (item)	// closing a view for an existing item?
	{
		item->SetEmphasis(InUseEmph, FALSE);
		item->SetOpenView(NULL);
	}
	delete ed;
}

long PhoneBookView :: FindEntry(wCommandMsg)
{
	wFindItemForm anon(this);	// all the work is done in the form
	return 0;
}

/*
 * File handling methods
 *
 */

long PhoneBookView :: New(wCommandMsg)
{
	if (CheckCurrentPhoneBook())
	{
		wNewPhoneBookForm fm(this);
		if (fm.GetResult() == AcFormExit)
		{
			// remove and delete all items from the container
			cnt->GetItemCltn()->Clear();
			stat->SetNumEntries(0);

			// delete the phbook collection
			delete pb;
			pb = new mPhoneBook();

			pb->SetFilename(fm.GetFilename());
			pb->SetName(fm.GetName());
			SetCaption();
			fModified = TRUE;
		}
	}
	return 0;
}


long PhoneBookView :: Open(wCommandMsg m)
{
	if (CheckCurrentPhoneBook())
	{
		bString filename;

		if (m.usCmd() != MI_LOADINIT)
		{
			wStdFileOpenDialog fdlg;

			fdlg.ChangeStyle(FdaCenter | FdaHelpButton);
			fdlg.SetInitialFile("*.pb");

			if (fdlg.CreateWindow(this) != DidOK)
				return 0;
		
			// remove and delete all items from the container
			HourGlass();
			cnt->GetItemCltn()->Clear();
			stat->SetNumEntries(0);

			// delete the phbook collection
			delete pb;
			pb = new mPhoneBook();

			filename = fdlg.GetFirstFile();
		}
		else 
		{
			filename = pb->GetFilename();
			HourGlass();
		}

		bRecordFile rf(filename, MAX_PHBK_ELEMENTS, MAX_PHBK_RECSIZE);
		if (rf.Open("r"))
		{
			wMessageBox(this, "Cannot open the input file", "Read Error", 
						MbOk | MbIconExclamation | MbMoveable);

			HourGlass();
			return 0;
		}

		// Set the user-friendly name of the phone book
		pb->SetFilename(filename);
		pb->SetName(filename);
		bEAList *eaList = rf.GetEA(".LONGNAME");
		if (eaList)
		{
			// Set the name of the phone book from the .LONGNAME 
			// extended attribute.  This attribute is used by the WPS
			// to display the names of objects derived from wpFileSystem 

			if (eaList->Entries())
				pb->SetName(((*eaList)[0])->Attribute());

			delete eaList;
		}

		if (!pb->Retrieve(rf))
		{
			wMessageBox(this, "Read error encountered on the input file", "Read Error", 
						MbOk | MbIconExclamation | MbMoveable);
		}
		fModified = FALSE;

		// create and add the container items
		mPhoneCardList *cardList = pb->GetPhoneCards();
		mAppPhoneCard *card;

		DisableUpdate();
		for (cardList->First(); (card = (mAppPhoneCard *)cardList->Current()) != NULL;
				cardList->Next())
		{
			bString name(card->GetLastName(), 45);
			name += ", ";
			name += card->GetFirstName();

			cnt->Insert(new wPhoneCardItem(cnt, name, card));
		}
		EnableUpdate();
		stat->SetNumEntries(cardList->Entries());
		HourGlass();
		SetCaption();
	}
	return 0;
}

bool PhoneBookView :: CheckCurrentPhoneBook()
{
	if (IsModified())
	{
		wMessageBox mb(this, "The current phone book has been modified.  Do yo wish to save your changes?", "", 
					   MbYesNoCancel | MbIconQuestion | MbMoveable);

		if (mb.MessBoxVal() == MrCancel)
			return FALSE;

		if (mb.MessBoxVal() == MrYes)
		{
			Save((wCommandMsg&)wMessage(WM_COMMAND, (MPARAM)(short)MI_SAVEFILE, 0));
			if (IsModified())
				return FALSE;		// an error occured
		}
	}
	return TRUE;
}

long PhoneBookView :: Save(wCommandMsg m)
{
	if (m.usCmd() == MI_SAVEAS || pb->GetFilename().IsBlank())
	{
		wStdFileSaveAsDialog fdlg;

		fdlg.ChangeStyle(FdaCenter | FdaHelpButton);
		if (pb->GetFilename().IsBlank())
			fdlg.SetInitialFile("untitled.pb");
		else
			fdlg.SetInitialFile(pb->GetFilename());

		if (fdlg.CreateWindow(this) == DidOK)
			pb->SetFilename(fdlg.GetFirstFile());
		
		else return 0;			
	}
	HourGlass();
	bRecordFile rf(pb->GetFilename(), MAX_PHBK_ELEMENTS, MAX_PHBK_RECSIZE);
	if (rf.Open("w"))
	{
		wMessageBox(this, "Cannot open the output file", "Save Error", 
					MbOk | MbIconExclamation | MbMoveable);

		HourGlass();
		return 0;
	}
	if (!pb->Store(rf))
	{
		wMessageBox(this, "Write error encountered saving the phone book", "Save Error", 
					MbOk | MbIconExclamation | MbMoveable);
	}
	else 
		SetModified(FALSE);

	bString nm = pb->GetName();
	rf.SetEA(".LONGNAME", bExtAttr(EaAscii, nm.Length(), (const char *)nm) ); 
	if (rf.Error())
	{
		char buf[80];
		sprintf(buf, "Error setting extended attribute: %ld (%lx)", rf.Error(), rf.Error());
		wMessageBox(this, buf, "Write Error", 
					MbOk | MbIconExclamation | MbMoveable);
	}

	rf.SetEA(".TYPE", bExtAttr(EaAscii, 10, "Phone Book") ); 
	if (rf.Error())
	{
		char buf[80];
		sprintf(buf, "Error setting extended attribute: %ld (%lx)", rf.Error(), rf.Error());
		wMessageBox(this, buf, "Write Error", 
					MbOk | MbIconExclamation | MbMoveable);
	}

	rf.Close();
	HourGlass();

	return 0;
}

long PhoneBookView :: UpdateCmdDescription(wMessage m)
{
	static long lastid=0;
	long id = (long)m.mp1;

	if (id != lastid)
	{
		if (id >=CMD_BASE && id <= (CMD_BASE + 32))
			stat->SetDesc(bString((ushort)id));
		else
			stat->SetDesc("");

		lastid = id;
	}
	return (long)m.mp2;
}

long PhoneBookView :: ToggleFrameControls(wCommandMsg m)
{
	wFrameControlList	*fcl = FrameControls();
	
	mnu->ToggleCheckItem(m.usCmd());
	if (!mnu->IsItemChecked(m.usCmd()))
	{
		if (m.usCmd() == MI_TOGGLETOOLBAR)
		{
			fcl->Find(toolbar);
			toolbar->Hide();
		}
		else
		{
			fcl->Find(stat);
			stat->Hide();
		}
		fcl->Remove();
	}
	else
	{
		if (m.usCmd() == MI_TOGGLETOOLBAR)
		{
			toolbar->Show();
			fcl->Insert(toolbar);
		}
		else
		{
			stat->Show();
			fcl->Insert(stat);
		}
	}
	return 0;
}

long PhoneBookView :: ChangeView(wCommandMsg m)
{
	if (m.cmdSource() == CmdSrcPushButton)
	{
		switch (m.usCmd())
		{
			case MI_SETDETAILSVIEW:
				cnt->SetView(DetailsView);
				cnt->SetImageSize(wDimension(20,20));
				mnu->CheckItem(MI_SETDETAILSVIEW);
				mnu->UnCheckItem(MI_SETICONVIEW);
				cnt->CtxMenu()->CheckItem(MI_SETDETAILSVIEW);
				cnt->CtxMenu()->UnCheckItem(MI_SETICONVIEW);
				break;

			case MI_SETICONVIEW:
				cnt->SetView(IconView);
				cnt->SetImageSize(wDimension(0,0));
				mnu->CheckItem(MI_SETICONVIEW);
				mnu->UnCheckItem(MI_SETDETAILSVIEW);
				cnt->CtxMenu()->CheckItem(MI_SETICONVIEW);
				cnt->CtxMenu()->UnCheckItem(MI_SETDETAILSVIEW);
				break;
		}
	}
	else
	{
		wImageButton *btn = toolbar->GetButton(m.usCmd());
		btn->Click();
	}		
	return 0;
}

long PhoneBookView :: OpenEntry(wCommandMsg)
{
	EditItem(cnt->CurrentItem());
	return 0;
}

long PhoneBookView :: DeleteEntry(wCommandMsg)
{
	wMessageBox	mb(this, "Do you want to delete the selected items", "Delete", MbYesNo);

	if (mb.MessBoxVal() == MrYes)
	{
		wPhoneCardItem 		*item;
		wContainerItemList	*l = cnt->GetItemsWithEmphasis(SelectedEmph);
		bool				ok = TRUE;

		// remove all selected (and not in use) items
		cnt->DisableUpdate();
		for (l->First() ; ok && (item = (wPhoneCardItem*)l->Current()) != 0 ; 
				l->Next())
			if (!item->IsInUse())
				ok = RemoveEntry(item->GetPhoneCard());
		cnt->EnableUpdate();

		SetModified(TRUE);
	}

	return 0;
}

long PhoneBookView :: DeleteOneEntry(wCommandMsg)
{
	// removes one entry -- from the context menu
	SetModified(TRUE);
	RemoveEntry(cnt->CurrentItem()->GetPhoneCard());
	return 0;	
}

void PhoneBookView :: EditItem(wPhoneCardItem *item)
{
	if (item)	// double clicked on item? (not white space)
	{
		if (item->IsInUse())
		{
			wPhoneCardEditor *ed = item->GetOpenView();
			if (ed->IsMinimized())
				ed->Restore();
				
			ed->ToTop();
		}
		else
		{
			item->SetEmphasis(InUseEmph, TRUE);
			item->SetOpenView(new wPhoneCardEditor(this, item->GetPhoneCard() ));
 		}
	}
}

long PhoneBookView :: ChangeName(wCommandMsg)
{
	wChangeNameForm fm(this);
	if (fm.GetResult() == AcFormExit)
	{
		pb->SetName(fm.GetName());
		SetModified(TRUE);
		SetCaption();
	}
	return 0;
}

long PhoneBookView :: MenuAction(wMenuActionMsg m)
{
	if (m.actionType() == MenuSelect)
	{
		stat->SetDesc(bString(m.usId()));
		return TRUE;
	}
	else if (m.actionType() == MenuInit)
	{
		if (m.usId() == M_ITEM)
		{
			ulong n = cnt->GetItemCountWithEmphasis(SelectedEmph);
			if (!n)
			{
				mnu->DisableItem(MI_DELETEENTRY);
				mnu->DisableItem(MI_COPYENTRY);	
				mnu->DisableItem(MI_PRINTSEL);	
			}
			else
			{
				mnu->EnableItem(MI_DELETEENTRY);
				mnu->EnableItem(MI_PRINTSEL);	
				if (n == 1)
					mnu->EnableItem(MI_COPYENTRY);	
			}
		}
	}
	else
	{
		if (m.hwndMenu() == cnt->ItemMenu()->hMenu())
			cnt->CurrentItem()->SetEmphasis(SourceEmph, FALSE);
	}
	return 0;
}

void PhoneBookView :: Paint()
{
	WindowPS()->Erase();
}

long PhoneBookView :: Size(wSizeMsg m)
{
	cnt->ChangeSize(m.sizeNew());
	return 0;
}

/*****************************************************************************
 * 
 * Container Support 
 *
 *****************************************************************************/

/*
 * This class provides a convienient way to construct the text columns
 * for the container details view
 */

wPhoneCardDataField :: wPhoneCardDataField(wContainer *cp, const char *colText, CntrFldFnp accfn)
					 : wContainerField(cp, FtString, colText, CtaCenter, 0)
{
	SetFieldAttribute(CfaLeft | CfaVertSeparator | CfaHorzSeparator, TRUE);
	SetAccessFns(accfn);
}

wIcon *GetPhoneCardDetailsIcon(wContainerItem *)
{
	static wIcon *icon = NULL;
	
	if (!icon)
		icon = new wIcon(ResIcon, I_MINICARD);

	return icon;
}

wDragImage *wPhoneCardItem::dragIcon = NULL;
wIcon *wPhoneCardItem::itemIcon = NULL;

wPhoneCardItem :: wPhoneCardItem(wContainer *pc, const char *text, mAppPhoneCard *_card)
				: wContainerItem(pc, text)    
{ 
	card = _card;
 	if (!dragIcon)
	{
		itemIcon = new wIcon(ResIcon, I_CARD);
		dragIcon = new wDragImage(itemIcon, FALSE);
	}
	SetName(text);
	SetTrueType("PhoneCard");
	SetDragImage(dragIcon);
	SetImage(itemIcon);
	SetDragCapabilities(Dragable | Moveable | Copyable);
	ExchangeMethods()->SetPurgeOnDelete(FALSE);
	ExchangeMethods()->Insert( (*pc->ExchangeMethods())[0] );

	lastName  = card->GetLastName();
	firstName = card->GetFirstName();
	companyName = card->GetCompanyName();
	homePhone = card->GetHomePhone();
	workPhone = card->GetWorkPhone();

	// associate card with container item
	card->SetContainerItem(this);
}

wPhoneCardItem :: ~wPhoneCardItem()
{
	// don't destroy drag image ('cause it's shared!)
	SetDragImage(NULL);	
}

bool wPhoneCardItem :: IsNameChanged()
{
	return (lastName  != card->GetLastName()) || 
		   (firstName != card->GetFirstName());
}

void wPhoneCardItem :: UpdateColumns()
{
	lastName  = card->GetLastName();
	firstName = card->GetFirstName();
	companyName = card->GetCompanyName();
	homePhone = card->GetHomePhone();
	workPhone = card->GetWorkPhone();
	Invalidate();
}

bString *GetLastNameField(wPhoneCardItem *item)
{
	return &(item->lastName);
}

bString *GetFirstNameField(wPhoneCardItem *item)
{
	return &(item->firstName);
}

bString *GetCompanyNameField(wPhoneCardItem *item)
{
	return &(item->companyName);
}

bString *GetHomePhoneField(wPhoneCardItem *item)
{
	return &(item->homePhone);
}

bString *GetWorkPhoneField(wPhoneCardItem *item)
{
	return &(item->workPhone);
}


wPhoneCardContainer :: wPhoneCardContainer(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style)
					 : wContainer(parent, id, p, size, style)
{
	ctxMenu = new wPopupMenu(parent, MP_PHONELIST);
	itemMenu = new wPopupMenu(parent, MP_ITEMLIST);
}

wPhoneCardContainer :: ~wPhoneCardContainer()
{
	delete ctxMenu;
	delete itemMenu;
}

void wPhoneCardContainer :: DeSelectAll()
{
	wContainerItemList *items = GetItemsWithEmphasis(SelectedEmph);
	wContainerItem *i;
	for (items->First(); (i = items->Current()) != NULL; items->Next())
		i->SetEmphasis(SelectedEmph, FALSE);

	delete items;
}

void wPhoneCardContainer :: MoveItemIntoViewport(wContainerItem *item)
{
	// this routine ensures that the desired item is entirely visible
	// to the user of the application
	long xOffset = 0, yOffset = 0;

	wRectl vpRectl = GetViewportRectl(TRUE);
	wRectl vpClientRectl = GetViewportRectl();
 	wRectl itemRectl = item->GetRectangle(CcIcon | CcText);

	// convert viewport coordinates to container client window coordintes
	vpRectl.yBottom() += vpClientRectl.yBottom();
	vpRectl.yTop() += vpClientRectl.yBottom();

	xOffset = vpRectl.xLeft();
	yOffset = vpClientRectl.xLeft();

	if (GetView() != DetailsView)
	{
		// adjust the x axis if necessary

		if (itemRectl.xLeft() < vpRectl.xLeft())
			xOffset = vpRectl.xLeft() - itemRectl.xLeft();

		else if (itemRectl.xRight() > vpRectl.xRight())
			xOffset = itemRectl.xRight() - vpRectl.xRight();
	}
	// adjust the y axis if necessary

	if (itemRectl.yBottom() < vpRectl.yBottom())
		yOffset = vpRectl.yBottom() - itemRectl.yBottom();

	else if (itemRectl.yTop() > vpRectl.yTop())
		yOffset = itemRectl.yTop() - vpRectl.yTop();


	if (xOffset)
		ScrollContainer(Horizontal, xOffset);

	if (yOffset)
		ScrollContainer(Vertical, yOffset);
}

void wPhoneCardContainer :: ContextMenu(wContainerItemMsg m)
{
	if (m.Item() == NULL)	// context menu over container white space?
	{
		ctxMenu->Position()= GetPointerPosition();
		ctxMenu->ItemID() = 200;
		ctxMenu->Options() = PumMouseButton1 | PumNone | PumKeyboard;
		ctxMenu->Go();
	}
	else	// context menu over container item
	{
		currentitem = (wPhoneCardItem*)m.Item();
		currentitem->SetEmphasis(SourceEmph, TRUE);
		itemMenu->Position()= GetPointerPosition();
		itemMenu->ItemID() = MI_OPENENTRY;
		itemMenu->Options() = PumMouseButton1 | PumNone | PumKeyboard;
		itemMenu->Go();
	}
}

void wPhoneCardContainer :: Enter(wContainerEnterMsg m)
{
	((PhoneBookView*)ParentWindow())->EditItem((wPhoneCardItem *)m.Item());
}

mAppPhoneCard :: mAppPhoneCard(wPhoneCardItem *item)
{
	viewCtl = item;
}

mAppPhoneCard :: mAppPhoneCard(mAppPhoneCard &c): mPhoneCard(c)
{
	viewCtl = NULL;
}

long wPhoneCardContainer :: Shred(wDragInfo *arr)
{
	long				lp, mx;
	wWorkplaceObject	**obj;
	PhoneBookView		*pbv = (PhoneBookView*)ParentWindow();

	mx = arr->Count();
	obj = arr->Objects();
	DisableUpdate();
	for (lp=0; lp<mx ; lp++)
	{
		mAppPhoneCard	*card = ((wPhoneCardItem*)obj[lp])->GetPhoneCard();
		pbv->RemoveEntry(card);
	}
	EnableUpdate();

	GetItemCltn()->Invalidate();

	return DrrAbort;
}


/*****************************************************************************
 * 
 * Dialogs
 *
 *****************************************************************************/

wChangeNameForm :: wChangeNameForm(PhoneBookView *framep) 
				 : wFormWindow(D_CHANGENAME, 2, 0, DlgModal)
{
	AddField( new wEditField(FtString, 32, E_NEWNAME, &newName, NULL, FsRequired) );
	AddField( new wEditField(FtString, 32, T_OLDNAME, &oldName) );
	
	oldName = framep->GetPhoneBook()->GetName();
	SetOptions(FmEnterExit, TRUE);
	SetActionButtons(BUT_CANCEL, BUT_OK);
	FormUp(framep);
}


wNewPhoneBookForm :: wNewPhoneBookForm(PhoneBookView *framep) 
				   : wFormWindow(D_NEWFILE, 2, 0, DlgModal)
{
	wEditField *ef;

	ef = new wEditField(FtString, 32, E_TITLE, &name, NULL, FsRequired);
	ef->SetFieldExitFn(FORMMETHOD(wNewPhoneBookForm, SetFileName));
	AddField(ef);

	AddField( new wEditField(FtString, 14, E_FILENAME, &filename, NULL, FsRequired) );
	SetOptions(FmEnterExit, TRUE);
	SetActionButtons(BUT_CANCEL, BUT_OK);
	FormUp(framep);
}

short wNewPhoneBookForm :: SetFileName(wEditField *fldp)
{
	const char *cp = fldp->GetText();
	short i = 8;
	char fn[9], fn2[14], ext[4], *tp;

	tp = fn;
	while (i && *cp)
	{
		if (isalnum(*cp) || *cp == '_')
		{
			*tp++ = toupper(*cp);
			i--;
		}
		cp++;
	}
	*tp = '\0';
	strcpy(fn2, fn);
	for (i = 1;;i++)
	{
		{
			bFile f(fn2);
			if (f.Exists())
			{
				strcpy(fn2, fn);
				sprintf(ext, ".%d", i);
				strcat(fn2, ext);
			}
			else
				break;
		}
	}
	((wEditField *)GetField(E_FILENAME))->SetText(fn2);
	return TRUE;
}

wFindItemForm :: wFindItemForm(PhoneBookView *framep) 
			   : wFormWindow(D_FINDENTRY, 4, 0, DlgModal)
{
	viewFrame = framep;

	AddField( new wEditField(FtString, LEN_FIRSTNAME, E_FIRSTNAME, &firstName) );
	AddField( new wEditField(FtString, LEN_LASTNAME, E_LASTNAME, &lastName) );
	AddField( new wEditField(FtString, LEN_COMPANYNAME, E_COMPANY, &companyName) );

	wPushButtonField *pf;
	AddField( pf = new wPushButtonField( BUT_FIND) );
	pf->SetFieldClickFn( FORMMETHOD(wFindItemForm, ProcFind) );

	SetActionButtons(BUT_CANCEL, 0);
	FormUp(framep);
}

short wFindItemForm :: ProcFind(wPushButtonField *)
{
	bool fFromStart = FALSE, fMatch;;

	if (IsModified())
	{
		// if any of the search parameters have been changed, then
		// reset the current item (if set) and start the search from
		// the begining of the list

		Convert();
		SetModified(FALSE);
		lastItem = NULL;
	}
	if (firstName.IsBlank() && lastName.IsBlank() && companyName.IsBlank())
	{
		wMessageBox(this, "You enter the search text into one or more the search fields.", "Input Error", 
					MbOk | MbIconExclamation | MbMoveable);

		return 0;
	}
	wContainerItemCltn *cltn = viewFrame->GetContainer()->GetItemCltn();

	if (!lastItem)
	{
		viewFrame->GetContainer()->DeSelectAll();
		cltn->First();
		fFromStart++;
	}
	else
	{
		lastItem->SetEmphasis(SelectedEmph, FALSE);
		cltn->Find(lastItem);
		cltn->Next();
	}

	for (;(lastItem = (wPhoneCardItem *)cltn->Current()) != NULL; cltn->Next())
	{
		mAppPhoneCard *card = lastItem->GetPhoneCard();
		fMatch = TRUE;
		for (;;)
		{
			if (!firstName.IsBlank() &&	strstr(card->GetFirstName(), firstName))
				break;

			if (!lastName.IsBlank() && strstr(card->GetLastName(), lastName))
				break;

			if (!companyName.IsBlank() && strstr(card->GetCompanyName(), companyName))
				break;

			fMatch = FALSE;
			break;
		}
		if (fMatch)
		{
			viewFrame->GetContainer()->MoveItemIntoViewport(lastItem);
			lastItem->SetEmphasis(SelectedEmph, TRUE);
			return 0;
		}
	}

	if (fFromStart)
	{
		wMessageBox(this, "No phone book items matched your search parameters!", "Find", 
					MbOk | MbIconExclamation | MbMoveable);
	}
	else
	{
		wMessageBox(this, "There are no more remaining matches!", "Find", 
					MbOk | MbIconExclamation | MbMoveable);
	}
	return 0;
}


/*****************************************************************************
 * 
 * Tool Bar 
 *
 *****************************************************************************/

ToolBar :: ToolBar(wFrameWindow *p)
	: wFrameControl(ClientTop)
{

	short	lp;
	wBitmap *bmp;

	CreateWindow(p, TOOLBAR, wPointl(0,0), wDimension(0,34));

	// create imagebuttons
	wPointl pos(2, 2);
	for (lp = 0 ; lp < TOOLBAR_BUTTONS; lp++)
	{
		pb[lp] = new wImageButton(this, MI_OPENFILE + lp, pos, wDimension(30,30), 
					  WsVisible | WsTabStop | (lp !=5 ? WsGroup : 0) | 
					  ((lp==4 || lp==5) ? IbButtonStick | IbAutoImageBtn : 0));

		pos.x() += 28;
		if (lp == 3 || lp == 5)
			pos.x() += 13;

		bmp = new wBitmap(ResBitmap, B_OPEN + lp);
		pb[lp]->SetImages(bmp, bmp, bmp);

		pb[lp]->ChangeOwner(OwnerWindow());
		if (lp)
		{
			// set the z order so that the auto-radio push
			// buttons function properly
			pb[lp]->PositionBehind(pb[lp-1]);
		}
	}
	pb[4]->Click();	// initialize to details view
	Show();
}

ToolBar :: ~ToolBar()
{
	short	lp;

	for (lp=0 ; lp < TOOLBAR_BUTTONS; lp++)
		delete pb[lp];
}

void ToolBar :: Paint()
{
	wPen		pn(WindowPS());
	wDimension	d = GetSize() - wDimension(1,1);

	WindowPS()->Erase(InvalidRectangle(), wColor(ClrPaleGray));

	// a 3d effect
	pn.SetColor(wColor(ClrDarkGray));
	pn.MoveTo(wPointl(0, 0));
	pn.LineTo(wPointl(d.xWidth(), 0));
	pn.LineTo(wPointl(d.xWidth(), d.yHeight()));
	pn.SetColor(wColor(ClrWhite));
	pn.MoveTo(wPointl(0, 0));
	pn.LineTo(wPointl(0, d.yHeight()));
	pn.LineTo(wPointl(d.xWidth(), d.yHeight()));
}

wImageButton *ToolBar :: GetButton(ushort id)
{ 
	return pb[id - MI_OPENFILE]; 
}

/*****************************************************************************
 * 
 * Title Bar Drag Icon 
 *
 *****************************************************************************/


TitleTools :: TitleTools(wFrameWindow *p)
	: wFrameControl(TitleBarRight)
{
	CreateWindow(p, TITLETOOLS, wPointl(0,0), wDimension(21,0));

	bmp = new wBitmap(ResBitmap, DOCUMENT);
}

TitleTools :: ~TitleTools()
{
	delete bmp;
}

void TitleTools :: Paint()
{
	WindowPS()->Erase(InvalidRectangle(), wColor(ClrPaleGray));
	bmp->DrawMono(WindowPS(), wPointl(1,1));
}


/*****************************************************************************
 * 
 * Status Bar
 *
 *****************************************************************************/


StatusBar :: StatusBar(wFrameWindow *p)
	: wFrameControl(ClientBottom)
{
	CreateWindow(p, STATUSBAR, wPointl(0,0), wDimension(0,15,DlgUnits));	

	entries = new wPanel3D(this, 1, wPointl(2,2,DlgUnits), wDimension(70,11,DlgUnits),
		WsVisible | P3OuterInset | P3NoInner | P3TextLeft, 1, 1);

	desc = new wPanel3D(this, 1, wPointl(74,2,DlgUnits), wDimension(100,11,DlgUnits),
		WsVisible | P3OuterInset | P3NoInner | P3TextLeft, 1, 1);

	entries->ChangeFont(Helv8);
	desc->ChangeFont(Helv8);
}

StatusBar :: ~StatusBar()
{
	delete entries;
	delete desc;
}

void StatusBar :: Paint()
{
	wPen		pn(WindowPS());
	wDimension	d = GetSize() - wDimension(1,1);

	WindowPS()->Erase(InvalidRectangle(), wColor(ClrPaleGray));

	// a 3d effect
	pn.SetColor(wColor(ClrDarkGray));
	pn.MoveTo(wPointl(0, 0));
	pn.LineTo(wPointl(d.xWidth(), 0));
	pn.LineTo(wPointl(d.xWidth(), d.yHeight()));
	pn.SetColor(wColor(ClrWhite));
	pn.MoveTo(wPointl(0, 0));
	pn.LineTo(wPointl(0, d.yHeight()));
	pn.LineTo(wPointl(d.xWidth(), d.yHeight()));
}

void StatusBar :: SetNumEntries(long num)
{
	char	buf[80];
	sprintf(buf, "Entries: %ld", num);
	entries->SetText(buf);
}

void StatusBar :: SetDesc(const char *s)
{
	desc->SetText(s);
}

long StatusBar :: Size(wSizeMsg m)
{
	wDimension	d(76, 4, DlgUnits);
	desc->ChangeSize(m.sizeNew() - d);
	return 0;
}

