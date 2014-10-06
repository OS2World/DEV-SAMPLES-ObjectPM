/*  VCS_ID
 *  $Filename:   bsetypes.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.6  $
 *  $Date:   03 Jan 1992 08:17:56  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __BSETYPES_HPP
#define __BSETYPES_HPP

class bThread;

class bMainThread;
class bCondition;
class bApp;
class bEventHandler;
class bConditionHandler;
class bDList;
class bDArray;
class bTree;
class bBitArray;
class bQueue;
class bStack;
class bStrList;
class bSemaphore;
class bSemaphoreList;
class bMutexSemaphore;
class bEventSemaphore;
class bString;
class bFacility;
class bFileName;
class bExtAttr;
class EAList;
class bEAList;
class bFileList;
class bFile;
class bFileList;
class bDirList;
class bDirectory;
class bDirList;
class bFSFile;
class bDirectory;
class bFile;
class bFileStatus;
class bProfile;
class fDataType;

typedef bThread *pbThread;
typedef bProfile *pbProfile;
typedef bCondition *pbCondition;
typedef bApp *pbApp;
typedef bConditionHandler *pbConditionHandler;
typedef bDList *pbDList;
typedef bDArray *pbDArray;
typedef bTree *pbTree;
typedef bBitArray *pbBitArray;
typedef bQueue *pbQueue;
typedef bStack *pbStack;
typedef bStrList *pbStrList;
typedef bSemaphore *pbSemaphore;
typedef bSemaphoreList *pbSemaphoreList;
typedef bDirectory *pbDirectory;
typedef bFile *pbFile;
typedef bFileStatus *pbFileStatus; 
typedef fDataType *pfDataType;

#ifndef NOMIGRATE

typedef bThread Thread;
typedef bMainThread MainThread;
typedef bDList DList;
typedef bStrList StrList;
typedef bString String;
typedef bFile File;
typedef bDirectory Directory;

#endif

#ifdef NULL
#undef NULL
#endif
#define NULL 0

enum bThreadResc
{
	ThreadRaw,
	ThreadAnchBlock,
	ThreadFull
};

#endif // __BSETYPES_HPP
