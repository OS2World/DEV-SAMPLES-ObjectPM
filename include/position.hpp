/*  VCS_ID
 *  $Filename:   position.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   10 Dec 1991 17:09:10  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __POSITION_HPP
#define __POSITION_HPP

class _EXPORT_ bPosition	
{
	public:
		bPosition() 					{ ypos = 0; xpos = 0; }
		bPosition( short y, short x ) 	{ ypos = y; xpos = x; }
		short &x()                    	{ return xpos; }
		short &y()                    	{ return ypos; }
		bPosition operator+ (bPosition& other) 
			{ return bPosition(ypos+other.ypos,xpos+other.xpos); }

		void operator+= (bPosition p)	{ xpos += p.xpos; ypos += p.ypos; }
		void operator-= (bPosition p)	{ xpos -= p.xpos; ypos -= p.ypos; }
		int  operator== (bPosition p)	{ return xpos == p.xpos && ypos == p.ypos; }
		int  operator!= (bPosition p)	{ return xpos != p.xpos || ypos != p.ypos; }

	private:
		short xpos;
		short ypos;
};

#endif // __POSITION_HPP
