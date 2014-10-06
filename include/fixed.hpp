/*  VCS_ID
 *  $Filename:   fixed.hpp
 *  $Author  :   Miguel Zubizarreta 
 *  $Revision:   1.3  $
 *  $Date:   10 Dec 1991 17:14:54  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __FIXED_HPP
#define __FIXED_HPP

class _EXPORT_ wFixed 
{
private:
    long    value;

public:

	wFixed()                            { value=0; }
    wFixed(int n)                       { value= (long)n << 16; }
    wFixed(double d);

    wFixed& operator=(int n)		    { value= (long)n << 16; return *this; }
    wFixed& operator=(double d);

	operator long() const               { return value; }
	operator double() const;

    friend int operator==( const wFixed& l, const wFixed& r) {return l.value==r.value;}
    friend int operator!=( const wFixed& l, const wFixed& r) {return l.value!=r.value;}
    friend int operator> ( const wFixed& l, const wFixed& r) {return l.value> r.value;}
    friend int operator>=( const wFixed& l, const wFixed& r) {return l.value>=r.value;}
    friend int operator< ( const wFixed& l, const wFixed& r) {return l.value< r.value;}
    friend int operator<=( const wFixed& l, const wFixed& r) {return l.value<=r.value;}

    friend wFixed operator-( const wFixed& r );
    friend wFixed operator+( const wFixed& l, const wFixed& r);
    friend wFixed operator-( const wFixed& l, const wFixed& r);
    friend wFixed operator*( const wFixed& l, const wFixed& r);
    friend wFixed operator/( const wFixed& l, const wFixed& r);

#ifndef ObjectPMLite
    friend wFixed Sin(const wFixed& angle);
    friend wFixed Cos(const wFixed& angle);
#endif
};

#endif // __FIXED_HPP
