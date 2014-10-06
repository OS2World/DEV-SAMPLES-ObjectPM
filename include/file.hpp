/*  VCS_ID
 *  $Filename:   file.hpp
 *  $Author  :   Mike Flis, John Pompeii
 *  $Revision:   1.2  $
 *  $Date:   10 Dec 1991 17:14:28  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
// FILE OBJECTS

#ifdef ObjectPMCore
  #include "filelite.hpp"
  #define __FILE_HPP
#endif

#ifndef __FILE_HPP
#define __FILE_HPP

#ifndef NoStreams
    #include <fstream.h>
#endif // NoStreams

#define NUMSORT 4	 // Number of File/Directory Sorting Methods

// file and extended attributes 
#define FileNormal     		0x0000
#define FileReadonly   		0x0001
#define FileHidden     		0x0002
#define FileSystem     		0x0004
#define FileDirectory  		0x0010
#define FileArchived   		0x0020
#define MustHaveReadonly	0x0101
#define MustHaveHidden      0x0202
#define MustHaveSystem      0x0404
#define MustHaveDirectory   0x1010
#define MustHaveArchived    0x2020
#define FileAny   FileNormal | FileReadonly | FileHidden | FileSystem | FileArchived		

enum bFilePosition
{
	FileBegin,   // Move relative to beginning of file 
	FileCurrent, // Move relative to current fptr position 
	FileEnd      // Move relative to end of file
};

#define CopyExist   1       // Copy even if destination exists
#define CopyAppend  2       // Append to end if destination exists  

#define EaBinary      0xFFFE      // length preceeded binary
#define EaAscii       0xFFFD      // length preceeded ASCII
#define EaBitmap      0xFFFB      // length preceeded bitmap
#define EaMetafile    0xFFFA      // length preceeded metafile
#define EaIcon        0xFFF9      // length preceeded icon
#define EaEa          0xFFEE      // length preceeded ASCII
                                  // name of associated data (#include)
#define EaMVMT        0xFFDF      // multi-valued, multi-typed field
#define EaMVST        0xFFDE      // multi-valued, single-typed field
#define EaASN1        0xFFDD      // ASN.1 field

#define FileEOF      (-1)
#define FileStdin    0
#define FileStdout   1
#define FileStderr   2

class _EXPORT_ bFileName
{
	private:
        char    buffer1[260];
        char    buffer2[260];
		char*   drive;
		char*   dir;
        char*   name;
        char*   ext;
		const char*   filename;
        char*   pathname;

	public:
		bFileName();
		ulong   Parse(const char *p, bool fDir = FALSE, bool fNorm = FALSE);
		ulong   Build(char drv, const char *dir, const char *fname, const char *ext, bool fMod = TRUE);
        ulong   Build(const char* env, const char* nm);
		const char* Filename()    const { return filename; }
		const char* Pathname()    const { return pathname;}
		char  Drive() 	 		  const { return *drive; }
		const char* Dir()      	  const { return dir; }
		const char* Name()     	  const { return name; }
		const char* Ext()		  const { return ext; }
};

class _EXPORT_ bExtAttr
{
	private:
		ushort	EAType, EALength;
		bString sAttr;
	public:
    	bExtAttr(ushort t, ushort l, const void *s);
		bExtAttr(const char *s);
		bExtAttr(bExtAttr& e)	
			{ EAType = e.EAType; EALength = e.EALength;	sAttr = e.sAttr; }

		ushort  Type()       	const { return EAType; }
		ushort  Length()	    const { return EALength; }
		bString Attribute()		{ return sAttr; }
};

class _EXPORT_ bEAList : public tDList<bExtAttr>
{
	private:
		ushort	ltype,			// EaMVMT, EaMVST, or EaASN1
				codepage;
		byte	flags;
	public:
    	bEAList(ushort lt=0) : tDList<bExtAttr>(TRUE) { ltype=lt; codepage=0; flags=0; }
		ushort	ListType()  	const { return ltype; }	
		ushort	Size();
		ushort	&bCodePage()	{ return codepage; }
		byte	&Flags()		{ return flags; }
};

enum bFSType 
{
	FSTypeDirectory,
	FSTypeFile
};

#ifndef DosOpen2
struct _FILESTATUS3;
typedef _FILESTATUS3 FILESTATUS3;
#endif

class _EXPORT_ bFileInfo
{
	public:
		bTimeStamp	create;
        bTimeStamp	lastacc;
        bTimeStamp	lastwr;
		ulong	    size;
        ulong       alloc;
        ulong       attr;

		bFileInfo();
		bFileInfo(const char* fileName) { SetInfo(fileName); }

        bool    IsValid()           const { return attr!=0xffff0000; }

		bTimeStamp Created()	    const { return create; }
		bTimeStamp LastAccess()     const { return lastacc; }
		bTimeStamp LastWrite()      const { return lastwr; }

		ulong   Size()		        const { return size; }
		ulong   AllocatedSize()     const { return alloc; }
		ulong   Attributes()	    const { return attr; }

        bool    SetInfo(ulong fileHandle);
        bool    SetInfo(const char* fileName);
        void    SetInfo(FILESTATUS3* status);

		bDate   DateCreated()	    const { return (bDate)create; }
		bDate   DateLastAccess()    const { return (bDate)lastacc; }
		bDate   DateLastWrite()     const { return (bDate)lastwr; }
		bTime   TimeCreated()	    const { return (bTime)create; }
		bTime   TimeLastAccess()    const { return (bTime)lastacc; }
		bTime   TimeLastWrite()     const { return (bTime)lastwr; }
};

const HFILE FileInvalid = 0xffffffff;

class _EXPORT_ bFSFile
{
	protected:
		HFILE       hf;
		ulong       err;
        bString     path;

		bFileInfo   fi;
		bDirectory* parentDir;
        const char* buildPath() const;

		bFSFile(bDirectory* parent);
		bool        IsOpen()    const   { return hf!=FileInvalid; }

	public:
		virtual     ~bFSFile();

		bString     FullPath()      const;
		const char* Name()          const { return buildPath(); }

		ulong       Error()         const { return err; }
	    bDirectory* Parent()        const { return parentDir; }

        int         cmp_FSFile(const bFSFile *test, const char* order) const;

		bFileInfo*  FileInfo();
		bool        Exists();
    	bStringList* EnumEA();
    	bool        ExistEA(const char *AttrName);	
		bEAList*    GetEA(const char *AttrName);
    	bool        SetEA(const char *AttrName, bEAList *pMVList);
    	bool        SetEA(const char *AttrName, bExtAttr Attribute);
		bool        DeleteEA(const char *AttrName);

		ulong       Copy(const char* dstName, ulong flags= 0);
//		ulong       Rename(const char* newName);
};

class bDirList;
class bFileList;

class _EXPORT_ bDirectory : public bFSFile
{
	private:
		bDirList*   dirList; 
		bFileList*  fileList;
        bString forder;
        bString dorder;

	public:
    	bDirectory(const char* dir, const char* forder= "N+E+",
            const char* dorder= "N+E+", bDirectory* parent= 0);
    	~bDirectory();

    	unsigned AddFiles(const char *fs, ulong attrib = (FileNormal | FileArchived));
    	unsigned AddDirectories(const char *fs, ulong attrib = 0) 
			   { return AddFiles(fs, attrib | MustHaveDirectory); } 

		bDirList*   Directories()   const { return dirList; }
		bFileList*  Files()         const { return fileList; }
};

enum OpenFlags
{
    OpenFlagsDasd             = 0x8000,
    OpenFlagsFailOnError      = 0x2000,
    OpenFlagsNoInherit        = 0x0080,
    OpenFlagsWriteThrough     = 0x4000,
    OpenFlagsNoLocality       = 0x0000,
    OpenFlagsSequential       = 0x0100,
    OpenFlagsRandom           = 0x0200,
    OpenFlagsRandomSequential = 0x0300,
    OpenFlagsNoCache          = 0x1000
};

class _EXPORT_ bFile : public bFSFile
{
	private:
	    char        fAppend;
        char        fTextMode;
        char        fAtEnd;
        char        fPad;
	    ulong       TextWrite(const char *s, long size);

	public:
		bFile(const char* nm, pbDirectory _pDir = NULL);
        bFile(HFILE f);
	    ~bFile();

		ulong       Open(const char *szOpenMode, ulong addModeFlags = 0, ulong attCreat = FileNormal);
    	ulong       Close();
        void        SetMode(bool Text, bool Append) {fTextMode= Text!=0; fAtEnd= (fAppend= Append!=0)!=0;}
		bool        IsOpen()    const   { return hf!=FileInvalid; }
		HFILE       Handle()    const   { return hf; }
		ulong       Seek(long offset, bFilePosition origin = FileBegin);
		long        Position(); 
		ulong       Write(const void *p, ulong size, ulong count = 1);
		ulong       Write(char c);
		ulong       Write(const char *s);
		ulong       FPrintf(const char *fmt, ...);
		ulong       Read(void *p, ulong size, ulong count = 1);
		short       Read();
		char*       Read(char *s, ulong n); 
		bool        IsEOF();
		long        GetSize();
		ulong       ChangeSize(ulong size);
		ulong       Flush();
		ulong       Delete();

        // IOCtl
        ulong       IOCtl(ulong Cat, ulong Fnc, void* parm, ulong plen, ulong *pAct, void* data, ulong dlen, ulong *dAct);
        ulong       IOCtlParm(ulong Cat, ulong Fnc, void* parm, ulong plen)
            { ulong act=plen; return IOCtl(Cat, Fnc, parm, plen, &act, 0, 0, 0) ?0 :act;}
        ulong       IOCtlData(ulong Cat, ulong Fnc, void* data, ulong dlen)
            { ulong act=dlen; return IOCtl(Cat, Fnc, 0, 0, 0, data, dlen, &act) ?0 :act;}
};   

class _EXPORT_ bDirList : public tSort<bDirectory>
{
	private:
		bDirectory* parent;
		bString order;
	    virtual int Compare(const bTreeNode *a, const bTreeNode *b);

	public:
		bDirList(bDirectory* dir, const char* order= "N+E+");
		bDirectory* Parent() const  { return parent; }
};

class _EXPORT_ bFileList : public tSort<bFile>
{
	private:
		bDirectory* parent;
		bString order;
	    virtual int Compare(const bTreeNode *a, const bTreeNode *b);

	public:
		bFileList(bDirectory* dir, const char* order= "N+E+");
		bDirectory* Parent() const  { return parent; }
};

#ifndef NoStreams
class _EXPORT_ bFileStream : public bFile, public fstream
{
	public:
		bFileStream(const char *nm, pbDirectory _pDir = NULL);
		ulong       Open(const char *szOpenMode, ulong addModeFlags = 0, ulong attCreat = FileNormal);
    	ulong       Close();
};
#endif // NoStreams

#endif // __FILE_HPP
