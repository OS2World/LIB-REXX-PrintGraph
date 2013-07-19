// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTDEMO.H  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:09:52  $
//
// $Log:   M:\prtgraph\prtdemo.h_v  $
// 
//    Rev 1.0   04 May 1996 21:09:52   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <malloc.h>
#include    <prtgrafc.h>
#include    "dialog.h"

/************************************************************************/
/* Defines for string table.                                            */
/************************************************************************/

#define ID_WINDOW                       2

#define DEMO_BASE                       100

#define SPIN_HW_TXT                     SPIN_HW     + DEMO_BASE
#define SPIN_HS_TXT                     SPIN_HS     + DEMO_BASE
#define CB_HEADER_TXT                   CB_HEADER   + DEMO_BASE
#define CB_ALLPAGES_TXT                 CB_ALLPAGES + DEMO_BASE
#define SPIN_FW_TXT                     SPIN_FW     + DEMO_BASE
#define SPIN_FS_TXT                     SPIN_FS     + DEMO_BASE
#define CB_FOOTER_TXT                   CB_FOOTER   + DEMO_BASE
#define SPIN_BW_TXT                     SPIN_BW     + DEMO_BASE
#define SPIN_BS_TXT                     SPIN_BS     + DEMO_BASE
#define CB_BORDER_TXT                   CB_BORDER   + DEMO_BASE
#define SPIN_INTERL_TXT                 SPIN_INTERL + DEMO_BASE
#define SPIN_LM_TXT                     SPIN_LM     + DEMO_BASE
#define SPIN_RM_TXT                     SPIN_RM     + DEMO_BASE
#define SPIN_TM_TXT                     SPIN_TM     + DEMO_BASE
#define SPIN_BM_TXT                     SPIN_BM     + DEMO_BASE
#define RB_TEXTL_TXT                    RB_TEXTL    + DEMO_BASE
#define RB_TEXTR_TXT                    RB_TEXTR    + DEMO_BASE
#define RB_TEXTC_TXT                    RB_TEXTC    + DEMO_BASE
#define RB_TEXTJ_TXT                    RB_TEXTJ    + DEMO_BASE
#define RB_BITMAP_TXT                   RB_BITMAP   + DEMO_BASE
#define RB_TABLES_TXT                   RB_TABLES   + DEMO_BASE
#define RB_STYLES_TXT                   RB_STYLES   + DEMO_BASE
#define RB_TABBED_TXT                   RB_TABBED   + DEMO_BASE
#define PB_FONT_TXT                     PB_FONT     + DEMO_BASE
#define EF_FONT_TXT                     EF_FONT     + DEMO_BASE
#define PB_PRINTER_TXT                  PB_PRINTER  + DEMO_BASE
#define PB_JOBPROPS_TXT                 PB_JOBPROPS + DEMO_BASE
#define PB_PRINT_TXT                    PB_PRINT    + DEMO_BASE


/************************************************************************/
/* Structure for holding Status texts                                   */
/************************************************************************/

typedef struct _ILIST
    {
    HWND            hwnd;                   /* Handle to dialog item */
    USHORT          Id;                     /* Id if dialog item */
    LONG            lleft;                  /* left edge */
    LONG            lright;                 /* right edge */
    LONG            ltop;                   /* top edge */
    LONG            lbottom;                /* bottom edge */
    char            cStatusText[ 128];      /* status text */
    struct _ILIST   *pnext;
    } ILIST, *PILIST;

/************************************************************************/
/* Function declarations.                                               */
/************************************************************************/
    
VOID DemoDlgInit( HWND);
VOID DemoDlgSetStatusText( HWND, MPARAM);
VOID DemoDlgGetItemPositions( HWND);
VOID DelItemList( VOID);
BOOL DemoPrint( HWND);
BOOL PrepareJob( HWND);
VOID DemoPrintTables( VOID);
VOID DemoPrintStyles( VOID);
VOID DemoPrintTabbed( VOID);
VOID DemoCentreWin( HWND);

MRESULT EXPENTRY DemoDlgProc( HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY DemoWndProc( HWND, ULONG, MPARAM, MPARAM);

VOID APIENTRY NewPageFunc( HGRPRT, USHORT, BOOL);

/************************************************************************/
/* Declaration for import function (about Dialog)                       */
/************************************************************************/

HWND EXPENTRY AddProductInfoDlg( HAB, HWND, PSZ, PSZ);

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
