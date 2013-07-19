/***********************************************************************
** 
** $Author:   KANIS  $
** $Workfile:   prtrxdae.c  $
** $Revision:   1.1  $
** $Date:   02 Oct 1996 10:24:02  $
**
** $Log:   M:\prtgraph\prtrxdae.c_v  $
** 
**    Rev 1.1   02 Oct 1996 10:24:02   KANIS
** Fix for Job property dialogs
** Changes marked with "E00001"
**
**    Rev 1.0   28 Sep 1996 13:07:48   KANIS
** Change of file extension for new make
**
** ********************************************************************/

#define     INCL_DOS
#define     INCL_BASE
#define     INCL_ERRORS
#define     INCL_WIN
#define     INCL_GPI
#define     INCL_DEV
#define     INCL_SPL
#define     INCL_SPLDOSPRINT
#define     INCL_BASE
#include    <os2.h>
#include    <bseerr.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdio.h>
#include    <ctype.h>
#include    <tstngen.h>
#include    "prt_dlg.h"
#include    "prt_int.h"
#include    "prtrxdae.h"

// **********************************************************************
// Function declarations
// **********************************************************************

MRESULT EXPENTRY PrtWndProc( HWND, ULONG, MPARAM, MPARAM);

PRT_LIST        pPrtList;
PSHR_MEM_BLOCK  pShrMem;        // Shared mem for dialogs
HMTX            HmtxShr;        // Access semaphore for shared mem
HEV             HevShr;         // Synch semaphore for shared mem
HAB             hab;
PVOID           pvShrObject = NULL;

//
// **********************************************************************

void main( void)
 
// **********************************************************************

    { 
    CHAR            szClassName[] = "REXX_PRINT_WIN";
    QMSG            qmsg;           /* structure to store messages */
    HMQ             hmq;
    HWND            hwndC;
    ULONG           lf = FCF_TASKLIST;
    ULONG           ulObjSize;
    APIRET          rc;
    
    // ***** Create or open the Event Semaphore *************************
    
    if ( DosOpenEventSem( SHR_HEV_NAME, &HevShr))
        DosCreateEventSem( SHR_HEV_NAME, &HevShr, 0L, FALSE);
    
    // ***** Create or open the Mutex Semaphore *************************
    
    DosCreateMutexSem( SHR_HMTX_NAME, &HmtxShr, 0L, FALSE);
    
    // ***** Create named shared memory *********************************

    ulObjSize = sizeof( SHR_MEM_BLOCK);

    rc = DosAllocSharedMem(&pvShrObject,
                           SHR_MEM_NAME,
                           ulObjSize,
                           PAG_READ | PAG_COMMIT | PAG_WRITE );
    if (rc != NO_ERROR) 
        {
        DosBeep( 880, 2000);
        DosPostEventSem( HevShr);
        DosCloseMutexSem( HmtxShr);
        DosCloseEventSem( HevShr);
        return;
        }
    
    pShrMem = ( PSHR_MEM_BLOCK)pvShrObject;
    memset( pShrMem, 0, sizeof( SHR_MEM_BLOCK));
    
    // ***** Create the window ******************************************
    
    hab = WinInitialize(0);

    hmq = WinCreateMsgQueue( hab, 0);

    WinRegisterClass( hab,
                      szClassName,
                      (PFNWP)PrtWndProc,
                      0L,
                      sizeof(PVOID));

     pShrMem->hwnd = WinCreateStdWindow( HWND_DESKTOP, 
                                         0L, 
                                         &lf,
                                         szClassName, 
                                         NULL, 
                                         0L,
                                         NULLHANDLE, 
                                         ID_WINDOW, 
                                         &hwndC );
 
    TST_TRACE(( "main: NOTE created window (%lu)", pShrMem->hwnd))

    DosPostEventSem( HevShr);
    
    if ( pShrMem->hwnd == NULLHANDLE)
        {
        DosBeep( 440, 2000);
        DosPostEventSem( HevShr);
        WinDestroyMsgQueue( hmq);
        WinTerminate( hab);
        DosFreeMem( pvShrObject);
        DosCloseMutexSem( HmtxShr);
        DosCloseEventSem( HevShr);
        return;
        }

    PrtGetPrinterList();

    while( WinGetMsg( hab, &qmsg, NULLHANDLE, 0, 0))
        WinDispatchMsg( hab, &qmsg);

    TST_TRACE(( "PrtMsgThread: NOTE Thread ends"))
    
    WinDestroyWindow( pShrMem->hwnd);
    WinDestroyMsgQueue( hmq);
    WinTerminate( hab);

    DosFreeMem( pvShrObject);
    DosCloseMutexSem( HmtxShr);
    DosCloseEventSem( HevShr);

    } // end of main()

//
// **********************************************************************

MRESULT EXPENTRY PrtWndProc(  HWND hwnd,
                              ULONG msg,
                              MPARAM mp1,
                              MPARAM mp2)

// **********************************************************************

    {
    LONG            ret;
    PPROG_DLG_DATA  pProgData;
    HPS             hps;
    RECTL           rcl;
    char            demo_str[ 256];
    PSZ             d_str = "This is an unregistered version of\n"
                            "PRTGRAPH.DLL v %s\n\n"
                            "This product is shareware and can be "
                            "registered through CompuServe or by "
                            "contacting the address in the online "
                            "programming help\n\n"
                            "¸1995, 1996 ADD Consulting (CH)";
            
    
    switch( msg)
        {
        case WM_CREATE :
            TST_TRACE(( "PrtWndProc: NOTE - Window created"))
            return(0L);

        case WM_SHAREWARE :
            sprintf( demo_str, d_str, VER_NUM);
            WinMessageBox( HWND_DESKTOP, 
                           HWND_DESKTOP, 
                           demo_str,
                           "PRTGRAPH - Unregistered Version",
                           0, MB_INFORMATION | MB_ENTER | MB_MOVEABLE);
            DosPostEventSem( HevShr);
            WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
            break;

        case WM_PAINT:
            hps = WinBeginPaint( hwnd, 0L, &rcl);
            GpiErase( hps);
            WinEndPaint(hps);
            return (0L);

        case WM_CLOSE :
            TST_TRACE(( "PrtWndProc: NOTE - Window close called"))
            WinPostMsg( hwnd, WM_QUIT, 0L, 0L);
            return(0L);

        case WM_JOBDLG :
            {                                                                   /* E00001 */
            LONG    idx = ( LONG)mp1;                                           /* E00001 */
            BOOL    external = TRUE;                                            /* E00001 */
            
            if( idx < 0L)                                                       /* E00001 */
                idx = pShrMem->prt_idx;                                         /* E00001 */
            else                                                                /* E00001 */
                external = FALSE;                                               /* E00001 */

            DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);            /* E00001 */
                                                                                /* E00001 */
            /* display job properties dialog and get updated */                 /* E00001 */
            /* job properties from driver */                                    /* E00001 */
                                                                                /* E00001 */
            ret = DevPostDeviceModes( hab,
                                      pPrtList.aDevStruct[ idx].pdriv,          /* E00001 */
                                      pPrtList.aDevStruct[ idx].pszDriverName,  /* E00001 */
                                      pPrtList.aDevStruct[ idx].pdriv->szDeviceName, /* E00001 */
                                      pPrtList.aDevStruct[ idx].pszLogAddress,  /* E00001 */
                                      DPDM_POSTJOBPROP);                        /* E00001 */

            DosReleaseMutexSem( pPrtList.hmtx);                                 /* E00001 */

            if( ret == DEV_OK)
                {
                memcpy( &( pShrMem->drvData), pPrtList.aDevStruct[ idx].pdriv,  /* E00001 */
                            pPrtList.aDevStruct[ idx].pdriv->cb);               /* E00001 */
                }                                                               /* E00001 */
                                                                                /* E00001 */
            if( external)                                                       /* E00001 */
                {                                                               /* E00001 */
                DosPostEventSem( HevShr);
                WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
                }                                                               /* E00001 */
            return( 0L);                                                        /* E00001 */
            }                                                                   /* E00001 */
                                                                                /* E00001 */
        case WM_PRTDLG :

            WinLoadDlg( HWND_DESKTOP,                                           /* E00001 */
                        hwnd,
                        (PFNWP)PrtPrinterDlgProc,
                        NULLHANDLE,
                        PRT_DLG_PRINTERS,
                        NULL);
            return( 0L);

        case WM_FONTDLG :
            { 
            FONTDLG     fdFontDlg;
            FIXED       fxFSize;
            SIZEL       sizl = {0, 0};
            PSZ         pszPreview;
            HDC         hdc;
            HPS         hpsW;
            HWND        hwndFd;

            memset ( &fdFontDlg, 0, sizeof ( FONTDLG ));
            pszPreview = ( PSZ) malloc( 12);
            strcpy( pszPreview, "abcABC");

            strcpy( pShrMem->pszfont, "");
            
            hdc = DevOpenDC( hab,
                             OD_INFO,
                             "*",
                             3L,
                             ( PDEVOPENDATA)&( pPrtList.aDevStruct[ pShrMem->prt_idx]),
                             (HDC)NULL);
                  
            if ( hdc == DEV_ERROR)
                {
                TST_TRACE(( "PrtChooseFont: ERROR - Failed to open device context"))
                strcpy( pShrMem->pszfont, "ERROR - Failed to open device context");
                FREE( pszPreview);
                DosPostEventSem( HevShr);
                WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
                return( 0L);
                }

            hps = GpiCreatePS( hab,
                               hdc,
                               (PSIZEL)&sizl,
                               PU_TWIPS | GPIA_ASSOC | GPIF_LONG);

            if ( hps == GPI_ERROR)
                {
                TST_TRACE(( "PrtChooseFont: ERROR - Failed to create presentation space"))
                DevCloseDC( hdc);
                strcpy( pShrMem->pszfont, "ERROR - Failed to create presentation space");
                FREE( pszPreview);
                DosPostEventSem( HevShr);
                WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
                return( 0L);
                }

            hpsW = WinGetPS ( HWND_DESKTOP);        
            fxFSize = MAKEFIXED( 10, 0);
            memset( &fdFontDlg, 0, sizeof ( FONTDLG ));
            
            fdFontDlg.cbSize = sizeof ( FONTDLG );
            fdFontDlg.hpsScreen = hpsW;
            fdFontDlg.hpsPrinter = hps;
            fdFontDlg.pszTitle = pShrMem->prt_tit;
            fdFontDlg.pszFamilyname = pShrMem->pszFace;
            fdFontDlg.usFamilyBufLen = FACESIZE;
            fdFontDlg.pszPreview = pszPreview;
            
            fdFontDlg.fl = FNTS_CENTER;
            fdFontDlg.flFlags = FNTF_NOVIEWSCREENFONTS;
            fdFontDlg.clrFore = CLR_NOINDEX;
            fdFontDlg.clrBack = CLR_NOINDEX;

            strcpy( fdFontDlg.fAttrs.szFacename, "");
            fdFontDlg.fAttrs.fsSelection = FATTR_SEL_OUTLINE;
            fdFontDlg.fxPointSize = fxFSize;
            
            hwndFd = WinFontDlg ( HWND_DESKTOP,
                                  hwnd,
                                  &fdFontDlg );
            if( hwndFd && ( fdFontDlg.lReturn == DID_OK))
                {
                strcpy( pShrMem->pszFace, fdFontDlg.fAttrs.szFacename);
                sprintf ( pShrMem->pszfont,
                          "%d.%s",
                          FIXEDINT ( fdFontDlg.fxPointSize ),
                          fdFontDlg.fAttrs.szFacename );
                } /* endif */
            else
                if ( !hwndFd)
                    strcpy( pShrMem->pszfont, "ERROR - Failed to load font dialog");
                else
                    strcpy( pShrMem->pszfont, "");

            GpiDestroyPS( hps);
            GpiDestroyPS( hpsW);
            DevCloseDC( hdc);
            FREE( pszPreview);

            DosPostEventSem( HevShr);
            WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
            }
            return( 0L);

        case WM_PROGRESS :
            pProgData = ( PPROG_DLG_DATA) malloc( sizeof( PROG_DLG_DATA));
            strcpy( pProgData->pszPrTitle, pShrMem->pszPrTitle);
            strcpy( pProgData->pszPrString1, pShrMem->pszPrString1);
            strcpy( pProgData->pszPrString2, pShrMem->pszPrString2);
            strcpy( pProgData->pszPrString3, pShrMem->pszPrString3);
            pShrMem->hwndProgress = WinLoadDlg( HWND_DESKTOP,
                                                hwnd,
                                                (PFNWP)PrtProgressDlgProc,
                                                NULLHANDLE,
                                                PRT_DLG_PROGRESS1,
                                                pProgData);

            DosPostEventSem( HevShr);
            return( 0);
        
        default:
            return( WinDefWindowProc(hwnd, msg, mp1, mp2) );
        }

    return( 0L);
    
    } // end of PrtWndProc()

//
// **********************************************************************

MRESULT EXPENTRY PrtPrinterDlgProc(  HWND hwnd,
                                     ULONG msg,
                                     MPARAM mp1,
                                     MPARAM mp2)


// **********************************************************************

    {
    ULONG           i;
    SHORT           idx;
    LONG            wcx,
                    wcy;
    SWP             swp;                                                        /* E00001 */
            
    switch( msg)
        {

        case WM_INITDLG :
            WinSetWindowText( WinWindowFromID( hwnd, FID_TITLEBAR), pShrMem->prt_tit);
            WinSendDlgItemMsg( hwnd, PRT_DLG_PRT_LST,
                               EM_SETTEXTLIMIT,
                               MPFROMSHORT( 128), 0L);
            DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);            /* E00001 */
            for ( i = 0; i < pPrtList.prt_count; i++)
                WinSendDlgItemMsg(  hwnd, PRT_DLG_PRT_LST,
                                    LM_INSERTITEM,
                                    MPFROMSHORT( LIT_END),
                                    MPFROMP( pPrtList.szPrinterList[ i]));

            DosReleaseMutexSem( pPrtList.hmtx);                                 /* E00001 */
            WinSendDlgItemMsg(  hwnd, PRT_DLG_PRT_LST,
                                LM_SELECTITEM,
                                MPFROMSHORT( pShrMem->prt_idx),
                                MPFROMLONG( 1));

            WinSetDlgItemText( hwnd, DID_OK, pShrMem->acDlgBut1);
            WinSetDlgItemText( hwnd, PRT_DLG_PROPS, pShrMem->acDlgBut2);
            WinSetDlgItemText( hwnd, DID_CANCEL, pShrMem->acDlgBut3);

            WinQueryWindowPos( hwnd, &swp);
            wcx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN);
            wcy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN);
            swp.x = ( wcx - swp.cx) / 2;
            swp.y = ( wcy - swp.cy) / 2;
            WinSetWindowPos( hwnd, swp.hwndInsertBehind, swp.x, swp.y, swp.cx, swp.cy, swp.fl);

            WinShowWindow( hwnd, TRUE);
            WinSetFocus( HWND_DESKTOP, hwnd);
            return( (MRESULT)TRUE);

        case WM_CONTROL :
            if ( SHORT2FROMMP( mp1) == LN_ENTER)
                {
                DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);        /* E00001 */
                                                                                /* E00001 */
                idx =  SHORT1FROMMR( WinSendDlgItemMsg( hwnd,                   /* E00001 */
                                                       PRT_DLG_PRT_LST,
                                                       LM_QUERYSELECTION,
                                                       0L, 0L));                /* E00001 */
                                                                                /* E00001 */
                if (idx == LIT_NONE)                                            /* E00001 */
                    {
                    pShrMem->prt_idx = pPrtList.def_prt;
                    strcpy( pShrMem->szPrtDlgRet, "");
                    }
                else
                    {
                    pShrMem->prt_idx = idx;
                    memcpy( &( pShrMem->drvData), pPrtList.aDevStruct[ idx].pdriv,
                            pPrtList.aDevStruct[ idx].pdriv->cb);
                    WinSendDlgItemMsg( hwnd,                                    /* E00001 */
                                       PRT_DLG_PRT_LST,                         /* E00001 */
                                       LM_QUERYITEMTEXT,                        /* E00001 */
                                       MPFROM2SHORT( idx, 127),                 /* E00001 */
                                       MPFROMP( pShrMem->szPrtDlgRet));         /* E00001 */
                    }                                                           /* E00001 */
                DosReleaseMutexSem( pPrtList.hmtx);                             /* E00001 */
                WinDismissDlg( hwnd, 0);                                        /* E00001 */
                DosPostEventSem( HevShr);                                       /* E00001 */
                WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);                  /* E00001 */
                return(0L);
            
                } /* end of if */
            
            break;
        
        case WM_COMMAND :
            switch(SHORT1FROMMP(mp1))
                {
                case DID_OK :
                    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);    /* E00001 */
                    idx = SHORT1FROMMR( WinSendDlgItemMsg( hwnd,                /* E00001 */
                                                          PRT_DLG_PRT_LST,      /* E00001 */
                                                          LM_QUERYSELECTION,
                                                          0L, 0L));             /* E00001 */
                    if (idx == LIT_NONE)                                        /* E00001 */
                        {                                                       /* E00001 */
                        pShrMem->prt_idx = pPrtList.def_prt;                    /* E00001 */
                        strcpy( pShrMem->szPrtDlgRet, "");
                        }
                    else
                        {
                        pShrMem->prt_idx = idx;
                        memcpy( &( pShrMem->drvData), pPrtList.aDevStruct[ idx].pdriv,
                                pPrtList.aDevStruct[ idx].pdriv->cb);
                        WinSendDlgItemMsg( hwnd, PRT_DLG_PRT_LST,               /* E00001 */
                                                 LM_QUERYITEMTEXT,              /* E00001 */
                                                 MPFROM2SHORT( idx, 127),       /* E00001 */
                                                 MPFROMP( pShrMem->szPrtDlgRet)); /* E00001 */
                        }                                                       /* E00001 */
                    DosReleaseMutexSem( pPrtList.hmtx);                         /* E00001 */
                    WinDismissDlg( hwnd, 0);                                    /* E00001 */
                    DosPostEventSem( HevShr);                                   /* E00001 */
                    WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);              /* E00001 */
                    return(0L);

                case DID_CANCEL :
                    strcpy( pShrMem->szPrtDlgRet, "");
                    WinDismissDlg( hwnd, 0);
                    DosPostEventSem( HevShr);                                   /* E00001 */
                    WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);              /* E00001 */
                    return(0L);
                    
                case PRT_DLG_PROPS :
                    idx = SHORT1FROMMR( WinSendDlgItemMsg( hwnd,                /* E00001 */
                                                          PRT_DLG_PRT_LST,      /* E00001 */
                                                          LM_QUERYSELECTION,
                                                          0L, 0L));             /* E00001 */
                    if (idx != LIT_NONE)                                        /* E00001 */
                        {
                        WinPostMsg( pShrMem->hwnd, WM_JOBDLG, MPFROMSHORT( idx), 0L); /* E00001 */
                        }                                                       /* E00001 */

                    return( 0);

                }
            break;

        default :
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        }

    return( WinDefDlgProc( hwnd, msg, mp1,mp2));

    }  // end of PrtPrinterDlgProc()

//
// **********************************************************************

MRESULT EXPENTRY PrtProgressDlgProc( HWND hwnd, 
                                     ULONG msg, 
                                     MPARAM mp1, 
                                     MPARAM mp2)

// **********************************************************************

    {
    PPROG_DLG_DATA  pjob;
    USHORT          usPage;
    SWP             swp;
    LONG            wcx, wcy;
    char            dlgstr[ 256];
                
    switch( msg)
        {

        case WM_INITDLG :
            pjob = ( PPROG_DLG_DATA)mp2;
            WinSetWindowPtr(hwnd, 0, pjob);
            
            if( strlen( pjob->pszPrTitle))
                WinSetWindowText( WinWindowFromID( hwnd, FID_TITLEBAR), pjob->pszPrTitle);
            
            if( strlen( pjob->pszPrString1))
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT1, pjob->pszPrString1);
            
            if( strlen( pjob->pszPrString2))
                {
                sprintf( dlgstr, pjob->pszPrString2, 1);
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT2, dlgstr);
                }

            if( strlen( pjob->pszPrString3))
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT3, pjob->pszPrString3);

            WinQueryWindowPos( hwnd, &swp);
            wcx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN);
            wcy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN);
            swp.x = ( wcx - swp.cx) / 2;
            swp.y = ( wcy - swp.cy) / 2;
            WinSetWindowPos( hwnd, swp.hwndInsertBehind, swp.x, swp.y, swp.cx, swp.cy, swp.fl);
            WinShowWindow( hwnd, TRUE);
            WinSetFocus( HWND_DESKTOP, hwnd);
            return( (MRESULT)TRUE);

        case WM_UPDATE :
            usPage = SHORT1FROMMP( mp1);
            pjob = WinQueryWindowPtr( hwnd, 0);
            sprintf( dlgstr, pjob->pszPrString2, usPage);
            WinSetDlgItemText( hwnd, PRT_PROG_TEXT2, dlgstr);
            return(0L);
        
        case WM_STOPME :
            pjob = WinQueryWindowPtr( hwnd, 0);
            FREE( pjob);
            WinDismissDlg( hwnd, 0);
            WinSetFocus( HWND_DESKTOP, pShrMem->hwndProg);
            DosPostEventSem( HevShr);
            return(0L);
        
        default :
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        } // end of switch

    } // end of PrtprogressDlgProc()

//
// **********************************************************************

VOID PrtGetPrinterList( )

// **********************************************************************

    {
    SPLERR          splerr;
    ULONG           cbBuf;
    ULONG           cTotal;
    ULONG           cReturned;
    ULONG           cbNeeded;
    ULONG           ulCount;
    ULONG           level = 4L;
    ULONG           i,cnt;
    USHORT          j, usJobs;
    PSZ             computer_name = NULL;
    PBYTE           pbuffer = NULL;
    PPRQINFO3       prq;
    PPRJINFO2       prj;
    char            *p;
    LONG            buflen,                                                     /* E00001 */
                    devrc;                                                      /* E00001 */
    
    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);                    /* E00001 */
                                                                                /* E00001 */
    pPrtList.prt_count = 0;                                                     /* E00001 */
    
    /***** Clear array of printer names *********************************/
    
    for ( i = 0; i < MAX_OPEN_DEVS; i++)
        FREE( pPrtList.szPrinterList[ i]);
    
    /******* 1. Get size of data for queues *****************************/

    splerr = SplEnumQueue( computer_name, level, pbuffer, 0L,
                          &cReturned, &cTotal, &cbNeeded, NULL);

    if ( (splerr == ERROR_MORE_DATA) || (splerr == NERR_BufTooSmall) )
        {
        pbuffer = (PBYTE) malloc( cbNeeded);
        
        cbBuf = cbNeeded;

        /******* 2. Get all available queues ****************************/

        splerr = SplEnumQueue( computer_name, level, pbuffer, cbBuf,
                              &ulCount, &cTotal, &cbNeeded, NULL);

        if (splerr == NO_ERROR)
            {

            pPrtList.prt_count = ulCount;
            
            for ( cnt = 0; cnt < MAX_OPEN_DEVS; cnt++)
                {
                FREE( pPrtList.aDevStruct[ cnt].pszLogAddress);                 /* E00001 */
                FREE( pPrtList.aDevStruct[ cnt].pszDriverName);                 /* E00001 */
                FREE( pPrtList.aDevStruct[ cnt].pdriv);                         /* E00001 */
                FREE( pPrtList.aDevStruct[ cnt].pszDataType);                   /* E00001 */
                } /* end of for */                                              /* E00001 */
                                                                                /* E00001 */
            /******* 3. Point to beginning of list **********************/

            prq = (PPRQINFO3)pbuffer;

            /******* 4. Extract required data ***************************/

            if( pPrtList.prt_count > MAX_OPEN_DEVS)
                pPrtList.prt_count = MAX_OPEN_DEVS;

            for ( i = 0; i < pPrtList.prt_count; i++)
                {
                pPrtList.aDevStruct[ i].pszLogAddress = strdup( prq->pszName);  /* E00001 */
                TST_TRACE(( "PrtGetPrinterList: pszName = %s",                  /* E00001 */
                            pPrtList.aDevStruct[ i].pszLogAddress))             /* E00001 */

                TST_TRACE(( "PrtGetPrinterList: prq->pszDriverName = %s", 
                            prq->pszDriverName))
                p = strchr( prq->pszDriverName, (int)'.');
                if ( p)
                    *p = '\0';
    
                pPrtList.aDevStruct[ i].pszDriverName = strdup( prq->pszDriverName); /* E00001 */
                TST_TRACE(( "PrtGetPrinterList: Driver Name = %s", prq->pszDriverName)) /* E00001 */
                                                                                /* E00001 */
                pPrtList.aDevStruct[ i].pszDataType = strdup( "PM_Q_STD");      /* E00001 */
                                                                                /* E00001 */
                pPrtList.szPrinterList[ i] = strdup( prq->pszComment);          /* E00001 */
                                                                                /* E00001 */

                buflen = DevPostDeviceModes( hab,                               /* E00001 */
                                             NULL,                              /* E00001 */
                                             pPrtList.aDevStruct[ i].pszDriverName, /* E00001 */
                                             prq->pDriverData->szDeviceName,    /* E00001 */
                                             pPrtList.aDevStruct[ i].pszLogAddress, /* E00001 */
                                             DPDM_POSTJOBPROP);                 /* E00001 */

                if( buflen <= 0)                                                /* E00001 */
                    {                                                           /* E00001 */
                    char str[ 128];                                             /* E00001 */
                    
                    sprintf( str, "Error getting driver data for %s", prq->pszComment); /* E00001 */
                    WinMessageBox( HWND_DESKTOP, HWND_DESKTOP,                  /* E00001 */
                                   str, "ERROR", 0, MB_CANCEL | MB_MOVEABLE | MB_ERROR); /* E00001 */
                    FREE( pbuffer);                                             /* E00001 */
                    DosReleaseMutexSem( pPrtList.hmtx);                         /* E00001 */
                    WinPostMsg( pShrMem->hwnd, WM_QUIT, 0L, 0L);                /* E00001 */
                    return;                                                     /* E00001 */
                    }                                                           /* E00001 */
                                                                                /* E00001 */
                pPrtList.aDevStruct[ i].pdriv = ( PDRIVDATA) malloc( buflen);   /* E00001 */
//                memcpy( pPrtList.aDevStruct[ i].pdriv, prq->pDriverData, prq->pDriverData->cb); /* E00001 */
                                                                                /* E00001 */
                devrc = DevPostDeviceModes( hab,                                /* E00001 */
                                            pPrtList.aDevStruct[ i].pdriv,      /* E00001 */
                                            pPrtList.aDevStruct[ i].pszDriverName, /* E00001 */
                                            prq->pDriverData->szDeviceName,     /* E00001 */
                                            pPrtList.aDevStruct[ i].pszLogAddress, /* E00001 */
                                            DPDM_QUERYJOBPROP);                 /* E00001 */

                if( devrc != DEV_OK)                                            /* E00001 */
                    {                                                           /* E00001 */
                    char str[ 128];                                             /* E00001 */
                    
                    sprintf( str, "Error getting driver data for %s", prq->pszComment); /* E00001 */
                    WinMessageBox( HWND_DESKTOP, HWND_DESKTOP,                  /* E00001 */
                                   str, "ERROR", 0, MB_CANCEL | MB_MOVEABLE | MB_ERROR); /* E00001 */
                    FREE( pbuffer);                                             /* E00001 */
                    DosReleaseMutexSem( pPrtList.hmtx);                         /* E00001 */
                    WinPostMsg( pShrMem->hwnd, WM_QUIT, 0L, 0L);                /* E00001 */
                    return;                                                     /* E00001 */
                    }                                                           /* E00001 */
                                                                                /* E00001 */
                if (( prq->fsType & PRQ3_TYPE_APPDEFAULT) == PRQ3_TYPE_APPDEFAULT) /* E00001 */
                    pPrtList.def_prt = i;
                    
                usJobs = prq->cJobs;
                prq++;
                prj = ( PPRJINFO2)prq;
                for ( j=0; j < usJobs; j++)
                    prj++;              
                prq = ( PPRQINFO3)prj;
                }

            }

        FREE( pbuffer);

        }

    DosReleaseMutexSem( pPrtList.hmtx);                                         /* E00001 */

    } // end of PrtGetPrinterList()

/*************************************************************************
**
**  (c)1996 ADD Consulting
**
**  END OF FILE.
**
*************************************************************************/
