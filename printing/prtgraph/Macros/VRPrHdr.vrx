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

/*:VRX         dlg_Close
*/
dlg_Close:
    call Quit
return

/*:VRX         dlg_Help
*/
dlg_Help: 
    address cmd 'view vrprint Formatting Characters'
return

/*:VRX         Fini
*/
Fini:
    window = VRWindow()
    call VRSet window, "Visible", 0
    drop window
return ret

/*:VRX         Halt
*/
Halt:
    signal _VREHalt
return

/*:VRX         Init
*/
Init:

    ret = '';

    if InitArgs.0 < 2 then
        call Quit;

    object = InitArgs.1;
    method = InitArgs.2;

    ok = VRSet( "SPIN_1", "Value", 3 )
    
    window = VRWindow()
    ok = VRSet( window, "Caption", method )
    call VRMethod window, "CenterWindow"
    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"
    drop window
return

/*:VRX         PB_accept_Click
*/
PB_accept_Click: 

    strlist = '';
    value = VRGet( "SPIN_1", "Value" )
    do i = 1 to value
        ename = "EF_Value" || i
        cname = "CB_" || i
        str = VRGet( ename, 'Value');
        set = VRGet( cname, 'Set');
        if set then
            str = '"' || str || '"'

        if i = 1 then
            strlist = str;
        else
            strlist = strlist',' str
    end

    ret = 'ok = VRMethod( "' || object ||'", "' || method || '",' value',' strlist || ");"
    call Quit
return

/*:VRX         PB_Cancel_Click
*/
PB_Cancel_Click: 
    ret = '';
    call Quit;
return

/*:VRX         Quit
*/
Quit:
    window = VRWindow()
    call VRSet window, "Shutdown", 1
    drop window
return

/*:VRX         SPIN_1_Change
*/
SPIN_1_Change: 
    value = VRGet( "SPIN_1", "Value" )
    endval = value + 1;

    do i = 1 to value
        ename = "EF_Value" || i
        cname = "CB_" || i
        call VRSet ename, 'Enabled', 1
        call VRSet cname, 'Enabled', 1
    end

    do i = endval to 5
        ename = "EF_Value" || i
        cname = "CB_" || i
        call VRSet ename, 'Enabled', 0
        call VRSet cname, 'Enabled', 0
    end
return

