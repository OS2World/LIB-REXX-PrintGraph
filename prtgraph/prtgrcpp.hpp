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

#ifndef PRTGRCPP_HPP
#define PRTGRCPP_HPP

// **********************************************************************
// Error return Constants
// **********************************************************************

#define     PRTGR_OK                0   // Success
#define     PRTGR_ERR_INV_HANDLE    1   // Invalid handle passed to function
#define     PRTGR_ERR_NO_PRINTER    2   // No printer has been defined
#define     PRTGR_ERR_PARAMETER     3   // Parameter was out of range
#define     PRTGR_ERR_INV_BITMAP    4   // Not a valid bitmap
#define     PRTGR_ERR_INV_FILENAME  5   // File not found
#define     PRTGR_ERR_INV_FONT      6   // Failed to load font
#define     PRTGR_ERR_JOB_OPEN      7   // Failed to open job
#define     PRTGR_ERR_NOT_TABLE     8   // Col/row func outside of table
#define     PRTGR_ERR_TABLE_HEADER  9   // Col/row func outside of table
#define     PRTGR_ERR_NO_JOB        10  // No print job is running
#define     PRTGR_ERR_PRINTING      11  // A print job is running

// ***********************************************************************
// Fill Styles
// ***********************************************************************

#define     FILL_NONE               0L  // No fill for box
#define     FILL_FULL               1L  // full fill for box
#define     FILL_90                 2L  // 90% tone fill for box
#define     FILL_80                 3L  // 80% fill for box
#define     FILL_75                 4L  // 75% fill for box
#define     FILL_70                 5L  // 70% fill for box
#define     FILL_60                 6L  // 60% fill for box
#define     FILL_HALF               7L  // Half tone fill for box
#define     FILL_LIGHT              8L  // Light tone fill for box
#define     FILL_VERT               9L  // Vertical line fill for box
#define     FILL_HORIZ              10L // Horizontal line fill for box
#define     FILL_DIAGR45            11L // 45ø Diag left to right line fill
#define     FILL_DIAGR33            12L // 33ø Diag left to right line fill
#define     FILL_DIAGL45            13L // 45ø Diag right to left line fill
#define     FILL_DIAGL33            14L // 33ø Diag right to left line fill

// **********************************************************************
// Line thicknesses
// **********************************************************************

#define     LINE_NONE               0L  // No line for box
#define     LINE_THIN               14L // Thin line (0.25mm for box
#define     LINE_MEDIUM             28L // meduium line (0.5mm) for box
#define     LINE_THICK              56L // Thick line (1mm) for box

// **********************************************************************
// Maximum number of lines in a header
// **********************************************************************

#define     PRTGR_MAX_HLINES    5           // Max lines in page header

// **********************************************************************
// Contants for measures
// **********************************************************************

#define     MSR_METRIC              "Metric"
#define     MSR_INCH                "Inch"

//***********************************************************************
// Hook function for new page. A call will be made to this function
// every time a new page is created internally by the library and
// before the page is printed. The format of the function is:
//
// Boolean APIENTRY MyNewPageFunc( LHANDLE   hp,
//                              unsigned long     page_num,
//                              Boolean      in_table);
//
// first_page is set to true if this is the first page of the document
//            i.e. during the OpenPrintJob method
//
// in_table   is set to true if a table is being printed that will
//            continue over to the new page.
//***********************************************************************

typedef void (APIENTRY FNNP)( LHANDLE, unsigned short, Boolean);
typedef FNNP *PFNNP;

// **********************************************************************
// Header Definition Class.
// **********************************************************************

class _Export PageHeaderDef
    {
    LHANDLE     hhdr;

    public:
        LHANDLE     getHandle() { return hhdr; }

        PageHeaderDef::PageHeaderDef( Boolean,          // TRUE=print page headers
                                      Boolean,          // TRUE= on all pages
                                      char *,           // Font name
                                      unsigned long,    // Font points
                                      unsigned long,    // Box mode
                                      unsigned long,    // Box line
                                      unsigned short);  // Number of lines

        PageHeaderDef::~PageHeaderDef( );

        int DefineColors( long,                         // text colour
                          long,                         // border colour
                          long);                        // fill colour

        int AddHeaderLine( unsigned short,              // line index (1 to 5)
                           char *);                     // Text

        int SetLineFont( unsigned short,                // line index (1 to 5)
                         char *,                        // font for the line
                         unsigned long);                // point size for the line
    };

// **********************************************************************
// Footer Definition Class.
// **********************************************************************

class _Export PageFooterDef
    {
    LHANDLE     hftr;

    public:
        LHANDLE getHandle() { return hftr; }

        PageFooterDef::PageFooterDef( Boolean,          // TRUE=print footers
                                      char *,           // Font for footer
                                      unsigned long,    // Font points
                                      unsigned long,    // box mode
                                      unsigned long,    // box line
                                      char *);          // Text

        PageFooterDef::~PageFooterDef( );

        int DefineColors( long,                         // text colour
                          long,                         // border colour
                          long);                        // fill colour
    };

// **********************************************************************
// Table Definition Class.
// **********************************************************************

class _Export TableDef
    {
    LHANDLE     htbl;

    public:
        LHANDLE getHandle() { return htbl; }

        TableDef::TableDef( Boolean,            // TRUE=boxed
                            Boolean,            // TRUE= header defined
                            Boolean,            // TRUE=print header on all pages
                            unsigned long,      // Cell line thickness
                            unsigned long,      // Cell fill type
                            unsigned long,      // Header line thickness
                            unsigned long,      // Header fill type
                            char *,             // Header font
                            unsigned long,      // Header font points
                            unsigned short,     // Number of columns
                            unsigned long);     // Left edge of table

        TableDef::~TableDef( );

        int AddColumn( unsigned short,          // Column number
                       unsigned long,           // width in mm
                       char *);                 // Header text

        int DefineColors( long,                 // cell text colour
                          long,                 // cell border colour
                          long,                 // cell fill colour
                          long,                 // header text colour
                          long,                 // header border colour
                          long);                // header fill colour

    };

// **********************************************************************
// Printer Class.
// **********************************************************************

class _Export Printer
    {
    LHANDLE         hp;

    public:

        // Constructors

        Printer::Printer( PFNNP);       // Initialise with hook for new page
        Printer::Printer( );            // Initialise with no hook for new page

        // Destructor

        Printer::~Printer( );

        // **************************************************************
        // Properties
        // **************************************************************

        char *Get_CurrentPrinter( );            // buffer to receive result
        char *Get_CurrentDevice( );             // buffer to receive result
        char *Get_DefaultPrinter( );            // buffer to receive result
        char *Get_Units( );                     // buffer to receive result
        char *Get_FormName( );                  // buffer to receive result
        char *Get_Version( );                   // buffer to receive result
        char *Get_JobName( );                   // buffer to receive result

        unsigned short Get_Spacing( );
        unsigned short Get_PageNum( );
        unsigned short Get_NumPrinters( );

        unsigned long Get_BottomMargin( );
        unsigned long Get_TopMargin( );
        unsigned long Get_LeftMargin( );
        unsigned long Get_RightMargin( );
        unsigned long Get_MinBotMargin( );
        unsigned long Get_MinTopMargin( );
        unsigned long Get_MinLeftMargin( );
        unsigned long Get_MinRightMargin( );
        unsigned long Get_FormHeight( );
        unsigned long Get_FormWidth( );
        unsigned long Get_PageHeight( );
        unsigned long Get_PageWidth( );

        long Get_PrintingColor( );

        Boolean Get_ColorEnabled( );
        Boolean Get_ShowProgress( );
        Boolean Get_WordBreak( );
        Boolean Get_Printing( );

        void Set_Units( const char*);
        void Set_PrintingColor( long);
        void Set_ShowProgress( Boolean);
        void Set_WordBreak( Boolean);
        void Set_ColorEnabled( Boolean);
        void Set_Spacing( unsigned short);

        // **************************************************************
        // Methods
        // **************************************************************

        int OpenPrintJob( char *,               // Title
                          unsigned short,       // Total pages
                          unsigned short);      // Copies

        int ClosePrintJob( );

        int AbortPrintJob( );

        int SetMargins( unsigned long,          // Left margin
                        unsigned long,          // Bottom margin
                        unsigned long,          // Right margin
                        unsigned long,          // Top margin
                        unsigned long,          // Border thickness
                        unsigned long);         // Fill style

        int SetPrintColors( long,               // Text color
                            long,               // Border color
                            long);              // Fill color

        int SetHeader( PageHeaderDef *);

        int SetFooter( PageFooterDef*);

        int PrintLeft( char *,                  // font
                       unsigned long,           // point size
                       char *);                 // string

        int PrintLine( char *,                  // font
                       unsigned long,           // point size
                       char *);                 // string

        int PrintRight( char *,                 // font
                        unsigned long,          // point size
                        char *);                // string

        int PrintJustified( char *,             // font
                            unsigned long,      // point size
                            char *);            // string

        int PrintCentered( char *,              // font
                           unsigned long,       // point size
                           char *);             // string

        Boolean BlockFits( char *,              // font
                           unsigned long,       // point size
                           char *);             // string

        Boolean LineFits( char *,               // font
                          unsigned long,        // point size
                          char *);              // string

        int PrintFile( char *,                  // font
                       unsigned long,           // point size
                       unsigned short,          // style
                       char *);                 // file name

        int PrintBox( unsigned long,            // Left
                      unsigned long,            // Bottom
                      unsigned long,            // Right
                      unsigned long,            // Top
                      unsigned long,            // Border thickness
                      unsigned long);           // Fill style

        int PrintBox( unsigned long,            // Left
                      unsigned long,            // Bottom
                      unsigned long,            // Right
                      unsigned long,            // Top
                      unsigned long,            // Border thickness
                      unsigned long,            // Fill style
                      long,                     // Border color
                      long);                    // Fill color

        int PrintBitmap( char *,                // file name
                         unsigned long,         // Left
                         unsigned long,         // Bottom
                         unsigned long,         // Right
                         unsigned long,         // Top
                         unsigned long);        // Border thickness

        int PrintBitmap( char *,                // file name
                         unsigned long,         // Left
                         unsigned long,         // Bottom
                         unsigned long,         // Right
                         unsigned long,         // Top
                         unsigned long,         // Border thickness
                         long);                 // Border color

        int PrintWinImage( HWND,                // Window to print
                           unsigned long,       // Left
                           unsigned long,       // Bottom
                           unsigned long,       // Right
                           unsigned long,       // Top
                           unsigned long,       // Border thickness
                           long);               // Border color

        int MoveX( long,                        // relative distance
                   Boolean);                    // TRUE = in points

        int MoveY( long,                        // relative distance
                   Boolean);                    // TRUE = in points

        int StartTable( TableDef*);

        int StartRow();

        int StartCol( unsigned short);          // column number

        int EndTable();

        int EndRow();

        int ResetColHeader( unsigned short,     // Column number
                            char *);            // New text

        int Goto( unsigned long,                // x coord
                  unsigned long,                // y coord
                  Boolean);                     // measure in points

        int NextTab( );

        int NewPage( );

        void PrinterList( Boolean,              // TRUE = refresh list
                          char **);             // Pre-allocated array for names

        int SetPrinter( unsigned short);        // Index in printer list + 1

        char *PrinterDialog( HWND,              // parent window handle
                             char *);           // Title of dialog

        char *PrinterDialog( HWND,              // parent window handle
                             char *,            // Title of dialog
                             char *,            // OK button text
                             char *,            // Job props button text
                             char *);           // Cancel button text

        char *FontDialog( char *,               // Title for dialog
                          char *);              // Old face name

        int JobProperties( HWND);               // Parent window

    };

// **********************************************************************
// these defines are used for compiling the DLL
// **********************************************************************

#define     MOD_NAME                "PRTGRCPP"
#define     USE_HOOK                TRUE

#endif

// ***********************************************************************
//
//                              END OF FILE.
//
// ***********************************************************************


