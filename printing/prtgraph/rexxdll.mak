# *********************************************************************
#
# $Author:   KANIS  $
# $Workfile:   rexxdll.mak  $
# $Revision:   1.0  $
# $Date:   28 Sep 1996 13:06:40  $
#
# $Log:   M:\prtgraph\rexxdll.mav  $
# 
#    Rev 1.0   28 Sep 1996 13:06:40   KANIS
# Initial revision
# 
# *********************************************************************

COMPARGS = -Gd-

!INCLUDE $(DEFMAK)

DEFINE = -DREXX_MOD

all   :   prtgrexx prtgraph.inf
    @echo [[REXX Dll is up to date]]

clean : 
    -@del prtgraph.obj prtgrexx.obj varpool.obj initterm.obj prtgraph.dll \
          prtgraph.inf prtgraph.lnk
    @echo [[REXX Dll is ready for build]]

prtgrexx : prtgraph.res prtgraph.dll
# ***********************************************************************
# Make REXX dll
# ***********************************************************************

prtgraph.lnk : rexxdll.mak
    @echo prtgraph.obj+ > $@
    @echo prtgrexx.obj+ >> $@
    @echo varpool.obj+ >> $@
    @echo initterm.obj >> $@
    @echo prtgraph.dll >> $@
    @echo NUL >> $@
    @echo rexx >> $@
    @echo prtgraph.def; >> $@

OBJS = $(ODIR)\prtgraph.obj $(ODIR)\prtgrexx.obj $(ODIR)\varpool.obj $(ODIR)\initterm.obj 

prtgraph.dll    :  $(OBJS) rexx.lib prtgraph.def
    @echo linking $@
    $(L32)
    @echo Binding resources to $@...
    rc $(@B).res $@

rexx.lib :

$(OBJS)  :   varpool.h prtgrexx.h prt_int.h prtrxdae.h varpool.h prt_dlg.h

# ***********************************************************************
# Make REXX Help
# ***********************************************************************

prtgraph.inf : prtgraph.ipf
    @echo Building Help $@
    ipfc $? /INF

# ***********************************************************************
#
#   (c)1996 ADD Consulting
#
#   END OF FILE.
#
# ***********************************************************************
