#   VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
# 

# Hello makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: errdemo.exe errdemo.msg errdemo.hlp

errdemo.exe: errdemo.obj errhandl.obj errdemo.res errdemo.def
    icc errdemo.obj errhandl.obj opmvai.lib errdemo.def
    rc errdemo.res

errdemo.res: errdemo.rc about.dlg about.h errdemo.h

errdemo.msg: errdemo.txt

errdemo.hlp: errdemo.ipf

