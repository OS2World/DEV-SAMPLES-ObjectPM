/*  VCS_ID
 *  $Filename:   app.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __APP_HPP
#define __APP_HPP

#define HmShadow	  1
#define HmExec  	  2

class _EXPORT_ bModule
{
private:
	HMODULE hmod;
	bool flags;

public:
	bModule(const char *modName);
	bModule(HMODULE hmod);
	~bModule();

	HMODULE hModule() const		{ return hmod; }
    operator HMODULE() const    { return hmod; }
	bool	IsShadow() const	{ return flags & HmShadow; }
	bool    IsExecutable() const { return flags & HmExec; }
#ifndef BaseSetLite
	bString GetName() const;
	bFileName *GetFullFileName() const;
#endif
};

class _EXPORT_ bFormat
{
    bString fileName;
public:
    bFormat(const char* file) : fileName(file) {}
    bString Print(ulong msg, ...) const;
    static bString Print(const char* fmt, ...) ;
};

class _EXPORT_ bFacility
{
	private:
		bString name, msgFile, helpFile;
		ushort fac, helpOffset;

	public:
		bFacility();
		bFacility(ushort fac, const char *name, const char *fn = 0);
		virtual ~bFacility();
 
		void    SetName(const char *n)      { name=n; }
		void    SetFacilityId(ushort f)     { fac= f; }
		void	SetMsgFilename(const char *fn) { msgFile= fn; }
		void	SetHelpFilename(const char *fn, ushort o) { helpFile= fn; helpOffset= o; }
		bString GetName()			  		{ return name;     }
		bString GetMsgFilename()			{ return msgFile;  }
		ushort  GetFacilityId()				{ return fac;	   }
		bString GetHelpFilename()			{ return helpFile; }
		ushort  GetHelpPanelOffset()		{ return helpOffset; }
		virtual bool FormatConditionString(bCondition *c, char *dest, ushort bufsize);
};

class dtInfo;

class _EXPORT_ bApp : private bProcess
{
	private:
		bDictionary *appDictionary;
        tDList<bFacility>* facilities;
        tDList<dtInfo>* ftypes;
		bCountry	*country;
        bModule     *resource;

		friend class bThread;
		void InitFieldTypes();

	public:
		bApp();
		~bApp();

        const char* ProcessName() const {return bProcess::ProcessName();} 
        PID        GetPid() {return bProcess::GetPid();}
        void       SetPriority(int delta, BOOL scope= FALSE){bProcess::SetPriority(delta, scope);}
        void       Kill()   {bProcess::Kill();}
        void       Signal(BOOL intr_break= FALSE) {bProcess::Signal(intr_break);}

		bDictionary *ObjectDictionary() { return appDictionary; }
		void 	  *GetObject(const char *objName);
		void 	  *RemoveObject(const char *objName);
		bool       PutObject(const char *objName, void *object);

        bModule   *ResourceModule();
        bModule   *SetResourceCurrent();

		bModule   *GetCurrentModule();
		void	   SetCurrentModule(bModule *mod);
		void 	   SetCurrentMsgFile(const char *msgf);
		bString    GetCurrentMsgFile();

		bool  	   AddFieldDataType(fDataType *fdt, bModule *mod = NULL);
		fDataType *GetFieldDataType(ushort id);
		bModule	  *GetFieldModule(ushort id);

		void       AddFacility(bFacility *fac);
		bFacility *GetFacility(ushort facId);
		bCountry  *GetCountry()						{ return country; }
		bool       SetCodePage(bCodePage cp);
		static void Beep(ulong freq = 500L, ulong durMSecs = 500L);
        static bool Alarm(AlarmType t);
};

bModule *GetResourceModule();

#if defined(BUILDLIB)
extern HMODULE bseHMODULE;
#endif

extern "C" void EXPENTRY wpInitObjectPM(HAB hab);

bApp*   AppPointer();
#define ThisApp         (AppPointer())
#define GetCurrentSetResource (ThisApp->SetResourceCurrent())
#define CurrentModule   (ThisApp->GetCurrentModule())
#define CurrentMsgFile  (ThisApp->GetCurrentMsgFile())

class _EXPORT_ bSound 
{
public:
    bSound(const char *name, bool sync= 0);
    bSound(HMODULE module, ulong resId, bool sync= 0);

    static void Stop();   
};

#endif // __APP_HPP
