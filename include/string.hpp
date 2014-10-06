/*  VCS_ID
 *  $Filename:   string.hpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.2  $
 *  $Date:   10 Sep 1992 18:28:00  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __STRING_HPP
#define __STRING_HPP

extern "C" {
	#include <string.h>
}

// usefull functions/macros for apps...

char* cdecl _nlsStrlwr(char *cp);
char* cdecl _nlsStrupr(char *cp);

/*
 * bUChar
 * This class represents a characters as single or double-byte.  All
 * comparison and case-mapping methods fully support multi-national 
 * character sets.  The bString classes uses this class to provide similar
 * level of support on character strings
 */ 										

class _EXPORT_ bUChar
{
	public:
		unsigned char c1, c2;

		bUChar()						{ c1 = 0; 		 	  	    }
		bUChar(char c)					{ c1 = c; 		  			}
		bUChar(ushort dc)				{ *((ushort *)this) = dc; 	}
		bUChar(char _c1, char _c2)		{ c1 = _c1; c2 = _c2;	  	}

		bool    IsDoubleByte();
		int     Compare(bUChar c);
		int     Compare(unsigned char c);
		int     ICompare(bUChar c);
		int     ICompare(unsigned char c);

		int operator==(bUChar& u)		{ return Compare(u) == 0;	}
		int operator!=(bUChar& u)		{ return Compare(u) != 0;	}
		int operator<(bUChar& u)		{ return Compare(u) < 0;	}
		int operator>(bUChar& u)		{ return Compare(u) > 0;	}
		int operator<=(bUChar& u)		{ return Compare(u) <= 0;   }
		int operator>=(bUChar& u)		{ return Compare(u) >= 0;   }

		int operator==(char c)			{ return Compare(c) == 0;	}
		int operator!=(char c)			{ return Compare(c) != 0;	}
		int operator<(char c)			{ return Compare(c) < 0;	}
		int operator>(char c)			{ return Compare(c) > 0;	}
		int operator<=(char c)			{ return Compare(c) <= 0;   }
		int operator>=(char c)			{ return Compare(c) >= 0;   }
		operator char()					{ return (char)c1;			}

		bUChar& operator=(char c);
		bUChar& operator=(ushort c);

		void   SetToUpper();
		bUChar ToUpper();
		bool   IsUpper();	
		void   SetToLower();
		bUChar ToLower();
		bool   IsLower();	
};

#ifdef __WATCOMC__
bool _nlsIsupper(char c);
bool _nlsIslower(char c);
bUChar _nlsToupper(char c);
bUChar _nlsTolower(char c);
bool _nlsIsDoubleByteLead(char c);
#else
#define _nlsIsupper(c)	 (((bUChar&)c).IsUpper())
#define _nlsIslower(c)  (((bUChar&)c).IsLower())
#define _nlsToupper(c)  (((bUChar&)c).ToUpper())
#define _nlsTolower(c)  (((bUChar&)c).ToLower())
#define _nlsIsDoubleByteLead(c)   (((bUChar&)c).IsDoubleByte())
#endif

/*
 * bUCharPtr
 * This class implements a pointer object used to traverse character
 * strings that contain both single and double-byte characters.	 It has been
 * designed so that the useage syntax is identical to that of using normal
 * char *'s for string traversal.
 *
 */ 										

class _EXPORT_ bUCharPtr
{
	private:
		bUChar *cp;

	public:
		bUCharPtr()						{ cp = NULL;				}
		bUCharPtr(const char *p)		{ cp = (bUChar *)p;   		}
		bUCharPtr(bUChar *p)			{ cp = p;					}

		bUCharPtr& operator++(int) 		{ cp = cp->IsDoubleByte()? cp + 1: (bUChar *)(((char *)cp) + 1); return *this;  }
		bUCharPtr& operator++()			{ cp = cp->IsDoubleByte()? cp + 1: (bUChar *)(((char *)cp) + 1); return *this;  }
		bUCharPtr& operator--(int)		{ cp--; if (cp->IsDoubleByte()) cp = (bUChar*)((char *)cp) + 1;	return *this;  }
		bUCharPtr& operator--()			{ cp--; if (cp->IsDoubleByte()) cp = (bUChar*)((char *)cp) + 1;	return *this;  }
		bUCharPtr& operator=(const char *c)   { cp = (bUChar *)c;	return *this; }

		void operator+=(long l);
		void operator-=(long l);
		bUCharPtr operator+(long l) const;
		bUCharPtr operator-(long l) const;
		bUChar&   operator*() const		{ return *cp; 				}
		operator  const char*()	const	{ return (const char *)cp; 	}

		ulong Length();
		ulong CharCount();
};


enum bStringOpt
{
	StNone,
	StIgnoreCase = 0x2000,
	StFixedSize	 = 0x0800
};

#define StringLen	(-1)
class bModule;

class _EXPORT_ bString
{
	public:
		bString(); 
		bString(const char *);
		bString(const char *, ulong maxLen);
		bString(const bString&);
		bString(ushort resId, bModule* mod= 0);
		bString(ushort msgno, ushort maxsize, const char **replace, 
			    ushort numreplace=0, const char *msgfile=NULL);

		void  SetOption(bStringOpt opt, bool fSet = TRUE);
		bool  GetOption(bStringOpt opt);

		bString& operator=( const bString& );
		bString& operator=( const char * );
		bString& operator+=( const bString& );
		bString& operator+=( const char * );
		bString  operator+( const bString& ) const;
		bString  operator+( const char *s2 ) const;

		bString& Set(const char *str, long len = StringLen);
		char	*CopyTo(char *dest, long len = StringLen, bool fTerm = TRUE) const;
		bString& ReplaceSubString(char *dest, const char *sstr, long len = StringLen);
		bString& ReplaceSubString(ulong indx, const char *sstr, long len = StringLen);
		bString  GetSubString(const char *start, long len = StringLen) const;
		bString  GetSubString(ulong indx, ulong len = StringLen) const;

		~bString();

		operator const char*() const;
        operator bUCharPtr() const;
		bUChar operator[](int i) const;

		ulong Length() const;
		ulong CharCount() const;
		ulong BufferSize() const;
		void  AdjustLength(ulong l) const;
		bool  IsBlank() const;

		int Compare(const char *str, int n = (-1)) const;
		int ICompare(const char *str, int n = (-1)) const;
		int cCompare(const char *str) const;

		int operator >=( const char *s2 ) const {return cCompare(s2)>=0;}
		int operator > ( const char *s2 ) const {return cCompare(s2)> 0;}
		int operator ==( const char *s2 ) const {return cCompare(s2)==0;}
		int operator < ( const char *s2 ) const {return cCompare(s2)< 0;}
		int operator <=( const char *s2 ) const {return cCompare(s2)<=0;}
		int operator !=( const char *s2 ) const {return cCompare(s2)!=0;}

		int operator >=( const bString& s2 ) const {return cCompare(s2)>=0;}
		int operator > ( const bString& s2 ) const {return cCompare(s2)> 0;}
		int operator ==( const bString& s2 ) const {return cCompare(s2)==0;}
		int operator < ( const bString& s2 ) const {return cCompare(s2)< 0;}
		int operator <=( const bString& s2 ) const {return cCompare(s2)<=0;}
		int operator !=( const bString& s2 ) const {return cCompare(s2)!=0;}

		void SetToUpper();
		void SetToLower();

	private:

		class bStringRep   // singleton letter class to hold string 
		{				   // and reference count
			friend class bString;

			public:
				bStringRep() { count=1; s[0] = '\0'; }

			private:
				ushort count;			// reference count
				char   s[1]; 			// first byte of string array
		} *rep;

		bString( bStringRep *r )	{ rep = r; }
		void cat(bStringRep **rep, const char *str, long len, bool isLocal, bool fReplace) const;
};

typedef tDList<bString> bStringList;
int cmp_BSTRING(const bString *a, const bString *b);
int cmpi_BSTRING(const bString *a, const bString *b);

#endif // __STRING_HPP
