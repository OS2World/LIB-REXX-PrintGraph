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

/*:VRX         CB_2_Click
*/
CB_2_Click: 
    set = VRGet( "CB_2", "Set" )
    if \set then do
        ok = VRSet( "DDCB_fc1", "Enabled", 0 )
        ok = VRSet( "DDCB_lc1", "Enabled", 0 )
        ok = VRSet( "DDCB_tc1", "Enabled", 0 )
        ok = VRSet( "SPIN_fill1", "Enabled", 0 )
        ok = VRSet( "SPIN_line1", "Enabled", 0 )
    end
    else do
        ok = VRSet( "DDCB_fc1", "Enabled", 1 )
        ok = VRSet( "DDCB_lc1", "Enabled", 1 )
        ok = VRSet( "DDCB_tc1", "Enabled", 1 )
        ok = VRSet( "SPIN_fill1", "Enabled", 0 )
        ok = VRSet( "SPIN_line1", "Enabled", 0 )
    end

return

/*:VRX         CB_3_Click
*/
CB_3_Click: 
    set = VRGet( "CB_3", "Set" )
    if \set then do
        ok = VRSet( "DDCB_fc", "Enabled", 0 )
        ok = VRSet( "DDCB_lc", "Enabled", 0 )
        ok = VRSet( "DDCB_tc", "Enabled", 0 )
        ok = VRSet( "DDCB_fc1", "Enabled", 0 )
        ok = VRSet( "DDCB_lc1", "Enabled", 0 )
        ok = VRSet( "DDCB_tc1", "Enabled", 0 )
    end
    else do
        ok = VRSet( "DDCB_fc", "Enabled", 1 )
        ok = VRSet( "DDCB_lc", "Enabled", 1 )
        ok = VRSet( "DDCB_tc", "Enabled", 1 )
        ok = VRSet( "DDCB_fc1", "Enabled", 1 )
        ok = VRSet( "DDCB_lc1", "Enabled", 1 )
        ok = VRSet( "DDCB_tc1", "Enabled", 1 )
    end
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
    crlf = "0d0a"x
    left = VRGet( "SPIN_left", "Value");
    cols = VRGet( "SPIN_cols", "Value");
    fill = VRGet( "SPIN_fill", "Value");
    line = VRGet( "SPIN_line", "Value");
    hfill = VRGet( "SPIN_fill1", "Value");
    hline = VRGet( "SPIN_line1", "Value");
    widths = VRGet( "EF_widths", "Value");
    headers = VRGet( "EF_headers", "Value");
    pts = VRGet( "SPIN_Pts", "Value");
    font = VRGet( "EF_font", "Value");
    set = VRGet( "CB_4", "Set");
    if set then
        font = '"' || font || '"'

    wide.0 = cols;
    do i = 1 to cols
        wide.i = 0;
    end
    txt.0 = cols;
    do i = 1 to cols
        txt.i = '';
    end

    hdr = VRGet( "CB_2", "Set");
    all = VRGet( "CB_1", "Set");
    clr = VRGet( "CB_3", "Set");
    if clr then do
        tc = VRGet( "DDCB_tc", "Value");
        if VRMethod( "DDCB_tc", "FindString", tc) > 0 then
            tc = '"' || tc || '"'
        lc = VRGet( "DDCB_lc", "Value");
        if VRMethod( "DDCB_lc", "FindString", lc) > 0 then
            lc = '"' || lc || '"'
        fc = VRGet( "DDCB_fc", "Value");
        if VRMethod( "DDCB_fc", "FindString", fc) > 0 then
            fc = '"' || fc || '"'
        htc = VRGet( "DDCB_tc1", "Value");
        if VRMethod( "DDCB_tc1", "FindString", htc) > 0 then
            htc = '"' || htc || '"'
        hlc = VRGet( "DDCB_lc1", "Value");
        if VRMethod( "DDCB_lc1", "FindString", hlc) > 0 then
            hlc = '"' || hlc || '"'
        hfc = VRGet( "DDCB_fc1", "Value");
        if VRMethod( "DDCB_fc1", "FindString", hfc) > 0 then
            hfc = '"' || hfc || '"'
        ret = "table.0 = 15" || crlf
    end
    else
        ret = "table.0 = 9" || crlf

    ret = ret || "table.1 =" fill || crlf
    ret = ret || "table.2 =" line || crlf
    ret = ret || "table.3 =" hdr || crlf
    ret = ret || "table.4 =" hfill || crlf
    ret = ret || "table.5 =" hline || crlf
    ret = ret || "table.6 =" all || crlf
    ret = ret || "table.7 =" pts || crlf
    ret = ret || "table.8 =" font || crlf
    ret = ret || "table.9 =" left || crlf

    if clr then do
        ret = ret || "table.10 =" tc || crlf
        ret = ret || "table.11 =" lc || crlf
        ret = ret || "table.12 =" fc || crlf
        ret = ret || "table.13 =" htc || crlf
        ret = ret || "table.14 =" hlc || crlf
        ret = ret || "table.15 =" hfc || crlf || crlf
    end

    ret = ret || "Cols.0.0 =" cols || crlf || crlf

    p = pos( ',', widths);
    i = 1;
    do while( p > 0)
        wide.i = substr( widths, 1, p - 1);
        widths = substr( widths, p + 1);
        p = pos( ',', widths);
        i = i + 1;
    end
    wide.i = widths;
    
    p = pos( ',', headers);
    i = 1;
    do while( p > 0)
        txt.i = substr( headers, 1, p - 1);
        headers = substr( headers, p + 1);
        p = pos( ',', headers);
        i = i + 1;
    end
    txt.i = headers;
    
    do i = 1 to cols
        ret = ret || "Cols." || i || ".1 =" wide.i || crlf
        ret = ret || "Cols." || i || ".2 =" txt.i || crlf
        ret = ret || crlf
    end

    ret = ret || 'ok = VRMethod( "' || object ||'", "' || method || '", "table.", "cols.");'
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

/*:VRX         VRPrTbl2_Close
*/
VRPrTbl2_Close:
    call Quit
return

