/*  VCS_ID
 *  $Filename:   profile.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.2  $
 *  $Date:   16 Dec 1991 12:59:40  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __PROFILE_HPP
#define __PROFILE_HPP

#define IniProfile	((HINI)0L)
#define IniUser		((HINI)-1L)
#define IniSystem	((HINI)-2L)

class _EXPORT_ bProfile
{
	private:
		bStringList *EnumProfileNames(const char *app);
	protected:
    	HINI hini;

	public:
    	bProfile(const char *profpath);
        bProfile(HINI h);
		~bProfile();
        
        bStringList *AppList()					{ return EnumProfileNames(0);   }
        bStringList *KeyList(const char *app)	{ return EnumProfileNames(app); }
		bool	AddApp(const char *app);

		bString GetKeyValue(const char *app, const char *key);
		bool	SetKeyValue(const char *app, const char *key, const char *val);

		long	GetKeyValue(const char *app, const char *key, long rc);
		bool	SetKeyValue(const char *app, const char *key, long val);

		byte *	GetKeyValue(const char *app, const char *key, byte *dest, ulong *cb);
		bool	SetKeyValue(const char *app, const char *key, byte *val, ulong cb);
};

#endif // __PROFILE_HPP
