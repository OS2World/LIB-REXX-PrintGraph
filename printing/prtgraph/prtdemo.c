// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   prtdemo.c  $
// $Revision:   1.0  $
// $Date:   28 Sep 1996 13:09:02  $
//
// $Log:   M:\prtgraph\prtdemo.c_v  $
** 
**    Rev 1.0   28 Sep 1996 13:09:02   KANIS
** New filw extension for new make
// 
//    Rev 1.0   04 May 1996 21:09:20   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#define INCL_WIN
#define INCL_SPL
#define INCL_DEV
#define INCL_BASE
#define INCL_DOS
#include <os2.h>
#include "prtdemo.h"

/***** Default printing font ********************************************/

PSZ         pszDefFont = "10.Helvetica Bold";

/***** Available line spacings ******************************************/

PSZ         achLineSpc[] = {
                "10", "20", "30", "40", "50", "60", "70", "80", "90", "100",    
                "110", "120", "130", "140", "150", "160", "170", "180", "190", "200",   
                "210", "220", "230", "240", "250", "260", "270", "280", "290", "300",   
                "310", "320", "330", "340", "350", "360", "370", "380", "390", "400",   
                "410", "420", "430", "440", "450", "460", "470", "480", "490", "500",   
                "510", "520", "530", "540", "550", "560", "570", "580", "590", "600" };

/***** Buffer for printing font *****************************************/

char        achPrtFont[ FACESIZE + 1];

HAB         Hab;
HMQ         Hmq;
HWND        hwndTop = NULLHANDLE,
            hwndDlg = NULLHANDLE;
PILIST      pItems = NULL;
PILIST      pCurItem = NULL;

HGRPRT      hPrt = NULLHANDLE;

/***** Local functions **************************************************/

void PrintTable1( HTABLE);
void PrintTable2( HTABLE, USHORT);

void main( void)
    {
    CHAR        szClassName[] = "PRINT_DEMO_WIN";
    ULONG       lf = 0L;
    HWND        hwnd;
    QMSG        qmsg;
    
    /***** Initialise the Pm environment ********************************/
        
    Hab = WinInitialize(0);
    Hmq = WinCreateMsgQueue( Hab, 0);
    
    /***** Initialise Printing DLL **************************************/
    
    WinRegisterClass( Hab,
                      szClassName,
                      (PFNWP)DemoWndProc,
                      0L,
                      sizeof(PVOID));

     hwndTop = WinCreateStdWindow( HWND_DESKTOP,
                                   0L, &lf, szClassName,
                                   "", 0L, NULLHANDLE, 
                                   ID_WINDOW,
                                   &hwnd);

    
    while( WinGetMsg( Hab, &qmsg, NULLHANDLE, 0, 0))
        WinDispatchMsg( Hab, &qmsg);

    /***** Destroy the PM environment ***********************************/
    
    WinDestroyWindow( hwndTop);
    WinDestroyMsgQueue( Hmq);
    WinTerminate( Hab);
    DelItemList();
    
    /***** Terminate printing DLL ***************************************/
    
    PrtGTerm( hPrt);
    
    return;
    
    } /* end of main() */

/*
*************************************************************************/
 
MRESULT EXPENTRY DemoDlgProc( HWND      hwnd,
                              ULONG     msg,
                              MPARAM    mp1,
                              MPARAM    mp2)
 
/************************************************************************
*                                                                       *
* Description : Dialog procedure for the demo dialog                    *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    BOOL                brc;
    PSZ                 pszFont,
                        pp, pq;
    USHORT              rc;
    PROP_TYPE           prop;
    char                cFamName[ FACESIZE],
                        buffer[ 256];
    HPOINTER            hptr;
    HACCEL              hacl;
    HWND                hwndMenu;
    SWCNTRL             swctl;
    PID                 pid;
 

    switch ( msg)
        {
        case WM_INITDLG :
            
            /***** Get the DLL version string & build title *************/
            
//            hPrt = PrtGInit( hwnd, ( PVOID)NewPageFunc);
            hPrt = PrtGInit( hwnd, NULL);

            prop = PrtGGet( hPrt, PRT_VERSION, &rc);
            pp = strdup( prop.string);
            sprintf( buffer, "PrtGraph Demo C/C++ v%s", pp);
            
            /***** Add entry to switch list *****************************/
            
            WinQueryWindowProcess(hwnd, &pid, NULL);/* gets process id */
            
            /***** initialize switch structure **************************/
            
            swctl.hwnd = hwnd;
            swctl.hwndIcon = NULLHANDLE;
            swctl.hprog = NULLHANDLE;
            swctl.idProcess = pid;
            swctl.idSession = 0;
            swctl.uchVisibility = SWL_VISIBLE;
            swctl.fbJump = SWL_JUMPABLE;
            strcpy(swctl.szSwtitle, buffer);
 
            WinCreateSwitchEntry( Hab, &swctl);
 
            /***** Set the title to the dialog **************************/
            
            prop = PrtGGet( hPrt, PRT_CURRENTPRINTER, &rc);
            pq = strdup( prop.string);
            sprintf( buffer, "PrtGraph Demo C/C++ v%s - %s", pp, pq);
            
            free( pp);
            free( pq);

            WinSetDlgItemText( hwnd, FID_TITLEBAR, buffer);
            
            /***** Load the menu ****************************************/
            
            hwndMenu = WinLoadMenu( hwnd, 0L, DEMO_DLG);
            WinEnableWindowUpdate( hwndMenu, TRUE);
            
            /***** Load and set the accel. table ************************/
            
            hacl = WinLoadAccelTable( Hab, 0L, DEMO_DLG);
            WinSetAccelTable( Hab, hacl, hwnd);
            
            /***** Load and set the icon ********************************/
            
            hptr = WinLoadPointer( HWND_DESKTOP, 0L, DEMO_DLG);
            WinPostMsg( hwnd, WM_SETICON, (MPARAM) hptr, 0L);
            
            /***** Centre the dialog on the screen **********************/
            
            DemoCentreWin( hwnd);
            
            /***** Initialise the fields ********************************/
            
            DemoDlgInit( hwnd);
            
            /***** Get status texts and positions for the fields ********/
            
            DemoDlgGetItemPositions( hwnd);
            return( 0L);
            
        case WM_HITTEST :
            
            /***** Interactive status line ******************************/
            
            DemoDlgSetStatusText( hwnd, mp1);
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        case WM_COMMAND :
            switch( SHORT1FROMMP( mp1))
                {
                case PB_ABOUT :
                    pp = PrtGVersion();
                    AddProductInfoDlg( Hab, hwnd, "PrtGraph Demo C/C++", pp);
                    free( pp); 
                    return(0L);
                
                case PB_PRINTER :
                    pq = PrtGPrinterDlg( hPrt, hwnd, "Choose your printer !!");
                    pp = PrtGVersion();
                    if( pp)
                        sprintf( buffer, "PrtGraph Demo C/C++ v%s - %s", pp, pq);
                    else
                        sprintf( buffer, "PrtGraph Demo C/C++ v%s - (None)", pp);
                    WinSetDlgItemText( hwnd, FID_TITLEBAR, buffer);
                    return(0L);
                        
                case PB_JOBPROPS :
                    PrtGJobProperties( hPrt, hwnd);
                    return(0L);
                
                case PB_PRINT :
                    hptr = WinQuerySysPointer( HWND_DESKTOP, SPTR_WAIT, TRUE);
                    WinSetPointer(HWND_DESKTOP, hptr);
                    brc = DemoPrint( hwnd);
                    hptr = WinQuerySysPointer( HWND_DESKTOP, SPTR_ARROW, TRUE);
                    WinSetPointer(HWND_DESKTOP, hptr);
                    return(0L);
                
                case PB_FONT :
                    
                    /***** Get the current Family Name ******************/
                    
                    WinQueryDlgItemText( hwnd, EF_FONT, 256, buffer);
                    pp = strchr( buffer, ( int)'.');
                    if ( pp)
                        {
                        pp++;
                        pq = strchr( pp, ( int)' ');
                        if( pq)
                            *pq = '\0';
                        } /* end of if */
                    else
                        pp = buffer;

                    strcpy( cFamName, pp);
                    
                    pszFont = PrtGFontDlg( hPrt, "Choose font for printing", cFamName);
                    if( pszFont)
                        WinSetDlgItemText( hwnd, EF_FONT, pszFont);
                    return(0L);

                case DID_CANCEL :
                    WinDismissDlg( hwnd, 0);
                    WinPostMsg( hwndTop, WM_QUIT, 0L, 0L);
                    return(0L);
                }

            break;

        default :
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        }

    return(0L);

    } /* end of DemoDlgProc() */

/*
*************************************************************************/
 
VOID DemoCentreWin( HWND     hwnd)
 
/************************************************************************
*                                                                       *
* Description : Centre the window in the screen                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    SWP         swp;
    LONG        cx, cy;
        
    cy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN);
    cx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN);

    WinQueryWindowPos( hwnd, &swp);
    swp.x = (cx - swp.cx) / 2;
    swp.y = (cy - swp.cy) / 2;
    swp.cx++;
    swp.fl = SWP_RESTORE | SWP_SIZE | SWP_MOVE | SWP_SHOW;
    WinSetWindowPos( hwnd, HWND_TOP, swp.x, swp.y,
                     swp.cx, swp.cy, swp.fl);
    swp.cx--;
    WinSetWindowPos( hwnd, HWND_TOP, swp.x, swp.y,
                     swp.cx, swp.cy, swp.fl);
    
    } /* end of DemoCentreWin() */

/*
*************************************************************************/
 
VOID DemoDlgSetStatusText( HWND       hwnd,
                           MPARAM     mp)
 
/************************************************************************
*                                                                       *
* Description : Set the status text                                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    POINTL      ptl;
    PILIST      p;
    
    ptl.x = (LONG)SHORT1FROMMP( mp);
    ptl.y = (LONG)SHORT2FROMMP( mp);
    
    if ( pCurItem)
        if(( ptl.x > pCurItem->lleft) && 
           ( ptl.x < pCurItem->lright) &&
           ( ptl.y > pCurItem->lbottom) && 
           ( ptl.y < pCurItem->ltop))
                return;
    
    p = pItems;
    while( p)
        {
        if(( ptl.x > p->lleft) && 
           ( ptl.x < p->lright) &&
           ( ptl.y > p->lbottom) && 
           ( ptl.y < p->ltop))
            {
            pCurItem = p;
            WinSetDlgItemText( hwnd, ST_HINT, pCurItem->cStatusText);
            p = NULL;
            return;
            }
        else
            p = p->pnext;
        }
    
    } /* end of DemoDlgSetStatusText() */

/*
*************************************************************************/
 
VOID DemoDlgInit( HWND    hwnd)
 
/************************************************************************
*                                                                       *
* Description : Initialise the buttons and fields in the dialog         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    
    /***** Set header group data ****************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_HW, SPBM_SETLIMITS, MPFROMSHORT( 240), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_HW, SPBM_SETCURRENTVALUE, MPFROMSHORT( 28), 0);
    WinSendDlgItemMsg( hwnd, SPIN_HS, SPBM_SETLIMITS, MPFROMSHORT( 15), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_HS, SPBM_SETCURRENTVALUE, MPFROMSHORT( 8), 0);
    WinCheckButton( hwnd, CB_HEADER, 1);
    WinCheckButton( hwnd, CB_ALLPAGES, 1);
    
    /***** set footer goup data *****************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_FW, SPBM_SETLIMITS, MPFROMSHORT( 240), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_FW, SPBM_SETCURRENTVALUE, MPFROMSHORT( 14), 0);
    WinSendDlgItemMsg( hwnd, SPIN_FS, SPBM_SETLIMITS, MPFROMSHORT( 15), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_FS, SPBM_SETCURRENTVALUE, 0, 0);
    WinCheckButton( hwnd, CB_FOOTER, 1);
    
    /***** set page border goup *****************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_BW, SPBM_SETLIMITS, MPFROMSHORT( 240), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_BW, SPBM_SETCURRENTVALUE, 0, 0);
    WinSendDlgItemMsg( hwnd, SPIN_BS, SPBM_SETLIMITS, MPFROMSHORT( 15), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_BS, SPBM_SETCURRENTVALUE, 0, 0);
    WinCheckButton( hwnd, CB_BORDER, 0);
    
    /***** set line spacing *********************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_INTERL, SPBM_SETARRAY, MPFROMP( achLineSpc), MPFROMSHORT( 60));
    WinSendDlgItemMsg( hwnd, SPIN_INTERL, SPBM_SETCURRENTVALUE, MPFROMSHORT( 11), 0);
    
    /***** set left margin **********************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_LM, SPBM_SETLIMITS, MPFROMSHORT( 100), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_LM, SPBM_SETCURRENTVALUE, MPFROMSHORT( 25), 0);
    
    /***** set right margin *********************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_RM, SPBM_SETLIMITS, MPFROMSHORT( 100), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_RM, SPBM_SETCURRENTVALUE, MPFROMSHORT( 20), 0);
    
    /***** set top margin ***********************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_TM, SPBM_SETLIMITS, MPFROMSHORT( 100), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_TM, SPBM_SETCURRENTVALUE, MPFROMSHORT( 20), 0);
    
    /***** set bottom margin ********************************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_BM, SPBM_SETLIMITS, MPFROMSHORT( 100), MPFROMSHORT( 0));
    WinSendDlgItemMsg( hwnd, SPIN_BM, SPBM_SETCURRENTVALUE, MPFROMSHORT( 25), 0);
    
    /***** set default radio button *************************************/
    
    WinCheckButton( hwnd, RB_TEXTL, 1);
    
    /***** Set the font field *******************************************/
    
    WinSetDlgItemText( hwnd, EF_FONT, pszDefFont);

    } /* end of DemoDlgInit() */

/*
*************************************************************************/
 
VOID DemoDlgGetItemPositions( HWND       hwnd)
 
/************************************************************************
*                                                                       *
* Description : Build list of Items with Status texts                   *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PILIST      p = NULL;
    SWP         swp;
    USHORT      cnt,
                usTextId;
    
    for ( cnt = CB_ALLPAGES; cnt <= SPIN_TM; cnt++)
        {
        usTextId = cnt + DEMO_BASE;
        if( pItems)
            {
            p->pnext = ( PILIST) calloc( 1, sizeof( ILIST));
            p = p->pnext;
            }
        else
            {
            pItems = ( PILIST) calloc( 1, sizeof( ILIST));
            p = pItems;
            }
        p->hwnd = WinWindowFromID( hwnd, cnt);
        p->Id = cnt;
        WinQueryWindowPos( p->hwnd, &swp);
        p->lleft = swp.x;
        p->lright = swp.x + swp.cx;
        p->ltop = swp.y + swp.cy;
        p->lbottom = swp.y;
        WinLoadString( Hab, 0L, usTextId, 128, p->cStatusText);
        } /* end of for */
    
    
    } /* end of DemoDlgGetItemPositions() */

/*
*************************************************************************/
 
VOID DelItemList( )
 
/************************************************************************
*                                                                       *
* Description : Destroy pItems                                          *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PILIST      p,
                q;
    
    p = pItems;
    
    while( p)
        {
        q = p;
        p = p->pnext;
        free( q);
        }
        
    } /* end of DelItemList() */


/************************************************************************/
/*                                                                      */
/* Printing functions.                                                  */
/*                                                                      */
/************************************************************************/

/*
*************************************************************************/
 
BOOL PrepareJob( HWND    hwnd)
 
/************************************************************************
*                                                                       *
* Description : Prepare Headers footers and page borders from fields    *
*               dialog.                                                 *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    HHEADER             hhdr;
    HFOOTER             hftr;
    USHORT              rc;
    BOOL                bFlag1, bFlag2;
    ULONG               ulData,
                        ulFill,
                        ulLine,
                        ulPts,
                        ullm,
                        ulrm,
                        ultm,
                        ulbm,
                        ulPb,
                        ulPs;
    PSZ                 pszData,
                        pszFont,
                        p,
                        pszTitle = "Test Printing (C/C++)";
    
    /***** Initialise Data structures ***********************************/
    
    pszData = ( PSZ) malloc( 256);
    pszFont = ( PSZ) malloc( 256);
    
    /***** Get the font for printing ************************************/

    WinQueryDlgItemText( hwnd, EF_FONT, 256, pszData);
    p = strchr( pszData, ( int)'.');
    if( p)
        {
        *p = '\0';
        ulPts = atol( pszData);
        p++;
        strcpy( achPrtFont, p);
        }
    else
        strcpy( achPrtFont, "Helvetica Bold");
        
    /***** Check if we want headers *************************************/
    
    bFlag1 = ( BOOL)WinQueryButtonCheckstate( hwnd, CB_HEADER);
    
    /***** Check for header on all pages ********************************/
        
    bFlag2 = ( BOOL)WinQueryButtonCheckstate( hwnd, CB_ALLPAGES);
    
    /***** Get header fill style ****************************************/
    
    WinSendMsg( WinWindowFromID( hwnd, SPIN_HS),
                SPBM_QUERYVALUE, &ulFill, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    
    /***** Get header line thickness ************************************/
    
    WinSendMsg( WinWindowFromID( hwnd, SPIN_HW),
                SPBM_QUERYVALUE, &ulLine, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    
    /***** Set printing colours *****************************************/
    
    PrtGSetPrintColors( hPrt, CLR_BLACK, CLR_BLUE, CLR_YELLOW);
    
    /***** Build the header struct for 3 lines **************************/
    
    hhdr = PrtGDefineHeader( bFlag1, bFlag2, achPrtFont, ulPts, ulFill, ulLine, 3);
    
    /***** Define header texts ******************************************/
    
    PrtGAddHeaderLine( hhdr, 1, "$c|");
    PrtGAddHeaderLine( hhdr, 2, "$lADD Consulting (CH)$r@");
    PrtGAddHeaderLine( hhdr, 3, "Demo for PrtGrafC Dynamic Link Library for C/C++");
    PrtGSetHdrLineFont( hhdr, 1, NULL, 14);
    PrtGDefineHdrColors( hhdr, CLR_BLACK, CLR_RED, CLR_CYAN);
    
    /***** Set the header data for the job ******************************/
    
    rc = PrtGSetHeader( hPrt, hhdr);
    
    /***** Free allocated resources *************************************/
    
    hhdr = PrtGDestroyHdrDef( hhdr);
    if( rc)
        return( FALSE);
    
    /***** Check if we want footers *************************************/
    
    bFlag1 = ( BOOL)WinQueryButtonCheckstate( hwnd, CB_FOOTER);
    
    /***** Get fill style for footers ***********************************/
    
    WinSendMsg( WinWindowFromID( hwnd, SPIN_FS),
                SPBM_QUERYVALUE, &ulFill, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    
    /***** Get Line thickness for footers *******************************/
    
    WinSendMsg( WinWindowFromID( hwnd, SPIN_FW),
                SPBM_QUERYVALUE, &ulLine, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));

    ulPts = 8;
    
    /***** Build the footer struct **************************************/
    
    hftr = PrtGDefineFooter( bFlag1, achPrtFont, ulPts, ulFill, ulLine, "$Ý$rpage $#");
    PrtGDefineFtrColors( hftr, CLR_BLACK, CLR_RED, CLR_CYAN);
    
    /***** Set the footer data for the job ******************************/
        
    rc = PrtGSetFooter( hPrt, hftr);
    
    /***** Free allocated resources *************************************/
    
    hftr = PrtGDestroyFtrDef( hftr);
    if( rc)
        return( FALSE);
    
    /***** Get the inter-line space setting *****************************/
    
    WinSendDlgItemMsg( hwnd, SPIN_INTERL,
                       SPBM_QUERYVALUE, MPFROMP( pszData), 
                       MPFROM2SHORT( 256, SPBQ_DONOTUPDATE));

    ulData = atol( pszData);
    rc = PrtGSetLineSpace( hPrt, ( USHORT)ulData);
    if( rc)
        return( FALSE);
    
    /***** Get the margin settings **************************************/
    
    WinSendMsg( WinWindowFromID( hwnd, SPIN_LM),
                SPBM_QUERYVALUE, &ullm, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    WinSendMsg( WinWindowFromID( hwnd, SPIN_RM),
                SPBM_QUERYVALUE, &ulrm, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    WinSendMsg( WinWindowFromID( hwnd, SPIN_TM),
                SPBM_QUERYVALUE, &ultm, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    WinSendMsg( WinWindowFromID( hwnd, SPIN_BM),
                SPBM_QUERYVALUE, &ulbm, 
                MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
    
    /***** Check if we want a page border *******************************/
    
    rc = WinQueryButtonCheckstate( hwnd, CB_BORDER);
    if ( rc)
        {
        WinSendMsg( WinWindowFromID( hwnd, SPIN_BW),
                    SPBM_QUERYVALUE, &ulPb, 
                    MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
        WinSendMsg( WinWindowFromID( hwnd, SPIN_BS),
                    SPBM_QUERYVALUE, &ulPs, 
                    MPFROM2SHORT( 0, SPBQ_DONOTUPDATE));
        } /* end of if */
    else
        {
        ulPb = 0;
        ulPs = 0;
        } /* end of else */
    
    /***** Set the margins for the job **********************************/
    
    rc = PrtGSetMargins( hPrt, ullm, ulrm, ultm, ulbm, ulPb, ulPs);
    if( rc)
        return( FALSE);
    
    /***** Open the print job *******************************************/
        
    rc = PrtGOpenPrintJob( hPrt, pszTitle, 0, 0);
    if( rc)
        return( FALSE);
        
    return ( TRUE);
         
    } /* end of PrepareJob() */

/*
*************************************************************************/
 
BOOL DemoPrint( HWND     hwnd)
 
/************************************************************************
*                                                                       *
* Description : Decide what to print and print it.                      *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    ULONG       ulPts;  

    PSZ         pszMask = "Hello everyone, this is some text in %s %lu point which "
                          "wraps over several lines. This is so that you can "
                          "see how the functions in the graphic printing DLL work. "
                          "We hope that you will find them useful.";
    PSZ         pszText;
    
    if( !PrepareJob( hwnd))
        return( FALSE);

    if ( WinQueryButtonCheckstate( hwnd, RB_TEXTL))
        {
        ulPts = 8; 
        pszText = ( PSZ)malloc( 1024);
        while ( ulPts <= 24)
            {
            sprintf( pszText, pszMask, achPrtFont, ulPts);
            PrtGPrintLine( hPrt, achPrtFont, ulPts, pszText);
            PrtGPrintLine( hPrt, achPrtFont, ulPts, "");
            ulPts = ulPts + 2;
            } /* end of while */
        free( pszText);
        }
        
    else if ( WinQueryButtonCheckstate( hwnd, RB_TEXTR))
        {
        ulPts = 8; 
        pszText = ( PSZ)malloc( 1024);
        while ( ulPts <= 24)
            {
            sprintf( pszText, pszMask, achPrtFont, ulPts);
            PrtGPrintRight( hPrt, achPrtFont, ulPts, pszText);
            PrtGPrintRight( hPrt, achPrtFont, ulPts, "");
            ulPts = ulPts + 2;
            } /* end of while */
        free( pszText);
        }

    else if ( WinQueryButtonCheckstate( hwnd, RB_TEXTC))
        {
        ulPts = 8; 
        pszText = ( PSZ)malloc( 1024);
        while ( ulPts <= 24)
            {
            sprintf( pszText, pszMask, achPrtFont, ulPts);
            PrtGPrintCentered( hPrt, achPrtFont, ulPts, pszText);
            PrtGPrintCentered( hPrt, achPrtFont, ulPts, "");
            ulPts = ulPts + 2;
            } /* end of while */
        free( pszText);
        }

    else if ( WinQueryButtonCheckstate( hwnd, RB_TEXTJ))
        {
        ulPts = 8; 
        pszText = ( PSZ)malloc( 1024);
        while ( ulPts <= 24)
            {
            sprintf( pszText, pszMask, achPrtFont, ulPts);
            PrtGPrintJustified( hPrt, achPrtFont, ulPts, pszText);
            PrtGPrintJustified( hPrt, achPrtFont, ulPts, "");
            ulPts = ulPts + 2;
            } /* end of while */
        free( pszText);
        }

    else if ( WinQueryButtonCheckstate( hwnd, RB_BITMAP))
        {
        PrtGPrintLine( hPrt, achPrtFont, 14, "Hello everyone, this is boxed printout of the ADD logo");
        PrtGPrintBitmap( hPrt, "C:\\OS2\\BITMAP\\ADDLOGO.BMP", 40, 90, 130, 170, LINE_THICK, CLR_DEFAULT);
        PrtGNewPage( hPrt);
        PrtGPrintLine( hPrt, achPrtFont, 14, "Picture of the print demo window");
        PrtGPrintWinImage( hPrt, hwndDlg, 20, 100, 0, 0, 0, CLR_DEFAULT);
        }

    else if ( WinQueryButtonCheckstate( hwnd, RB_TABLES))
        DemoPrintTables( );

    else if ( WinQueryButtonCheckstate( hwnd, RB_STYLES))
        DemoPrintStyles( );
        
    else if ( WinQueryButtonCheckstate( hwnd, RB_TABBED))
        DemoPrintTabbed();
    
    if ( PrtGClosePrintJob( hPrt))
        return( FALSE);
    else
        return( TRUE);

    } /* end of DemoPrint() */

/*
*************************************************************************/
 
VOID DemoPrintTables( )
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    HTABLE      htbl;
    ULONG       aulT1[ 3] = { 45, 50, 40 };
    ULONG       aulT2[ 4] = { 25, 50, 40, 30 };
    
    /********************************************************************/
    /* Define a table with no running headers and three columns.        */
    /* Cells are not filled and have 0.25mm line thickness.             */
    /********************************************************************/

    PrtGPrintLine( hPrt, achPrtFont, 12, "The following table is defined without headers...");

    htbl = PrtGDefineTable( TRUE, FALSE, FALSE, 14, 0, 0, 0, "", 0, 3, 15);

    /***** Add the three columns ****************************************/
    
    PrtGAddColumn( htbl, 1, aulT1[ 0], ""); 
    PrtGAddColumn( htbl, 2, aulT1[ 1], ""); 
    PrtGAddColumn( htbl, 3, aulT1[ 2], ""); 
    
    /***** Start printing the table *************************************/
    
    PrintTable1( htbl);

    /***** Destroy table definition *************************************/
    
    htbl = PrtGDestroyTblDef( htbl);
    
    /********************************************************************/
    /* Define a table with running headers and three columns.           */
    /* Cells are not filled and have 0.25mm line thickness.             */
    /********************************************************************/

    PrtGPrintLine( hPrt, achPrtFont, 12, "The same table with running headers...");
    
    htbl = PrtGDefineTable( TRUE, TRUE, TRUE, 
                            LINE_THIN, FILL_LIGHT, LINE_MEDIUM, FILL_HALF, 
                            "Helvetica Bold", 
                            12L, 3, 10);

    PrtGDefineTableColors( htbl, 
                           CLR_BLACK, CLR_BLUE, CLR_YELLOW,
                           CLR_BLACK, CLR_RED, CLR_CYAN);
                           
    /***** Add the three columns ****************************************/
    
    PrtGAddColumn( htbl, 1, aulT1[ 0], "Column 1"); 
    PrtGAddColumn( htbl, 2, aulT1[ 1], "Column 2"); 
    PrtGAddColumn( htbl, 3, aulT1[ 2], "Column 3"); 
    
    /***** Start printing the table *************************************/
    
    PrintTable1( htbl);

    /***** Destroy table definition *************************************/
    
    htbl = PrtGDestroyTblDef( htbl);
    
    /********************************************************************/
    /* Define a four column table with running headers.                 */
    /* The headers will be repeated on each page.                       */
    /********************************************************************/
    
    PrtGPrintLine( hPrt, achPrtFont, 12, "The following table is defined with running headers"
                 " headers and a fill style...");
    
    htbl = PrtGDefineTable( TRUE, TRUE, TRUE, 
                            14L, 0L, 28L, 8L, 
                            "Helvetica Bold", 
                            12L, 4, 20);

    /***** Add the four columns *****************************************/
    
    PrtGAddColumn( htbl, 1, aulT2[ 0], "Col Nø"); 
    PrtGAddColumn( htbl, 2, aulT2[ 1], "Text"); 
    PrtGAddColumn( htbl, 3, aulT2[ 2], "Random Nø"); 
    PrtGAddColumn( htbl, 4, aulT2[ 3], "Text 2"); 

    /***** Start the table **********************************************/

    PrintTable2( htbl, 20);
        
    htbl = PrtGDestroyTblDef( htbl);
    
    } /* end of DemoPrintTables() */


/*
*************************************************************************/
 
VOID DemoPrintStyles( )
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    ULONG           ulWide,
                    ulHigh,
                    ulblx,
                    ulbly,
                    ultrx,
                    ultry,
                    ulhinc,
                    ulvinc,
                    ulvpos1,
                    ulvpos2,
                    ulhpos,
                    ulFill;
    char            buffer[ 64];
    
    /***** Get the page size ********************************************/
    
    PrtGGetPageSize( hPrt, &ulWide, &ulHigh);

    /***** Calculate positions for printing *****************************/
    
    ulvpos1 = ( ULONG)((ulHigh / 3) * 2);
    ulvpos2 = ( ULONG)(ulHigh / 3);
    ulvinc = ( ULONG)( ulvpos2 / 3);

    ulbly = ulvpos1; 
    ultry = ulvpos1 + ulvinc;

    ulhpos = ( ULONG)( ulWide / 8);
    ulhinc = ( ULONG)(( ulhpos / 3) * 2);

    ulblx = 5;
    ultrx = ulblx + ulhinc;
    
    /***** Say what we are printing *************************************/
    
    PrtGPrintLine( hPrt, achPrtFont, 10, "Defined styles for filling");
    
    /***** print a row of boxes with different styles *******************/
    
    for( ulFill = 0; ulFill <= 7; ulFill++)
        {
        PrtGPrintBox( hPrt, ulblx, ulbly, ultrx, ultry, 28, ulFill, CLR_DEFAULT, CLR_DEFAULT);
        PrtGGoto( hPrt, ulblx, ulbly - 10, FALSE);
        sprintf( buffer, "Style %lu", ulFill);
        PrtGPrintLeft( hPrt, achPrtFont, 10, buffer);
        ulblx += ulhpos;
        ultrx += ulhpos;
        }

    /***** print a row of boxes with different styles *******************/
    
    ulblx = 5;
    ultrx = ulblx + ulhinc;
    ulbly = ulvpos2;
    ultry = ulvpos2 + ulvinc;
    
    for( ulFill = 8; ulFill <= 15; ulFill++)
        {
        PrtGPrintBox( hPrt, ulblx, ulbly, ultrx, ultry, 28, ulFill, CLR_DEFAULT, CLR_DEFAULT);
        PrtGGoto( hPrt, ulblx, ulbly - 10, FALSE);
        sprintf( buffer, "Style %lu", ulFill);
        PrtGPrintLeft( hPrt, achPrtFont, 10, buffer);
        ulblx += ulhpos;
        ultrx += ulhpos;
        }
    
    } /* end of DemoPrintStyles() */


/*
*************************************************************************/
 
VOID DemoPrintTabbed( )
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    ULONG       ulWide,
                ulHigh,
                ulx,
                uly,
                ulvinc,
                ulhinc;
    USHORT      numtabs,
                i;
    char        buffer[ 64];
    
    PrtGGetPageSize( hPrt, &ulWide, &ulHigh);

    /***** Calculate the number of tabs *********************************/
    
    numtabs = ( ULONG)( ulWide / 10) - 1;
    
    /***** Print '|' at each tab position *******************************/
    
    PrtGPrintLine( hPrt, achPrtFont, 10, "Tab positions are shown on the next line");
    PrtGPrintLine( hPrt, "", 0, "");
    PrtGPrintLeft( hPrt, "",  0, "|");

    for ( i = 0; i < numtabs; i++)
        {
        PrtGTab( hPrt);
        PrtGPrintLeft( hPrt, "",  0, "|");
        } /* end of for */
    
    /***** show some moves **********************************************/

    PrtGPrintLine( hPrt, "", 0, "");
    PrtGPrintLine( hPrt, "", 0, "");

    PrtGPrintLeft( hPrt, "",  0, "Here we are");
    PrtGMoveX( hPrt, 10, FALSE);
    PrtGPrintLeft( hPrt, "",  0, "1 cm right");

    PrtGMoveY( hPrt, -10, FALSE);
    PrtGPrintLeft( hPrt, "",  0, "1 cm down ");
    PrtGMoveY( hPrt, 5, TRUE);
    PrtGPrintLeft( hPrt, "",  0, "5 pts up ");
    PrtGMoveY( hPrt, -5, TRUE);
    PrtGPrintLeft( hPrt, "",  0, "5 pts down");

    /***** Go to the bottom of the page *********************************/
    
    PrtGPrintLine( hPrt, "", 0, "");

    PrtGMoveX( hPrt, 100, FALSE);
    PrtGPrintLeft( hPrt, "",  0, "10 cm right");

    PrtGMoveX( hPrt, -50, FALSE);
    PrtGPrintLeft( hPrt, "",  0, "5 cm left");

    PrtGGoto( hPrt, 10, 10, FALSE);
    PrtGPrintLine( hPrt, "", 20, "The End");

    
    } /* end of DemoPrintTabbed() */


/**/
/***********************************************************************/

MRESULT EXPENTRY DemoWndProc(  HWND hwnd,
                               ULONG msg,
                               MPARAM mp1,
                               MPARAM mp2)

/************************************************************************
*                                                                       *
*  Description     : Main Window procedure for Demo program             *
*                                                                       *
*  Function        : Message dependant                                  *
*                                                                       *
*  Return          : Message dependant                                  *
*                                                                       *
************************************************************************/

    {

    switch( msg)
        {
        case WM_CREATE :

            /***** Load the dialog **********************************************/
    
            hwndDlg = WinLoadDlg( HWND_DESKTOP,
                                  hwnd,
                                  (PFNWP)DemoDlgProc,
                                  NULLHANDLE,
                                  DEMO_DLG,
                                  NULL);
    
            return( 0L);
            
        default:
            return( WinDefWindowProc(hwnd, msg, mp1, mp2) );
        }
    
    } /* end of DemoWndProc() */

/*
*************************************************************************/
 
void PrintTable1( HTABLE    htbl)
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 

    if ( !PrtGStartTable( hPrt, htbl))
        {

        /***** Start printing a row *************************************/
        
        PrtGStartRow( hPrt);
        
        /***** write to col 1 *******************************************/
        
        PrtGStartCol( hPrt, 1);
        PrtGPrintRight( hPrt, "Helvetica", 10, "This is some text in the first column. It is not very long,");
        
        /***** write to col 2 *******************************************/
        
        PrtGStartCol( hPrt, 2);
        PrtGPrintJustified( hPrt, "Helvetica Bold", 10, "This is some text in the second column. It is not very long,");
        PrtGPrintJustified( hPrt, "", 0, "This text has several lines and with a bit of luck should force a new page.");
        PrtGPrintJustified( hPrt, "", 0,"If it does then we have a test of a cell rolling over from one page to the next and we will not have to write any more.");
        
        /***** write to col 3 *******************************************/
        
        PrtGStartCol( hPrt, 3);
        PrtGPrintCentered( hPrt, "Helvetica Bold", 14, "This is some text in the third column. It is not very long,");
        
        /***** print out the row ****************************************/
        
        PrtGEndRow( hPrt);
        
        /***** start the next row ***************************************/
        
        PrtGStartRow( hPrt);
        
        /***** write to col 1 *******************************************/
        
        PrtGStartCol( hPrt, 1);
        PrtGPrintRight( hPrt, "CG Times", 10, "This is some text in the first column. It is not very long,");
        
        /***** write to col 2 *******************************************/
        
        PrtGStartCol( hPrt, 2);
        PrtGPrintLeft( hPrt, "Helvetica Bold", 10, "This is some text in the second column. It is not very long and should be left justified.");
        PrtGPrintCentered( hPrt, "", 0, "This text has several lines and with a bit of luck should be centred.");
        PrtGPrintJustified( hPrt, "", 0, "This text here was designed to be justified and should roll over several lines, of course the last line will be left aligned.");
        PrtGPrintRight( hPrt, "", 0, "This last bit of text should finally show all the styles in one cell as it is right aligned.");
        
        /***** write to col 3 *******************************************/
        
        PrtGStartCol( hPrt, 3);
        PrtGPrintJustified( hPrt, "CG Times", 8, "This is some text in the third column. It is not very long,");
        
        /***** print out the row ****************************************/
        
        PrtGEndRow( hPrt);
        
        /***** Terminate the table **************************************/
        
        PrtGEndTable( hPrt);
        
        } /* end of if */
    else
        PrtGPrintLeft( hPrt, "Helvetica Bold", 14, "ERROR - Failed to create the table...");
    
    } /* end of PrintTable1() */

/*
*************************************************************************/
 
void PrintTable2( HTABLE    htbl,
                  USHORT    cnt)
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    USHORT      i;
    char        buffer[ 256];
    
    if ( !PrtGStartTable( hPrt, htbl))
        {
        for ( i = 1; i <= cnt; i++)
            {
            PrtGStartRow( hPrt);
            PrtGStartCol( hPrt, 1);
            sprintf( buffer, "%u", i);
            PrtGPrintLeft( hPrt, "Helvetica Bold", 10, buffer);
            PrtGStartCol( hPrt, 2);
            PrtGPrintLeft( hPrt, "Helvetica Italic", 10, "Some Helvetica Italic text" );
            PrtGStartCol( hPrt, 3);
            sprintf( buffer, "%d", rand());
            PrtGPrintRight( hPrt, "Helvetica", 10, buffer);
            PrtGStartCol( hPrt, 4);
            PrtGPrintRight( hPrt, "Helvetica", 10, "PJK");
            PrtGEndRow( hPrt);
            } /* end of for */
        PrtGEndTable( hPrt);
        }
    else
        PrtGPrintLeft( hPrt, "Helvetica Bold", 14, "ERROR - Failed to create the table...");

    } /* end of PrintTable2() */

/*
*************************************************************************/
 
VOID APIENTRY NewPageFunc( HGRPRT  hp,
                           USHORT  usPage,
                           BOOL    bTable)
 
/************************************************************************
*                                                                       *
* Description :                                                         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    DosBeep( 1000, 500);
    } /* end of NewPageFunc() */

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
