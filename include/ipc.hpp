/*  VCS_ID
 *  $Filename:   ipc.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.0  $
 *  $Date:   03 Jul 1991 12:37:00  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __IPC_HPP
#define __IPC_HPP

#ifndef INCL_DOSSEMAPHORES
    typedef  ULONG    HEV;
    typedef  ULONG    HMTX;
    typedef  ULONG    HMUX;
#endif

#define SemIndefiniteWait  -1L
#define SemImmediateReturn	0L

class _EXPORT_ bSemaphore
{
protected:
	bString semName;
	ulong   hsem;
	long    semErr;
	bSemaphore(const char* semName);
	bSemaphore(ulong h= 0) {hsem=h; semErr=0;}
    ~bSemaphore();
public:
	ulong   hSemaphore()	    const { return hsem; }
	ulong   SemaphoreError()    const { return semErr; }
	bool	IsOpen()		    const { return hsem!=0; }
	bool    RequestTimeOut()    const;

    bString Name()              const { return semName; }
};

class _EXPORT_ bMuxSemaphore : public bSemaphore
{
	ulong   semId;
public:
	bMuxSemaphore(bString& semName, ulong id) : bSemaphore(semName) {semId=id;}
	bMuxSemaphore(ulong hsem, ulong id) : bSemaphore(hsem) {semId=id;}
	bMuxSemaphore(ulong id) {semId=id;}

	virtual ~bMuxSemaphore();
	virtual void Release()= 0;
	ulong   SemaphoreId()	    const { return semId; }
};

typedef bSemaphore *pbSemaphore;


class _EXPORT_ bMutexSemaphore : public bMuxSemaphore
{
public:
	bMutexSemaphore(bString& name, ulong id=0) : bMuxSemaphore(name, id) {}
	bMutexSemaphore(HMTX hsem, ulong id) : bMuxSemaphore(hsem, id) {}
	bMutexSemaphore(ulong id = 0, bool fPublic = FALSE, bool fInitOwned = FALSE)
         : bMuxSemaphore(id) {Create(fPublic, fInitOwned);}
	~bMutexSemaphore();

	ulong   Create( bool fPublic = FALSE, bool fInitOwned = FALSE );
	ulong   Open();
	ulong   Close();

	bool    Request(long timeOut = SemIndefiniteWait);
	void    Release();

	PID     OwnedProcess();
	TID     OwnedThread();
	ulong   GetRequestCount();
	bool    IsOwnerDead();
    operator HMTX () const {return hsem;}
};

typedef bMutexSemaphore bNamedMutexSemaphore; 

class _EXPORT_ bEventSemaphore : public bMuxSemaphore
{
public:
	bEventSemaphore(bString& name, ulong id= 0) : bMuxSemaphore(name, id) {}
	bEventSemaphore(HEV hsem, ulong id) : bMuxSemaphore(hsem, id) {}
	bEventSemaphore(ulong id = 0, bool fPublic = FALSE, bool fInitPosted = FALSE)
        : bMuxSemaphore(id) {Create(fPublic, fInitPosted);}

	~bEventSemaphore();
	
   	ulong   Create(bool fPublic = FALSE, bool fInitPosted = FALSE);
	ulong   Open();
    ulong   Close();
		
	ulong   Post();
	ulong   Reset();
    void    Release();

	ulong   Wait(long timeOut = SemIndefiniteWait);

	ulong   GetPostingsCount();
    operator HEV () const {return hsem;}
};

typedef bEventSemaphore bNamedEventSemaphore;

class _EXPORT_ bSemaphoreList : public bSemaphore
{
    tDList<bMuxSemaphore> list;
public:
	bSemaphoreList(bString& name) : bSemaphore(name) {}
	bSemaphoreList(bool fWaitOnAll) {Create(0,fWaitOnAll);}

	~bSemaphoreList();

	ulong   Create(bool fPublic, bool fWaitOnAll);
	ulong   Open();
	ulong   Close();

	bSemaphore* Wait(long timeOut = SemIndefiniteWait);

	bool    Add(bMuxSemaphore* newSem);
	bool    Remove(bMuxSemaphore* sem, bool fPURGE = TRUE);
	void    RemoveAll(bool fPURGE = TRUE);
	void    ResetAll();
    operator HMUX () const  {return hsem;}

	bool    First(bIterator* it=NULL)   {return list.First(it);}
	bool    Last(bIterator* it=NULL)    {return list.Last(it);}
	bool    Next(bIterator* it=NULL)    {return list.Next(it);}
	bool    Prev(bIterator* it=NULL)    {return list.Prev(it);}

	bMuxSemaphore* Subscript(ulong n)   {return list.Subscript(n);}
    bMuxSemaphore* operator[](ulong n)  {return list.operator[](n);}
    bool    IsEmpty()   const           {return list.IsEmpty();}
    ulong   Entries()   const           {return list.Entries();}
    bool    Find(const bMuxSemaphore* item, tIterator<bMuxSemaphore>* it=0) {return list.Find(item,it);}
    bMuxSemaphore* Current(tIterator<bMuxSemaphore>* it=0) {return list.Current(it);}
    bMuxSemaphore* operator()()         {return list.operator()();}
};

typedef bSemaphoreList bNamedSemaphoreList;

typedef bSemaphoreList *pbSemaphoreList;


/*	
 *		Guardian - makes entry into scope in which it is declared dependent
 *		upon a semaphore which is set upon entry and cleared upon exit.
 */

class _EXPORT_ bGuardian
{
private:
	bMutexSemaphore *sem;
public:
	bGuardian(bMutexSemaphore *s) { s->Request(SemIndefiniteWait); sem=s; }
	~bGuardian()				  { sem->Release(); }
};

/*	
 *		EndGuardian - clears a semaphore upon exit from enclosing scope.
 */

class _EXPORT_ bEndGuardian
{
public:
	bMutexSemaphore *sem;
public:
	bEndGuardian(bMutexSemaphore *s)    { sem=s; }
	~bEndGuardian()				  	{ sem->Release(); }
};

/*	
 *		CriticalGuardian - gives exclusive access to critical section
 *		enclosed within same scope as that in which it is declared
 */

class _EXPORT_ bCriticalGuardian
{
public:
	bCriticalGuardian();
	~bCriticalGuardian();
};

//-*****************************************************************************
//
//	CLASS:	bRWSemaphore
//
//	DESCRIPTION:
//
//		Instances of the bRWSemaphore class can be created to arbitrate access
//		to resources that are used in the classical Reader/Writer mode.
//
//		In the Reader/Writer model reader processes access shared data, but do
//		not alter it, and writer processes change the values of shared
//		information.  Any number of readers should be allowed to proceed
//		concurrently in the absence of a writer, but only one writer may
//		execute at a time while readers are excluded.
//
//		Users of this class have a choice in whether readers or writers have
//		priority in accessing the resource.
//
//		A "ReaderPreference" mode of access can be specified when the
//		bRWSemaphore is created.  When this mode is chosen, reader processes
//		will always be given preference while no writers have exclusive access
//		to the resource.
//
//		A "WriterPreference" mode may also be specified.  When used, writer
//		processes that are waiting for a resource will always be given service
//		priority over reader processes that may be waiting for the resource,
//		even if the reader processes requested the resource before the writer
//		process did.
//
//+*****************************************************************************

class _EXPORT_ bRWSemaphore
{
public:
	enum lockingMode { ReaderPreference, WriterPreference };

private:
	bRWSemaphore( const bRWSemaphore& ); // can not copy
	lockingMode lockMode;
    ulong   event;
    ulong   mutex;
	ulong   nWriting;
	ulong   nReading;
	ulong   nWriteWaiting;
	ulong   nReadWaiting;

public:
	bRWSemaphore( lockingMode mode=ReaderPreference );
	~bRWSemaphore();

    lockingMode GetMode() const {return lockMode;}
    void    SetMode( lockingMode mode );
	bool    Request( bool exclusiveFlag=FALSE, long timeout=SemIndefiniteWait );
	void    Release( );
};

#endif // __IPC_HPP
