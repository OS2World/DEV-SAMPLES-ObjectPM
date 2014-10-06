/*  VCS_ID
 *  $Filename:   dtype.hpp
 *  $Author  :   John Pompeii
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
//		This module contains the definition of the base class for all
//		field data types. 
//
//-*****************************************************************************

#ifndef __DTYPE_HPP
#define __DTYPE_HPP

// standard validation return codes

#define FrOk		 	0
#define FrToUpper		(-1)
#define FrToLower   	(-2)
#define FrStringTrunc	(-3)
#define FrInvalidType	32
#define FrInvalidChar	33
#define FrDateFormat	34
#define FrInvalidMDY	35
#define FrTimeFormat	36
#define FrNumTooLarge	37
#define FrInvalidFPFmt  38
#define FrInvalidCurrFmt 39


class _EXPORT_ fDataType
{
	protected:
		ushort id;

	public:
		fDataType();
		virtual ~fDataType();

		ushort GetID()   				{ return id; }
		void   SetID(ushort _id)	 	{ id = _id;	 }

		virtual short ValidateChar(bUChar c, const char *fmt) = 0;
		virtual short Validate(const char *s, const char *fmt) = 0;
 		virtual short SetFromString(const char *s, const char *fmt) = 0;
		virtual short SetFromNativeType(const void *v, bool fInitBlank) = 0;
		virtual short SetFromObject(const fDataType *obj) = 0;
		virtual short CopyToString(char *dest, short len, const char *fmt) = 0;
		virtual short CopyToNativeType(void *dest) = 0;
		virtual short CopyToObject(fDataType *obj) = 0;
		virtual bool  IsLessThan(fDataType *obj) = 0;
		virtual bool  IsGreaterThan(fDataType *obj) = 0;
		virtual bool  IsEqual(fDataType *obj) = 0;
		virtual fDataType *Copy() = 0;
		virtual bString    DefaultMask(const char *fmt, ushort fldlen);

		virtual bool IsNil() = 0;		
		void SetToNil()				{ SetFromString("", ""); }
};

/* 
 * Base class for character type fields.  This class provides
 * validation and case translation functions typical with character strings
 */

class _EXPORT_ fStringType : public fDataType
{
	protected:
		void ParseFmt(const char *fmt, ushort *flags);
		fDataType::id;

	public:
		short ValidateChar(bUChar c, const char *fmt);
		short Validate(const char *s, const char *fmt);
};

/*
 * field type for strings where the native type is bString
 *
 * valid picture strings include:
 *
 * 		%9	 Allow entry of numbers (0-9)
 *		%A	 Allow entry of characters (a-z)
 *		%X	 Allow all printable characters (default)
 *		%!	 Convert entered letters to upper case
 *		%~   Convert entered letters to lower case
 * 		%m   Edit mask (not supported yet)
 *		NULL Defaults to %X
 */

class _EXPORT_ fString : public fStringType, public bString
{
public:
	fString();
	~fString();

 	short SetFromString(const char *s, const char *fmt);
	short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
	short SetFromObject(const fDataType *obj);
	short CopyToString(char *dest, short len, const char *fmt);
	short CopyToNativeType(void *dest);
	short CopyToObject(fDataType *obj);
	bool  IsLessThan(fDataType *obj);
	bool  IsGreaterThan(fDataType *obj);
	bool  IsEqual(fDataType *obj);
	fDataType *Copy();

	bool IsNil();		
};

/*
 * field type for strings where the native type is char[] or char *
 *
 * valid picture strings are the same as fString
 */

class _EXPORT_ fCharArray : public fString
{
	public:
		fCharArray();

		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short CopyToNativeType(void *dest);
		fDataType *Copy();
};

/*
 * field type for characters where the native type is uchar
 *
 * valid picture strings are the same as fString
 */

class _EXPORT_ fChar : public fStringType
{
	private:
		unsigned char c;

	public:
		fChar();

 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();

		bool IsNil();		
};

/*
 * field type for strings where the native type is bString
 *
 * valid picture strings include:
 *
 *		%rlu Set true/false characters 
 *		%!	 Convert entered letters to upper case
 *		%~   Convert entered letters to lower case
 */

class _EXPORT_ fBool : public fChar
{
	private:
		unsigned char f, t;
		void ParseFmt(const char *fmt, ushort *flags);

	public:
		fBool();

		short ValidateChar(bUChar c, const char *fmt);
		short Validate(const char *s, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromObject(const fDataType *obj);
		short CopyToObject(fDataType *obj);
		fDataType *Copy();
};

/* 
 * time & date field classes.
 * Most of the guts of these classes are in the bTimeStamp class.
 * Refer to timestmp.hpp for a list of the valid format options
 */


class _EXPORT_ fDate : public fDataType, public bDate
{
	public:
		fDate();
		~fDate();

		short ValidateChar(bUChar c, const char *fmt);
		short Validate(const char *s, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();
		bString    DefaultMask(const char *fmt, ushort fldlen);

		bool IsNil();		
};


class _EXPORT_ fTime : public fDataType, public bTime
{
	public:
		fTime();
		~fTime();

		short ValidateChar(bUChar c, const char *fmt);
		short Validate(const char *s, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();
		bString    DefaultMask(const char *fmt, ushort fldlen);
		bool  IsNil();		
};

/* 
 * Base class for integer type fields.  This class provides
 * validation and case translation functions typical with integers
 */

class _EXPORT_ fIntegerType : public fDataType
{
	protected:
		void  ParseFmt(const char *fmt, ushort *flags, ushort *width, ushort *base);
		short PrepString(char *s, ushort flags, ushort base);
		fDataType::id;
		ushort iflags;

	public:
		short ValidateChar(bUChar c, const char *fmt);
		short Validate(const char *s, const char *fmt);
		bool  IsNil();		
};

/*
 * field type for integers where the native type is short or ushort
 *
 * valid picture strings include:
 *
 * 		%bn	 Set base (radix) where n = 2 to 36
 *		%wn	 Zero pad to width n
 *		%+	 Always display sign (+/-)
 *		%,	 Comma separate thousands for base 10 numbers
 *	    NULL Defaults to an unsigned base 10 integer
 */

class _EXPORT_ fShort : public fIntegerType
{
	private:
		short n;

	protected:
		fIntegerType::iflags;
		fIntegerType::id;

	public:
		fShort();
		fShort(short s);
		fShort(const fShort& s);

		short Validate(const char *s, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();

		operator short()				{ return n; }
		short    operator= (short);
};

class _EXPORT_ fUShort : public fShort
{
	public:
		fUShort();
		fUShort(ushort s);
		fUShort(const fUShort& s);
	
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);

		operator ushort()				{ return (ushort)(short)(*this); }
		ushort   operator= (ushort);
};

/*
 * field type for integers where the native type is long or ulong
 *
 * valid picture strings are the same as for fShort
 */

class _EXPORT_ fLong : public fIntegerType
{
	private:
		long  n;

	protected:
		fIntegerType::iflags;
		fIntegerType::id;

	public:
		fLong();
		fLong(long l);
		fLong(const fLong& l);

 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();

		operator long()				{ return n; }
		long     operator= (long);
};


class _EXPORT_ fULong : public fLong
{
	public:
		fULong();
		fULong(ulong l);
		fULong(const fULong& l);
	
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);

		operator ulong()			{ return (ulong)(long)(*this); }
		ulong    operator= (ulong);
};


/* 
 * Base class for decimal type fields.  This class provides
 * validation and case translation functions typical with money and
 * floating point numbers
 */

class _EXPORT_ fDecimalType : public fDataType
{
	protected:
		void  ParseFmt(const char *fmt, ushort *flags, short *prec);
		short PrepString(char *s, ushort flags);
		fDataType::id;

	public:
		short ValidateChar(bUChar c, const char *fmt);
};


/*
 * field type for floats where the native type is double
 *
 * valid picture strings include:
 *
 * 		%dn	 Sets the number of places to the right of the dp
 *		%z	 Keep trailing zeros (dp is always printed)
 *		%+	 Always display sign (+/-)
 *		%,	 Comma separate thousands for base 10 numbers
 *		%e	 Display in scientific notation form 
 */

class _EXPORT_ fDouble : public fDecimalType
{
	private:
		double n;
		bool  fNil;

	public:
		fDouble();
		fDouble(double d);
		fDouble(const fDouble& d);

		short Validate(const char *s, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();
		bool  IsNil();		

		operator double()				{ return n; }
		double   operator= (double);
};


/*
 * field type for money where the native type is bMoney
 *
 * valid picture strings include:
 *
 *		%+	 Always display sign (+/-)
 *		%,	 Comma separate thousands for base 10 numbers
 *		%(	 Use parenthesis to denote a negative number
 *		%$	 Include currency indicator
 */

class _EXPORT_ fMoney : public fDecimalType, public bMoney
{
	private:
		bool  fNil;

	public:
		fMoney();
		fMoney(long d);
		fMoney(const fMoney& d);

		short Validate(const char *s, const char *fmt);
		short ValidateChar(bUChar c, const char *fmt);
 		short SetFromString(const char *s, const char *fmt);
		short SetFromNativeType(const void *v, bool fInitBlank = FALSE);
		short SetFromObject(const fDataType *obj);
		short CopyToString(char *dest, short len, const char *fmt);
		short CopyToNativeType(void *dest);
		short CopyToObject(fDataType *obj);
		bool  IsLessThan(fDataType *obj);
		bool  IsGreaterThan(fDataType *obj);
		bool  IsEqual(fDataType *obj);
		fDataType *Copy();
		bool  IsNil();		
};



// standard abstract data types

#define FtString		1
#define FtMLString		2
#define FtChar          3
#define FtBool			4
#define FtDate			5
#define FtTime			6
#define FtShort			7
#define FtLong			8
#define FtUShort		9
#define FtULong			10
#define FtDouble		11
#define FtMoney		    12
#define FtLongMoney	    13
#define FtBCD		    14	
#define FtCharArray		15

#define FtUser          101		  /* types 1 - 100 reserved for ObjectPM */

#endif // __DTYPE_HPP
