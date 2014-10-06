/*  VCS_ID
 *  $Filename:   slist.hpp
 *  $Author  :   chas
 *  $Revision:   1.2  $
 *  $Date:   16 Dec 1991 12:59:40  $
 *
 *  Copyright (c)    1995 by Secant Technologies
 *
 */

#ifndef __SLIST_HPP
#define __SLIST_HPP

class _EXPORT_ bSNode
{
protected:
    friend class bSList;
    bSNode*     next;
    void*       what;
public:
    bSNode(void* w)                 {what= w;}
    bSNode*     Next() const        {return next;}
    void        What(void* w)       {what= w;}
    void*       What() const        {return what;}
};

class _EXPORT_ bKeyNode : public bSNode
{
    ulong       key;
public:
    bKeyNode(void* w) : bSNode(w)   {key= 0;}
    bKeyNode*   Next() const        {return (bKeyNode*)next;}
    void        Key(ulong k)        {key= k;}
    ulong       Key() const         {return key;}
};

class _EXPORT_ bNameNode : public bKeyNode
{
    char*       name;
public:
    bNameNode(void* w) : bKeyNode(w) {name= 0;}
    ~bNameNode();
    bNameNode*     Next() const     {return (bNameNode*)next;}
    void        Name(const char* n);
    const char* Name() const        {return name;}
};

class _EXPORT_ bSList
{
protected:
    bSNode* root;
public:
    bSList(bSNode* r= 0)            {root= r;}
    bSNode* Root() const            {return root;}
    void Root(bSNode* r)            {root= r;}

    void    Add(bSNode& n);
    void    Append(bSNode& n);
    bool    Remove(bSNode& n);
    void*   Remove(void* v);

    typedef void* (*IterFnc)(void*, void*);
    void*   Iterate(IterFnc fnc, void* arg);

    typedef bool (*SplitFnc)(void*, void*);
    bSNode* Split(SplitFnc fnc, void* arg);
};

class _EXPORT_ bKeyList : public bSList
{
public:
    bKeyList(bKeyNode* r= 0) : bSList(r) {}
    bKeyNode* Root() const          {return (bKeyNode*)root;}
    void    Root(bKeyNode* r)       {root= r;}

    void    Add(bKeyNode& n)        {bSList::Add(n);}
    void    Append(bKeyNode& n)     {bSList::Append(n);}
    bool    Remove(bKeyNode& n)     {return bSList::Remove(n);}
    bKeyNode* Remove(void* v)       {return (bKeyNode*)bSList::Remove(v);}

    bKeyNode* Split(SplitFnc fnc, void* arg) {return (bKeyNode*)bSList::Split(fnc, arg);}

    void*   Find(ulong key) const;
private:
    void    Add(bSNode& n);
    void    Append(bSNode& n);
    bool    Remove(bSNode& n);
};

class _EXPORT_ bNameList : public bKeyList
{
public:
    bNameList(bNameNode* r= 0) : bKeyList(r) {}
    bNameNode* Root() const         {return (bNameNode*)root;}
    void Root(bNameNode* r)         {root= r;}

    void    Add(bNameNode& n)       {bKeyList::Add(n);}
    void    Append(bNameNode& n)    {bKeyList::Append(n);}
    bool    Remove(bNameNode& n)    {return bKeyList::Remove(n);}
    bNameNode* Remove(void* v)      {return (bNameNode*)bKeyList::Remove(v);}

    bNameNode* Split(SplitFnc fnc, void* arg) {return (bNameNode*)bKeyList::Split(fnc, arg);}

    void*   Find(ulong key) const   {return bKeyList::Find(key);}
    void*   Find(const char* name) const;
};

class bMutexSemaphore;

class _EXPORT_ bLockList : public bNameList
{
    bMutexSemaphore* mutex;
public:

    bLockList(bNameNode* r= 0);
    ~bLockList();

    void    Add(bNameNode& n);
    void    Append(bNameNode& n);
    bool    Remove(bNameNode& n);
    bNameNode* Remove(void* v);

    void*   Iterate(IterFnc fnc, void* arg);
    bNameNode* Split(SplitFnc fnc, void* arg);

    void*   Find(ulong key) const;
    void*   Find(const char* name) const;
	bMutexSemaphore *Mutex()  { return mutex; } 
};

template<class W>
class _EXPORT_ tSNode : public bSNode
{
public:
    tSNode(W* w) : bSNode(w) {}
    tSNode<W>* Next() const         {return (tSNode<W>*)next;}
    void    What(W* w)              {what= w;}
    W*      What() const            {return (W*)what;}
};

template<class W>
class _EXPORT_ tKeyNode : public bKeyNode
{
public:
    tKeyNode(W* w) : bKeyNode(w) {}
    tKeyNode<W>* Next() const       {return (tKeyNode<W>*)next;}
    void    What(W* w)              {what= w;}
    W*      What() const            {return (W*)what;}
};

template<class W>
class _EXPORT_ tNameNode : public bNameNode
{
public:
    tNameNode(W* w) : bNameNode(w) {}
    tNameNode<W>* Next() const      {return (tNameNode<W>*)next;}
    void    What(W* w)              {what= w;}
    W*      What() const            {return (W*)what;}
};

template<class W>
class _EXPORT_ tSList : public bSList
{
public:
    tSList(tSNode<W>* r= 0) : bSList(r) {}
    tSNode<W>* Root() const         {return (tSNode<W>*)root;}
    void Root(tSNode<W>* r)         {root= r;}

    void    Add(tSNode<W>& t)       {bSList::Add(t);}
    void    Append(tSNode<W>& t)    {bSList::Append(t);}
    bool    Remove(tSNode<W>& t)    {return bSList::Remove(t);}
    tSNode<W>* Remove(W* t)         {return (tSNode<W>*) bSList::Remove(t);}

    typedef W* (*IterFnc)(W*, void*);
    W*      Iterate(IterFnc fnc, void* arg)
        {return (W*)bSList::Iterate((bSList::IterFnc)fnc, arg);}

    typedef bool (*SplitFnc)(W*, void*);
    tSNode<W>* Split(SplitFnc fnc, void* arg)
        {return (tSNode<W>*)bSList::Split((bSList::SplitFnc)fnc, arg);}
};

template<class W>
void Clear(tSList<W>& l)
{
	for(tSNode<W>* c= l.Root();c;)
	{
    	tSNode<W>* n= c->Next();
        delete c->What();
        c= n;
	}
	l.Root(0);
}

template<class W>
class _EXPORT_ tKeyList : public bKeyList
{
public:
    tKeyList(tKeyNode<W>* r= 0) : bKeyList(r) {}
    tKeyNode<W>* Root() const       {return (tKeyNode<W>*)root;}
    void Root(tKeyNode<W>* r)       {root= r;}

    void    Add(tKeyNode<W>& n)     {bKeyList::Add(n);}
    void    Append(tKeyNode<W>& n)  {bKeyList::Append(n);}
    bool    Remove(tKeyNode<W>& n)  {return bKeyList::Remove(n);}
    tKeyNode<W>* Remove(W* v)       {return (tKeyNode<W>*)bKeyList::Remove(v);}

    tKeyNode<W>* Split(SplitFnc fnc, void* arg) {return (tKeyNode<W>*)Split(fnc, arg);}

    typedef W* (*IterFnc)(W*, void*);
    W*      Iterate(IterFnc fnc, void* arg)
        {return (W*)bKeyList::Iterate((bKeyList::IterFnc)fnc, arg);}

    typedef bool (*SplitFnc)(W*, void*);
    tKeyNode<W>* Split(SplitFnc fnc, void* arg)
        {return (tKeyNode<W>*)bKeyList::Split((bKeyList::SplitFnc)fnc, arg);}

    W*      Find(ulong key) const   {return (W*)bKeyList::Find(key);}
};

template<class W>
void Clear(tKeyList<W> &l)
{
	for(tKeyNode<W>* c= l.Root();c;)
	{
    	tKeyNode<W>* n= c->Next();
        delete c->What();
        c= n;
	}
	l.Root(0);
}

template<class W>
class _EXPORT_ tNameList : public bNameList
{
public:
    tNameList(tNameNode<W>* r= 0) : bNameList(r) {}
    tNameNode<W>* Root() const      {return (tNameNode<W>*)root;}
    void Root(tNameNode<W>* r)      {root= r;}

    void    Add(tNameNode<W>& t)    {bNameList::Add(t);}
    void    Append(tNameNode<W>& t) {bNameList::Append(t);}
    bool    Remove(tNameNode<W>& t) {return bNameList::Remove(t);}
    tNameNode<W>* Remove(W* t)      {return (tNameNode<W>*)bNameList::Remove(t);}

    typedef W* (*IterFnc)(W*, void*);
    W*      Iterate(IterFnc fnc, void* arg)
        {return (W*)bNameList::Iterate((bNameList::IterFnc)fnc, arg);}

    typedef bool (*SplitFnc)(W*, void*);
    tNameNode<W>* Split(SplitFnc fnc, void* arg)
        {return (tNameNode<W>*)bNameList::Split((bNameList::SplitFnc)fnc, arg);}

    W*      Find(const char* name) const {return (W*)bNameList::Find(name);}
    W*      Find(ulong key) const   {return (W*)bNameList::Find(key);}
};

template<class W>
void Clear(tNameList<W>& l)
{
	for(tNameNode<W>* c= l.Root();c;)
	{
    	tNameNode<W>* n= c->Next();
        delete c->What();
        c= n;
	}
	l.Root(0);
}

template<class W>
class _EXPORT_ tLockList : public bLockList
{
public:
    tLockList(tNameNode<W>* r= 0) : bLockList(r) {}
    tNameNode<W>* Root() const      {return (tNameNode<W>*)root;}
    void Root(tNameNode<W>* r)      {root= r;}

    void    Add(tNameNode<W>& t)    {bLockList::Add(t);}
    void    Append(tNameNode<W>& t) {bLockList::Append(t);}
    bool    Remove(tNameNode<W>& t) {return bLockList::Remove(t);}
    tNameNode<W>* Remove(W* t)      {return (tNameNode<W>*)bLockList::Remove(t);}

    typedef W* (*IterFnc)(W*, void*);
    W*      Iterate(IterFnc fnc, void* arg)
        {return (W*)bLockList::Iterate((bLockList::IterFnc)fnc, arg);}

    typedef bool (*SplitFnc)(W*, void*);
    tNameNode<W>* Split(SplitFnc fnc, void* arg)
        {return (tNameNode<W>*)bLockList::Split((bLockList::SplitFnc)fnc, arg);}

    W*      Find(const char* name) const {return (W*)bLockList::Find(name);}
    W*      Find(ulong key) const   {return (W*)bLockList::Find(key);}
};

#endif // __SLIST_HPP


