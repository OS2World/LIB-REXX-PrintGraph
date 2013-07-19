# *********************************************************************
#
# $Author:   KANIS  $
# $Workfile:   rexxexe.mak  $
# $Revision:   1.0  $
# $Date:   28 Sep 1996 13:06:42  $
#
# $Log:   M:\prtgraph\rexxexe.mav  $
# 
#    Rev 1.0   28 Sep 1996 13:06:42   KANIS
# Initial revision
# 
# *********************************************************************

EXE = 1
!include $(ADDMAKE)\default.mak

all:      prtrxdae.exe reg.exe \
          prtgraph.zip

# ***********************************************************************
# Make REXX Daemon
# ***********************************************************************

prtrxdae.lnk : rexxexe.mak
    @echo prtrxdae.obj > $@
    @echo prtrxdae.exe >> $@
    @echo NUL,, >> $@
    @echo prtrxdae.def; >> $@

reg.lnk : rexxexe.mak
    @echo reg.obj > $@
    @echo reg.exe >> $@
    @echo NUL,, >> $@
    @echo reg.def; >> $@

prtrxdae.exe : prtrxdae.res prtrxdae.obj prtrxdae.def prtrxdae.lnk
    @echo linking $@
    $(L32)
    @echo binding resources to $@
    rc $(@B).res $@

reg.exe : reg.obj reg.def reg.lnk
    @echo linking $@
    $(L32)

prtrxdae.obj : prtgrexx.h prt_int.h prtrxdae.h

# ***********************************************************************
# Make resources
# ***********************************************************************

prtrxdae.res : prtrxdae.rc

# ***********************************************************************
# Make zip file
# ***********************************************************************

prtgraph.zip: prtgraph.dll prtgraph.inf prtrxdae.exe read.me thanks.txt warranty.txt license.txt
    zip -9 $@ $**
    -del read.me
    -del license.txt
    -del thanks.txt

read.me : readme.rex
    -copy $? $@

license.txt: license.rex
    -copy $? $@

thanks.txt: thanks.rex
    -copy $? $@

# ***********************************************************************
#
#   (c)1996 ADD Consulting
#
#   END OF FILE.
#
# ***********************************************************************
