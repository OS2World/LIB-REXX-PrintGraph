# ************************************************************************
#
#  Author   : Peter Kanis
#  Workfile : %M%
#  Created  : 20 Apr 1999
#  Revision : %I%
#  Date     : %E%
#
# ************************************************************************

PROJ = $(HOME)/projects/
O = o
ODIR = obj
MINCL = $(PROJ)include
MDLLS = $(PROJ)slib
MBIN = $(PROJ)bin

JNIINC = -I $(PROJ)jni/include/mvs -I $(PROJ)jni/include
JNILIBS = -L /usr/lpp/java/J1.1/lib

DB2INC = -I //'DB2.R510.DSN510.SDSNC.H'


TSTINC = -I $(PROJ)tstngn/incl

# ****** For DLLs ********************************************************

CXX = cxx -V -c -+ -I ./ -I $(MINCL) $(DB2INC) $(JNIINC) $(TSTINC) \
-W c,dll,expo,langlvl(extended)

# ****** For executables *************************************************

CC = cxx -c -+ -I ./ -I $(MINCL) $(DB2INC) $(JNIINC) $(TSTINC) \
-W c,dll,langlvl(extended)

# ****** Bind dll ********************************************************

SLIB = cxx -L $(MDLLS) $(JNILIBS) -W l,dll -o $@ $<

# ****** Bind executable *************************************************

L32 = cxx -L $(MDLLS) $(JNILIBS) -W l,dll -o $@ $<

# ************************************************************************
#  Metarules
# ************************************************************************

$(ODIR)/%.o : %.cc
	$(CXX) -o $@ $<

$(ODIR)/%.o : %.cxx
	$(CC) -o $@ $<

$(MINCL)/%.h : %.h
	cp $? $@

$(MINCL)/%.hpp : %.hpp
	cp $? $@

$(MDLLS)/%.x : %.x
	cp $? $@

$(MINCL)/%.inl : %.inl
	cp $? $@

$(MDLLS)/%.so : %.so
	cp $? $@

# ************************************************************************
#  Standard Targets
# ************************************************************************

clean :
	-rm $(ODIR)/*

mclean : clean
	-rm $(ALL)

new : clean all

# ************************************************************************
#
#                               END OF FILE.
#
# ************************************************************************


