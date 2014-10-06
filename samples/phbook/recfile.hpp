/*  VCS_ID
 *  $Filename:   recfile.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


/*
 * bRecordFile
 *
 * A class for reading and writing comma seperated ascii data files
 * for objects.
 */

class bRecordFile : public bFile
{
	private:
		ushort nextString, stringsRead;
		ushort maxStrings, maxSize;
		ulong err;
		char **strings;
		bString opCode;
		char *rbuf;

	public:
		bRecordFile(const char *fileName, ushort maxElements, ushort maxRecordSize);
	   ~bRecordFile();

	    void  Init();
		ulong GetRecError()		{ return err; }

	    // methods for writing records
		bool WriteRecord(const char *opCode);

    	bRecordFile& operator<< (const char *);
    	bRecordFile& operator<< (long);
    	bRecordFile& operator<< (ulong);

		// methods for reading records
		bool ReadRecord();

		bString GetOpCode()					{ return opCode;      }
		short   GetElementCount()			{ return stringsRead; }
    	bRecordFile& operator>> (bString&);
    	bRecordFile& operator>> (long&);
    	bRecordFile& operator>> (ulong&);
};

// errors

#define RfWriteError	1
#define RfReadError		2
#define RfFormatError   3
#define RfMaxStrings	4


