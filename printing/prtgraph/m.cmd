@echo off
del tmp
nmake -nologo -f rexxdll.mak NODEBUG=1 all 2>&1 | tee -a tmp
rem nmake -nologo -f rexxexe.mak NODEBUG=1 all 2>&1 | tee -a tmp
nmake -nologo -f vrprint.mak NODEBUG=1 dll 2>&1 | tee -a tmp
slstart tmp
