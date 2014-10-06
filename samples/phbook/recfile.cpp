/*  VCS_ID
 *  $Filename:   recfile.cpp
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

#define InclFiles
#define InclCFunctions
#include <ObjectPM.hpp>

#include "recfile.hpp"
extern "C"
{
	#include <string.h>
	#include <stdlib.h>
}


bRecordFile :: bRecordFile(const char *fileName, ushort maxElements, ushort maxRecordSize)
			 : bFile (fileName, NULL)
{
	ushort i = 0;

	err = nextString = stringsRead = 0;
	maxStrings = maxElements;
	maxSize = maxRecordSize;
	rbuf = new char[maxSize + 1];
	strings = new char *[maxElements];

	for (i = 0; i < maxElements; i++)
		strings[i] = NULL;
}

bRecordFile :: ~bRecordFile()
{
	ushort i;

	for (i = 0; strings[i] != NULL; i++)
		delete strings[i];

	delete strings;
	delete rbuf;
}

void bRecordFile :: Init()
{
	ushort i;

	for (i = 0; strings[i] != NULL; i++)
	{
		delete strings[i];
		strings[i] = NULL;
	}
	nextString = stringsRead = 0;
}

bool bRecordFile :: WriteRecord(const char *_opCode)
{
	ushort i, rc = 0;
	opCode = _opCode;
	err = 0;

	rc |= Write(opCode);
	rc |= Write(',');

	if (!rc)
	{
		for (i = 0; i < nextString; i++)
		{
			if (i)
			{
				if ((rc = Write(',')) != 0)
					break;
			}
			if ((rc = Write(strings[i])) != 0)
 				break;
		}
		Write("\r\n");
	}
	Init();
	if (rc)
	{
		err = RfWriteError;
		return FALSE;
	}
	return TRUE;
}
		
bRecordFile& bRecordFile :: operator<< (const char *cp)
{
	char c;

	if (*cp)
	{
		ushort n = 3;
		const char *cp2 = cp;
		char *tp;
 
		while ((c = *cp2++) != '\0')
		{
			if (c == '"' || c == '\\' || c == ',')
				n++;

			n++;
		}
 		tp = strings[nextString++] = new char[n];
		*tp++ = '"';
		while ((c = *cp++) != '\0')
		{
			if (c == '"' || c == '\\' || c == ',')
				*tp++ = '\\';

			*tp++ = c;
		}
		*tp++ = '"';
		*tp = '\0';
	}
	else
	{
 		strings[nextString] = new char[1];
		strings[nextString++][0] = '\0';
	}
	return *this;
}
    	
bRecordFile& bRecordFile :: operator<< (long l)
{
	strings[nextString] = new char[12];
	ltoa(l, strings[nextString++], 10);
	return *this;
}

bRecordFile& bRecordFile :: operator<< (ulong l)
{
	strings[nextString] = new char[12];
	ultoa(l, strings[nextString++], 10);
	return *this;
}

bool bRecordFile :: ReadRecord()
{
	char *bp, *cp, c;

	Init();
	err = 0;
	Read(rbuf, maxSize);

	if (Error())
	{
		err = RfReadError;
		return FALSE;
	}
	cp = strtok(rbuf, ",");
	if (strblank(cp))
	{
		err = RfFormatError;
		return FALSE;
	}
	opCode = cp;
	bp = cp = strtok(NULL, "");
	c = *cp;

	while (c)
	{
		if (nextString == maxStrings)
		{
			err = RfMaxStrings;
			return FALSE;
		}
		while ((c = *cp) != ',' && c != '\0')
		{
			if (c == '\\' || c == '"')
			{
				strdel(cp, 1);
				if (c == '\\')
					cp++;
			}
			else cp++;
		}
		*cp++ = '\0';
		strings[nextString] = new char [strlen(bp) + 1];
		strcpy(strings[nextString++], bp);
		stringsRead++;
		bp = cp;
	}
	nextString = 0;
	return TRUE;
}

bRecordFile& bRecordFile :: operator>> (bString& s)
{
	if (nextString < stringsRead)
		s = strings[nextString++];
	
	return *this;
}
    	
bRecordFile& bRecordFile :: operator>> (long& l)
{
	if (nextString < stringsRead)
		l = atol(strings[nextString++]);
	
	return *this;
}

bRecordFile& bRecordFile :: operator>> (ulong& l)
{
	if (nextString < stringsRead)
		l = atol(strings[nextString++]);
	
	return *this;
}

    	
