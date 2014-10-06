#   VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#

# pcalc makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: pcalc.exe

pcalc.exe: pcalc.obj pcalc.res pcalc.def
    icc pcalc.obj opmvai.lib pcalc.def
    rc pcalc.res

pcalc.obj: pcalc.cpp

pcalc.res: pcalc.rc pcalcdlg.dlg pcalcdlg.h

