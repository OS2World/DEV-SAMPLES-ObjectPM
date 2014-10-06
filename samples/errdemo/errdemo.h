/*  VCS_ID
 *  $Filename:   errdemo.h
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


#define ITriangle I_OBJPM

#define LASTMSG     	4		/* index of the last message string */
#define MBarError   	100		/* menu id's */
#define MiFatal     	101
#define MiError     	102
#define MiWarning		103

#define MBarCondition	200
#define MiRecord		201
#define MiTell			202

#define MBarHelp		300
#define MiHelp			301
#define MiGeneralHelp	302
#define MiHelpIndex		303

#define ScAbout     	400
							
#define AppFrame		100
#define AppError        101
#define MainHelpTable 	20
#define AppFrameHelp	1000
#define HMiFatal		1001
#define HMiError		1002
#define HMiWarning		1003

#define CondHelpBase	2000

#define WM_COMMAND 0x0020

/* Record Condtion Dialog */

#define D_ADDCONDITION	300
#define T_TEXT			101
#define E_CONDITION		102
#define R_ERROR			103
#define R_WARNING		104
#define R_THREAD1		105
#define R_THREAD2		106
#define R_THREAD3		107
#define E_ARG			108
#define B_OK			1
#define B_CANCEL		2
#define B_HELP			3
