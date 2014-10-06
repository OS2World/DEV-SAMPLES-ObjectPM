/*  VCS_ID
 *  $Filename:   phdata.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


/*
 * Data Model Classes for a Phone Book
 */

#include "recfile.hpp"

class mStorable
{
	public:
		virtual bool Store(bRecordFile& rf);
		virtual bool Retrieve(bRecordFile& rf);
};

class mAddress : public mStorable
{
	private:
		bString street1;
		bString street2;
		bString city;
		bString state;
		bString zip;

	public:
		mAddress();
	    mAddress(mAddress&);

		bString GetStreet1()			{ return street1; }
		bString GetStreet2()			{ return street2; }
		bString GetCity()				{ return city;	  }
		bString GetState()				{ return state;	  }
		bString GetZip()				{ return zip;	  }

		void SetStreet1(const char *s)	{ street1 = s;	}
		void SetStreet2(const char *s)	{ street2 = s;	}
		void SetCity(const char *c)		{ city = c;		}
		void SetState(const char *s)	{ state = s;	}
		void SetZip(const char *z)		{ zip = z;		}

		bool Store(bRecordFile& rf);
		bool Retrieve(bRecordFile& rf);
};

// Address field lengths

#define LEN_STREET		40
#define LEN_CITY		25
#define LEN_STATE		2
#define LEN_ZIP			10


class mPhoneCard : public mStorable
{
	private:
		bString  lastName;
		bString  firstName;
		mAddress homeAddress;
		bString  homePhone;
		bString  companyName;
		mAddress workAddress;
		bString  workPhone;
		bString  notes;

	protected:
		void *viewCtl;

	public:
		mPhoneCard();
	    mPhoneCard(mPhoneCard &);

		bString   GetLastName() 			{ return lastName;		}
		bString   GetFirstName() 			{ return firstName;		}
		mAddress *GetHomeAddress() 			{ return &homeAddress;	}
		bString   GetHomePhone() 			{ return homePhone;		}
		bString   GetCompanyName()			{ return companyName;	}
		mAddress *GetWorkAddress() 			{ return &workAddress;	}
		bString   GetWorkPhone() 			{ return workPhone;		}
		bString   GetNotes() 				{ return notes;			}

		void SetLastName(const char *ln)	{ lastName = ln;		}
		void SetFirstName(const char *fn)	{ firstName = fn;		}
		void SetHomePhone(const char *hph)	{ homePhone = hph;		}
		void SetWorkPhone(const char *wph)	{ workPhone = wph;		}
		void SetNotes(const char *n)		{ notes = n;			}
		void SetCompanyName(const char *c)	{ companyName = c;		}

		bool Store(bRecordFile& rf);
		bool Retrieve(bRecordFile& rf);
};

// this class is used to define the sort key for the list of 
// names in the sorted collection (map)

class mNameKey
{
	public:
		bString lastName;
		bString firstName;

		mNameKey(bString l, bString f);
};

typedef tCMap<mNameKey, mPhoneCard> mPhoneCardList;


// PhoneCard field lengths

#define LEN_LASTNAME	25
#define LEN_FIRSTNAME	15
#define LEN_HOMEPHONE	14
#define LEN_WORKPHONE	20
#define LEN_COMPANYNAME	32
#define LEN_NOTES		256

#define MAX_PHBK_ELEMENTS	8
#define MAX_PHBK_RECSIZE	625

class mPhoneBook : public mStorable
{
	private:
		bString fname;
		bString	  name;
		mPhoneCardList phoneCards;

	protected:
		void *viewCtl;

	public:
		mPhoneBook();
	   	mPhoneBook(mPhoneBook&);

		bString GetFilename()			{ return fname;			}
		bString GetName()				{ return name;  		}
		mPhoneCardList *GetPhoneCards()	{ return &phoneCards;	}

		void SetFilename(const char *fn)	{ fname = fn;		}
		void SetName(const char *nm)		{ name  = nm;		}

		bool AddPhoneCard(mPhoneCard *pc);
		bool Store(bRecordFile& rf);
		bool Retrieve(bRecordFile& rf);
};



