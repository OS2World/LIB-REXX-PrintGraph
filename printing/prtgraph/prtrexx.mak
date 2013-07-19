!INCLUDE $(ADDMAKE)\default.mak

all   :   pgraph \
          prtgraph.dll \
          prtgraph.inf \
          prtrxdae.exe \
          prtgraph.zip

pgraph :
    -touch prtgraph.c
    -touch initterm.c
    
# ============================================================================
#   Make REXX dll
# ============================================================================

prtgraph.dll    :  prtgraph.obj prtgrexx.obj varpool.obj initterm.obj prtgraph.def

varpool.obj  :   varpool.c varpool.h

prtgrexx.obj  :   prtgrexx.c prtgrexx.h prt_int.h prtrxdae.h varpool.h

prtgraph.obj  :   prtgraph.c prtgrexx.h prt_int.h

initterm.obj  :   initterm.c prtgrexx.h prt_int.h 

# ============================================================================
#   Make REXX Help
# ============================================================================

prtgraph.inf : prtgraph.ipf

# ============================================================================
#   Make REXX Daemon
# ============================================================================

prtrxdae.exe : prtrxdae.res prtrxdae.obj prtrxdae.def

prtrxdae.obj : prtrxdae.cc prtgrexx.h prt_int.h prtrxdae.h

# ============================================================================
#   Make resources
# ============================================================================

prtrxdae.res : prtrxdae.rc

# ============================================================================
#   Make zip file
# ============================================================================

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

