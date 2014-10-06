/*  VCS_ID
 *  $Filename:   errhandl.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   28 Dec 1991 14:20:32  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
class AppErrorHandler : public bConditionHandler
{
	private:
		bString	appName;

	public:
		AppErrorHandler(char *appName, long condType, char *logfileName);
   	   ~AppErrorHandler();

		short ProcConditions(bCondition *c);
};


// Application facility errors

#define FAC_ERRDEMO  		20				// facility ID
#define FAC_APPMSGFILE 		"errdemo.msg"	// message file name
#define FAC_APPHELPFILE		"errdemo.hlp"	// help file library
#define FAC_APPHELPOFFSET	2000			// offset = help_panel_id - error_code

#define UE_CORRUPT	 		1				// error codes...
#define UE_INITIO			2
#define UW_GUESSWHAT		6

// "IO" Facility

#define FAC_IO				21
#define FAC_IOMSGFILE		"iolib.msg"
#define FAC_IOHELPFILE		"iolib.hlp"
#define FAC_IOHELPOFFSET	10000

#define UE_FILENOTFOUND		101
#define UE_METHODNOTIMP		102
