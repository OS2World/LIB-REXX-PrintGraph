// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTGREXX.H  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:10:06  $
//
// $Log:   M:\prtgraph\prtgrexx.h_v  $
// 
//    Rev 1.0   04 May 1996 21:10:06   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#ifndef PRT_REXX_H
#define PRT_REXX_H

#define     INCL_REXXSAA
#include    <rexxsaa.h>

#define     BUILDRXSTRING(t,s)      { strcpy((t)->strptr,(s));(t)->strlength=strlen((t)->strptr);}
#define     RXGETLONG( r)           ( RXNULLSTRING(r) ? 0L : atol( (r).strptr) )

#define     INVALID_ROUTINE         40       /* Raise Rexx error        */
#define     VALID_ROUTINE           0        /* Successful completion   */

// **********************************************************************
// Property constants
// **********************************************************************

#define     LEFTMARGIN          0
#define     RIGHTMARGIN         1
#define     TOPMARGIN           2
#define     BOTTOMMARGIN        3
#define     PAGEWIDTH           4
#define     PAGEHEIGHT          5
#define     PRINTING            6
#define     CURRENTPRINTER      7
#define     CURRENTDEVICE       8
#define     LINESPACE           9
#define     VERSION             10
#define     PRINTCOLOR          11
#define     COLORENABLED        12
#define     MEASURES            13
#define     PAGENUM             14
#define     JOBNAME             15
#define     DEFAULTPRINTER      16
#define     MINLEFTMAR          17
#define     MINRIGHTMAR         18
#define     MINTOPMAR           19
#define     MINBOTTOMMAR        20
#define     FORMNAME            21
#define     FORMWIDTH           22
#define     FORMHEIGHT          23
#define     WORDBREAK           24
#define     SHOWPROGRESS        25
#define     XPOS                26
#define     YPOS                27
#define     XPOSTWIPS           28
#define     YPOSTWIPS           29
#define     PROP_NONE           30

#define     MSR_METRIC              "Metric"
#define     MSR_INCH                "Inch"

// **********************************************************************
// Error return Constants
// **********************************************************************

#define     PRTGR_OK                    0   /* Success */
#define     PRTGR_ERR_INV_HANDLE        1   /* Invalid handle passed to function */
#define     PRTGR_ERR_NO_PRINTER        2   /* No printer has been defined */
#define     PRTGR_ERR_PARAMETER         3   /* Parameter was out of range */
#define     PRTGR_ERR_INV_BITMAP        4   /* Not a valid bitmap */
#define     PRTGR_ERR_INV_FILENAME      5   /* File not found */
#define     PRTGR_ERR_INV_FONT          6   /* Failed to load font */
#define     PRTGR_ERR_JOB_OPEN          7   /* Failed to open job */
#define     PRTGR_ERR_NOT_TABLE         8   /* Col/row func outside of table */
#define     PRTGR_ERR_TABLE_HEADER      9   /* Col/row func outside of table */
#define     FILE_BLK_SIZE_ERR           1000

// **********************************************************************
// Fill Styles
// **********************************************************************

#define     FILL_NONE           ( ULONG)0   /* No fill for box */
#define     FILL_FULL           ( ULONG)1   /* full fill for box */
#define     FILL_90             ( ULONG)2   /* 90% tone fill for box */
#define     FILL_80             ( ULONG)3   /* 80% fill for box */
#define     FILL_75             ( ULONG)4   /* 75% fill for box */
#define     FILL_70             ( ULONG)5   /* 70% fill for box */
#define     FILL_60             ( ULONG)6   /* 60% fill for box */
#define     FILL_HALF           ( ULONG)7   /* Half tone fill for box */
#define     FILL_LIGHT          ( ULONG)8   /* Light tone fill for box */
#define     FILL_VERT           ( ULONG)9   /* Vertical line fill for box */
#define     FILL_HORIZ          ( ULONG)10  /* Horizontal line fill for box */
#define     FILL_DIAGR45        ( ULONG)11  /* 45ø Diagonal left to right line fill for box */
#define     FILL_DIAGR33        ( ULONG)12  /* 33ø Diagonal left to right line fill for box */
#define     FILL_DIAGL45        ( ULONG)13  /* 45ø Diagonal right to left line fill for box */
#define     FILL_DIAGL33        ( ULONG)14  /* 33ø Diagonal right to left line fill for box */

// **********************************************************************
// structs for REXX
// **********************************************************************

typedef struct
    {
    char    acProp[32];
    BOOL    bSet;
    } OBJ_PROP;

// **********************************************************************
// Functions for REXX
// **********************************************************************

LONG    ColorToIndex( PSZ);
USHORT  FindProperty( PSZ);
VOID    LongToRXString( LONG, PRXSTRING);

// **********************************************************************
// Declare exported functions for REXX/2
// **********************************************************************

ULONG APIENTRY PrtGRxLoadFuncs( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxDropFuncs( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxClosePrintJob( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetMargins( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetLineSpace( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetHeader( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetHeaderMode( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetFooter( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxOpenPrintJob( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintLine( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintRight( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintJustified( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintCentered( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintLeft( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxGoTo( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxGoToX( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxGoToY( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxGotoTab( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintBox( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxDrawLine( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxTab( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxStartTable( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxDefineTable( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxStartRow( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxStartCol( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxEndRow( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxEndTable( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxNewPage( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrinterList( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrinterDialog( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxFontDialog( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxInit( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxTerm( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxJobProperties( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetPrinter( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintBitmap( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetHeaderLineFont( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxAbortPrintJob( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxResetColHeader( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxResetHeader( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxLineFits( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxBlockFits( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintFile( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSetProgressTexts( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintWinImage( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxPrintBullet( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxSaveJobProps( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);
ULONG APIENTRY PrtGRxReadJobProps( CHAR*, ULONG, PRXSTRING, CHAR*, PRXSTRING);

#endif

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
