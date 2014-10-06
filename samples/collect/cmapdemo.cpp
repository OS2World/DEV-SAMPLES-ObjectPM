/*  VCS_ID
 *  $Filename:   cmapdemo.cpp
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
//		Sample program for bCMap class.
//
//		Note the use of the overloaded operator* used as a shorthand for
//		returning the current value at the iterator position for collections.
//
//		Also, note the use of the overloaded "operator(const char *)" to cast
//		the bString (returned from Current() in our demo) to a printable const
//		char * value.
//
//-*****************************************************************************

#define NoWindows
#include <objectpm.hpp>

#include <iostream.h>

class Thing
{
	public:
		char *theName;
		USHORT theNum;

		// constructor that initializes members
		Thing( char *name, USHORT num=0 )
		{
			theName = name ? strdup( name ) : NULL;
			theNum = num;
		}

		// destructor that frees the name
		~Thing()
		{
			delete theName;
		}

};

// registers type "Thing" with the DTRepository

bType regThing(
	"Thing",   bType::StructField, 2,                   // 2 elements
	"theName", FIELD_OFFSET(Thing, theName), 1,         // dereference once
	"theNum",  FIELD_OFFSET(Thing, theNum),  0 );       // embedded data

// an array of keys to to looked up in the mapping

Thing keys[] =
{
	Thing("O", 2),
	Thing("B", 1),
	Thing("C", 1),
	Thing("X", 2),
	Thing("Z", 9),
	NULL
};

Define_tCMap(Thing, bString); // instantiate the template methods

short bMainThread::Start()
{
	// mapping of Things to bStrings, non-unique, purge keys and elements
	tCMap<Thing, bString> cmap( "Thing", FALSE, TRUE, TRUE );

	// specify the sort criteria for the mapping - by theName, then theNum
	cmap.SortBy( 2,
		"theName", (CompareFunc)cmpi_STRING, TRUE,
		"theNum",  (CompareFunc)cmp_USHORT,  TRUE );

	cout << "Adding elements (sorted by name then number ascending)...\n";

	// add a few elements to the mapping
	cmap.InsertAssoc( new Thing("A", 3), new bString("A-3 (00)") );
	cmap.InsertAssoc( new Thing("X", 2), new bString("X-2 (09D)") );
	cmap.InsertAssoc( new Thing("B", 1), new bString("B-1 (01D)") );
	cmap.InsertAssoc( new Thing("Z", 3), new bString("Z-3 (10)") );
	cmap.InsertAssoc( new Thing("M", 2), new bString("M-2 (04)") );
	cmap.InsertAssoc( new Thing("J", 1), new bString("J-1 (02)") );
	cmap.InsertAssoc( new Thing("L", 3), new bString("L-3 (03)") );
	cmap.InsertAssoc( new Thing("N", 2), new bString("N-2 (05)") );
	cmap.InsertAssoc( new Thing("O", 1), new bString("O-1 (06)") );
	cmap.InsertAssoc( new Thing("O", 2), new bString("O-2 (07D)") );
	cmap.InsertAssoc( new Thing("O", 3), new bString("O-3 (08)") );

	// iterating through the elements of the mapping
	cout << "Iterating forwards:\n";
    int i;
	for ( cmap.First(), i=0; cmap.Current(); cmap.Next(), i++ )
	{
		cout << i << ". " << (const char *)*cmap.Current() << "\n";
	}
	cout << "\n";

	// iterating even elements using subscripts
	cout << "Even elements in order, using subscripts:\n";
	for ( i=0; cmap[i]; i+=2 )
	{
		cout << i << ". " << (const char *)*cmap[i] << "\n";
	}
	cout << "\n";

	// iterating even elements using an external iterator
	cout << "Even elements in order, using iterators:\n";
	tCMap<Thing, bString>::Iter evenIt( &cmap );

	for ( evenIt.First(), i=0; *evenIt; i+=2, evenIt+=2 )
	{
		cout << i << ". " << (const char *)**evenIt << "\n";
	}
	cout << "\n";

	// a couple examples of approximate searching for keys whose
	// first sort field matches the specified values...

	cout << "Searching for elements with name='O':\n";
	Thing	thingo("O");
	for ( cmap.ApproxSearch( &thingo, 1 );
			*cmap;
				cmap.NextMatching( &thingo, 1 ) )
	{
		cout << "\tFound " << (const char *)**cmap << "\n";
	}
	cout << "Done searching\n\n";

	cout << "Searching for elements with name='K':\n";
	Thing thingk("K");
	for ( cmap.ApproxSearch( &thingk, 1 );
			*cmap;
				cmap.NextMatching( &thingk, 1 ) )
	{
		cout << "\tFound " << (const char *)**cmap << "\n";
	}
	cout << "Done searching\n\n";

	// go through the array of keys, looking up each key in the mapping
	// when the key is found, remove the association from the mapping and
	// free the key and value components

	cout << "Removing elements associated with specified keys: \n";
	for ( i=0; i<5; i++ )
	{
		cout << "\tRemoving < Name "
			<< keys[i].theName << ", Num "
			<< keys[i].theNum << " >  ";

		// search for the next key in our array
		bString *r = cmap.Search( &keys[i] );

		// if found, its value will be in r and intenal iterator will be set
		if ( r )
		{
			Thing *k;

			// remove association from the mapping and return its key and value
			r = cmap.RemoveAssoc( &k );
			cout << "Found.\n";

			// free the key and value objects
			delete r;
			delete k;
		}
		else
			cout << "Failed!\n";
	}
	cout << "\n";

	cout << "What's left?\n";
	for ( cmap.First(), i=0; cmap.Current(); cmap.Next(), i++ )
		cout << i << ". " << (const char *)*cmap.Current() << "\n";
	cout << "\n";

	// make a copy of the mapping with non-self-purging data and keys
	tCMap<Thing, bString> cmap2 = cmap;

	// this is an example of using an external iterator to iterate through
	// the elements of the mapping - we also show how to access the key
	// at a specific location with the CurrentKey method

	cout << "Using an iterator to iterate through the copy:\n";
	tCMap<Thing, bString>::Iter it( &cmap2 );

	for ( it.First(), i=0; it.Current(); it.Next(), i++ )
	{
		Thing *key= it.CurrentKey();
		cout << i << ". Key < Name "
			<< key->theName << ", Num "
			<< key->theNum << " >, Data "
			<< (const char *)*it.Current() << "\n";
	}
	cout << "\n";

	// since our mapping is not self-purging, we need to remove the
	// elements from it before the mapping gets destructed (when it goes out of
	// scope) - we do this by successively setting the internal iterator to
	// the beginning of the mapping, then removing the association at that
	// location from the mapping.  The memory for these objects is actually
	// freed automatically by the collection class (specified in the
	// constructor to purge keys and elements).

	while ( cmap2.First() )
	{
		Thing *key;  // to hold the returned key pointer
		cmap2.RemoveAssoc( &key );

		// free the key and value objects
		cout << "Removing < Name "
			<< key->theName << ", Num "
			<< key->theNum << " >\n";

	}

	return 0;

	// when the mappings go out of scope, they get destructed automatically

	// the elements of the self-purging mapping (cmap) will get destructed
	// appropriately because we specified their types when we declared the
	// mapping using the template

	// we chose to specify it as a non-self-purging mapping, so we had to
	// remove and free its elements ourselves - if we hadn't, the elements
	// would not have gotten freed when the mapping was destructed
}

int
main(int argc, char* argv[])
{
	// create the two ObjectPM process/thread objects to
	// initialize the class library.  VIO programs must do this.
	bApp		thisApp;
	bMainThread priThread(argc, argv, ThreadRaw);

	cout << "\nComplex-Mapping Demonstration Program\n";
	cout << "Copyright (C) 1995 by Secant Technologies. All rights reserved.\n\n";

    return  priThread.Start();     
}

