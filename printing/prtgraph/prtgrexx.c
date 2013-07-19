// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   prtgrexx.c  $
// $Revision:   1.1  $
// $Date:   02 Oct 1996 10:23:56  $
//
// $Log:   M:\prtgraph\prtgrexx.c_v  $
// 
//    Rev 1.1   02 Oct 1996 10:23:56   KANIS
// Fix for Job property dialogs
// Changes marked with "E00001"
// 
//    Rev 1.0   04 May 1996 21:09:36   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

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
#define     INCL_REXXSAA

#include    <os2.h>
#include    <bseerr.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdio.h>
#include    <ctype.h>
#include    <rexxsaa.h>
#include    <tstngen.h>
#include    "prtgrexx.h"
#include    "prt_int.h"
#include    "prt_dlg.h"
#include    "varpool.h"

char    tag1[] = "AAA4619";
ULONG   demo = 0XFFFFFFFF;
PSZ     module_name = "PRTGRAPH";
BOOL    use_hook = FALSE;

// **********************************************************************
// Global Variables
// **********************************************************************

extern  PSHR_MEM_BLOCK  pShrMem;        // Shared mem for dialogs
extern  HMTX            HmtxShr;        // Access semaphore for shared mem
extern  HEV             HevShr;         // Synch semaphore for shared mem
extern  PVOID           pvShrObject = NULL;

extern PRT_LIST     pPrtList;   // List of printer data

BOOL            bPM = FALSE;    // If TRUE working in PM environment

// **********************************************************************
// Colour definition table
// **********************************************************************

extern COLOURS     col_arr[];

// **********************************************************************
// Properties list.
// **********************************************************************

OBJ_PROP    properties[] =
    {
    "LEFTMARGIN", FALSE,
    "RIGHTMARGIN", FALSE,
    "TOPMARGIN", FALSE,
    "BOTTOMMARGIN", FALSE,
    "PAGEWIDTH", FALSE,
    "PAGEHEIGHT", FALSE,
    "PRINTING", FALSE,
    "CURRENTPRINTER", FALSE,
    "CURRENTDEVICE", FALSE,
    "LINESPACE", TRUE, 
    "VERSION", FALSE,
    "PRINTCOLOR", TRUE,
    "COLORENABLED", TRUE,
    "MEASURES", TRUE,
    "PAGENUM", FALSE,
    "JOBNAME", FALSE,
    "DEFAULTPRINTER", FALSE,
    "MINLEFTMAR", FALSE,
    "MINRIGHTMAR", FALSE,
    "MINTOPMAR", FALSE,
    "MINBOTTOMMAR", FALSE,
    "FORMNAME", FALSE,
    "FORMWIDTH", FALSE,
    "FORMHEIGHT", FALSE,
    "WORDBREAK", TRUE,
    "SHOWPROGRESS", TRUE,
    "XPOS", FALSE,
    "YPOS", FALSE,
    "XPOSTWIPS", FALSE,
    "YPOSTWIPS", FALSE
    };

// **********************************************************************
// REXX Interface function list.
// **********************************************************************

PSZ  RxFncTable[] =
    {
    "PrtGRxLoadFuncs",
    "PrtGRxClosePrintJob",
    "PrtGRxOpenPrintJob",
    "PrtGRxAbortPrintJob",
    "PrtGRxSetMargins",
    "PrtGRxSetLineSpace",
    "PrtGRxSetHeader",
    "PrtGRxSetFooter",
    "PrtGRxSetHeaderMode",
    "PrtGRxSetHdrLineFont",
    "PrtGRxSetHeaderLineFont",
    "PrtGRxWriteln",
    "PrtGRxJustRight",
    "PrtGRxJustified",
    "PrtGRxCentre",
    "PrtGRxWrite",
    "PrtGRxBox",
    "PrtGRxDrawLine",
    "PrtGRxPrintLine",
    "PrtGRxPrintRight",
    "PrtGRxPrintJustified",
    "PrtGRxPrintCentered",
    "PrtGRxPrintLeft",
    "PrtGRxPrintBox",
    "PrtGRxPrintFile",
    "PrtGRxTab",
    "PrtGRxGoTo",
    "PrtGRxGoToX",
    "PrtGRxGoToY",
    "PrtGRxGotoTab",
    "PrtGRxMoveX",
    "PrtGRxMoveY",
    "PrtGRxStartTable",
    "PrtGRxDefineTable",
    "PrtGRxStartRow",
    "PrtGRxStartCol",
    "PrtGRxEndRow",
    "PrtGRxEndTable",
    "PrtGRxNewPage",
    "PrtGRxPrinterList",
    "PrtGRxSetPrinter",
    "PrtGRxPrinterDlg",
    "PrtGRxFontDlg",
    "PrtGRxJobProps",
    "PrtGRxPrinterDialog",
    "PrtGRxFontDialog",
    "PrtGRxJobProperties",
    "PrtGRxInit",
    "PrtGRxTerm",
    "PrtGRxVersion",
    "PrtGRxBitMap",
    "PrtGRxPrintBitmap",
    "PrtGRxPrintWinImage",
    "PrtGRxPrintJPEG",
    "PrtGRxGetPageSize",
    "PrtGRxCurrentPrinter",
    "PrtGRxCurrentDevice",
    "PrtGRxResetColHeader",
    "PrtGRxResetHeader",
    "PrtGRxBlockFits",
    "PrtGRxLineFits",
    "PrtGRxStringLength",
    "PrtGRxSetProgressTexts",
    "PrtGRxGet",
    "PrtGRxSet",
    "PrtGRxLoadResMod",
    "PrtGRxFreeResMod",
    "PrtGRxPrintBullet",
    "PrtGRxDropFuncs"
    };


/*
 * PrtGRxLoadFuncs
 */
 
ULONG APIENTRY PrtGRxLoadFuncs( CHAR      *name, 
                                ULONG     numargs, 
                                RXSTRING  args[],
                                CHAR      *queuename, 
                                RXSTRING  *retstr)
 
    { 
    USHORT      entries,
                j;
    
    BUILDRXSTRING( retstr, "0")
    
    if( numargs != 0)
        return INVALID_ROUTINE;

    entries = sizeof(RxFncTable)/sizeof(PSZ);

    /***** Loop registering the functions with REXX enviroment **********/
    
    for (j = 1; j < entries; j++) 
        RexxRegisterFunctionDll( RxFncTable[j], "PRTGRAPH", RxFncTable[j]);
    
    /***** Allocate the buffers *****************************************/
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;

    } // end of PrtGRxLoadFuncs()

/*
 * PrtGRxDropFuncs
 */

ULONG APIENTRY PrtGRxDropFuncs( CHAR      *name, 
                                ULONG     numargs, 
                                RXSTRING  args[],
                                CHAR      *queuename, 
                                RXSTRING  *retstr)
 
    { 
    
    INT         entries;                      /* Num of entries             */
    INT         j;                            /* Counter                    */

    BUILDRXSTRING( retstr, "0")
    
    /***** Check Arguments **********************************************/
    
    if( numargs != 0)
        return INVALID_ROUTINE;

    entries = sizeof(RxFncTable)/sizeof(PSZ);

    TST_TRACE(( "PrtGRxDropFuncs: remove %u entries", entries))
        
    /***** Loop registering the functions with REXX enviroment **********/
    
    for (j = 0; j < entries; j++) 
        RexxDeregisterFunction( RxFncTable[j]);
    
    TST_TRACE(( "PrtGRxDropFuncs: entries removed"))

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;

    } // end of PrtGRxDropFuncs()

/*
 * PrtGRxInit
 */
 
ULONG APIENTRY PrtGRxInit( CHAR      *name,
                           ULONG     numargs,
                           RXSTRING  args[],
                           CHAR      *queuename,
                           RXSTRING  *retstr)
 
    { 
    PJOB_TYPE       pjob;
    char            *dummy, 
                    buffer[ 35];
    ULONG           ulPC;
    HWND            hwnd;
    char            str[ 128];
    
    BUILDRXSTRING( retstr, "0")

    if (numargs > 0)
        {
        bPM = TRUE;
        hwnd = ( HWND)strtoul( args[ 0].strptr, &dummy, 0);
        }
    else
        bPM = FALSE;
        
    pjob = PrtObjectInit( );

    if( !bPM)
        {
        if( !PrtStartDaemon())
            {
            printf( "Failed to start PM Daemon...\n\nCannot start PRTGRAPH\n\n");
            return VALID_ROUTINE;
            }

        pjob->hab = WinQueryAnchorBlock( HWND_DESKTOP);
        DosRequestMutexSem( HmtxShr, SEM_INDEFINITE_WAIT);
        pjob->hwnd = pShrMem->hwnd;

        if( demo)
            {
            DosResetEventSem( HevShr, &ulPC);
            WinPostMsg( pjob->hwnd, WM_SHAREWARE, 0L, 0L);
            DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);
            }

        DosReleaseMutexSem( HmtxShr);
        }
    else
        {
        pjob->hwnd = hwnd;
        pjob->hab = WinQueryAnchorBlock( hwnd);
        if( pjob->hab == NULLHANDLE)
            {
            sprintf( str, "Failed to get anchor block for window %lu\nCannot Initialise PrtGraph", pjob->hwnd);
            WinMessageBox( HWND_DESKTOP, 
                           HWND_DESKTOP, 
                           str, 
                           "PrtGraph - ERROR", 
                           0, MB_ENTER | MB_ICONHAND | MB_SYSTEMMODAL | MB_MOVEABLE);
            PrtObjectDestroy( pjob);
            return VALID_ROUTINE;
            }
        if( demo)
            {
            char    demo_str[ 256];
            PSZ     d_str = "This is an unregistered version of\n"
                            "PRTGRAPH.DLL v %s\n\n"
                            "This product is shareware and can be "
                            "registered through CompuServe or by "
                            "contacting the address in the online "
                            "programming help\n\n"
                            "¸1995, 1996 ADD Consulting (CH)";

            sprintf( demo_str, d_str, VER_NUM);
            WinMessageBox( HWND_DESKTOP, 
                           HWND_DESKTOP,
                           demo_str,
                           "PrtGraph - Unregistered Version",
                           0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);

            } // end of demo block
        }

    dummy = ltoa( (LONG)pjob, buffer, 10);
    BUILDRXSTRING( retstr, dummy)
    return VALID_ROUTINE;
    
    } // end of PrtGRxInit()

/*
 * PrtGRxTerm
 */
 
ULONG APIENTRY PrtGRxTerm( CHAR      *name,
                           ULONG     numargs,
                           RXSTRING  args[],
                           CHAR      *queuename,
                           RXSTRING  *retstr)
 
    { 
    PJOB_TYPE       pjob;

    BUILDRXSTRING( retstr, "0")
    
    if (numargs < 1)
        return INVALID_ROUTINE;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    /***** Close object window ******************************************/

    PrtObjectDestroy( pjob);
    if( !bPM)
        PrtReleaseDaemon();

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
    
    } // end of PrtGRxTerm()

/*
 *  PrtGRxClosePrintJob
 */

ULONG APIENTRY PrtGRxClosePrintJob( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
    {
    PJOB_TYPE    pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( pjob->bPrinting)
        {
        PrtClose( pjob);
        BUILDRXSTRING( retstr, "1")
        }
        
    return VALID_ROUTINE;
    
    }

/*
 *  PrtGRxDefineTable
 */

ULONG APIENTRY PrtGRxDefineTable( CHAR *name,
                                  ULONG argc,
                                  RXSTRING argv[],
                                  CHAR *queuename,
                                  RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    ULONG       i, j, k;
    POINTL      ptl;
    BOOL        bRes;
    ULONG       left_mar,
                wide;
    USHORT      cols;    
    PSZ         dummy,
                tstem,
                cstem;
    char        cstem_cpx[ 128];
    
    BUILDRXSTRING( retstr, "0")

    if (argc != 3)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if ( !RXNULLSTRING( argv[ 1]))
        tstem = argv[ 1].strptr;
    else
        return INVALID_ROUTINE;

    if ( !RXNULLSTRING( argv[ 2]))
        cstem = argv[ 2].strptr;
    else
        return INVALID_ROUTINE;

    sprintf( cstem_cpx, "%s0.", cstem);
    cols = StemFetchLong( cstem_cpx, 0, &bRes);

    if ( !bRes || !cols)  return TRUE;

    /***** Create table structure ***************************************/
    
    pjob->pdata->pt_table = PrtCreateTable( ( int)cols);

    TST_TRACE(( "DefineTable: Created table struct %p", pjob->pdata->pt_table))

    TST_TRACE(( "DefineTable: table def - %s column def %s", tstem, cstem))

    k = StemFetchLong( tstem, 0, &bRes);
    if ( !bRes || !(( k == 11) || ( k == 17))) goto ERROR_EXIT;
    
    pjob->pdata->pt_table->lfill = StemFetchLong( tstem, 1, &bRes);
    if ( !bRes) goto ERROR_EXIT;

    pjob->pdata->pt_table->lline_type = StemFetchLong( tstem, 2, &bRes);
    if ( !bRes) goto ERROR_EXIT;

    pjob->pdata->pt_table->bHeader = StemFetchLong( tstem, 3, &bRes);
    if ( !bRes)  goto ERROR_EXIT;
    
    if( pjob->pdata->pt_table->bHeader)
        {
        pjob->pdata->pt_table->lhfill = StemFetchLong( tstem, 4, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        pjob->pdata->pt_table->lhline_type = StemFetchLong( tstem, 5, &bRes);
        if ( !bRes) goto ERROR_EXIT;

        pjob->pdata->pt_table->bAllPages = StemFetchLong( tstem, 6, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        pjob->pdata->pt_table->lpts = StemFetchLong( tstem, 7, &bRes);
        if ( !bRes) goto ERROR_EXIT;

        dummy = StemFetchString( tstem, 8, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        strcpy( pjob->pdata->pt_table->cFont, dummy);
        FREE( dummy)
        }

    left_mar = StemFetchLong( tstem, 9, &bRes) * pjob->unit_conv;
    if ( !bRes)  goto ERROR_EXIT;

    pjob->pdata->pt_table->boxtype = StemFetchLong( tstem, 10, &bRes);
    if ( !bRes)  goto ERROR_EXIT;
    
    pjob->pdata->pt_table->hboxtype = StemFetchLong( tstem, 11, &bRes);
    if ( !bRes)  goto ERROR_EXIT;
    
    if ( k == 17)
        {
        dummy = StemFetchString( tstem, 12, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->ltcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->ltcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->ltcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->ltcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->ltcolor = pjob->lColor;
        
        dummy = StemFetchString( tstem, 13, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->llcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->llcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->llcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->llcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->llcolor = pjob->lColor;
        
        dummy = StemFetchString( tstem, 14, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->lfcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->lfcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->lfcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->lfcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->lfcolor = pjob->lColor;
        
        dummy = StemFetchString( tstem, 15, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->lhtcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->lhtcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->lhtcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->lhtcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->lhtcolor = pjob->lColor;
        
        dummy = StemFetchString( tstem, 16, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->lhlcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->lhlcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->lhlcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->lhlcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->lhlcolor = pjob->lColor;
        
        dummy = StemFetchString( tstem, 17, &bRes);
        if ( !bRes)
            pjob->pdata->pt_table->lhfcolor = pjob->lColor;
        else if ( dummy)
            {
            pjob->pdata->pt_table->lhfcolor = ColorToIndex( dummy);
            if( pjob->pdata->pt_table->lhfcolor == CLR_NOINDEX)
                pjob->pdata->pt_table->lhfcolor = pjob->lColor;
            FREE( dummy)
            } /* end of if */
        else
            pjob->pdata->pt_table->lhfcolor = pjob->lColor;

        } /* end of if */
    else
        {
        pjob->pdata->pt_table->ltcolor = pjob->lColor;
        pjob->pdata->pt_table->llcolor = pjob->lColor;
        pjob->pdata->pt_table->lfcolor = pjob->lColor;
        pjob->pdata->pt_table->lhtcolor = pjob->lColor;
        pjob->pdata->pt_table->lhlcolor = pjob->lColor;
        pjob->pdata->pt_table->lhfcolor = pjob->lColor;
        } /* end of else */
    

    left_mar += pjob->pdata->pt_lmargin;
    
    for ( j = 1; j <= cols; j++)
        {
        i = j - 1;
        sprintf( cstem_cpx, "%s%d.", cstem, j);
        TST_TRACE(( "DefineTable: create columns %lu from %s", i, cstem_cpx))
        wide = StemFetchLong( cstem_cpx, 1, &bRes) * pjob->unit_conv;
        if ( !bRes)
            {
            TST_TRACE(( "DefineTable: failed to get data from %s1", cstem_cpx))
            goto ERROR_EXIT;
            }
        pjob->pdata->pt_table->aCol[ i].llm_box = left_mar;
        left_mar += wide;

        pjob->pdata->pt_table->aCol[ i].lrm_box = left_mar;

        dummy = StemFetchString( cstem_cpx, 2, &bRes);
        if ( !bRes)
            {
            TST_TRACE(( "DefineTable: failed to get data from %s2", cstem_cpx))
            goto ERROR_EXIT;
            }

        pjob->pdata->pt_table->aCol[ i].pszHeader = strdup( dummy);
        TST_TRACE(( "DefineTable: free dummy (%s)", dummy))
        FREE( dummy)
        
        pjob->pdata->pt_table->aCol[ i].llm_text = pjob->pdata->pt_table->aCol[ i].llm_box + 
                                                   pjob->pdata->pt_table->lline_type;
        pjob->pdata->pt_table->aCol[ i].lrm_text = pjob->pdata->pt_table->aCol[ i].lrm_box - 
                                                   pjob->pdata->pt_table->lline_type;

        pjob->pdata->pt_table->aCol[ i].lrm_text -= (ONE_MIL * 2);
        pjob->pdata->pt_table->aCol[ i].llm_text += (ONE_MIL * 2);

        pjob->pdata->pt_table->aCol[ i].uslines = 0;
        pjob->pdata->pt_table->aCol[ i].usstart = 0;
        pjob->pdata->pt_table->aCol[ i].usnewpage = 0;
        pjob->pdata->pt_table->aCol[ i].lpts = pjob->pdata->pt_table->lpts;
        pjob->pdata->pt_table->aCol[ i].alines = NULL;
        strcpy( pjob->pdata->pt_table->aCol[ i].cFont, pjob->pdata->pt_table->cFont);
        
        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    pjob->pdata->pt_table->ptltr.x = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_table->usCols-1].lrm_box;
    pjob->pdata->pt_table->ptltr.y = ptl.y;
    pjob->pdata->pt_table->ly_pos = ptl.y;

    if( pjob->pdata->pt_table->bHeader)
        {
        if( PrtWriteTableHeader( pjob))
            BUILDRXSTRING( retstr, "1")
        else
            goto ERROR_EXIT;
        }
    else
        BUILDRXSTRING( retstr, "1")

    TST_TRACE(( "DefineTable: completed successfully"))

    return VALID_ROUTINE;

ERROR_EXIT:
    TST_TRACE(( "DefineTable: failed"))
    pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);
    return VALID_ROUTINE;

}


/*
 *  PrtGRxEndRow
 */

ULONG APIENTRY PrtGRxEndRow( CHAR *name,
                             ULONG argc,
                             RXSTRING argv[],
                             CHAR *queuename,
                             RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    USHORT      rc;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    rc = PrtEndRow( pjob);
    
    if( rc == PRTGR_OK)
        BUILDRXSTRING( retstr, "1")

    TST_TRACE(( "EndRow: returns %u", rc))

    return VALID_ROUTINE;

}

/*
 *  PrtGRxEndTable
 */

ULONG APIENTRY PrtGRxEndTable( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE       pjob;
    POINTL          ptl;

    BUILDRXSTRING( retstr, "0")

    TST_TRACE(( "EndTable: starts"))

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( pjob->pdata->pt_table == NULL)  
        return VALID_ROUTINE ;

    /***** Restore margins for page *************************************/
    
    pjob->pdata->pt_tmargin = pjob->pdata->pt_table->ptltr.y - (ONE_MIL * 2);

    ptl.x = pjob->pdata->pt_lmargin;
    ptl.y = pjob->pdata->pt_tmargin;
    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    
    pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);
    
    TST_TRACE(( "EndTable: freed table struct"))

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxGoTo
 */

ULONG APIENTRY PrtGRxGoTo( CHAR *name,
                           ULONG argc,
                           RXSTRING argv[],
                           CHAR *queuename,
                           RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    LONG        x, y;
    BOOL        bPoints = FALSE;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 3)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( pjob->pdata->pt_table != NULL)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 2]))
        return VALID_ROUTINE;

    if( argc > 3)
        if ( !RXNULLSTRING( argv[ 3]))
            bPoints = ( BOOL)atoi( argv[ 3].strptr);

    x = atol( argv[ 1].strptr);
    y = atol( argv[ 2].strptr);

    PrtGoto( pjob, x, y, bPoints);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxGoToX
 */

ULONG APIENTRY PrtGRxGoToX( CHAR *name,
                            ULONG argc,
                            RXSTRING argv[],
                            CHAR *queuename,
                            RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    LONG        x;
    BOOL        bPoints = FALSE;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( pjob->pdata->pt_table != NULL)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;

    if( argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            bPoints = ( BOOL)atoi( argv[ 2].strptr);

    x = atol( argv[ 1].strptr);

    PrtGotoX( pjob, x, bPoints);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxGoToY
 */

ULONG APIENTRY PrtGRxGoToY( CHAR *name,
                            ULONG argc,
                            RXSTRING argv[],
                            CHAR *queuename,
                            RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    LONG        y;
    BOOL        bPoints = FALSE;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( pjob->pdata->pt_table != NULL)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;

    if( argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            bPoints = ( BOOL)atoi( argv[ 2].strptr);

    y = atol( argv[ 1].strptr);

    PrtGotoY( pjob, y, bPoints);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxJobProperties
 */

ULONG APIENTRY PrtGRxJobProperties( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    ULONG       ulPC;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !bPM)
        {
        DosRequestMutexSem( HmtxShr, SEM_INDEFINITE_WAIT);

        PrtSetupShrMem( pjob);

        DosResetEventSem( HevShr, &ulPC);

        WinPostMsg( pjob->hwnd, WM_JOBDLG, MPFROMLONG( -1L), 0L);
        DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);
        memcpy( pjob->DevStruct.pdriv, &( pShrMem->drvData), pShrMem->drvData.cb);
        DosReleaseMutexSem( HmtxShr);
        }
    else
        {
        DevPostDeviceModes( pjob->hab,
                            pjob->DevStruct.pdriv,
                            pjob->DevStruct.pszDriverName,
                            pjob->DevStruct.pdriv->szDeviceName,
                            pjob->DevStruct.pszLogAddress,
                            DPDM_POSTJOBPROP);
        }
    
    PrtQueryQueueInfo( pjob);

    BUILDRXSTRING( retstr, "1")
    
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintJustified
 */

ULONG APIENTRY PrtGRxPrintJustified( CHAR *name,
                                     ULONG argc,
                                     RXSTRING argv[],
                                     CHAR *queuename,
                                     RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        rc;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        rc = PrtWriteCol( pjob, szFont, points, szString, JUST_JUSTIFY);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        rc = PrtWrite( pjob, szString, JUST_JUSTIFY);
        }

    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintCentered
 */

ULONG APIENTRY PrtGRxPrintCentered( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        rc;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        rc = PrtWriteCol( pjob, szFont, points, szString, JUST_CENTRE);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        rc = PrtCentre( pjob, szString);
        }

    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintRight
 */

ULONG APIENTRY PrtGRxPrintRight( CHAR *name,
                                 ULONG argc,
                                 RXSTRING argv[],
                                 CHAR *queuename,
                                 RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        rc;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        rc = PrtWriteCol( pjob, szFont, points, szString, JUST_RIGHT);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        rc = PrtJustRight( pjob, szString);
        }

    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintLeft
 */

ULONG APIENTRY PrtGRxPrintLeft( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        rc;
    
    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        rc = PrtWriteCol( pjob, szFont, points, szString, JUST_LEFT);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        rc = PrtWrite( pjob, szString, JUST_LEFT);
        }

    
    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintLine
 */

ULONG APIENTRY PrtGRxPrintLine( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        rc;
    
    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        rc = PrtWriteCol( pjob, szFont, points, szString, JUST_LEFT);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        rc = PrtWriteln( pjob, szString);
        }

    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxPrintBox
 */

ULONG APIENTRY PrtGRxPrintBox( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      bl, tr, ptl;
    LONG        th, fill, llc, lfc;
    USHORT      bt;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 6)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    
    if ( !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    else
        bl.x = ptl.x;

    if ( !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    else
        bl.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    else
        tr.x = pjob->pdata->pt_rmargin;

    if ( !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    else
        tr.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);
    else
        th = 28;

    if (argc > 6)
        if ( !RXNULLSTRING( argv[ 6]))
            fill = atol( argv[ 6].strptr);
        else
            fill = 0;
    else
        fill = 0;

    if (argc > 7)
        if ( !RXNULLSTRING( argv[ 7]))
            {
            llc = ColorToIndex( argv[ 7].strptr);
            if( llc == CLR_NOINDEX)
                llc = pjob->lColor;
            }
        else
            llc = pjob->lColor;
    else
        llc = pjob->lColor;

    if (argc > 8)
        if ( !RXNULLSTRING( argv[ 8]))
            {
            lfc = ColorToIndex( argv[ 8].strptr);
            if( lfc == CLR_NOINDEX)
                lfc = pjob->lColor;
            }
        else
            lfc = pjob->lColor;
    else
        lfc = pjob->lColor;

    if( argc > 9)
        {
        if ( !RXNULLSTRING( argv[ 9]))
            {
            bt = ( USHORT)atoi( argv[ 9].strptr);
            }
        else
            bt = BOX_ALL;
        }
    else
        bt = BOX_ALL;

    PrtBox( pjob, bl, tr, th, fill, bt, llc, lfc);

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxPrintBitmap
 */

ULONG APIENTRY PrtGRxPrintBitmap( CHAR *name,
                                  ULONG argc,
                                  RXSTRING argv[],
                                  CHAR *queuename,
                                  RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      bl, 
                tr,
                ptlhere;
    LONG        th,
                res,
                llc;
    HMODULE     hmod = NULLHANDLE;
    PSZ         file_name,
                p,
                title = NULL;
    BOOL        rc;

    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;
    
    file_name = argv[ 1].strptr;
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = pjob->lColor;

    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.x = (atol( argv[ 2].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    
    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        bl.y = (atol( argv[ 3].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.x = (atol( argv[ 4].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        tr.y = (atol( argv[ 5].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        th = atol( argv[ 6].strptr);

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        llc = atol( argv[ 7].strptr);
        
    if(( argc > 8) && !RXNULLSTRING( argv[ 8]))
        title = argv[ 8].strptr;

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        title = argv[ 7].strptr;

    if(( p = strchr( file_name, ( int)'$')) != NULL)
        {
        *p = '\0';
        p++;
        res = atol( p);
        if( strlen( file_name))
            hmod = ( HMODULE)atol( file_name);

        rc = PrtDrawBitMap2( pjob, hmod, res, bl, tr, th, llc, title);
        }
    else
        rc = PrtDrawBitMap( pjob, file_name, bl, tr, th, llc, title);

    if( rc)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;

}

/*
 *  PrtGRxPrintJPEG
 */

ULONG APIENTRY PrtGRxPrintJPEG( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      bl, 
                tr,
                ptlhere;
    LONG        th,
                llc;
    PSZ         file_name,
                title = NULL;

    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;
    
    file_name = argv[ 1].strptr;
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = pjob->lColor;

    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.x = (atol( argv[ 2].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    
    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        bl.y = (atol( argv[ 3].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.x = (atol( argv[ 4].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        tr.y = (atol( argv[ 5].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        th = atol( argv[ 6].strptr);

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        llc = atol( argv[ 7].strptr);
        
    if(( argc > 8) && !RXNULLSTRING( argv[ 8]))
        title = argv[ 8].strptr;

    if ( PrtDrawJPEG( pjob, file_name, bl, tr, th, llc, title))
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;

}

/*
 *  PrtGRxPrintFile
 */

ULONG APIENTRY PrtGRxPrintFile( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szFile,
                pszBuffer,
                szFont;
    LONG        points = 0;
    char        cStyle;
    BOOL        bFont = FALSE;
    BOOL        bPoint = FALSE;
    HFILE       hf;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 5)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    if( !RXNULLSTRING( argv[ 1]))
        {
        szFont = argv[ 1].strptr;
        bFont = TRUE;
        }

    /***** Get the font size ********************************************/
    
    if( !RXNULLSTRING( argv[ 2]))
        {
        points = atol( argv[ 2].strptr);
        bPoint = TRUE;
        }

    /***** Get the printing style ***************************************/
    
    if( !RXNULLSTRING( argv[ 3]))
        cStyle = *argv[ 3].strptr;
    else
        cStyle = 'L';

    /***** Get the file to print ****************************************/
    
    szFile = argv[ 4].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( bFont)
        if( !PrtSetFont( pjob, szFont))
            return VALID_ROUTINE;

    if( bPoint)
        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

    TST_TRACE(( "PrintFle: %s in %lu.%s in style %c", szFile, points, szFont, cStyle))
    hf = FileReset( szFile);
    TST_TRACE(( "PrintFle: opened file (%lu)", hf))

    if ( !hf)
        return VALID_ROUTINE;

    pszBuffer = ( PSZ) malloc( 8092);
    strcpy( pszBuffer, "");
    TST_TRACE(( "PrintFle: created buffer %p", pszBuffer))
    
    while ( !FileReadLn( hf, pszBuffer))
        {
        TST_TRACE(( "PrintFle: Read %s", pszBuffer))

        switch ( cStyle)
            {
            case 'C' :
                PrtCentre( pjob, pszBuffer);
                break;
            
            case 'J' :
                PrtWrite( pjob, pszBuffer, JUST_JUSTIFY);
                break;
            
            case 'R' :
                PrtJustRight( pjob, pszBuffer);
                break;
            
            default :
                PrtWriteln( pjob, pszBuffer);
                break;
            
            } /* end of switch cStyle */
        
        } /* end of while */
    
    DosClose( hf);
    
    FREE( pszBuffer)
        
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxStartCol
 */

ULONG APIENTRY PrtGRxStartCol( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    USHORT      uscol;

    BUILDRXSTRING( retstr, "0")

    if (argc != 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    uscol = ( USHORT) atoi( argv[ 1].strptr);

    if(uscol > pjob->pdata->pt_table->usCols)
        return VALID_ROUTINE;

    pjob->pdata->pt_col = uscol - 1;

    TST_TRACE(( "StartCol: set current column to %u", pjob->pdata->pt_col))

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxStartRow
 */

ULONG APIENTRY PrtGRxStartRow( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    pjob->pdata->pt_tmargin = pjob->pdata->pt_table->ly_pos;

    PrtFreeCells( pjob->pdata->pt_table);

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxStartTable
 */

ULONG APIENTRY PrtGRxStartTable( CHAR *name,
                                 ULONG argc,
                                 RXSTRING argv[],
                                 CHAR *queuename,
                                 RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    int         i, j, k;
    ULONG       left_mar,
                wide;
    POINTL      ptl;

    BUILDRXSTRING( retstr, "0")

    if (argc < 6)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Create table structure ***************************************/
    
    if ( !RXNULLSTRING( argv[ 3]))
        {
        j = atoi( argv[ 3].strptr);
        pjob->pdata->pt_table = PrtCreateTable( j);
        
        TST_TRACE(( "StartTable: created %d column entries %p", j, pjob->pdata->pt_table->aCol))
        }
    else
        return VALID_ROUTINE;

    if ( !RXNULLSTRING( argv[ 1]))
        pjob->pdata->pt_table->lfill = atol( argv[ 1].strptr);
    else
        pjob->pdata->pt_table->lfill = 0;

    if ( !RXNULLSTRING( argv[ 2]))
        pjob->pdata->pt_table->lline_type = atol( argv[ 2].strptr);
    else
        pjob->pdata->pt_table->lline_type = 0;

    
    if ( RXNULLSTRING( argv[ 4]))
        left_mar = 0L;
    else
        left_mar = atol( argv[ 4].strptr) * pjob->unit_conv;

    left_mar += pjob->pdata->pt_lmargin;
    
    if( pjob->pdata->pt_table->lline_type > 0)
        pjob->pdata->pt_table->boxtype = BOX_ALL;
    
    /***** Get column definitions ***************************************/
    
    if( argc != ( j + 5))
        {
        pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);
        return VALID_ROUTINE;
        }

    i = 5;  /* argument counter */

    pjob->pdata->pt_table->bFirstRow = TRUE;
    for( k = 0; k < j; k++)
        {
        
        TST_TRACE(( "StartTable: create column entry %d", k))

        /***** No empty args allowed ************************************/
        
        if ( RXNULLSTRING( argv[ i]))
            {
            pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);
            return VALID_ROUTINE;
            }
        
        wide = atol( argv[ i].strptr) * pjob->unit_conv;
        
        /***** Get left margin for column *******************************/
        
        pjob->pdata->pt_table->aCol[ k].llm_box = left_mar;

        left_mar += wide;
        
        /***** Calc right margin for column *****************************/
        
        pjob->pdata->pt_table->aCol[ k].lrm_box = left_mar;
        
        /***** Calculate text margins ***********************************/
        
        pjob->pdata->pt_table->aCol[ k].llm_text = pjob->pdata->pt_table->aCol[ k].llm_box + 
                                                   pjob->pdata->pt_table->lline_type;
        pjob->pdata->pt_table->aCol[ k].lrm_text = pjob->pdata->pt_table->aCol[ k].lrm_box - 
                                                   pjob->pdata->pt_table->lline_type;

        pjob->pdata->pt_table->aCol[ k].lrm_text -= (ONE_MIL * 2);
        pjob->pdata->pt_table->aCol[ k].llm_text += (ONE_MIL * 2);

        pjob->pdata->pt_table->aCol[ k].uslines = 0;
        pjob->pdata->pt_table->aCol[ k].usstart = 0;
        pjob->pdata->pt_table->aCol[ k].usnewpage = 0;
        pjob->pdata->pt_table->aCol[ k].lpts = 0;
        pjob->pdata->pt_table->aCol[ k].alines = NULL;
        strcpy( pjob->pdata->pt_table->aCol[ k].cFont, "");

        i++;
        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    pjob->pdata->pt_table->ptltr.x = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_table->usCols-1].lrm_box;
    pjob->pdata->pt_table->ptltr.y = ptl.y;
    pjob->pdata->pt_table->ly_pos = ptl.y;
    pjob->pdata->pt_table->ltcolor = pjob->lColor;
    pjob->pdata->pt_table->llcolor = pjob->lColor;
    pjob->pdata->pt_table->lfcolor = pjob->lColor;
    pjob->pdata->pt_table->lhtcolor = pjob->lColor;
    pjob->pdata->pt_table->lhlcolor = pjob->lColor;
    pjob->pdata->pt_table->lhfcolor = pjob->lColor;

    BUILDRXSTRING( retstr, "1")
    TST_TRACE(( "StartTable: completed successfully"))
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxSetHeader
 */

ULONG APIENTRY PrtGRxSetHeader( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    USHORT      cnt,
                lines,
                i;

    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !pjob->pdata->pt_header)
        return VALID_ROUTINE;

    lines = ( USHORT)atoi( argv[ 1].strptr);
    
    PrtInitHeader( pjob, lines);
    
    TST_TRACE(( "PrtGRxSetHeader: Create %u lines", pjob->pdata->pt_hlines))

    if ( argc < ( pjob->pdata->pt_hlines + 2))
        return INVALID_ROUTINE;

  
    for ( cnt = 0, i = 2; cnt < pjob->pdata->pt_hlines; cnt++, i++)
        {
        TST_TRACE(( "PrtGRxSetHeader: %s line %u", argv[ i].strptr, cnt))
        if ( !RXNULLSTRING( argv[ i]))
            pjob->pdata->pt_psz[ cnt].pszLine = strdup( argv[ i].strptr);
        else            
            pjob->pdata->pt_psz[ cnt].pszLine = strdup( "");

        /***** Set the default font *************************************/
        
        strcpy( pjob->pdata->pt_psz[ cnt].cfont, pjob->pdata->pt_hfont);
        pjob->pdata->pt_psz[ cnt].lpts = pjob->pdata->pt_hpts;
        
        } /* end of for */
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxSetHeaderMode
 */

ULONG APIENTRY PrtGRxSetHeaderMode( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    
    pjob->pdata->pt_header = ( BOOL) atol( argv[ 1].strptr);

    if ( pjob->pdata->pt_header)
        {
        if( argc > 2)
            {
            if ( !RXNULLSTRING( argv[ 2]))
                strcpy( pjob->pdata->pt_hfont, argv[ 2].strptr);
            else
                strcpy( pjob->pdata->pt_hfont, "Helvetica Bold");
            }

        if( argc > 3)
            {
            if ( !RXNULLSTRING( argv[ 3]))
                pjob->pdata->pt_hpts = atol( argv[ 3].strptr);
            else
                pjob->pdata->pt_hpts = 10;
            }

        if( argc > 4)
            {
            if ( !RXNULLSTRING( argv[ 4]))
                pjob->pdata->pt_hbox_mode = atol( argv[ 4].strptr);
            else
                pjob->pdata->pt_hbox_mode = 0;
            }

        if( argc > 5)
            {
            if ( !RXNULLSTRING( argv[ 5]))
                pjob->pdata->pt_hbox_line = atol( argv[ 5].strptr);
            else
                pjob->pdata->pt_hbox_line = 28;
            }

        if( argc > 6)
            {
            if ( !RXNULLSTRING( argv[ 6]))
                pjob->pdata->pt_allpages = ( BOOL) atol( argv[ 6].strptr);
            else
                pjob->pdata->pt_allpages = TRUE;
            }
                
        if( argc > 7)
            {
            if ( !RXNULLSTRING( argv[ 7]))
                {
                pjob->pdata->pt_hlcolor = ColorToIndex( argv[ 7].strptr);
                if( pjob->pdata->pt_hlcolor == CLR_NOINDEX)
                    pjob->pdata->pt_hlcolor = pjob->lColor;
                }
            else
                pjob->pdata->pt_hlcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_hlcolor = pjob->lColor;
                
        if( argc > 8)
            {
            if ( !RXNULLSTRING( argv[ 8]))
                {
                pjob->pdata->pt_hfcolor = ColorToIndex( argv[ 8].strptr);
                if( pjob->pdata->pt_hfcolor == CLR_NOINDEX)
                    pjob->pdata->pt_hfcolor = pjob->lColor;
                }
            else
                pjob->pdata->pt_hfcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_hfcolor = pjob->lColor;
                
        if( argc > 9)
            {
            if ( !RXNULLSTRING( argv[ 9]))
                {
                pjob->pdata->pt_htcolor = ColorToIndex( argv[ 9].strptr);
                if( pjob->pdata->pt_htcolor == CLR_NOINDEX)
                    pjob->pdata->pt_htcolor = pjob->lColor;
                }
            else
                pjob->pdata->pt_htcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_htcolor = pjob->lColor;

        if( argc > 10)
            {
            if ( !RXNULLSTRING( argv[ 10]))
                {
                pjob->pdata->pt_boxtype = ( USHORT)atoi( argv[ 10].strptr);
                }
            else
                pjob->pdata->pt_boxtype = BOX_ALL;
            }
        else
            pjob->pdata->pt_boxtype = BOX_ALL;

        } /* end of if */

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

/*
 *  PrtGRxSetFooter
 */

ULONG APIENTRY PrtGRxSetFooter( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 6)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !RXNULLSTRING( argv[ 1]))
        strcpy( pjob->pdata->pt_ffont, argv[ 1].strptr);
    else
        strcpy( pjob->pdata->pt_ffont, "Helvetica");
        
    if ( !RXNULLSTRING( argv[ 2]))
        pjob->pdata->pt_fpts = atol( argv[ 2].strptr);
    else
        pjob->pdata->pt_fpts = 8;

    if ( !RXNULLSTRING( argv[ 3]))
        pjob->pdata->pt_fbox_mode = atol( argv[ 3].strptr);
    else
        pjob->pdata->pt_fbox_mode = 0;

    if ( !RXNULLSTRING( argv[ 4]))
        pjob->pdata->pt_fbox_line = atol( argv[ 4].strptr);
    else
        pjob->pdata->pt_fbox_line = 0;

    if ( !RXNULLSTRING( argv[ 5]))
        strcpy( pjob->pdata->pt_footline, argv[ 5].strptr);
    else
        strcpy( pjob->pdata->pt_footline, "");
    
    if( argc > 6)
        {
        if ( !RXNULLSTRING( argv[ 6]))
            {
            pjob->pdata->pt_flcolor = ColorToIndex( argv[ 6].strptr);
            if( pjob->pdata->pt_flcolor == CLR_NOINDEX)
                pjob->pdata->pt_flcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_flcolor = pjob->lColor;
        }
    else
        pjob->pdata->pt_flcolor = pjob->lColor;
                
    if( argc > 7)
        {
        if ( !RXNULLSTRING( argv[ 7]))
            {
            pjob->pdata->pt_ffcolor = ColorToIndex( argv[ 7].strptr);
            if( pjob->pdata->pt_ffcolor == CLR_NOINDEX)
                pjob->pdata->pt_ffcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_ffcolor = pjob->lColor;
        }
    else
        pjob->pdata->pt_ffcolor = pjob->lColor;
                
    if( argc > 8)
        {
        if ( !RXNULLSTRING( argv[ 8]))
            {
            pjob->pdata->pt_ftcolor = ColorToIndex( argv[ 8].strptr);
            if( pjob->pdata->pt_ftcolor == CLR_NOINDEX)
                pjob->pdata->pt_ftcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_ftcolor = pjob->lColor;
        }
    else
        pjob->pdata->pt_ftcolor = pjob->lColor;

    if( argc > 9)
        {
        if ( !RXNULLSTRING( argv[ 9]))
            {
            pjob->pdata->pt_fboxtype = ( USHORT)atoi( argv[ 9].strptr);
            }
        else
            pjob->pdata->pt_fboxtype = BOX_ALL;
        }
    else
        pjob->pdata->pt_fboxtype = BOX_ALL;

    pjob->pdata->pt_footer = TRUE;

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxSetMargins
 */

ULONG APIENTRY PrtGRxSetMargins( CHAR *name,
                                 ULONG argc,
                                 RXSTRING argv[],
                                 CHAR *queuename,
                                 RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if (argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            pjob->pdata->pt_left_margin = (ULONG) atol( argv[ 1].strptr);

    if (argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            pjob->pdata->pt_right_margin = (ULONG) atol( argv[ 2].strptr);

    if (argc > 3)
        if ( !RXNULLSTRING( argv[ 3]))
            pjob->pdata->pt_top_margin = (ULONG) atol( argv[ 3].strptr);

    if (argc > 4)
        if ( !RXNULLSTRING( argv[ 4]))
            pjob->pdata->pt_bot_margin = (ULONG) atol( argv[ 4].strptr);

    if (argc > 5)
        {
        if ( !RXNULLSTRING( argv[ 5]))
            pjob->pdata->pt_border = atol( argv[ 5].strptr);
        else
            pjob->pdata->pt_border = 0;
        }
    else
        pjob->pdata->pt_border = 0;

    if (argc > 6)
        {
        if ( !RXNULLSTRING( argv[ 6]))
            pjob->pdata->pt_fill = atol( argv[ 6].strptr);
        else
            pjob->pdata->pt_fill = 0;
        }
    else
        pjob->pdata->pt_fill = 0;

    if (argc > 7)
        {
        if ( !RXNULLSTRING( argv[ 7]))
            {
            pjob->pdata->pt_blcolor = ColorToIndex( argv[ 7].strptr);
            if( pjob->pdata->pt_blcolor == CLR_NOINDEX)
                pjob->pdata->pt_blcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_blcolor = pjob->lColor;
        }
    else
        pjob->pdata->pt_blcolor = pjob->lColor;

    if (argc > 8)
        {
        if ( !RXNULLSTRING( argv[ 8]))
            {
            pjob->pdata->pt_bfcolor = ColorToIndex( argv[ 8].strptr);
            if( pjob->pdata->pt_bfcolor == CLR_NOINDEX)
                pjob->pdata->pt_bfcolor = pjob->lColor;
            }
        else
            pjob->pdata->pt_bfcolor = pjob->lColor;
        }
    else
        pjob->pdata->pt_bfcolor = pjob->lColor;

    if ( PrtCheckMargins( pjob))
        BUILDRXSTRING( retstr, "1")
            
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxSetPrinter
 */

ULONG APIENTRY PrtGRxSetPrinter( CHAR *name,
                                 ULONG argc,
                                 RXSTRING argv[],
                                 CHAR *queuename,
                                 RXSTRING *retstr)
        
{
    PJOB_TYPE       pjob;
    int             idx = 0;

    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !RXNULLSTRING( argv[ 1]))
        idx = atoi( argv[ 1].strptr);

    PrtSetPrinter( pjob, idx);    
    PrtQueryQueueInfo( pjob);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}

/*
 *  PrtGRxPrinterDialog
 */

ULONG APIENTRY PrtGRxPrinterDialog( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         pszBut;
    char        pszStem[ 128];
    ULONG       ulButs,
                ulPC;
    BOOL        res;
    
    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( argc > 1)
        {
        if( !RXNULLSTRING( argv[ 1]))
            strcpy( pjob->prt_tit, argv[ 1].strptr);
        else
            strcpy( pjob->prt_tit, "Choose Printer");
        }
    else        
        strcpy( pjob->prt_tit, "Choose Printer");
    
    if (( argc > 2) && !RXNULLSTRING( argv[ 2]))
        {
        strcpy( pszStem, argv[ 2].strptr);
        
        ulButs = StemFetchLong(  pszStem, 0, &res);
        if( ( ulButs == 3) && res)
            {
            pszBut = StemFetchString( pszStem, 1, &res);
            if( res && pszBut)
                strcpy( pjob->acDlgBut1, pszBut);
            FREE( pszBut)
            pszBut = StemFetchString( pszStem, 2, &res);
            if( res && pszBut)
                strcpy( pjob->acDlgBut2, pszBut);
            FREE( pszBut)
            pszBut = StemFetchString( pszStem, 3, &res);
            if( res && pszBut)
                strcpy( pjob->acDlgBut3, pszBut);
            FREE( pszBut)
            } /* end of if */
        
        } /* end of if */
    
    if( !bPM)
        {
        DosRequestMutexSem( HmtxShr, SEM_INDEFINITE_WAIT);
        PrtSetupShrMem( pjob);
        DosResetEventSem( HevShr, &ulPC);
        WinPostMsg( pjob->hwnd, WM_PRTDLG, 0L, 0L);
        DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);
    
        DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
        TST_TRACE(( "PrtGRxPrinterDialog : Got %s back from daemon", pShrMem->szPrtDlgRet))
        strcpy( pjob->szPrtDlgRet, pShrMem->szPrtDlgRet);

        if( strlen( pjob->szPrtDlgRet))
            {
            TST_TRACE(( "PrtGRxPrinterDialog : Copy return to default printer name"))
            strcpy( pjob->szPrinter, pjob->szPrtDlgRet);
            TST_TRACE(( "PrtGRxPrinterDialog : Get new index %u", pShrMem->prt_idx))
            pjob->prt_idx = pShrMem->prt_idx;
            TST_TRACE(( "PrtGRxPrinterDialog : Create new DevStruct"))
            PrtCreateDevStruct( pjob, pjob->prt_idx);
            TST_TRACE(( "PrtGRxPrinterDialog : Copy DrivData"))

            FREE( pjob->DevStruct.pdriv)

            pjob->DevStruct.pdriv = ( PDRIVDATA) malloc((size_t) pPrtList.aDevStruct[ pjob->prt_idx].pdriv->cb);
            memcpy( pjob->DevStruct.pdriv, &( pShrMem->drvData), pShrMem->drvData.cb);
            }

        DosReleaseMutexSem( HmtxShr);
        DosReleaseMutexSem( pPrtList.hmtx);
        }
    else
        {
        WinDlgBox( HWND_DESKTOP,
                   pjob->hwnd,
                   (PFNWP)PrtPrinterDlgProc,
                   pjob->hmod,
                   PRT_DLG_PRINTERS,
                   pjob);
        }

    BUILDRXSTRING( retstr, pjob->szPrtDlgRet)
    TST_TRACE(( "PrtGRxPrinterDialog : Cet new queue info"))
    PrtQueryQueueInfo( pjob);
    
    return VALID_ROUTINE;
}

/*
 *  PrtGRxFontDialog
 */

ULONG APIENTRY PrtGRxFontDialog( CHAR *name,
                                 ULONG argc,
                                 RXSTRING argv[],
                                 CHAR *queuename,
                                 RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    ULONG       ulPC;

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( argc > 1)
        {
        if( !RXNULLSTRING( argv[ 1]))
            strcpy( pjob->prt_tit, argv[ 1].strptr);
        else
            strcpy( pjob->prt_tit, "Choose Font");
        }
    else        
        strcpy( pjob->prt_tit, "Choose Font");

    if ( argc > 2)
        {
        if( !RXNULLSTRING( argv[ 2]))
            strcpy( pjob->pszFace, argv[ 2].strptr);
        else
            strcpy( pjob->pszFace, "");
        }
    else        
        strcpy( pjob->pszFace, "");

    if( !bPM)
        {
        PrtSetupShrMem( pjob);

        DosResetEventSem( HevShr, &ulPC);

        WinPostMsg( pjob->hwnd, WM_FONTDLG, 0L, 0L);

        DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);

        DosRequestMutexSem( HmtxShr, SEM_INDEFINITE_WAIT);
        strcpy( pjob->pszfont, pShrMem->pszfont);
        DosReleaseMutexSem( HmtxShr);
        }
    else
        {
        PrtChooseFont( pjob, pjob->prt_tit, pjob->pszFace);
        }

    BUILDRXSTRING( retstr, pjob->pszfont)

    return VALID_ROUTINE;
}

/*
 *  PrtGRxOpenPrintJob
 */

ULONG APIENTRY PrtGRxOpenPrintJob( CHAR *name,
                                   ULONG argc,
                                   RXSTRING argv[],
                                   CHAR *queuename,
                                   RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    ULONG       ulPC;
    USHORT      copies = 1;

    BUILDRXSTRING( retstr, "0")
    
    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !bPM)
        {
        if ( pjob->bPrinting)
            {
            printf( "PRTGRAPH - WARNING\n");
            if (argc > 1)
                if ( !RXNULLSTRING( argv[ 1]))
                    printf( "Cannot print job \"%s\"\n%s is busy\nJob \"%s\" is still printing\n\n", 
                             argv[ 1].strptr, pjob->szPrinter, pjob->pdata->doc_name);
                else
                    printf( "Cannot print new job\n%s is busy\nJob \"%s\" is still printing\n\n", 
                             pjob->szPrinter, pjob->pdata->doc_name);
            else
                printf( "Cannot print new job\n%s is busy\nJob \"%s\" is still printing\n\n", 
                         pjob->szPrinter, pjob->pdata->doc_name);
            return VALID_ROUTINE;
            } /* end of if */
        
        if ( demo)
            {
            DosResetEventSem( HevShr, &ulPC);
            WinPostMsg( pjob->hwnd, WM_SHAREWARE, 0L, 0L);
            DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);
            } /* end of if */
        }
    else
        {
        if ( pjob->bPrinting)
            {
            char    warning_str[ 256];
            
            if (argc > 1)
                if ( !RXNULLSTRING( argv[ 1]))
                    sprintf( warning_str, "Cannot print job \"%s\"\n%s is busy\nJob \"%s\" is still printing", 
                             argv[ 1].strptr, pjob->szPrinter, pjob->pdata->doc_name);
                else
                    sprintf( warning_str, "Cannot print new job\n%s is busy\nJob \"%s\" is still printing", 
                             pjob->szPrinter, pjob->pdata->doc_name);
            else
                sprintf( warning_str, "Cannot print new job\n%s is busy\nJob \"%s\" is still printing", 
                         pjob->szPrinter, pjob->pdata->doc_name);
            WinMessageBox( HWND_DESKTOP, 
                           pjob->hwnd,
                           warning_str,
                           "PrtGraph - WARNING",
                           0, MB_ERROR | MB_ENTER | MB_MOVEABLE);
            return TRUE;
            } /* end of if */
    
        if ( demo)
            {
            char    demo_str[ 256];
            PSZ     d_str = "This is an unregistered version of\n"
                            "PRTGRAPH.DLL v %s\n\n"
                            "This product is shareware and can be "
                            "registered through CompuServe or by "
                            "contacting the address in the online "
                            "programming help\n\n"
                            "¸1995, 1996 ADD Consulting (CH)";

            sprintf( demo_str, d_str, VER_NUM);
            WinMessageBox( HWND_DESKTOP, 
                           pjob->hwnd,
                           demo_str,
                           "PrtGraph - Unregistered Version",
                           0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
            
            } /* end of if */
        }

    /***** get the job title ********************************************/      /* E00001 */
    
    if (argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            strcpy( pjob->pdata->doc_name, argv[ 1].strptr);
        else
            strcpy( pjob->pdata->doc_name, "PrtGraph Document");
    else
        strcpy( pjob->pdata->doc_name, "PrtGraph Document");
    
    /***** Get the number of copies *************************************/
    
    if( argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            copies = (USHORT) atoi( argv[ 2].strptr);
    
    /***** Open the printer job *****************************************/
    
    if ( !PrtOpen( pjob, copies))
        return VALID_ROUTINE;

    /***** Set Header box ***********************************************/
    
    PrtSetHeaderBox( pjob);
    
    /***** Set page borders *********************************************/
    
    if ( pjob->pdata->pt_border)
        PrtSetBorder( pjob);
    
    PrtMakeTabs( pjob);
    
    /***** Start the job ************************************************/

    pjob->pdata->pt_page = 0;

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    PrtNewPage( pjob);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;

}

/*
 *  PrtGRxNewPage
 */

ULONG APIENTRY PrtGRxNewPage( CHAR *name,
                              ULONG argc,
                              RXSTRING argv[],
                              CHAR *queuename,
                              RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;
    
    if( !pjob->pdata->pt_table)
        PrtNewPage( pjob);
    else
        pjob->pdata->pt_table->bNewPage = TRUE;

    BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE;
}

/*
 *  PrtGRxPrinterList
 */

ULONG APIENTRY PrtGRxPrinterList( CHAR *name,
                                  ULONG argc,
                                  RXSTRING argv[],
                                  CHAR *queuename,
                                  RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    char        pStem[ 64];
    BOOL        ok = FALSE,
                err = FALSE;
    ULONG       i, j;

    BUILDRXSTRING( retstr, "0")

    /***** Check Arguments (should be > 2) ******************************/
    
    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    
    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;

    strcpy( pStem, argv[ 1].strptr);

    PrtGetPrinterList( );
    if( strlen( pStem))
        {
        DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
        if( StemSetValueLong(  pStem, 0L, pPrtList.prt_count))
            {
            for ( i = 0; i < pPrtList.prt_count; i++)
                {
                j = i + 1;
                if ( !StemSetValue(  pStem, j, pPrtList.szPrinterList[ i]))
                    err = TRUE;
                }
            ok = !err;
            }
        DosReleaseMutexSem( pPrtList.hmtx);
        }
    
    if ( ok)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE;
}

/*
 *  PrtGRxTab
 */

ULONG APIENTRY PrtGRxTab( CHAR *name,
                          ULONG argc,
                          RXSTRING argv[],
                          CHAR *queuename,
                          RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      ptl;
    USHORT      i;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get current position *****************************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    
    /***** Find the nearest tabulator ***********************************/
    
    i = 0;
    while (i < pjob->numtabs)
        {
        if ( pjob->tabs[ i] > ptl.x)
            {
            ptl.x = pjob->tabs[ i];
            i = pjob->numtabs;
            } /* end of if */
        else
            i++;
        } /* end of while */
    
    /***** Move to new tabulator ****************************************/

    GpiMove( pjob->pdata->pt_hps, &ptl);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxGotoTab
 */

ULONG APIENTRY PrtGRxGotoTab( CHAR *name,
                              ULONG argc,
                              RXSTRING argv[],
                              CHAR *queuename,
                              RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      ptl;
    USHORT      i;

    BUILDRXSTRING( retstr, "0")

    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return VALID_ROUTINE;

    i = atol( argv[ 1].strptr);

    if( i > pjob->numtabs)
        return VALID_ROUTINE ;

    /***** Get current position *****************************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    ptl.x = pjob->tabs[ i];
    
    /***** Move to new tabulator ****************************************/

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;
}

/*
 *  PrtGRxSetHeaderLineFont
 */

ULONG APIENTRY PrtGRxSetHeaderLineFont( CHAR *name,
                                        ULONG argc,
                                        RXSTRING argv[],
                                        CHAR *queuename,
                                        RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    int         index;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !pjob->pdata->pt_header)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 1]))
        return INVALID_ROUTINE;

    if ( pjob->pdata->pt_header && pjob->pdata->pt_hlines)
        {
        index = atoi( argv[ 1].strptr);
        if( !index || ( index > pjob->pdata->pt_hlines))
            return VALID_ROUTINE;

        index--;
        
        if ( argc > 2)
            if ( !RXNULLSTRING( argv[ 2]))
                strcpy( pjob->pdata->pt_psz[ index].cfont, argv[ 2].strptr);
        
        if ( argc > 3)
            if ( !RXNULLSTRING( argv[ 3]))
                pjob->pdata->pt_psz[ index].lpts = atol( argv[ 3].strptr);
        
        BUILDRXSTRING( retstr, "1")

        if( pjob->bPrinting)
            PrtSetHeaderBox( pjob);
        }

    return VALID_ROUTINE;
}


/*
 *  PrtGRxResetColHeader
 */

ULONG APIENTRY PrtGRxResetColHeader( CHAR *name,
                                     ULONG argc,
                                     RXSTRING argv[],
                                     CHAR *queuename,
                                     RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    USHORT      usCol;
    
    BUILDRXSTRING( retstr, "0")

    if (argc != 3)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( !pjob->pdata->pt_table)
        return VALID_ROUTINE;

    if ( !RXNULLSTRING( argv[ 1]))
        usCol = ( USHORT)atol( argv[ 1].strptr);
    else
        return INVALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 2]))
        return INVALID_ROUTINE;

    usCol--;
    
    PrtResetColHdr( pjob, usCol, argv[ 2].strptr);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}

/*
 *  PrtGRxResetHeader
 */

ULONG APIENTRY PrtGRxResetHeader( CHAR *name,
                                  ULONG argc,
                                  RXSTRING argv[],
                                  CHAR *queuename,
                                  RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         *strs;
    ULONG       cnt, i;

    BUILDRXSTRING( retstr, "0")
        
    if (argc < 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    cnt = argc - 1;
    strs = ( PSZ *) calloc( cnt, sizeof( PSZ));
    for( i = 0; i < cnt; i++)
        strs[ i] = argv[ i + 1].strptr;

    PrtResetHeader( pjob, cnt, strs);

    FREE( strs)
    
    if( pjob->bPrinting)
        PrtSetHeaderBox( pjob);

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}


/*
 *  PrtGRxAbortPrintJob
 */

ULONG APIENTRY PrtGRxAbortPrintJob( CHAR *name,
                                    ULONG argc,
                                    RXSTRING argv[],
                                    CHAR *queuename,
                                    RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;

    BUILDRXSTRING( retstr, "0")

    if (argc < 1)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( !pjob->bPrinting)
        return VALID_ROUTINE;
        
    PrtAbort( pjob);
    
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}

/*
 *  PrtGRxBlockFits
 */

ULONG APIENTRY PrtGRxBlockFits( CHAR *name,
                                ULONG argc,
                                RXSTRING argv[],
                                CHAR *queuename,
                                RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        ok = FALSE;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( pjob, szFont))
        return VALID_ROUTINE;

    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    ok = PrtCheckFits( pjob, szString);

    if ( ok)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;

}


/*
 *  PrtGRxSetProgressTexts
 */

ULONG APIENTRY PrtGRxSetProgressTexts( CHAR *name,
                                       ULONG argc,
                                       RXSTRING argv[],
                                       CHAR *queuename,
                                       RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         pszStem;
    PSZ         pszTitle = NULL,
                pszStr1 = NULL,
                pszStr2 = NULL,
                pszStr3 = NULL;
    ULONG       ul;
    BOOL        res;

    BUILDRXSTRING( retstr, "0")

    if ( argc != 2)
        return INVALID_ROUTINE;
    
    if( RXNULLSTRING( argv[ 0]))
        return INVALID_ROUTINE;
        
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    pszStem = argv[ 1].strptr;

    ul = StemFetchLong( pszStem, 0, &res);
    if( ( ul == 4) && res)
        {
        pszTitle = StemFetchString( pszStem, 1, &res);
        pszStr1 = StemFetchString( pszStem, 2, &res);
        pszStr2 = StemFetchString( pszStem, 3, &res);
        pszStr3 = StemFetchString( pszStem, 4, &res);

        PrtSetProgressTexts( pjob, pszTitle, pszStr1, pszStr2, pszStr3, NULL);

        FREE( pszTitle)

        FREE( pszStr1)

        FREE( pszStr2)

        FREE( pszStr3)

        } /* end of if */
    else
        return VALID_ROUTINE;

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}

/*
 *  PrtGRxLineFits
 */

ULONG APIENTRY PrtGRxLineFits( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points = 0;
    BOOL        ok = FALSE;

    BUILDRXSTRING( retstr, "0")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( pjob, szFont))
        return VALID_ROUTINE;

    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    ok = PrtLineFits( pjob, szString);

    if ( ok)
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxStringLength
 */

ULONG APIENTRY PrtGRxStringLength( CHAR *name,
                                   ULONG argc,
                                   RXSTRING argv[],
                                   CHAR *queuename,
                                   RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szFont;
    LONG        points;
    LONG        len;

    BUILDRXSTRING( retstr, "-1")
    
    if (argc != 4)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    /***** Get the font *************************************************/
    
    szFont = argv[ 1].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 2]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( pjob, szFont))
        return VALID_ROUTINE;

    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    len = PrtStringLength( pjob, szString);

    LongToRXString( len, retstr);

    return VALID_ROUTINE ;
}

/*
 *  PrtGRxGet
 */

ULONG APIENTRY PrtGRxGet( CHAR *name,
                          ULONG argc,
                          RXSTRING argv[],
                          CHAR *queuename,
                          RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         pszProp;
    USHORT      usProp;
    LONG        val;
    
    BUILDRXSTRING( retstr, "0")
    
    if (argc != 2)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( RXNULLSTRING( argv[ 1]))
        return INVALID_ROUTINE;

    pszProp = strupr( strdup( argv[ 1].strptr));

    usProp = FindProperty( pszProp);
    
    switch ( usProp)
        {
        case LEFTMARGIN :
            LongToRXString( pjob->pdata->pt_left_margin, retstr);
            break;

        case RIGHTMARGIN :
            LongToRXString( pjob->pdata->pt_right_margin, retstr);
            break;

        case TOPMARGIN :
            LongToRXString( pjob->pdata->pt_top_margin, retstr);
            break;

        case BOTTOMMARGIN :
            LongToRXString( pjob->pdata->pt_bot_margin, retstr);
            break;

        case PAGEWIDTH :
            val = pjob->pdata->pt_page_size.cx - 
                    ( ULONG)( pjob->pdata->pt_right_margin + pjob->pdata->pt_left_margin);
            LongToRXString( val, retstr);
            break;

        case PAGEHEIGHT :
            val = pjob->pdata->pt_page_size.cy - 
                    ( ULONG)( pjob->pdata->pt_top_margin + pjob->pdata->pt_bot_margin);
            LongToRXString( val, retstr);
            break;

        case PRINTING :
            LongToRXString( pjob->bPrinting, retstr);
            break;

        case CURRENTPRINTER :
            BUILDRXSTRING( retstr, pjob->szPrinter)
            break;

        case CURRENTDEVICE :
            BUILDRXSTRING( retstr, pjob->DevStruct.pszLogAddress)
            break;

        case LINESPACE :
            LongToRXString( ( LONG)pjob->usline_space, retstr);
            break;

        case VERSION :
            BUILDRXSTRING( retstr, VER_NUM)
            break;

        case PRINTCOLOR :
            BUILDRXSTRING( retstr, col_arr[ pjob->lColor].acClrN)
            break;

        case COLORENABLED :
            LongToRXString( pjob->bColor, retstr);
            break;

        case MEASURES :
            BUILDRXSTRING( retstr, pjob->pszMeasure)
            break;

        case PAGENUM :
            LongToRXString( ( LONG)pjob->pdata->pt_page, retstr);
            break;

        case JOBNAME :
            BUILDRXSTRING( retstr, pjob->pdata->doc_name)
            break;

        case DEFAULTPRINTER :
            PrtGetPrinterList( );
            DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
            BUILDRXSTRING( retstr, pPrtList.szPrinterList[ pPrtList.def_prt])
            DosReleaseMutexSem( pPrtList.hmtx);
            break;

        case MINLEFTMAR :
            LongToRXString( pjob->pdata->pt_min_lmargin, retstr);
            break;

        case MINRIGHTMAR :
            LongToRXString( pjob->pdata->pt_min_rmargin, retstr);
            break;

        case MINTOPMAR :
            LongToRXString( pjob->pdata->pt_min_tmargin, retstr);
            break;

        case MINBOTTOMMAR :
            LongToRXString( pjob->pdata->pt_min_bmargin, retstr);
            break;

        case FORMNAME :
            BUILDRXSTRING( retstr, pjob->pszForm)
            break;

        case FORMWIDTH :
            LongToRXString( pjob->pdata->pt_page_size.cx, retstr);
            break;

        case FORMHEIGHT :
            LongToRXString( pjob->pdata->pt_page_size.cy, retstr);
            break;

        case WORDBREAK :
            LongToRXString( pjob->bWordBreak, retstr);
            break;

        case SHOWPROGRESS :
            LongToRXString( pjob->bProgress, retstr);
            break;

        case XPOS :
            LongToRXString( PrtXPos( pjob), retstr);
            break;

        case YPOS :
            LongToRXString( PrtYPos( pjob), retstr);
            break;

        case XPOSTWIPS :
            LongToRXString( PrtXPosTwips( pjob), retstr);
            break;

        case YPOSTWIPS :
            LongToRXString( PrtYPosTwips( pjob), retstr);
            break;

        default :
            BUILDRXSTRING( retstr, "")
            return INVALID_ROUTINE;
        
        } // end of switch usProp
    
    return VALID_ROUTINE;
    }

/*
 *  PrtGRxSet
 */

ULONG APIENTRY PrtGRxSet( CHAR *name,
                          ULONG argc,
                          RXSTRING argv[],
                          CHAR *queuename,
                          RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         pszProp,
                pszVal;
    USHORT      usProp;
    USHORT      usVal;
    BOOL        bVal,
                ok;
    
    BUILDRXSTRING( retstr, "0")
    
    if (argc != 3)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if( RXNULLSTRING( argv[ 1]))
        return INVALID_ROUTINE;

    if( RXNULLSTRING( argv[ 2]))
        return INVALID_ROUTINE;

    pszProp = strupr( argv[ 1].strptr);
    pszVal = strupr( argv[ 2].strptr);
    usProp = FindProperty( pszProp);
    
    if ( usProp == PROP_NONE)
        return VALID_ROUTINE;
    
    if ( !properties[ usProp].bSet)
        return VALID_ROUTINE;
    
    switch ( usProp)
        {
        case LINESPACE :
            usVal = (USHORT)atoi( pszVal);
            ok = Set_LineSpace( pjob, usVal);
            break;

        case PRINTCOLOR :
            ok = Set_RxPrintColor( pjob, pszVal);
            break;

        case COLORENABLED :
            bVal = ( BOOL)atol( pszVal);
            pjob->bColor = bVal;
            break;

        case MEASURES :
            ok = Set_Measures( pjob, pszVal);
            break;

        case WORDBREAK :
            bVal = ( BOOL)atol( pszVal);
            pjob->bWordBreak = bVal;
            break;

        case SHOWPROGRESS :
            bVal = ( BOOL)atol( pszVal);
            pjob->bProgress = bVal;
            break;

        default :
            return INVALID_ROUTINE;
        
        } // end of switch usProp
    
    if( ok)
        BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;

    }

/*
 *  LongToRXString
 */

VOID LongToRXString( LONG  val, PRXSTRING var)

    {
    char    buffer[ 32],
            *p;
    
    p = _ltoa( val, buffer, 10);

    if ( p)
        BUILDRXSTRING( var, p)
    else
        BUILDRXSTRING( var, "")
    }

/*
 *  FindProperty
 */

USHORT FindProperty( PSZ    pszProp)

    {
    USHORT      res = 0,
                cnt = 0;
    BOOL        found = FALSE;
    
    while ( (cnt < PROP_NONE) && !found)
        {
        if ( !strcmp( properties[ cnt].acProp, pszProp))
            {
            found = TRUE;
            res = cnt;
            } // end of if
        
        cnt++;
        } // end of while
    
    return res;
    }

// **********************************************************************
// 
// Old functions still supported
// 
// **********************************************************************

/*
*************************************************************************/
 
ULONG APIENTRY PrtGRxVersion( CHAR      *name,
                              ULONG     numargs,
                              RXSTRING  args[],
                              CHAR      *queuename,
                              RXSTRING  *retstr)
 
/************************************************************************
*                                                                       *
* Description : Return version number of DLL                            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    
    BUILDRXSTRING( retstr, "0")
    if (numargs > 0)
        return INVALID_ROUTINE;

    BUILDRXSTRING( retstr, VER_NUM)
    return VALID_ROUTINE;

    } /* end of PrtGRxVersion() */

/*
*************************************************************************/
 
ULONG APIENTRY PrtGRxSetLineSpace( CHAR      *name,
                                   ULONG     numargs,
                                   RXSTRING  args[],
                                   CHAR      *queuename,
                                   RXSTRING  *retstr)
 
/************************************************************************
*                                                                       *
* Description : Set the margins for the print job                       *
*                                                                       *
* Parameters  : job_pointer (from PrtGRxInit)                           *
*               line_space (%)                                          *
*                                                                       *
* Return      : 1 ok 0 error                                            *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    
    BUILDRXSTRING( retstr, "0")
    
    /***** Check Arguments (should be > 2) ******************************/
    
    if (numargs < 1)
        return INVALID_ROUTINE;
    
    /***** Check 1st arguments ******************************************/
    
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if (numargs > 1)
        {
        if ( !RXNULLSTRING( args[ 1]))
            pjob->usline_space = (USHORT) atoi( args[ 1].strptr);
        else
            pjob->usline_space = LINE_SPACE;
        }
    else
        pjob->usline_space = LINE_SPACE;

    TST_TRACE(( "PrtGRxSetLineSpace: NOTE - Set line space to %u", pjob->usline_space))
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
    
    } /* end of PrtGRxSetLineSpace() */

/*
*************************************************************************/
 
ULONG APIENTRY PrtGRxCurrentPrinter( CHAR      *name,
                                     ULONG     numargs,
                                     RXSTRING  args[],
                                     CHAR      *queuename,
                                     RXSTRING  *retstr)
 
/************************************************************************
*                                                                       *
* Description : Return the name of the current printer                  *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    BUILDRXSTRING( retstr, "")

    /***** Check Arguments (should be > 2) ******************************/
    
    if (numargs < 1)
        return INVALID_ROUTINE;
    
    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    BUILDRXSTRING( retstr, pjob->szPrinter)
    return VALID_ROUTINE;
    
    } /* end of PrtGRxCurrentPrinter() */

/*
*************************************************************************/
 
ULONG APIENTRY PrtGRxCurrentDevice( CHAR      *name,
                                    ULONG     numargs,
                                    RXSTRING  args[],
                                    CHAR      *queuename,
                                    RXSTRING  *retstr)
 
/************************************************************************
*                                                                       *
* Description : Return The "printer" name for VX-REXX Charts            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    {
    PJOB_TYPE       pjob;
    
    BUILDRXSTRING( retstr, "")

    /***** Check Arguments (should be > 2) ******************************/
    
    if (numargs < 1)
        return INVALID_ROUTINE;
    
    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    BUILDRXSTRING( retstr, pjob->DevStruct.pszLogAddress)
    return VALID_ROUTINE;
    
    } /* end of PrtGRxCurrentDevice() */

/*
*************************************************************************/
 
ULONG APIENTRY PrtGRxGetPageSize( CHAR      *name,
                                  ULONG     numargs,
                                  RXSTRING  args[],
                                  CHAR      *queuename,
                                  RXSTRING  *retstr)
 
/************************************************************************
*                                                                       *
* Description : Return formatted string with page dimensions            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      : "page_width;page_height"                                *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    char            sizestr[ 128];
    LONG            wide, 
                    high;
    
    BUILDRXSTRING( retstr, ",")
    
    if (numargs < 1)
        return INVALID_ROUTINE;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    wide = pjob->pdata->pt_page_size.cx - 
            ( ULONG)(pjob->pdata->pt_right_margin + pjob->pdata->pt_left_margin);
    high = pjob->pdata->pt_page_size.cy - 
            ( ULONG)(pjob->pdata->pt_top_margin + pjob->pdata->pt_bot_margin);
    
    sprintf( sizestr, "%lu,%lu", wide, high);
    
    BUILDRXSTRING( retstr, sizestr)
    return VALID_ROUTINE;
   
    } /* end of PrtGRxGetPageSize() */

//
// **********************************************************************
 
ULONG APIENTRY PrtGRxPrintWinImage( CHAR      *name,
                                    ULONG     numargs,
                                    RXSTRING  args[],
                                    CHAR      *queuename,
                                    RXSTRING  *retstr)
 
// **********************************************************************
//
// Description : Print the image from a window
//
// Function    :
//
// Return      :
//
// **********************************************************************
 
    {
    PJOB_TYPE       pjob;
    HWND            hwnd;
    POINTL          ptlhere, bl, tr;
    LONG            th,
                    llc;
    PSZ             title = NULL;

    BUILDRXSTRING( retstr, "0")

    if( numargs < 1)
        return INVALID_ROUTINE;

    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( args[ 1]))
        return VALID_ROUTINE;

    hwnd = ( HWND)atol( args[ 1].strptr);
    
    if ( !hwnd)
        return VALID_ROUTINE;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = pjob->lColor;

    if(( numargs > 2) && !RXNULLSTRING( args[ 2]))
        bl.x = (atol( args[ 2].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    
    if(( numargs > 3) && !RXNULLSTRING( args[ 3]))
        bl.y = (atol( args[ 3].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( numargs > 4) && !RXNULLSTRING( args[ 4]))
        tr.x = (atol( args[ 4].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;

    if(( numargs > 5) && !RXNULLSTRING( args[ 5]))
        tr.y = (atol( args[ 5].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;

    if(( numargs > 6) && !RXNULLSTRING( args[ 6]))
        th = atol( args[ 6].strptr);

    if(( numargs > 7) && !RXNULLSTRING( args[ 7]))
        llc = atol( args[ 7].strptr);
        
    if(( numargs > 8) && !RXNULLSTRING( args[ 8]))
        title = args[ 8].strptr;

    if ( PrtDrawWindow( pjob, hwnd, bl, tr, th, llc, title))
        BUILDRXSTRING( retstr, "1")
    
    return VALID_ROUTINE;

    } // end of PrtGRxPrintWinImage()

//
// **********************************************************************
 
ULONG APIENTRY PrtGRxMoveX( CHAR      *name,
                            ULONG     numargs,
                            RXSTRING  args[],
                            CHAR      *queuename,
                            RXSTRING  *retstr)
 
// **********************************************************************
//
// Description : Move the cursor relatibve on X axis
//
// Function    :
//
// Return      :
//
// **********************************************************************
 
    {
    PJOB_TYPE       pjob;
    LONG            x;
    BOOL            bPoints = FALSE;
    
    BUILDRXSTRING( retstr, "0")

    if (numargs < 2)
        return INVALID_ROUTINE;
   
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;
   
    if( pjob->pdata->pt_table != NULL)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( args[ 1]))
        return VALID_ROUTINE;

    if( numargs > 2)
        if ( !RXNULLSTRING( args[ 2]))
            bPoints = ( BOOL)atoi( args[ 2].strptr);
        
    x = atol( args[ 1].strptr);

    PrtMoveX( pjob, x, bPoints);
        
    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;

    } // end of PrtGRxMoveX()

//
// **********************************************************************
 
ULONG APIENTRY PrtGRxMoveY( CHAR      *name,
                            ULONG     numargs,
                            RXSTRING  args[],
                            CHAR      *queuename,
                            RXSTRING  *retstr)
 
// **********************************************************************
//
// Description : Move cursor relative on Y axis
//
// Function    :
//
// Return      :
//
// **********************************************************************
 
    {
    PJOB_TYPE       pjob;
    LONG            y;
    BOOL            bPoints = FALSE;
    
    BUILDRXSTRING( retstr, "0")

    if (numargs < 2)
        return INVALID_ROUTINE;
   
    pjob = ( PJOB_TYPE) atol( args[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;
   
    if( pjob->pdata->pt_table != NULL)
        return VALID_ROUTINE;

    if ( RXNULLSTRING( args[ 1]))
        return VALID_ROUTINE;

    if( numargs > 2)
        if ( !RXNULLSTRING( args[ 2]))
            bPoints = ( BOOL)atoi( args[ 2].strptr);
        
    y = atol( args[ 1].strptr);

    PrtMoveY( pjob, y, bPoints);
            
    BUILDRXSTRING( retstr, "0")
    return VALID_ROUTINE;
    
    } // end of PrtGRxMoveY()

//
// **********************************************************************
 
ULONG APIENTRY PrtGRxLoadResMod( CHAR      *name,
                                 ULONG     argc,
                                 RXSTRING  argv[],
                                 CHAR      *queuename,
                                 RXSTRING  *retstr)
 
// **********************************************************************
//
// Description : Load a Resource DLL
//
// Function    :
//
// Return      :
//
// **********************************************************************
 
    {
    HMODULE         hmod = NULLHANDLE;
    char            load_err[ 256];
    
    LongToRXString( ( ULONG)hmod, retstr);

    if( argc < 1)
        return INVALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 0]))
        return VALID_ROUTINE;

    if( DosLoadModule( load_err, sizeof( load_err), argv[ 0].strptr, &hmod))
        return VALID_ROUTINE;

    LongToRXString( ( ULONG)hmod, retstr);

    return VALID_ROUTINE;

    } // end of PrtGRxLoadResMod()

//
// **********************************************************************
 
ULONG APIENTRY PrtGRxFreeResMod( CHAR      *name,
                                 ULONG     argc,
                                 RXSTRING  argv[],
                                 CHAR      *queuename,
                                 RXSTRING  *retstr)
 
// **********************************************************************
//
// Description : Free a resource DLL
//
// Function    :
//
// Return      :
//
// **********************************************************************
 
    {
    HMODULE         hmod;
    
    BUILDRXSTRING( retstr, "0")

    if( argc < 1)
        return INVALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 0]))
        return VALID_ROUTINE;

    hmod = ( HMODULE)atol( argv[ 0].strptr);
    if( !DosFreeModule( hmod))
        BUILDRXSTRING( retstr, "1")

    return VALID_ROUTINE;
    
    } // end of PrtGRxFreeResMod()

/*
 *  PrtGRxDrawLine
 */

ULONG APIENTRY PrtGRxDrawLine( CHAR *name,
                               ULONG argc,
                               RXSTRING argv[],
                               CHAR *queuename,
                               RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    POINTL      bl, tr, ptl;
    LONG        th, llc, lt;
    
    BUILDRXSTRING( retstr, "0")

    if (argc < 6)
        return INVALID_ROUTINE;
    
    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;
    
    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    
    if ( !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    else
        bl.x = ptl.x;

    if ( !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    else
        bl.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * pjob->unit_conv) + pjob->pdata->pt_lmargin;
    else
        tr.x = pjob->pdata->pt_rmargin;

    if ( !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    else
        tr.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);
    else
        th = 14;

    if (argc > 6)
        if ( !RXNULLSTRING( argv[ 6]))
            {
            llc = ColorToIndex( argv[ 6].strptr);
            if( llc == CLR_NOINDEX)
                llc = pjob->lColor;
            }
        else
            llc = pjob->lColor;
    else
        llc = pjob->lColor;

    if( argc > 7)
        {
        if ( !RXNULLSTRING( argv[ 7]))
            {
            lt = atol( argv[ 7].strptr);
            }
        else
            lt = 0;
        }
    else
        lt = 0;

    PrtLine( pjob, bl, tr, th, llc, lt);

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE ;

}

ULONG APIENTRY PrtGRxPrintBullet( CHAR *name,
                                  ULONG argc,
                                  RXSTRING argv[],
                                  CHAR *queuename,
                                  RXSTRING *retstr)
        
{
    PJOB_TYPE   pjob;
    PSZ         szString,
                szBullet,
                szFont,
                szBfont;
    char        justification = 'L';
    LONG        points = 0,
                bpts = 0,
                left_mar,
                wide;
    USHORT      just = JUST_LEFT, 
                i;
    POINTL      ptl;
    
    BUILDRXSTRING( retstr, "0")
    
    /***** Check Arguments (should be 7) ********************************/
    
    if (argc != 10)
        return INVALID_ROUTINE;

    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    if ( pjob == NULL )
        return VALID_ROUTINE;

    if ( !pjob->bPrinting)
        return VALID_ROUTINE;

    if( pjob->pdata->pt_table)
        return VALID_ROUTINE;

    // ***** Get the indent *********************************************
    
    if ( RXNULLSTRING( argv[ 1]))
        left_mar = 0L;
    else
        left_mar = atol( argv[ 1].strptr) * pjob->unit_conv;

    // ***** Get the hanging indent *************************************
    
    if ( !RXNULLSTRING( argv[ 2]))
        wide = atol( argv[ 2].strptr) * pjob->unit_conv;
    else
        wide = 560;
    
    /***** Get the bullet font ******************************************/
    
    szFont = argv[ 3].strptr;

    /***** Get the bullet font size *************************************/
    
    points = RXGETLONG( argv[ 4]);
    
    /***** Get the bullet char ******************************************/

    szBullet = argv[ 5].strptr;

    /***** Get the font *************************************************/
    
    szFont = argv[ 6].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 7]);
    
    // ***** Get the justification **************************************
    
    justification = toupper( argv[ 8].strptr[ 0]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 9].strptr;
    
    // ***** Create a 2 column table ************************************
    
    pjob->pdata->pt_table = PrtCreateTable( 2);
    
    // ***** with no cells drawn ****************************************
    
    pjob->pdata->pt_table->lfill = 0;
    pjob->pdata->pt_table->lline_type = 0;
    pjob->pdata->pt_table->hboxtype = 0;
    
    // ***** Set up the columns *****************************************
    
    left_mar += pjob->pdata->pt_lmargin;
    
    pjob->pdata->pt_table->aCol[ 0].llm_box = left_mar;
    left_mar += wide;
        
    pjob->pdata->pt_table->aCol[ 0].lrm_box = left_mar;
    pjob->pdata->pt_table->aCol[ 1].llm_box = left_mar;
    pjob->pdata->pt_table->aCol[ 1].lrm_box = pjob->pdata->pt_rmargin;

    /***** Calculate text margins ***********************************/

    for( i = 0; i < 2; i++)
        {        
        pjob->pdata->pt_table->aCol[ i].llm_text = pjob->pdata->pt_table->aCol[ i].llm_box;
        pjob->pdata->pt_table->aCol[ i].lrm_text = pjob->pdata->pt_table->aCol[ i].lrm_box;
     
        pjob->pdata->pt_table->aCol[ i].uslines = 0;
        pjob->pdata->pt_table->aCol[ i].usstart = 0;
        pjob->pdata->pt_table->aCol[ i].usnewpage = 0;
        pjob->pdata->pt_table->aCol[ i].lpts = 0;
        pjob->pdata->pt_table->aCol[ i].alines = NULL;
        strcpy( pjob->pdata->pt_table->aCol[ i].cFont, "");

        i++;
        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    pjob->pdata->pt_table->ptltr.x = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_table->usCols-1].lrm_box;
    pjob->pdata->pt_table->ptltr.y = ptl.y;
    pjob->pdata->pt_table->ly_pos = ptl.y;
    pjob->pdata->pt_table->ltcolor = pjob->lColor;
    pjob->pdata->pt_table->llcolor = pjob->lColor;
    pjob->pdata->pt_table->lfcolor = pjob->lColor;
    pjob->pdata->pt_table->lhtcolor = pjob->lColor;
    pjob->pdata->pt_table->lhlcolor = pjob->lColor;
    pjob->pdata->pt_table->lhfcolor = pjob->lColor;
    
    // ***** Start the row **********************************************
    
    pjob->pdata->pt_tmargin = pjob->pdata->pt_table->ly_pos;
    PrtFreeCells( pjob->pdata->pt_table);
    
    // ***** Print the bullet *******************************************
    
    pjob->pdata->pt_col = 0;
    PrtWriteCol( pjob, szBfont, bpts, szBullet, just);
    
    switch( justification)
        {
        case 'C':
            just = JUST_CENTRE;
            break;
        
        case 'J':
            just = JUST_JUSTIFY;
            break;
        
        case 'R':
            just = JUST_RIGHT;
            break;
        
        default :
            break;
        
        } // end of switch justification
    
    // ***** Print the text *********************************************
    
    pjob->pdata->pt_col = 1;
    PrtWriteCol( pjob, szFont, points, szString, just);
    
    // ***** End the row ************************************************
    
    PrtEndRow( pjob);
    
    // ***** Free the table *********************************************
    
    pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);

    BUILDRXSTRING( retstr, "1")
    return VALID_ROUTINE;
}

/*
 *  PrtGRxSaveJobProps
 */

ULONG APIENTRY PrtGRxSaveJobProps( CHAR *name,
                                   ULONG argc,
                                   RXSTRING argv[],
                                   CHAR *queuename,
                                   RXSTRING *retstr)
{
    PJOB_TYPE   pjob;
    PSZ         AppName,
                KeyName;
    PDRIVDATA   pdriv;
    HINI        prf;
    
    BUILDRXSTRING( retstr, "0")

    if (argc != 4)
        return INVALID_ROUTINE;

    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 2]) || RXNULLSTRING( argv[ 3]))
        return INVALID_ROUTINE;
    
    AppName = argv[ 2].strptr;
    KeyName = argv[ 3].strptr;

    pdriv  = pjob->DevStruct.pdriv;
    
    if ( !RXNULLSTRING( argv[ 1]))
        prf = PrfOpenProfile( pjob->hab, argv[ 1].strptr);
    else
        prf = HINI_USERPROFILE;

    AppName = argv[ 2].strptr;
    KeyName = argv[ 3].strptr;

    if( PrfWriteProfileData( prf, AppName, KeyName, pdriv, pdriv->cb))
        BUILDRXSTRING( retstr, "1")

    if( prf != HINI_USERPROFILE)
        PrfCloseProfile( prf);

    return VALID_ROUTINE;
}

/*
 *  PrtGRxReadJobProps
 */

ULONG APIENTRY PrtGRxReadJobProps( CHAR *name,
                                   ULONG argc,
                                   RXSTRING argv[],
                                   CHAR *queuename,
                                   RXSTRING *retstr)
{
    PJOB_TYPE   pjob;
    PSZ         AppName,
                KeyName;
    ULONG       datalen;
    PDRIVDATA   pdriv;
    HINI        prf;
    
    if (argc != 4)
        return INVALID_ROUTINE;

    pjob = ( PJOB_TYPE) atol( argv[ 0].strptr);
    
    if ( pjob == NULL )
        return VALID_ROUTINE;

    if ( RXNULLSTRING( argv[ 2]) || RXNULLSTRING( argv[ 3]))
        return INVALID_ROUTINE;
    
    if ( !RXNULLSTRING( argv[ 1]))
        prf = PrfOpenProfile( pjob->hab, argv[ 1].strptr);
    else
        prf = HINI_USERPROFILE;

    AppName = argv[ 2].strptr;
    KeyName = argv[ 3].strptr;

    if( PrfQueryProfileSize( prf, AppName, KeyName, &datalen))
        {
        pdriv = ( PDRIVDATA) calloc( 1, datalen);
    
        if( PrfQueryProfileData( prf, AppName, KeyName, pdriv, &datalen))
            {

            if( ( pdriv->cb == pjob->DevStruct.pdriv->cb) &&
                !strcmp( pdriv->szDeviceName, pjob->DevStruct.pdriv->szDeviceName) &&
                ( pdriv->lVersion == pjob->DevStruct.pdriv->lVersion))
                {
                memcpy( pjob->DevStruct.pdriv, pdriv, pdriv->cb);
                BUILDRXSTRING( retstr, "0")
                }
            else
                {
                BUILDRXSTRING( retstr, "1")
                }
            }
        else
            {
            BUILDRXSTRING( retstr, "2")
            }
        }
    else
        {
        BUILDRXSTRING( retstr, "3")
        }

    if( prf != HINI_USERPROFILE)
        PrfCloseProfile( prf);

    return VALID_ROUTINE;
}

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
