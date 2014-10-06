/*  VCS_ID
 *  $Filename:   phbook.h
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define B_FIND	41
#define B_PRINITEM	41
#define B_COPY	40
#define B_DELETE	39
#define B_ADD	38
#define DOCUMENT	1
#define MP_ITEMLIST	3
#define BUT_SELECTALL	4
#define BUT_FIND	5
#define T_FULLNAME	111
#define T_OLDNAME	107
#define D_CHANGENAME 260
#define D_COPYENTRY 261
#define D_FINDENTRY 262
#define D_NEWFILE	259
#define E_FILENAME	102
#define E_NEWNAME	102
#define E_TITLE	104
#define D_PHONECARD1	256
#define D_PHONECARD2	257
#define T_TEXT	101
#define E_FIRSTNAME	102
#define E_LASTNAME  103
#define E_PHONENO	104
#define E_STREET1	105
#define E_STREET2	106
#define E_CITY	107
#define E_STATE	108
#define E_ZIP	109
#define E_COMPANY	112
#define BUT_OK	1
#define BUT_CANCEL	2

#define I_PHBOOK				11
#define I_CARD					12
#define I_MINICARD				13

#define B_OPEN					32
#define B_SAVE					33
#define B_SAVEAS				34
#define B_PRINT					35
#define B_DETAILSVIEW			36
#define B_ICONVIEW				37

#define MAINMENU				1
#define MP_PHONELIST			2
#define M_FILE					100
#define M_ITEM					200
#define M_OPTIONS				300
#define M_HELP					400

// control ids
#define NAMES		90
#define	TOOLBAR		91
#define STATUSBAR	92
#define TITLETOOLS	93


// commands...

#define CMD_BASE				112
#define MI_LOADINIT				(CMD_BASE - 1)
#define MI_NEWFILE				(CMD_BASE + 0)
#define MI_OPENFILE				(CMD_BASE + 1)
#define MI_SAVEFILE				(CMD_BASE + 2)
#define MI_SAVEAS				(CMD_BASE + 3)
#define MI_PRINTPHONEBOOK		(CMD_BASE + 4)

#define MI_SETDETAILSVIEW		(CMD_BASE + 5)
#define MI_SETICONVIEW			(CMD_BASE + 6)

#define MI_ADDENTRY				(CMD_BASE + 7)
#define MI_DELETEENTRY			(CMD_BASE + 8)
#define MI_COPYENTRY			(CMD_BASE + 9)
#define MI_FINDENTRY			(CMD_BASE + 10)

#define MI_TOGGLESTATUSBAR		(CMD_BASE + 11)
#define MI_TOGGLETOOLBAR		(CMD_BASE + 12)
#define MI_PRINTITEM			(CMD_BASE + 13)
#define MI_SETPHONEBOOKNAME		(CMD_BASE + 14)
#define MI_ARRANGEICONS			(CMD_BASE + 15)
#define MI_PRINTSETUP			(CMD_BASE + 16)
#define MI_SAVESETUP			(CMD_BASE + 17)
#define MI_PRINTSEL				(CMD_BASE + 18)

#define MI_OPENENTRY			(CMD_BASE + 19)
#define MI_DELETEONEENTRY		(CMD_BASE + 20)

#define WM_COMMAND 			0x0020
#define WM_CONTROLPOINTER 	0x0038
