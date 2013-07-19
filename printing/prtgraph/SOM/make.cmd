/**/
'@echo off'
if "..\settings.cmd"()<>0 then exit 32000

vxodk = value( "VXODK",,"OS2ENVIRONMENT" )
if( right( vxodk, 1 ) \= '\' )then do
    vxodk = vxodk || '\'
end

compiler = Value( "vxcompiler", ,"OS2ENVIRONMENT" )
version = Value( "vxversion", , "OS2ENVIRONMENT" )
dllname = Value( "vxdllname", , "OS2ENVIRONMENT" ) 
som = Value( "vxsom", , "OS2ENVIRONMENT" )

if( vxodk = "" )then do
    say "Please define the VXODK environment variable."
    exit 32000
end
toolkit = value( "TOOLKIT",,"OS2ENVIRONMENT" )
if( toolkit = "" )then do
    say "Please define the TOOLKIT environment variable."
    exit 32000
end

"@echo off"
"setlocal"

if( som = 'SOM2' )then do
    "set SMINCLUDE=.;"||vxodk||"SOM."version"\SC;%SOMBASE%\INCLUDE;%SMINCLUDE%;%INCLUDE%"
    "set PATH="||vxodk||"BIN;%SOMBASE%\BIN;%TOOLKIT%\OS2BIN;%PATH%"
end; else do
    "set SMINCLUDE=.;"||vxodk||"SOM."version"\SC;%TOOLKIT%\SC;%SMINCLUDE%;%INCLUDE%"
    "set PATH="||vxodk||"BIN;%TOOLKIT%\OS2BIN;%PATH%"
end

"vxbrows2.exe /n vxrexx.cls"
"cd sc"

if( som = 'SOM2' )then do
    if( compiler = 'CSET' )then do
         "nmake /nologo SOM2=1 /f vxrexx.mak" arg(1)
    end;else do
        "wmake USE_WMAKE=1 SOM2=1 /f vxrexx.mak" arg(1)
    end
end; else do
    if( compiler = 'CSET' )then do
        "nmake /nologo /f som.mak" arg(1)
    end; else do
        "wmake USE_WMAKE=1 /f vxrexx.mak" arg(1)
    end
end

"cd .."
"endlocal"
