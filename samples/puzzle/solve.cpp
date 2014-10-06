/*  VCS_ID
 *  $Filename:   solve.cpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define InclGraphics
#define InclFixedMath
#include <ObjectPM.hpp>
#include "puzzle.hpp"	// include the class definitions

extern "C"
{
	#include <stdlib.h>
	#include <time.h>
}

/*
    physical locations
    0, 1, 2, 3, 
    4, 5, 6, 7,
    8, 9, A, B,
    C, D, E, F

char tiles[16];    

char nPosible[16]= 
{
    2, 3, 3, 2,
    3, 4, 4, 3, 
    3, 4, 4, 3,
    2, 3, 3, 2 
};

char neighbors[16][4]=  // left, up, right, down
{
    {         1,  4}, // 0
    { 0,      2,  5}, // 1
    { 1,      3,  6}, // 2
    { 2,          7}, // 3	

    {     0,  5,  8}, // 4
    { 4,  1,  6,  9}, // 5
    { 5,  2,  7, 10}, // 6
    { 6,  3,     11}, // 7

    {     4,  9, 12}, // 8
    { 8,  5, 10, 13}, // 9
    { 9,  6, 11, 14}, // 10
    {10,  7,     15}, // 11

    {     8, 13    }, // 12
    {12,  9, 14    }, // 13
    {13, 10, 15    }, // 14
    {14, 11        }, // 15
};
*/

Define_tStack(Shove)

void Puzzle :: Init(char x, char y)
{
    Size= x*y;
    tile= new char[Size];
    nNeighbors= new char[Size];
    memset(nNeighbors, 0, Size);
    Neighbor= new char[Size*4];

    for(int n= 0; n<Size; n++)
    {
        char nn= 0;
        char* N= Neighbor + n*4;
        // check neighbor above
        if(n>=x)
            N[nn++]= n-x;

        // check neighbor below
        if(n<Size-x)
            N[nn++]= n+x;

        // check neighbor to left
        if(n%y)
            N[nn++]= n-1;

        // check neighbor to right
        if((n+1)%y)
            N[nn++]= n+1;

        nNeighbors[n] = nn;
        tile[n]= n+1;
    }
    Blank= Size-1;
    tile[Blank]= 0;
}

void Puzzle :: Jumble()
{
	time_t t;
	srand((unsigned)time(&t));

    Shove* move= MoveStack.Top();
    char previous= move ?move->from :0;
    int notfirst= move!=0;

	for(unsigned i = 0; i < Size*Size; )
	{
        unsigned index= rand()%(nNeighbors[Blank]-notfirst);

        for(char* N= Neighbor+Blank*4;;N++)
            if( *N!=previous )
            {
                if(!index)
                    break;
                index--;
            }

        previous= Blank;
        MoveStack.Push( new Shove(Blank, *N) );
        DrawMove(*N, FALSE);
        i++;
        notfirst= 1;
    }
    Paint();
}

void Puzzle :: DrawMove(char from, bool paint)
{
    tile[Blank]= tile[from];
    if(paint)
        DrawTile(Blank);
    tile[from]= 0;
    Blank= from;
    if(paint)
        DrawTile(from);
}

bool Puzzle :: Move(char from)
{
    // check neighbors to see if blank
    char* N= Neighbor + from*4;
	for(unsigned i = 0; N[i]!=Blank; i++)
        if(i == nNeighbors[from])
            return FALSE;
            
    Shove* move= MoveStack.Top();
    if(move && move->from==Blank && move->to==from)
        delete MoveStack.Pop();
    else
        MoveStack.Push( new Shove(Blank, from) );

    DrawMove(from, TRUE);
    return TRUE;
}

void Puzzle :: Solve()
{
    for(;;)
    {
        Shove *move= MoveStack.Pop();
        if(!move)
            return;
        DrawMove( move->from, TRUE );
        bThread :: Sleep(1);
        delete move;
    }
}

bool Puzzle :: IsSolved()
{
    if( tile[Size-1] )
        return FALSE;

    for(int n= Size-1; n>0; n--)
    {
        if(tile[n-1]!=n)
            return FALSE;
    }

    MoveStack.Clear();
    return TRUE;
}
