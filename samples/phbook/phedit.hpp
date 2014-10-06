/*  VCS_ID
 *  $Filename:   phedit.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define PC_EDITFORMS 2

class wPhoneCardNotebook;


class wPhoneCardEditor : public wFrameWindow
{
	private:
		wIcon *icon;
		wPhoneCardNotebook *np;
		wFormWindow *forms[PC_EDITFORMS];
		PhoneBookView *vp;
		mAppPhoneCard *card;

	public:
		wPhoneCardEditor(PhoneBookView *vp, mAppPhoneCard *card);
		~wPhoneCardEditor();

		wPhoneCardNotebook  *GetNoteBook()	{ return np;   }
		mAppPhoneCard 		*GetPhoneCard()	{ return card; }

		void CloseView();
		void CancelView();
		long Close(wMessage);
		void Paint();
};

class wPhoneCardNotebook : public wNoteBook
{
	public:
		wPhoneCardNotebook(wWindow *parent, ushort id, wPointl p, wDimension d, ulong style)
					: wNoteBook(parent, id, p, d, style)	{}

		void PageSelected(wNBPageMsg m);
};

class wPhoneCardForm : public wFormWindow
{
	protected:
		wPhoneCardEditor *viewFrame;

	public:
		wPhoneCardForm(wPhoneCardEditor *framep, ushort dlg_id, short nFields);

		short ProcOK(wPushButtonField *);
		short ProcCancel(wPushButtonField *);
};

class wPersonalForm : public wPhoneCardForm
{
	private:
		bString lastName;
		bString firstName;
		bString homePhone;
		bString street1;
		bString street2;
		bString city;
		bString state;
		bString zip;

	public:
		wPersonalForm(wPhoneCardEditor *framep);
		short Save();
};

class wBusinessForm : public wPhoneCardForm
{
	private:
		bString companyName;
		bString workPhone;
		bString street1;
		bString street2;
		bString city;
		bString state;
		bString zip;

	public:
		wBusinessForm(wPhoneCardEditor *framep);
		short Save();
};



