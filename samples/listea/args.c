/*  VCS_ID
 *  $Filename:   args.c
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


// PARSE COMMAND LINE OPTION FLAGS

#include <ctype.h>
#include <string.h>

/***************************************************************************
	DESCRIPTION:
		PARSES THE COMMAND LINE OPTION FLAGS (IE -snq)

	EXPECTS:
		ARGC	# OF TOTAL COMMAND LINE ARGS
		ARGV	ARRAY OF CHAR PTRS TO COMMAND LINE PARAMS
		POS		ARGSUMENT IN ARGV TO START WITH
		FS		STRING OF VALID OPTION FLAG STARTERS (IE -/);
		UPPER	COMPARE UPPERCASE COMMAND LINE FLAGS TO LETTERS[]
		NUMOPT	NUMBER OF OPTIONS FLAGS IN LETTERS[] AND FLAGS[]
		LETTERS	THE VALID OPTION LETTERS
		FLAGS	THE CORRESPONDING FLAG FOR EACH OPTION LETTER

	RETURNS:	
		A LONG WITH THE BITS SET BASED ON THE COMMAND LINE OPTIONS
		PASSED TO IT

	SAMPLE CALL:
		main(int artgc, char **argv)
		{
			#define SKIPHEADER	1
			#define QUIETMODE	2
			#define HELP		4

			long	options
			char	opts[]={'S','Q','H'};
			long	flgs[]={SKIPHEADER,QUIETMODE,HELP};
			int		pos=1;
		
			options=SetOptionFlags(argc,argv,&pos,"-/",1,3,opts,flgs);
			// pos now points to first non-option flag command line argument
			if (options & HELP)
				printf("Help Message\n");
		}
****************************************************************************/

long SetOptionFlags(int argc, char **argv, int *pos, char *fs, int upper,
  					 int numopt, char letters[], long flags[])
{
	int lp,lp1,lp2;
	long	options=0;

	for(lp=*pos ; lp<argc && strchr(fs,argv[lp][0]) ; lp++)
		for(lp1=1 ; argv[lp][lp1] ; lp1++)
			for(lp2=0 ; lp2<numopt ; lp2++)
				if ((upper && toupper(argv[lp][lp1])==letters[lp2])
					|| argv[lp][lp1]==letters[lp2])
				{
					options |= flags[lp2];
					break;
				}
	*pos=lp;
	return options;
}
