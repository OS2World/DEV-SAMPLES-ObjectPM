/*  VCS_ID
 *  $Filename:   money.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   
 *  $Date:   
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __MONEY_HPP
#define __MONEY_HPP

class _EXPORT_ bMoney
{
	private:
		long m;
		short Parse(const char *s, bool fUpdate);

	public:
		bMoney()								{ m = 0;   }
		bMoney(long val)						{ m = val; }
		bMoney(const char *strVal);
		bMoney(bMoney& n)						{ m = n.m; }

		bMoney&	 operator=(const bMoney&n)		{ m = n.m; return *this;  } 
		bMoney&  operator=(long val)			{ m = val; return *this;  }
		bMoney&  operator=(const char *val);
		bMoney   operator-() const		        { return bMoney(-m); }
		int      operator!() const				{ return m != 0L;         }
		bMoney&  operator+=(const bMoney&n)		{ m += n.m; return *this; }
		bMoney&  operator-=(const bMoney&n)		{ m -= n.m; return *this; }
		operator bString() const;
		operator long() const					{ return m;				  }
		bMoney   operator+(const bMoney&) const;
		bMoney   operator+(long l) const;
		bMoney   operator-(const bMoney&) const;
		bMoney   operator-(long l) const;
		int      operator==(const bMoney&) const;
		int      operator==(long l) const;
		int      operator!=(const bMoney&) const;
		int      operator!=(long l) const;
		int      operator<(const bMoney&) const;
		int      operator<(long l) const;
		int      operator>(const bMoney&) const;
		int      operator>(long l) const;
		int      operator<=(const bMoney&) const;
		int      operator<=(long l) const;
		int      operator>=(const bMoney&) const;
		int      operator>=(long l) const;

		bString  Format(ushort opts) const;
		long	 Dollars() const;
		ushort 	 Cents() const;
		short 	 IsStringValid(const char *strVal) const;
		short	 SetValue(const char *strVal);
		void	 SetValue(long l)				{ m = l; }
};

// return codes from IsStringValid() && SetValue

#define MeOk				0
#define MeFormat			39
#define MeTooLarge			37

// option flags to Format()

#define MfParenNeg			1
#define MfThousandsSep		2
#define MfShowSign			4
#define MfInclCurrencyInd	8

int cmp_BMONEY(const bMoney *a, const bMoney *b);

#endif // __MONEY_HPP
