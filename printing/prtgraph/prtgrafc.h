// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTGRAFC.H  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:09:54  $
//
// $Log:   M:\prtgraph\prtgrafc.h_v  $
// 
//    Rev 1.0   04 May 1996 21:09:54   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#ifndef     PRTGRC_DEFINED
    #define     PRTGRC_DEFINED

#ifdef __cplusplus
    extern "C" {
#endif

// **********************************************************************
// Error return Constants
// **********************************************************************

#define     PRTGR_OK                    0       // Success 
#define     PRTGR_ERR_INV_HANDLE        1       // Invalid handle passed to function 
#define     PRTGR_ERR_NO_PRINTER        2       // No printer has been defined 
#define     PRTGR_ERR_PARAMETER         3       // Parameter was out of range 
#define     PRTGR_ERR_INV_BITMAP        4       // Not a valid bitmap 
#define     PRTGR_ERR_INV_FILENAME      5       // File not found 
#define     PRTGR_ERR_INV_FONT          6       // Failed to load font 
#define     PRTGR_ERR_JOB_OPEN          7       // Failed to open job 
#define     PRTGR_ERR_NOT_TABLE         8       // Col/row func outside of table 
#define     PRTGR_ERR_TABLE_HEADER      9       // Col/row func outside of table 
#define     PRTGR_ERR_NO_JOB            10      // No print job is running 
#define     PRTGR_ERR_PRINTING          11      // A print job is running 
#define     PRTGR_ERR_READONLY          12      // You tried setting a read only property 
#define     PRTGR_ERR_INV_PROP          13      // Invalid property requested 
#define     PRTGR_ERR_INV_VALUE         14      // Property value is invalid 

// **********************************************************************
// Fill Styles
// **********************************************************************

#define     FILL_NONE           ( ULONG)0   // No fill for box 
#define     FILL_FULL           ( ULONG)1   // full fill for box 
#define     FILL_90             ( ULONG)2   // 90% tone fill for box 
#define     FILL_80             ( ULONG)3   // 80% fill for box 
#define     FILL_75             ( ULONG)4   // 75% fill for box 
#define     FILL_70             ( ULONG)5   // 70% fill for box 
#define     FILL_60             ( ULONG)6   // 60% fill for box 
#define     FILL_HALF           ( ULONG)7   // Half tone fill for box 
#define     FILL_LIGHT          ( ULONG)8   // Light tone fill for box 
#define     FILL_VERT           ( ULONG)9   // Vertical line fill for box 
#define     FILL_HORIZ          ( ULONG)10  // Horizontal line fill for box 
#define     FILL_DIAGR45        ( ULONG)11  // 45ø Diagonal left to right line fill for box 
#define     FILL_DIAGR33        ( ULONG)12  // 33ø Diagonal left to right line fill for box 
#define     FILL_DIAGL45        ( ULONG)13  // 45ø Diagonal right to left line fill for box 
#define     FILL_DIAGL33        ( ULONG)14  // 33ø Diagonal right to left line fill for box 

// **********************************************************************
// Line thicknesses
// **********************************************************************

#define     LINE_NONE           ( ULONG)0   // No line for box 
#define     LINE_THIN           ( ULONG)14  // Thin line (0.25mm for box 
#define     LINE_MEDIUM         ( ULONG)28  // meduium line (0.5mm) for box 
#define     LINE_THICK          ( ULONG)56  // Thick line (1mm) for box 

#define     MSR_METRIC          "Metric"
#define     MSR_INCH            "Inch"

// **********************************************************************
// Print styles for Printing files
// **********************************************************************

#define     PRT_CENTER          0
#define     PRT_JUSTIFIED       1
#define     PRT_RIGHT           2
#define     PRT_LEFT            3

// **********************************************************************
// max number of lines in a header
// **********************************************************************

#define     PRTGR_MAX_HLINES    5           // Max lines in page header 

// **********************************************************************
// Handle to a graphic printer
// **********************************************************************

typedef LHANDLE   HGRPRT;

// **********************************************************************
// Handle to header Definition
// **********************************************************************

typedef LHANDLE   HHEADER;

// **********************************************************************
// Handle to footer Definition
// **********************************************************************

typedef LHANDLE   HFOOTER;

// **********************************************************************
// Handle to table Definition
// **********************************************************************

typedef LHANDLE   HTABLE;

// **********************************************************************
// Hook function for new page. A call will be made to this function
// every time a new page is created internally by the library and
// before the page is printed. The format of the function is:
//
// BOOL APIENTRY MyNewPageFunc( HGRPRT    hp,
//                              ULONG     page_num,
//                              BOOL      in_table);
//
// first_page is set to true if this is the first page of the document
//            i.e. during the PrtGOpenPrintJob call
//
// in_table   is set to true if a table is being printed that will
//            continue over to the new page.
// **********************************************************************

typedef VOID (APIENTRY FNNP)(HGRPRT, USHORT, BOOL);
typedef FNNP *PFNNP;

// **********************************************************************
// Type used for setting and getting properties for the printer
// **********************************************************************

typedef union
    {
    BOOL    flag;           // Boolean property 
    ULONG   numeric;        // Numeric properties 
    PSZ     string;         // String properties 
    } PROP_TYPE;

// **********************************************************************
// Properties for the printer
// **********************************************************************

#define     PRT_LEFTMARGIN          0
#define     PRT_RIGHTMARGIN         1
#define     PRT_TOPMARGIN           2
#define     PRT_BOTTOMMARGIN        3
#define     PRT_PAGEWIDTH           4
#define     PRT_PAGEHEIGHT          5
#define     PRT_PRINTING            6
#define     PRT_CURRENTPRINTER      7
#define     PRT_CURRENTDEVICE       8
#define     PRT_DEFAULTPRINTER      9
#define     PRT_LINESPACE           10 
#define     PRT_VERSION             11
#define     PRT_PRINTCOLOR          12
#define     PRT_COLORENABLED        13
#define     PRT_MEASURES            14
#define     PRT_PAGENUM             15
#define     PRT_JOBNAME             16
#define     PRT_MINLEFTMAR          17
#define     PRT_MINRIGHTMAR         18
#define     PRT_MINTOPMAR           19
#define     PRT_MINBOTTOMMAR        20
#define     PRT_FORMNAME            21
#define     PRT_FORMWIDTH           22
#define     PRT_FORMHEIGHT          23
#define     PRT_WORDBREAK           24
#define     PRT_SHOWPROGRESS        25
#define     PRT_PRINTERNUM          26

// **********************************************************************
// Exported function definitions
// **********************************************************************

USHORT  APIENTRY PrtGAbortPrintJob( HGRPRT);
USHORT  APIENTRY PrtGClosePrintJob( HGRPRT);
USHORT  APIENTRY PrtGSetMargins( HGRPRT, ULONG, ULONG, ULONG, ULONG, ULONG, ULONG);
USHORT  APIENTRY PrtGSetFooter( HGRPRT, HFOOTER);
USHORT  APIENTRY PrtGSetHeader( HGRPRT, HHEADER);
USHORT  APIENTRY PrtGOpenPrintJob( HGRPRT, PSZ, USHORT, USHORT);
USHORT  APIENTRY PrtGPrintLine( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGPrintRight( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGPrintJustified( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGPrintCentered( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGPrintLeft( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGGoto( HGRPRT, ULONG, ULONG, BOOL);
USHORT  APIENTRY PrtGPrintBox( HGRPRT, ULONG, ULONG, ULONG, ULONG, ULONG, ULONG, LONG, LONG);
USHORT  APIENTRY PrtGTab(  HGRPRT);
USHORT  APIENTRY PrtGStartTable( HGRPRT, HTABLE);
USHORT  APIENTRY PrtGStartRow( HGRPRT);
USHORT  APIENTRY PrtGStartCol( HGRPRT, USHORT);
USHORT  APIENTRY PrtGEndRow( HGRPRT);
USHORT  APIENTRY PrtGEndTable( HGRPRT);
USHORT  APIENTRY PrtGNewPage( HGRPRT);
VOID    APIENTRY PrtGPrinterList( HGRPRT, BOOL, PSZ*);
PSZ     APIENTRY PrtGPrinterDialog( HGRPRT, HWND, PSZ);
PSZ     APIENTRY PrtGFontDialog( HGRPRT, PSZ, PSZ);
HGRPRT  APIENTRY PrtGInit( HWND, PFNNP);
VOID    APIENTRY PrtGTerm( HGRPRT);
USHORT  APIENTRY PrtGJobProperties( HGRPRT, HWND);
USHORT  APIENTRY PrtGSetPrinter( HGRPRT, USHORT);
USHORT  APIENTRY PrtGPrintBitmap( HGRPRT, PSZ, ULONG, ULONG, ULONG, ULONG, ULONG, LONG);
USHORT  APIENTRY PrtGGetPageSize( HGRPRT, PULONG, PULONG);
PSZ     APIENTRY PrtGCurrentPrinter( HGRPRT);
USHORT  APIENTRY PrtGSetDlgButtonTexts( HGRPRT, PSZ, PSZ, PSZ);

USHORT  APIENTRY PrtGSetPrintColors( HGRPRT, LONG, LONG, LONG);
USHORT  APIENTRY PrtGResetColHeader( HGRPRT, USHORT, PSZ);

BOOL    APIENTRY PrtGBlockFits( HGRPRT, PSZ, ULONG, PSZ);
BOOL    APIENTRY PrtGLineFits( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGPrintFile( HGRPRT, PSZ, ULONG, USHORT, PSZ);
USHORT  APIENTRY PrtGPrintWinImage( HGRPRT, HWND, ULONG, ULONG, ULONG, ULONG, ULONG, LONG);
USHORT  APIENTRY PrtGMoveX( HGRPRT, LONG, BOOL);
USHORT  APIENTRY PrtGMoveY( HGRPRT, LONG, BOOL);

PROP_TYPE APIENTRY PrtGGet( HGRPRT, USHORT, PUSHORT);
USHORT APIENTRY PrtGSet( HGRPRT, USHORT, PROP_TYPE);

// **********************************************************************
// Structure building Functions
// **********************************************************************

HHEADER APIENTRY PrtGDefineHeader( BOOL,            // TRUE=print page headers 
                                   BOOL,            // TRUE= on all pages 
                                   PSZ,             // Font name 
                                   ULONG,           // Font points 
                                   ULONG,           // Box mode 
                                   ULONG,           // Box line 
                                   USHORT);         // Number of lines 

USHORT  APIENTRY PrtGDefineHdrColors( HHEADER,
                                      LONG,         // text colour 
                                      LONG,         // border colour 
                                      LONG);        // fill colour 

USHORT  APIENTRY PrtGAddHeaderLine( HHEADER,        // handle returned by PrtGBuildHeader 
                                    USHORT,         // line index (1 to 5) 
                                    PSZ);           // Text 

USHORT  APIENTRY PrtGSetHdrLineFont( HHEADER,       // handle returned by PrtGBuildHeader 
                                     USHORT,        // line index (1 to 5) 
                                     PSZ,           // font for the line 
                                     ULONG);        // point size for the line 

HFOOTER APIENTRY PrtGDefineFooter( BOOL,            // TRUE=print footers 
                                   PSZ,             // Font for footer 
                                   ULONG,           // Font points 
                                   ULONG,           // box mode 
                                   ULONG,           // box line 
                                   PSZ);            // Text 

USHORT  APIENTRY PrtGDefineFtrColors( HFOOTER,
                                      LONG,         // text colour 
                                      LONG,         // border colour 
                                      LONG);        // fill colour 

HTABLE  APIENTRY PrtGDefineTable( BOOL,             // TRUE=boxed 
                                  BOOL,             // TRUE= header defined 
                                  BOOL,             // TRUE=print header on all pages 
                                  ULONG,            // Cell line thickness 
                                  ULONG,            // Cell fill type 
                                  ULONG,            // Header line thickness 
                                  ULONG,            // Header fill type 
                                  PSZ,              // Header font 
                                  ULONG,            // Header font points 
                                  USHORT,           // Number of columns 
                                  ULONG);           // Left edge of table

USHORT  APIENTRY PrtGDefineTableColors( HTABLE,        // handle to the table definition 
                                        LONG,          // cell text colour 
                                        LONG,          // cell border colour 
                                        LONG,          // cell fill colour 
                                        LONG,          // header text colour 
                                        LONG,          // header border colour 
                                        LONG);         // header fill colour 

USHORT  APIENTRY PrtGAddColumn( HTABLE,             // Handle returned from PrtGDefineTable 
                                USHORT,             // Column number (1 to 12) 
                                ULONG,              // width in in units of measure 
                                PSZ);               // Header text 

HHEADER APIENTRY PrtGDestroyHdrDef( HHEADER);
HFOOTER APIENTRY PrtGDestroyFtrDef( HFOOTER);
HTABLE  APIENTRY PrtGDestroyTblDef( HTABLE);


// *********************************************************************
// Old functions still supported
// *********************************************************************

USHORT  APIENTRY PrtGBox( HGRPRT, ULONG, ULONG, ULONG, ULONG, ULONG, ULONG);
USHORT  APIENTRY PrtGBoxColor( HGRPRT, ULONG, ULONG, ULONG, ULONG, ULONG, ULONG, LONG, LONG);
USHORT  APIENTRY PrtGBitMap( HGRPRT, PSZ, ULONG, ULONG, ULONG, ULONG, ULONG);
USHORT  APIENTRY PrtGBitMapColor( HGRPRT, PSZ, ULONG, ULONG, ULONG, ULONG, ULONG, LONG);
USHORT  APIENTRY PrtGSetLineSpace( HGRPRT, USHORT);
USHORT  APIENTRY PrtGWriteln( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGJustRight( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGJustified( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGCentre( HGRPRT, PSZ, ULONG, PSZ);
USHORT  APIENTRY PrtGWrite( HGRPRT, PSZ, ULONG, PSZ);
PSZ     APIENTRY PrtGPrinterDlg( HGRPRT, HWND, PSZ);
PSZ     APIENTRY PrtGFontDlg( HGRPRT, PSZ, PSZ);
USHORT  APIENTRY PrtGJobProps( HGRPRT, HWND);
PSZ     APIENTRY PrtGVersion( VOID);

#ifdef __cplusplus
    }
#endif

#endif

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
