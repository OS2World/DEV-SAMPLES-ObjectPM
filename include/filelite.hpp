/*  VCS_ID
 *  $Filename:   filelite.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.2  $
 *  $Date:       $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#ifndef __FILE_HPP
#define __FILE_HPP

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

class bDirectory;

class bFile
{
	private:
		ulong hf;
		ulong	err;
		char *name;
		
	public:
		bFile(const char *nm, bDirectory *_pDir = NULL);
		~bFile();
		ushort  Open(const char *szOpenMode, ushort addModeFlags = 0, ushort attCreat = FileNormal);
		bool    IsOpen()		    const   { return (hf != 0xffff); }
		ushort  Seek(long offset, bFilePosition origin = FileBegin);
		long    Position(); 
		ulong   Read(void *p, ushort size, ushort count = 1);
		char   *Read(char *s, ushort n); 
    	ushort  Close();
		ushort  Error()         const { return (ushort) err;     }
};

#endif // __FILE_HPP
