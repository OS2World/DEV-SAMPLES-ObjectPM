/*  VCS_ID
 *  $Filename:   thread.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __THREAD_HPP
#define __THREAD_HPP

#ifndef __PMTYPES_HPP
class wWindowClass;
class wHelpManager;
#endif

extern "C"
{
    typedef void EXPENTRY InitFnc(HAB, bool);
    typedef void EXPENTRY UnInitFnc();
    typedef void EXPENTRY QuitFnc(bThread *, short, bool);

    typedef InitFnc*    pInitFnc;
    typedef UnInitFnc*  pUnInitFnc;
    typedef QuitFnc*    pQuitFnc;

    extern  pInitFnc    pInitThread;
    extern  pUnInitFnc  pUnInitThread;
    extern  pQuitFnc    pQuitThread;

    extern  InitFnc     wmInitThread;
    extern  UnInitFnc   wmUnInitThread;
    extern  QuitFnc     wmQuitThread;
}
extern  HMODULE rscHMODULE;
void    EXPENTRY SetOpmModule(HMODULE);

extern char* flattenEnv(const char* env[], char pad= 0);

#define PrtycIdleTime		0
#define PrtycNoChange		1
#define PrtycRegular		2
#define PrtycTimeCritical	3
#define PrtycForegroundServer	4

class wWindow;

class _EXPORT_ bThread : public bEventListener
{
    tNameNode< bThread > link;
    static  tNameList< bThread > chain;
    static  bEventSemaphore threadSync;
    static  bMutexSemaphore semOwner;

    tSList< bCondition > condList;
    tSList< bConditionHandler > condHandlers;
    tSList< bExceptionHandler > exceptHandlers;
public:
	tNameList< wWindowClass > classInfo;
	wWindow *pFirst;
	wWindow *pLast;
	wWindow *pCreate;
private:
	bThread*        parent;
	short           exitCode;
	wHelpManager*   helpMan;

	friend void     _Optlink InitThread(bThread *thd);
    static bCondition* dispatchCondition(bCondition* c, void* thread);
    friend ulong APIENTRY exceptionCatch(struct _EXCEPTIONREPORTRECORD*, struct _EXCEPTIONREGISTRATIONRECORD*, struct _CONTEXT*, void*);
protected:
	long            flags;
	HAB             hab;
	HMQ             hmq;
	void*           threadArg;
public:
    // register an already created thread
    bThread(ulong threadId, const char* name= 0);

    // next method is for compatibility only -- do not use for new programs
	bThread(bThread *parent, const char *name, void *arg = 0, ushort stacksize = 4096, bThreadResc resc = ThreadFull);
	virtual ~bThread();

    static  bThread* FindThread(TID t) { return chain.Find(t); }
    static  bThread* FindThread(const char* n)  { return chain.Find(n); }
    static  bThread* WorkingThread();
protected:
	bThread() : link(this) {}
    void    Init(const char *name, void *arg = 0, bThreadResc resc = ThreadFull, int stacksize = 4096, bThread *parent= bThread::WorkingThread());
    void    InitOpm();

public:
	wHelpManager*&  HelpInstance()  	{ return helpMan;   }
	HAB             Hab() const         { return hab;       }
	HMQ             Hmq() const			{ return hmq;       }
	short           ExitCode() const	{ return exitCode;	}
	bThread*        Parent() const		{ return parent;    }
	TID             ThreadId() const    { return link.Key();}
    const char*     ThreadName() const  { return link.Name();}

    bool            IsPrimaryThread();
	bool            IsActive();
	bool            IsAlive();
	bool            IsInMsgLoop();

    enum    PriorityClass
    {
        NoChange, IdleTime, Regular, TimeCritical, ForegroundServer
    };
    enum    PriorityDelta
    {
        Minimum= -31, Maximum= 31
    };
	ushort          SetPriority(short priorChg, PriorityClass pc = NoChange);
 	ushort          GetPriority();
	bool            Suspend();
	bool            Resume();
	static void     Sleep(ulong msecs);

    static bThread* WaitAnyThread(TID* =0);
    void            Wait();

    // following two methods are for backward compatability
	void    AddEventHandler(bConditionHandler *pEv, bool fPreempt = TRUE);
	bool    RemoveEventHandler(bConditionHandler *pEv);

    bExceptionHandler* AddExceptionHandler(ExceptionNum l, ExceptionNum h, bEventListener* tP, bExceptionMethod mP);
	bool            RemoveExceptionHandler(bExceptionHandler* pEv);

    bConditionHandler* AddConditionHandler(ulong t, bEventListener* tP, bConditionMethod mP, bool fPreempt = TRUE);
	bool            RemoveConditionHandler(bConditionHandler* pEv);

 	bCondition&     NewCondition(ushort fac, ulong ctyp, long code);
 	bCondition*     LastCondition(ulong ct = CtAll);
 	bCondition*     LastError() 	{ return LastCondition(CtError); }
 	ushort          Conditions(ulong ct = CtAll);
	ushort 	        Errors()		{ return Conditions(CtError); } 

	void            ClearConditions();
  	bool            ConditionNotify(ulong ct = CtAll, bool fMult = TRUE);
	short           LastPMError();

	virtual short   Start() = 0;
	void            Exec();
	void            Quit(bool fDestroySelf = FALSE);
};

inline 
bThread :: bThread(bThread *parent, const char *name, void *arg, ushort stacksize, bThreadResc resc)
    : link(this) {Init(name, arg, resc, stacksize, parent);}

#define CurrentThread   (bThread::WorkingThread())
#define ThisThread      (bThread::WorkingThread())

typedef ulong APIENTRY _EXCEPTIONHANDLER(struct _EXCEPTIONREPORTRECORD*,
    struct _EXCEPTIONREGISTRATIONRECORD*, struct _CONTEXT*, void*);

class _EXPORT_ bMainThread : public bThread
{
    struct Registration 
    {
        Registration* next;
        _EXCEPTIONHANDLER* handler;
        bThread* thread;
    } registration;

public:
	short argc;
	char **argv;
	bMainThread(short AppArgc, char **AppArgv, bThreadResc resc = ThreadFull, long qsize=0);
	~bMainThread();
	short Start();
};

class _EXPORT_ bProcess
{
public:
    enum ProcessTerm {
        Normal, HardError, Trap, KillProcess, Exception, NoStart };

    enum ProcessPriorityClass {
        NoChange, IdleTime, Regular, TimeCritical, ForegroundServer };

protected:
    tNameNode< bProcess > link;
    static tNameList< bProcess > chain;
    ulong   ResultCode;
    ProcessTerm Why;
    void    GetResults(ulong* result);

    bProcess();     // used by bSession, bApp - must call SetNameKey
    void    SetNameKey(const char* name, ulong key= 0);
    int     Start(const char* prgmName, const char* argv[]= 0, const char* Env[]= 0);

public:
    bProcess(const char* prgmName, const char* argv[]= 0, const char* Env[]= 0);
    bProcess(const char* prgmName, ulong pid);
    ~bProcess();

    const char* ProcessName() const {return link.Name();}
    PID     GetPid() const  {return link.Key();}

    void    SetPriority(int delta, BOOL scope= FALSE);
    void    Kill();
    void    Signal(BOOL intr_break= FALSE);

    bool    IsActive();
    ulong   Result();
    ProcessTerm Wait();

    static bProcess* FindProcess(PID pid) {return chain.Find(pid);}
    static bProcess* WaitAnyChild();
};

class _EXPORT_ bPipeProcess : public bProcess
{
public:
    bPipeProcess(HFILE* write_stdin, HFILE* read_stdout, HFILE* read_stderr,
        const char* prgmName, const char* argv[]= 0, const char* Env[]= 0);
};

class _EXPORT_ bSession : private bProcess
{
    static bool readQueue(bool nowait);

    ulong   sessionId;
public:
    bSession(const char* prgmName, const char* argv[]= 0, const char* Env[]= 0);
    ~bSession();

    const char* ProcessName() const {return bProcess::ProcessName();}
    PID     GetPid() const  {return bProcess::GetPid();}
    ulong   GetSid() const  {return sessionId;}

    void    Kill() {bProcess::Kill();}
    void    Signal(BOOL intr_break= FALSE) {bProcess::Signal(intr_break);}

    bool    IsActive();
    void    Wait();
    ulong   Result()        {Wait(); return ResultCode;}

    bool    Bond(bool b);
    bool    InSwitch(bool b);
    bool    Select();

    static bSession* FindSession(ulong sid);
};

#endif // __THREAD_HPP

