/*  VCS_ID
 *  $Filename:   collect.hpp
 *  $Author  :   chas, John Pompeii, Jeff Knaus, John Brooking
 *  $Revision:   1.8  $
 *  $Date:   16 Jan 1992 17:14:08  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __COLLECT_HPP
#define __COLLECT_HPP

#include <string.h>

extern "C"
{
	int cmp_STRING(const char* a, const char* b);
	int cmpi_STRING(const char* a, const char* b);
	int cmpn_STRING(const char* a, const char* b);
	int cmpni_STRING(const char* a, const char* b);
	int cmp_SHORT(const short* a, const short* b);
	int cmp_USHORT(const ushort* a, const ushort* b);
	int cmp_LONG(const long* a, const long* b);
	int cmp_ULONG(const ulong* a, const ulong* b);
	int cmp_INT(const INT* a, const INT* b);
	int cmp_UINT(const UINT* a, const UINT* b);
	int cmp_CHAR(const schar* a, const schar* b);
	int cmpi_CHAR(const char* a, const char* b);
	int cmp_UCHAR(const uchar* a, const uchar* b);
	int cmp_BOOL(const bool* a, const bool* b);
	int cmp_PTR(const void* a, const void* b);
	int cmp_FLOAT(const float* a, const float* b);
	int cmp_DOUBLE(const double* a, const double* b);
}

//	TYPES

class bIterator;				// Iterator (collection class-independent)

class bNode;					// base class for Nodes 
class bTreeNode;				// Tree node, derived from bNode

class bCltn; 					// base class for Cltns

class bDList;					// Doubly-linked list, from bCltn
template<class T> class tDList;

class bMap;
template<class K, class V> class tMap;
template<class K, class V> class tCMap;
template<class T> class tSort;

#ifndef BaseSetLite
class bDArray;					// Dynamic array,      from bCltn
template<class T>class tDArray;

class bBitArray;				// Dynamic bit array,  from bCltn

class bStack;					// Stack, derived from private DList
template<class T>class tStack;

class bQueue;					// Queue, derived from private DList
template<class T>class tQueue;
#endif

// DEFINED SYMBOLS

#define PosFirst 		0
#define PosLast		   -1
#define PosCurrent	   -2	
#define RelPosBefore	0		// insert new data before or after current
#define RelPosAfter		1

#define Ascending		TRUE	// insert ordered DList in A or D order
#define Descending		FALSE

#ifdef NULL
#undef NULL
#define NULL 0
#endif

// DEFINED TYPES

typedef int (*CompareFunc)(const void*, const void*);
typedef void* (*IterFunc)(void*);
typedef void* (*IterFunc1)(void*, void*);

//+*****************************************************************************
//
//	CLASS:       bNode
//
//	DESCRIPTION:
//
//		A generic node in a collection.
//
//-*****************************************************************************

class _EXPORT_ bNode
{
public:
	bNode* nextNode;
    bNode* prevNode;
	void* pItem;

	bNode();
	bNode(void* dp);
	bNode* Next() const {return nextNode;}
	bNode* Prev() const {return prevNode;}
    void* operator*() const {return pItem;}
};

//+*****************************************************************************
//
//	CLASS:       bTreeNode
//	INHERITANCE: bNode public
//
//	DESCRIPTION:
//
//		A node that stores a void pointer to some data in a red-black tree of
//		similar nodes.
//
//	COMMENTS:
//
//		The bTreeNode contains extra information needed to support the
//		red-black tree building and balancing algorithms.
//
//-*****************************************************************************

class _EXPORT_ bTreeNode : public bNode
{
private:
	bTreeNode* parentNode;
	bool isRed;
	void* key;

public:
	bTreeNode();
	bTreeNode(void* keyp, void* datap=NULL);
	void* Value()       const   {return this ?pItem :NULL;}
	void Value(void* v)         {if(this) pItem= v;}
	void* Key()         const   {return this ?key :NULL;}
	void Key(void* k)           {if(this) key= k;}
	bool IsNil()        const   {return this==NULL;}
	bool IsRed()        const   {return this ?isRed :FALSE;}
	bool IsBlack()      const   {return this ? !isRed :TRUE;}
	ushort BlackHeight(bTreeNode* root);
	bTreeNode* Parent() const   {return this ?parentNode :NULL;}
	bTreeNode* Left()   const   {return this ?(bTreeNode*) prevNode :NULL;}
	bTreeNode* Right()  const   {return this ?(bTreeNode*) nextNode :NULL;}
	void ColorRed()             {if(this) isRed= TRUE;}
	void ColorBlack()           {if(this) isRed= FALSE;}
	void Parent(bTreeNode* n)   {if(this) parentNode= n;}
	void Left(bTreeNode* n)     {if(this) prevNode= n;}
	void Right(bTreeNode* n)    {if(this) nextNode= n;}
	virtual void AssignContents(void* other);
};

//+*****************************************************************************
//
//	CLASS:       bCltn
//
//	DESCRIPTION:
//
//		The base of all collection classes.
//
//	COMMENTS:
//
//		This is an abstract class.
//
//-*****************************************************************************

class bRWSemaphore;

class _EXPORT_ bCltn
{
protected:
	ulong           numNodes;				// Number of nodes
	bIterator*      defIt;				    // A default iterator
    enum Flags {fPurge= 1};
	unsigned        flags;					// whether to purge on delete
	bRWSemaphore*   rwSem;			        // locking mechanism
	CompareFunc     compare;                // default comparison function

	bNode*          Node(ulong n);	        // returns pointer to nth node

	bCltn(const bCltn& other);              // only derived classes can copy
public:
    bCltn(CompareFunc cmp= NULL, bool _purge= FALSE);
	virtual ~bCltn();                       // first non-pure virtual
protected:
	bCltn&  operator=(const bCltn&);        // only derived classes can assign
	virtual void*   getCurrent(bIterator* it=NULL) =0;
	virtual void*   getSubscript(ulong n)          =0;
	virtual bool    doInsert(const void* n);
    virtual void*   doRemove(bIterator* it=NULL);
	virtual void*   getSearch(const void* key, CompareFunc=NULL, bIterator* it=NULL);
	virtual void    DeleteElement(void* e);
public:
	virtual bool    First(bIterator* it=NULL);
	virtual bool    Last(bIterator* it=NULL);
	virtual bool    Next(bIterator* it=NULL);
	virtual bool    Prev(bIterator* it=NULL);

	virtual void    Clear() =0;

	virtual ulong   Entries()   const   {return numNodes;}
	bIterator*      Iterator()  const   {return defIt;}

	void            SetCompareFunction(CompareFunc cmp) {compare= cmp;}
	CompareFunc     CompareFunction()   const   {return compare;}

	bool    Find(const void* item, bIterator* it=NULL);
	void*   Search(const void* key, CompareFunc f=NULL, bIterator* it=NULL)
		                                {return getSearch(key, f, it);}

	bool    Insert(const void* n)       {return doInsert(n);}
	void*   Remove(bIterator* it=NULL)  {return doRemove(it);}
	void*   Current(bIterator* it=NULL) {return getCurrent(it);}
	void*   Subscript(ulong n)          {return getSubscript(n);}

	void*   operator*()                 {return Current();}
	void*   operator()()                {return Current();}
	void*   operator[](ulong n)         {return Subscript(n);}

	bool    operator++(int)             {return Next();}
	bool    operator--(int)             {return Prev();}

	bool    IsEmpty()       const       {return Entries()==0;}
	bool    IsNotEmpty()    const       {return Entries()!=0;}

	void    SetPurgeOnDelete(bool b)    {if(b) flags|=fPurge; else flags&=~fPurge;}
	bool    IsPurgeOn()     const       {return flags&fPurge;}

	void*   Apply(IterFunc f);
	void*   Apply(IterFunc1 f, void* p);

	void    UseLocking(bool writerPreference=TRUE);
	bool    Request(bool writeFlag=FALSE, long timeout=-1);
	void    Release();
};

#define _NOTSET		(-2)

//+*****************************************************************************
//
//	CLASS:       bIterator
//
//	DESCRIPTION:
//
//		A generic collection iterator.
//
//	COMMENTS:
//
//		Can be used to iterate any type of collection.
//
//-*****************************************************************************

class bRWSemaphore;

class _EXPORT_ bIterator
{
protected:
	bCltn 		*pCol;
	bNode 		*pNode;
	long 		 offset;		    // offset w/in node (where appropriate)
public:
	bIterator(bCltn* pcol);
	bIterator(const bIterator& it) 
        : pCol(it.pCol), pNode(it.pNode), offset(it.offset) {} 

	bool    First()                 {return pCol->First(this);}
	bool    Last()                  {return pCol->Last(this);}
	bool    Next()                  {return pCol->Next(this);}
	bool    Prev()                  {return pCol->Prev(this);}
	bool    operator++(int)         {return Next();}
	bool    operator--(int)         {return Prev();}

    void    Node(bNode *n)          {pNode= n;}
    bNode*  Node()          const   {return pNode;}
    void    Offset(long l)          {offset= l;}
    long    Offset()        const   {return offset;}

	void    Clear()                 {pNode= NULL; offset= 0;}
	void*   Current()               {return pCol->Current(this);}
	void*   operator*()             {return pCol->Current(this);}
	operator bool()                 {return pCol->Current(this)!=0;}

	bool    operator+=(ulong n);
	bool    operator-=(ulong n);
	void    SetTo(ulong n)          {First(); operator+=(n);}

	bool    Request(bool writeFlag=FALSE, long timeout=-1);
	void    Release();
};

//+*****************************************************************************
//
//	CLASS:       tIterator<ElementType>
//	INHERITANCE: bIterator
//
//	DESCRIPTION:
//
//		The collection iterator template class.
//
//	COMMENTS:
//
//		Can be used to iterate any type of collection returning
//		the element type specified.
//
//-*****************************************************************************

template<class E>
class _EXPORT_ tIterator : public bIterator
{
public:
	tIterator(bCltn* pcol) : bIterator(pcol)    {}
	tIterator(const tIterator<E>& it) : bIterator(it) {}
	E* Current()	{return (E*)bIterator::Current();}
	E* operator*()	{return (E*)bIterator::operator*();}
};

//+*****************************************************************************
//
//	CLASS:       tMapIterator<KeyType,ValueType>
//	INHERITANCE: tIterator<ValueType>
//
//	DESCRIPTION:
//
//		The map iterator template class.
//
//	COMMENTS:
//
//		Can be used to iterate maps returning
//		the element types specified.
//
//-*****************************************************************************

template<class K, class V>
class _EXPORT_ tMapIterator : public tIterator<V>
{
public:
	tMapIterator(tMap<K,V>* pcol) : tIterator<V>(pcol) {}
	tMapIterator(const tMapIterator<K,V>& it) : tIterator<V>((tIterator<V> &)it) {}
	K* CurrentKey()	{return (K*) ((bMap*)pCol)->CurrentKey(this);}
};

//+*****************************************************************************
//
//	CLASS:       tCMapIterator<KeyType,ValueType>
//	INHERITANCE: tIterator<ValueType>
//
//	DESCRIPTION:
//
//		The map iterator template class.
//
//	COMMENTS:
//
//		Can be used to iterate maps returning
//		the element types specified.
//
//-*****************************************************************************

template<class K, class V>
class _EXPORT_ tCMapIterator : public tIterator<V>
{
public:
	tCMapIterator(tCMap<K,V>* pcol) : tIterator<V>(pcol) {}
	tCMapIterator(const tCMapIterator<K,V>& it) : tIterator<V>((tIterator<V> &)it) {}
	K* CurrentKey()	{return (K*) ((bMap*)pCol)->CurrentKey(this);}
};

//+*****************************************************************************
//
//	CLASS:       bDList
//	INHERITANCE: bCltn public
//
//	DESCRIPTION:
//
//		A doubly linked list.
//
//-*****************************************************************************

class _EXPORT_ bDList : public bCltn
{
protected:
	bNode* headNode;                // head end of list
    bNode* zero;
    bNode* tailNode;		        // tail end of list

public:
	bDList(CompareFunc cmp, bool _fPurge=FALSE);
	bDList(bool _fPurge=FALSE);
	bDList(const bDList& other);
    virtual ~bDList();
	bDList& operator=(const bDList& obj);

protected:
	virtual void*   getCurrent(bIterator* it=NULL);
	virtual void*   getSubscript(ulong n);
	virtual void*   getSearch(const void* key, CompareFunc=NULL, bIterator* it=NULL);
	virtual bool    doInsert(const void* n);
    virtual void*   doRemove(bIterator* it=NULL);
    virtual bNode*  doRemoveNode(bIterator* it=NULL);
	virtual void    doInsertNode(bNode* n, short pos, bIterator* it= NULL);
public:
	virtual bool    First(bIterator* it=NULL);
	virtual bool    Last(bIterator* it=NULL);
	virtual bool    Next(bIterator* it=NULL);
	virtual bool    Prev(bIterator* it=NULL);
	virtual void    Clear();

	bool    Arrange(const void* ref, short p=RelPosBefore, bIterator* it=NULL);
	bool    ArrangeToHead(bIterator* it=NULL);
	bool    ArrangeToTail(bIterator* it=NULL);

	// intrusive inserts
	void    InsertNodeAt(bNode* p, short pos, bIterator* it= NULL);
	void    InsertNodeAtHead(bNode* p);
	void    OrderedInsertNode(bNode* , CompareFunc f=NULL, bool fAsc=Ascending);
	void    InsertNode(bNode* p);

	// non-intrusive inserts
	void    InsertAt(const void* p, short pos, bIterator* it= NULL);
	void    InsertAtHead(const void* p);
	void    OrderedInsert(const void* p,  CompareFunc f=NULL, bool fAsc=Ascending);

	// intrusive removes (does not delete bNode)
    bNode*  RemoveNode(bIterator* it=NULL);
	bNode*  RemoveHeadNode();
	bNode*  RemoveTailNode();

	// non-intrusive removes (deletes bNode)
	void*   RemoveHead();
	void*   RemoveTail();

	void*   PeekTail();
	void*   Replace(const void* p, bIterator* it=NULL);
};

#ifdef OLD_COLLECTION_TEMPLATES
    #define Declare_Iter(T)         typedef bIterator Iter
    #define Declare_MapIter(K,V)    typedef bIterator Iter
    #define Declare_CMapIter(K,V)   typedef bIterator Iter
    #define Inline_DeleteElement(V)	{delete (V*)e;}
    #define Inline_DeleteKey(K)     {delete (K*)e;}
    #define Inline_Destructor       {Clear();}
#else
    #define Declare_Iter(T)         typedef tIterator<T> Iter
    #define Declare_MapIter(K,V)    typedef tMapIterator<K,V> Iter
    #define Declare_CMapIter(K,V)   typedef tCMapIterator<K,V> Iter
    #define Inline_DeleteElement(V)	;
    #define Inline_DeleteKey(K)     ;
    #define Inline_Destructor       ;
#endif


//+*****************************************************************************
//
//	CLASS:       tDList<T>
//	INHERITANCE: bDList public
//
//	DESCRIPTION:
//
//		A doubly linked list template class.
//
//-*****************************************************************************

template<class T>
class _EXPORT_ tDList : public bDList
{
public:
    typedef int  (*CompareFunc)(const T*, const T*);
    typedef void* (*IterFunc) (T*);
    typedef void* (*IterFunc1)(T*, void*);
    Declare_Iter(T);

	tDList(bool _fPurge=FALSE) : bDList(_fPurge) {}
	tDList(const tDList<T>& other) : bDList(other) {}
	tDList(CompareFunc cmp, bool _fPurge=FALSE) : bDList((::CompareFunc)cmp, _fPurge) {}
	virtual ~tDList() Inline_Destructor
	tDList<T>& operator=(const tDList<T> &obj) {return (tDList<T> &)bDList::operator=(obj);}

    virtual void DeleteElement(void* e) Inline_DeleteElement(V)
	Iter*   Iterator()          const   {return (Iter*)defIt;}

	T*      Current(Iter* it=NULL)      {return (T*) bDList::Current(it);}
	T*      Subscript(ulong n) 		    {return (T*) bDList::Subscript(n);}
	bool    Find(const T* item, Iter* it=NULL)  {return bDList::Find(item, it);}
	T*      Search(const T* key, CompareFunc f=NULL, Iter* it=NULL)
		        {return (T*) bDList::Search(key, (::CompareFunc)f, it);}

	T*      operator*()					{return (T*) bDList::operator*();}
	T*      operator()()				{return (T*) bDList::operator()();}
	T*      operator[](ulong n) 		{return (T*) bDList::operator[](n);}

	void*   Apply(IterFunc f)           {return bDList::Apply((::IterFunc)f);}
	void*   Apply(IterFunc1 f, void* p) {return bDList::Apply((::IterFunc1)f, p);}

	void    SetCompareFunction(CompareFunc cmp) {bDList::SetCompareFunction((::CompareFunc) cmp);}
	CompareFunc CompareFunction() const {return (CompareFunc)bDList::CompareFunction();}

	T*      Replace(const T* p, Iter* it= NULL) {return (T*) bDList::Replace(p, it);}
	bool    Arrange(const T* ref, short p=RelPosBefore, Iter* it=NULL) {return bDList::Arrange(ref, p, it);}
	bool    ArrangeToHead(Iter* it=NULL){return bDList::ArrangeToHead(it);}
	bool    ArrangeToTail(Iter* it=NULL){return bDList::ArrangeToTail(it);}

    bool    Insert(const T* p)		    {return bDList::Insert(p);}
	void    InsertAt(const T* p, short pos, Iter* it=NULL) {bDList::InsertAt(p, pos, it);}
	void    InsertAtHead(const T* p)	{bDList::InsertAtHead(p);}
	void    OrderedInsert(const T* p, CompareFunc f=NULL, bool fAsc=Ascending)
		        {bDList::OrderedInsert(p, (::CompareFunc)f, fAsc);}

	T*      Remove(Iter* it=NULL)       {return (T*)bDList::Remove(it);}
	T*      RemoveHead()       	        {return (T*)bDList::RemoveHead();}
	T*      RemoveTail()       	        {return (T*)bDList::RemoveTail();}
	T*      PeekTail()       	        {return (T*)bDList::PeekTail();}

private: // privitize base void* methods
	void    SetCompareFunction(::CompareFunc cmp);
	bool    Find(const void* item, bIterator* it);
	void*   Search(const void* key, CompareFunc f, bIterator* it);
	bool    Insert(const void* n);
	void*   Remove(bIterator* it);
	void*   Current(bIterator* it);
	void*   Apply(::IterFunc f);
	void*   Apply(::IterFunc1 f, void* p);
	bool    Arrange(const void* ref, short p, bIterator* it);
	bool    ArrangeToHead(bIterator* it);
	bool    ArrangeToTail(bIterator* it);
	void    InsertAt(const void* p, short pos, bIterator* it);
	void    InsertAtHead(const void* p);
	void    OrderedInsert(const void* p, ::CompareFunc f, bool fAsc);
};

#define Define_tDList(T) _EXPORT_ tDList<T> :: ~tDList() {Clear();} \
    void _EXPORT_ tDList<T> :: DeleteElement(void* e) {delete (T*)e;}

//+*****************************************************************************
//
//	CLASS:       bStack
//	INHERITS:    bDList private
//
//	DESCRIPTION:
//
//		A generic stack class.
//
//-*****************************************************************************

class _EXPORT_ bStack : private bDList
{
public:
	bStack(bool _fPurge=FALSE) : bDList(_fPurge) {}
	bStack(const bStack &other) : bDList(other) {}
    ~bStack();
	bStack& operator=(const bStack& obj) {return (bStack&) bDList::operator=(obj);}

	bool    First(bIterator* it=NULL)   {return bDList::First(it);}
	bool    Last(bIterator* it=NULL)    {return bDList::Last(it);}
	bool    Next(bIterator* it=NULL)    {return bDList::Next(it);}
	bool    Prev(bIterator* it=NULL)    {return bDList::Prev(it);}

	void*   Current(bIterator* it=NULL) {return bDList::Current(it);}
	void    Clear()                     {bDList::Clear();}

	bool    IsEmpty()                   {return bDList::IsEmpty();}
    bool    IsNotEmpty()                {return bDList::IsNotEmpty();}
	ulong   Entries() const             {return bDList::Entries();}
	void*   Subscript(ulong n)          {return bDList::Subscript(n);}

	void*   operator*()                 {return bDList::operator*();}
	void*   operator()()                {return bDList::operator()();}
	void*   operator[](ulong n)         {return bDList::operator[](n);}

	void    SetPurgeOnDelete(bool b)    {bDList::SetPurgeOnDelete(b);}
	bool    IsPurgeOn()         const   {return bDList::IsPurgeOn();}

	void    UseLocking(bool writerPreference=TRUE) 
                        {bDList::UseLocking(writerPreference);}
	bool    Request(bool writeFlag=FALSE, long timeout=-1) 
                        {return bDList::Request(writeFlag, timeout);}
	void    Release()   {bDList::Release();}
	void*   Replace(const void* p, bIterator* it=NULL) 
                        {return bDList::Replace(p, it);}

	void    Push(const void* p)         {bDList::Insert(p);}
	void    Push(bNode* p)              {bDList::Insert(p);}

	void*   Pop()                       {return bDList::RemoveTail();}
	void*   Top()                       {return bDList::PeekTail();}
};

//+*****************************************************************************
//
//	TEMPLATE:	tStack<T>
//	INHERITS:   public bStack
//
//	DESCRIPTION:
//
//		A stack template class.
//
//-*****************************************************************************

template<class T>
class _EXPORT_ tStack : public bStack
{
public:
    Declare_Iter(T);

	tStack(bool _fPurge=FALSE) : bStack(_fPurge) {}
	tStack(const tStack<T> &other) : bStack(other) {}
	virtual ~tStack() Inline_Destructor
	tStack<T>& operator=(const tStack<T> &obj) {return (tStack<T> &)bStack::operator=(obj);}

    virtual void DeleteElement(void* e) Inline_DeleteElement(V)

public:
	T*      Current(Iter* it=NULL)	    {return (T*) bStack::Current(it);}
	T*      Subscript(ulong n) 		    {return (T*) bStack::Subscript(n);}

	T*      operator*()					{return (T*) bStack::operator*();}
	T*      operator()()                {return (T*) bStack::operator()();}
	T*      operator[](ulong n) 		{return (T*) bStack::operator[](n);}

	T*      Replace(const T* p, Iter* it= NULL)
										{return (T*) bStack::Replace(p, it);}

	void    Push(T* p)				    {bStack::Push(p);}
	T*      Pop() 						{return (T*)bStack::Pop();}
	T*      Top() 						{return (T*)bStack::Top();}
};

#define Define_tStack(T) _EXPORT_ tStack<T> :: ~tStack() {Clear();} \
    void _EXPORT_ tStack<T> :: DeleteElement(void *e) {delete (T*)e;}


//+*****************************************************************************
//
//	CLASS:       bQueue
//	INHERITS:    bDList private
//
//	DESCRIPTION:
//
//		A generic queue class.
//
//-*****************************************************************************

class _EXPORT_ bQueue : private bDList
{
public:
	bQueue(bool _fPurge=FALSE) : bDList(_fPurge) {}
	bQueue(const bQueue &other) : bDList(other) {}
    ~bQueue();
	bQueue& operator=(const bQueue& obj) {return (bQueue&) bDList::operator=(obj);}

	bool    First(bIterator* it=NULL)   {return bDList::First(it);}
	bool    Last(bIterator* it=NULL)    {return bDList::Last(it);}
	bool    Next(bIterator* it=NULL)    {return bDList::Next(it);}
	bool    Prev(bIterator* it=NULL)    {return bDList::Prev(it);}

	void*   Current(bIterator* it=NULL) {return bDList::Current(it);}
	void    Clear()                     {bDList::Clear();}

	bool    IsEmpty()                   {return bDList::IsEmpty();}
    bool    IsNotEmpty()                {return bDList::IsNotEmpty();}
	ulong   Entries() const             {return bDList::Entries();}
	void*   Subscript(ulong n)          {return bDList::Subscript(n);}

	void*   operator*()                 {return bDList::operator*();}
	void*   operator()()                {return bDList::operator()();}
	void*   operator[](ulong n)         {return bDList::operator[](n);}

	void    SetPurgeOnDelete(bool b)    {bDList::SetPurgeOnDelete(b);}
	bool    IsPurgeOn()         const   {return bDList::IsPurgeOn();}

	void    UseLocking(bool writerPreference=TRUE) 
                        {bDList::UseLocking(writerPreference);}
	bool    Request(bool writeFlag=FALSE, long timeout=-1) 
                        {return bDList::Request(writeFlag, timeout);}
	void    Release()   {bDList::Release();}

	bool    Insert(const void* p)       {return bDList::Insert(p);}
	void*   Remove()                    {return bDList::RemoveHead();}
};

//+*****************************************************************************
//
//	CLASS:       tQueue<T>
//	INHERITS:    bQueue public
//
//	DESCRIPTION:
//
//		A queue template class.
//
//-*****************************************************************************

template<class T>
class _EXPORT_ tQueue : public bQueue
{
public:
	tQueue(bool _fPurge=FALSE) : bQueue(_fPurge) {}
	tQueue(const tQueue<T> &other) : bQueue(other) {}
	virtual ~tQueue() Inline_Destructor
	tQueue<T>& operator=(const tQueue<T> &obj) {return (tQueue<T> &)bQueue::operator=(obj);}

    virtual void DeleteElement(void* e) Inline_DeleteElement(V)

    bool    Insert(const T* p)		    {return bQueue::Insert(p);}    
	T*      Remove()                    {return (T*) bQueue::Remove();}

	T*      Current()	                {return (T*) bQueue::Current();}
	T*      Subscript(ulong n) 		    {return (T*) bQueue::Subscript(n);}

	T*      operator*()					{return (T*) bQueue::operator*();}
	T*      operator()()                {return (T*) bQueue::operator()();}
	T*      operator[](ulong n) 		{return (T*) bQueue::operator[](n);}
};

#define Define_tQueue(T) _EXPORT_ tQueue<T> :: ~tQueue() {Clear();} \
    void _EXPORT_ tQueue<T> :: DeleteElement(void *e) {delete (T*)e;}

#ifndef BaseSetLite

//+*****************************************************************************
//
//	CLASS:       bRecord
//	INHERITANCE: none
//
//	DESCRIPTION:
//
//		The abstract class representing a record to be stored in a mapping.  To
//		be used in deriving data types to be accessed via accessor methods.  Not
//		needed unless bAttributeColumnFormats are used to specify data columns.
//
//-*****************************************************************************

class _EXPORT_ bRecord
{
};

//+*****************************************************************************
//
//	CLASS:       bColumnFormat
//	INHERITANCE: none
//
//	DESCRIPTION:
//
//		A class for specifiying data type columns and their respective access
//		methods.  Used internally by bType classes.
//
//-*****************************************************************************

// calculates offset of field within type specified
#define FIELD_OFFSET(type, field) ((ushort)(long)&(((type*)0)->field))

class _EXPORT_ bColumnFormat
{
public:
	char* columnId;

	bColumnFormat(const char* id);
	operator char*() const {return columnId;}
	virtual void* GetColumnPtr(void* rec, void* buffer);
};

// for registering columns types for data to be accessed directly

class _EXPORT_ bFieldColumnFormat : public bColumnFormat
{
public:
	ushort offset;
	ushort depth;

	bFieldColumnFormat(const char* id, ushort fieldOffset, ushort indirection);
	void* GetColumnPtr(void* rec, void* buffer);
};

//+*****************************************************************************
//
//	CLASS:       bType
//	INHERITANCE: none
//
//	DESCRIPTION:
//
//		A class for registering data types and their access formats to be used
//		in sorted tables and their respective sorts.
//
//-*****************************************************************************

class _EXPORT_ bType
{
	friend int cmp_bType(const bType* , const bType* );

public:
	enum bAccessType {BaseType, StructField, RecordAttribute};

private:
	static tSort<bType>* DTRepository;

	char* name;
	bAccessType access;
	tDList<bColumnFormat> columns;

	bType(const char* id);

public:
	static bType* GetType(const char* id);

	bType(const char* id, bAccessType t, ulong n, ...);
	bColumnFormat* GetColumn(const char* id);
};

#endif 		// BaseSetLite

//+*****************************************************************************
//
//	CLASS:       bMap
//	INHERITANCE: bCltn public
//
//	DESCRIPTION:
//
//		The elements may be searched or iterated using the specified comparison
//		function.  The collection may be constructed to hold only uniquely
//		keyed members, where uniqueness is determined by applying the specified
//		comparison function.
//
//-*****************************************************************************

class _EXPORT_ bMap : public bCltn
{
protected:
    enum Flags {fPurge=1, fPurgeKeys=2, fUnique=4, fAscending=8};
	bTreeNode*      root;

	bool            IsRoot(bTreeNode* np)   const   {return np==root;}
	bTreeNode*      Root()                  const   {return root;}
	bTreeNode*      TreeSuccessor(bTreeNode* x);
	bTreeNode*      TreePredecessor(bTreeNode* x);
	bTreeNode*      TreeMinimum(bTreeNode* x);
	bTreeNode*      TreeMaximum(bTreeNode* x);
	bool            TreeInsert(bTreeNode* z);
	bool            RBInsert(bTreeNode* x);
	void            TreeDelete(bTreeNode* z);
	bTreeNode*      RBDelete(bTreeNode* z);
	void            RBDeleteFixup(bTreeNode* x, bTreeNode* xp);
	void            LeftRotate(bTreeNode* x);
	void            RightRotate(bTreeNode* x);
	bool            InsertNode(bTreeNode* p);
	bTreeNode*      NodeOf(bIterator* it);

	bool            TreeInsertAssoc(const void* key, const void* data);
	void*           TreeRemoveAssoc(void* *key=NULL, bIterator* it=NULL);

public:
	bMap(CompareFunc cmp= NULL, bool unique=FALSE, bool purge=FALSE, bool purgeKeys=FALSE);
	bMap(const bMap &other);
    virtual ~bMap();
	bMap& operator=(const bMap& obj);

protected:
	virtual void*   getCurrent(bIterator* it=NULL);
	virtual void*   getSubscript(ulong n);
	virtual void*   getSearch(const void* key, CompareFunc f=NULL, bIterator* it=NULL);
	virtual void*   doRemove(bIterator* it=NULL);
	virtual bool    doInsert(const void* data);
	virtual void*   getSearch(const void* key, bIterator* it);
	virtual void*   getCurrentKey(bIterator* it=NULL);
	virtual int     Compare(const bTreeNode *a, const bTreeNode *b);
public:
	virtual bool    First(bIterator* it=NULL);
	virtual bool    Last(bIterator* it=NULL);
	virtual bool    Next(bIterator* it=NULL);
	virtual bool    Prev(bIterator* it=NULL);

	virtual void    Clear();
	virtual void    DeleteKey(void* e);

	void*   Search(const void* key, CompareFunc f, bIterator* it=NULL)
                                            {return getSearch(key, f, it);}
	void*   Search(const void* key, bIterator* it=NULL)
                                            {return getSearch(key, it);}

	bool    InsertAssoc(const void* key, const void* data) {return TreeInsertAssoc(key, data);}
	void*   RemoveAssoc(void* *key=NULL, bIterator* it=NULL) {return TreeRemoveAssoc(key, it);}

	void*   CurrentKey(bIterator* it=NULL)  {return getCurrentKey(it);}

	void    SetPurgeKeysOnDelete(bool b)    {if(b) flags|=fPurgeKeys; else flags&=~fPurgeKeys;}
	bool    IsPurgeKeysOn()         const   {return flags&fPurgeKeys;}
	void    SetUniqueKeys(bool b)           {if(b) flags|=fUnique; else flags&=~fUnique;}
	bool    AreKeysUnique()         const   {return flags&fUnique;}
    void    SetDescending(bool b)           {if(b) flags|=fAscending; else flags&=~fAscending;}
    bool    IsDescending()          const   {return flags&fAscending;}
};

//+*****************************************************************************
//
//	CLASS:       tMap<KeyType,ValueType>
//	INHERITANCE: bMap public
//
//	DESCRIPTION:
//
//		The tMap template class allows the Key and Value data types to be
//		specified in the variable declaration.
//
//-*****************************************************************************

template<class K,class V>
class _EXPORT_ tMap : public bMap
{
public:
    typedef int (*CompareFunc)(const K*, const K*);
    typedef void* (*IterFunc) (V*);
    typedef void* (*IterFunc1)(V*, void*);
    Declare_MapIter(K,V);

	tMap() : bMap() {}
	tMap(const tMap<K,V> &other) : bMap(other) {}
	tMap(CompareFunc cmp, bool unique=FALSE, bool purge=FALSE, bool purgeKeys=FALSE)
		: bMap((::CompareFunc)cmp, unique, purge, purgeKeys) {}
	virtual ~tMap() Inline_Destructor
	tMap<K,V>& operator=(const tMap<K,V> &obj) {return (tMap<K,V> &)bMap::operator=(obj);}

	virtual void DeleteElement(void* e) Inline_DeleteElement(V)
	virtual void DeleteKey(void* e) Inline_DeleteKey(V)

	Iter*   Iterator()              const   {return (Iter*)defIt;}

    bool    Insert(const V* p)		        {return bMap::Insert(p);}
	V*      Remove(Iter* it= NULL)          {return (V*)bMap::Remove(it);}

	V*      Current(Iter* it=NULL)          {return (V*) bMap::Current(it);}
	V*      Subscript(ulong n) 		        {return (V*) bMap::Subscript(n);}
	bool    Find(const V* item, Iter* it=NULL)  {return bMap::Find(item, it);}
	V*      Search(const K* key, CompareFunc f, Iter* it=NULL)
                    {return (V*) bMap::Search(key, (::CompareFunc)f, it);}
	V*      Search(const K* key, Iter* it=NULL)
                    {return (V*) bMap::Search(key, it);}

	V*      operator*()					    {return (V*) bMap::operator*();}
	V*      operator()()					{return (V*) bMap::operator()();}
	V*      operator[](ulong n) 		    {return (V*) bMap::operator[](n);}

	void*   Apply(IterFunc f)               {return bMap::Apply((::IterFunc)f);}
	void*   Apply(IterFunc1 f, void* p)     {return bMap::Apply((::IterFunc1)f, p);}

	void    SetCompareFunction(CompareFunc cmp) {bMap::SetCompareFunction((::CompareFunc) cmp);}
	CompareFunc CompareFunction()   const   {return (CompareFunc)bMap::CompareFunction();}

	K*      CurrentKey(Iter* it=NULL)       {return (K*) bMap::CurrentKey(it);}

	bool    InsertAssoc(const K* key, const V* data)  {return TreeInsertAssoc(key, data);}
	V*      RemoveAssoc(K* *key=NULL, Iter* it=NULL)  {return (V*)TreeRemoveAssoc((void* *)key, it);}

private: // privitize base void* methods
	void    SetCompareFunction(::CompareFunc cmp);
	bool    Find(const void* item, bIterator* it);
	void*   Search(const void* key, ::CompareFunc f, bIterator* it);
	bool    Insert(const void* n);
	void*   Remove(bIterator* it);
	void*   Current(bIterator* it);
	void*   Apply(::IterFunc f);
	void*   Apply(::IterFunc1 f, void* p);
	void*   Search(const void* key, bIterator* it);
	bool    InsertAssoc(const void* key, const void* data);
	void*   RemoveAssoc(void* *key, bIterator* it);
	void*   CurrentKey(bIterator* it);
};

#define Define_tMap(K,V) _EXPORT_ tMap<K,V> :: ~tMap() {Clear();} \
    void _EXPORT_ tMap<K,V> :: DeleteElement(void *e) {delete (V*)e;} \
    void _EXPORT_ tMap<K,V> :: DeleteKey(void *k) {delete (K*)k;}

//+*****************************************************************************
//
//	CLASS:       tSort<ValueType>
//	INHERITANCE: tMap<ValueType,ValueType> public
//
//	DESCRIPTION:
//
//		The bMap template class for mappings where the value
//		being stored is also the key for sorting and searching.
//
//-*****************************************************************************

template<class V>
class _EXPORT_ tSort : public tMap<V,V>
{
public:
	tSort() : tMap<V,V>() {}
	tSort(const tSort<V> &other) : tMap<V,V>(other) {}
	tSort(CompareFunc cmp, bool unique=FALSE, bool purge=FALSE)
		: tMap<V,V>(cmp, unique, purge, FALSE) {}
	~tSort();

	tSort<V>& operator=(const tSort<V> &obj) {return (tSort<V> &)bMap::operator=(obj);}
};

#define Define_tSort(V) Define_tMap(V,V) \
    _EXPORT_ tSort<V>::~tSort() {}

#ifndef BaseSetLite

//+*****************************************************************************
//
//	CLASS:       bColumnSort
//	INHERITANCE: none
//
//	DESCRIPTION:
//
//		Used by a bMap for comparisons.
//
//-*****************************************************************************

class _EXPORT_ bColumnSort
{
public:
	bColumnFormat* columnType;
	bool ascend;
	CompareFunc compare;

	bColumnSort(bColumnFormat* columnFormat, CompareFunc cmp, bool ascendFlag);
	bColumnFormat* Column() {return columnType;}
	int Compare(const bTreeNode* l, const bTreeNode* r);
};

//+*****************************************************************************
//
//	CLASS:       bComplexMap
//	INHERITANCE: bMap public
//
//	DESCRIPTION:
//
//		Represents a complex mapping between key data type and a value data
//		type.  This mapping is considered complex because a compound key may be
//		specified, allowing for approximate searching via the partial key matching
//		facility.
//
//		Maintains a sorted collection of key-value pairs where the value element
//		may be specified as the key element.  The data type of the key element
//		must have been registered with the data type repository prior to
//		creation of a bComplexMap using that type as the key type.
//
//		The elements may be searched or iterated within the context of the sort
//		specification.  The sort specification is composed of a list of
//		<column id, comparison function, direction indicator> triplets which
//		can be specified via an invocation of the SortBy method.
//
//		A sort can be specified to be unique.  In that case, uniqueness can
//		be determined by evaluating the comparison functions in the sort
//		specification in order of specification until all columns of the
//		specification are determined to be matching or one is found that does
//		not match.
//
//-*****************************************************************************

class _EXPORT_ bComplexMap : public bMap
{
protected:
	bType* recFormat;
	tDList<bColumnSort> columnSorts;
    void    CopySorts(const tDList<bColumnSort> &);

	void*   getApproxSearch(const void* key, ushort depth=0, bIterator* it=NULL);
	virtual int Compare(const bTreeNode* l, const bTreeNode* r);

public:
	bComplexMap(const char* formatId, bool unique=FALSE, bool purge=FALSE,
		   bool purgeKeys=FALSE);
	bComplexMap(const bComplexMap &other);
	~bComplexMap();
	bComplexMap& operator=(const bComplexMap& obj);

	int     ApproxKeyedCompare(const bTreeNode* a, const bTreeNode* b, ushort depth=0);
	void*   ApproxSearch(const void* key, ushort depth=0, bIterator* it=NULL)
	            {return getApproxSearch(key, depth, it);}
	bool    NextMatching(const void* key, ushort depth=0, bIterator* it=NULL);
	bool    PrevMatching(const void* key, ushort depth=0, bIterator* it=NULL);

	void    SortBy(ulong n, ...);
	void    AddSortSpec(const char* columnId, CompareFunc cmp, bool ascend);
};

//+*****************************************************************************
//
//	CLASS:       tCMap<KeyType,ValueType>
//	INHERITANCE: bComplexMap public
//
//	DESCRIPTION:
//
//		The bComplexMap template class allows the Key and Value data types to be
//		specified in the variable declaration.
//
//-*****************************************************************************

template<class K, class V>
class _EXPORT_ tCMap : public bComplexMap
{
public:
    typedef int (*CompareFunc)(const K*, const K*);
    typedef void* (*IterFunc) (V*);
    typedef void* (*IterFunc1)(V*, void*);
    Declare_CMapIter(K,V);

	tCMap(const tCMap<K,V> &other) : bComplexMap(other) {}
	tCMap(const char* tableId, bool unique=FALSE, bool purge=FALSE, bool purgeKeys=FALSE)
		: bComplexMap(tableId, unique, purge, purgeKeys) {}
	virtual ~tCMap() Inline_Destructor
	virtual void DeleteElement(void* e) Inline_DeleteElement(V)
	virtual void DeleteKey(void* e) Inline_DeleteKey(V)

	tCMap<K,V>& operator=(const tCMap<K,V> &obj) {return (tCMap<K,V> &)bComplexMap::operator=(obj);}

    bool    Insert(const V* p)		    {return bComplexMap::Insert(p);}
	V*      Remove(Iter* it= NULL)      {return (V*)bComplexMap::Remove(it);}

	Iter*   Iterator() const            {return (Iter*)defIt;}

	V*      Current(Iter* it=NULL)      {return (V*) bComplexMap::Current(it);}
	V*      Subscript(ulong n) 	        {return (V*) bComplexMap::Subscript(n);}
	bool    Find(const V* item, Iter* it=NULL)  {return bComplexMap::Find(item, it);}
	V*      Search(const K* key, CompareFunc f, Iter* it=NULL)
                    {return (V*) bComplexMap::Search(key, (::CompareFunc)f, it);}
	V*      Search(const K* key, Iter* it=NULL)
                    {return (V*) bComplexMap::Search(key, it);}

	V*      operator*()					{return (V*) bComplexMap::operator*();}
	V*      operator()()				{return (V*) bComplexMap::operator()();}
	V*      operator[](ulong n) 		{return (V*) bComplexMap::operator[](n);}

	void*   Apply(IterFunc f)           {return bComplexMap::Apply((::IterFunc)f);}
	void*   Apply(IterFunc1 f, void* p) {return bComplexMap::Apply((::IterFunc1)f, p);}

	void    SetCompareFunction(CompareFunc cmp) {bComplexMap::SetCompareFunction((::CompareFunc) cmp);}
	CompareFunc CompareFunction() const {return (CompareFunc)bComplexMap::CompareFunction();}

	K*      CurrentKey(Iter* it=NULL)   {return (K*) bComplexMap::CurrentKey(it);}

	bool    InsertAssoc(const K* key, const V* data)     
                        {return TreeInsertAssoc(key, data);}
	V*      RemoveAssoc(K* *key=NULL, Iter* it=NULL)  
                        {return (V*)TreeRemoveAssoc((void* *)key, it);}

	// for keyed lookup only
	V*      ApproxSearch(const K* key, ushort depth=0, Iter* it=NULL)
		                {return (V*)bComplexMap::ApproxSearch(key, depth, it);}
	bool    NextMatching(K* key, ushort depth=0, Iter* it=NULL)
		                {return bComplexMap::NextMatching(key, depth, it);}
	bool    PrevMatching(K* key, ushort depth=0, Iter* it=NULL)
		                {return bComplexMap::PrevMatching(key, depth, it);}

private: // privitize base void* methods
	void    SetCompareFunction(::CompareFunc cmp);
	bool    Find(const void* item, bIterator* it);
	bool    Insert(const void* n);
	void*   Remove(bIterator* it);
	void*   Current(bIterator* it);
	void*   Apply(::IterFunc f);
	void*   Apply(::IterFunc1 f, void* p);
	void*   Search(const void* key, ::CompareFunc f, bIterator* it);
	void*   Search(const void* key, bIterator* it);
	bool    InsertAssoc(const void* key, const void* data);
	void*   RemoveAssoc(void* *key, bIterator* it);
	void*   CurrentKey(bIterator* it);
	void*   ApproxSearch(const void* key, ushort depth, bIterator* it);
	bool    NextMatching(const void* key, ushort depth, bIterator* it);
	bool    PrevMatching(const void* key, ushort depth, bIterator* it);
};

#define Define_tCMap(K,V) _EXPORT_ tCMap<K,V> :: ~tCMap() {Clear();} \
    void _EXPORT_ tCMap<K,V> :: DeleteElement(void *e) {delete (V*)e;} \
    void _EXPORT_ tCMap<K,V> :: DeleteKey(void *k) {delete (K*)k;}

//+*****************************************************************************
//
//	CLASS:       tCSort<ValueType>
//	INHERITANCE: tCMap<ValueType,ValueType> public
//
//	DESCRIPTION:
//
//		The bComplexMap template class for complex mappings where the value
//		being stored is also the key for sorting and searching.
//
//-*****************************************************************************

template<class V>
class _EXPORT_ tCSort : public tCMap<V,V>
{
public:
	tCSort(const char* tableId, bool unique=FALSE, bool purge=FALSE, bool purgeKeys=FALSE)
		: tCMap<V,V>(tableId, unique, purge, purgeKeys) {}
	tCSort(const tCSort<V> &other) : tCMap<V,V>(other) {}
	~tCSort();

	tCSort<V>& operator=(const tCSort<V> &obj) {return (tCSort<V> &)bComplexMap::operator=(obj);}
};

#define Define_tCSort(V) Define_tCMap(V,V) \
    _EXPORT_ tSort<V>::~tSort() {}

//+*****************************************************************************
//
//	CLASS:       bDArray
//	INHERITS:    bCltn private
//
//	DESCRIPTION:
//
//		A dynamic array class.
//
//-*****************************************************************************

#define _DEF_BLKSIZE	20

class _EXPORT_ bDArray : public bCltn
{
private:
	bNode*  headNode;
    bNode*  tailNode;
	ushort  elSize;
    ushort  blkSize;

	ulong           CalcGlobalOffset (bIterator* it);
public:
	bDArray(const bDArray &other) {headNode=tailNode=NULL;* this= other;}
	bDArray(ushort elsize, ushort blksize=_DEF_BLKSIZE);
    virtual ~bDArray();
	bDArray& operator=(const bDArray &obj);

protected:
	virtual void*   getCurrent(bIterator* it=NULL);
	virtual void*   getSubscript(ulong n);
	virtual bool 	doInsert(const void* pobject);
    virtual void*   doRemove(bIterator* it=NULL);
public:
	virtual bool    First(bIterator* it=NULL);
	virtual bool    Last(bIterator* it=NULL);
	virtual bool    Next(bIterator* it=NULL);
	virtual bool    Prev(bIterator* it=NULL);

	virtual void    Clear();
};

//+*****************************************************************************
//
//	CLASS:       tDArray
//	INHERITS:    bDArray public
//
//	DESCRIPTION:
//
//		The dynamic array template class.
//
//-*****************************************************************************

template<class T>
class _EXPORT_ tDArray : public bDArray
{
public:
    typedef int (*CompareFunc)(const T*, const T*);
    typedef void* (*IterFunc) (T*);
    typedef void* (*IterFunc1)(T*, void*);
    Declare_Iter(T);

	tDArray(ushort elsize= sizeof(T), ushort blksize=_DEF_BLKSIZE) : bDArray(elsize, blksize) {}
	tDArray(const tDArray<T> &other) : bDArray(other) {}
	~tDArray();
	tDArray<T>& operator=(const tDArray<T> &obj) {return (tDArray<T> &)bDArray::operator=(obj);}

	Iter*   Iterator()          const   {return (Iter*)defIt;}

    bool    Insert(const T* p)		    {return bDArray::Insert(p);}
	T*      Remove(Iter* it= NULL)      {return (T*)bDArray::Remove(it);}

	T*      Current(Iter* it=NULL)      {return (T*) bDArray::Current(it);}
	T*      Subscript(ulong n) 		    {return (T*) bDArray::Subscript(n);}
	T*      Search(const T* key, CompareFunc f=NULL, Iter* it=NULL)
		        {return (T*) bDArray::Search(key, (::CompareFunc)f, it);}

	T*      operator*()					{return (T*) bDArray::operator*();}
	T*      operator()()				{return (T*) bDArray::operator()();}
	T*      operator[](ulong n) 		{return (T*) bDArray::operator[](n);}

	void*   Apply(IterFunc f)           {return bDArray::Apply((::IterFunc)f);}
	void*   Apply(IterFunc1 f, void* p) {return bDArray::Apply((::IterFunc1)f, p);}

	void    SetCompareFunction(CompareFunc cmp) {bDArray::SetCompareFunction((::CompareFunc) cmp);}
	CompareFunc CompareFunction() const {return (CompareFunc)bDArray::CompareFunction();}

private: // privitize base void* methods
	void    SetCompareFunction(::CompareFunc cmp);
	bool    Find(const void* item, bIterator* it);
	void*   Search(const void* key, ::CompareFunc f, bIterator* it);
	bool    Insert(const void* n);
	void*   Remove(bIterator* it);
	void*   Current(bIterator* it);
	void*   Apply(::IterFunc f);
	void*   Apply(::IterFunc1 f, void* p);
};

#define Define_tDArray(T) _EXPORT_ tDArray<T>::~tDArray() {Clear();}

//+*****************************************************************************
//
//	CLASS:       bBitArray
//	INHERITS:    bCltn public
//
//	DESCRIPTION:
//
//		An array of bits.
//
//-*****************************************************************************

#define BITVALUE(i)			((bool)((ulong)i-1))

#define _DEF_BITSIZE	100

class _EXPORT_ bBitArray : public bCltn
{
private:
	bNode*  headNode;
	bNode*  tailNode;

	void            RangeCheck (ulong i);
public:
	bBitArray(ulong nbits=_DEF_BITSIZE);
	bBitArray(const bBitArray &other);
    virtual ~bBitArray();
protected:
	virtual void*   getCurrent(bIterator* it=NULL);
	virtual void*   getSubscript(ulong n);
public:
	virtual bool First(bIterator* it=NULL);
	virtual bool Last(bIterator* it=NULL);
	virtual bool Next(bIterator* it=NULL);
	virtual bool Prev(bIterator* it=NULL);	
	virtual void Clear();

	void    Grow(ulong newsize=0);

	operator int();

	void    SetBit(ulong n);
	void    ClearBit(ulong n);
	void    ToggleBit(ulong n);

	void    SetMultiple(ulong n, ...);
	void    ClearMultiple(ulong n, ...);
	void    ToggleMultiple(ulong n, ...);

	void    SetAll();						// set all bits
	void    ClearAll();					    // clear all bits
	void    ToggleAll();
};

//+*****************************************************************************
//
//	CLASS:       bArgArray
//	INHERITANCE: bDArray public
//
//	DESCRIPTION:
//
//		Implements a simple standard mechanism for passing arguments of
//		heterogenous types in a variable length array.
//
//-*****************************************************************************

class _EXPORT_ bArgArray : public bDArray
{
public:
	ushort argc;

	bArgArray(ushort n, ...);
	void* operator[](ulong n);
};

#endif 		// BaseSetLite

//+*****************************************************************************
//
//	TYPEDEF:	bCharPList
//
//	DESCRIPTION:
//
//		A bDList of char* s.
//
//-*****************************************************************************

typedef tDList<char> bCharPList;

//+*****************************************************************************
//
//	TYPEDEF:	bDictionary
//
//	DESCRIPTION:
//
//		A bMap of anything to anything.  
//
//		Defined for compatibility with 1.XX dictionaries.
//
//-*****************************************************************************

typedef bMap bDictionary;

#endif // __COLLECT_HPP

