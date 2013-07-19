# *********************************************************************
#
# $Author$
# $Workfile$
# $Revision$
# $Date$
#
# $Log$
# 
# *********************************************************************


!include $(ADDMAKE)\default.mak

zipall = vrprint.dll resource.dll vrprint.inf demo\vrprint.vrp \
           demo\vrprint.rc demo\vrprint.res demo\vrprint.exe \
           demo\window1.vrx demo\window1.vry demo\addlogo.bmp \
           demo\setup.exe demo\license.txt demo\warranty.txt \
           demo\prtman.ico demo\read.me demo\testorig.jpg \
           printer.mto vrprint.vxo macros\*.* reg.exe

zipproj = resource.dll demo\vrprint.vrp \
          demo\vrprint.rc demo\vrprint.res demo\vrprint.exe \
          demo\window1.vrx demo\window1.vry demo\addlogo.bmp \
          demo\testorig.jpg demo\readme.prj

zipmacro = macros\*.* demo\readme.mac

zipinf = vrprint.inf demo\readme.txt

zipupd = vrprint.dll reg.exe

objs =  initterm.obj printer.obj props.obj prtgraph.obj sominit.obj

!include T:\VXODK\bin\makecset.inc

dll: somobj vrprint.dll vrprint.inf resource.dll
    reg vrprint.dll F86F-AF19-8124-8F2B
    @echo [[ Built Local VRPrinter...]]

clean :
    cd som\sc
    -@del printer.*
    cd ..\..
    -@del $(objs)
    -@del vrprint.inf vrprint.lnk resource.lnk
    -@del vrprint.zip vrpmacro.zip vrpproj.zip vrpinf.zip vrpdll.zip
    -@del vrprint.dll vrprint.inf resource.dll
    @echo [[ Cleaned up for build... ]]

somobj :
    cd som
    make
    cd ..

all: somobj vrprint.dll vrprint.inf resource.dll
    zip -9j vrprint.zip $(zipall)
    zip -9j vrpmacro.zip $(zipmacro)
    zip -9j vrpproj.zip $(zipproj)
    zip -9j vrpinf.zip $(zipinf)
    zip -9j vrpdll.zip $(zipupd)
    -copy *.zip l:\public
    @echo [[ Done Full Build.]]

vrprint.lnk : vrprint.mak
    @echo Generating $@...
    @echo INITTERM.obj + > $@
    @echo PRINTER.obj + >> $@
    @echo props.obj + >> $@
    @echo prtgraph.obj + >> $@
    @echo SOMINIT.obj >> $@
    @echo VRPRINT.DLL >> $@
    @echo NUL >> $@
    @echo cppom30 os2386 rexx som vxrexxc >> $@
    @echo VRPRINT.DEF; >> $@

vrprint.dll : $(objs) vrprint.res vrprint.lnk vrprint.def
    @echo Linking $@...
    ilink $(LFLAGS) /NOD @vrprint.lnk
    @echo binding resources for $@
    rc $(@B).res $@

resource.lnk : vrprint.mak
    @echo Generating $@...
    @echo resource.obj > $@
    @echo resource.dll >> $@
    @echo NUL,, >> $@
    @echo resource.def; >> $@

resource.dll : resource.obj resource.res resource.def resource.lnk
    @echo Linking $@...
    $(L32)
    @echo binding resources for $@...
    rc $(@B).res $@

resource.obj : resource.c
    @echo Compiling $@...
    icc -C $?

printer.obj : printer.ih printer.ph printer.h prt_int.h prt_dlg.h

printer.ih : som\sc\printer.ih
    @copy $? $@

printer.ph : som\sc\printer.ph
    @copy $? $@

printer.h : som\sc\printer.h
    @copy $? $@

props.obj : printer.prp prt_int.h prt_dlg.h

sominit : prt_int.h prt_dlg.h

initterm.obj : prt_int.h prt_dlg.h

prtgraph.obj : prt_int.h prt_dlg.h

printer.prp : som\sc\printer.prp
    @copy $? $@

vrprint.res : vrprint.rc printer.ico vrprint.ico

vrprint.inf : vrprint.ipf
    ipfc vrprint.ipf /inf

# ***********************************************************************
#
#   (c)1996 ADD Consulting
#
#   END OF FILE.
#
# ***********************************************************************
