/*:VRX         Main
*/
/*  Main
*/
Main:
/*  Process the arguments.
    Get the parent window.
*/
    parse source . calledAs .
    parent = ""
    argCount = arg()
    argOff = 0
    if( calledAs \= "COMMAND" )then do
        if argCount >= 1 then do
            parent = arg(1)
            argCount = argCount - 1
            argOff = 1
        end
    end; else do
        call VROptions 'ImplicitNames'
    end
    InitArgs.0 = argCount
    if( argCount > 0 )then do i = 1 to argCount
        InitArgs.i = arg( i + argOff )
    end
    drop calledAs argCount argOff

/*  Load the windows
*/
    call VRInit
    parse source . . spec
    _VREPrimaryWindowPath = ,
        VRParseFileName( spec, "dpn" ) || ".VRW"
    _VREPrimaryWindow = ,
        VRLoad( parent, _VREPrimaryWindowPath )
    drop parent spec
    if( _VREPrimaryWindow == "" )then do
        call VRMessage "", "Cannot load window:" VRError(), ,
            "Error!"
        _VREReturnValue = 32000
        signal _VRELeaveMain
    end

/*  Process events
*/
    call Init
    signal on halt
    do while( \ VRGet( _VREPrimaryWindow, "Shutdown" ) )
        _VREEvent = VREvent()
        interpret _VREEvent
    end
_VREHalt:
    _VREReturnValue = Fini()
    call VRDestroy _VREPrimaryWindow
_VRELeaveMain:
    call VRFini
exit _VREReturnValue

VRLoadSecondary:
    __vrlsWait = abbrev( 'WAIT', translate(arg(2)), 1 )
    if __vrlsWait then do
        call VRFlush
    end
    __vrlsHWnd = VRLoad( VRWindow(), VRWindowPath(), arg(1) )
    if __vrlsHWnd = '' then signal __vrlsDone
    if __vrlsWait \= 1 then signal __vrlsDone
    call VRSet __vrlsHWnd, 'WindowMode', 'Modal' 
    __vrlsTmp = __vrlsWindows.0
    if( DataType(__vrlsTmp) \= 'NUM' ) then do
        __vrlsTmp = 1
    end
    else do
        __vrlsTmp = __vrlsTmp + 1
    end
    __vrlsWindows.__vrlsTmp = VRWindow( __vrlsHWnd )
    __vrlsWindows.0 = __vrlsTmp
    do while( VRIsValidObject( VRWindow() ) = 1 )
        __vrlsEvent = VREvent()
        interpret __vrlsEvent
    end
    __vrlsTmp = __vrlsWindows.0
    __vrlsWindows.0 = __vrlsTmp - 1
    call VRWindow __vrlsWindows.__vrlsTmp 
    __vrlsHWnd = ''
__vrlsDone:
return __vrlsHWnd

/*:VRX         Fini
*/
Fini:
    window = VRWindow()
    call VRSet window, "Visible", 0
    drop window
return 0

/*:VRX         Halt
*/
Halt:
    signal _VREHalt
return

/*:VRX         Init
*/
Init:

    call RXFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
    call SysLoadFuncs

    call VRRedirectStdIO 'Off'

    window = VRWindow()
    call VRMethod window, "CenterWindow"
    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"
    drop window

    /**** Get the VX-REXX environmnt ********/

    set_path = VALUE( 'PATH', , 'OS2ENVIRONMENT');
    bootdrive = substr( set_path, pos( '\OS2\SYSTEM', set_path ) -2, 2);
    vxrexx = ''
    vxrexx = VALUE( 'VXREXX',, 'OS2ENVIRONMENT');
    if right( vxrexx, 1) = '\' then do
        l = length( vxrexx) - 1
        vxrexx = substr( vxrexx, 1, l);
    end
    vxsamp = vxrexx || '\samples'
    prtproj = vxsamp || '\VRPrint'
    vxsys = vxrexx || '\system'
    bmpdir = vxrexx

return

/*:VRX         PB_1_Click
*/
PB_1_Click: 

    call VRSet "Window1", "Pointer", "Wait"

    n = 12
    inst_prog = VRGet( "CB_1", "Set");
    inst_proj = VRGet( "CB_2", "Set");
    inst_del = VRGet( "CB_3", "Set");

    if inst_prog then
        n = n + 2
    
    if inst_proj then
        n = n + 14

    s_inc = set_increment( n);
    ok = VRSet( "DT_2", "Caption", "Installing VRPrinter DLL and support files" )

    /**** Install DLL, VXO & INF files *******************/

    'copy VRPRINT.DLL' vxrexx '> NUL'
    call slider_inc
    'copy DJPEG.EXE' vxrexx '> NUL'
    call slider_inc
    'copy VRPRINT.VXO' vxrexx '> NUL'
    call slider_inc
    'copy VRPRINT.INF' vxrexx '> NUL'
    call slider_inc
    
    /**** Install MTO and macro files *******************/

    'copy PRINTER.MTO' vxsys '> NUL'
    call slider_inc

    'copy *.VRM' vxsys '> NUL'
    call slider_inc
    'copy *.VRW' vxsys '> NUL'
    call slider_inc

    classname = 'WPProgram'
    title     = 'VRPrinter' || '0a'x || 'Reference'
    location  = '<VXREXX_FOLDER>'
    setup     = 'EXENAME=view.exe;' ||,
                'PROGTYPE=PM;' ||,
                'PARAMETERS=' || vxrexx || '\VRPRINT.INF;' ||,
                'STARTUPDIR=' || vxrexx || ';'
    call SysCreateObject classname, title, location, setup, 'r'
    call slider_inc


    if inst_prog then do
        'md' prtproj
        ok = VRSet( "DT_2", "Caption", "Installing VRPrinter demo program" )
        'copy VRPRINT.EXE' prtproj '> NUL'
        call slider_inc

        classname = "WPProgram"
        title = "VRPrinter Demo"
        location = "<VXREXX_SAMPLES>"
        setup = "EXENAME=" || prtproj || "\VRPRINT.EXE;PROGTYPE=PM;STARTUPDIR=" || prtproj || ";"
        call SysCreateObject classname, title, location, setup, 'r'
        call slider_inc

    end

    if inst_proj then do
        if \inst_prog then
            'md' prtproj
        ok = VRSet( "DT_2", "Caption", "Installing VRPrinter demo project" )

        classname = "WPShadow"
        title     = "VRPrinter"
        location  = "<SAMPLE_SOURCE>"
        setup     = "SHADOWID=" || prtproj || ";"

        call SysCreateObject classname, title, location, setup, 'r'
        call slider_inc

        'copy VRPRINT.VRP' prtproj '> NUL'
        call slider_inc
        'copy VRPRINT.RC' prtproj '> NUL'
        call slider_inc
        'copy VRPRINT.RES' prtproj '> NUL'
        call slider_inc
        'copy TOPWIN.VRX' prtproj '> NUL'
        call slider_inc
        'copy TOPWIN.VRY' prtproj '> NUL'
        call slider_inc
        'copy *.TXT' prtproj '> NUL'
        'copy READ.ME' prtproj '> NUL'
        call slider_inc
        'copy ADDLOGO.BMP' prtproj '> NUL'
        call slider_inc
        'copy PRTMAN.ICO' prtproj '> NUL'
        call slider_inc
        'copy RESOURCE.DLL' vxrexx '> NUL'
        call slider_inc
        'copy ADDLOGO.BMP' bmpdir '> NUL'
        call slider_inc
        'copy TESTORIG.JPG' bmpdir '> NUL'
        call slider_inc
    end
    
    if inst_del then do
        ok = VRSet( "DT_2", "Caption", "Deleting installation files" )
        'del *.VRM > NUL'
        'del *.VRX > NUL'
        'del *.VRP > NUL'
        'del *.VXO > NUL'
        'del *.VRY > NUL'
        'del *.VRW > NUL'
        'del *.MTO > NUL'
        'del *.EXE > NUL'
        'del *.DLL > NUL'
        'del *.TXT > NUL'
        'del *.INF > NUL'
        'del *.BMP > NUL'
        'del *.ICO > NUL'
        'del *.RC > NUL'
        'del *.RES > NUL'
        'del *.ME > NUL'
    end

    ok = VRSet( "DT_2", "Caption", "installation complete" )
    call VRSet "Window1", "Pointer", "<default>"

return

/*:VRX         PB_2_Click
*/
PB_2_Click: 
    call Quit
return

/*:VRX         Quit
*/
Quit:
    window = VRWindow()
    call VRSet window, "Shutdown", 1
    drop window
return

/*:VRX         set_increment
*/
set_increment: procedure expose ticks

    parse arg inc

    sl_inc = 100 / inc

    ticks = 0

    call VRSet SL_1, "Percentile", 0

return sl_inc

/*:VRX         Slider_inc
*/
Slider_inc: 
    ticks = ticks + 1;
    position = format( ticks * s_inc, 3, 0);

    call VRSet SL_1, "Percentile", position
return

/*:VRX         Window1_Close
*/
Window1_Close:
    call Quit
return

