#   VCS_ID
#  $Filename:   makefile.ibm
#  $Author  :   John Pompeii
#  $Revision:   1.1  $
#  $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
#
 
# mdiedit makefile for IBM C++ 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Tdp -D_MT=1
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Tdp -D_MT=1
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

.rc.res:
    rc -r $*.rc

all: mdiedit.exe

mdiedit.exe: mdiedit.obj mdiedit.res mdiedit.def
    icc mdiedit.obj opmvai.lib mdiedit.def
    rc mdiedit.res

mdiedit.obj: mdiedit.cpp

mdiedit.res: mdiedit.rc mdidlg.dlg mdidlg.h

