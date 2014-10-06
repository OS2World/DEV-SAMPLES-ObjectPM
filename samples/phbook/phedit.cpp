/*  VCS_ID
 *  $Filename:   phedit.cpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define InclControls
#define InclGraphics
#define InclForms
#define InclFiles
#include <ObjectPM.hpp>

#define NOTEBOOK 100

#include "phbook.hpp"
#include "phedit.hpp"


wPhoneCardEditor :: wPhoneCardEditor(PhoneBookView *_vp, mAppPhoneCard *_card)
{
	vp = _vp;
	card = _card;

	HourGlass();
	CreateWindow(FaTitleBar | FaSysMenu | FaSizeBorder | FaMinMax);
	SetCaption("New Phone Book Entry");				  
//	SetIcon(icon = new wIcon(ResIcon, I_FORMDEMO));   

	np = new wPhoneCardNotebook(this, NOTEBOOK, wPointl(2, 0, DlgUnits),
			     wDimension(325, 158, DlgUnits), WsVisible | BkSpiralBinding);

	np->SetMajorTabDimension(wDimension(42, 12, DlgUnits));
	np->SetMinorTabDimension(wDimension(40, 12, DlgUnits));
	np->ChangeFont(Helv10);

	forms[0]  = new wPersonalForm(this);
	forms[1]  = new wBusinessForm(this);

	ChangeFrameSize( CalcFrameSize(wDimension(320, 165, DlgUnits)) );
	ChangePosition(PosCenter);
	HourGlass();
	np->GotoPage((*np->Pages())[0]);
	Show();
	ToTop();
}

wPhoneCardEditor :: ~wPhoneCardEditor()
{
	// delete the notebook. Note that this also destroys the forms
	// that are on each page so that we don't have to do it.
	delete np;
}

long wPhoneCardEditor :: Close(wMessage)
{
	CloseView();
	return FALSE;
}

void wPhoneCardEditor :: Paint()
{
	WindowPS()->Erase(WindowRectangle(), ClrPaleGray);		  // Erase the client window
}

void wPhoneCardEditor :: CloseView()
{
	short i;
	bool fModified = FALSE;

	// first, check all forms for validation errors 
	for (i = 0; i < PC_EDITFORMS; i++)
	{
		fModified |= forms[i]->IsModified();
		if (!(forms[i]->Convert()))
			return;
	}

	// save the data to the target object
	for (i = 0; i < PC_EDITFORMS; i++)
		forms[i]->Save();

	if (card->GetContainerItem() == NULL)	// new card?
		vp->AddNewEntry(card);

	else if (fModified)
		vp->ModifyEntry(card);

	// tell the main frame window to destroy this view
	vp->PostMessage(wMessage(WmDestroyCardEditor, (MPARAM)this, NULL));
}

void wPhoneCardEditor :: CancelView()
{
	if (card->GetContainerItem() == NULL)
	{
		// canceling an add of a new entry
		delete card;
	}
	vp->PostMessage(wMessage(WmDestroyCardEditor, (MPARAM)this, NULL));
}

void wPhoneCardNotebook :: PageSelected(wNBPageMsg m)
{
	wNoteBookPage *pw;

	if ((pw = m.NewTopPage()) != NULL)
	{
		if (pw->GetWindow())
			pw->GetWindow()->ToTop();  	// activate the new top form
	}
}

/***************************************************************************** 
 *
 * Form Pages
 *
 *****************************************************************************/


wPhoneCardForm :: wPhoneCardForm(wPhoneCardEditor *framep, ushort dlg_id, short nFields)
			    : wFormWindow(dlg_id, nFields + 2, 0, DlgModeless)
{
	viewFrame = framep;

	wPushButtonField *pf;
	AddField( pf = new wPushButtonField( BUT_OK) );
	pf->SetFieldClickFn( FORMMETHOD(wPhoneCardForm, ProcOK) );

	AddField( pf = new wPushButtonField( BUT_CANCEL) );
	pf->SetFieldClickFn( FORMMETHOD(wPhoneCardForm, ProcCancel) );
}

short wPhoneCardForm :: ProcOK(wPushButtonField *)
{
	viewFrame->CloseView();
	return 0;
}

short wPhoneCardForm :: ProcCancel(wPushButtonField *)
{
	viewFrame->CancelView();
	return 0;
}


wPersonalForm :: wPersonalForm(wPhoneCardEditor *framep)
			   : wPhoneCardForm(framep, D_PHONECARD1, 8)
{
	wNoteBookPage *pg;
	wNoteBookPageList *pages = viewFrame->GetNoteBook()->Pages();

	AddField( new wEditField(FtString, LEN_FIRSTNAME, E_FIRSTNAME, &firstName) );
	AddField( new wEditField(FtString, LEN_LASTNAME, E_LASTNAME, &lastName) );
	AddField( new wEditField(FtString, LEN_STREET, E_STREET1, &street1) );
	AddField( new wEditField(FtString, LEN_STREET, E_STREET2, &street2) );
	AddField( new wEditField(FtString, LEN_CITY, E_CITY, &city) );
	AddField( new wEditField(FtString, LEN_STATE, E_STATE, &state, "%!") );
	AddField( new wEditField(FtString, LEN_ZIP, E_ZIP, &zip) );

	wEditField *ed = new wEditField(FtString, LEN_HOMEPHONE, E_PHONENO, &homePhone);
	ed->SetEditMask("(999) 999-9999");
	AddField(ed);

	mAppPhoneCard *card = viewFrame->GetPhoneCard();

	firstName = card->GetFirstName();
	lastName  = card->GetLastName();
	homePhone = card->GetHomePhone();
	street1   = card->GetHomeAddress()->GetStreet1();
	street2   = card->GetHomeAddress()->GetStreet2();
	city      = card->GetHomeAddress()->GetCity();
	state     = card->GetHomeAddress()->GetState();
	zip		  = card->GetHomeAddress()->GetZip();

	pages->InsertPage(pg = new wNoteBookPage(NULL, BpMajor | BpStatusTextOn, ""));
	pg->SetTab("Personal");
	pg->SetPageHandle(0);

	FormUp(viewFrame->GetNoteBook());
	ChangePosition(wPointl(0, 0));
	pg->SetWindow(this);
	Show();
}

short wPersonalForm :: Save()
{
	mAppPhoneCard *card = viewFrame->GetPhoneCard();
	mAddress *addr = card->GetHomeAddress();

	card->SetFirstName(firstName);
	card->SetLastName(lastName);
	card->SetHomePhone(homePhone);
	addr->SetStreet1(street1);
	addr->SetStreet2(street2);
	addr->SetCity(city);
	addr->SetState(state);
	addr->SetZip(zip);

	return 0;
};

wBusinessForm :: wBusinessForm(wPhoneCardEditor *framep)
			   : wPhoneCardForm(framep, D_PHONECARD2, 7)
{
	wNoteBookPage *pg;
	wNoteBookPageList *pages = viewFrame->GetNoteBook()->Pages();

	AddField( new wEditField(FtString, LEN_COMPANYNAME, E_COMPANY, &companyName) );
	AddField( new wEditField(FtString, LEN_STREET, E_STREET1, &street1) );
	AddField( new wEditField(FtString, LEN_STREET, E_STREET2, &street2) );
	AddField( new wEditField(FtString, LEN_CITY, E_CITY, &city) );
	AddField( new wEditField(FtString, LEN_STATE, E_STATE, &state, "%!") );

	wEditField *ed = new wEditField(FtString, LEN_ZIP, E_ZIP, &zip);
	ed->SetEditMask("99999-9999");
	AddField(ed);

	ed = new wEditField(FtString, LEN_WORKPHONE, E_PHONENO, &workPhone);
	ed->SetEditMask("(999) 999-9999 XXXXX");
	AddField(ed);

	mAppPhoneCard *card = viewFrame->GetPhoneCard();

	companyName = card->GetCompanyName();
	workPhone = card->GetWorkPhone();
	street1   = card->GetWorkAddress()->GetStreet1();
	street2   = card->GetWorkAddress()->GetStreet2();
	city      = card->GetWorkAddress()->GetCity();
	state     = card->GetWorkAddress()->GetState();
	zip		  = card->GetWorkAddress()->GetZip();

	pages->InsertPage(pg = new wNoteBookPage(NULL, BpMajor | BpStatusTextOn, ""));
	pg->SetTab("Business");
	pg->SetPageHandle(1);

	FormUp(viewFrame->GetNoteBook());
	ChangePosition(wPointl(0, 0));
	pg->SetWindow(this);
	Show();
}

short wBusinessForm :: Save()
{
	mAppPhoneCard *card = viewFrame->GetPhoneCard();
	mAddress *addr = card->GetWorkAddress();

	card->SetCompanyName(companyName);
	card->SetWorkPhone(workPhone);
	addr->SetStreet1(street1);
	addr->SetStreet2(street2);
	addr->SetCity(city);
	addr->SetState(state);
	addr->SetZip(zip);

	return 0;
};


