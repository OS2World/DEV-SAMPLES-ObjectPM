#   VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#
 
# SeeFont makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: seefont.exe

seefont.exe: seefont.obj seefont.res seefont.def
    icc seefont opmvai.lib seefont.def
    rc seefont.res

seefont.res: seefont.rc dialogs.dlg dialogs.h

