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

/*:VRX         CB_1_Click
*/
CB_1_Click: 
    
    /***** Enable or disable spin buttoms *******************************/
    
    if VRGet( CB_1, 'Set') then do
        call VRSet SPIN_1, 'Enabled', 1
        call VRSet SPIN_4, 'Enabled', 1
    end
    else do
        call VRSet SPIN_1, 'Enabled', 0
        call VRSet SPIN_4, 'Enabled', 0
    end

return

/*:VRX         Fini
*/
Fini:
    window = VRWindow()
    call VRSet window, "Visible", 0
    drop window

return 0

/*:VRX         front_page_Close
*/
front_page_Close: 
    call front_page_Fini
return

/*:VRX         front_page_Create
*/
front_page_Create: 
    call front_page_Init
return

/*:VRX         front_page_Fini
*/
front_page_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         front_page_Init
*/
front_page_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         front_page_Resize
*/
front_page_Resize: 
    call resize_dlg front_page, GB_11
    if loading then do
        call VRSet "NB_1", "Selected", 2
        call VRSet "NB_1", "Selected", 3
        call VRSet "NB_1", "Selected", 4
        call VRSet "NB_1", "Selected", 5
        call VRSet "NB_1", "Selected", 6
        call VRSet "NB_1", "Selected", 1
        loading = 0
        call VRSet "NB_1", "Painting", 1;
    end
return

/*:VRX         ftr_dlg_Close
*/
ftr_dlg_Close: 
    call ftr_dlg_Fini
return

/*:VRX         ftr_dlg_Create
*/
ftr_dlg_Create: 
    call ftr_dlg_Init
return

/*:VRX         ftr_dlg_Fini
*/
ftr_dlg_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         ftr_dlg_Init
*/
ftr_dlg_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         ftr_dlg_Resize
*/
ftr_dlg_Resize: 
    call resize_dlg ftr_dlg, GB_5
return

/*:VRX         Halt
*/
Halt:
    signal _VREHalt
return

/*:VRX         hdr_ftr_dlg_Close
*/
hdr_ftr_dlg_Close: 
    call hdr_ftr_dlg_Fini
return

/*:VRX         hdr_ftr_dlg_Create
*/
hdr_ftr_dlg_Create: 
    call hdr_ftr_dlg_Init
return

/*:VRX         hdr_ftr_dlg_Fini
*/
hdr_ftr_dlg_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         hdr_ftr_dlg_Init
*/
hdr_ftr_dlg_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         hdr_ftr_dlg_Resize
*/
hdr_ftr_dlg_Resize: 
    call resize_dlg hdr_ftr_dlg, GB_4
return

/*:VRX         idm_about_Click
*/
idm_about_Click: 
    wTitle = 'VRPrint Demo v' || version
    call aboutwin VRWindow(), wTitle
return

/*:VRX         idm_exit_Click
*/
idm_exit_Click: 
    call Quit
return

/*:VRX         idm_prt_setup_Click
*/
idm_prt_setup_Click: 
    
    /***** Call the printers dialog *************************************/
    
    buttons.0 = 3
    buttons.1 = '~Accept'
    buttons.2 = '~Job Properties...'
    buttons.3 = 'Cancel'

    pName = VRMethod( "PRT_1", "PrinterDialog", 'Choose printer', 'buttons.');
    if pName = '' then
        pName = VRGet( "PRT_1", "CurrentPrinter");
    wTitle = 'VRPrinter Demo v' || version '-' pName
    call VRSet Window1, 'Caption', wTitle

return

/*:VRX         Init
*/
Init:

    window = VRWindow()
    call VRMethod window, "CenterWindow"

    loading = 1;

    call VRRedirectStdIO 'Off'

    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"

    /***** Set the title of the window **********************************/
    
    pName = VRGet( "PRT_1", "CurrentPrinter");
    version = VRGet( "PRT_1", "Version");
    wTitle = 'VRPrinter Demo v' || version '-' pName
    call VRSet window, 'Caption', wTitle
    
    /***** Get the path to the OS/2 logo ********************************/
    
    set_path = VALUE( 'VXREXX', , 'OS2ENVIRONMENT');
    bmp_name = set_path || '\addlogo.bmp'
    jpeg_name = set_path || '\testorig.jpg'

    call VRSet "NB_1", "Painting", 0;

    drop window ver set_path bootdrive

return

/*:VRX         Page_dlg_Close
*/
Page_dlg_Close: 
    call Page_dlg_Fini
return

/*:VRX         Page_dlg_Create
*/
Page_dlg_Create: 
    call Page_dlg_Init
return

/*:VRX         Page_dlg_Fini
*/
Page_dlg_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         Page_dlg_Init
*/
Page_dlg_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         Page_dlg_Resize
*/
Page_dlg_Resize: 
    call resize_dlg Page_dlg, GB_7
return

/*:VRX         PB_1_Click
*/
PB_1_Click: 
    
    /***** Get Page settings ********************************************/
    
    border = VRGet( CB_1, 'Set');
    if border then do
        thick = VRGet( SPIN_1, 'Value');
        style = VRGet( SPIN_4, 'Value');
    end
    else do
        thick = 0;
        style = 0;
    end
    bcolor = VRGet( "DDCB_bcolor", "Value");
    fcolor = VRGet( "DDCB_fcolor", "Value");
    tcolor = VRGet( "DDCB_color", "Value");

    call VRSet "PRT_1", "PrintColor", tcolor

    /***** Get header settings ******************************************/
    
    header = VRGet( CB_2, 'Set');
    allpages = VRGet( CB_4, 'Set');
    if header then do
        hthick = VRGet( SPIN_2, 'Value');
        hstyle = VRGet( SPIN_3, 'Value');
    end
    else do
        hthick = 0;
        hstyle = 0;
    end
    hlcolor = VRGet( "DDCB_hlcolor", "Value");
    hfcolor = VRGet( "DDCB_hfcolor", "Value");
    htcolor = VRGet( "DDCB_htcolor", "Value");

    htext1 = VRGet( "EF_3", "value");
    htext2 = VRGet( "EF_4", "value");
    htext3 = VRGet( "EF_5", "value");
    htext4 = VRGet( "EF_6", "value");
    hlines = 4;
    if htext4 = '' then do
        hlines = 3;
        if htext3 = '' then do
            hlines = 2
            if htext2 = '' then do
                hlines = 1
                if htext1 = '' then do
                    hlines = 0
                    header = 0
                end
            end
        end
    end

    /***** Get footer settings ******************************************/
    
    footer = VRGet( CB_3, 'Set');
    if footer then do
        fthick = VRGet( SPIN_6, 'Value');
        fstyle = VRGet( SPIN_5, 'Value');
    end
    else do
        fthick = 0;
        fstyle = 0;
    end
    flcolor = VRGet( "DDCB_flcolor", "Value");
    ffcolor = VRGet( "DDCB_ffcolor", "Value");
    ftcolor = VRGet( "DDCB_ftcolor", "Value");

    ftext = VRGet( "EF_8", "value");
    if ftext = '' then
        ftext = '$Ý$rpage $#'

    /***** Get table settings ******************************************/
    
    tthick = VRGet( SPIN_15, 'Value');
    tstyle = VRGet( SPIN_14, 'Value');
    tlcolor = VRGet( "DDCB_tlcolor", "Value");
    tfcolor = VRGet( "DDCB_tfcolor", "Value");
    ttcolor = VRGet( "DDCB_ttcolor", "Value");

    ththick = VRGet( SPIN_13, 'Value');
    thstyle = VRGet( SPIN_12, 'Value');
    thlcolor = VRGet( "DDCB_thlcolor", "Value");
    thfcolor = VRGet( "DDCB_thfcolor", "Value");
    thtcolor = VRGet( "DDCB_thtcolor", "Value");

    /***** Get margins for page *****************************************/
    
    lm = VRGet( SPIN_10, 'Value');
    rm = VRGet( SPIN_9, 'Value');
    tm = VRGet( SPIN_8, 'Value');
    bm = VRGet( SPIN_7, 'Value');
    ils = VRGet( SPIN_11, 'Value');

    /***** Find what we want to print ***********************************/
    
    if VRGet( RB_1, 'Set') then do
        pstyle = 1
        text_style = 'L'
    end
    if VRGet( RB_2, 'Set') then do
        pstyle = 2
        text_style = 'R'
    end
    if VRGet( RB_3, 'Set') then do
        pstyle = 3
        text_style = 'C'
    end
    if VRGet( RB_4, 'Set') then do
        pstyle = 4
        text_style = 'J'
    end
    if VRGet( RB_5, 'Set') then
        pstyle = 5
    if VRGet( RB_6, 'Set') then
        pstyle = 6
    if VRGet( RB_7, 'Set') then
        pstyle = 7
    if VRGet( RB_8, 'Set') then
        pstyle = 8
    if VRGet( RB_9, 'Set') then do
        pstyle = 9
        text_file_name = VRGet( "EF_2", "Value");
        if text_file_name = '' then do
            call beep 1000, 1000
            return
        end
    end
    if VRGet( RB_10, 'Set') then
        pstyle = 10
    
    /***** get the font face name ***************************************/
    
    facename = VRGet( EF_1, 'Value');
    if facename = '' then do
        call beep 1000, 1000
        return
    end

    p = pos( '.', facename) + 1;
    facename = substr( facename, p);

    call VRSet Window1, 'pointer', 'wait'
    
    /***** Set the margins **********************************************/
    
    rcy = VRMethod( "PRT_1", "SetMargins", lm, rm, tm, bm, thick, style, bcolor, fcolor);
    
    /***** Set the header mode ******************************************/
    
    rcy = VRMethod( "PRT_1", "SetHeaderMode", header, facename, 10, hstyle, hthick, allpages, hlcolor, hfcolor, htcolor, 12);
    
    /***** Set the header ***********************************************/
    
    rcy = VRMethod( "PRT_1", "SetHeader", hlines, htext1, htext2, htext3, htext4);
    
    if hlines > 0 then
        rcy = VRMethod( "PRT_1", "SetHeaderLineFont", 1,,14);
 
    /***** Set the footer if any ****************************************/
    
    if footer then do
        rcy = VRMethod( "PRT_1", "SetFooter", facename, 8, fstyle, fthick, ftext, flcolor, ffcolor, ftcolor, 4);
    end
    
    /***** Open the print job *******************************************/
    
    rcy = VRMethod( "PRT_1", "OpenPrintJob", 'Test Printing');

    /***** Check that everything was ok *********************************/
    
    if \rcy then do
        call VRSet Window1, 'pointer', '<default>'
        return
    end

    call PrintItAll

    call VRSet Window1, 'pointer', '<default>'

return

/*:VRX         PB_2_Click
*/
PB_2_Click: 
    call Quit
return

/*:VRX         PB_3_Click
*/
PB_3_Click: 
    
    /***** Get the font for printing ************************************/

    face = VRGet( EF_1, 'Value')
    p = pos( '.', face)
    if p > 0 then
        face = word( substr( face, p + 1), 1);
    else
        face = ''
    font = VRMethod( "PRT_1", "FontDialog", 'Choose Font for Printing', face);
    if font <> '' then
        call VRSet EF_1, 'Value', font

    drop font face
return

/*:VRX         PB_4_Click
*/
PB_4_Click: 
    
    /***** Get/Set the job properties for selected printer **************/
    
    rcy = VRMethod( "PRT_1", "JobProperties");
return

/*:VRX         PB_5_Click
*/
PB_5_Click: 
    call idm_prt_setup_Click
return

/*:VRX         PB_7_Click
*/
PB_7_Click: 
    
    FileName = VRFileDialog( VRWindow(), "Pick text file to print", "Open", "*.*", , ,  )
    
    if FileName <> '' then
        call VRSet EF_2, 'Value', FileName

    drop FileName
return

/*:VRX         Print_dlg_Close
*/
Print_dlg_Close: 
    call Print_dlg_Fini
return

/*:VRX         Print_dlg_Create
*/
Print_dlg_Create: 
    call Print_dlg_Init
return

/*:VRX         Print_dlg_Fini
*/
Print_dlg_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         Print_dlg_Init
*/
Print_dlg_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         Print_dlg_Resize
*/
Print_dlg_Resize: 
    call resize_dlg Print_dlg, GB_6
return

/*:VRX         PrintItAll
*/
PrintItAll: 
    /***** Set the line spacing for printing ****************************/
    
    rcy = VRSet( "PRT_1", "LineSpace", ils);

    rcy = VRMethod( "PRT_1", "ResetHeader", 2,,);

    /***** Set the texts for printing ***********************************/
    
    txt1 = 'Hello everyone, this is some text in'
    txt2 = 'point which wraps over several lines.'
    txt3 = 'This is so that you can see how the VRPrinter methods work.'
    txt4 = 'We hope that you will find them useful.'
    
    select
        
        /***** If left justified text demo ******************************/
        
        when pstyle = 1 then do
            fnt = 8
            rcy = VRMethod( "PRT_1", "PrintLine", facename, fnt, txt1 facename fnt txt2 txt3 txt4);
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            do fnt = 10 to 24 by 2
                rcy = VRMethod( "PRT_1", "PrintLine", , fnt, txt1 facename fnt txt2 txt3 txt4);
                rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            end
        end
        
        /***** If right justified text demo *****************************/
        
        when pstyle = 2 then do
            fnt = 8
            rcy = VRMethod( "PRT_1", "PrintRight", facename, fnt, txt1 facename fnt txt2 txt3 txt4);
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            do fnt = 10 to 24 by 2
                rcy = VRMethod( "PRT_1", "PrintRight", , fnt, txt1 facename fnt txt2 txt3 txt4);
                rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            end
        end
        
        /***** If centred text demo *************************************/
        
        when pstyle = 3 then do
            fnt = 8
            rcy = VRMethod( "PRT_1", "PrintCentered", facename, fnt, txt1 facename fnt txt2 txt3 txt4);
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            do fnt = 10 to 24 by 2
                rcy = VRMethod( "PRT_1", "PrintCentered", , fnt, txt1 facename fnt txt2 txt3 txt4);
                rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            end
        end
        
        /***** If justified text demo ***********************************/
        
        when pstyle = 4 then do
            fnt = 8
            rcy = VRMethod( "PRT_1", "PrintJustified", facename, fnt, txt1 facename fnt txt2 txt3 txt4);
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            do fnt = 10 to 24 by 2
                rcy = VRMethod( "PRT_1", "PrintJustified", , fnt, txt1 facename fnt txt2 txt3 txt4);
                rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
            end
        end
        
        /***** If print bitmap demo *************************************/
        
        when pstyle = 5 then do
            rcy = VRMethod( "PRT_1", "PrintLine", facename, 14, 'Here are some bitmaps');
            rcy = VRMethod( "PRT_1", "PrintBitMap", "$101", 20, 120, 120, 220, 28, ,'Fig 1. - A bitmap from exe resource');
            rcy = VRMethod( "PRT_1", "PrintBitMap", bmp_name, 30, 20, 110, 95, 56, ,'Fig 2. - A bitmap from a file');

            rcy = VRMethod( "PRT_1", "NewPage");

            rcy = VRMethod( "PRT_1", "PrintLine", facename, 14, 'Here is a bitmap and a JPEG (if you have djpeg.exe)');
            hmod = VRMethod( "PRT_1", "LoadResMod", "RESOURCE");
            rcy = VRMethod( "PRT_1", "PrintBitMap", hmod || "$100", 20, 120, 120, 220, 28, ,'Fig 3. - A bitmap from a DLL');
            rcy = VRMethod( "PRT_1", "PrintJPEG", jpeg_name, 30, 20, 110, 95, 56, ,'Fig 4. - A JPEG image');

            rcy = VRMethod( "PRT_1", "NewPage");
            rcy = VRMethod( "PRT_1", "PrintCentered", facename, 10, 'This one has no title and no declared dimensions');
            rcy = VRMethod( "PRT_1", "Goto", 50, 100);
            rcy = VRMethod( "PRT_1", "PrintBitMap", bmp_name,,,,, 14);
            call VRMethod "PRT_1", "FreeResMod", hmod

        end
        
        /***** If print table demo **************************************/
        
        when pstyle = 6 then do
            rcy = VRMethod( "PRT_1", "PrintLine", facename, 12, 'Example of printing a table with different styles in each cell');
            rcy = VRMethod( "PRT_1", "PrintLine",,,'');
            rcy = VRMethod( "PRT_1", "PrintLine",,,'Table created with StartTable');
            call WriteTable

            rcy = VRMethod( "PRT_1", "PrintLine",facename, 12,'');
            rcy = VRMethod( "PRT_1", "PrintLine", facename, 12, 'Table created with DefineTable & NewPage between rows');
            rcy = VRMethod( "PRT_1", "PrintLine",facename, 12,'');
            call WriteTable3

            rcy = VRMethod( "PRT_1", "PrintLine",facename, 12,'');
            rcy = VRMethod( "PRT_1", "PrintLine", facename, 12, 'Table created with DefineTable and with bitmaps');
            rcy = VRMethod( "PRT_1", "PrintLine",facename, 12,'');
            call WriteTable2

        end
        
        /***** If styles demo *******************************************/
        
        when pstyle = 7 then do
            call PrintStyles
        end
        
        /***** If tabbing and goto demo *********************************/
        
        when pstyle = 8 then do
            call PrintTabbedText
        end

        when pstyle = 9 then do
            rcy = VRMethod( "PRT_1", "PrintFile", "Courier", 8, text_style, text_file_name);
        end

        when pstyle = 10 then do
            rcy = VRMethod( "PRT_1", "PrintObjectImage", "Window1", 20, 20, , , 0, ,'Fig 1. - Demo Window');
            rcy = VRMethod( "PRT_1", "NewPage");
 
            ok = VRMethod( "Screen", "ListWindows", "window.")
            if ok = 1 then do
                found = 0
                do while( found = 0)
                    idx = random( 1, window.0)
                    w = word( window.idx, 1 )
                    if VRGet( w, "Visible" ) = 1 then do
                        rcy = VRMethod( w, "Activate");
                        if VRGet( w, "WindowState") <> Minimized then do
                            title_text = VRGet( w, "Caption" )
                            rcy = VRMethod( "PRT_1", "PrintLine",facename, 12,'Print image of' title_text);
                            rcy = VRMethod( "PRT_1", "PrintWinImage", w, 20, 20, , , 0, ,'Figure -' title_text);
                            found = 1;
                            rcy = VRMethod( "window1", "Activate");
                        end
                    end
                end
            end
            
        end

    end
    
    /***** Close the print job ******************************************/
    
    rcy = VRMethod( "PRT_1", "ClosePrintJob");

return

/*:VRX         PrintStyles
*/
PrintStyles: 
    
    wide = VRGet( "PRT_1", "PageWidth");
    high = VRGet( "PRT_1", "PageHeight");

    /***** Calculate positions for printing *****************************/
    
    vpos1 = trunc( high / 3) * 2;
    vpos2 = trunc( high / 3);
    vinc = trunc( vpos2/ 3);

    by1 = vpos1 
    ty1 = vpos1 + vinc
    by2 = vpos2
    ty2 = vpos2 + vinc

    hpos = trunc( wide / 8);
    hinc = trunc( hpos / 3) * 2;

    bx = 5;
    tx = bx + hinc;
    
    /***** Say what we are printing *************************************/
/*    
    rcy = VRMethod( "PRT_1", "PrintLine", facename, 10, 'Defined styles for filling');
*/  
    /***** print a row of boxes with different styles *******************/
    
    do style = 0 to 7
        rcy = VRMethod( "PRT_1", "PrintBox", bx, by1, tx, ty1, 28, style, "Red", "Blue");
        rcy = VRMethod( "PRT_1", "Goto", bx, by1 - 10);
        rcy = VRMethod( "PRT_1", "PrintLeft", facename, 10, 'Style' style);
        bx = bx + hpos;
        tx = tx + hpos;
    end

    bx = 5;
    tx = bx + hinc;
    
    /***** print a row of boxes with different styles *******************/
    
    do style = 8 to 15
        rcy = VRMethod( "PRT_1", "PrintBox", bx, by2, tx, ty2, 28, style, "Pink", "Green");
        rcy = VRMethod( "PRT_1", "Goto", bx, by2 - 10);
        rcy = VRMethod( "PRT_1", "Printleft", facename, 10, 'Style' style);
        bx = bx + hpos;
        tx = tx + hpos;
    end

return

/*:VRX         PrintTabbedText
*/
PrintTabbedText: 
    
    /***** Get the page size ********************************************/
    
    wide = VRGet( "PRT_1", "PageWidth");
    high = VRGet( "PRT_1", "PageHeight");
    
    /***** Calculate the number of tabs *********************************/
    
    numtabs = trunc( wide / 10) - 1;
    
    /***** Print '|' at each tab position *******************************/
    
    rcy = VRMethod( "PRT_1", "PrintLine", facename, 10, 'Tab positions are shown on the next line');
    rcy = VRMethod( "PRT_1", "PrintLine", , , '');
    rcy = VRMethod( "PRT_1", "PrintLeft", , , '|');

    do i = 1 to numtabs
        rcy = VRMethod( "PRT_1", "Tab");
        rcy = VRMethod( "PRT_1", "PrintLeft", , , '|');
    end

    /***** show some moves **********************************************/

    rcy = VRMethod( "PRT_1", "PrintLine", , , '');
    rcy = VRMethod( "PRT_1", "PrintLine", , , '');

    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 10,'Here we are');
    rcy = VRMethod( "PRT_1", "MoveX", 10, 0);
    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 10,'1 cm right');

    rcy = VRMethod( "PRT_1", "MoveY", -10, 0);
    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 10,'1 cm down, superscript 2');
    rcy = VRMethod( "PRT_1", "MoveY", 5, 1);
    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 8,'5');
    rcy = VRMethod( "PRT_1", "MoveY", -5, 1);
    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 10,' and subscript O');
    rcy = VRMethod( "PRT_1", "MoveY", -5, 1);
    rcy = VRMethod( "PRT_1", "PrintLeft", Helvetica, 8,'2');

    rcy = VRMethod( "PRT_1", "PrintLine", Helvetica, 10,'');

    rcy = VRMethod( "PRT_1", "PrintLine", , 10, 'Draw some lines');

    lx = 10
    ly = 20
    tx = 150
    ty = 200

    do i = 0 to 9
        rcy = VRMethod( "PRT_1", "DrawLine", lx, ly, tx, ty, 1, ,i);
        ty = ty - 15
    end

    rcy = VRMethod( "PRT_1", "Goto", 10, 10);
    rcy = VRMethod( "PRT_1", "PrintLine", , 20, 'The End');
    rcy = VRMethod( "PRT_1", "NewPage")

    rcy = VRMethod( "PRT_1", "PrintBullet", 0, 5, "Helvetica Bold", 12, "",,
                    "Helvetica", 10, 'L', txt1)
    rcy = VRMethod( "PRT_1", "PrintBullet", 0, 5, "Helvetica Bold", 12, "",,
                    "Helvetica", 10, 'R', txt2)
    rcy = VRMethod( "PRT_1", "PrintBullet", 0, 5, "Helvetica Bold", 12, "",,
                    "Helvetica", 10, 'L', txt3)
    rcy = VRMethod( "PRT_1", "PrintBullet", 0, 5, "Helvetica Bold", 12, "",,
                    "Helvetica", 10, 'L', txt4)

return

/*:VRX         Quit
*/
Quit:
    window = VRWindow()
    call VRSet window, "Shutdown", 1
    drop window
return

/*:VRX         resize_dlg
*/
resize_dlg:  procedure

    dlg = arg(1)
    gbox = arg(2)

    h1 = VRGet( dlg, 'InteriorHeight');
    h2 = VRGet( gbox, 'Height');
    w1 = VRGet( dlg, 'Width');
    w2 = VRGet( gbox, 'Width');
    if w1 < w2 then
        l = 0
    else
        l = trunc(( w1 - w2) / 2)

    if h1 < h2 then
        t = 0
    else
        t = trunc(( h1 - h2) / 2)

    call VRSet gbox, 'Left', l
    call VRSet gbox, 'Top', t

return

/*:VRX         table_dlg_Close
*/
table_dlg_Close: 
    call table_dlg_Fini
return

/*:VRX         table_dlg_Create
*/
table_dlg_Create: 
    call table_dlg_Init
return

/*:VRX         table_dlg_Fini
*/
table_dlg_Fini: 
    window = VRInfo( "Window" )
    call VRDestroy window
    drop window
return
/*:VRX         table_dlg_Init
*/
table_dlg_Init: 
    window = VRInfo( "Object" )
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
    drop window
return

/*:VRX         table_dlg_Resize
*/
table_dlg_Resize: 
    call resize_dlg table_dlg, GB_13
return

/*:VRX         tolower
*/
tolower: procedure

parse arg str

tin = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
tout = 'abcdefghijklmnopqrstuvwxyz'

retstr = translate( str, tout, tin);

return retstr

/*:VRX         Window1_Close
*/
Window1_Close:
    call Quit
return

/*:VRX         WriteTable
*/
WriteTable: 
    
    /***** Initialise a table *******************************************/
    
    rcy = VRMethod( "PRT_1", "StartTable", tstyle, tthick, 3, 10, 45, 50, 40);

    if rcy then do
        
        /***** Start printing a row *************************************/
        
        rcy = VRMethod( "PRT_1", "StartRow");

        /***** write to col 1 *******************************************/
        

        rcy = VRMethod( "PRT_1", "StartCol", 1);
        rcy = VRMethod( "PRT_1", "PrintRight", 'Helvetica', 10, 'This is some text in the first column. It is not very long,');
        
        /***** write to col 2 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 2);
        rcy = VRMethod( "PRT_1", "PrintJustified", 'Helvetica Bold', 10, 'This is some text in the second column. It is not very long,');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'This text has several lines and with a bit of luck should force a new page.');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'If it does then we have a test of a cell rolling over from one page to the next and we will not have to write any more.');
        
        /***** write to col 3 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 3);
        rcy = VRMethod( "PRT_1", "PrintCentered", 'Helvetica Bold', 14, 'This is some text in the third column. It is not very long,');
        
        /***** print out the row ****************************************/
        
        rcy = VRMethod( "PRT_1", "EndRow");
        
        /***** start the next row ***************************************/
        
        rcy = VRMethod( "PRT_1", "StartRow");
        
        /***** write to col 1 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 1);
        rcy = VRMethod( "PRT_1", "PrintRight", 'Times New Roman', 10, 'This is some text in the first column. It is not very long,');
        
        /***** write to col 2 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 2);
        rcy = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 10, 'This is some text in the second column. It is not very long and should be left justified.');
        rcy = VRMethod( "PRT_1", "PrintCentered",,,'This text has several lines and with a bit of luck should be centred.');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'This text here was designed to be justified and should roll over several lines, of course the last line will be left aligned.');
        rcy = VRMethod( "PRT_1", "PrintRight",,,'This last bit of text should finally show all the styles in one cell as it is right aligned.');
        
        /***** write to col 3 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 3);
        rcy = VRMethod( "PRT_1", "PrintJustified", 'Times New Roman', 8, 'This is some text in the third column. It is not very long,');
        
        /***** print out the row ****************************************/
        
        rcy = VRMethod( "PRT_1", "EndRow");
        
        /***** Terminate the table **************************************/
        
        rcy = VRMethod( "PRT_1", "EndTable");

    end
    else
        rcy = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 14, 'ERROR - Failed to create the table...');

return

/*:VRX         WriteTable2
*/
WriteTable2: 


/***** Define the table ********************************/

table.0 = 11
table.1 = tstyle
table.2 = tthick
table.3 = 1
table.4 = thstyle
table.5 = ththick
table.6 = 1
table.7 = 12
table.8 = 'Helvetica Bold'
table.9 = 10
table.10 = 15
table.11 = 15

/***** Make 3 columns ***********************************/

Cols.0.0 = 3

Cols.1.1 = 25
Cols.1.2 = 'Index'

Cols.2.1 = 50
Cols.2.2 = '$cImage'

Cols.3.1 = 70
Cols.3.2 = '$rRes Number'

names.0 = 18
names.1 = 'BLUJEAN.BMP'
names.2 = 'BOX.BMP'
names.3 = 'BRICK.BMP'
names.4 = 'BUTTERFL.BMP'
names.5 = 'COLUMNS.BMP'
names.6 = 'DELFT.BMP'
names.7 = 'FERNS.BMP'
names.8 = 'FLAMINGO.BMP'
names.9 = 'FLEUR.BMP'
names.10 = 'LEAVES.BMP'
names.11 = 'MAZE.BMP'
names.12 = 'ORCHIDS.BMP'
names.13 = 'OS2TILE.BMP'
names.14 = 'SHELLS.BMP'
names.15 = 'SUNFLOW.BMP'
names.16 = 'SWIRLS.BMP'
names.17 = 'TIEDYE.BMP'
names.18 = 'ZIGZAG.BMP'

rcy = VRMethod( "PRT_1", "DefineTable", "table.", "Cols.");

/**** Start printing in the table **********************************/

if rcy then do
    hmod = VRMethod( "PRT_1", "LoadResMod", "RESOURCE");
    do i = 1 to 18
        rcy = VRMethod( "PRT_1", "StartRow");
        rcy = VRMethod( "PRT_1", "StartCol", 1)
        rcy = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 10, i);
        rcy = VRMethod( "PRT_1", "StartCol", 2)
        resnum = 100 + i;
        rcy = VRMethod( "PRT_1", "PrintBitMap", hmod || '$' || resnum,,,,,,,names.i);
        rcy = VRMethod( "PRT_1", "StartCol", 3)
        rcy = VRMethod( "PRT_1", "PrintRight", 'Helvetica Bold', 10, resnum);
        rcy = VRMethod( "PRT_1", "EndRow");
    end
    rcy = VRMethod( "PRT_1", "EndTable");
    call VRMethod "PRT_1", "FreeResMod", hmod
end    
else
    rcy = VRMethod( "PRT_1", "PrintLine", 'Helvetica Bold', 14, 'ERROR - Failed to create the table...');

return

/*:VRX         WriteTable3
*/
WriteTable3: 

    /***** Define the table ********************************/

    table.0 = 17
    table.1 = tstyle
    table.2 = tthick
    table.3 = 1
    table.4 = thstyle
    table.5 = ththick
    table.6 = 1
    table.7 = 12
    table.8 = 'Helvetica Bold'
    table.9 = 10
    table.10 = 26
    table.11 = 24
    table.12 = ttcolor
    table.13 = tlcolor
    table.14 = tfcolor
    table.15 = thtcolor
    table.16 = thlcolor
    table.17 = thfcolor

    /***** Make 3 columns ***********************************/

    Cols.0.0 = 3

    Cols.1.1 = 45
    Cols.1.2 = 'Column 1'

    Cols.2.1 = 50
    Cols.2.2 = '$cColumn 2'

    Cols.3.1 = 40
    Cols.3.2 = '$rColumn 3'

    rcy = VRMethod( "PRT_1", "DefineTable", "table.", "Cols.");

    if rcy then do

        /***** Change column headers for following pages ****************/
        
        call VRMethod "PRT_1", "ResetColHeader", 1, "New header 1"
        call VRMethod "PRT_1", "ResetColHeader", 2, "$rNew header 2"
        call VRMethod "PRT_1", "ResetColHeader", 3, "$cNew header 3"

        /***** Start printing a row *************************************/
        
        rcy = VRMethod( "PRT_1", "StartRow");

        /***** write to col 1 *******************************************/
        

        rcy = VRMethod( "PRT_1", "StartCol", 1);
        rcy = VRMethod( "PRT_1", "PrintRight", 'Helvetica', 10, 'This is some text in the first column. It is not very long,');
        
        /***** write to col 2 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 2);
        rcy = VRMethod( "PRT_1", "PrintJustified", 'Helvetica Bold', 10, 'This is some text in the second column. It is not very long,');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'This text has several lines and with a bit of luck should force a new page.');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'If it does then we have a test of a cell rolling over from one page to the next and we will not have to write any more.');
        
        /***** write to col 3 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 3);
        rcy = VRMethod( "PRT_1", "PrintCentered", 'Helvetica Bold', 14, 'This is some text in the third column. It is not very long,');
        
        /***** print out the row ****************************************/
        
        rcy = VRMethod( "PRT_1", "EndRow");
        rcy = VRMethod( "PRT_1", "NewPage");
        
        /***** start the next row ***************************************/
        
        rcy = VRMethod( "PRT_1", "StartRow");
        
        /***** write to col 1 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 1);
        rcy = VRMethod( "PRT_1", "PrintRight", 'Times New Roman', 10, 'This is some text in the first column. It is not very long,');
        
        /***** write to col 2 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 2);
        rcy = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 10, 'This is some text in the second column. It is not very long and should be left justified.');
        rcy = VRMethod( "PRT_1", "PrintCentered",,,'This text has several lines and with a bit of luck should be centred.');
        rcy = VRMethod( "PRT_1", "PrintJustified",,,'This text here was designed to be justified and should roll over several lines, of course the last line will be left aligned.');
        rcy = VRMethod( "PRT_1", "PrintRight",,,'This last bit of text should finally show all the styles in one cell as it is right aligned.');
        
        /***** write to col 3 *******************************************/
        
        rcy = VRMethod( "PRT_1", "StartCol", 3);
        rcy = VRMethod( "PRT_1", "PrintJustified", 'Times New Roman', 8, 'This is some text in the third column. It is not very long,');
        
        /***** print out the row ****************************************/
        
        rcy = VRMethod( "PRT_1", "EndRow");
        
        /***** Terminate the table **************************************/
        
        rcy = VRMethod( "PRT_1", "EndTable");

    end
    else
        rcy = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 14, 'ERROR - Failed to create the table...');

return

