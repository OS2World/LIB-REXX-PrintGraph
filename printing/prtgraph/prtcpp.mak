# ============================================================================
#
#       prtcpp.mak
#
#       Make file for PRTGRAPH
#
#       Version of 1995-05-08
#
#       by Peter Kanis  (c) ADD Consulting
#
# ============================================================================

# ============================================================================
#       Standard Make file header.
# ============================================================================

SRCDRV      =   W:
SRCDIR      =   $(SRCDRV)\prtgraph
VERSION     =   2.2

!INCLUDE $(ADDMAKDIR)\standard.mak

ICONLIST    =

!IF "$(DEFINE)" == "-DTST_NGEN"
LIBS = tstngen
!ELSE
LIBS = ""
!ENDIF

MFLAGS  = -DCPP_MOD -DUSE_HOOK
MLIST   = prtgrcpp.lib \
          prtgrcpp.hpp \
          prtgrcpp.dll
CPRTGR = $(CPPDLL)

#           $(ADDBOOK)prtgrcpp.inf

# ============================================================================
#       build module
# ============================================================================

ALL:    path \
        pgraph \
        $(MLIST)
        @echo [[ PrtGraph Compiled and Linked ]]

# ============================================================================
#   change directory & copy language dependent files
# ============================================================================

!INCLUDE $(ADDMAKDIR)\director.mak

pgraph :
    -touch prtgraph.c
    -touch initterm.c
    
# ============================================================================
#   Maintain Lib files
# ============================================================================

prtgrcpp.lib    :  prtgrcpp.dll
        $(IMPLIB) prtgrcpp.lib prtgrcpp.dll

# ============================================================================
#   Make C++ DLL
# ============================================================================

prtgrcpp.dll    :  $(OBJDIR)initterm.obj $(OBJDIR)prtgraph.obj $(OBJDIR)prtgrcpp.obj \
                   $(OBJDIR)prtgrafc.obj prtgrcpp.def prtgrcpp.lnk \
                   prtgraph.res 
        $(LK32) @prtgrcpp.lnk
        rc prtgraph.res $@

prtgrcpp.lnk    :   prtgrcpp.def prtcpp.mak
        echo $(OBJDIR)prtgraph.obj + >  prtgrcpp.lnk
        echo $(OBJDIR)prtgrafc.obj + >>  prtgrcpp.lnk
        echo $(OBJDIR)initterm.obj + >>  prtgrcpp.lnk
        echo $(OBJDIR)prtgrcpp.obj >>  prtgrcpp.lnk
        echo $(ADDDLL)prtgrcpp.dll >>  prtgrcpp.lnk
        echo NUL >>  prtgrcpp.lnk
        echo $(LIBS) >>  prtgrcpp.lnk
        echo prtgrcpp.def; >>  prtgrcpp.lnk

$(OBJDIR)prtgrcpp.obj  :   prtgrcpp.cpp prt_int.h prtgraph.h prtgrcpp.hpp
        $(CPPDLL) $(MFLAGS) prtgrcpp.cpp

$(ADDINC)prtgrcpp.hpp : prtgrcpp.hpp
     -copy  $? $@
     -touch $@

# ============================================================================
#   Make C++ Help
# ============================================================================

$(ADDBOOK)prtgrcpp.inf : prtgrcpp.inf
        -copy  $? $@

prtgrcpp.inf : prtgrcpp.ipf
        ipfc $? /INF

# ============================================================================
#   Make C Test Program
# ============================================================================

prtdemo.exe    :   $(OBJDIR)prtdemo.obj prtdemo.def prtdemo.lnk \
                   prtdemo.res
        $(LK32) @prtdemo.lnk
        rc prtdemo.res $@

prtdemo.lnk    :   prtdemo.def prt.mak
        echo $(OBJDIR)prtdemo.obj >   prtdemo.lnk
        echo prtdemo.exe >>  prtdemo.lnk
        echo NUL                    >>  prtdemo.lnk
        echo prtgrafc               >>  prtdemo.lnk
        echo prtdemo.def;    >>  prtdemo.lnk

$(OBJDIR)prtdemo.obj  :   prtdemo.c prtdemo.h $(ADDINC)prtgrafc.h 
        $(CC32) $(@B).c

prtdemo.res    :   prtdemo.rc dialog.dlg dialog.h
        rc $(INCLPATH) -r prtdemo.rc $@ 

$(ADDEXE)prtdemo.exe  :   prtdemo.exe
     -copy  $? $@
     -touch $@

# ============================================================================
#   Make resources
# ============================================================================

prtgraph.res    :   prtgraph.rc prt_dlg.dlg prt_dlg.h
        rc $(INCLPATH) -r prtgraph.rc $@ 

# ============================================================================
#   Make Genearal functions objects
# ============================================================================

$(OBJDIR)prtgraph.obj  :   prtgraph.c
    $(CPRTGR) $(MFLAGS) $(@B).c

$(OBJDIR)initterm.obj  :   initterm.c 
    $(DL32) $(MFLAGS) $(@B).c

# ============================================================================
#
#                     (c) ADD Consulting 1994
#
#                            END OF FILE.
#
# ============================================================================
