#
# Makefile for vxrexx.cls classes
#

prepopts =
scopts = -r -s 64000 -s "h;sc;ih;c"

.SUFFIXES: .cls .csc

.csc.h:
    -@echo foo > $*.c
    -@del $*.c 2>&1 >nul
    sc $(scopts) $<
    vxgetrel $*.sc ..\$*.rel
    ..\..\prepc $*.c $(prepopts)

hfiles = printer.h
          
all: $(hfiles)
    @echo SOM class files are up-to-date.

smpath :
    SET SMINCLUDE=.;T:\VXODK\SOM.210\SC;$(TOOLKIT)\SC;$(SMINCLUDE);$(INCLUDE)
    SET PATH=T:\VXODK\BIN;$(TOOLKIT)\OS2BIN;$(PATH)

printer.h: printer.csc 

clean:
    -del *.ih
    -del *.sc
    -del *.c
    -del *.ph
    -del *.def
    -del *.h
    -del *.cs2

#
# End of makefile
#
