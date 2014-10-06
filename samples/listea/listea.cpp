/*  VCS_ID
 *  $Filename:   listea.cpp
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
	#include "args.c"
}

int count = 0;

#define MAXEA 9
char	*eatype[MAXEA]={"EAT_BINARY","EAT_ASCII","EAT_BITMAP","EAT_METAFILE","EAT_ICON",
				  "EAT_EA","EAT_MVMT","EAT_MVST","EAT_ASN1"};
long	eaval[MAXEA]={EaBinary,EaAscii,EaBitmap,EaMetafile,EaIcon,EaEa,EaMVMT,
						EaMVST,EaASN1};

void* PrintEAVal(bExtAttr *e)
{
	int		lp;

	if (count)
		printf("\n                      ");
	for (lp=0 ; lp < MAXEA && eaval[lp] != e->Type(); lp++)	// FIND THE TYPE
		;

	printf("%-12s ",lp<MAXEA ? eatype[lp] : "");	// DISPLAY IT
	if (lp == 1)	// EAT_ASCII
		printf("%s", (const char *)e->Attribute());
	else
		printf("(Binary Data)");
	count++;
	return 0;
}

void PrintHelp()
{
	printf("Usage: LISTEA <Options> <list of filenames>\n");
	printf("Options: -s     Skip files without extended attributes\n");
	printf("         -h     Display this screen\n");
}


#define HELP   	1
#define SKIP	2

short bMainThread::Start() 
{
	File	*f;
	bStringList	*ev;
	int		lp, ex;
	long	opt = 0, 
			flg[]={SKIP,HELP};
	char	l[]={'S','H'};

	if (argc < 2)
	{
		PrintHelp();
		return 1;
	}
	lp=1;
	opt=SetOptionFlags(argc,argv,&lp,"-/",TRUE,3,l,flg);
	if (opt & HELP)
	{
		PrintHelp();
		return 0;
	}
	for ( ; lp < argc ; lp++)
	{
		f=new File(argv[lp]);
		ex = f->Exists();
		ev = f->EnumEA();
		if ( (opt & SKIP) && (ev->IsEmpty() || !ex) ) continue;

		printf("==============================================================================\n");
		printf("Extended Attributes of %s\n", argv[lp]);
		printf("------------------------------------------------------------------------------\n");
		if (!ex)	// FILE DOES NOT EXIST
		{
			printf("%s does not exist\n",argv[lp]);
			continue;
		}
		if (ev->IsEmpty())	// FILE HAS NO EXTENDED ATTRIBUTES
			printf("-- None --\n");
		else
		{
			printf("Name                  Type         Value(s)");

			bEAList	*eal;			// LIST OF ACTUAL VALUES 
			bStringList *l = f->EnumEA();	// LIST OF EA NAMES (ie. .SUBJECT, .TYPE)
			if (l->First())
				do
				{
					printf("\n%-22s", (const char *)(*(l->Current())));	// DISPLAY THE EA NAME
					eal=f->GetEA(**(*l));		// GET THE VALUES
					count = 0;
					if (eal)
						eal->Apply(PrintEAVal);	// DISPLAY THEM

					putchar('\n');
				} while (l->Next());
		}
		delete f;
		delete ev;
	}
	printf("==============================================================================\n");
	return 0;
}

main(int argc, char **argv)
{
	bApp		thisApp;
	bMainThread	priThread(argc, argv, ThreadRaw);

	printf("LISTEA - List Extended Attributes. Copyright (C) 1995 by Secant Technologies.\n\n");
    return priThread.Start();
}

