#    VCS_ID
#    $Filename:   makefile.ibm
#    $Author  :   John Pompeii
#    $Revision:   1.1  $
#    $Date:   28 Dec 1991 14:20:38  $
# 
# 	Copyright (c)	1995 by Secant Technologies
 
 
 
# Collection makefile for IBM C++ 
# usage: make all, cmapdemo.exe, mapdemo.exe, or listdemo.exe

.SUFFIXES: .cpp 

!IF "$(DEBUG)" == "ON"
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /Wpro /O- /Ti+ /Q+ /Tdp -D_MT=1
LFLAGS= /NOD /CO /M /NOI /NOLOGO
!ELSE
CPPFLAGS=/C+ /Gd+ /Ge+ /Gm+ /O+ /Wpro /Q+ /Tdp -D_MT=1
LFLAGS= /NOD /M /NOI /NOLOGO
!ENDIF

.cpp.obj:
    icc $(CPPFLAGS) $*.cpp

all: cmapdemo.exe mapdemo.exe listdemo.exe

cmapdemo.exe: cmapdemo.obj cmapdemo.def
    icc cmapdemo opmvai.lib cmapdemo.def

mapdemo.exe: mapdemo.obj mapdemo.def
    icc mapdemo opmvai.lib mapdemo.def

listdemo.exe: listdemo.obj listdemo.def
    icc listdemo opmvai.lib listdemo.def

