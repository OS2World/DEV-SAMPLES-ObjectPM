/*  VCS_ID
 *  $Filename:   phbook.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#include "phdata.hpp"		// model classes
#include "phbook.h"			// resource definitions


/*
 * PhoneBook View Classes
 */

#define TOOLBAR_BUTTONS		10

class ToolBar : public wFrameControl
{
	private:
		wImageButton *pb[TOOLBAR_BUTTONS];
	public:
		ToolBar(wFrameWindow *p);
		~ToolBar();

		void Paint();
		wImageButton *GetButton(ushort id);
};

class TitleTools : public wFrameControl
{
	private:
		wBitmap	*bmp;
		
	public:
		TitleTools(wFrameWindow *p);
		~TitleTools();

		void Paint();
};

class StatusBar : public wFrameControl
{
	private:
		wPanel3D	*desc, *entries;
	public:
		StatusBar(wFrameWindow *p);
		~StatusBar();

		void Paint();
		long Size(wSizeMsg);

		void SetNumEntries(long num);
		void SetDesc(const char *s);
};

// declare for forward references
class wPhoneCardItem;
class wPhoneCardContainer;
class mAppPhoneCard;
class wPhoneCardEditor;


// App defined messages
#define WmDestroyCardEditor		0x2200


class PhoneBookView : public wFrameWindow
{
	private:
		wPhoneCardContainer	*cnt;
		wMenu		*mnu;
		mPhoneBook  *pb;
		wIcon		*icon;
		StatusBar	*stat;
		ToolBar		*toolbar;
		bool		 fModified;

	public:
		PhoneBookView(short argc, char **argv);
		~PhoneBookView();

		void SetModified(bool fMod)			{ fModified = fMod; }
		bool IsModified()					{ return fModified; }
		mPhoneBook *GetPhoneBook()			{ return pb;		}
		wPhoneCardContainer *GetContainer() { return cnt;		}

		bool AddNewEntry(mAppPhoneCard *);
		bool ModifyEntry(mAppPhoneCard *);
		bool RemoveEntry(mAppPhoneCard *);
		bool CheckCurrentPhoneBook();
		void SetCaption();

		// command handlers
		long AddEntry(wMessage);
		long FindEntry(wCommandMsg);
		long OpenEntry(wCommandMsg);
		long DeleteEntry(wCommandMsg);
		long DeleteOneEntry(wCommandMsg);
		void DestroyCardEditor(wMessage m);
		long Open(wCommandMsg);
		long New(wCommandMsg);
		long Save(wCommandMsg);
		long ToggleFrameControls(wCommandMsg);
		long ChangeView(wCommandMsg);
		long ChangeName(wCommandMsg);

		void EditItem(wPhoneCardItem *item);

		// message handlers
		void Paint();
		long Size(wSizeMsg m);
		long MenuAction(wMenuActionMsg);
		long UpdateCmdDescription(wMessage);
};


class wPhoneCardContainer : public wContainer
{
	private:
		wPopupMenu 		*ctxMenu, *itemMenu;
		wPhoneCardItem	*currentitem;

//		void openitem(wPhoneCardItem *item);

	public:
		wPhoneCardContainer(wWindow *parent, ushort id, wPointl p, wDimension size, ulong style);
	   ~wPhoneCardContainer();

		void DeSelectAll();
		void MoveItemIntoViewport(wContainerItem *item);
		void ContextMenu(wContainerItemMsg m);
		void Enter(wContainerEnterMsg m);
		long Shred(wDragInfo *arr);

		wPopupMenu *CtxMenu() { return ctxMenu; }
		wPopupMenu *ItemMenu() { return itemMenu; }
		wPhoneCardItem *CurrentItem() { return currentitem; }
};


// customized app version of the mPhoneCard model class.  This
// subclass adds the necessary view information and methods in
// order to the  use the mPhoneCard class in this app

class mAppPhoneCard : public mPhoneCard
{
	public:
		mAppPhoneCard(wPhoneCardItem *item);
	    mAppPhoneCard(mAppPhoneCard &);

		wPhoneCardItem *GetContainerItem()			{ return (wPhoneCardItem *)viewCtl; }
		void SetContainerItem(wPhoneCardItem *item)	{ viewCtl = (void *)item; }
};


class wPhoneCardItem : public wContainerItem
{
	private:
		static wDragImage *dragIcon;
		static wIcon      *itemIcon;

		// "shadow" string members for the column text.  Note that
		// since bStrings use reference counting, the actual text strings
		// are not duplicated in an object of this class when initialized
		// from its associated mAppPhoneCard object.

		bString  lastName;
		bString  firstName;
		bString  homePhone;
		bString  companyName;
		bString  workPhone;

		mAppPhoneCard *card;
		wPhoneCardEditor *openView;
		
		// accessor friend functions for container details view

		friend bString *GetLastNameField(wPhoneCardItem *);

		friend bString *GetFirstNameField(wPhoneCardItem *);
		friend bString *GetCompanyNameField(wPhoneCardItem *);
		friend bString *GetHomePhoneField(wPhoneCardItem *);
		friend bString *GetWorkPhoneField(wPhoneCardItem *);

	public:
		wPhoneCardItem(wContainer *pc, const char *text, mAppPhoneCard *card);
	   ~wPhoneCardItem();

		mAppPhoneCard *GetPhoneCard()				{ return card;     }
		wPhoneCardEditor *GetOpenView()				{ return openView; }
		void SetOpenView(wPhoneCardEditor *ed)		{ openView = ed;   }
		bool IsNameChanged();
		void UpdateColumns();
};


class wPhoneCardDataField : public wContainerField
{
	public:
		wPhoneCardDataField(wContainer *cp, const char *colText, CntrFldFnp accfn);
};


class wChangeNameForm : public wFormWindow
{
	private:
		bString oldName;
		bString newName;

	public:
		wChangeNameForm(PhoneBookView *framep);
		bString GetName()		{ return newName; }
};

class wNewPhoneBookForm : public wFormWindow
{
	private:
		bString name;
		bString filename;

	public:
		wNewPhoneBookForm(PhoneBookView *framep);

		short   SetFileName(wEditField *fldp);
		bString GetName()		{ return name;		}
		bString GetFilename()	{ return filename; 	}
};

class wFindItemForm : public wFormWindow
{
	private:
		bString firstName;
		bString lastName;
		bString companyName;
		wPhoneCardItem *lastItem;
		PhoneBookView *viewFrame;

	public:
		wFindItemForm(PhoneBookView *framep);
		short ProcFind(wPushButtonField *);
};
