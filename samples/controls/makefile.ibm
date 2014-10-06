#    VCS_ID
#    $Filename:   makefile.ibm
#    $Author  :   John Pompeii
#    $Revision:   1.1  $
#    $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#

# controls makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Q+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Q+ /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: controls.exe

controls.obj: controls.cpp controls.h

controls.exe: controls.obj controls.res controls.def
    icc controls.obj opmvai.lib controls.def
    rc controls.res

controls.res: controls.rc about.dlg about.h controls.h

