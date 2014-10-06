/*  VCS_ID
 *  $Filename:   phdata.cpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define InclFiles

#include <ObjectPM.hpp>
#include "phdata.hpp"

/*****************************************************************************
 * 
 * PhoneBook data classes
 *
 *****************************************************************************/

#define OP_ADDR  "ADDR"
#define OP_CARD	 "CARD"
#define OP_PHBK	 "PHBK"

mAddress :: mAddress()
{
}

mAddress :: mAddress(mAddress& a) 
		  :	street1(a.street1), street2(a.street2), city(a.city),	
			state(a.state), zip(a.zip)	
{
}

bool mAddress :: Store(bRecordFile& rf)
{
	rf << street1 << street2 << city << state << zip;
	return rf.WriteRecord(OP_ADDR);
};

bool mAddress :: Retrieve(bRecordFile& rf)
{
	if (!rf.ReadRecord())
		return FALSE;
		
	if (rf.GetElementCount() != 5 || rf.GetOpCode() != OP_ADDR)
	{
		// formatting error
		return FALSE;
	}
	rf >> street1 >> street2 >> city >> state >> zip;
	return TRUE;
}


mPhoneCard :: mPhoneCard()
{
}

mPhoneCard :: mPhoneCard(mPhoneCard& c)
			: lastName(c.lastName),	firstName(c.firstName),
			  homeAddress(c.homeAddress), homePhone(c.homePhone),
			  companyName(c.companyName), workAddress(c.workAddress),
			  workPhone(c.workPhone), notes(c.notes), viewCtl(NULL)
{
}

bool mPhoneCard :: Store(bRecordFile& rf)
{
	rf << lastName << firstName << homePhone << companyName << workPhone;
	rf << notes;

	if (rf.WriteRecord(OP_CARD))
	{
		if (!homeAddress.Store(rf))
			return FALSE;

		if (!workAddress.Store(rf))
			return FALSE;

		return TRUE;
	}
	return FALSE;
};

bool mPhoneCard :: Retrieve(bRecordFile& rf)
{
	if (!rf.ReadRecord())
		return FALSE;
		
	if (rf.GetElementCount() != 6 || rf.GetOpCode() != OP_CARD)
	{
		// formatting error
		return FALSE;
	}
	rf >> lastName >> firstName >> homePhone >> companyName >> workPhone;
	rf >> notes;

	if (!homeAddress.Retrieve(rf))
		return FALSE;

	if (!workAddress.Retrieve(rf))
		return FALSE;

	return TRUE;
}

mNameKey :: mNameKey(bString l, bString f) : lastName(l), firstName(f) 
{
}

mPhoneBook :: mPhoneBook() : phoneCards("mNameKey", TRUE, TRUE, TRUE),
							 name("Untitled")
{
	// specify the sort criteria for the mapping
	phoneCards.SortBy( 2,
		"lastName", (CompareFunc)cmpi_BSTRING, TRUE,
		"firstName", (CompareFunc)cmpi_BSTRING,  TRUE );

}

mPhoneBook :: mPhoneBook(mPhoneBook& p)	: phoneCards("mNameKey", TRUE, TRUE, TRUE) 
{
	mPhoneCard *c;

	// specify the sort criteria for the mapping
	phoneCards.SortBy( 2,
		"lastName", (CompareFunc)cmpi_BSTRING, TRUE,
		"firstName", (CompareFunc)cmpi_BSTRING,  TRUE );

//	for (p.phoneCards.First(); (c = p.phoneCards.Current()) != NULL; p.phoneCards.Next())
//		phoneCards.Add(new mPhoneCard(*c));
}

bool mPhoneBook :: Store(bRecordFile& rf)
{
	mPhoneCard *card;

	rf << phoneCards.Entries();
	if (!rf.WriteRecord(OP_PHBK))
		return FALSE;

	for (phoneCards.First(); (card = *phoneCards) != NULL; phoneCards.Next())
	{
		if (!card->Store(rf))
			return FALSE;
	}
	return TRUE;
};

bool mPhoneBook :: Retrieve(bRecordFile& rf)
{
	long nCards;

	if (!rf.ReadRecord())
		return FALSE;
		
	if (rf.GetElementCount() != 1 || rf.GetOpCode() != OP_PHBK)
	{
		// formatting error
		return FALSE;
	}
	rf >> nCards;

	while (nCards--)
	{
		mPhoneCard *card = new mPhoneCard();
		if (!card->Retrieve(rf))
			return FALSE;

		AddPhoneCard(card);
	}
	return TRUE;
}

bool mPhoneBook :: AddPhoneCard(mPhoneCard *pc)
{
	mNameKey *key = new mNameKey(pc->GetLastName(), pc->GetFirstName());
	return phoneCards.InsertAssoc(key, pc);
}


bool mStorable :: Store(bRecordFile& rf)
{
	return TRUE;
}

bool mStorable :: Retrieve(bRecordFile& rf)
{
	return TRUE;
}
