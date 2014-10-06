/*  VCS_ID
 *  $Filename:   country.hpp
 *  $Author  :   Brad Kimble, John Brooking
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


//+*****************************************************************************
//
//
//	DESCRIPTION:
//
//		The Country object.
//
//-*****************************************************************************

#ifndef __COUNTRY_HPP
#define __COUNTRY_HPP


#ifndef INCL_DOSNLS
struct _COUNTRYINFO;
typedef _COUNTRYINFO COUNTRYINFO;
#endif

// Defines used for various Foreign language functions.
// This includes things for Country Info, code pages, and display
// formats for dates, time, and currency.

//  Defines to use to determine the type of date representation to be used.

enum bDateFormat
{
	Form_MMDDYY,   	  // MM/DD/YY
	Form_DDMMYY,   	  // DD/MM/YY
   	Form_YYMMDD    	  // YY/MM/DD
};

//  Defines to use to determine the type of time representation to be used.

enum bTimeFormat
{
   Form_12Hour,         // With AM/PM indicator
   Form_24Hour          // Without AM/PM indicator
};

// Defines for the Position of the currency ID
enum bCurrencyIDPos
{
	CurrencyID_Precedes,	// Currency ID precedes the money value.
	CurrencyID_Follows, 	// Currency ID follows the money value.
	CurrencyID_Decimal 		// Currency ID replaces decimal indicator.
};

// Enumerated country codes
enum bCountryCode
{
	DEFAULT_COUNTRY_CODE = 0,
	Asian_English	= 99,
	Australia		= 61,
	Belgium			= 32,
	Canada			=  2,
	China			= 86,
	Czechoslovakia	= 42,
	Denmark			= 45,
	Finland			=358,
	France			= 33,
	Germany			= 49,
	Hungary			= 36,
	Iceland			=354,
	Italy			= 39,
	Japan			= 81,
	Korea			= 82,
	Latin_America	=  3,
	Netherlands		= 31,
	Norway			= 47,
	Poland			= 48,
	Portugal		=351,
	Spain			= 34,
	Sweden			= 46,
	Switzerland		= 41,
	Taiwan			= 88,
	Turkey			= 90,
	United_Kingdom	= 44,
	United_States	=  1,
	Yugoslavia		= 38
};

// Enumerated code page

enum bCodePage
{
	CURRENT_CODEPAGE    = 0,
	CP_United_States	= 437,
	CP_Multilingual		= 850,
	CP_Latin2			= 852,
	CP_Turkish			= 857,
	CP_Portuguese		= 860,
	CP_Iceland			= 861,
	CP_French_Canadian	= 863,		// eh?
	CP_Nordic			= 865,
	CP_Japan			= 932,
	CP_Korea			= 934,
	CP_China			= 936,
	CP_Taiwan			= 938,
	CP_JapanSAA			= 942,
	CP_KoreaSAA			= 944,
	CP_ChinaSAA			= 946,
	CP_TaiwanSAA		= 948
};

class _EXPORT_ bCountry
{
		bCountryCode	CountryCode;
		bCodePage   	CodePage;

		bDateFormat		DateFormat;
		char 	   		DateSep;
		bTimeFormat		TimeFormat;
		char 	   		TimeSep;
        bString         AM;
        bString         PM;

		bString         Currency;
		char 			ThousandsSep;
   		char 			DecimalSep;
     	unsigned		CurrencySpace;
   		unsigned 		CurrencyDecPl;
		bCurrencyIDPos	CurrencyIDPos;
        bool            LeadingZero; 

		char			DataListSep;

	public:

    	bCountry( bCountryCode usWhichCountry = DEFAULT_COUNTRY_CODE,
			 	bCodePage usWhichCodePage = CURRENT_CODEPAGE );
    	~bCountry();

		const char*     GetCountryName();
		bCountryCode	GetCountry()    const { return CountryCode; }
		bCodePage   	GetCodePage()   const { return CodePage; }

		bDateFormat 	GetDateFormat() const { return DateFormat; }
		char 	   		GetDateSep()    const { return DateSep; }
		bTimeFormat		GetTimeFormat() const { return TimeFormat; }
		char 	   		GetTimeSep()    const { return TimeSep; }
		const char*		GetAM()         const { return AM; }
		const char*		GetPM()         const { return PM; }

		const char*     GetCurrency()       const { return Currency; }
		char 			GetThousandsSep()   const { return ThousandsSep; }
   		char 			GetDecimalSep()     const { return DecimalSep; }
        bool            GetLeadingZero()    const { return LeadingZero; }
     	unsigned		GetCurrencySpace()  const { return CurrencySpace; }
   		unsigned		GetCurrencyDecPl()  const { return CurrencyDecPl; }
		bCurrencyIDPos	GetCurrencyIDPos()  const { return CurrencyIDPos; }

		char			GetDataListSep()    const { return DataListSep; }
};

#endif // __COUNTRY_HPP
