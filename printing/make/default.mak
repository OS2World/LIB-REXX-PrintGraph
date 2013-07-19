# *********************************************************************
#
#   by Peter Kanis ADDC Infotech GmbH
#
#   This file should be included at the top of any GNU make makefile
#      include $(DEFMAK)
#
#   Required Environment variables:
#      DEFMAK      : Path to this file.
#      AMAK        : Path to the all.mak file.
#      PROOT       : Path to project directories
#
#   Imported DEFINES:
#      MSVC=1      : Build for Microsoft Visual C++ v5 on Windows
#      EXE=1       : Build *.exe file under Windows or OS/2 **
#      DEBUGME=1   : Build debug version
#      OPTIMIZE=1  : Build optimized version (overridden by DEBUGME)
#
#   Imported MACROS:
#      DEFINE   : Extra defines to pass to the compiler -D<name>
#      COMPARGS : Extra compiler flags to pass
#      ORBFLAGS : Extra flags for idl compiler
#
#   Exported MACROS:
#      MLIBS    : master lib file directory
#      MDLLS    : master shared library directory
#      MBIN     : master executable directory
#      MINCL    : master include directory (should be in the INCLUDE path)
#      MHELP    : master help files
#      ODIR     : output directory relative to source
#      OSDIR    : Root to master files for the platform
#      COPY     : copy out of date dependency to target
#      ILIB     : create archive library (1st step)
#      MLIB     : create archive library (2nd step)
#      SLIB     : link a shared library
#      L32      : Create an executable (subsystem:console)
#      L32PM    : Create an executable (subsystem:windows)
#      O        : Object file extension for the platform
#
#   ** Under OS/2 or Windows native compilers, you need to write
#      different makefiles to build exe and dll files: DO NOT MIX them.
#
#  The following targets are defined:
#      all     : Build all targets
#      targets : Print out the targets for all
#      clean   : Delete local targets in $(ODIR)
#      mclean  : clean local and master targets
#      new     : clean local targets and rebuild
#
#  Local Makefile must define:
#      ALL     : The list of targets
#      MODULE  : The name of the module
#
# $Author$
# $Workfile$
# $Revision$
# $Date$
#
# $Log$
#
# *********************************************************************

# ***********************************************************************
# determine the platform we are running on
# ***********************************************************************

WHAT_OS = $(shell uname)

MD = -@mkdir
CHM = -@chmod a+X+w
MV = -@mv
COPY = cp $? $@
ERASE = -@rm
TOUCH =
RNAME =
CPBIN = cp $@ $(MBIN)
CPDLL = cp $@ $(MDLLS)

CLPACK = $(PKGDIR)/classes.jar
JAR = jar -cv0f $(CLPACK) $(PKGROOT)

# ***********************************************************************
# Operating System dependent definitions
# ***********************************************************************

ifeq ($(WHAT_OS), AIX)

# ***********************************************************************
# This is AIX, determine the revision (1 or 2)
# ***********************************************************************

HOST_OS = -DOSUNIX
ODIR = aix
OSDIR = $(ODIR)
O = o
FCPP = -+
CXX = xlC_r
NOUT =  > /dev/null 2>&1

CXXLIBS = -lpthreads -lC_r -lc_r

# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = idl
ifdef ORBIX201
IDLFLAGS = -B -s s.cc -c c.cc $(ORBFLAGS)
else
IDLFLAGS = -B -s s.cc -c c.cc $(ORBFLAGS) -out $(ODIR)
endif
IDLC = $(IDL) $(IDLFLAGS)

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = /projects/$(OSDIR)/lib
MDLLS   = /projects/$(OSDIR)/slib
MBIN    = /projects/$(OSDIR)/bin
M2BIN   = /projects/$(OSDIR)/bin
MINCL   = /projects/$(OSDIR)/include
MHELP   = /projects/$(OSDIR)/help
VCINC   = $(MINCL)

# *********************************************************************
# Paths
# *********************************************************************

ORALIBS = -L$(ORACLE_HOME)/lib -L$(ORACLE_HOME)/rdbms/lib
ORAINC  = $(ORACLE_HOME)/rdbms/demo

# *********************************************************************
# Link libraries for Oracle OCI
# *********************************************************************

NETLIBS = -lsqlnet -lncr -lsqlnet
LLIBORA = -lclient -lcommon -lgeneric
LLIBEPC = -lepc
CORELIBS = -lnlsrtl3 -lc3v6 -lcore3 -lnlsrtl3 -lcore3 -lnlsrtl3
OCILIBS = -bdynamic -lclient $(NETLIBS) $(LLIBORA) $(LLIBEPC) $(CORELIBS)

NDFOPT = $(ORACLE_HOME)/rdbms/lib/kpundf.o

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

ifdef ORBIX201
LORB = -L/usr/lpp/Orbix201/corba2/lib
IORB = -I/usr/lpp/Orbix201/corba2/include
else
LORB = -L/usr/lpp/Orbix23c/lib
IORB = -I/usr/lpp/Orbix23c/inc
endif

INC = -I../incl -I$(MINCL) $(IORB) -I$(ORAINC) -I/usr/dt/include \
-I/usr/include/X11 -I../../incl -I$(ODIR)

LIBP= $(LORB) $(ORALIBS) -L$(MDLLS) -L$(MLIBS) -L/usr/dt/lib

# ***********************************************************************
# Set up compiler and linker switches for either Debug or No debug and
# EXE or DLL.
# ***********************************************************************

BCPPF = $(DEFINE) $(HOST_OS) -qinfo=nopro -qflag=w:w

ifdef DEBUGME                               # Debug version

CXXFLAGS = -c $(BCPPF) -g $(COMPARGS) $(INC) -o $@

else                                        # Production version

ifdef OPTIMIZE                              # Optimize it

CXXFLAGS = -c $(BCPPF) -O $(COMPARGS) $(INC) -o $@

else                                        # Don't optimize

CXXFLAGS = -c $(BCPPF) $(COMPARGS) $(INC) -o $@

endif                                       # Optimize
endif                                       # Debug/Production

COPTF = -c $(BCPPF) -O $(COMPARGS) $(INC) -o $@

LDFLAGS = $(BCPPF) $(LIBP) -bdynamic -brtl -o $@

# ***********************************************************************
# Macro for linking
# ***********************************************************************

L32 = $(CXX) $(LDFLAGS) $+
L32PM = $(L32)

SLIB = /usr/lpp/xlC/bin/makeC++SharedLib -brtl $(LIBP) -o $@ $+

define ILIB
@echo Building static library $@...
$(AR) -rv $@ $+
ranlib -t $@
endef

CFLAGS = $(CXXFLAGS)

endif

# ***********************************************************************
#                           End of AIX
# ***********************************************************************

ifeq ($(WHAT_OS), OSF1)

# ***********************************************************************
# We are running on Digital Unix
# ***********************************************************************

HOST_OS = -DOSUNIX
ODIR = dec
OSDIR = $(ODIR)
O = o
FCPP =
CXX = /usr/bin/cxx
NOUT =  > /dev/null 2>&1

# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = idl
IDLFLAGS = -B -s s.cc -c c.cc $(ORBFLAGS) -out $(ODIR)
IDLC = $(IDL) $(IDLFLAGS)

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = $(PROOT)$(OSDIR)/lib
MDLLS   = $(PROOT)$(OSDIR)/slib
MBIN    = $(PROOT)$(OSDIR)/bin
M2BIN   = $(MBIN)
MHELP   = $(PROOT)$(OSDIR)/help
MINCL   = $(PROOT)$(OSDIR)/include

VCINC   = $(MINCL)

# *********************************************************************
# Link libraries for Oracle OCI
# *********************************************************************

NETLIBS = -lsqlnet -lncr -lsqlnet
LLIBORA = -lclient -lcommon -lgeneric
LLIBEPC = -lepc
CORELIBS = -lnlsrtl3 -lc3v6 -lcore3 -lnlsrtl3 -lcore3 -lnlsrtl3
OCILIBS = -lclient $(NETLIBS) $(LLIBORA) $(LLIBEPC) $(CORELIBS)

NDFOPT = $(ORACLE_HOME)/rdbms/lib/kpundf.o

SYSLIBS = -lrt

CXXLIBS = -lpthreads -lcxx -lcxxstd -lexc -lc_r

# *********************************************************************
# Paths
# *********************************************************************

ORACLE_HOME = /vol_1/oracle/7.3.2

ORALIBS = -L$(ORACLE_HOME)/lib -L$(ORACLE_HOME)/rdbms/lib
ORAINC  = $(ORACLE_HOME)/rdbms/demo

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC   = -I../incl -I$(MINCL) -I/opt/iona/OrbixMT_2.3c/inc -I$(ORAINC) \
-I/usr/dt/include -I/usr/include/X11 -I../../incl -I$(ODIR)

LIBP  = -L/opt/iona/OrbixMT_2.3c/lib $(ORALIBS) -L$(MLIBS) -L$(MDLLS) \
-L/usr/dt/lib

# ***********************************************************************
# Set up compiler and linker switches
# ***********************************************************************

BCPPF = $(DEFINE) $(HOST_OS) -D_REENTRANT -DEXCEPTIONS -threads -pthread

ifdef DEBUGME                               # Debug version

CXXFLAGS = -oldcxx -c -DNDEBUG $(BCPPF) -g2 -O0 $(COMPARGS) $(INC) -o $@

else                                        # Production version

ifdef OPTIMIZE                              # Optimize code

CXXFLAGS = -oldcxx -c -DNDEBUG $(BCPPF) -O -g0 $(COMPARGS) $(INC) -o $@

else                                        # Don't optimize

CXXFLAGS = -oldcxx -c -DNDEBUG $(BCPPF) $(COMPARGS) $(INC) -o $@

endif                                       # Optimize
endif                                       # Debugme/Production

COPTF = -oldcxx -c -DNDEBUG $(BCPPF) -O -g0 $(COMPARGS) $(INC) -o $@

LDFLAGS = -oldcxx -D_REENTRANT -DEXCEPTIONS -threads $(LIBP) -o

# ***********************************************************************
# Macros for linking
# ***********************************************************************

SLIB = ld -shared -error_unresolved -oldstyle_liblookup -msym -g $(LIBP) -o $@ $+

L32 = $(CXX) $(LDFLAGS) $@ $+
L32PM = $(L32)

define ILIB
$(AR) -rc $(ODIR)/$(@F) $+
ranlib $(ODIR)/$(@F)
endef

NOUT =  > /dev/null 2>&1

CFLAGS = $(CXXFLAGS)

endif
# ***********************************************************************
#                           End of OSF1
# ***********************************************************************

ifeq ($(WHAT_OS), CYGWIN32_NT)

# ***********************************************************************
# We are running on Windoze NT
# ***********************************************************************

HOST_OS = -DOSWIN
O = obj
NOUT = >nul 2>&1
OSDIR = winnt

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = $(PROOT)$(OSDIR)/lib
MLIBSD  = $(PROOTD)$(OSDIR)/lib
MDLLS   = $(PROOT)$(OSDIR)/slib
MBIN    = $(PROOT)$(OSDIR)/bin
M2BIN   = $(MBIN)
MINCL   = $(PROOT)$(OSDIR)/include
MINCLD  = $(PROOTD)$(OSDIR)/include
MHELP   = $(PROOT)$(OSDIR)/help
ORALIBS = $(ORACLE_HOME)/LIB/MSVC/
ORAINC = -I$(ORACLE_HOME)/INCLUDE

ifdef MSVC                                  # Compiling for MS Visual C++

CXX = cl
ODIR = winNT
FCPP = /TP
VCINC = $(PROOT)$(OSDIR)/vcinc
VCINCD = $(PROOTD)$(OSDIR)/vcinc
ORBINC = -Ic:/iona/Orbix_2.3c/inc
ORBLIBS = c:/iona/Orbix_2.3c/lib/


# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = idl
IDLFLAGS = -B -s s.cc -c c.cc $(ORBFLAGS) -out $(ODIR)
IDLC = $(IDL) $(IDLFLAGS)

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC = -I../incl -I$(VCPBASE)include -I$(MINCLD) -I$(VCINCD) $(ORAINC) \
$(JNIINC) $(ORAINC) $(ORBINC) -I$(ODIR)

LIBP = /libpath:$(VCPBASE)lib/ /libpath:$(MLIBSD)/ /libpath:$(ORALIBS) \
/libpath:$(ORBLIBS)

else                                        # Compiling for VisualAge C++

CXX = icc
ODIR = ibmNT
FCPP = -Tdp
VCINC = $(MINCL)
VCINCD = $(MINCLD)
ORBINC = -Ic:/iona/Orbix22/corba2/INCLUDE
ORBLIBS = c:/iona/Orbix22/corba2/lib/
JNIINC = -IC:/jdk1.1.7/include -IC:/jdk1.1.7/include/win32

# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = c:/iona/Orbix22/bin/idl
IDLFLAGS = -B -s s.cc -c c.cc -f $(ORBFLAGS)
IDLC = $(IDL) $(IDLFLAGS)
ORBIX201=1

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC = -I../incl -I$(VABASE)/include -I$(VABASE)/sdk/winh \
-I$(VABASE)/sdk/winh/winnt -I$(VABASE)/sdk/winh/win95 -I$(MINCLD) \
$(JNIINC) $(ORAINC) $(ORBINC) -I$(ODIR)

LIBP = $(VABASE)/lib/ $(VABASE)/sdk/lib/ $(MLIBSD)/ $(ORALIBS) \
$(ORBLIBS)

RNAME = dllrname $@ CPPWOT3=ADDCPP0 CPPWOB3I=ADDCPP01 CPPWOU3I=ADDCPP02 \
CPPWM35I=ADDCPP03 CPPWOR3U=ADDCPPRU /Q

TOUCH = touch $(ODIR)/*

endif                                       # Different compilers

endif

# ***********************************************************************
#                       End of Windoze NT
# ***********************************************************************

ifeq ($(WHAT_OS), CYGWIN32_95)

# ***********************************************************************
# We are running on Windoze 95
# ***********************************************************************

HOST_OS = -DOSWIN
O = obj
NOUT = >nul 2>&1
OSDIR = win95

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = $(PROOT)$(OSDIR)/lib
MLIBSD  = $(PROOTD)$(OSDIR)/lib
MDLLS   = $(PROOT)$(OSDIR)/slib
MBIN    = $(PROOT)$(OSDIR)/bin
M2BIN   = $(MBIN)
MINCL   = $(PROOT)$(OSDIR)/include
MINCLD  = $(PROOTD)$(OSDIR)/include
MHELP   = $(PROOT)$(OSDIR)/help
ORALIBS = $(ORACLE_HOME)/LIB/MSVC/
ORAINC = -I$(ORACLE_HOME)/INCLUDE

ifdef MSVC                                  # Compiling for MS Visual C++

ODIR = win95
CXX = cl
FCPP = /TP
VCINC = $(PROOT)$(OSDIR)/vcinc
VCINCD = $(PROOTD)$(OSDIR)/vcinc
ORBINC = -Ic:/iona/Orbix_2.3c/inc
ORBLIBS = c:/iona/Orbix_2.3c/lib/

# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = idl
IDLFLAGS = -B -s s.cc -c c.cc $(ORBFLAGS) -out $(ODIR)
IDLC = $(IDL) $(IDLFLAGS)

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC = -I../incl -I$(VCPBASE)/include -I$(MINCLD) -I$(VCINCD) $(ORAINC) \
$(JNIINC) $(ORBINC) -I$(ODIR)

LIBP = /libpath:$(VCPBASE)lib/ /libpath:$(MLIBSD)/ /libpath:$(ORALIBS) \
/libpath:$(ORBLIBS)

else                                        # Compiling for VisualAge C++

ODIR = ibm95
CXX = icc
FCPP = -Tdp
VCINC = $(MINCL)
VCINCD = $(MINCLD)
ORBINC = -Ic:/iona/Orbix22/corba2/INCLUDE
ORBLIBS = c:/iona/Orbix22/corba2/lib/

# ***********************************************************************
# Orbix IDL compiler
# ***********************************************************************

IDL = idl
IDLFLAGS = -B -s s.cc -c c.cc -f $(ORBFLAGS)
IDLC = $(IDL) $(IDLFLAGS)
ORBIX201=1

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC = -I../incl -I$(VABASE)/include -I$(VABASE)/sdk/winh \
-I$(VABASE)/sdk/winh/winnt -I$(VABASE)/sdk/winh/win95 -I$(MINCLD) $(ORAINC) \
$(JNIINC) $(ORBINC) -I$(ODIR)

LIBP = $(VABASE)/lib/ $(VABASE)/sdk/lib/ $(MLIBSD)/ $(ORALIBS) $(ORBLIBS)

RNAME = dllrname $@ CPPWOT3=ADDCPP0 CPPWOB3I=ADDCPP01 CPPWOU3I=ADDCPP02 \
CPPWM35I=ADDCPP03 CPPWOR3U=ADDCPPRU /Q

TOUCH = touch $(ODIR)/*

endif                                       # Different Compilers

endif
# ***********************************************************************
#                       End of Windoze 95
# ***********************************************************************

ifeq ($(WHAT_OS), OS/2)

HOST_OS = -DOS2
O = obj
ODIR = os2
CXX = icc
NOUT = >nul 2>&1
OSDIR = os2

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = $(PROOT)$(OSDIR)/lib
MDLLS   = $(PROOT)$(OSDIR)/slib
MBIN    = $(PROOT)$(OSDIR)/bin
M2BIN   = $(MBIN)
MINCL   = $(PROOT)$(OSDIR)/include
MHELP   = $(PROOT)$(OSDIR)/help
VCINC = $(MINCL)

INC = -I../incl -I$(MINCL) -I$(ODIR)
LIB = $(MLIBS);c:/ibmcpp/lib;c:/ibmcpp/dll;c:/tcpip/lib;

RNAME = dllrname $@ CPPOM30=ADDCPP0 CPPOOB3=ADDCPP1 CPPOOU3=ADDCPP2 /Q

TOUCH = touch $(ODIR)/*

endif

# ***********************************************************************
#                           End of OS/2
# ***********************************************************************

# ***********************************************************************
# Running on SunOS
# ***********************************************************************

ifeq ($(WHAT_OS), SunOS)                    # Running on Solaris

HOST_OS = -DOSUNIX

ifeq ($(shell uname -i), i86pc)             # If pc version

INTEL=1

endif                                       # end pc

ifdef INTEL                                 # if intel

ODIR = sunpc
CXX = g++

else                                        # else sparc

ODIR = sun
CXX = CC

endif                                       # end platform

OSDIR = $(ODIR)
O = o
NOUT = > /dev/null 2>&1

# ***********************************************************************
# Path macros
# ***********************************************************************

MLIBS   = $(PROOT)$(OSDIR)/lib
MDLLS   = $(PROOT)$(OSDIR)/slib
MBIN    = $(PROOT)$(OSDIR)/bin
M2BIN   = $(MBIN)
MHELP   = $(PROOT)$(OSDIR)/help
MINCL   = $(PROOT)$(OSDIR)/include

VCINC   = $(MINCL)

# *********************************************************************
# Link libraries for Oracle OCI
# *********************************************************************

# NETLIBS = -lsqlnet -lncr -lsqlnet
# LLIBORA = -lclient -lcommon -lgeneric
# LLIBEPC = -lepc
# CORELIBS = -lnlsrtl3 -lc3v6 -lcore3 -lnlsrtl3 -lcore3 -lnlsrtl3
# OCILIBS = -lclient $(NETLIBS) $(LLIBORA) $(LLIBEPC) $(CORELIBS)

# NDFOPT = $(ORACLE_HOME)/rdbms/lib/kpundf.o

ifdef INTEL                                 # if intel

CXXLIBS = -lpthread -lposix4 -lstdc++

else                                        # else sparc

CXXLIBS = -lpthread -lposix4 -lC -lm -lC_mtstubs -lw -lcx -lc

endif                                       #end platform

# *********************************************************************
# Paths
# *********************************************************************

# ORACLE_HOME = /vol_1/oracle/7.3.2

# ORALIBS = -L$(ORACLE_HOME)/lib -L$(ORACLE_HOME)/rdbms/lib
# ORAINC  = $(ORACLE_HOME)/rdbms/demo

# ***********************************************************************
# Standard include and lib paths
# ***********************************************************************

INC   = -I../incl -I$(MINCL) -I/usr/dt/include -I/usr/openwin/include \
-I/usr/java1.1/include -I/usr/java1.1/include/solaris -I/usr/openwin/share/include \
-I../../incl -I$(ODIR)

LIBP  = -L$(MLIBS) -L$(MDLLS) -L/usr/dt/lib -L/usr/openwin/lib

# ***********************************************************************
# Set up compiler and linker switches
# ***********************************************************************

ifdef EXE                                   # Build EXE

ifdef INTEL                                 # intel

BCPPF = $(DEFINE) $(HOST_OS) -fenum-int-equiv -Wall -D_REENTRANT -D__EXTENSIONS__ -DPOSIX_PTHREAD_SEMANTICS

else                                        # sparc

BCPPF = $(DEFINE) $(HOST_OS) -D_REENTRANT -D__EXTENSIONS__ -DPOSIX_PTHREAD_SEMANTICS

endif                                       # end platform

else                                        # library

ifdef INTEL                                 # intel

BCPPF = $(DEFINE) $(HOST_OS) -fenum-int-equiv -Wall -fpic -D_REENTRANT -D__EXTENSIONS__ -DPOSIX_PTHREAD_SEMANTICS

else                                        # sparc

BCPPF = $(DEFINE) $(HOST_OS) -pic -D_REENTRANT -D__EXTENSIONS__ -DPOSIX_PTHREAD_SEMANTICS

endif                                       # end platform

endif                                       # end exe or lib

ifdef DEBUGME                               # Debug version

ifdef INTEL                                 # intel

CXXFLAGS = -c -DNDEBUG $(BCPPF) -g $(COMPARGS) $(INC) -o $@

else                                        # sparc

CXXFLAGS = -c -DNDEBUG $(BCPPF) -g2 -O0 $(COMPARGS) $(INC) -o $@

endif                                       # end platform

else                                        # Production version

ifdef OPTIMIZE                              # Optimize code

ifdef INTEL                                 # intel

CXXFLAGS = -c -DNDEBUG $(BCPPF) -O $(COMPARGS) $(INC) -o $@

else                                        # sparc

CXXFLAGS = -c -DNDEBUG $(BCPPF) -O -g0 $(COMPARGS) $(INC) -o $@

endif                                       # end platform

else                                        # Don't optimize

ifdef INTEL                                 # intel

CXXFLAGS = -c -DNDEBUG $(BCPPF) $(COMPARGS) $(INC) -o $@

else                                        # sparc

CXXFLAGS = -c -DNDEBUG $(BCPPF) $(COMPARGS) $(INC) -o $@

endif                                       # end platform

endif                                       # end Optimize

endif                                       # end Debugme/Production

ifdef INTEL                                 # intel

COPTF = -c -DNDEBUG $(BCPPF) -O $(COMPARGS) $(INC) -o $@

else                                        # sparc

COPTF = -c -DNDEBUG $(BCPPF) -O -g0 $(COMPARGS) $(INC) -o $@

endif                                       # end platform

LDFLAGS = $(LIBP) -o

# ***********************************************************************
# Macros for linking
# ***********************************************************************

ifdef INTEL                                 # intel

SLIB = $(CXX) -shared $(LIBP) -o $@ $+

else                                        # sparc

SLIB = $(CXX) -G $(LIBP) -o $@ $+

endif                                       # end platform

L32 = $(CXX) $(LDFLAGS) $@ $+

L32PM = $(CXX) $(LDFLAGS) $@ $+

CFLAGS = $(CXXFLAGS)

endif                                       # end Solaris

# ***********************************************************************
#                   End of OS dependent things
# ***********************************************************************

# ***********************************************************************
# Compiler flags etc for Windows NT/95
# ***********************************************************************

ifeq ($(HOST_OS), -DOSWIN)                  # Windows OS

OSDLL = d:/ibmcppw/bin

OCILIBS = ociw32.lib
NDFOPT =
CXXLIBS =


ifdef MSVC                                  # MS Visual C++

LF = /nologo /incremental:no /machine:I386 /pdb:$(ODIR)/$(basename $(@F)).pdb \
$(LIBP) /out:$@ $+

CF = $(DEFINE) $(HOST_OS) -DWIN32 -D_WINDOWS /nologo $(INC)

ifdef DEBUGME                               # Build debug

ifdef EXE                                   # make exe file

CXXFLAGS = $(CF) -D_DEBUG /MD /W3 /Gm /GX /Zi /Od /Fp$(ODIR)/ /Fo$@ /c

LDFLAGS = /subsystem:console /debug $(LF)
LDPMFLAGS =/subsystem:windows /debug $(LF)

else                                        # make dll

CXXFLAGS = $(CF) -D_DEBUG /MDd /W3 /Gm /GX /Zi /Od /Fp$(ODIR)/ /Fo$@ /c

LDFLAGS = /subsystem:windows /dll $(LF) /implib:$(ODIR)/$(basename $(@F)).lib

endif                                       # end exe/dll

else                                        # Build production

ifdef EXE                                   # make exe file

ifdef OPTIMIZE                              # Use optimization

CXXFLAGS = $(CF) -DNDEBUG /MD /W3 /GX /O2 /Fo$@ /Fp$(ODIR)/ /c

else                                        # No optimization

CXXFLAGS = $(CF) -DNDEBUG /MD /W3 /GX /Fo$@ /Fp$(ODIR)/ /c

endif                                       # end Optimize

LDFLAGS = /subsystem:console $(LF)
LDPMFLAGS = /subsystem:windows $(LF)

else                                        # make dll file

ifdef OPTIMIZE                              # Optimize it

CXXFLAGS = $(CF) -DNDEBUG /MD /W3 /GX /O2 /Fo$@ /Fp$(ODIR)/ /c

else                                        # don't optimize it

CXXFLAGS = $(CF) -DNDEBUG /MD /W3 /GX /Fo$@ /Fp$(ODIR)/ /c

endif                                       # end Optimize

LDFLAGS = /subsystem:windows /dll $(LF) /implib:$(ODIR)/$(basename $(@F)).lib


endif                                       # end exe/dll


endif                                       # build production

# ***********************************************************************
# Macro for linking any DLL or exe:
# ***********************************************************************

L32 = link $(LDFLAGS)
L32PM = link $(LDPMFLAGS)

SLIB = $(L32)

# ***********************************************************************
# Macro for linking any libs: (MS visual C++ does it for you)
# ***********************************************************************

ILIB =
MLIB =

RC = irc

CFLAGS = $(CXXFLAGS)

else                                        # Build for VisualAge C++

# ***********************************************************************
# Set up compiler and linker switches for either Debug or No debug
# ***********************************************************************

WFLAGS = -Weff+par+rea+use+

FCPP = -Tdp

BCF = $(DEFINE) $(HOST_OS) -C -Q -G5 -Gm -Gd -Se -Ss -W3 -N40 $(COMPARGS) \
$(INC) -Fo$@ $(WFLAGS)

BCPPF = $(DEFINE) $(HOST_OS) -C -Q -G5 -Gm -Gd -Se -W3 -N40 $(COMPARGS) \
$(INC) -Fo$@ $(WFLAGS)

ifdef EXE                                   # Build exe file

ifdef DEBUGME                               # Make debug version

CFLAGS = -DDEBUG $(BCF) -Ge -Fb -Ti
CXXFLAGS = -DDEBUG $(BCPPF) -Ge -Fb -Ti

LDFLAGS = /nologo /debug $(LIBP) $+ /out:$@
LDPMFLAGS = /nologo /pmtype:pm /debug $(LIBP) $+ /out:$@

else                                        # Make production

ifdef OPTIMIZE                              # Optimize it

CFLAGS = -DNDEBUG $(BCF) -Ge -O
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge -O

else                                        # Don't optimize it

CFLAGS = -DNDEBUG $(BCF) -Ge
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge

endif                                       # end Optimize

LDFLAGS = /nologo $(LIBP) $+ /out:$@
LDPMFLAGS = /nologo /pmtype:pm $(LIBP) $+ /out:$@

endif                                       # end production/debug

else                                        # Build dll file

ifdef DEBUGME                               # make debug

CFLAGS = -DDEBUG $(BCF) -Ge- -Ti
CXXFLAGS = -DDEBUG $(BCPPF) -Ge- -Fb -Ti
LDFLAGS = /nologo /dll /debug $(LIBP) $+ /out:$@

else                                        # make production

ifdef OPTIMIZE                              # Optimize it

CFLAGS = -DNDEBUG $(BCF) -Ge- -O
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge- -O

else                                        # Don't Optimize it

CFLAGS = -DNDEBUG $(BCF) -Ge-
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge-

endif                                       # end Optimize

LDFLAGS = /nologo /dll $(LIBP) $+ /out:$@

endif                                       # end production/debug

endif                                       # end Build dll

# ***********************************************************************
# Macro for linking any DLL or exe:
# ***********************************************************************

MLIB = ilib /nologo /Gi:$(ODIR)/$(basename $(@F)) $^

L32 = ilink $(LDFLAGS)
L32PM = ilink $(LDPMFLAGS)

SLIB = $(L32)

# *****************************************.******************************
# Macro for linking any libs:
# ***********************************************************************

ILIB = ilib /nologo /noba /O:$(ODIR)/$(basename $(@F)) $^

RC = irc $(INC)
RCT = -fo$@

endif                                       # VisualAge C++

endif                                       # Windows platforms

# ************************************************************************
# OS/2 Building
# ************************************************************************

ifeq ($(HOST_OS), -DOS2)

# ***********************************************************************
# Set up compiler and linker switches for either Debug or No debug
# ***********************************************************************

OCILIBS =
NDFOPT =
CXXLIBS =
FCPP = -Tp

WFLAGS = -Weff+par+rea+use+

BCF = $(DEFINE) $(HOST_OS) -C -Q -G5 -Gm -Gd -Se -Ss -W3 -N40 $(INC) $(COMPARGS) \
$(INC) -Fo$@
BCPPF = $(DEFINE) $(HOST_OS) -C -Q -G5 -Gm -Gd -Se -W3 -N40 $(INC) $(COMPARGS) \
$(INC) -Ft$(ODIR)/tmpinc -Fo$@

ifdef EXE                                   # Build exe file

ifdef DEBUGME                               # Make debug version

CFLAGS = -DDEBUG $(BCF) -Ge -Fb -Ti
CXXFLAGS = -DDEBUG $(BCPPF) -Ge -Fb -Ti

LDFLAGS = -Q -B"/DEBUG" -Fe$@
LDPMFLAGS = -Q -B"/DEBUG /pmtype:pm" -Fe$@

else                                        # Make production

ifdef OPTIMIZE
CFLAGS = -DNDEBUG $(BCF) -Ge -O
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge -O
else
CFLAGS = -DNDEBUG $(BCF) -Ge
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge
endif

LDFLAGS = -Q -Fe$@
LDPMFLAGS = -Q -B"/pmtype:pm" -Fe$@

endif                                       # production/debug

else                                        # Build dll file

ifdef DEBUGME                               # make debug

CFLAGS = -DDEBUG $(BCF) -Ge- -Ti
CXXFLAGS = -DDEBUG $(BCPPF) -Ge- -Fb -Ti
LDFLAGS = -Q -B"/DLL /DEBUG" -Fe$@

else                                        # make production

ifdef OPTIMIZE                              # Optimize

CFLAGS = -DNDEBUG $(BCF) -Ge- -O
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge- -O

else                                        # Don't optimize

CFLAGS = -DNDEBUG $(BCF) -Ge-
CXXFLAGS = -DNDEBUG $(BCPPF) -Ge-

endif                                       #optimize choice

LDFLAGS = -Q -B"/DLL" -Fe$@

endif                                       # production/debug

endif                                       # Build dll

# ***********************************************************************
# Macro for linking any DLL or exe:
# ***********************************************************************

MLIB = implib /nologo $(ODIR)/$(basename $(@F)).lib $@

L32 = icc $(LDFLAGS) $+
L32PM = icc $(LDPMFLAGS) $+

SLIB = $(L32)

# ***********************************************************************
# Macro for linking any libs:
# ***********************************************************************

ILIB = ilib /nologo /noba $@ $+;

RC = rc -r
RCT = $@

endif                                       # Build for OS/2

# ***********************************************************************
# Patterns
# ***********************************************************************

$(CLDIR)/%.class : %.java
	@echo Compiling $@...
	javac -deprecation -d ./ $<

%.class : %.java
	@echo Compiling $@...
	javac -deprecation $<

$(ODIR)/%.hh : %.idl
ifdef ORBIX201
	$(IDLC) $<
	mv $(basename $(@F))c.cc $(ODIR)
	mv $(basename $(@F))s.cc $(ODIR)
	mv $(basename $(@F)).hh $(ODIR)
else
	$(IDLC) $<
endif

$(ODIR)/%.$(O): %.c
	@echo Compiling $@...
	$(CXX) $(CFLAGS) $<

$(ODIR)/%.$(O): %.cc
	@echo Compiling $@...
	$(CXX) $(CXXFLAGS) $(FCPP) $<

$(ODIR)/%.$(O) : $(ODIR)/%.cc
	@echo Compiling $@...
	$(CXX) $(CXXFLAGS) $(FCPP) $<

$(ODIR)/%.$(O): *.cpp
	@echo Compiling $@...
	$(CXX) $(CXXFLAGS) $<

$(ODIR)/%.$(O): %.cxx
	@echo Compiling $@...
	$(CXX) $(CXXFLAGS) $(FCPP) $<

$(ODIR)/%.hlp: %.ipf
	@echo compiling help...
	ipfc $<
	cp $(@F) $(ODIR)/.
	$(ERASE) $(@F)

$(ODIR)/%.inf: %.ipf
	@echo compiling help...
	ipfc $< /inf
	cp $(@F) $(ODIR)/.
	$(ERASE) $(@F)

$(MHELP)/%.hlp : $(ODIR)/%.hlp
	$(COPY)

$(MHELP)/%.inf : $(ODIR)/%.inf
	$(COPY)

$(MINCL)/%.h : %.h
	$(COPY)

$(MINCL)/%.hpp : %.hpp
	$(COPY)

$(MINCL)/%.inl : %.inl
	$(COPY)

$(VCINC)/%.hpp : %.hpp
	$(COPY)

$(VCINC)/%.inl : %.inl
	$(COPY)

$(MDLLS)/%.so : $(ODIR)/%.so
	$(COPY)

$(MDLLS)/%.a : $(ODIR)/%.a
	$(COPY)

$(MLIBS)/%.a : $(ODIR)/%.a
	$(COPY)

$(MLIBS)/%.lib : $(ODIR)/%.lib
	$(COPY)

$(MBIN)/% : $(ODIR)/%
	$(COPY)

$(M2BIN)/% : $(ODIR)/%
	$(COPY)

$(MDLLS)/%.dll : $(ODIR)/%.dll
	$(COPY)

# ************************************************************************
#  Some common targets
# ************************************************************************

test:
	@echo WHAT_OS = $(WHAT_OS)
	@echo HOST_OS = $(HOST_OS)
	@echo PROOT = $(PROOT)
	@echo PROOTD = $(PROOTD)
	@echo OSDIR = $(ODIR)
	@echo ODIR = $(ODIR)
	@echo MINCL = $(MINCL)
	@echo VCINC = $(VCINC)
	@echo MINCLD = $(MINCLD)
	@echo VCINCD = $(VCINCD)
	@echo MBIN = $(MBIN)
	@echo MLIBS = $(MLIBS)
	@echo MDLLS = $(MDLLS)
	@echo MHELP = $(MHELP)
	@echo CXX = $(CXX)
	@echo O = $(O)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo CFLAGS = $(CFLAGS)
	@echo LDFLAGS = $(LDFLAGS)
	@echo OCILIBS = $(OCILIBS)
	@echo LIBP = $(LIBP)
	@echo INC = $(INC)
	@echo VABASE = $(VABASE)
	@echo VCPBASE = $(VCPBASE)

# ************************************************************************
# Ensure directories exist
# ************************************************************************

dirs :
	$(MD) $(ODIR)
	$(CHM) $(ODIR)
	$(MD) $(MLIBS)
	$(CHM) $(MLIBS)
	$(MD) $(MDLLS)
	$(CHM) $(MDLLS)
	$(MD) $(MBIN)
	$(CHM) $(MBIN)
	$(MD) $(MHELP)
	$(CHM) $(MHELP)
	$(MD) $(MINCL)
	$(CHM) $(MINCL)
	$(MD) $(VCINC)
	$(CHM) $(VCINC)

targets :
	@echo $(ALL)

clean :
	$(ERASE) $(ODIR)/* $(NOUT)
	@echo [[Deleted local targets... ]]

jclean :
	$(ERASE) $(CLDIR)/* $(NOUT)
	$(ERASE) $(CLPACK) $(NOUT)
	$(ERASE) $(JDDIR) $(NOUT)
	@echo [[Deleted local targets... ]]

new : clean all

jnew : jclean all

mclean : clean
	$(ERASE) $(ALL) $(NOUT)
	@echo [[Deleted master files...]]

package : $(CLPACK)
	$(JAR)
	@echo [[Package $(PKGNAME) is complete...]]

jdoc :
	javadoc -package -d $(JDDIR) *.java
	@echo [[Doc for $(PKGNAME) is complete...]]

# ************************************************************************
#  Lib dependencies (general)
# ************************************************************************

Testengn.lib : $(MLIBS)/Testengn.lib

Testngnw.lib : $(MLIBS)/Testngnw.lib

Addtcl.lib : $(MLIBS)/Addtcl.lib

Addtcp.lib : $(MLIBS)/Addtcp.lib

Addxpf.lib : $(MLIBS)/Addxpf.lib

Addlst.lib : $(MLIBS)/Addlst.lib

Addgui.lib : $(MLIBS)/Addgui.lib

Addoci.lib : $(MLIBS)/Addoci.lib

Addprt.lib : $(MLIBS)/Addprt.lib

Addtclw.lib : $(MLIBS)/Addtclw.lib

Addtcpw.lib : $(MLIBS)/Addtcpw.lib

Addxpfw.lib : $(MLIBS)/Addxpfw.lib

Addlstw.lib : $(MLIBS)/Addlstw.lib

Addociw.lib : $(MLIBS)/Addociw.lib

-lAddxpf : $(MDLLS)/libAddxpf.so

-lAddlst : $(MDLLS)/libAddlst.so

-lAddoci : $(MDLLS)/libAddoci.so

-lAddtcl : $(MDLLS)/libAddtcl.so

-lTestengn : $(MDLLS)/libTestengn.so

-lAddtcp : $(MDLLS)/libAddtcp.so

wsock32.lib kernel32.lib so32dll.lib \
tcp32dll.lib advapi32.lib comdlg32.lib user32.lib \
gdi32.lib rexx.lib wrexx32.lib :


$(CXXLIBS) $(OCILIBS) -lpthreads -lm :


# ***********************************************************************
#
#   (c)1998 ADDC Infotech GmbH
#
#   END OF FILE.
#
# ***********************************************************************

