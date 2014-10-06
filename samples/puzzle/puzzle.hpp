/*  VCS_ID
 *  $Filename:   puzzle.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:44:02  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
#include "about.h"
#include "puzzle.h"

// Top level window class for graph class

class Tile : public wPicture
{
	private:
		short n;

	public:
		Tile(wPresSpace *ps, short tileNo) : 
			wPicture(ps, FALSE, FALSE) { n = tileNo; } 
		short TileNumber() { return n; }
};
				   
struct Shove
{
    char from, to;
    Shove(char f, char t) : from(f), to(t) {}
};

class Puzzle
{
	private:
		wSubPicture *tilePic;
		wPointl     tilePos[16];
		wDimension  tileSize;
		wPresSpace *ps;
		wFont *font;
		bool jumbled;
        char*   tile;
        char*   nNeighbors;
        char*   Neighbor;
        char    Size;
        char    Blank;

        void    Init(char x, char y);
        void    DrawMove(char from, bool paint);
        tStack<Shove> MoveStack;

	public:
		Puzzle(wPresSpace *_ps);
        ~Puzzle();
        bool    Move(char from);
		void    DrawTile(char t);
        void    Paint();
		wDimension& TileSize() { return tileSize; }
		short HitTest(wPointl p);
		bool  IsSolved();
		void  Jumble();
		void  Solve();
		wPresSpace *pPS() { return ps; }
};


class PuzzleFrame : public wFrameWindow
{
	private:
		wIcon *icon;
		wMenu *menubar;
		Puzzle *puz;

		void Paint();
		long MenuCommand(wCommandMsg);
		long ButtonClick(wButtonClickMsg);
		long Size(wSizeMsg);

	public:
		PuzzleFrame();
		~PuzzleFrame();
};

class AboutDialog : public wDialogWindow
{
	public:
		AboutDialog(wWindow *owner) : 
			wDialogWindow(D_ABOUT) { CreateWindow(owner); }
		long InitDlg(wInitDlgMsg)               { ChangePosition(PosCenter, OwnerWindow()); return FALSE; }
		long PushButtonCommand(wCommandMsg)     { Dismiss(); return FALSE; }
};

