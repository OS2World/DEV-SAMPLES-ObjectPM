/*  VCS_ID
 *  $Filename:   listdemo.cpp
 *  $Author  :   Jeff Knaus
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


//+*****************************************************************************
//
//	DESCRIPTION:
//
//		Demo program for bDList class.
//
//-*****************************************************************************

#define NoWindows
#include <objectpm.hpp>

#include <iostream.h>

int
cmpi_bString(const bString *a, const bString *b )
{
	return strcmpi( (const char *)*a, (const char *)*b );
}

char *Keys[] =
{
	"To",
	"The",
	"Around",
	NULL
};

short bMainThread::Start() 
{
	// create a dlist that's typed for bStrings and supports
	// comparisons (for order insert)
	tDList<bString> sl( cmpi_bString, FALSE );

	cout << "Adding first six items (using alpha sort)...\n";

	sl.OrderedInsert( new bString("Columbus") );
	sl.OrderedInsert( new bString("Sailed") );
	sl.OrderedInsert( new bString("To") );
	sl.OrderedInsert( new bString("The") );
	sl.OrderedInsert( new bString("New") );
	sl.OrderedInsert( new bString("World") );

	cout << "Last 2 inserts are end inserts.\n\n";
	sl.Insert( new bString("** THE **") );
	sl.Insert( new bString("** END **") );

	cout << "Iterating forwards:\n";
    int i;
	for ( sl.First(), i=0; sl.Current(); sl.Next(), i++ )
		cout << i << ". " << (const char *)*sl.Current() << "\n";
	cout << "\n";

	cout << "In order, by subscript:\n";
	for ( i=0; sl[i]; i++ )
		cout << i << ". " << (const char *)*sl[i] << "\n";
	cout << "\n";

	cout << "Searching for specific key elements:\n";
	for ( char **key=Keys; *key; key++ )
	{
		bString tmp(*key);
		cout << "Searching for element \"" << *key << "\"--";
		// must reset iterator before each search --bDList searches don't
		sl.First();
		bString *r = sl.Search( &tmp );
		if ( r )
			cout << "Found \"" << (const char *)*r << "\"\n";
		else
			cout << "Not found!\n";
	}
	cout << "\n";

	cout << "Removing key elements if found:\n";
	for ( key=Keys; *key; key++ )
	{
		cout << "Removing element \"" << *key << "\"--";
		// must reset iterator before each search --bDList searches don't
		sl.First();
		bString tmp(*key);
		bString *r = sl.Search( &tmp );
		if ( r )
		{
			r = sl.Remove();
			cout << "Removed \"" << (const char *)*r << "\"\n";
			delete r;
		}
		else
			cout << "Not found!\n";
	}
	cout << "\n";

	cout << "Iterating remaining elements backwards:\n";
	for ( sl.Last(), i=0; sl.Current(); sl.Prev(), i++ )
		cout << i << ". " << (const char *)*sl.Current() << "\n";
	cout << "\n";

	tDList<bString> sl2 = sl;
	cout << "Copy of the list:\n";
	for ( sl2.Last(), i=0; sl2.Current(); sl2.Prev(), i++ )
		cout << i << ". " << (const char *)*sl2.Current() << "\n";
	cout << "\n";

	return 0;
}

int
main(int argc, char* argv[])
{
	// create the two ObjectPM process/thread objects to
	// initialize the class library.  VIO programs must do this.
	bApp		thisApp;
	bMainThread priThread(argc, argv, ThreadRaw);

	cout << "\nLinked List Demonstration Program\n";
	cout << "Copyright (C) 1995 by Secant Technologies. All rights reserved.\n\n";

    return  priThread.Start();     
}

