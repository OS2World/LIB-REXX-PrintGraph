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

#ifndef PRT_INT_H
#define PRT_INT_H


#ifdef __cplusplus
    extern "C" {
#endif

#define     VER_NUM             "2.3"

#ifndef FREE
    #define     FREE( p)        { if( p) { free( p);p = NULL;}}
#endif

#define     FILE_BLK_SIZE_ERR   1000

// **********************************************************************
// Defines for parsing.
// **********************************************************************

#define     FLAG_CHAR               '$'
#define     LEFT_CHAR               'l'
#define     RIGHT_CHAR              'r'
#define     CENTRE_CHAR             'c'
#define     DATE_CHAR               '@'
#define     TIME_CHAR               '?'
#define     DTIME_CHAR              '!'
#define     PAGE_CHAR               '#'
#define     TITLE_CHAR              '|'
#define     TITLE_CHAR_ALT          'Ý'
#define     REP_CHAR                'þ'

// **********************************************************************
// Constants for graphics manipulation
// **********************************************************************

#define     TWIPS_PER_MIL           56.7    // twips per millimetre
#define     TWIPS_PER_TEN           144.0   // twips per tenth of in
#define     ONE_MIL                 57      // 1mm in twips (rounded)
#define     ONE_POINT               20      // 1 pt in twips
#define     TAB_LEN_MM              567     // length of metric tab (1cm)
#define     TAB_LEN_IN              720     // length of INCH tab (1/2")
#define     ONE_TENTH               144     // twips per 1/10th inch
#define     MM_TO_TENTH             2.54    // Conversion mm to 1/10 in

// **********************************************************************
// Defaults and constants
// **********************************************************************

#define     LINE_SPACE              120     // use line spacing of 120%
#define     MAX_FNT                 30      // Max number of fonts
#define     CELL_BLOCK              120     // block of lines for cell
#define     MAX_HEAD                5       // Max num of header lines

#define     DEF_LMAR_MM             25
#define     DEF_RMAR_MM             20
#define     DEF_TMAR_MM             20
#define     DEF_BMAR_MM             25

#define     DEF_LMAR_IN             10
#define     DEF_RMAR_IN             8
#define     DEF_TMAR_IN             8
#define     DEF_BMAR_IN             10

#define     TITLE_LEFT              0
#define     TITLE_RIGHT             1
#define     TITLE_CENTRE            2

#define     JUST_LEFT               0
#define     JUST_RIGHT              1
#define     JUST_CENTRE             2
#define     JUST_JUSTIFY            3

#define     BUF_SIZE                65535   // Size of text buffers

#define     MAX_OPEN_DEVS           20      // Max number of open devices

#define     BOX_LEFT                0x0001
#define     BOX_RIGHT               0x0002
#define     BOX_TOP                 0x0004
#define     BOX_BOT                 0x0008
#define     BOX_NOEDGE              0x0010
#define     BOX_ALL                 BOX_LEFT | BOX_RIGHT | BOX_TOP | BOX_BOT
#define     BOX_TOPBOT              BOX_TOP | BOX_BOT

// **********************************************************************
// BUG fix for Postscript.
// **********************************************************************

#define     PS_MASK                 0xFFFF0000L

// **********************************************************************
// Defines for shared memory
// **********************************************************************

#define     SHR_HEV_NAME            "\\SEM32\\PRTRXDAE\\HEV.SEM"
#define     SHR_HMTX_NAME           "\\SEM32\\PRTRXDAE\\HMTX.SEM"
#define     SHR_MEM_NAME            "\\SHAREMEM\\PRTRXDAE\\SHR.MEM"
#define     DAE_PROG_NAME           "PRTRXDAE.EXE"

// **********************************************************************
// Defines for window messages
// **********************************************************************

#define     WM_JOBDLG               WM_USER + 1
#define     WM_PRTDLG               WM_USER + 2
#define     WM_FONTDLG              WM_USER + 4
#define     WM_PROGRESS             WM_USER + 5
#define     WM_SHAREWARE            WM_USER + 6
#define     WM_UPDATE               WM_USER + 100
#define     WM_STOPME               WM_USER + 101

// **********************************************************************
// Internal structures
// **********************************************************************

typedef struct
    {
    LONG            cb;
    LONG            lVersion;
    CHAR            szDeviceName[32];
    CHAR            abGeneralData[2048];
    } DRVD;

// **********************************************************************
// Shared memory block
// **********************************************************************

typedef struct
    {
    HWND            hwnd;                           // Handle to daemon window
    HWND            hwndProgress;                   // Handle to progress dialog

    HWND            hwndProg;                       // Handle of REXX window
    SHORT           prt_idx;                        // Index of current printer

    char            pszfont[ 128];                  // Name of font returned from font dialog
    char            pszFace[ FACESIZE];             // Name of face returned from font dialog

    char            prt_tit[ 128];                  // Title for printer dialog
    char            szPrtDlgRet[ 128];              // Return from printer dialog
    char            acDlgBut1[ 32];                 // Text for OK button
    char            acDlgBut2[ 32];                 // Text for Job props button
    char            acDlgBut3[ 32];                 // Text for Cancel button

    BOOL            bProgress;                      // display progress dialog during printing
    char            pszPrTitle[ 128];               // progress dialog Title
    char            pszPrString1[ 128];             // progress dialog display string
    char            pszPrString2[ 128];             // progress dialog display string
    char            pszPrString3[ 128];             // progress dialog display string

    char            pszLogAddress[ 128];
    char            pszDriverName[ 128];
    DRVD            drvData;

    } SHR_MEM_BLOCK, *PSHR_MEM_BLOCK;

typedef struct
    {
    USHORT                  idsession;
    USHORT                  ret_code;
    }  ES_TYPE;

// **********************************************************************
// Header line description
// **********************************************************************

typedef struct
    {
    char        cfont[ FACESIZE];
    LONG        lpts;
    PSZ         pszLine;
    } H_LINE, *PH_LINE;

// **********************************************************************
// Definition of colours for REXX/SAA
// **********************************************************************

typedef struct
    {
    char    acClr[16];
    char    acClrN[16];
    LONG    lClr;
    } COLOURS;

#if defined(C_MOD) || defined(CPP_MOD)

// **********************************************************************
// Structure for defining columns
// **********************************************************************

typedef struct
    {
    ULONG           ulLeft;                 // Left edge of column in mm
    ULONG           ulWide;                 // Width of column in mm
    PSZ             pszText;                // Header text
    } COL_DEF_TYPE, *PCOL_DEF_TYPE;

// **********************************************************************
// Structure used to define a table.
// **********************************************************************

typedef struct
    {
    BOOL            bHeader;                // if TRUE header is defined
    BOOL            bAllPages;              // if TRUE repeat table header on all pages
    USHORT          boxtype;                // Type of box around cells
    ULONG           lline_type;             // line thickness (TWIPS) around cells
    ULONG           lfill;                  // fill type for the table
    LONG            llcolor;
    LONG            lfcolor;
    LONG            ltcolor;
    USHORT          hboxtype;               // Type of box around cells
    ULONG           lhline_type;            // line thickness (TWIPS) for table header cells
    ULONG           lhfill;                 // fill type for the table header
    LONG            lhlcolor;
    LONG            lhfcolor;
    LONG            lhtcolor;
    char            cFont[ FACESIZE];       // font for header text
    ULONG           lpts;                   // Point size for header text
    USHORT          usCols;                 // number of colums in the table
    ULONG           ulLeft;                 // left edge of the table
    ULONG           ulCurLeft;              // Current left edge for columns
    USHORT          usLastCol;              // Last column accessed
    PCOL_DEF_TYPE   aCol;                   // array of column definitions
    } TABLE_DEF_TYPE, *PTABLE_DEF_TYPE;

// **********************************************************************
// Structure used to define the page headers.
// **********************************************************************

typedef struct
    {
    BOOL            bHeader;                // TRUE = print headers
    BOOL            bAllpages;              // TRUE = repeat on all pages
    char            pszhFont[ 64];          // Font for text in header
    ULONG           ulpoints;               // Point size for text in header
    ULONG           ulbox_mode;             // Fill style for the page header
    ULONG           ulbox_line;             // line thickness (TWIPS) around page header
    USHORT          boxtype;                // Which edges are to be printed
    USHORT          num_lines;              // Number of text lines in page header
    LONG            lhlcolor;               // Color for the line around the header
    LONG            lhfcolor;               // Color for fill pattern
    LONG            lhtcolor;               // Color for text
    PH_LINE         ppsz;                   // Array of header lines
    } HDR_DEF_TYPE, *PHDR_DEF_TYPE;

// **********************************************************************
// Structure used to define the page footers.
// **********************************************************************

typedef struct
    {
    BOOL            bFooter;                // TRUE = print footers
    char            pszfFont[ 64];          // Font for text in footer
    ULONG           ulpoints;               // point size for text in footer
    ULONG           ulbox_mode;             // fill style for footer
    ULONG           ulbox_line;             // line thickness (TWIPS) around footer
    USHORT          boxtype;                // Which edges are to be printed
    LONG            flcolor;                // Color for the line around the footer
    LONG            ffcolor;                // Color for fill pattern
    LONG            ftcolor;                // Color for text
    PSZ             pszString;              // Text for footer
    } FTR_DEF_TYPE, *PFTR_DEF_TYPE;

#endif

// **********************************************************************
// description of a font used for a print job
// **********************************************************************

typedef struct
    {
    char        sz_name[ FACESIZE];
    LONG        lLcid;
    } FONT_DESC, *PFONT_DESC;

// **********************************************************************
// line for cell with justification props
// **********************************************************************

typedef struct
    {
    USHORT      usJust;
    char        pszLine[ 256];
    } LINE_DESC, *PLINE_DESC;

// **********************************************************************
// description of a column in a table
// **********************************************************************

typedef struct
    {
    HBITMAP             hbm;                // Bitmap in cell
    HDC                 hdc;                // Device context for bitmap
    HPS                 hps;                // Temporary presentation space
    POINTL              aptl[ 4];           // coords of bitmap
    ULONG               cColors;
    PLONG               alColors;           // Color map
    } BMAP, *PBMAP;

typedef struct
    {
    LONG                llm_box;            // left margin of box
    LONG                lrm_box;            // right margin of box
    LONG                llm_text;           // left margin of text
    LONG                lrm_text;           // right margin of text
    PSZ                 pszHeader;          // column header definition
    char                cFont[ FACESIZE];   // font for cell
    LONG                lpts;               // Point size for cell
    USHORT              usblock;            // Number of lines in cell
    USHORT              uslines;            // Number of lines to write
    USHORT              usstart;            // line number to start writing
    USHORT              usnewpage;          // First line for new page
    PBMAP               bitmap;             // Has a bitmap in the cell
    PLINE_DESC          alines;             // array of lines to print in cell
    } COL_TYPE, *PCOL_TYPE;

// **********************************************************************
// description of a table
// **********************************************************************

typedef struct
    {
    BOOL        bHeader;                // if TRUE header is defined
    BOOL        bAllPages;              // repeat header on all pages
    BOOL        bFirstRow;              // if TRUE we are printing the first row
    BOOL        bNewPage;               // if TRUE force page break
    POINTL      ptltr;                  // top right corner of current row
    LONG        ly_pos;                 // Y pos for first line of column
    LONG        lnext_y;                // Ypos for next row
    LONG        lline_type;             // type of line for drawing box
    LONG        lfill;                  // fill type for the table
    LONG        llcolor;                // cell line colour
    LONG        lfcolor;                // cell fill colour
    LONG        ltcolor;                // cell text colour
    LONG        lhline_type;            // type of line for drawing header box
    LONG        lhfill;                 // fill type for the header
    LONG        lhlcolor;               // header line colour
    LONG        lhfcolor;               // header fill colour
    LONG        lhtcolor;               // header text colour
    char        cFont[ FACESIZE];       // font for header
    LONG        lpts;                   // Point size for header
    USHORT      boxtype;                // Type of box around cells
    USHORT      hboxtype;               // Type of box around headers
    USHORT      usCols;                 // number of colums in the table
    PCOL_TYPE   aCol;                   // array of columns
    } TABLE_TYPE, *PTABLE_TYPE;

// **********************************************************************
// description of a print job
// **********************************************************************

typedef struct
    {
    HDC             pt_hdc;             // Device Handle
    HPS             pt_hps;             // Presentation-space handle

    char            doc_name[ 128];     // Name of the document for the spooler
    char            date_str[ 35];      // String with date following PM settings
    char            time_str[ 35];      // String with time following PM settings
    LONG            doc_name_len;       // Length of the document name

    ULONG           pt_left_margin;     // Left margin offset in mm
    ULONG           pt_right_margin;    // Right margin offset in mm
    ULONG           pt_top_margin;      // Top margin offset in mm
    ULONG           pt_bot_margin;      // bottom margin offset in mm

    ULONG           pt_min_lmargin;     // Min Left margin offset in mm
    ULONG           pt_min_rmargin;     // Min Right margin offset in mm
    ULONG           pt_min_tmargin;     // Min Top margin offset in mm
    ULONG           pt_min_bmargin;     // Min Bottom margin offset in mm

    SIZEL           pt_page_size;       // Page size of grafic page in mm

    SIZEL           pt_graph_size;      // Page size of grafic page in twips
    SIZEL           pt_bl_offset;       // Bottom left margins in twips
    SIZEL           pt_tr_offset;       // Top right margin offsets in twips
    SIZEL           pt_tr_margin;       // Top right margins in twips (including header)

    LONG            pt_prt_top;         // Top of the printable page (excluding header)
    LONG            pt_tmargin;         // Current top margin
    LONG            pt_bmargin;         // Current bottom margin
    LONG            pt_lmargin;         // Current left margin in twips
    LONG            pt_rmargin;         // Current right margin in twips
    LONG            pt_wide;            // page width in twips left to right margin
    double          xpels;              // transform factor for bitmaps (x-axis)
    double          ypels;              // transform factor for bitmaps (y-axis)
    double          aspect;

    LONG            pt_point_size;      // Current point size of the font

    LONG            pt_lcid;            // requested character-set local identifier
    SHORT           pt_next_idx;        // next free slot for a font
    SHORT           pt_font_idx;        // index of current font descriptor
    FONT_DESC       pt_font[ MAX_FNT];  // array of fonts used for job

    USHORT          pt_page;            // Page counter
    USHORT          pt_pages;           // Total Page counter for the job
    PTABLE_TYPE     pt_table;           // pointer to a table
    USHORT          pt_col;             // Current column number

    BOOL            pt_header;          // TRUE : Header is defined
    BOOL            pt_allpages;        // TRUE : header on all pages
    USHORT          pt_hlines;          // Number of lines in header
    PH_LINE         pt_psz;             // header lines (user defined)
    char            pt_hfont[ FACESIZE];// header font id
    LONG            pt_hpts;            // header point size
    LONG            pt_hbox_line;       // Box line thickness for the header
    LONG            pt_hbox_mode;       // Box fill style for the header
    USHORT          pt_boxtype;         // Type of box around the header
    LONG            pt_hlcolor;         // Color for the line around the header
    LONG            pt_hfcolor;         // Color for fill pattern
    LONG            pt_htcolor;         // Color for text
    POINTL          pt_hdr_bl;          // Bottom left corner of header box
    POINTL          pt_hdr_tr;          // Top right corner of header box

    BOOL            pt_footer;          // TRUE : footer is defined
    char            pt_footline[ 132];  // footer line (user defined)
    char            pt_ffont[ FACESIZE];// footer font id
    LONG            pt_fpts;            // footer point size
    LONG            pt_fbox_line;       // Box line thickness for the footer
    LONG            pt_fbox_mode;       // Box mode for the footer
    USHORT          pt_fboxtype;        // Type of box around the footer
    LONG            pt_flcolor;         // Color for the line around the footer
    LONG            pt_ffcolor;         // Color for fill pattern
    LONG            pt_ftcolor;         // Color for text
    POINTL          pt_ftr_bl;          // Bottom left corner of footer box
    POINTL          pt_ftr_tr;          // Top right corner of footer box

    LONG            pt_border;          // Page has border of given width
    LONG            pt_fill;            // Page background
    USHORT          pt_box;             // Type of box around the page
    LONG            pt_blcolor;         // Color for the border
    LONG            pt_bfcolor;         // Color for fill pattern
    POINTL          pt_border_bl;       // lower left coord for border (ignored if pt_border = 0)
    POINTL          pt_border_tr;       // upper right coord for border (ignored if pt_border = 0)

    } PRINTER_TYPE, *PPRINTER_TYPE;

// **********************************************************************
// base object data
// **********************************************************************

typedef struct
    {
    HAB             hab;
    HWND            hwnd;
    HMODULE         hmod;

    PSZ             buffer1;                        // buffer used for word wrapping
    PSZ             buffer2;                        // buffer used for word wrapping
    BOOL            bWordBreak;                     // use word break

    DEVOPENSTRUC    DevStruct;                      // device open structure

    BOOL            bMetric;                        // TRUE use mm
    char            pszMeasure[ 32];                // name of the measures
    USHORT          one_unit;                       // One unit in Twips
    double          unit_conv;                      // unit conversion factor

    USHORT          tab_len;                        // distance between tabs
    LONG            *tabs;                          // Array of tab positions
    LONG            numtabs;                        // Number of tabs

    ULONG           def_bmar;                       // Default bottom mar
    ULONG           def_tmar;                       // Default top mar
    ULONG           def_rmar;                       // Default right mar
    ULONG           def_lmar;                       // Default left mar

    USHORT          usline_space;                   // % line spacing

    BOOL            bPrinting;                      // TRUE job is printing

    BOOL            check_page;                     // Flag for starting job

    char            pszfont[ 64];                   // Name of font returned from font dialog
    char            pszFace[ 64];                   // Name of face returned from font dialog
    char            pszForm[ 32];                   // Cuurent form on current printer

    SHORT           prt_idx;                        // Index of current printer
    char            szPrinter[ 128];                // Current printer name

    LONG            lColor;                         // Default colour
    BOOL            bColor;                         // TRUE Enable colour printing
    PVOID           pt_np_func;                     // Pointer to the new page hook function
    char            prt_tit[ 128];                  // Title for printer dialog
    char            szPrtDlgRet[ 128];              // Return from printer dialog
    char            acDlgBut1[ 32];                 // Text for OK button
    char            acDlgBut2[ 32];                 // Text for Job props button
    char            acDlgBut3[ 32];                 // Text for Cancel button

    BOOL            bProgress;                      // display progress dialog during printing
    HWND            hwndProgress;                   // Handle to progress dialog
    PSZ             pszPrTitle;                     // progress dialog Title
    PSZ             pszPrString1;                   // progress dialog display string
    PSZ             pszPrString2;                   // progress dialog display string
    PSZ             pszPrString3;                   // progress dialog display string
    PSZ             pszPrButton;                    // progress dialog button text

    PPRINTER_TYPE   pdata;

    } JOB_TYPE, *PJOB_TYPE;

// **********************************************************************
// Global list of available printers
// **********************************************************************

typedef struct
    {
    HMTX            hmtx;                           // access semaphore
    ULONG           prt_count;                      // number of available printers
    SHORT           def_prt;                        // Index of default printer
    DEVOPENSTRUC    aDevStruct[ MAX_OPEN_DEVS];     // Array of printer data
    PSZ             szPrinterList[ MAX_OPEN_DEVS];  // List of available printers
    } PRT_LIST;

// **********************************************************************
// Internal C routines.
// **********************************************************************

BOOL        PrtOpen( PJOB_TYPE, USHORT);
BOOL        PrtQueryQueueInfo( PJOB_TYPE);
VOID        PrtClose( PJOB_TYPE);
LONG        PrtFindQueue( PSZ, PPRQINFO3, LONG);
BOOL        PrtLoadFont( PJOB_TYPE, SHORT);
LONG        PrtGetNewLcid( PJOB_TYPE);
SHORT       PrtGetSelForm( HDC, HCINFO*);
VOID        PrtBox( PJOB_TYPE, POINTL, POINTL, LONG, LONG, USHORT, LONG, LONG);
BOOL        PrtSetFontSize( PJOB_TYPE, SHORT, LONG);
SHORT       PrtNewFont( PJOB_TYPE, PSZ);
LONG        PrtStringLen( PJOB_TYPE, PSZ);
ULONG       PrtStringLength( PJOB_TYPE, PSZ);
SHORT       PrtFontAvailable( PJOB_TYPE, PSZ);
VOID        PrtNewPage( PJOB_TYPE);
VOID        PrtHeader( PJOB_TYPE);
VOID        PrtFooter( PJOB_TYPE);
BOOL        PrtWrite( PJOB_TYPE, PSZ, USHORT);
BOOL        PrtWriteln( PJOB_TYPE, PSZ);
BOOL        PrtJustified( PJOB_TYPE, PSZ, LONG);
VOID        PrtWordBreak( PJOB_TYPE, LONG, LONG);
BOOL        PrtCentre( PJOB_TYPE, PSZ);
BOOL        PrtJustRight( PJOB_TYPE, PSZ);
BOOL        PrtWriteCol( PJOB_TYPE, PSZ, LONG, PSZ, USHORT);
VOID        PrtSetBorder( PJOB_TYPE);
VOID        PrtSetHeaderBox( PJOB_TYPE);
VOID        PrtGetPrinterList( VOID);
VOID        PrtGetDateString( PJOB_TYPE);
VOID        PrtWriteFormatted( PJOB_TYPE, PSZ, BOOL, USHORT);
BOOL        PrtDrawBitMap( PJOB_TYPE, PSZ, POINTL, POINTL, LONG, LONG, PSZ);
BOOL        PrtDrawJPEG( PJOB_TYPE, PSZ, POINTL, POINTL, LONG, LONG, PSZ);
BOOL        PrtDrawBitMap2( PJOB_TYPE, HMODULE, ULONG, POINTL, POINTL, LONG, LONG, PSZ);
ULONG       PrtDrawWindow( PJOB_TYPE, HWND, POINTL, POINTL, ULONG, LONG, PSZ);
VOID        PrtFixFlagChars( PSZ);
PSZ         PrtChooseFont( PJOB_TYPE, PSZ, PSZ);
USHORT      PrtEndRow( PJOB_TYPE);
PJOB_TYPE   PrtObjectInit( VOID);
VOID        PrtObjectDestroy( PJOB_TYPE);
HFILE       FileReset( PSZ);
APIRET      FileRead( HFILE, PVOID, USHORT);
APIRET      FileReadLn( HFILE, PSZ);
BOOL        PrtWriteTableHeader( PJOB_TYPE);
VOID        PrtAbort( PJOB_TYPE);
BOOL        PrtCheckFits( PJOB_TYPE, PSZ);
BOOL        PrtLineFits( PJOB_TYPE, PSZ);
BOOL        PrtCheckMargins( PJOB_TYPE);
VOID        PrtSetProgressTexts( PJOB_TYPE, PSZ, PSZ, PSZ, PSZ, PSZ);
VOID        PrtLoadProgressDlg( PJOB_TYPE);

VOID        PrtCreateDevStruct( PJOB_TYPE, USHORT);
VOID        PrtDeleteDevStruct( PJOB_TYPE);

VOID        PrtSetPrinter( PJOB_TYPE, int);
BOOL        PrtSetFont( PJOB_TYPE, PSZ);

BOOL        Set_LineSpace( PJOB_TYPE, USHORT);
BOOL        Set_Measures( PJOB_TYPE, const char *);

VOID        PrtMoveX( PJOB_TYPE, LONG, BOOL);
VOID        PrtMoveY( PJOB_TYPE, LONG, BOOL);
VOID        PrtGoto( PJOB_TYPE, LONG, LONG, BOOL);
VOID        PrtGotoX( PJOB_TYPE, LONG, BOOL);
VOID        PrtGotoY( PJOB_TYPE, LONG, BOOL);

VOID        PrtSetCellBitmap( PJOB_TYPE, HBITMAP, PPOINTL, HPS,
                              ULONG, PLONG, PBITMAPINFOHEADER2, PSZ);
VOID        PrtWriteTitle( PJOB_TYPE, PSZ, LONG, LONG);

VOID        PrtFreeCells( PTABLE_TYPE);
PTABLE_TYPE PrtFreeTable( PTABLE_TYPE);
PTABLE_TYPE PrtCreateTable( int);
VOID        PrtInitHeader( PJOB_TYPE, USHORT);
VOID        PrtMakeTabs( PJOB_TYPE);
VOID        PrtResetColHdr( PJOB_TYPE, USHORT, PSZ);
BOOL        PrtBitmapOut( PJOB_TYPE, PPOINTL, HBITMAP, ULONG, PLONG);

ULONG       PrtXPos( PJOB_TYPE);
ULONG       PrtYPos( PJOB_TYPE);
ULONG       PrtXPosTwips( PJOB_TYPE);
ULONG       PrtYPosTwips( PJOB_TYPE);

VOID PrtResetHeader( PJOB_TYPE, LONG, PSZ*);

MRESULT EXPENTRY PrtPrinterDlgProc( HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY PrtProgressDlgProc( HWND, ULONG, MPARAM, MPARAM);
BOOL PrtStartDaemon( VOID);
VOID PrtReleaseDaemon( VOID);
VOID PrtSetupShrMem( PJOB_TYPE);
BOOL Set_RxPrintColor(PJOB_TYPE, PSZ);
BOOL Set_PrintColor( PJOB_TYPE, LONG);

VOID PrtLine( PJOB_TYPE, POINTL, POINTL, LONG, LONG, LONG);

#ifdef TST_NGEN
    #define TRACEWINERROR( s, v)  { ERRORID  errid; USHORT usSev,usCode;\
    errid = WinGetLastError( pjob->hab);usCode = ERRORIDERROR( errid);usSev = ERRORIDSEV( errid);\
    TstWriteTrace( s, v, usSev, usCode);}

    #define TRACEWINERRORN( s)  { ERRORID  errid; USHORT usSev,usCode;\
    errid = WinGetLastError( pjob->hab);usCode = ERRORIDERROR( errid);usSev = ERRORIDSEV( errid);\
    TstWriteTrace( s, usSev, usCode);}
#else
    #define TRACEWINERROR( s, v)
    #define TRACEWINERRORN( s)
#endif

#ifdef __cplusplus
    }
#endif

#endif


#endif

// ***********************************************************************
//
//                              END OF FILE.
//
// ***********************************************************************


