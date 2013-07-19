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
        call VROptions 'NoEchoQuit'
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

    window = VRWindow()
    call VRMethod window, "CenterWindow"
    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"
    drop window
return

/*:VRX         PB_accept_Click
*/
PB_accept_Click: 

    have_buttons = 0
    b1 = VRGet( "EF_Value2", "Value" )
    if b1 <> '' then do
        have_buttons = 1
        if VRGet( "CB_2", "Set" ) then
            b1 = '"' || b1 || '"'
    end

    b2 = VRGet( "EF_Value3", "Value" )
    if b2 <> '' then do
        have_buttons = 1
        if VRGet( "CB_3", "Set" ) then
        b2 = '"' || b2 || '"'
    end

    b3 = VRGet( "EF_Value4", "Value" )
    if b3 <> '' then do
        have_buttons = 1
        if VRGet( "CB_4", "Set" ) then
            b3 = '"' || b3 || '"'
    end

    if have_buttons then do
        crlf = "0d0a"x

        ret = 'PDButs.0 = 3' || crlf
        if b1 <> '' then
            ret = ret || 'PDButs.1 =' b1 || crlf
        if b2 <> '' then
            ret = ret || 'PDButs.2 =' b2 || crlf
        if b3 <> '' then
            ret = ret || 'PDButs.3 =' b3 || crlf
    end

    ret = ret || 'ok = VRMethod( "' || object ||'", "' || method || '"'
    
    title = VRGet( "EF_Value1", "Value" )
    
    if VRGet( "CB_1", "Set" ) & ( title <> '') then
        title = '"' || title || '"'

    if title <> '' then
        ret = ret || ',' title

    if have_buttons then do
        if title <> '' then
            ret = ret ||  ', , "PDButs."'
        else
            ret = ret || ', "PDButs."'
    end

    ret = ret || ');'

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

/*:VRX         VRPrPDlg_Close
*/
VRPrPDlg_Close:
    call Quit
return

