#  VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#
 
# Hello makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS= /Gd+ /Ge+ /Gm+ /Wpro /O- /Tdp /Ti+
!ELSE
CPPFLAGS= /Gd+ /Ge+ /Gm+ /Wpro /O+ /Tdp
!ENDIF

.cpp.obj:
    icc /C+ $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: hello.exe

hello.exe: hello.obj hello.res hello.def
    icc hello.obj opmvai.lib hello.def
    rc hello.res

hello.obj: hello.cpp

hello.res: hello.rc hello.h

