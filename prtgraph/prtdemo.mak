# *********************************************************************
#
# $Author:   KANIS  $
# $Workfile:   prtdemo.mak  $
# $Revision:   1.0  $
# $Date:   16 Jun 1996 12:49:34  $
#
# $Log:   M:\prtgraph\prtdemo.mav  $
# 
#    Rev 1.0   16 Jun 1996 12:49:34   KANIS
# Initial revision.
# 
# *********************************************************************

all: prtdemo.exe

prtdemo.exe : prtdemo.obj prtdemo.res
    ilink /NOFREE /NOI /NOL /ALIGN:4 /EXEPACK /BASE:0x10000 @prtdemo.lnk
    rc prtdemo.res $@

prtdemo.obj: prtdemo.c prtdemo.h
    icc -DNDEBUG -C -Ge -G5 -Gm+ -W3 -Gp+ -O -Re -Se -Ss -Q -N40 prtdemo.c

prtdemo.res: prtdemo.rc dialog.h dialog.dlg prtdemo.h
    rc -r prtdemo.rc $@

# ***********************************************************************
#
#   (c)1996 ADD Consulting
#
#   END OF FILE.
#
# ***********************************************************************
