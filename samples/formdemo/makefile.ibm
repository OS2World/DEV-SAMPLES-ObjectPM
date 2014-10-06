#   VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#
 
# formdemo makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

.ipf.hlp:
    ipfc $*.ipf

all: formdemo.exe formdemo.hlp

formdemo.exe: formdemo.obj formdemo.res formdemo.def
    icc formdemo.obj opmvai.lib formdemo.def
    rc formdemo.res

formdemo.obj: formdemo.cpp

formdemo.res: formdemo.rc 

formdemo.hlp: formdemo.ipf

