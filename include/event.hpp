/*  VCS_ID
 *  $Filename:   event.hpp
 *  $Author  :   John Pompeii
 *  $Revision$   
 *  $Date$   
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __EVENT_HPP
#define __EVENT_HPP

enum  bEventType
{
	EvNull,
	EvWindowMsg,
	EvException,
	EvCondition,
	EvCommMsg
};

#define CtNull			0x00000000
#define CtError			0x00000001
#define CtWarning		0x00000002
#define CtGeneral		0x00000004

#define CtFatal 		0x00010000
#define CtSystem		0x00020000
#define CtAll			0xffff

enum bCondTerminator
{
	Tell,
	Remember
};

// Standard OS/2 / ObjectPM facilities

#define FacOS2Base    1
#define FacOS2PM      2  
#define FacObjectPM   3
#define FacObjComm    4
#define FacBaseSet	  5
#define FacWorkplace  6
#define FacSQLLib     7
#define FacCMLib	  8
#define FacIBMLan     9

// abstract base class for all classes that process events

class _EXPORT_ bEventListener
{
	virtual void trick();   // define in module to hold class instantiation  
};

// typedef for EventListener method
typedef long (bEventListener::*bEventMethod)();
#define EVENTMETHOD(cl,mt) ((bEventMethod)&cl::mt)

#define CONDITION(f, t, c) (ThisThread->NewCondition(f, t, c))
#define CONDITIONAT(f, t, c) ((ThisThread->NewCondition(f, t, c)).SetFileLocation(__FILE__, __LINE__))
#define ATLOC(m, i) .SetLocation(m, i)
#define ERRORS_EXIST (ThisThread->Errors())
#define NOTIFY ThisThread->ConditionNotify()
#define CLEARCONDITIONS ThisThread->ClearConditions()

#define MAX_CONDITIONS 32
#define COND_ARGSIZE  128

class _EXPORT_ bCondition
{
		friend class bThread;

        tSNode<bCondition> link;
		bThread* thd;
		
		ulong   condType;
		long    condCode;
		ushort  facility;
		ushort  module;
		ushort  instance;
		ushort  cArgs;

		ushort  nextArg;
		char    fileName[13];
		char    strArgs[COND_ARGSIZE];

		bCondition(ushort fac, ulong ctyp, long code);
		bCondition();
		void Set(ushort fac, ulong ctyp, long code);
public:
	    ulong   GetConditionType() const {return condType;}
	    ulong   GetType()     const {return condType;}
	    long    GetCode()     const {return condCode;}
		ushort  GetFacility() const {return facility;}
		ushort  GetModule()   const {return module;}
		ushort  GetInstance() const {return instance;}
		const char* GetFileName() const {return fileName;}
        bCondition* GetNext()   const;

		bool AddArgument(const char *arg);
		bCondition& SetLocation(ushort mod, ushort inst);
		bCondition& SetFileLocation(const char *fileName, ushort line);
		bCondition& operator= (bCondition &c);
		bCondition& operator<< (const char *str);
		bCondition& operator<< (long l);
		bCondition& operator<< (int i);
		bCondition& AtLoc(ushort mod, ushort inst); 
		void operator<< (bCondTerminator t);
		char** ArgPointers(char **argArray, ushort elements);
};

typedef long (bEventListener::*bConditionMethod)(bCondition*);
#define CONDITIONMETHOD(cl,mt) ((bConditionMethod)&cl::mt)

class _EXPORT_ bConditionHandler : public bEventListener
{
    friend class bThread;
    tSNode<bConditionHandler> link;
    virtual void trick();   // define in module to hold class instantiation  
    
    ulong   type;
    bool    tc;
	bEventListener* thisPtr;
	bConditionMethod methodPtr;
	bConditionHandler(ulong t, bEventListener* tP, bConditionMethod mP)
        :link(this) { tc= TRUE; type= t; thisPtr= tP; methodPtr= mP; }
public:
    // constructor for compatibility
	bConditionHandler(ulong t, bEventListener* tP, bEventMethod mP)
        :link(this) { tc= FALSE; type= t; thisPtr= tP; methodPtr= (bConditionMethod)mP; }
    long    Notify(bCondition* c)   {return (thisPtr->*methodPtr)(c);}
	ulong   GetConditionType() const {return type;}
};

// Access Types
#define At_Unknown  0
#define At_Read     1
#define At_Write    2
#define At_Execute  4
#define At_Space    8
#define At_Limit    0x10

enum ExceptionNum
{
    AccessViolation= 5,
    // Info[0] - AccessType, [1] - FaultAddr
    InPageError,
    // Info[0] - FaultAddr

    IllegalInstruction= 0x1C,
    InvalidLockSequence,

    NoncontinuableException= 0x24,
    InvalidDisposition,
    Unwind,
    BadStack,
    InvalidUnwindTarget,

    ArrayBoundsExceeded= 0x93,
    FloatDenormalOperand,
    FloatDivideByZero,
    FloatInexactResult,
    FloatInvalidOperation,
    FloatOverflow,
    FloatStackCheck,
    FloatUnderflow,
    IntegerDivideByZero,
    IntegerOverflow,
    PrivilegedInstruction,
    DatatypeMisalignment,
    // Info[0] - AccessType, [1] - Alignment, [2] - FaultAddr
    Breakpoint,
    SingleStep,

    ProcessTerminate= 0x10001,
    AsyncProcessTerminate,
    // Info[0] - TID of 'terminator' thread
    Signal
    // Info[0] - Signal Number
};

class _EXPORT_ bException
{
public:
    struct ControlContext
    {
        ulong ctx_RegEbp;
        ulong ctx_RegEip;
        ulong ctx_SegCs;
        ulong ctx_EFlags;
        ulong ctx_RegEsp;
        ulong ctx_SegSs;
    };

    struct IntegerContext
    {
        ulong ctx_RegEdi;
        ulong ctx_RegEsi;
        ulong ctx_RegEax;
        ulong ctx_RegEbx;
        ulong ctx_RegEcx;
        ulong ctx_RegEdx;
    };

    struct FloatContext
    {
        ulong   ctx_env[7];
        uchar   ctx_stack[8][10];
    };

    struct SegmentContext
    {
        ulong ctx_SegGs;
        ulong ctx_SegFs;
        ulong ctx_SegEs;
        ulong ctx_SegDs;
    };

    ExceptionNum    exception;
    ulong*          Info;
    ControlContext* Control;
    IntegerContext* Integer;
    FloatContext*   Float;
    SegmentContext* Segment;
    bThread*        thread;
    static  int Hold();
    static  int Release();
    static  int Cause(ExceptionNum e);

    static  void SignalAcknowledge(ulong t);
    static  void DisableReport();
    static  void EnableReport();
private:
    friend ulong APIENTRY exceptionCatch(struct _EXCEPTIONREPORTRECORD*, struct _EXCEPTIONREGISTRATIONRECORD*, struct _CONTEXT*, void*);
    bException(ulong e) { exception= (ExceptionNum)e; }
};

typedef bool (bEventListener::*bExceptionMethod)(bException*);
#define EXCEPTIONMETHOD(cl,mt) ((bExceptionMethod)&cl::mt)

class _EXPORT_ bExceptionHandler  
{
    friend class bThread;
    tSNode<bExceptionHandler> link;
    ExceptionNum        low, high;
	bEventListener*     thisPtr;
	bExceptionMethod    methodPtr;
	bExceptionHandler(ExceptionNum l, ExceptionNum h, bEventListener* tP, bExceptionMethod mP)
        :link(this) { low= l; high= h; thisPtr= tP; methodPtr= mP; }
public:
    bool    Notify(bException* c)   {return (thisPtr->*methodPtr)(c);}
	bool    InRange(ExceptionNum i) const {return i>=low && i<=high;}
};

#endif // __EVENT_HPP
