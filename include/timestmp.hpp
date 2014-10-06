//+*****************************************************************************
//
// VERSION:  $Revision:   1.4  $
//			 $Date:   27 Oct 1992 16:44:56	$
//
// MODULE:	 timestmp.hpp
// AUTHOR:	 chas
// FACILITY: Object PM
//
// Copyright (c)	1995 by Secant Technologies
//
//
// DESCRIPTION:
//
//	   This declares the bTime, bDate, bTimeStamp, bDeltaTime, bDeltaDate,
//	   and bDeltaTimeStamp objects.
//
//-*****************************************************************************

#ifndef __TIMESTMP_HPP
#define __TIMESTMP_HPP

#include "string.hpp"

#pragma pack(1)

class bDeltaTime;
class bDeltaDate;
class bDeltaTimeStamp;

//+*****************************************************************************
//
//	  CLASS:	   bTime
//
//	  DESCRIPTION:
//		Keep track of the number of hundredths of seconds since 12 midnight
//
//		Dynamic string formatting according to a description string
//		using characters similar to printf formatting characters.
//
//			+Format +Description
//			| %C	| Country dependent format
//			| %h	| Hundredths of seconds
//			| %H	| Hour in 24-hour format (00-23)
//			| %I	| Hour in 12-hour format (01-12)
//			| %M	| Minute as a decimal number (00-59)
//			| %p	| Current locale's AM/PM indicator for a 12-hour clock
//			| 	    | (followed by default PM hours)
//			| %R	| time separator is next charater
//			| %S	| Second as a decimal number (00-59)
//			| %%	| Percent sign
//
//		Currently there is no support for daylight-savings time or time zone
//		names.
//
//		In constructors and Set methods taking a character pointer for time
//		value, a NULL pointer may be used to indicate the current time.
//		Otherwise the value string must conform to the format string.
//		A NULL Format string uses the default country format.
//
//		A long cast and math operators are provided
//		as the number of hundredths of seconds since midnight.
//
//-*****************************************************************************

#define TsNow (const char*)0

class _EXPORT_ bTime
{
	private:
		void	ampmflags(char& f);
	protected:
		schar	hundredths; // 0-99
		schar	seconds;	// 0-59
		schar	minutes;	// 0-59
		schar	hours;		// 0-23

		signed char	Normalize(long hs);
		int 	parse(const char*& time, const char*& fmt, char* seps);
		int 	format(const char*& fmt, char*& buffer, char* seps) const;
		static int build(char*& mask, const char*& fmt, char* seps);

	public:
		bTime();
		bTime(uchar h, uchar mi, uchar s, uchar hu= 0) { hours= h; minutes= mi; seconds= s; hundredths= hu; }
		bTime(const char* time, const char* fmt= 0);

		bTime(const bTime& time);
		bTime& operator= (const bTime& time);

		// is this a normalized time?
		bool	IsValid() const;
		void	SetInvalid()		{ hours= 24; }

		// accessesors
		long	Ordinal() const;	// hundreths of seconds from start of day
		uchar   Hundredth() const	{ return hundredths; }
		uchar   Second()	const	{ return seconds; }
		uchar   Minute()	const	{ return minutes; }
		uchar   Hour() 	const	{ return hours; }

		static	int GetTimeZone();

		// setters
		void	Ordinal(long hs);
		void	Hundredth(uchar h) { hundredths= h; }
		void	Second(uchar s)	{ seconds= s; }
		void	Minute(uchar m)	{ minutes= m; }
		void	Hour(uchar h)	{ hours= h; }
		void	SetTime(uchar h, uchar mi, uchar s, uchar hu= 0) { hours= h; minutes= mi; seconds= s; hundredths= hu; }
		bool	SetTime(const char* time= 0, const char* fmt= 0 );
		bTime&	operator= (const char* time) { SetTime(time); return *this; }

		static	void SetTimeZone(int tz);
        void    SetSystem();

		// other information
		
        uchar   Hour12()	const	{ return uchar(hours>12 ?hours-12 :(hours ?hours :12)); }
		bool	IsAM()		const	{ return hours<12; }

		// Comparison
		int 	Compare(const bTime& t) const;
		bool	operator== (const bTime& t) const { return Compare(t)==0; }
		bool	operator!= (const bTime& t) const { return Compare(t)!=0; }
		bool	operator>= (const bTime& t) const { return Compare(t)>=0; }
		bool	operator<= (const bTime& t) const { return Compare(t)<=0; }
		bool	operator>  (const bTime& t) const { return Compare(t)>0; }
		bool	operator<  (const bTime& t) const { return Compare(t)<0; }

		// Formatters
		static bString BuildMask(const char* fmt);
		bString  Format(const char* fmt = 0) const;
		operator bString()	const	{ return Format(); }

		// Math
 friend bTime operator+ ( const bTime& t, const bDeltaTime& dt );
 friend bTime operator- ( const bTime& t, const bDeltaTime& dt );
 friend bDeltaTime operator- ( const bTime& t, const bTime& dt );

		bTime& operator+= ( const bDeltaTime &dt );
		bTime& operator-= ( const bDeltaTime &dt );
        
		bTime& operator+= (long days);
		bTime& operator-= (long days)   { return operator+=(-days); }
		bTime& operator++ (int)         { return operator+=(1); }
		bTime& operator-- (int)         { return operator-=(-1); }
};

// DB2 Formats
#define TIME_DB2_ISO_FORMAT "%R.%H.%M.%S"    // DB2 ISO time
#define TIME_DB2_USA_FORMAT "%R:%I:%M %p"     // DB2 USA time
#define TIME_DB2_EUR_FORMAT "%R.%H.%M.%S"    // DB2 EUR time
#define TIME_DB2_JIS_FORMAT "%R:%H:%M:%S"    // DB2 JIS time
#define TIME_DB2_FORMAT 	TIME_DB2_USA_FORMAT // Default DB2 time

// **********************************************************************
// Some macros having to do with months and leap years
//			  +Macro			+Description
//			  | IsLeap(y)		| Returns TRUE if year y is a leap year
//			  | Has30Days(m)	| Returns TRUE if month m has 30 days
//			  | Has31Days(m)	| Returns TRUE if month m has 31 days
//			  | DaysIn(m,y) 	| Returns the number of days in month m, year y
//			  | 				|  (accounting for February and leap years)
// **********************************************************************

#define IsLeap(y)	((y)%4==0 && ((y)%100 || (y)%400==0) )
#define Is30Days(m) ((m)==4 || (m)==6 || (m)==9 || (m)==11)
#define Is31Days(m) ((m)==1 || (m)==3 || (m)==5 || (m)==7 || (m)==8 || (m)==10 || (m)==12)
#define DaysIn(m,y) ( Is30Days(m) ?30 :((m)==2 ?28+IsLeap(y) :31) )

//+*****************************************************************************
//
//	  CLASS:	   bDate
//
//	  DESCRIPTION:
//		Keep track of the number of days since 1 AD.
//		(Discounting the change from Julian to Gregorian calendars)
//
//		Dynamic string formatting according to a description string
//		using characters similar to printf formatting characters.
//
//			+Format +Description
//			| %a	| Abbreviated weekday name
//			| %A	| Full weekday name
//			| %b	| Abbreviated month name
//			| %B	| Full month name
//			| %c	| Country dependent date
//			| %d	| Day of the month as a decimal number (01-31)
//			| %j	* Day of the year as a decimal number (000-365)
//			| %m	| Month as a decimal number (01-12)
//			| %r	| date separator is next charater
//			| %U	* Week of year (full weeks starting with Sunday)
//			| %w	* Weekday as a decimal number (0-6; Sunday is 0)
//			| %W	* Week of year (full weeks starting with Monday)
//			| %y	| Year without the century as a decimal number (00-99)
//			| %Y	| Year with the century as a decimal number
//			| %%	| Percent sign
//						(* not used in input)
//
//		In constructors and Set methods taking a character pointer for date
//		value, a NULL pointer may be used to indicate the current date.
//		Otherwise the value string must conform to the format string.
//		A NULL Format string uses the default country format.
//
//		A long cast and math operators are provided to use bDate as the
//		number of days since 1/1/0000.
//
//-*****************************************************************************

#define TsToday (const char*)0

class _EXPORT_ bDate
{
	protected:
		schar	days;		// 0-x
		schar	months; 	// 0-11
		short	years;

		void	AddMonths(schar m);
		void	AddDays(schar d);
		int 	parse(const char*& date, const char*& fmt, char* seps);
		int 	format(const char*& fmt, char*& buffer, char* seps) const;
		static int build(char*& mask, const char*& fmt, char* seps);

	public:
		bDate();
		bDate(ushort y, uchar m, uchar d) { Year(y); Month(m); Day(d); }
		bDate(const char* date, const char* fmt= 0);

		bDate(const bDate& time);
		bDate& operator= (const bDate& time);

		// is this a valid date?
		bool	IsValid() const;
		void	SetInvalid()		{ months= 12; }

		// accessesors
		long	Ordinal()   const;	// days from 0
		uchar   Day()		const	{ return uchar(days+1); }
		uchar   Month()	    const	{ return uchar(months+1); }
		ushort  Year() 	    const	{ return ushort(years+1); }

		 // setters
		void	Ordinal(long d);
		void	Day(uchar d) 	    { days= uchar(d-1); }
		void	Month(uchar m)	    { months= uchar(m-1); }
		void	Year(ushort y)	    { years= ushort(y-1); }
		void	SetDate(ushort y, uchar m, uchar d) { Year(y); Month(m); Day(d); }
		bool	SetDate(const char* date= 0, const char* fmt= 0 );
		bDate&	operator= (const char* date) { SetDate(date); return *this; }

        void    SetSystem();

		// Formatters
		static bString BuildMask(const char* fmt);
		bString  Format(const char* fmt = 0) const;
		operator bString()	const	{ return Format(); }

		// other information
		bool    IsLeapYear() const	{ return IsLeap(years+1); }
		ushort  DayOfYear() const; 	    // returns 0-365
		uchar   DaysInMonth() const;	// returns 28,30,31

		uchar   FirstDayOfYear(uchar dayOffset=0) const;  // returns 0-6
		uchar   DayOfWeek(uchar dayOffset=0) const; 	  // returns 0-6
		uchar   WeekDay() const {return DayOfWeek(0);}
		uchar   WeekOfYear(uchar dayOffset=0) const;	  // returns 0-51
		uchar   WeekOfYearFromSunday() const {return WeekOfYear(0);}
		uchar   WeekOfYearFromMonday() const {return WeekOfYear(1);}

		// Comparison
		int 	Compare(const bDate& dt) const;
		bool	operator== (const bDate& dt) const { return Compare(dt)==0; }
		bool	operator!= (const bDate& dt) const { return Compare(dt)!=0; }
		bool	operator>= (const bDate& dt) const { return Compare(dt)>=0; }
		bool	operator<= (const bDate& dt) const { return Compare(dt)<=0; }
		bool	operator>  (const bDate& dt) const { return Compare(dt)>0; }
		bool	operator<  (const bDate& dt) const { return Compare(dt)<0; }

		// Math
 friend bDate operator+ ( const bDate& d, const bDeltaDate& dd );
 friend bDate operator- ( const bDate& d, const bDeltaDate& dd );
 friend bDeltaDate operator- ( const bDate& d, const bDate& dd );

		bDate&	operator+= ( const bDeltaDate &dd );
		bDate&	operator-= ( const bDeltaDate &dd );

		bDate& operator+= (long days);
		bDate& operator-= (long days)   { return operator+=(-days); }
		bDate& operator++ (int)         { return operator+=(1); }
		bDate& operator-- (int)         { return operator-=(-1); }
};

// DB2 Formats
#define DATE_DB2_ISO_FORMAT "%r-%4Y-%m-%d"    // DB2 ISO date
#define DATE_DB2_USA_FORMAT "%r/%m/%d/%4Y"    // DB2 USA date
#define DATE_DB2_EUR_FORMAT "%r.%d.%m.%4Y"    // DB2 EUR date
#define DATE_DB2_JIS_FORMAT "%r-%4Y-%m-%d"    // DB2 JIS date
#define DATE_DB2_FORMAT 	DATE_DB2_USA_FORMAT // Default DB2 date

//+*****************************************************************************
//
//	  CLASS:	   bTimeStamp
//	  INHERITANCE: bTime, bDate
//
//	  DESCRIPTION:
//
//		Look at bTime and bDate for capabilities
//
//-*****************************************************************************

class _EXPORT_ bTimeStamp : public bTime, public bDate
{
	public:
		bTimeStamp() {}
		bTimeStamp( const char* datetime, const char* fmt= 0 );
		bTimeStamp( short y, schar m, schar d, schar h, schar mi, schar s, schar hu= 0)
			: bTime(h, mi, s, hu), bDate(y, m, d) {}

		bTimeStamp(const bTimeStamp& time);
		bTimeStamp& operator= (const bTimeStamp& time);

		// accessesor
		long	Ordinal() const;	// hundreths of seconds from 1/1/1 

		// setters
		void	Ordinal(long hs);
		void	Set( short y, schar m, schar d, schar h, schar mi, schar s= 0, schar hu= 0)
			{ bTime::SetTime(h,mi,s,hu); bDate::SetDate(y,m,d); }
		bool	SetTime(const char* datetime= 0, const char* fmt= 0 );
		bTimeStamp&  operator= (const char* ts) { SetTime(ts); return *this; }

        void    SetSystem();

		// Formatters
		static bString BuildMask(const char* fmt);
		bString  Format(const char* fmt = 0) const;
		operator bString()	const	{ return Format(); }

		// is this a normalized timestamp?
		bool	IsValid()	const	{ return bTime::IsValid() && bDate::IsValid(); }
		long	Normalize();

		// Comparison
		int 	Compare(const bTimeStamp& ts) const;
		bool	operator== (const bTimeStamp& ts) const { return Compare(ts)==0; }
		bool	operator!= (const bTimeStamp& ts) const { return Compare(ts)!=0; }
		bool	operator>= (const bTimeStamp& ts) const { return Compare(ts)>=0; }
		bool	operator<= (const bTimeStamp& ts) const { return Compare(ts)<=0; }
		bool	operator>  (const bTimeStamp& ts) const { return Compare(ts)>0; }
		bool	operator<  (const bTimeStamp& ts) const { return Compare(ts)<0; }

		// Math
 friend bTimeStamp operator+ ( const bTimeStamp& ts, const bDeltaTimeStamp& dts );
 friend bTimeStamp operator- ( const bTimeStamp& ts, const bDeltaTimeStamp& dts );
 friend bDeltaTimeStamp operator- ( const bTimeStamp& ts, const bTimeStamp& dts );

		bTimeStamp& operator+= ( const bDeltaTimeStamp &ts ); // this += DT
		bTimeStamp& operator-= ( const bDeltaTimeStamp &ts ); // this -= DT
};

// Default DB2 timestamp
#define TS_DB2_FORMAT	"%r-%4Y-%2m-%2d-%R.%2H.%2M.%2S.%6h"

#define TsCountryDate	"%c"
#define TsCountryTime	"%C"
#define TsCountryDateTime "%c %C"

//+*****************************************************************************
//
//	  CLASS:	   bDeltaTime
//	  INHERITANCE: bTime
//
//	  DESCRIPTION:
//
//		  Similar to a bTime but signifies a time difference rather than
//		  an absolute time.  As such, its methods are somewhat different and
//		  it is used in time arithmetic.
//
//	  COMMENTS:
//
//-*****************************************************************************

class _EXPORT_ bDeltaTime : public bTime
{
	public:
		bDeltaTime(short h, schar mi, schar s, schar hu= 0) : bTime(h,mi,s,hu) {}

		bool	IsPositive() const	{return Ordinal()>0;}
		bool	IsZero() const;
		bool	IsNegative() const	{return Ordinal()<0;}

		   // return difference expressed in particular unit
		long	TotalHours() const	{return hours;}
		long	TotalMinutes() const {return hours*60+minutes;}
		long	TotalSeconds() const {return TotalMinutes()*60+seconds;}
		long	TotalHundredths() const {return TotalSeconds()*100+hundredths;}
};

// Major time zone constants
#define TIME_GREENLAND		(180)	// 3 hours west 	   // US/Canada
#define TIME_NEWFOUNDLAND	(210)	// 3:30 hours west
#define TIME_ATLANTIC		(240)	// 4 hours west
#define TIME_EASTERN		(300)	// 5 hours west
#define TIME_CENTRAL		(360)	// 6 hours west
#define TIME_MOUTAIN		(420)	// 7 hours west
#define TIME_PACIFIC		(480)	// 8 hours west
#define TIME_ALASKA 		(540)	// 9 hours west

#define TIME_ATHENS 		(-60)	// 1 hour east? 	   // Major cities
#define TIME_BEIJING		(-480)	// 8 hours east
#define TIME_BERLIN 		(-60)	// 1 hour east
#define TIME_CHICAGO		(360)	// 6 hours west
#define TIME_GREENWICH		(0) 	// The famed Greenwich Mean Time
#define TIME_LONDON 		(0) 	// Same as Greenwich
#define TIME_LOSANGELES 	(480)	// 8 hours west
#define TIME_NEWYORK		(300)	// 5 hours west
#define TIME_MOSCOW 		(-180)	// 3 hours east
#define TIME_PARIS			(-60)	// 1 hour east
#define TIME_ROME			(-60)	// 1 hour east
#define TIME_SYDNEY 		(-600)	// 10 hours east
#define TIME_TOKYO			(-540)	// 9 hours east
#define TIME_WASHINGTON 	(300)	// 5 hours west
#define TIME_RIODEJANEIRO	(180)	// 3 hours west

//+*****************************************************************************
//
//	  CLASS:	   bDeltaDate
//	  INHERITANCE: bDate
//
//	  DESCRIPTION:
//
//		Similar to a bDate, but signifies a date difference rather than
//		an absolute date.  As such, its methods are somewhat different and
//		it is used in date arithmetic.
//
//	  COMMENTS:
//
//-*****************************************************************************

class _EXPORT_ bDeltaDate : public bDate
{
	public:
		bDeltaDate( short y, schar m, schar d) { years= y; months= m; days= d; }

		void	SetDate(short y, schar m, schar d) { years= y; months= m; days= d; }

		bool	IsPositive() const	{return Ordinal()>0;}
		bool	IsZero() const;
		bool	IsNegative() const	{return Ordinal()<0;}

		   // return difference expressed in particular unit
		long	TotalYears() const	{return years;}
		long	TotalMonths() const {return years*12+months;}
		long	TotalDays() const	{return Ordinal();}
};

//+*****************************************************************************
//
//	  CLASS:	   bDeltaTimeStamp
//	  INHERITANCE: bTimeStamp
//
//	  DESCRIPTION:
//
//		Similar to a bTimeStamp, but signifies a time difference rather than
//		an absolute time.  As such, its methods are somewhat different and
//		it is used in timestamp arithmetic.
//
//	  COMMENTS:
//
//-*****************************************************************************

class _EXPORT_ bDeltaTimeStamp : public bDeltaTime, public bDeltaDate
{
	public:
		bDeltaTimeStamp( short y, schar m, schar d, schar h, schar mi, schar s, schar hu= 0)
			: bDeltaTime(h, mi, s, hu), bDeltaDate(y, m, d) {}

		void	Set( short y, schar m, schar d, schar h, schar mi, schar s= 0, schar hu= 0)
			{ bDeltaTime::SetTime(h,mi,s,hu); bDeltaDate::SetDate(y,m,d); }
		bool	IsPositive() const;
		bool	IsZero() const {return bDeltaDate::IsZero() && bDeltaTime::IsZero();}
		bool	IsNegative() const;
};

#pragma pack()

int cmp_BDATE(const bDate *, const bDate *b);
int cmp_BTIME(const bTime *a, const bTime *b);
int cmp_BTIMESTAMP(const bTimeStamp *a, const bTimeStamp *b);

// some compatibility defines
#define TS_NOW TsNow
#define TS_TODAY TsToday
#define FormatAs Format

//+*****************************************************************************
//
//	  CLASS:	   bTimer
//
//	  DESCRIPTION:
//
//      High precision timer used to measure code speed   
//
//	  COMMENTS:
//
//-*****************************************************************************

struct bQuadWord;

extern "C" bQuadWord EXPENTRY AddQuad(const bQuadWord& l, const bQuadWord& r);
extern "C" bQuadWord EXPENTRY SubQuad(const bQuadWord& l, const bQuadWord& r);
extern "C" void EXPENTRY DoubleQuad(double* d, const bQuadWord* r);
extern "C" void EXPENTRY QuadDouble(bQuadWord* r, const double* d);

struct bQuadWord
{
    ulong   lower;
    ulong   higher;
    operator double() {double d; DoubleQuad(&d, this); return d;}
    bQuadWord& operator= (double d) {QuadDouble(this, &d); return *this;}
};

inline bQuadWord operator+(const bQuadWord& l, const bQuadWord& r) {return AddQuad(l, r);}
inline bQuadWord operator-(const bQuadWord& l, const bQuadWord& r) {return SubQuad(l, r);}

class bTimer
{
    static ulong tps;
    bQuadWord   start;

public:
    bTimer();               // start timer

    bQuadWord   Elapsed();  // return lapsed time
    bQuadWord   Lap();      // return lapsed time and reset timer

    static  ulong TicsPerSecond();
    static  double Seconds(bQuadWord tics);
};

#endif // __TIMESTMP_HPP
