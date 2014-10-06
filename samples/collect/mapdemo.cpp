/*  VCS_ID
 *  $Filename:   mapdemo.cpp
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
//		Sample program for bMap class.
//
//		Note the use of the overloaded operator* used as a shorthand for
//		returning the current value at the iterator position for collections.
//
//-*****************************************************************************

#define NoWindows
#include <objectpm.hpp>

#include <iostream.h>

int
cmpi_bString( const bString *a, const bString *b )
{
	return strcmpi( (const char *)*a, (const char *)*b );
}

class Thing
{
	public:
		char *theName;
		USHORT theNum;

		Thing( char *name, USHORT num )
			{ theName=strcpy(new char[strlen(name)+1], name); theNum=num; }
		~Thing()
			{ delete theName; }
		int operator-( Thing& other )
			{ int r; return ((r=strcmpi(theName,other.theName)) != 0) ? r : (theNum-other.theNum); }
};

char *Keys[] =
{
	"A",
	"C",
	"Y",
	"Z",
	NULL };

Define_tMap(bString, Thing) // instantiate the template methods

short bMainThread::Start() 
{
	// create mappng of uniquely keyed elements that is self purging og
	// both keys and values
	tMap<bString, Thing> map( cmpi_bString, TRUE, TRUE, TRUE );

	cout << "Adding elements with separate keys and values...\n";

	// insert some stuff
	int i = 0;
	map.InsertAssoc( new bString("X"), new Thing("X", i++) );
	map.InsertAssoc( new bString("B"), new Thing("B", i++) );
	map.InsertAssoc( new bString("X"), new Thing("X", i++) );
	map.InsertAssoc( new bString("B"), new Thing("B", i++) );
	map.InsertAssoc( new bString("Z"), new Thing("Z", i++) );
	map.InsertAssoc( new bString("B"), new Thing("B", i++) );
	map.InsertAssoc( new bString("B"), new Thing("B", i++) );
	map.InsertAssoc( new bString("J"), new Thing("J", i++) );
	map.InsertAssoc( new bString("A"), new Thing("A", i++) );

	// iterating through the elements of the mapping
	cout << "Iterating forwards:\n";
	for ( map.First(), i=0; map.Current(); map.Next(), i++ )
	{
		cout << i << ". " << (*map)->theName << "(" << (*map)->theNum << ")\n";
	}
	cout << "\n";

	// iterating even elements using an external iterator
	cout << "Even elements in order, using iterators:\n";
	tMapIterator<bString, Thing> evenIt( &map );
	for ( evenIt.First(), i=0; *evenIt; i+=2, evenIt+=2 )
	{
		cout << i << ". " << (*evenIt)->theName << "(" << (*evenIt)->theNum << ")\n";
	}
	cout << "\n";

	// searching for specific exact keys
	cout << "Searching for elements by key\n";
	for ( char **key=Keys; *key; key++ )
	{
		bString tmp(*key);

		cout << "\tSearching for element with key = \"" << *key << "\"--";
		Thing *r = map.Search( &tmp );
		if ( r )
			cout << "Found " << r->theName << "(" << r->theNum << ")\n";
		else
			cout << "Not found!\n";
	}
	cout << "\n";

	// go through the array of keys, looking up each key in the mapping
	// when the key is found, remove the association from the mapping and
	// free the key and value components
	cout << "Removing elements that match keys\n";
	for ( key=Keys; *key; key++ )
	{
		cout << "\tRemoving element with key=\"" << *key << "\"--";
		bString tmp(*key);
		Thing *r = map.Search( &tmp );
		bString *k;
		if ( r )
		{
			r = map.RemoveAssoc( &k );
			cout << "Removed " << r->theName << "(" << r->theNum << ")\n";
			delete r;
			delete k;
		}
		else
			cout << "Not found!\n";
	}
	cout << "\n";

	cout << "What's left:\n";
	for ( map.First(), i=0; map.Current(); map.Next(), i++ )
			cout << (*map)->theName << "(" << (*map)->theNum << ")\n";
	cout << "\n";

	// make a copy of the mapping with non-self-purging data and keys
	tMap<bString, Thing> map2 = map;

	// this is an example of using an external iterator to iterate through
	// the elements of the mapping - we also show how to access the key
	// at a specific location with the CurrentKey method
	cout << "Using an iterator to iterate through the copy:\n";
	tMapIterator<bString, Thing> it( &map2 );
	for ( map2.First(&it), i=0; map2.Current(&it); map2.Next(&it), i++ )
	{
		Thing *value= map2.Current(&it);

		cout << i << ". Key "
			<< (const char *)*map2.CurrentKey(&it) << ", Value < Name "
			<< value->theName << ", Num "
			<< value->theNum << " >\n";
	}
	cout << "\n";

	// since our mapping is not self-purging, we need to remove the
	// elements from it before the mapping gets destructed (when it goes out of
	// scope) - we do this by successively setting the internal iterator to
	// the beginning of the mapping, then removing the association at that
	// location from the mapping.

	while ( map2.First() )
	{
		bString *key;  // to hold the returned key pointer
		Thing *value = map2.RemoveAssoc( &key );

		// free the key and value objects
		cout << "Removing < Name "
			<< value->theName << ", Num "
			<< value->theNum << " >\n";

	}

	return 0;

	// when the mappings go out of scope, they get destructed automatically

	// the elements of the self-purging mapping (map) will get destructed
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

	cout << "\nSimple Mapping Demonstration Program\n";
	cout << "Copyright (C) 1995 by Secant Technologies. All rights reserved.\n\n";

    return  priThread.Start();     
}

