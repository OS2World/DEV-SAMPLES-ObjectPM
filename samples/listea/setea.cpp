/*  VCS_ID
 *  $Filename:   setea.cpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.2  $
 *  $Date:   06 Jan 1992 03:03:36  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#define NoWindows
#define InclFiles
#include <ObjectPM.hpp>

extern "C" {
	#include <stdio.h>
	#include <string.h>
}

short 
bMainThread::Start() 
{
	char 	*cp;
	SHORT	len, lp;
	BOOL	rc;
	bEAList	*bl;

	if (argc < 4)	// check # of arguments
	{
		printf("Usage: SETEA <filename> <EA name> [/D] <EA value> <EA value> ... \n");
		printf("  Where /D specifies delete - EA values are ignored\n");
		printf("  EG:  SETEA temp.doc .SUBJECT \"Temporary Stuff\" \"More Stuff\"\n");
		printf("  Note that you can only set EA as ascii strings\n");
		return 2;
	}

	bFile	f(argv[1]);	// make a file 

	// if argc>4, more than one value for this ea so use a multi-value
	// single-type (eat_ascii) list else just use an eat_ascii list (of one)
	if (argc > 4)
		bl = new bEAList(EaMVST);
	else
		bl = new bEAList(EaAscii);

	if (stricmp(argv[3], "/D") == 0)	// delete the ea?
		rc = f.DeleteEA(argv[2]);
	else
		for (lp=3 ; lp<argc ; lp++)		// set them
		{
			// strip double quotes from ea value
			cp = argv[lp];	
			if (*cp == '\"')
				cp++;
			len = strlen(cp)-1;
			if (cp[len] == '\"')
				cp[len]=0;

			// insert it into the ea list -- use alternate bextattr that takes a string
			bl->Insert(new bExtAttr(cp));	
		}

	// and set the ea(s)
	rc = f.SetEA(argv[2], bl);

	printf("SetEA finished %s\n", rc ? "successfully":"unsuccessfully");

	delete bl;

	return !rc;
}

main(int argc, char **argv)
{
	bApp		thisApp;
	bMainThread	priThread(argc, argv, ThreadRaw);
    return priThread.Start();
}

