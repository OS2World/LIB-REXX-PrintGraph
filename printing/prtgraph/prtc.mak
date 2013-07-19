# ============================================================================
#
#       prtc.mak
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

MFLAGS  = -DC_MOD -DUSE_HOOK
MLIST   = prtgrafc.lib \
          prtgrafc.h \
          prtgrafc.dll \
          prtgrafc.inf \
          prtdemo.exe
CPRTGR = $(DL32)

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

prtgrafc.lib    :  prtgrafc.def
        $(IMPLIB) prtgrafc.lib prtgrafc.def

# ============================================================================
#   Make C DLL
# ============================================================================

prtgrafc.dll    :  $(OBJDIR)prtgraph.obj $(OBJDIR)prtgrafc.obj $(OBJDIR)initterm.obj \
                   prtgrafc.def prtgrafc.lnk prtgraph.res
        $(L32) @prtgrafc.lnk
        rc prtgraph.res $@

prtgrafc.lnk    :   prtgrafc.def prtc.mak
        echo $(OBJDIR)prtgraph.obj + >   prtgrafc.lnk
        echo $(OBJDIR)initterm.obj + >>  prtgrafc.lnk
        echo $(OBJDIR)prtgrafc.obj >>  prtgrafc.lnk
        echo $(ADDDLL)prtgrafc.dll >>  prtgrafc.lnk
        echo NUL >>  prtgrafc.lnk
        echo $(LIBS) >>  prtgrafc.lnk
        echo prtgrafc.def; >>  prtgrafc.lnk

$(OBJDIR)prtgrafc.obj  :   prtgrafc.c prt_int.h prtgrafc.h
        $(DL32) $(MFLAGS) $(@B).c

$(ADDINC)prtgrafc.h : prtgrafc.h
     -copy  $? $@
     -touch $@

# ============================================================================
#   Make C Help
# ============================================================================

$(ADDBOOK)prtgrafc.inf : prtgrafc.inf
     -copy  $? $@

prtgrafc.inf : prtgrafc.ipf
   ipfc $? /INF

# ============================================================================
#   Make C Test Program
# ============================================================================

prtdemo.exe    :   $(OBJDIR)prtdemo.obj prtdemo.def prtdemo.lnk \
                   prtdemo.res
        $(L32E) @prtdemo.lnk
        rc prtdemo.res $@

prtdemo.lnk    :   prtdemo.def prtc.mak
        echo $(OBJDIR)prtdemo.obj >   prtdemo.lnk
        echo prtdemo.exe >>  prtdemo.lnk
        echo NUL >>  prtdemo.lnk
        echo prtgrafc >>  prtdemo.lnk
        echo prtdemo.def; >>  prtdemo.lnk

$(OBJDIR)prtdemo.obj  :   prtdemo.c prtdemo.h prtgrafc.h 
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
    $(CPRTGR) $(MFLAGS) $(@B).c


# ============================================================================
#
#                     (c) ADD Consulting 1994
#
#                            END OF FILE.
#
# ============================================================================
