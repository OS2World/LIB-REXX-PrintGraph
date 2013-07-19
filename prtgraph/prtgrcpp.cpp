// ***********************************************************************
//
// $Author$
// $Workfile$
// $Revision$
// $Date$
//
// $Log$
//
// ***********************************************************************


#define     INCL_DOS
#define     INCL_BASE
#define     INCL_ERRORS
#define     INCL_WIN
#define     INCL_DEV
#define     INCL_SPL
#define     INCL_SPLDOSPRINT
#define     INCL_BASE
#define     INCL_GPILCIDS
#define     INCL_GPITRANSFORMS
#define     INCL_GPIPATHS
#define     INCL_GPICONTROL
#define     INCL_GPIPRIMITIVES
#define     INCL_GPIERRORS
#define     INCL_GPIBITMAPS

#include    <xpf.h>
#include    <bseerr.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdio.h>
#include    <ctype.h>
#include    <tstngen.h>
#include    "prt_dlg.h"
#include    "prt_int.h"
#include    "prtgrcpp.hpp"

#ifdef DEMO
    char    demo_str[ 256];
    char*     d_str = "This is an unregistered version of\n"
                    "PRTGRCPP.DLL v %s\n\n"
                    "This product is shareware and can be "
                    "registered through CompuServe or by "
                    "contacting the address in the online "
                    "programming help\n\n"
                    "¸1995 ADD Consulting (CH)";
#endif

extern PRT_LIST     pPrtList;       // List of printer data


// ***********************************************************************

Printer::Printer( PFNNP     pnpf)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

#ifdef DEMO
    sprintf( demo_str, d_str, VER_NUM);
    WinMessageBox( HWND_DESKTOP,
                   HWND_DESKTOP,
                   demo_str,
                   "PRTGRCPP - Unregistered Version",
                   0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
#endif

    pjob = PrtObjectInit( );
    if( pjob)
        pjob->pt_np_func = pnpf;
    hp = ( LHANDLE) pjob;

    } // end of Printer()

// ***********************************************************************

Printer::Printer( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

#ifdef DEMO
    sprintf( demo_str, d_str, VER_NUM);
    WinMessageBox( HWND_DESKTOP,
                   HWND_DESKTOP,
                   demo_str,
                   "PRTGRCPP - Unregistered Version",
                   0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
#endif

    pjob = PrtObjectInit( );
    hp = ( LHANDLE) pjob;

    } // end of Printer()

// ***********************************************************************

Printer::~Printer( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob != 0 )
        PrtObjectDestroy( pjob);

    } // end of ~Printer()

// ***********************************************************************

char *Printer::Get_CurrentPrinter()

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;

    return( pjob->szPrinter);

    } // end of Get_CurrentPrinter

// ***********************************************************************

char *Printer::Get_CurrentDevice()

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;

    return( pjob->DevStruct.pszLogAddress);

    } // end of Get_CurrentDevice

// ***********************************************************************

char *Printer::Get_DefaultPrinter()

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;
    PrtGetPrinterList( );
    return( pPrtList.szPrinterList[ pPrtList.def_prt]);

    } // end of Get_DefaultPrinter

// ***********************************************************************

char *Printer::Get_Units( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;

    return( pjob->pszMeasure);

    } // end of Get_Units

// ***********************************************************************

char *Printer::Get_FormName()

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;

    return( pjob->pszForm);

    } // end of Get_FormName

// ***********************************************************************

char *Printer::Get_Version( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( VER_NUM);
    } // end of Get_Version

// ***********************************************************************

char *Printer::Get_JobName( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return 0;

    return( pjob->pdata->doc_name);

    } // end of Get_JobName

// ***********************************************************************

int Printer::Get_NumPrinters( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( pPrtList.prt_count);
    } // end of Get_NumPrinters

// ***********************************************************************

int Printer::Get_PageNum( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0);

    return( pjob->pdata->pt_page);

    } // end of Get_PageNum

// ***********************************************************************

int Printer::Get_Spacing( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0);

    return( pjob->usline_space);

    } // end of Get_Spacing

// ***********************************************************************

ULONG Printer::Get_BottomMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_bot_margin);

    } // end of Get_BottomMargin

// ***********************************************************************

ULONG Printer::Get_TopMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_top_margin);

    } // end of Get_TopMargin

// ***********************************************************************

ULONG Printer::Get_LeftMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_left_margin);

    } // end of Get_TopMargin

// ***********************************************************************

ULONG Printer::Get_RightMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_right_margin);

    } // end of Get_RightMargin

// ***********************************************************************

ULONG Printer::Get_MinBotMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_min_bmargin);

    } // end of Get_MinBotMargin

// ***********************************************************************

ULONG Printer::Get_MinTopMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_min_tmargin);

    } // end of Get_MinTopMargin

// ***********************************************************************

ULONG Printer::Get_MinLeftMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_min_lmargin);

    } // end of Get_MinLeftMargin

// ***********************************************************************

ULONG Printer::Get_MinRightMargin( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_min_rmargin);

    } // end of Get_MinRightMargin

// ***********************************************************************

ULONG Printer::Get_FormHeight( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( ( ULONG)pjob->pdata->pt_page_size.cy);

    } // end of Get_FormHeight

// ***********************************************************************

ULONG Printer::Get_FormWidth( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( ( ULONG)pjob->pdata->pt_page_size.cx);

    } // end of Get_FormWidth

// ***********************************************************************

ULONG Printer::Get_PageHeight( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_page_size.cy -
            ( ULONG)( pjob->pdata->pt_top_margin + pjob->pdata->pt_bot_margin));

    } // end of Get_PageHeight

// ***********************************************************************

ULONG Printer::Get_PageWidth( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->pdata->pt_page_size.cx -
            ( ULONG)( pjob->pdata->pt_right_margin + pjob->pdata->pt_left_margin));

    } // end of Get_PageWidth

// ***********************************************************************

long Printer::Get_PrintingColor( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( 0L);

    return( pjob->lColor);

    } // end of Get_PrintColor

// ***********************************************************************

Boolean Printer::Get_ColorEnabled( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( FALSE);

    return( pjob->bColor);

    } // end of Get_ColorEnabled

// ***********************************************************************

Boolean Printer::Get_ShowProgress( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( FALSE);

    return( pjob->bProgress);

    } // end of Get_ShowProgress

// ***********************************************************************

Boolean Printer::Get_WordBreak( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( FALSE);

    return( pjob->bWordBreak);

    } // end of Get_WordBreak

// ***********************************************************************

Boolean Printer::Get_Printing( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return( FALSE);

    return( pjob->bPrinting);

    } // end of Get_Printing

// ***********************************************************************

VOID Printer::Set_Units( const char *msr)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    Set_Measures( pjob, msr);

    } // end of Set_Units

// ***********************************************************************

VOID Printer::Set_PrintingColor( long clr)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    Set_PrintColor( pjob, clr);

    } // end of Set_PrintingColor

// ***********************************************************************

VOID Printer::Set_ShowProgress( Boolean flag)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    pjob->bProgress = flag;

    } // end of Set_ShowProgress

// ***********************************************************************

VOID Printer::Set_WordBreak( Boolean flag)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    pjob->bWordBreak = flag;

    } // end of Set_WordBreak

// ***********************************************************************

VOID Printer::Set_ColorEnabled( Boolean flag)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    pjob->bColor = flag;

    } // end of Set_ColorEnabled

// ***********************************************************************

VOID Printer::Set_Spacing( USHORT spc)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;

    if ( pjob == 0 )
        return;

    Set_LineSpace( pjob, spc);

    } // end of Set_Spacing

// ***********************************************************************

int Printer::OpenPrintJob( char*    title, USHORT   pages, USHORT   copies)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGOpenPrintJob( hp, title, pages, copies));
    } // end of OpenPrintJob

// ***********************************************************************

int Printer::ClosePrintJob( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGClosePrintJob( hp));
    } // end of ClosePrintJob

// ***********************************************************************

int Printer::AbortPrintJob( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGAbortPrintJob( hp));
    } // end of AbortPrintJob

// ***********************************************************************

int Printer::SetMargins( ULONG lm,              // Left margin
                         ULONG bm,              // Bottom margin
                         ULONG rm,              // Right margin
                         ULONG tm,              // Top margin
                         ULONG th,              // Border thickness
                         ULONG fill)            // Fill style


// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGSetMargins( hp, lm, bm, rm, tm, th, fill));
    } // end of SetMargins


// ***********************************************************************

int Printer::SetPrintColors( long tcol,         // Text color
                             long bcol,         // Border color
                             long fcol)         // Fill color

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGSetPrintColors( hp, tcol,bcol,fcol));
    } // end of SetPrintColors

// ***********************************************************************

int Printer::SetHeader( PageHeaderDef *phdef)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    LHANDLE     hhdr = phdef->getHandle();
    return( PrtGSetHeader( hp, hhdr));
    } // end of SetHeader

// ***********************************************************************

int Printer::SetFooter( PageFooterDef *pfdef)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    LHANDLE     hftr = pfdef->getHandle();
    return( PrtGSetFooter( hp, hftr));
    } // end of SetFooter

// ***********************************************************************

int Printer::PrintLeft( char*   font,
                        ULONG   points,
                        char*   str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGWrite( hp, font, points, str));
    } // end of PrintLeft

// ***********************************************************************

int Printer::PrintLine( char*   font,
                        ULONG   points,
                        char*   str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGWriteln( hp, font, points, str));
    } // end of PrintLine

// ***********************************************************************

int Printer::PrintRight( char*  font,
                         ULONG  points,
                         char*  str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGJustRight( hp, font, points, str));
    } // end of PrintRight

// ***********************************************************************

int Printer::PrintJustified( char*  font,
                             ULONG  points,
                             char*  str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGJustified( hp, font, points, str));
    } // end of PrintJustified

// ***********************************************************************

int Printer::PrintCentered( char*   font,
                            ULONG   points,
                            char*   str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGCentre( hp, font, points, str));
    } // end of PrintCentered

// ***********************************************************************

Boolean Printer::BlockFits( char*   font,
                            ULONG   points,
                            char*   str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGBlockFits( hp, font, points, str));
    } // end of BlockFits

// ***********************************************************************

Boolean Printer::LineFits( char*    font,
                           ULONG    points,
                           char*    str)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGLineFits( hp, font, points, str));
    } // end of LineFits

// ***********************************************************************

int Printer::PrintFile( char*   szFont,
                        ULONG   points,
                        USHORT  style,
                        char*   szFile)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGPrintFile( hp, szFont, points, style, szFile));
    } // end of PrintFile

// ***********************************************************************

int Printer::PrintBox( ULONG xl,                // Left
                       ULONG yl,                // Bottom
                       ULONG xr,                // Right
                       ULONG yr,                // Top
                       ULONG th,                // Border thickness
                       ULONG fill)              // Fill style

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGBox( hp, xl, yl, xr, yr, th, fill));
    } // end of PrintBox

// ***********************************************************************

int Printer::PrintBox( ULONG xl,                // Left
                       ULONG yl,                // Bottom
                       ULONG xr,                // Right
                       ULONG yr,                // Top
                       ULONG th,                // Border thickness
                       ULONG fill,              // Fill style
                       long bcol,               // Border color
                       long fcol)               // Fill color

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGBoxColor( hp, xl, yl, xr, yr, th, fill, bcol, fcol));
    } // end of PrintBox

// ***********************************************************************

int Printer::PrintBitmap( char* fname,            // file name
                          ULONG xl,             // Left
                          ULONG yl,             // Bottom
                          ULONG xr,             // Right
                          ULONG yr,             // Top
                          ULONG th)             // Border thickness

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGBitMap( hp, fname, xl, yl, xr, yr, th));
    } // end of PrintBitmap

// ***********************************************************************

int Printer::PrintBitmap( char* fname,            // file name
                          ULONG xl,             // Left
                          ULONG yl,             // Bottom
                          ULONG xr,             // Right
                          ULONG yr,             // Top
                          ULONG th,             // Border thickness
                          long bcol)            // Border color

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGBitMapColor( hp, fname, xl, yl, xr, yr, th, bcol));
    } // end of PrintBitmap

// ***********************************************************************

int Printer::StartTable( TableDef *tdef)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    LHANDLE     htbl = tdef->getHandle();
    return( PrtGStartTable( hp, htbl));
    } // end of StartTable

// ***********************************************************************

int Printer::StartRow( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGStartRow( hp));
    } // end of StartRow

// ***********************************************************************

int Printer::StartCol( USHORT col)              // column number

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGStartCol( hp, col));
    } // end of StartCol

// ***********************************************************************

int Printer::EndTable( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGEndTable( hp));
    } // end of EndTable

// ***********************************************************************

int Printer::EndRow( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGEndRow( hp));
    } // end of EndRow

// ***********************************************************************

int Printer::ResetColHeader( USHORT col,        // Column number
                             char*  str)        // New text

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGResetColHeader( hp, col, str));
    } // end of ResetColHeader

// ***********************************************************************

int Printer::Goto( ULONG    x,                  // x coord
                   ULONG    y,                  // y coord
                   Boolean  points)             // measure in points

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGGoto( hp, x, y, points));
    } // end of Goto

// ***********************************************************************

int Printer::NextTab( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGTab( hp));
    } // end of NextTab

// ***********************************************************************

int Printer::NewPage( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGNewPage( hp));
    } // end of NewPage

// ***********************************************************************

VOID Printer::PrinterList( Boolean  refresh,        // TRUE = refresh list
                           char     **pprts)        // array of printers

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    USHORT          i;

    if ( refresh)
        PrtGetPrinterList();

    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    for ( i = 0; i < pPrtList.prt_count; i++)
        strcpy( pprts[ i], pPrtList.szPrinterList[ i]);
    DosReleaseMutexSem( pPrtList.hmtx);

    } // end of PrinterList

// ***********************************************************************

int Printer::SetPrinter( USHORT idx)            // Index in printer list + 1

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGSetPrinter( hp, idx));
    } // end of SetPrinter

// ***********************************************************************

char *Printer::PrinterDialog( HWND  hwnd,       // parent window handle
                              char  *title)     // Title of dialog

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGPrinterDlg( hp, hwnd, title));
    } // end of PrinterDialog

// ***********************************************************************

char *Printer::PrinterDialog( HWND hwnd,        // parent window handle
                              char *title,      // Title of dialog
                              char *ok,         // OK button text
                              char *job,        // Job props button text
                              char *cancel)     // Cancel button text

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    if ( !PrtGSetDlgButtonTexts( hp, ok, job, cancel))
        return( PrtGPrinterDlg( hp, hwnd, title));
    else
        return( 0);
    } // end of PrinterDialog

// ***********************************************************************

char *Printer::FontDialog( char *title,         // Title for dialog
                           char *oface)         // Old face name

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGFontDlg( hp, title, oface));
    } // end of FontDialog

// ***********************************************************************

int Printer::JobProperties( HWND hwnd)          // Parent window

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGJobProps( hp, hwnd));
    } // end of JobProperties

// ***********************************************************************

int Printer::PrintWinImage( HWND  hwnd,         // Window to print
                            ULONG xl,           // Left
                            ULONG yb,           // Bottom
                            ULONG xr,           // Right
                            ULONG yt,           // Top
                            ULONG th,           // Border thickness
                            long  llc)          // Border color

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGPrintWinImage( hp, hwnd, xl, yb, xr, yt, th, llc));
    } // end of PrintWinImage

// ***********************************************************************

int Printer::MoveX( long    delta,              // relative distance
                    Boolean points)             // TRUE = in points

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGMoveX( hp, delta, points));
    } // end of MoveX

// ***********************************************************************

int Printer::MoveY( long    delta,              // relative distance
                    Boolean points)             // TRUE = in points

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGMoveY( hp, delta, points));
    } // end of MoveY

// ***********************************************************************

PageHeaderDef::PageHeaderDef( Boolean   bHeader,
                              Boolean   bAllPages,
                              char*     pszFont,
                              ULONG     ulPts,
                              ULONG     ulFill,
                              ULONG     ulLine,
                              USHORT    usLines)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    hhdr = PrtGDefineHeader( bHeader,
                             bAllPages,
                             pszFont,
                             ulPts,
                             ulFill,
                             ulLine,
                             usLines);
    } // end of PageHeaderDef()

// ***********************************************************************

PageHeaderDef::~PageHeaderDef( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PHDR_DEF_TYPE       phdr;
    USHORT              i;

    phdr = ( PHDR_DEF_TYPE)hhdr;

    if( phdr)
        {
        if( phdr->ppsz)
            {
            for ( i = 0; i < phdr->num_lines; i++)
                FREE( phdr->ppsz[ i].pszLine);
            }
        FREE( phdr->ppsz);
        if( phdr->pszhFont)
            FREE( phdr->pszhFont);
        FREE( phdr);
        }

    } // end of ~PageHeaderDef()

// ***********************************************************************

int PageHeaderDef::DefineColors( long   lctext,
                                 long   lcborder,
                                 long   lcfill)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGDefineHdrColors( hhdr, lctext, lcborder, lcfill));
    } // end of DefineColors()

// ***********************************************************************

int PageHeaderDef::AddHeaderLine( USHORT    usLine,
                                  char      *pszText)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGAddHeaderLine( hhdr, usLine, pszText));
    } // end of AddHeaderLine()

// ***********************************************************************

int PageHeaderDef::SetLineFont( USHORT  usLine,
                                char    *pszFont,
                                ULONG   ulPts)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGSetHdrLineFont( hhdr, usLine, pszFont, ulPts));
    } // end of SetLineFont()

// ***********************************************************************

PageFooterDef::PageFooterDef( Boolean   bFooter,
                              char      *pszFont,
                              ULONG     ulPts,
                              ULONG     ulFill,
                              ULONG     ulLine,
                              char      *pszText)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    hftr = PrtGDefineFooter( bFooter,
                             pszFont,
                             ulPts,
                             ulFill,
                             ulLine,
                             pszText);

    } // end of PageFooterDef()

// ***********************************************************************

PageFooterDef::~PageFooterDef( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PFTR_DEF_TYPE       pftr;

    pftr = ( PFTR_DEF_TYPE)hftr;

    if( pftr)
        {
        if( pftr->pszString)
            FREE( pftr->pszString);
        if( pftr->pszfFont)
            FREE( pftr->pszfFont);
        FREE( pftr);
        }

    } // end of PageFooterDef()

// ***********************************************************************

int PageFooterDef::DefineColors( long   lctext,
                                 long   lcborder,
                                 long   lcfill)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGDefineFtrColors( hftr, lctext, lcborder, lcfill));
    } // end of DefineColors()

// ***********************************************************************

TableDef::TableDef( Boolean boxed,
                    Boolean bHeader,
                    Boolean bAllPages,
                    ULONG   lLine,
                    ULONG   lFill,
                    ULONG   lHline,
                    ULONG   lHfill,
                    char    *pszFont,
                    ULONG   lPts,
                    USHORT  usCols,
                    ULONG   ulLeftEdge)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    htbl = PrtGDefineTable( boxed,
                            bHeader,
                            bAllPages,
                            lLine,
                            lFill,
                            lHline,
                            lHfill,
                            pszFont,
                            lPts,
                            usCols,
                            ulLeftEdge);


    } // end of TableDef()

// ***********************************************************************

TableDef::~TableDef( )

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    PTABLE_DEF_TYPE  pTbl;
    USHORT              i;

    pTbl = ( PTABLE_DEF_TYPE)htbl;
    if( pTbl)
        {
        for ( i = 0; i < pTbl->usCols; i++)
            if( pTbl->aCol[ i].pszText)
                FREE( pTbl->aCol[ i].pszText);

        FREE( pTbl->aCol);
        FREE( pTbl);
        }

    } // end of ~TableDef()

// ***********************************************************************

int TableDef::DefineColors( long    lcct,
                            long    lccl,
                            long    lccf,
                            long    lhct,
                            long    lhcl,
                            long    lhcf)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGDefineTableColors( htbl, lcct, lccl, lccf, lhct, lhcl, lhcf));
    } // end of DefineColors()

// ***********************************************************************

int TableDef::AddColumn( USHORT usCol,
                         ULONG  ulWide,
                         char   *pszHeader)

// ***********************************************************************
//
//
//
// ***********************************************************************

    {
    return( PrtGAddColumn( htbl, usCol, ulWide, pszHeader));
    } // end of PrtGAddColumn()

// ***********************************************************************
//
//                              END OF FILE.
//
// ***********************************************************************


