// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTGRAPH.C  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:09:28  $
//
// $Log:   M:\prtgraph\prtgraph.c_v  $
//
//    Rev 1.0   04 May 1996 21:09:28   KANIS
// First VCS store for v2.2
//
// *********************************************************************
//  Export:  PrtOpen();
//           PrtQueryQueueInfo( );
//           PrtClose( );
//           PrtFindQueue( );
//           PrtLoadFont( );
//           PrtGetNewLcid( );
//           PrtGetSelForm( );
//           PrtBox( );
//           PrtSetFontSize( );
//           PrtNewFont( );
//           PrtStringLen( );
//           PrtFontAvailable( );
//           PrtNewPage( );
//           PrtHeader( );
//           PrtFooter( );
//           PrtWrite( );
//           PrtWriteln( );
//           PrtJustified( );
//           PrtWordBreak( );
//           PrtCentre( );
//           PrtJustRight( );
//           PrtWriteCol( );
//           PrtSetBorder( );
//           PrtSetHeaderBox( );
//           PrtGetPrinterList( );
//           PrtGetDateString( );
//           PrtWriteFormatted( );
//           PrtDrawBitMap( );
//           PrtFixFlagChars( );
//           PrtChooseFont( );
//           PrtEndRow( );
//           PrtObjectInit( );
//           PrtObjectDestroy( );
//           FileReset( );
//           FileRead( );
//           FileReadLn( );
//           PrtWriteTableHeader( );
//           PrtAbort( );
//           PrtCheckFits( );
//           PrtLineFits( );
//           PrtCheckMargins( );
//           PrtSetProgressTexts( );
//           PrtPrinterDlgProc( );
//           PrtProgressDlgProc( );
//           PrtStartDaemon();
//           PrtReleaseDaemon();
//           PrtSetupShrMem();
//           PrtCreateDevStruct();
//           PrtDeleteDevStruct();
//           PrtLoadProgressDlg();
//           PrtSetPrinter();
//           PrtSetFont();
//           Set_LineSpace();
//           Set_Measures();
//           Set_PrintColor();

#define     INCL_DOS
#define     INCL_BASE
#define     INCL_ERRORS
#define     INCL_WIN
#define     INCL_DEV
#define     INCL_SPL
#define     INCL_SPLDOSPRINT
#define     INCL_BASE
#define     INCL_GPILOGCOLORTABLE
#define     INCL_GPILCIDS
#define     INCL_GPITRANSFORMS
#define     INCL_GPIPATHS
#define     INCL_GPICONTROL
#define     INCL_GPIPRIMITIVES
#define     INCL_GPIERRORS
#define     INCL_GPIBITMAPS
#define     INCL_REXXSAA

#include    <xpf.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdio.h>
#include    <ctype.h>
#include    <rexxsaa.h>
#include    <tstngen.h>
#include    "prt_int.h"
#include    "prt_dlg.h"
#include    "prtgraph.h"

PSHR_MEM_BLOCK  pShrMem;        // Shared mem for dialogs
HMTX            HmtxShr;        // Access semaphore for shared mem
HEV             HevShr;         // Synch semaphore for shared mem
PVOID           pvShrObject;
HWND            hwndProg;       // Handle of REXX window

PRT_LIST        pPrtList;

extern BOOL     bPM;
extern PSZ      module_name;
extern BOOL     use_hook;

// **********************************************************************
// Colour definition table for REXX/SAA
// **********************************************************************

COLOURS     col_arr[] =
    {
    "WHITE", "White", CLR_WHITE,
    "BLACK", "Black", CLR_BLACK,
    "BLUE", "Blue", CLR_BLUE,
    "RED", "Red", CLR_RED,
    "PINK", "Pink", CLR_PINK,
    "GREEN", "Green", CLR_GREEN,
    "CYAN", "Cyan", CLR_CYAN,
    "YELLOW", "Yellow", CLR_YELLOW,
    "DARKGRAY", "DarkGray", CLR_DARKGRAY,
    "DARKBLUE", "DarkBlue", CLR_DARKBLUE,
    "DARKRED", "DarkRed", CLR_DARKRED,
    "DARKPINK", "DarkPink", CLR_DARKPINK,
    "DARKGREEN", "DarkGreen", CLR_DARKGREEN,
    "DARKCYAN", "DarkCyan", CLR_DARKCYAN,
    "BROWN", "Brown", CLR_BROWN,
    "PALEGRAY", "PaleGray", CLR_PALEGRAY,
    "<DEFAULT>", "<default>", CLR_DEFAULT
    };


// **********************************************************************

BOOL PrtOpen( PJOB_TYPE pjob,
              USHORT    copies)

// **********************************************************************

    {
    PRINTDLG    pd;
    DOCINFO     di;
    /* Initialize the PRINTDLG members. */

    pd.lStructSize = sizeof(PRINTDLG);
    pd.hDevMode = (HANDLE) NULL;
    pd.hDevNames = (HANDLE) NULL;
    pd.Flags = PD_RETURNDC;
    pd.hwndOwner = pjob->hwnd;
    pd.hDC = (HDC) NULL;
    pd.nFromPage = 1;
    pd.nToPage = 1;
    pd.nMinPage = 0;
    pd.nMaxPage = 0;
    pd.nCopies = copies;
    pd.hInstance = (HANDLE) NULL;
    pd.lCustData = 0L;
    pd.lpfnPrintHook = (LPPRINTHOOKPROC) NULL;
    pd.lpfnSetupHook = (LPSETUPHOOKPROC) NULL;
    pd.lpPrintTemplateName = (LPSTR) NULL;

    pd.lpSetupTemplateName = (LPSTR)  NULL;
    pd.hPrintTemplate = (HANDLE) NULL;
    pd.hSetupTemplate = (HANDLE) NULL;

    /* Display the PRINT dialog box. */

    if( !PrintDlg(&pd))
        return FALSE;

    pjob->pdata->pt_hdc = pd.hDC;

    pjob->pdata->doc_name_len = (LONG) strlen( pjob->pdata->doc_name);

    pjob->pdata->pt_next_idx = 0;

    PrtGetDateString( pjob);

    /***** Get Queue info ***********************************************/

    if ( !PrtQueryQueueInfo( pjob))
        return(FALSE);

    di.cbSize = sizeof(DOCINFO);
    strcpy( di.lpszDocName, pjob->pdata->doc_name);
    di.lpszOutput = (LPTSTR) NULL;
    di.lpszDataType = (LPTSTR) NULL;
    di.fwType = 0;

    if( StartDoc( pjob->pdata->pt_hdc, &di) == SP_ERROR)
        {
        DeleteDC( pjob->pdata->pt_hdc);
        return( FALSE);
        } // end of if

    pjob->check_page = TRUE;
    pjob->bPrinting = TRUE;

    if ( pjob->bProgress)
        PrtLoadProgressDlg( pjob);

    return( TRUE);

    } // end of PrtOpen()

// **********************************************************************

BOOL PrtQueryQueueInfo( PJOB_TYPE pjob)

// **********************************************************************

    {
    SIZEL           sizel;
    HCINFO          hcinfo;         /* info about selected form */
    HPS             hps_info;
    HDC             hdc_info;
    LONG            cx;

    cx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN);

    /************* 9. Create an OD_INFO device context **************/

    TST_TRACE(( "PrtQueryQueueInfo - DevOpenDC for (%s)",
                pjob->DevStruct.pszDriverName))

    hdc_info = DevOpenDC( pjob->hab,
                           OD_INFO,
                           "*",
                           3L,
                           ( PDEVOPENDATA)&( pjob->DevStruct),
                           (HDC)NULL);

    if ( hdc_info == DEV_ERROR )
        {
        TRACEWINERROR( "PrtQueryQueueInfo - ERROR DevOpenDC (%s) failed severity %X error %X",
                        pjob->DevStruct.pszDriverName)
        return( FALSE);
        }

    memset( &sizel, 0, sizeof(sizel));

    /********** 10. create PS for printer info -- not a full-blown PS *********/

    hps_info = GpiCreatePS( pjob->hab,
                            hdc_info,
                            (PSIZEL)&sizel,
                            PU_TWIPS | GPIA_ASSOC | GPIF_LONG);

    if ( hps_info == DEV_ERROR)
        {
        TST_TRACE(( "PrtQueryQueueInfo - ERROR GpiCreatePS failed"))
        DevCloseDC(hdc_info);
        return( FALSE);
        }

    /********* 11. Store the page size of the device (PU_TWIPS) *******/

    GpiQueryPS(hps_info, (PSIZEL)&pjob->pdata->pt_graph_size);

    TST_TRACE(( "PrtQueryQueueInfo - width %lu height %lu TWIPS",
                pjob->pdata->pt_graph_size.cx, pjob->pdata->pt_graph_size.cy))

    /******** 12. Fetch size of selected form in mm ***************/

    if ( !PrtGetSelForm( hdc_info, &hcinfo))
        {
        TST_TRACE(( "PrtQueryQueueInfo - ERROR PrtGetSelForm failed"))
        DevCloseDC(hdc_info);
        return( FALSE);
        }

    TST_TRACE(( "PrtQueryQueueInfo - copy form name %s", hcinfo.szFormname))

    strcpy( pjob->pszForm, hcinfo.szFormname);

    TST_TRACE(( "PrtQueryQueueInfo - Got form name %s", pjob->pszForm))

    if ( pjob->bMetric)
        {
        pjob->pdata->pt_page_size.cx = hcinfo.cx;
        pjob->pdata->pt_page_size.cy = hcinfo.cy;
        pjob->pdata->pt_min_lmargin = hcinfo.xLeftClip;
        pjob->pdata->pt_min_rmargin = hcinfo.cx - hcinfo.xRightClip;
        pjob->pdata->pt_min_tmargin = hcinfo.cy - hcinfo.yTopClip;
        pjob->pdata->pt_min_bmargin = hcinfo.yBottomClip;
        } // end of if
    else
        {
        pjob->pdata->pt_page_size.cx = ( LONG) ( hcinfo.cx / MM_TO_TENTH);
        pjob->pdata->pt_page_size.cy = ( LONG) ( hcinfo.cy / MM_TO_TENTH);
        pjob->pdata->pt_min_lmargin = ( ULONG)( (float)hcinfo.xLeftClip / MM_TO_TENTH);
        pjob->pdata->pt_min_rmargin = ( ULONG)( (float)( hcinfo.cx - hcinfo.xRightClip) / MM_TO_TENTH);
        pjob->pdata->pt_min_tmargin = ( ULONG)( (float)( hcinfo.cx - hcinfo.yTopClip) / MM_TO_TENTH);
        pjob->pdata->pt_min_bmargin = ( ULONG)( (float)hcinfo.yBottomClip / MM_TO_TENTH);
        } // end of else

    TST_TRACE(( "PrtQueryQueueInfo - ml %lu mr %lu mt %lu mb %lu",
                pjob->pdata->pt_min_lmargin, pjob->pdata->pt_min_rmargin,
                pjob->pdata->pt_min_tmargin, pjob->pdata->pt_min_bmargin))

    TST_TRACE(( "PrtQueryQueueInfo - width %lu height %lu (units)",
                pjob->pdata->pt_page_size.cx, pjob->pdata->pt_page_size.cy))

    pjob->pdata->pt_left_margin = max( pjob->pdata->pt_left_margin,
                                        pjob->pdata->pt_min_lmargin);
    pjob->pdata->pt_right_margin = max( pjob->pdata->pt_right_margin,
                                        pjob->pdata->pt_min_rmargin);
    pjob->pdata->pt_top_margin = max( pjob->pdata->pt_top_margin,
                                        pjob->pdata->pt_min_tmargin);
    pjob->pdata->pt_bot_margin = max( pjob->pdata->pt_bot_margin,
                                        pjob->pdata->pt_min_bmargin);

    TST_TRACE(( "PrtQueryQueueInfo - lm %lu rm %lu tm %lu bm %lu",
                pjob->pdata->pt_left_margin, pjob->pdata->pt_right_margin,
                pjob->pdata->pt_top_margin, pjob->pdata->pt_bot_margin))

    /*********** 13. set horiz offset correctly with ************/
    /***********     consideration of clipping limit **************/

    pjob->pdata->pt_bl_offset.cx = ( LONG)(( pjob->pdata->pt_left_margin -
                                            pjob->pdata->pt_min_lmargin) * pjob->unit_conv);
    pjob->pdata->pt_bl_offset.cy = ( LONG)(( pjob->pdata->pt_bot_margin -
                                            pjob->pdata->pt_min_bmargin) * pjob->unit_conv);

    pjob->pdata->pt_tr_offset.cx = ( LONG)(( pjob->pdata->pt_right_margin -
                                            pjob->pdata->pt_min_rmargin) * pjob->unit_conv);
    pjob->pdata->pt_tr_offset.cy = ( LONG)(( pjob->pdata->pt_top_margin -
                                            pjob->pdata->pt_min_tmargin) * pjob->unit_conv);

    pjob->pdata->pt_tr_margin.cx = pjob->pdata->pt_graph_size.cx -
                                        pjob->pdata->pt_tr_offset.cx;
    pjob->pdata->pt_tr_margin.cy = pjob->pdata->pt_graph_size.cy -
                                        pjob->pdata->pt_tr_offset.cy;
    pjob->pdata->pt_rmargin = pjob->pdata->pt_tr_margin.cx;
    pjob->pdata->pt_lmargin = pjob->pdata->pt_bl_offset.cx;
    pjob->pdata->pt_prt_top = pjob->pdata->pt_tr_margin.cy;

    pjob->pdata->pt_wide = pjob->pdata->pt_rmargin - pjob->pdata->pt_lmargin;
    pjob->pdata->xpels = ( double)pjob->pdata->pt_graph_size.cx / ( double)hcinfo.xPels;
    pjob->pdata->ypels = ( double)pjob->pdata->pt_graph_size.cy / ( double)hcinfo.yPels;
    pjob->pdata->aspect = ( double)hcinfo.xPels / ( double)cx;

    /****************** 15. Close DC and free memory *******************/

    DevCloseDC(hdc_info);

    return (TRUE);

    } // end of PrtQueryQueueInfo()


// **********************************************************************

VOID PrtClose( PJOB_TYPE pjob)

// **********************************************************************

    {
    TST_TRACE(( "PrtClose: NOTE - Closing print job"))

    if( pjob->bPrinting)
        DevEscape( pjob->pdata->pt_hdc, DEVESC_ENDDOC, 0, NULL, (PLONG)NULL, (PBYTE)NULL);

    GpiResetPS( pjob->pdata->pt_hps, GRES_ALL);
    GpiAssociate( pjob->pdata->pt_hps, NULLHANDLE);
    GpiDestroyPS( pjob->pdata->pt_hps);
    DevCloseDC( pjob->pdata->pt_hdc);

    pjob->pdata->pt_hdc = (HDC) 0;
    pjob->pdata->pt_hps = ( HPS) 0;

    if ( pjob->pdata->pt_table)
        pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);

    pjob->pdata->pt_point_size = 0;

    pjob->pdata->pt_lcid = 0;
    pjob->pdata->pt_next_idx = 0;
    pjob->pdata->pt_font_idx = 0;

    pjob->pdata->pt_page = 0;
    pjob->pdata->pt_pages = 0;
    pjob->pdata->pt_col = 0;
    pjob->pdata->doc_name_len = 0;

    strcpy( pjob->pdata->doc_name, "");

    pjob->bPrinting = FALSE;

    if( pjob->bProgress)
        {
        WinSendMsg( pjob->hwndProgress, WM_STOPME, 0L, 0L);
        pjob->hwndProgress = NULLHANDLE;
        }

    TST_TRACE(( "PrtClose: NOTE - Closed print job"))

    } // end of PrtClose()


// **********************************************************************

LONG PrtFindQueue( PSZ pszQueueName,
                   PPRQINFO3 pQueueInfo,
                   LONG lCount)

// **********************************************************************

    {
    LONG i;

    for (i = 0L; i < lCount; ++i)
        {
        if ( !strcmp( pszQueueName, pQueueInfo[i].pszName ) )
         return i;
        }

    return -1L;                 /*  if not found  */

    } // end of PrtFindQueue()


// **********************************************************************

BOOL PrtLoadFont( PJOB_TYPE pjob, SHORT index)

// **********************************************************************

    {
    LONG        clfonts =0L;
    LONG        clreq = 0L;
    FONTMETRICS *pfm = NULLHANDLE;
    FATTRS      fat;
    SHORT       j;


    /********** 1. get number of fonts of requested type *******/

    if ((clfonts = GpiQueryFonts( pjob->pdata->pt_hps, QF_PUBLIC,
                                  pjob->pdata->pt_font[ index].sz_name,
                                  &clreq, 0L, pfm)) <= 0L)
        return( FALSE);      /* font not found */

    clfonts = min(clfonts, 0x10000 / sizeof(FONTMETRICS));

    /*********** 2. Reserve memory *******************************/

    pfm = ( FONTMETRICS*) calloc( clfonts, (size_t) (sizeof(FONTMETRICS)));
    if (pfm == NULLHANDLE)
        return( FALSE);

    /************ 3. Get fontmetrics ***********************/

    GpiQueryFonts( pjob->pdata->pt_hps, QF_PUBLIC, pjob->pdata->pt_font[ index].sz_name, &clfonts,
                   (LONG) sizeof(FONTMETRICS), pfm);


    /**************** 4. Search an outline font *****************/

    for (j=0; j<clfonts && (!(pfm[j].fsDefn & FM_DEFN_OUTLINE)); j++)
        j=j;

    if (j==clfonts)             /* No outline font found !!! */
        {
        FREE(pfm);
        return( FALSE);
        }

    /**************** 5. copy font-attributes of 'normal-font' ***********/

    strcpy(fat.szFacename, pfm[j].szFacename);
    fat.usRecordLength  = sizeof(FATTRS);
    fat.fsSelection     = 0;
    fat.lMatch          = pfm[j].lMatch;
    fat.idRegistry      = 0;
    fat.usCodePage      = 0;
    fat.lMaxBaselineExt = 0;
    fat.lAveCharWidth   = 0;
    fat.fsType          = 0;
    fat.fsFontUse       = FATTR_FONTUSE_OUTLINE;


    /*********** 6. Create outline-font ***************************************/

    if ( GpiCreateLogFont( pjob->pdata->pt_hps, NULL, pjob->pdata->pt_font[ index].lLcid, &fat) == GPI_ERROR)
        {
        FREE( pfm);
        return( FALSE);
        }

    /************ 7. free resources ****************************/

    FREE( pfm);
    return( TRUE);

    } // end of PrtLoadFont()


// **********************************************************************

LONG PrtGetNewLcid( PJOB_TYPE pjob)

// **********************************************************************

    {
    LONG            count;      /* number of lcids */
    PSTR8           pnames;     /* pointer to 8 character logical font name */
    PLONG           plcids;     /* pointer to lcids */
    PLONG           ptypes;     /* pointer to types */
    LONG            new_lcid;   /* new lcid to set */
    LONG            j;          /* variable for looping */

    count = GpiQueryNumberSetIds(pjob->pdata->pt_hps);   /* get number of lcids */
    pnames = ( STR8*)calloc(count, sizeof(STR8));       /* allocate memory for font names */
    plcids = ( long*)calloc(count, sizeof(LONG));       /* allocate memory for lcids */
    ptypes = ( long*)calloc(count, sizeof(LONG));       /* allocate memory for types */

    GpiQuerySetIds(pjob->pdata->pt_hps,count,ptypes,pnames,plcids); /* query all lcids */

    for (new_lcid=1;new_lcid<255;new_lcid++)        /* search unused lcid */
        {
        for (j=0;j<count;j++)
            {
            if (plcids[j]==new_lcid)
                break;              /* quit inner loop if new_lcid is free */
            }

        if (j==count)               /* inner loop was quitted without break */
            {                       /* i.e. new_lcid was not found */
            break;                  /* quit outer loop  */
            }
        }

    /*********** 2. free memory ***************************/

    FREE(pnames);
    FREE(plcids);
    FREE(ptypes);

    /******************* 3. return new lcid *******************/

    return( new_lcid);

    } // end of PrtGetNewLcid()


// **********************************************************************

SHORT PrtGetSelForm( HDC hdc,
                     HCINFO *phcinfo)

// **********************************************************************

    {
    LONG            clforms;        /* number of forms available for this hdc */
    LONG            i;              /* var for looping */
    HCINFO          *phc;           /* o: pointer to HCINFO for all forms */

    clforms = DevQueryHardcopyCaps( hdc, 0L, 0L, NULL);

    TST_TRACE(( "PrtGetSelForm: get info for %ld forms", clforms))

    phc = ( HCINFO*)calloc( clforms, sizeof( HCINFO));

    /*************** 3. query forms data *************************/

    TST_TRACE(( "PrtGetSelForm: Query forms data into %ld HCINFOs at %p", clforms, phc))
    DevQueryHardcopyCaps( hdc,
                          0L,               /* start with first form */
                          clforms,          /* query all forms  */
                          phc);             /* struct to hold returned data */


    /************** 4. search form that is actually selected **********/

    for (i = 0L; i < clforms; i++)
        {
        if ( phc[ i].flAttributes & HCAPS_CURRENT )      /* currently selected font */
            break;                                      /* quit for-loop */
        }

    TST_TRACE(( "PrtGetSelForm: Default form is number %ld", i))
    if (i == clforms )          /* no form with HCAPS_CURRENT was found, ?strange? */
        return( FALSE);

    /* copy currently selected font into given variable */

    memcpy( phcinfo, phc+i, sizeof(HCINFO) );

    /**************** 5. free memory ***********************/

    FREE(phc);

    return( TRUE);

    } // end of PrtGetSelForm()


// **********************************************************************

VOID PrtBox( PJOB_TYPE pjob,
             POINTL bl,
             POINTL tr,
             LONG thickness,
             LONG fill,
             USHORT boxtype,
             LONG lcl,
             LONG lcf)

// **********************************************************************

    {
    LONG    pattern,
            path_id = 1L;
    POINTL  ptlhere,                /* Here we are now */
            br,                     /* Bottom rigt point */
            tl;                     /* top left point */

    /***** Store the current current cursor position ********************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    /***** Set any fill pattern defined *********************************/

    if ( fill != FILL_NONE)
        {
        TST_TRACE(( "PrtBox - NOTE - use fill style %lu", fill))
        switch ( fill)
            {
            case FILL_FULL :
                pattern = PATSYM_DENSE1;
                break;

            case FILL_90 :
                pattern = PATSYM_DENSE2;
                break;

            case FILL_80 :
                pattern = PATSYM_DENSE3;
                break;

            case FILL_75 :
                pattern = PATSYM_DENSE4;
                break;

            case FILL_70 :
                pattern = PATSYM_DENSE5;
                break;

            case FILL_60 :
                pattern = PATSYM_DENSE6;
                break;

            case FILL_HALF :
                pattern = PATSYM_DENSE7;
                break;

            case FILL_LIGHT :
                pattern = PATSYM_DENSE8;
                break;

            case FILL_VERT :
                pattern = PATSYM_VERT;
                break;

            case FILL_HORIZ :
                pattern = PATSYM_HORIZ;
                break;

            case FILL_DIAGR45 :
                pattern = PATSYM_DIAG1;
                break;

            case FILL_DIAGR33 :
                pattern = PATSYM_DIAG2;
                break;

            case FILL_DIAGL45 :
                pattern = PATSYM_DIAG3;
                break;

            case FILL_DIAGL33 :
                pattern = PATSYM_DIAG4;
                break;

            default :
                pattern = PATSYM_HALFTONE;
                break;

            } /* end of switch fill */

        GpiSetColor( pjob->pdata->pt_hps, lcf);

        GpiSetPattern( pjob->pdata->pt_hps, pattern);

        /***** Draw the filled box **************************************/

        GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);
        GpiBox( pjob->pdata->pt_hps, DRO_FILL, &tr, 0, 0);
        GpiSetPattern( pjob->pdata->pt_hps, PATSYM_DEFAULT);

        } /* end of if */

    TST_TRACE(( "PrtBox - NOTE - coords (%lu,%lu)(%lu,%lu)", bl.x, bl.y, tr.x, tr.y))
    TST_TRACE(( "PrtBox - NOTE - Line thickness (%lu) style (%lu)", thickness, fill))

    /***** Draw the outline thickness ***********************************/

    tl.x = bl.x;
    tl.y = tr.y;
    br.x = tr.x;
    br.y = bl.y;

    GpiSetColor( pjob->pdata->pt_hps, lcl);
    GpiSetLineWidthGeom( pjob->pdata->pt_hps, thickness);

    if(( boxtype & BOX_LEFT) == BOX_LEFT)
        {
        GpiBeginPath( pjob->pdata->pt_hps, path_id);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &tl);
        GpiBox( pjob->pdata->pt_hps, DRO_OUTLINE, &bl, 0, 0);
        GpiEndPath( pjob->pdata->pt_hps);
        GpiStrokePath( pjob->pdata->pt_hps, 1, 0);
        }

    if(( boxtype & BOX_RIGHT) == BOX_RIGHT)
        {
        GpiBeginPath( pjob->pdata->pt_hps, path_id);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &tr);
        GpiBox( pjob->pdata->pt_hps, DRO_OUTLINE, &br, 0, 0);
        GpiEndPath( pjob->pdata->pt_hps);
        GpiStrokePath( pjob->pdata->pt_hps, 1, 0);
        }

    if(( boxtype & BOX_TOP) == BOX_TOP)
        {
        GpiBeginPath( pjob->pdata->pt_hps, path_id);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &tl);
        GpiBox( pjob->pdata->pt_hps, DRO_OUTLINE, &tr, 0, 0);
        GpiEndPath( pjob->pdata->pt_hps);
        GpiStrokePath( pjob->pdata->pt_hps, 1, 0);
        }

    if(( boxtype & BOX_BOT) == BOX_BOT)
        {
        GpiBeginPath( pjob->pdata->pt_hps, path_id);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);
        GpiBox( pjob->pdata->pt_hps, DRO_OUTLINE, &br, 0, 0);
        GpiEndPath( pjob->pdata->pt_hps);
        GpiStrokePath( pjob->pdata->pt_hps, 1, 0);
        }

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    /***** Restore the original position ********************************/

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    } // end of PrtBox()


// **********************************************************************

BOOL PrtSetFontSize( PJOB_TYPE pjob,
                     SHORT idx,
                     LONG points)

// **********************************************************************

    {
    SIZEF             sizfx;                    /* used to set character box */
    LONG              cell_width;               /* width of character cell */
    LONG              cell_hight;               /* hight of character cell */

    if( points == 0L)
        return TRUE;

    /***** Set the current font id **************************************/

    if ( pjob->pdata->pt_lcid != pjob->pdata->pt_font[ idx].lLcid)
        {
        pjob->pdata->pt_lcid = pjob->pdata->pt_font[ idx].lLcid;
        if ( !GpiSetCharSet( pjob->pdata->pt_hps, pjob->pdata->pt_lcid))
            return( FALSE);
        }

    cell_width = points * ONE_POINT;
    cell_hight = cell_width;

    sizfx.cx = cell_width<<16;
    sizfx.cy = cell_hight<<16;

    if ( !GpiSetCharBox( pjob->pdata->pt_hps, &sizfx))
         return( FALSE);

    if ( !GpiSetCharMode( pjob->pdata->pt_hps, CM_MODE3))
        return( FALSE);

    pjob->pdata->pt_point_size = points;

    return( TRUE);

    } // end of PrtSetFontSize()


// **********************************************************************

SHORT PrtNewFont( PJOB_TYPE pjob, PSZ szFontname)

// **********************************************************************

    {
    SHORT           idx;
    LONG            lcid;

    if ( pjob->pdata->pt_next_idx == MAX_FNT)
        return( -1);

    lcid = PrtGetNewLcid( pjob);
    TST_TRACE(( "PrtNewFont - PrtGetNewLcid returned %d", lcid))
    if (lcid == -1)
        return( -1);

    idx = pjob->pdata->pt_next_idx;
    pjob->pdata->pt_next_idx++;

    pjob->pdata->pt_font[ idx].lLcid = lcid;
    strcpy( pjob->pdata->pt_font[ idx].sz_name, szFontname);

    if( !PrtLoadFont( pjob, idx))
        {
        TST_TRACE(( "PrtNewFont - PrtLoadFont( %s ) failed", szFontname))
        return( -1);
        }

    return( idx);

    } // end of PrtNewFont()


// **********************************************************************

LONG PrtStringLen( PJOB_TYPE pjob, PSZ sz)

// **********************************************************************

    {
    POINTL      aptl[ TXTBOX_COUNT] = { 0,0,0,0,0,0,0,0,0,0};
    LONG        lsz = 0;
    BOOL        rc;

    lsz = strlen( sz);

    if ( lsz)
        {
        rc = GpiQueryTextBox( pjob->pdata->pt_hps, lsz, sz, TXTBOX_COUNT, aptl);
        if ( rc)

            /***** Fix for Postscript BUG *******************************/

            if ( aptl[ TXTBOX_BOTTOMRIGHT].x < 0)
                {
                aptl[ TXTBOX_BOTTOMRIGHT].x = aptl[ TXTBOX_BOTTOMRIGHT].x ^ PS_MASK;
                } /* end of if */

            lsz = aptl[ TXTBOX_BOTTOMRIGHT].x - aptl[ TXTBOX_BOTTOMLEFT].x;
        }

    TST_TRACE(( "PrtStringLen: NOTE - aptl[TXTBOX_BOTTOMRIGHT].x %lX aptl[ TXTBOX_BOTTOMLEFT].x %lX",
                    aptl[TXTBOX_BOTTOMRIGHT].x, aptl[ TXTBOX_BOTTOMLEFT].x))
    TST_TRACE(( "PrtStringLen: NOTE - For font %s %lu returned %lu",
                    pjob->pdata->pt_font[ pjob->pdata->pt_font_idx].sz_name, pjob->pdata->pt_point_size, rc))
    TST_TRACE(( "PrtStringLen: NOTE - Got twips length %ld for '%s'", lsz, sz))

    return( lsz);

    } // end of PrtStringLen()


// **********************************************************************

SHORT PrtFontAvailable( PJOB_TYPE pjob, PSZ szFont)

// **********************************************************************

    {
    SHORT       idx = -1,
                i;

    i = 0;
    while ( i < pjob->pdata->pt_next_idx)
        {
        if ( strcmp( pjob->pdata->pt_font[ i].sz_name, szFont) == 0)
            {
            idx = i;
            i = pjob->pdata->pt_next_idx;
            }
        i++;
        } /* end of while */

    return( idx);

    } // end of PrtFontAvailable()


// **********************************************************************

VOID PrtNewPage( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL          bl,
                    sbl,
                    str;
    LONG            llc,
                    lfc;
    PFNNP           pfnnp;

    /***** Increment the page counter ***********************************/

    pjob->pdata->pt_page++;

    TST_TRACE(( "PrtNewPage - NOTE - new page %u", pjob->pdata->pt_page))

    /***** If not first page send new frame to printer ******************/

    if( pjob->pdata->pt_page > 1)
        {
        if ( DevEscape( pjob->pdata->pt_hdc, DEVESC_NEWFRAME, 0, NULL, NULL, NULL) != DEV_OK)
            {
            TST_TRACE(( "PrtNewPage: ERROR - Failed to create new page"))
            return;
            }
        }

    if( pjob->bProgress)
        WinPostMsg( pjob->hwndProgress, WM_UPDATE, MPFROMSHORT( pjob->pdata->pt_page), 0L);

    // ***** Call the callback function *********************************

    if( use_hook)
        {
        if( pjob->pt_np_func)
            {
            TST_TRACE(( "PrtNewPage - NOTE - Call callback function"))
            pfnnp = ( PFNNP)pjob->pt_np_func;
            pfnnp( ( LHANDLE)pjob, pjob->pdata->pt_page, ( BOOL)pjob->pdata->pt_table);
            }
        }

    if( pjob->bColor)
        {
        llc = pjob->pdata->pt_blcolor;
        lfc = pjob->pdata->pt_bfcolor;
        }
    else
        {
        llc = pjob->lColor;
        lfc = pjob->lColor;
        }

    /***** If page has a fill style print it ****************************/

    if( pjob->pdata->pt_fill)
        {

        TST_TRACE(( "PrtNewPage - NOTE - draw border"))
        if( ( pjob->pdata->pt_header && (pjob->pdata->pt_page == 1)) ||
            ( pjob->pdata->pt_allpages && (pjob->pdata->pt_page > 1)) )
            str.y = pjob->pdata->pt_hdr_bl.y;
        else
            str.y = pjob->pdata->pt_border_tr.y;

        if( pjob->pdata->pt_footer)
            sbl.y = pjob->pdata->pt_ftr_tr.y;
        else
            sbl.y = pjob->pdata->pt_border_bl.y;

        sbl.x = pjob->pdata->pt_border_bl.x;
        str.x = pjob->pdata->pt_border_tr.x;
        PrtBox( pjob,
                sbl,
                str,
                0L,
                pjob->pdata->pt_fill,
                0,
                llc,
                lfc);
        }

    /***** Print the header and footer **********************************/

    PrtFooter( pjob);
    PrtHeader( pjob);

    /***** If the page has a border print it ****************************/

    if( pjob->pdata->pt_border)
        {

        TST_TRACE(( "PrtNewPage - NOTE - draw border"))

        PrtBox( pjob,
                pjob->pdata->pt_border_bl,
                pjob->pdata->pt_border_tr,
                pjob->pdata->pt_border,
                0L,
                pjob->pdata->pt_box,
                llc,
                lfc);
        }

    /***** Set current pos to top left corner ***************************/

    bl.x = pjob->pdata->pt_bl_offset.cx;
    bl.y = pjob->pdata->pt_prt_top;
    GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);

    } // end of PrtNewPage()


// **********************************************************************

VOID PrtHeader( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL          ptl;
    SHORT           idx;
    LONG            interline,
                    llc,
                    lfc,
                    ltc;
    int             i;

    if( !pjob->pdata->pt_header)
        {
        pjob->pdata->pt_prt_top = pjob->pdata->pt_tr_margin.cy - ( 2 * ONE_MIL);
        pjob->pdata->pt_tmargin = pjob->pdata->pt_prt_top;
        return;
        }

    if ( !pjob->pdata->pt_allpages && (pjob->pdata->pt_page > 1))
        {
        pjob->pdata->pt_tmargin = pjob->pdata->pt_tr_margin.cy;
        pjob->pdata->pt_prt_top = pjob->pdata->pt_tmargin;
        return;
        }

    if( pjob->bColor)
        {
        llc = pjob->pdata->pt_hlcolor;
        lfc = pjob->pdata->pt_hfcolor;
        ltc = pjob->pdata->pt_htcolor;
        }
    else
        {
        llc = pjob->lColor;
        lfc = pjob->lColor;
        ltc = pjob->lColor;
        }

    if ( pjob->pdata->pt_hbox_line != 0)
        {
        PrtBox( pjob,
                pjob->pdata->pt_hdr_bl,
                pjob->pdata->pt_hdr_tr,
                pjob->pdata->pt_hbox_line,
                pjob->pdata->pt_hbox_mode,
                pjob->pdata->pt_boxtype,
                llc,
                lfc);

        } /* end of if */

    ptl.x = pjob->pdata->pt_lmargin;
    ptl.y = pjob->pdata->pt_hdr_tr.y;

    if( pjob->bColor)
        GpiSetColor( pjob->pdata->pt_hps, ltc);

    for ( i = 0; i < pjob->pdata->pt_hlines; i++)
        {

        interline = (( pjob->pdata->pt_psz[ i].lpts * ONE_POINT) * LINE_SPACE) / 100;
        ptl.y -= interline;
        GpiMove( pjob->pdata->pt_hps, &ptl);

        idx = PrtFontAvailable( pjob, pjob->pdata->pt_psz[ i].cfont);
        if ( idx == -1)
            {
            idx = PrtNewFont( pjob, pjob->pdata->pt_psz[ i].cfont);
            if ( idx == -1)
                return;
            } /* end of if */

        if( !PrtSetFontSize( pjob, idx, pjob->pdata->pt_psz[ i].lpts))
            {
            TST_TRACE(("PrtHeader: ERROR - PrtSetFontSize failed"))
            return;
            }

        TST_TRACE(( "PrtHeader: NOTE - write formatted (%s)", pjob->pdata->pt_psz[ i].pszLine))
        PrtWriteFormatted( pjob, pjob->pdata->pt_psz[ i].pszLine, FALSE, 0);

        } /* end of for */

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    pjob->pdata->pt_prt_top = pjob->pdata->pt_hdr_bl.y - ( 2 * ONE_MIL);
    pjob->pdata->pt_tmargin = pjob->pdata->pt_prt_top;

    if( pjob->bColor)
        GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    } // end of PrtHeader()


// **********************************************************************

VOID PrtFooter( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL          ptl;
    SHORT           idx;
    LONG            old_mar,
                    llc,
                    lfc,
                    ltc;

    if( !pjob->pdata->pt_footer)
        return;

    TST_TRACE(( "PrtFooter: NOTE - Print with %s %lu", pjob->pdata->pt_ffont, pjob->pdata->pt_fpts))

    idx = PrtFontAvailable( pjob, pjob->pdata->pt_ffont);
    if ( idx == -1)
        {
        idx = PrtNewFont( pjob, pjob->pdata->pt_ffont);
        if ( idx == -1)
            return;
        } /* end of if */

    if( !PrtSetFontSize( pjob, idx, pjob->pdata->pt_fpts))
        {
        TST_TRACE(("PrtHeader: ERROR - PrtSetFontSize failed"))
        return;
        }

    if( pjob->bColor)
        {
        llc = pjob->pdata->pt_flcolor;
        lfc = pjob->pdata->pt_ffcolor;
        ltc = pjob->pdata->pt_ftcolor;
        }
    else
        {
        llc = pjob->lColor;
        lfc = pjob->lColor;
        ltc = pjob->lColor;
        }

    if ( pjob->pdata->pt_fbox_line != 0)
        {
        PrtBox( pjob,
                pjob->pdata->pt_ftr_bl,
                pjob->pdata->pt_ftr_tr,
                pjob->pdata->pt_fbox_line,
                pjob->pdata->pt_fbox_mode,
                pjob->pdata->pt_fboxtype,
                llc, lfc);

        } /* end of if */

    pjob->check_page = FALSE;
    old_mar = pjob->pdata->pt_bmargin;
    pjob->pdata->pt_bmargin = pjob->pdata->pt_bl_offset.cy;
    ptl.x = pjob->pdata->pt_lmargin;
    ptl.y = pjob->pdata->pt_bmargin;
    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);

    if( pjob->bColor)
        GpiSetColor( pjob->pdata->pt_hps, ltc);
    PrtWriteFormatted( pjob, pjob->pdata->pt_footline, FALSE, 0);
    if( pjob->bColor)
        GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);
    pjob->pdata->pt_bmargin = old_mar;
    pjob->check_page = TRUE;

    } // end of PrtFooter()


// **********************************************************************

BOOL PrtWrite( PJOB_TYPE pjob,
               PSZ szString,
               USHORT usJust)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            linterline,
                    drop,
                    llen,
                    lstart,
                    ledge,
                    lspace;
    BOOL            bmore;
    SHORT           fd_idx;
    LONG            pts;

    if( !szString)
        return FALSE;

    /***** Find our present position ************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    if ( usJust == JUST_JUSTIFY)
        {
        ptlhere.x = pjob->pdata->pt_lmargin;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        }

    lstart = ptlhere.x;

    /***** Get inter-line spacing from font metrics *********************/

    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;
    drop = linterline / 3;

    /***** check for new page *******************************/

    if ( pjob->check_page && ( ptlhere.y < ( pjob->pdata->pt_bmargin + drop)))
        {
        fd_idx = pjob->pdata->pt_font_idx;
        pts = pjob->pdata->pt_point_size;
        PrtNewPage( pjob );
        PrtSetFontSize( pjob, fd_idx, pts);
        ptlhere.y = pjob->pdata->pt_prt_top - linterline;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        }

    /***** Check if start of page (top left corner) *********************/

    if ( ptlhere.y == pjob->pdata->pt_tmargin)
        {
        ptlhere.y -=linterline;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        } /* end of if */

    /***** Get the coords for the right margin **************************/

    ledge = pjob->pdata->pt_rmargin - ONE_MIL;

    /***** Calculate the max string length in twips *********************/

    lspace = ledge - lstart;

    /***** Get the string length in twips *******************************/

    llen = PrtStringLen( pjob, szString);

    if (( llen > pjob->pdata->pt_wide) && ( strlen( szString) == 1))
        return FALSE;

    TST_TRACE(( "PrtWrite - NOTE - input string is %lu twips long space %lu twips", llen, lspace))

    /***** If the string is too long, break it **************************/

    if ( lspace <= llen)
        {
        strcpy( pjob->buffer1, szString);
        do
            {
            bmore = FALSE;
            PrtWordBreak( pjob, ptlhere.x, ledge);

            TST_TRACE(( "PrtWrite - NOTE - input string is split '%s'", pjob->buffer1))
            TST_TRACE(( "PrtWrite - NOTE - input string is split '%s'", pjob->buffer2))

            switch ( usJust)
                {
                case JUST_RIGHT :
                    TST_TRACE(( "PrtWrite - NOTE - Justify right '%s'", pjob->buffer1))
                    llen = PrtStringLen( pjob, pjob->buffer1);
                    ptlhere.x = ledge - llen;
                    GpiMove( pjob->pdata->pt_hps, &ptlhere);
                    break;

                case JUST_CENTRE :
                    TST_TRACE(( "PrtWrite - NOTE - Centre '%s'", pjob->buffer1))
                    llen = PrtStringLen( pjob, pjob->buffer1);
                    ptlhere.x = ((pjob->pdata->pt_wide - llen) / 2) + pjob->pdata->pt_lmargin;
                    GpiMove( pjob->pdata->pt_hps, &ptlhere);
                    break;

                default :
                    break;

                } /* end of switch usJust */

            if (usJust == JUST_JUSTIFY)
                {
                if ( strlen( pjob->buffer2) != 0)
                    PrtJustified( pjob, pjob->buffer1, lspace);
                else
                    GpiCharString( pjob->pdata->pt_hps, strlen( pjob->buffer1), pjob->buffer1);
                }
            else
                GpiCharString( pjob->pdata->pt_hps, strlen( pjob->buffer1), pjob->buffer1);

            if ( strlen( pjob->buffer2) != 0)
                {
                bmore = TRUE;
                ptlhere.x = pjob->pdata->pt_lmargin;
                ptlhere.y -= linterline;

                /***** check for new page *******************************/

                if ( pjob->check_page && ( ptlhere.y < ( pjob->pdata->pt_bmargin + drop)))
                    {
                    fd_idx = pjob->pdata->pt_font_idx;
                    pts = pjob->pdata->pt_point_size;
                    PrtNewPage( pjob);
                    PrtSetFontSize( pjob, fd_idx, pts);
                    ptlhere.y = pjob->pdata->pt_prt_top - linterline;
                    } /* end of if */

                GpiMove( pjob->pdata->pt_hps, &ptlhere);

                strcpy( pjob->buffer1, pjob->buffer2);

                } /* end of if */

            } while ( bmore);

        } /* end of if */

    /***** else just write the string ***********************************/

    else
        {
        switch ( usJust)
            {
            case JUST_RIGHT :
                TST_TRACE(( "PrtWrite - NOTE - Justify right '%s'", szString))
                llen = PrtStringLen( pjob, szString);
                ptlhere.x = ledge - llen;
                GpiMove( pjob->pdata->pt_hps, &ptlhere);
                break;

            case JUST_CENTRE :
                TST_TRACE(( "PrtWrite - NOTE - Centre '%s'", szString))
                llen = PrtStringLen( pjob, szString);
                ptlhere.x = ((pjob->pdata->pt_wide - llen) / 2) + pjob->pdata->pt_lmargin;
                GpiMove( pjob->pdata->pt_hps, &ptlhere);
                break;

            default :
                break;

            } /* end of switch usJust */

        if (usJust == JUST_JUSTIFY)
            PrtJustified( pjob, szString, lspace);
        else
            GpiCharString( pjob->pdata->pt_hps, ( LONG)strlen( szString), szString);
        TST_TRACE(( "PrtWrite - NOTE - printed '%s'", szString))
        }

    if (usJust == JUST_JUSTIFY)
        {
        GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
        ptlhere.x = pjob->pdata->pt_lmargin;
        ptlhere.y -= linterline;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        }

    return TRUE;

    } // end of PrtWrite()


// **********************************************************************

BOOL PrtWriteln( PJOB_TYPE pjob, PSZ szString)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            linterline;
    BOOL            rc;

    if( !szString)
        return FALSE;

    /***** Get inter-line spacing from font metrics *********************/

    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;

    /***** Print the string *********************************************/

    rc = PrtWrite( pjob, szString, JUST_LEFT);

    /***** Find our present position ************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    /***** Insert line crlf *********************************************/

    ptlhere.x = pjob->pdata->pt_lmargin;
    ptlhere.y -= linterline;
    GpiMove( pjob->pdata->pt_hps, &ptlhere);

    return rc;

    } // end of PrtWriteln()


// **********************************************************************

BOOL PrtJustified( PJOB_TYPE pjob,
                   PSZ pszString,
                   LONG lspace)

// **********************************************************************

    {
    LONG            num_spaces,
                    lpsz,
                    cnt,
                    llen,
                    extra;
    SHORT           incr;
    FIXED           increment;

    if( !pszString)
        return FALSE;

    /***** Get the number of spaces in the string ***********************/

    llen = PrtStringLen( pjob, pszString);

    if (( llen > pjob->pdata->pt_wide) && ( strlen( pszString) == 1))
        return FALSE;

    extra = lspace - llen;
    lpsz = strlen( pszString);
    num_spaces = 0;

    for ( cnt = 0; cnt < lpsz; cnt++)
        {
        if (isspace( (int)pszString[ cnt]))
            num_spaces++;
        } /* end of for */

    /***** If no words just left ****************************************/

    if ( num_spaces == 0)
        {
        GpiCharString( pjob->pdata->pt_hps, lpsz, pszString);
        return TRUE;
        } /* end of if */

    /***** Calculate new space ******************************************/

    incr = ( SHORT)extra / ( SHORT)num_spaces;
    increment = MAKEFIXED( incr, 0);

    /***** print the string char by char ********************************/

    GpiSetCharBreakExtra( pjob->pdata->pt_hps, increment);
    GpiCharString( pjob->pdata->pt_hps, lpsz, pszString);
    increment = MAKEFIXED( 0, 0);
    GpiSetCharBreakExtra( pjob->pdata->pt_hps, increment);

    return TRUE;

    } // end of PrtJustified()


// **********************************************************************

VOID PrtWordBreak( PJOB_TYPE pjob,
                   LONG lmar,
                   LONG rmar)

// **********************************************************************

    {
    LONG            szlen = 0,
                    cnt;
    POINTL          ptl = {0L,0L};
    PPOINTL         aptl = NULL;
    int             i = 0,
                    j = 0;
    PSZ             p = NULL;

    /***** Get all the character positions ******************************/

    szlen = (LONG) strlen( pjob->buffer1);
    TST_TRACE(( "PrtWordBreak: NOTE - lm = %lu, rm = %lu strlen = %lu", lmar, rmar, szlen))
    aptl = ( PPOINTL) calloc( (szlen + 1), sizeof( POINTL));
    memset( aptl, 0, (szlen + 1) * sizeof( POINTL));

    TST_TRACE(( "PrtWordBreak: NOTE - Created array of %lu pointl", szlen + 1))
    if ( aptl == NULL)
        {
        TST_TRACE(( "PrtWordBreak: ERROR - Failed to calloc pointl array"))
        return;
        } /* end of if */

    ptl.x = 0;
    rmar -= lmar;
    ptl.y = 1000;

    GpiQueryCharStringPosAt( pjob->pdata->pt_hps, &ptl, 0L, szlen, pjob->buffer1, NULL, aptl);

    /***** BUG fix for Postscript ***************************************/

    for ( cnt = 0; cnt <= szlen; cnt++)
        {
        if ( aptl[ cnt].x < 0)
            {
            aptl[ cnt].x = aptl[ cnt].x ^ PS_MASK;
            } /* end of if */

        } /* end of for */

    /***** Check if string fits *****************************************/

    if ( aptl[ szlen].x <= rmar)
        {
        FREE( aptl);
        strcpy( pjob->buffer2, "");
        TST_TRACE(( "PrtWordBreak: NOTE - String fits"))
        return;
        }

    TST_TRACE(( "PrtWordBreak: NOTE - String doesn't fit"))

    /***** Find the first character that is too far right ***************/

    i = 0;
    while ( (aptl[ i].x < rmar) && (i < szlen))
        {
        i++;
        } /* end of while */
    j = i - 1;
    i = j;

    TST_TRACE(( "PrtWordBreak: NOTE - break string at or before %u", j))

    /***** Find the preceding white space *******************************/

    if( pjob->bWordBreak)
        {
        while ( i > 0)
            {
            if (isspace( (int)pjob->buffer1[ i]))
                break;
            i--;
            } /* end of while */
        }
    else
        i = 0;

    TST_TRACE(( "PrtWordBreak: NOTE - break string at %u", j))

    /***** If no white space split the string ***************************/

    if ( i == 0)
        {
        p = &pjob->buffer1[ j];
        strcpy( pjob->buffer2, p);
        pjob->buffer1[ j] = '\0';
        TST_TRACE(( "PrtWordBreak: NOTE - break string (no space) 1st part '%s'", pjob->buffer1))
        TST_TRACE(( "PrtWordBreak: NOTE - break string (no space) 2nd part '%s'", p))
        } /* end of if */

    /***** Else split at found space ************************************/

    else
        {
        pjob->buffer1[ i] = '\0';
        p = &pjob->buffer1[ i + 1];
        TST_TRACE(( "PrtWordBreak: NOTE - break string 1st part '%s' (%u)", pjob->buffer1, strlen( pjob->buffer1)))
        TST_TRACE(( "PrtWordBreak: NOTE - break string 2nd part '%s' (%lu)", p, strlen( p)))
        strcpy( pjob->buffer2, p);
        }

    TST_TRACE(( "PrtWordBreak: NOTE - returning '%s'", pjob->buffer2))
    FREE( aptl);

    } // end of PrtWordBreak()


// **********************************************************************

BOOL PrtCentre( PJOB_TYPE pjob, PSZ szString)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            linterline;
    BOOL            rc;

    if( !szString)
        return FALSE;

    /***** Get inter-line spacing from font metrics *********************/

    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;

    /***** Print the string *********************************************/

    rc = PrtWrite( pjob, szString, JUST_CENTRE);

    /***** Find our present position ************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    /***** Insert line crlf *********************************************/

    ptlhere.x = pjob->pdata->pt_lmargin;
    ptlhere.y -= linterline;

    GpiMove( pjob->pdata->pt_hps, &ptlhere);

    return rc;

    } // end of PrtCentre()


// **********************************************************************

BOOL PrtJustRight( PJOB_TYPE pjob, PSZ szString)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            linterline;
    BOOL            rc;

    if( !szString)
        return FALSE;

    /***** Get inter-line spacing from font metrics *********************/

    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;

    /***** Print the string *********************************************/

    rc = PrtWrite( pjob, szString, JUST_RIGHT);

    /***** Find our present position ************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    /***** Insert line crlf *********************************************/

    ptlhere.x = pjob->pdata->pt_lmargin;
    ptlhere.y -= linterline;

    GpiMove( pjob->pdata->pt_hps, &ptlhere);

    return rc;

    } // end of PrtJustRight()


BOOL PrtWriteCol( PJOB_TYPE pjob,
                  PSZ szFont,
                  LONG points,
                  PSZ szString,
                  USHORT usJust)

    {
    PTABLE_TYPE     ptable;
    SHORT           idx,
                    fd_idx;
    BOOL            bmore;
    LONG            wide,
                    len,
                    pts;

    if( !pjob || !szString)
        return FALSE;

    ptable = pjob->pdata->pt_table;

    if ( !strlen( ptable->aCol[ pjob->pdata->pt_col].cFont) && !szFont)
        return FALSE;

    if( strlen( szString) == 1)
        {
        wide = ( ptable->aCol[ pjob->pdata->pt_col].lrm_text -
                 ptable->aCol[ pjob->pdata->pt_col].llm_text) + 1;
        fd_idx = pjob->pdata->pt_font_idx;
        pts = pjob->pdata->pt_point_size;
        idx = PrtFontAvailable( pjob, szFont);
        if ( idx == -1)
            {
            idx = PrtNewFont( pjob, szFont);
            if ( idx == -1)
                return FALSE;
            } /* end of if */
        PrtSetFontSize( pjob, idx, points);
        len = PrtStringLen( pjob, szString);
        PrtSetFontSize( pjob, fd_idx, pts);
        if( len >= wide)
            return FALSE;
        }

    TST_TRACE(( "PrtWriteCol: Write to column %u", pjob->pdata->pt_col))

    /***** Set the font & size if necessary *****************************/

    TST_TRACE(( "PrtWriteCol: Check for font"))
    if (( strlen( ptable->aCol[ pjob->pdata->pt_col].cFont) == 0) && ( strlen( szFont) != 0))
        strcpy( ptable->aCol[ pjob->pdata->pt_col].cFont, szFont);

    TST_TRACE(( "PrtWriteCol: Check for points"))
    if(( ptable->aCol[ pjob->pdata->pt_col].lpts == 0) && ( points != 0))
        ptable->aCol[ pjob->pdata->pt_col].lpts = points;

    if(( ptable->aCol[ pjob->pdata->pt_col].lpts != 0) &&
        ( strlen( ptable->aCol[ pjob->pdata->pt_col].cFont) != 0))
        {
        TST_TRACE(( "PrtWriteCol: NOTE - set font '%s' %lu pts column %u",
                   ptable->aCol[ pjob->pdata->pt_col].cFont,
                   ptable->aCol[ pjob->pdata->pt_col].lpts, pjob->pdata->pt_col))

        idx = PrtFontAvailable( pjob, ptable->aCol[ pjob->pdata->pt_col].cFont);
        if ( idx == -1)
            idx = PrtNewFont( pjob, ptable->aCol[ pjob->pdata->pt_col].cFont);
        PrtSetFontSize( pjob, idx, ptable->aCol[ pjob->pdata->pt_col].lpts);
        }

    /***** Create a new line buffer for column **************************/

    ptable->aCol[ pjob->pdata->pt_col].uslines++;
    idx = ptable->aCol[ pjob->pdata->pt_col].uslines - 1;


    if( ptable->aCol[ pjob->pdata->pt_col].uslines == 1)
        {
        TST_TRACE(( "PrtWriteCol: NOTE - Allocate memory for string in column %u", pjob->pdata->pt_col))
        ptable->aCol[ pjob->pdata->pt_col].alines = ( PLINE_DESC) calloc( CELL_BLOCK, sizeof( LINE_DESC));
        TST_TRACE(( "PrtWriteCol: NOTE - Allocated memory for string in column %u (%p)", pjob->pdata->pt_col, ptable->aCol[ pjob->pdata->pt_col].alines))
        memset( ptable->aCol[ pjob->pdata->pt_col].alines, 0, CELL_BLOCK * sizeof( LINE_DESC));
        TST_TRACE(( "PrtWriteCol: NOTE - filled alines (%p) with 0", ptable->aCol[ pjob->pdata->pt_col].alines))
        ptable->aCol[ pjob->pdata->pt_col].usblock = CELL_BLOCK;
        }
    else
        if ( ptable->aCol[ pjob->pdata->pt_col].uslines == ptable->aCol[ pjob->pdata->pt_col].usblock)
            {
            TST_TRACE(( "PrtWriteCol: NOTE - Reallocate memory for string in column %u", pjob->pdata->pt_col))
            ptable->aCol[ pjob->pdata->pt_col].usblock += CELL_BLOCK;
            ptable->aCol[ pjob->pdata->pt_col].alines =
                    ( LINE_DESC*)realloc( ptable->aCol[ pjob->pdata->pt_col].alines,
                                          (size_t)ptable->aCol[ pjob->pdata->pt_col].usblock);
            }


    /***** Wrap the string if necessary *********************************/

    strcpy( pjob->buffer1, szString);

    do
        {
        bmore = FALSE;
        PrtWordBreak( pjob, ptable->aCol[ pjob->pdata->pt_col].llm_text,
                      ptable->aCol[ pjob->pdata->pt_col].lrm_text);

        strcpy( ptable->aCol[ pjob->pdata->pt_col].alines[ idx].pszLine, pjob->buffer1);

        TST_TRACE(( "PrtWriteCol - NOTE - input string is split '%s' (%u)",
                    ptable->aCol[ pjob->pdata->pt_col].alines[ idx].pszLine, idx))

        if ( strlen( pjob->buffer2) != 0)
            {
            bmore = TRUE;
            ptable->aCol[ pjob->pdata->pt_col].alines[ idx].usJust = usJust;
            ptable->aCol[ pjob->pdata->pt_col].uslines++;
            idx++;
            if ( ptable->aCol[ pjob->pdata->pt_col].uslines == ptable->aCol[ pjob->pdata->pt_col].usblock)
                {
                TST_TRACE(( "PrtWriteCol: NOTE - Reallocate memory for string in column %u", pjob->pdata->pt_col))
                ptable->aCol[ pjob->pdata->pt_col].usblock += CELL_BLOCK;
                ptable->aCol[ pjob->pdata->pt_col].alines =
                        ( LINE_DESC*)realloc( ptable->aCol[ pjob->pdata->pt_col].alines,
                                              ptable->aCol[ pjob->pdata->pt_col].usblock);
                }

            strcpy( pjob->buffer1, pjob->buffer2);

            } /* end of if */
        else
            {
            TST_TRACE(( "PrtWriteCol: NOTE - text fits in column %u", pjob->pdata->pt_col))
            if ( usJust == JUST_JUSTIFY)
                ptable->aCol[ pjob->pdata->pt_col].alines[ idx].usJust = JUST_LEFT;
            else
                ptable->aCol[ pjob->pdata->pt_col].alines[ idx].usJust = usJust;
            }
        } while ( bmore);

    ptable->aCol[ pjob->pdata->pt_col].usnewpage = ptable->aCol[ pjob->pdata->pt_col].uslines;

    TST_TRACE(( "PrtWriteCol: NOTE - completed successfully"))

    return TRUE;

    } // end of PrtWriteCol()


// **********************************************************************

VOID PrtSetBorder( PJOB_TYPE pjob)

// **********************************************************************

    {

    if ( pjob->pdata->pt_footer)
        {
        pjob->pdata->pt_border_bl.x = pjob->pdata->pt_ftr_bl.x;
        pjob->pdata->pt_border_bl.y = pjob->pdata->pt_ftr_bl.y;
        }
    else
        {
        pjob->pdata->pt_border_bl.x = pjob->pdata->pt_lmargin - ( pjob->pdata->pt_border + ONE_MIL);
        pjob->pdata->pt_border_bl.y = pjob->pdata->pt_bl_offset.cy - ( pjob->pdata->pt_border + ONE_MIL);
        }
    if ( pjob->pdata->pt_header)
        {
        pjob->pdata->pt_border_tr.x = pjob->pdata->pt_hdr_tr.x;
        pjob->pdata->pt_border_tr.y = pjob->pdata->pt_hdr_tr.y;
        }
    else
        {
        pjob->pdata->pt_border_tr.x = pjob->pdata->pt_rmargin + pjob->pdata->pt_border + ONE_MIL;
        pjob->pdata->pt_border_tr.y = pjob->pdata->pt_tr_margin.cy + pjob->pdata->pt_border + ONE_MIL;
        }

    } // end of PrtSetBorder()


// **********************************************************************

VOID PrtSetHeaderBox( PJOB_TYPE pjob)

// **********************************************************************

    {
    ULONG           interline,
                    ulhigh,
                    ldrop;
    USHORT          i;


    if( !pjob->pdata->pt_hlines)
        {
        interline = (( pjob->pdata->pt_hpts * ONE_POINT) * LINE_SPACE) / 100;
        ldrop = ( 4 * ONE_MIL);
        interline += ldrop;
        }
    else
        {
        interline = 0L;
        for ( i = 0; i < pjob->pdata->pt_hlines; i++)
            {
            ulhigh = (( pjob->pdata->pt_psz[ i].lpts * ONE_POINT) * LINE_SPACE) / 100;
            interline += ulhigh;
            } /* end of for */
        ldrop = ( 2 * ONE_MIL);
        interline += ldrop;
        } /* end of else */


    if ( pjob->pdata->pt_header)
        {
        pjob->pdata->pt_hdr_tr.x = pjob->pdata->pt_rmargin + pjob->pdata->pt_hbox_line + ONE_MIL;
        pjob->pdata->pt_hdr_tr.y = pjob->pdata->pt_tr_margin.cy + pjob->pdata->pt_hbox_line + ONE_MIL;
        pjob->pdata->pt_hdr_bl.x = pjob->pdata->pt_lmargin - ( pjob->pdata->pt_hbox_line + ONE_MIL);
        pjob->pdata->pt_hdr_bl.y = pjob->pdata->pt_hdr_tr.y - interline;
        }

    if ( pjob->pdata->pt_footer)
        {
        interline = (( pjob->pdata->pt_fpts * ONE_POINT) * LINE_SPACE) / 100;
        interline += ( ULONG)( ONE_MIL);

        if ( pjob->pdata->pt_header)
            pjob->pdata->pt_ftr_tr.x = pjob->pdata->pt_hdr_tr.x;
        else
            pjob->pdata->pt_ftr_tr.x = pjob->pdata->pt_rmargin + pjob->pdata->pt_fbox_line + ONE_MIL;
            pjob->pdata->pt_ftr_bl.y = pjob->pdata->pt_bl_offset.cy - ( pjob->pdata->pt_fbox_line + ONE_MIL);
        if ( pjob->pdata->pt_header)
            pjob->pdata->pt_ftr_bl.x = pjob->pdata->pt_hdr_bl.x;
        else
            pjob->pdata->pt_ftr_bl.x = pjob->pdata->pt_lmargin - ( pjob->pdata->pt_fbox_line + ONE_MIL);
        pjob->pdata->pt_ftr_tr.y = pjob->pdata->pt_ftr_bl.y + interline;
        pjob->pdata->pt_bmargin = pjob->pdata->pt_ftr_tr.y;
        }
    else
        pjob->pdata->pt_bmargin = pjob->pdata->pt_bl_offset.cy;

    } // end of PrtSetHeaderBox()


// **********************************************************************

VOID PrtGetPrinterList( )

// **********************************************************************

    {
    ULONG           cbBuf;
    ULONG           cTotal;
    ULONG           cReturned;
    ULONG           cbNeeded;
    ULONG           ulCount;
    ULONG           level = 1L;
    ULONG           i,cnt;
    USHORT          j, usJobs;
    PSZ             computer_name = NULL;
    PBYTE           pbuffer = NULL;
    PRINTER_INFO_1  *prq;
    char            *p;

    RequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);

    pPrtList.prt_count = 0;

    /***** Clear array of printer names *********************************/

    for ( i = 0; i < MAX_OPEN_DEVS; i++)
        FREE( pPrtList.szPrinterList[ i]);

    /******* 1. Get size of data for queues *****************************/

    EnumPrinters( PRINTER_ENUM_NAME, computer_name, level,
                       pbuffer, 0, &cbNeeded, &cReturned);

    pBuffer = ( PBYTE)malloc( cbNeeded);
    cbBuf = cbNeeded;

    if( EnumPrinters( PRINTER_ENUM_NAME, computer_name, level,
                       pbuffer, cbBuf, &cbNeeded, &ulCount))
            {

            pPrtList.prt_count = ulCount;
/*
            for ( cnt = 0; cnt < MAX_OPEN_DEVS; cnt++)
                {
                FREE( pPrtList.aDevStruct[ cnt].pszLogAddress);
                FREE( pPrtList.aDevStruct[ cnt].pszDriverName);
                FREE( pPrtList.aDevStruct[ cnt].pdriv);
                FREE( pPrtList.aDevStruct[ cnt].pszDataType);
                }
*/
            /******* 3. Point to beginning of list **********************/

            prq = (PRINTER_INFO_1*)pbuffer;

            /******* 4. Extract required data ***************************/

            if( pPrtList.prt_count > MAX_OPEN_DEVS)
                pPrtList.prt_count = MAX_OPEN_DEVS;

            for ( i = 0; i < pPrtList.prt_count; i++)
                {
                pPrtList.aDevStruct[ i].pszLogAddress = strdup( prq->pszName);
                TST_TRACE(( "PrtGetPrinterList: pszName = %s",
                            pPrtList.aDevStruct[ i].pszLogAddress))

                TST_TRACE(( "PrtGetPrinterList: prq->pszDriverName = %s",
                            prq->pszDriverName))
                p = strchr( prq->pszDriverName, (int)'.');
                if ( p)
                    *p = '\0';

                pPrtList.aDevStruct[ i].pszDriverName = strdup( prq->pszDriverName);
                TST_TRACE(( "PrtGetPrinterList: Driver Name = %s", prq->pszDriverName))

                pPrtList.aDevStruct[ i].pszDataType = strdup( "PM_Q_STD");

                pPrtList.szPrinterList[ i] = strdup( prq->pszComment);

                pPrtList.aDevStruct[ i].pdriv = ( PDRIVDATA) malloc((size_t) prq->pDriverData->cb);
                memcpy( pPrtList.aDevStruct[ i].pdriv, prq->pDriverData, prq->pDriverData->cb);

                if (( prq->fsType & PRQ3_TYPE_APPDEFAULT) == PRQ3_TYPE_APPDEFAULT)
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

    DosReleaseMutexSem( pPrtList.hmtx);

    } // end of PrtGetPrinterList()


// **********************************************************************

VOID PrtGetDateString( PJOB_TYPE pjob)

// **********************************************************************

    {
    DATETIME        pt_time;            /* time date of creation */
    ULONG           buflen;
    char            sep[ 10],
                    dtype[ 10],
                    *pt,
                    sAM[ 10],
                    sPM[ 10];
    int             dt;

    /***** Get the date *************************************************/

    DosGetDateTime( &pt_time );

    /***** Get the date format from the system **************************/

    buflen = 10;
    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "iDate", "2", dtype, buflen);
    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "sDate", ".", sep, buflen);
    dt = atoi( dtype);

    switch ( dt)
        {
        case 0 :        /* US Date */
            sprintf( pjob->pdata->date_str, "%02u%s%02u%s%4u",
                     pt_time.month, sep,
                     pt_time.day, sep,
                     pt_time.year);
            break;

        case 1 :        /* EU Date */
            sprintf( pjob->pdata->date_str, "%02u%s%02u%s%4u",
                     pt_time.day, sep,
                     pt_time.month, sep,
                     pt_time.year);
            break;

        case 2 :        /* ISO Date */
            sprintf( pjob->pdata->date_str, "%04u%s%02u%s%02u",
                     pt_time.year, sep,
                     pt_time.month, sep,
                     pt_time.day);
            break;

        default :       /* ISO Date */
            sprintf( pjob->pdata->date_str, "%04u.%02u.%02u",
                     pt_time.year,
                     pt_time.month,
                     pt_time.day);

            break;

        } /* end of switch dt */

    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "iTime", "1", dtype, buflen);
    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "sTime", ":", sep, buflen);
    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "s1159", ":", sAM, buflen);
    PrfQueryProfileString( HINI_USERPROFILE, "PM_National", "s2359", ":", sPM, buflen);
    dt = atoi( dtype);

    switch ( dt)
        {
        case 0 :
            if( pt_time.hours > 11)
                {
                pt_time.hours -= 12;
                pt = sPM;
                }
            else
                pt = sAM;

            sprintf( pjob->pdata->time_str, "%02u%s%02u %s",
                     pt_time.hours,
                     sep,
                     pt_time.minutes,
                     pt);
            break;

        case 1 :
            sprintf( pjob->pdata->time_str, "%02u%s%02u",
                     pt_time.hours,
                     sep,
                     pt_time.minutes);
            break;

        default :
            sprintf( pjob->pdata->time_str, "%02u:%02u",
                     pt_time.hours,
                     pt_time.minutes);
            break;

        } // end of switch dtype

    } // end of PrtGetDateString()


// **********************************************************************

VOID PrtWriteFormatted( PJOB_TYPE pjob,
                        PSZ szString,
                        BOOL bTable,
                        USHORT usCol)

// **********************************************************************

    {
    PSZ             p, q,
                    psz;
    char            temp[ 256],
                    cbuffer[ 512];
    USHORT          just1,
                    just2,
                    cnt, i;
    BOOL            print;
    LONG            lstr,
                    lcwide;
    POINTL          ptlprt;
    LINE_DESC       olines[ 10];

    TST_TRACE(( "PrtWriteFormatted: NOTE - print (%s) %p", szString, szString))

    if( !szString)
        return;

    strcpy( cbuffer, szString);
    TST_TRACE(( "PrtWriteFormatted: NOTE - copied string (%s)", cbuffer))

    p = strchr( cbuffer, FLAG_CHAR);
    TST_TRACE(( "PrtWriteFormatted: NOTE - searched for flag (%p)", p))

    if ( p == NULL)
        {
        PrtWrite( pjob, cbuffer, JUST_LEFT);
        return;
        }

    TST_TRACE(( "PrtWriteFormatted: NOTE - got flag from (%s)", p))

    just2 = JUST_LEFT;
    cnt = 0;

    do
        {
        psz = cbuffer;
        just1 = just2;
        q = p;
        p++;
        *q = '\0';

        TST_TRACE(( "PrtWriteFormatted: NOTE - checking to find (%c)", *p))
        print = TRUE;

        switch ( *p)
            {
            case LEFT_CHAR :
            case RIGHT_CHAR :
            case CENTRE_CHAR :
                if( *p == LEFT_CHAR)
                    just2 = JUST_LEFT;
                else if( *p == RIGHT_CHAR)
                    just2 = JUST_RIGHT;
                else if( *p == CENTRE_CHAR)
                    just2 = JUST_CENTRE;
                p++;
                switch ( *p)
                    {
                    case DATE_CHAR :
                        p++;
                        sprintf( temp, "%s%s", pjob->pdata->date_str, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found date flag (%s)", temp))
                        break;

                    case TIME_CHAR :
                        p++;
                        sprintf( temp, "%s%s", pjob->pdata->time_str, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found time flag (%s)", temp))
                        break;

                    case DTIME_CHAR :
                        p++;
                        sprintf( temp, "%s %s%s", pjob->pdata->date_str, pjob->pdata->time_str, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found time flag (%s)", temp))
                        break;

                    case TITLE_CHAR :
                    case TITLE_CHAR_ALT :
                        p++;
                        sprintf( temp, "%s%s", pjob->pdata->doc_name, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found title flag (%s)", temp))
                        break;

                    case PAGE_CHAR :
                        p++;
                        sprintf( temp, "%u%s", pjob->pdata->pt_page, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found page flag (%s)", temp))
                        break;

                    default :
                        strcpy( temp, p);
                        TST_TRACE(( "PrtWriteFormatted: NOTE - found nothing (%s)", temp))
                        break;

                    } /* end of switch &p */

                break;

            case DATE_CHAR :
                p++;
                sprintf( temp, "%s%s%s", psz, pjob->pdata->date_str, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found date flag (%s)", temp))
                print = FALSE;
                break;

            case TIME_CHAR :
                p++;
                sprintf( temp, "%s%s%s", psz, pjob->pdata->time_str, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found time flag (%s)", temp))
                print = FALSE;
                break;

            case DTIME_CHAR :
                p++;
                sprintf( temp, "%s%s %s%s", psz, pjob->pdata->time_str, pjob->pdata->time_str, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found time flag (%s)", temp))
                print = FALSE;
                break;

            case TITLE_CHAR :
            case TITLE_CHAR_ALT :
                p++;
                sprintf( temp, "%s%s%s", psz, pjob->pdata->doc_name, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found title flag (%s)", temp))
                print = FALSE;
                break;

            case PAGE_CHAR :
                p++;
                sprintf( temp, "%s%u%s", psz, pjob->pdata->pt_page, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found page flag (%s)", temp))
                print = FALSE;
                break;

            default :
                sprintf( temp, "%s%c%s", psz, REP_CHAR, p);
                TST_TRACE(( "PrtWriteFormatted: NOTE - found nothing (%s)", temp))
                print = FALSE;
                break;

            } /* end of switch *p */


        if ( print)
            {
            olines[ cnt].usJust = just1;
            strcpy( olines[ cnt].pszLine, psz);
            TST_TRACE(( "PrtWriteFormatted: NOTE - copied string to olines %u (%s)", cnt, olines[ cnt].pszLine))
            cnt++;
            }

        strcpy( cbuffer, temp);

        p = strchr( cbuffer, FLAG_CHAR);

        } while ( p != NULL);

    olines[ cnt].usJust = just2;
    strcpy( olines[ cnt].pszLine, cbuffer);
    TST_TRACE(( "PrtWriteFormatted: NOTE - copied string to olines %u (%s)", cnt, olines[ cnt].pszLine))
    cnt++;

    /***** Print it *****************************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlprt);

    for ( i = 0; i < cnt; i++)
        {
        PrtFixFlagChars( olines[ i].pszLine);
        if( !bTable)
            PrtWrite( pjob, olines[ i].pszLine, olines[ i].usJust);
        else
            {
            lcwide = pjob->pdata->pt_table->aCol[ usCol].lrm_text - pjob->pdata->pt_table->aCol[ usCol].llm_text;
            lstr = PrtStringLen( pjob, olines[ i].pszLine);
            switch ( olines[ i].usJust)
                {
                case JUST_RIGHT :
                    ptlprt.x = pjob->pdata->pt_table->aCol[ usCol].lrm_text - lstr;
                    break;

                case JUST_CENTRE :
                    ptlprt.x = pjob->pdata->pt_table->aCol[ usCol].llm_text + ((lcwide - lstr) / 2);
                    break;

                default :
                    ptlprt.x = pjob->pdata->pt_table->aCol[ usCol].llm_text;
                    break;

                } /* end of switch  */

            GpiMove( pjob->pdata->pt_hps, &ptlprt);

            GpiCharString( pjob->pdata->pt_hps,
                           (LONG)strlen( olines[ i].pszLine),
                           olines[ i].pszLine);

            } /* end of else */

        } /* end of for */

    } // end of PrtWriteFormatted()


// **********************************************************************

BOOL PrtDrawBitMap( PJOB_TYPE   pjob,
                    PSZ         file_name,
                    POINTL      bl,
                    POINTL      tr,
                    LONG        th,
                    LONG        lcolor,
                    PSZ         title)

// **********************************************************************

    {
    POINTL              ptlhere;
    ULONG               faction = 0;
    APIRET              ioerr = 0;
    HFILE               hfile = (HFILE)0;
    HPS                 hps = (HPS)0;
    HDC                 hdc = (HDC)0;
    HBITMAP             hbm = (HBITMAP)0;
    POINTL              aptl[ 4];
    SIZEL               sizl = {0, 0};
    FILESTATUS3         fsts;
    PBITMAPFILEHEADER2  pbfh2;                  /* can address any file types */
    PBITMAPINFOHEADER2  pbmp2;                  /* address any info headers */
    PBYTE               pFileBegin = NULL;      /* beginning of bitmap file data */
    PBYTE               pBits;
    PBYTE               pBitsAligned;
    ULONG               cbImageData;
    ULONG               cbRead;                 /* Number of bytes read by DosRead. */
    ULONG               cScans,
                        lx, ly,
                        cScansRet;              /* number of scan lines in bitmap (cy) */
    USHORT              planes,
                        bitcount;
    LONG                cColors;                /* number of colors */
    PLONG               alColor;                /* color table array */

    if( pjob->pdata->pt_table && pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].bitmap)
        return FALSE;

    /***** Get the current position *************************************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    /***** Create device context etc.. for bitmap ***********************/

    hdc = DevOpenDC( pjob->hab, OD_MEMORY, "*",
                     5L, ( PDEVOPENDATA)&(pjob->DevStruct),
                     NULLHANDLE);
//                    0, NULL, pjob->pdata->pt_hdc);

    if ( hdc == DEV_ERROR)
        {
        TRACEWINERRORN( "PrtDrawBitMap: ERROR - DevOpenDC failed severity %X error %X")
        return( FALSE);
        }

    /***** Set the presentation space ***********************************/

    hps = GpiCreatePS( pjob->hab,
                       hdc, &sizl,
                       PU_PELS | GPIA_ASSOC);

    if ( hps == GPI_ERROR)
        {
        TRACEWINERRORN( "PrtDrawBitMap: ERROR - GpiCreatePS  failed severity %X error %X")
        DevCloseDC( hdc);
        return FALSE;
        }

    /***** Open the file ************************************************/

    ioerr = DosOpen( file_name, &hfile, &faction, 0L,
                     FILE_NORMAL, FILE_OPEN,
                     OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
                     NULL);
    TST_TRACE(( "PrtDrawBitMap: Opened file <%s> (%lu)", file_name, ioerr))
    if ( ioerr)
        return( FALSE);

    /***** Read in the bitmap *******************************************/

    if ( DosQueryFileInfo( hfile, FIL_STANDARD, &fsts, sizeof(fsts)))
        {
        DosClose( hfile);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

    /***** Create the buffer to load ************************************/

    pFileBegin = ( PBYTE) malloc( fsts.cbFile);
    TST_TRACE(( "PrtDrawBitMap: NOTE - created buffer %lu bytes", fsts.cbFile))

    /***** Read the buffer **********************************************/

    if ( DosRead( hfile, (PVOID)pFileBegin, fsts.cbFile, &cbRead))
        {
        DosClose( hfile);
        FREE( pFileBegin);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

    /***** Close Bitmap file ********************************************/

    DosClose( hfile);
    TST_TRACE(( "PrtDrawBitMap: NOTE - Closed the file"))

    /***** Check what kind of bitmap ************************************/

    pbfh2 = (PBITMAPFILEHEADER2) pFileBegin;
    pbmp2 = NULL;                   /* only set this when we validate type */

    switch (pbfh2->usType)
        {
        case BFT_BITMAPARRAY:
            pbfh2 = &(((PBITMAPARRAYFILEHEADER2) pFileBegin)->bfh2);
            pbmp2 = &pbfh2->bmp2;    /* pointer to info header (readability) */
            cbImageData = fsts.cbFile - pbfh2->offBits;
            pBits = (PBYTE)pbfh2 + pbfh2->offBits;
            break;

        case BFT_BMAP:
            pbmp2 = &pbfh2->bmp2;    /* pointer to info header (readability) */
            cbImageData = fsts.cbFile - pbfh2->offBits;
            pBits = (PBYTE)pbfh2 + pbfh2->offBits;
            break;

        case BFT_ICON:
        case BFT_POINTER:
        case BFT_COLORICON:
        case BFT_COLORPOINTER:
        default:      /* these formats aren't supported; don't set any ptrs */
            break;

        }   /* end switch (pbfh2->usType) */

    /***** Check if it was valid ****************************************/

    if (pbmp2 == NULL)
        {
        FREE( pFileBegin);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

// printf( "File header: usType = %u cbSize = %lu offBits = %lu\n",
//         pbfh2->usType, pbfh2->cbSize, pbfh2->offBits);
// printf( "Info block is %lu bytes\n", 14 + pbfh2->bmp2.cbFix);
    /*
     *   Check to see if BMP file has an old structure, a new structure, or
     *   Windows structure.  Capture the common data and treat all bitmaps
     *   generically with pointer to new format.  API's will determine format
     *   using cbFixed field.
     *
     *   Windows bitmaps have the new format, but with less data fields
     *   than PM.  The old strucuture has some different size fields,
     *   though the field names are the same.
     *
     *
     *   NOTE: bitmap data is located by offsetting the beginning of the file
     *         by the offset contained in pbfh2->offBits.  This value is in
     *         the same relative location for different format bitmap files.
    */

    if (pbmp2->cbFix == sizeof(BITMAPINFOHEADER))           /* old format? */
        {
        cScans = (ULONG) ((PBITMAPINFOHEADER)pbmp2)->cy;
// printf( "PrtDrawBitMap: NOTE - OLD FORMAT cbFix %lu, cx %lu, cy %lu\n",
//                     pbmp2->cbFix,
//                     (ULONG) ((PBITMAPINFOHEADER)pbmp2)->cx,
//                     (ULONG) ((PBITMAPINFOHEADER)pbmp2)->cy);

        lx = (ULONG) ((PBITMAPINFOHEADER)pbmp2)->cx;
        ly = (ULONG) ((PBITMAPINFOHEADER)pbmp2)->cy;
        planes = ((PBITMAPINFOHEADER)pbmp2)->cPlanes;
        bitcount = ((PBITMAPINFOHEADER)pbmp2)->cBitCount;
        }
    else
        {                              /* new PM format, Windows, or other */
        cScans = pbmp2->cy;
// printf( "PrtDrawBitMap: NOTE - NEW FORMAT cbFix %lu, cx %lu, cy %lu\n",
//                     pbmp2->cbFix,
//                     pbmp2->cx,
//                     pbmp2->cy);

        lx = pbmp2->cx;
        ly = pbmp2->cy;
        planes = pbmp2->cPlanes;
        bitcount = pbmp2->cBitCount;
        }

// printf( "PrtDrawBitMap: planes = %u bitcount = %u\n", planes, bitcount);

    TST_TRACE(( "PrtDrawBitMap: NOTE - got %lu scan lines", cScans))

    hbm = GpiCreateBitmap( hps, pbmp2, 0L, NULL, NULL);
    TST_TRACE(( "PrtDrawBitMap: NOTE - GpiCreateBitmap returned %lu", hbm))

    if (!hbm)
        {
        FREE( pFileBegin);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

// printf( "PrtDrawBitMap: Copy color table %lu bytes\n", (pbfh2->offBits - (14 + pbmp2->cbFix)));

    cColors = (pbfh2->offBits - (14 + pbmp2->cbFix)) / sizeof( ULONG);

// printf( "PrtDrawBitMap: %lu entries in color table\n", cColors);

    alColor = ( PLONG)malloc( (pbfh2->offBits - (14 + pbmp2->cbFix)));
    alColor = memcpy( alColor, pbmp2 + pbmp2->cbFix, (pbfh2->offBits - (14 + pbmp2->cbFix)));

// printf( "PrtDrawBitMap: Copied color table %lu bytes\n", (pbfh2->offBits - (14 + pbmp2->cbFix)));

    if ( GpiSetBitmap( hps, hbm) == HBM_ERROR)
        {
        FREE( pFileBegin);
        FREE( alColor);
        GpiDeleteBitmap( hbm);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

    /***** Shove scan linesinto presentation space **********************/

// printf( "PrtDrawBitMap: Align bitmap bits %lu bytes\n", cbImageData);

    pBitsAligned = (PBYTE) malloc( cbImageData );
    memcpy( pBitsAligned, pBits, cbImageData );

// printf( "PrtDrawBitMap: Aligned bitmap bits %lu bytes\n", cbImageData);

    cScansRet = GpiSetBitmapBits( hps, 0L, cScans,
                                  pBitsAligned,
                                  (PBITMAPINFO2) pbmp2);

    if (cScansRet != cScans)                         /* original # of scans? */
        {
        FREE( pFileBegin);
        FREE( pBitsAligned);
        FREE( alColor);
        GpiDeleteBitmap( hbm);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        return( FALSE);
        }

    /***** Set coordinates for transfer ********************************/

    aptl[ 2].x = 0;
    aptl[ 2].y = 0;
    aptl[ 3].x = lx;
    aptl[ 3].y = ly;

    aptl[ 0].x = bl.x;
    aptl[ 0].y = bl.y;
    if( tr.x == 0)
        tr.x = bl.x + ( LONG)((double)lx * pjob->pdata->xpels * pjob->pdata->aspect);
    aptl[ 1].x = tr.x;
    if( tr.y == 0)
        tr.y = bl.y + ( LONG)((double)ly * pjob->pdata->ypels * pjob->pdata->aspect);
    aptl[ 1].y = tr.y;

    if( pjob->pdata->pt_table)
        {
        PrtSetCellBitmap( pjob, hbm, aptl, hps, cColors, alColor, pbmp2, title);
        FREE( pFileBegin);
        FREE( pBitsAligned);
        return TRUE;
        }

// printf( "PrtDrawBitMap: NOTE - source (%lu,%lu) to (%lu,%lu)\n",
//                aptl[ 2].x, aptl[ 2].y, aptl[ 3].x, aptl[ 3].y);
// printf( "PrtDrawBitMap: NOTE - target (%lu,%lu) to (%lu,%lu)\n",
//                aptl[ 0].x, aptl[ 0].y, aptl[ 1].x, aptl[ 1].y);

    /***** Shove the bitmap at the printer ******************************/

    GpiSetBitmap( hps, 0L );

    if ( !PrtBitmapOut( pjob, aptl, hbm, cColors, alColor))
        {
// printf( "PrtDrawBitMap - ERROR PrtBitmapOut failed\n");
        GpiDeleteBitmap( hbm);
        GpiResetPS( hps, GRES_ALL);
        GpiAssociate( hps, NULLHANDLE);
        GpiDestroyPS( hps);
        DevCloseDC( hdc);
        FREE( pFileBegin);
        FREE( pBitsAligned);
        FREE( alColor);
        return FALSE;
        } // end of if

// printf( "PrtDrawBitMap : PrtBitmapOut succeeded\n");

    /***** If picture is framed *****************************************/

    if ( th > 0)
        PrtBox( pjob, bl, tr, th, 0, BOX_ALL, lcolor, pjob->lColor);

    /***** Clean up bitmap stuff ****************************************/

    GpiDeleteBitmap( hbm);
    GpiResetPS( hps, GRES_ALL);
    GpiAssociate( hps, NULLHANDLE);
    GpiDestroyPS( hps);
    DevCloseDC( hdc);
    FREE( pFileBegin);
    FREE( pBitsAligned);
    FREE( alColor);

    /***** Set the current position back to where we were ***************/

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);

    if( title)
        PrtWriteTitle( pjob, title, bl.x, tr.x);

    TST_TRACE(( "PrtDrawBitMap: NOTE - returns TRUE"))

    return( TRUE);

    } // end of PrtDrawBitMap()


// **********************************************************************

VOID PrtFixFlagChars( PSZ psz)

// **********************************************************************

    {
    PSZ           p;

    p = strchr( psz, REP_CHAR);

    while ( p)
        {
        *p = FLAG_CHAR;
        p = strchr( psz, REP_CHAR);
        } /* end of while */

    } // end of PrtFixFlagChars()


// **********************************************************************

PSZ PrtChooseFont( PJOB_TYPE    pjob,
                   PSZ          pszTitle,
                   PSZ          pszFamName)

// **********************************************************************

    {
    FONTDLG         fdFontDlg;
    FIXED           fxFSize;
    SIZEL           sizl = {0, 0};
    char            pszPreview[ 12];
    HDC             hdc;
    HPS             hps,
                    hpsW;
    HWND            hwndFd;

    memset ( &fdFontDlg, 0, sizeof ( FONTDLG ));
    strcpy( pjob->pszfont, "");
    strcpy( pszPreview, "abcABC");

    hdc = DevOpenDC( pjob->hab,
                     OD_INFO,
                     "*",
                     3L,
                     ( PDEVOPENDATA)&( pjob->DevStruct),
                     (HDC)NULL);

    if ( hdc == DEV_ERROR)
        {
        TST_TRACE(( "PrtChooseFont: ERROR - Failed to open device context"))
        DosReleaseMutexSem( pPrtList.hmtx);
        return( pjob->pszfont);
        }

    hps = GpiCreatePS( WinQueryAnchorBlock( WinQueryFocus( HWND_DESKTOP)),
                       hdc,
                       (PSIZEL)&sizl,
                       PU_TWIPS | GPIA_ASSOC | GPIF_LONG);

    if ( hps == GPI_ERROR)
        {
        TST_TRACE(( "PrtChooseFont: ERROR - Failed to create presentation space"))
        DevCloseDC( hdc);
        DosReleaseMutexSem( pPrtList.hmtx);
        return( pjob->pszfont);
        }

    hpsW = WinGetPS ( HWND_DESKTOP);
    fxFSize = MAKEFIXED( 10, 0);
    memset( &fdFontDlg, 0, sizeof ( FONTDLG ));

    fdFontDlg.cbSize = sizeof ( FONTDLG );
    fdFontDlg.hpsScreen = hpsW;
    fdFontDlg.hpsPrinter = hps;
    fdFontDlg.pszTitle = pszTitle;
    fdFontDlg.pszFamilyname = pszFamName;
    fdFontDlg.usFamilyBufLen = 256;
    fdFontDlg.pszPreview = pszPreview;

    fdFontDlg.fl = FNTS_CENTER;
    fdFontDlg.flFlags = FNTF_NOVIEWSCREENFONTS;
    fdFontDlg.clrFore = CLR_NOINDEX;
    fdFontDlg.clrBack = CLR_NOINDEX;

    strcpy( fdFontDlg.fAttrs.szFacename, "");
    fdFontDlg.fAttrs.fsSelection = FATTR_SEL_OUTLINE;
    fdFontDlg.fxPointSize = fxFSize;

    hwndFd = WinFontDlg ( HWND_DESKTOP,
                          pjob->hwnd,
                          &fdFontDlg );
    if( hwndFd && ( fdFontDlg.lReturn == DID_OK))
        {
        strcpy( pszFamName, fdFontDlg.fAttrs.szFacename);
        sprintf ( pjob->pszfont,
                  "%d.%s",
                  FIXEDINT ( fdFontDlg.fxPointSize ),
                  fdFontDlg.fAttrs.szFacename );
        } /* endif */

    GpiDestroyPS( hps);
    GpiDestroyPS( hpsW);
    DevCloseDC( hdc);
    DosReleaseMutexSem( pPrtList.hmtx);

    return( pjob->pszfont);

    } // end of PrtChooseFont()



// **********************************************************************

USHORT PrtEndRow( PJOB_TYPE pjob)

// **********************************************************************

    {
    PTABLE_TYPE     ptable;
    POINTL          ptltr,
                    ptlbl,
                    ptlprt;
    USHORT          uscol,
                    usbox_type,
                    usbt,
                    uslines,
                    usclines,
                    i, j, cnt;
    LONG            lvspace,
                    lvhigh,
                    high,
                    lvbot,
                    lstr,
                    lcwide,
                    ldrop,
                    ltemp,
                    lline;
    BOOL            bNofit = FALSE,
                    bNofitBefore = FALSE;
    SHORT           idx;


    ptable = pjob->pdata->pt_table;
    uscol = ptable->usCols;
    ldrop = 0;

    if ( ptable->bFirstRow)
        {
        lvspace = ptable->ptltr.y - pjob->pdata->pt_bmargin;
        lvspace -= (ONE_MIL * 4);
        if ( lvspace <= 0)
            bNofit = TRUE;
        else
            {
            for ( i = 0; i < uscol; i++)
                {
                lline = ((ptable->aCol[ i].lpts * ONE_POINT) * pjob->usline_space) / 100;
                if( lline >= lvspace)
                    bNofit = TRUE;
                }

            } // end of else

        if( bNofit)
            {
            PrtNewPage( pjob);
            ptable->ptltr.y = pjob->pdata->pt_prt_top - ONE_MIL;
            ptable->ly_pos = ptable->ptltr.y;
            if( ptable->bAllPages)
                PrtWriteTableHeader( pjob);
            }

        ptable->bFirstRow = FALSE;
        ptable->bNewPage = FALSE;

        } // end of if

    if ( ptable->bNewPage)
        {
        ptltr.y = ptable->ptltr.y;
        ptlbl.y = ptltr.y - (ONE_MIL * 4);
        usbox_type = ptable->boxtype & ~BOX_BOT;

        for ( i = 0; i < uscol; i++)
            {
            usbt = usbox_type;
            if( (( usbox_type & BOX_LEFT) == BOX_LEFT) &&
                (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                (i == 0))
                usbt = usbox_type & ~BOX_LEFT;

            if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                (i == (uscol - 1)))
                usbt = usbox_type & ~BOX_RIGHT;

            TST_TRACE(( "PrtEndRow: NOTE - Print box type %u for cell %u", usbox_type, i))
            ptltr.x = ptable->aCol[ i].lrm_box;
            ptlbl.x = ptable->aCol[ i].llm_box;
            PrtBox( pjob,
                    ptlbl,
                    ptltr,
                    ptable->lline_type,
                    ptable->lfill,
                    usbt,
                    ptable->llcolor,
                    ptable->lfcolor);
            } /* end of for */

        PrtNewPage( pjob);
        ptable->ptltr.y = pjob->pdata->pt_prt_top - ONE_MIL;
        ptable->ly_pos = ptable->ptltr.y;
        if( ptable->bAllPages)
            PrtWriteTableHeader( pjob);
        else
            {
            usbox_type = ptable->boxtype & ~BOX_TOP;
            ptltr.y = ptable->ptltr.y;
            ptlbl.y = ptltr.y - (ONE_MIL * 4);
            ptable->ptltr.y = ptlbl.y;

            for ( i = 0; i < uscol; i++)
                {
                usbt = usbox_type;
                if( (( usbox_type & BOX_LEFT) == BOX_LEFT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == 0))
                    usbt = usbox_type & ~BOX_LEFT;

                if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == (uscol - 1)))
                    usbt = usbox_type & ~BOX_RIGHT;

                TST_TRACE(( "PrtEndRow: NOTE - Print box type %u for cell %u", usbox_type, i))
                ptltr.x = ptable->aCol[ i].lrm_box;
                ptlbl.x = ptable->aCol[ i].llm_box;
                PrtBox( pjob,
                        ptlbl,
                        ptltr,
                        ptable->lline_type,
                        ptable->lfill,
                        usbt,
                        ptable->llcolor,
                        ptable->lfcolor);
                } /* end of for */
            } // end of else

        ptable->bNewPage = FALSE;

        } // end of if
    else
        {

        // ***** Check any bitmaps will fit *****************************

        ptltr.y = ptable->ptltr.y;
        ptlbl.y = ptltr.y - (ONE_MIL * 4);
        usbox_type = ptable->boxtype & ~BOX_BOT;
        lvspace = ptable->ptltr.y - pjob->pdata->pt_bmargin;
        lvspace -= (ONE_MIL * 4);
        bNofit = FALSE;
        for ( i = 0; i < uscol; i++)
            {
            if ( ptable->aCol[ i].bitmap)
                {
                lline = ((ptable->aCol[ i].lpts * ONE_POINT) * pjob->usline_space) / 100;
                usclines = ptable->aCol[ i].uslines;

                ltemp = lline * ( LONG)usclines;
                lvhigh = max( ptable->aCol[ i].bitmap->aptl[ 0].y, ltemp);
                if ( lvhigh > lvspace)
                    bNofit = TRUE;
                } // end of if

            } // end of for

        if( bNofit)
            {
            for ( i = 0; i < uscol; i++)
                {
                usbt = usbox_type;
                if( (( usbox_type & BOX_LEFT) == BOX_LEFT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == 0))
                    usbt = usbox_type & ~BOX_LEFT;

                if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == (uscol - 1)))
                    usbt = usbox_type & ~BOX_RIGHT;

                TST_TRACE(( "PrtEndRow: NOTE - Print box type %u for cell %u", usbox_type, i))
                ptltr.x = ptable->aCol[ i].lrm_box;
                ptlbl.x = ptable->aCol[ i].llm_box;
                PrtBox( pjob,
                        ptlbl,
                        ptltr,
                        ptable->lline_type,
                        ptable->lfill,
                        usbt,
                        ptable->llcolor,
                        ptable->lfcolor);
                } /* end of for */

            PrtNewPage( pjob);
            ptable->ptltr.y = pjob->pdata->pt_prt_top - ONE_MIL;
            ptable->ly_pos = ptable->ptltr.y;
            if( ptable->bAllPages)
                PrtWriteTableHeader( pjob);
            else
                {
                usbox_type = ptable->boxtype & ~BOX_TOP;
                ptltr.y = ptable->ptltr.y;
                ptlbl.y = ptltr.y - (ONE_MIL * 4);
                ptable->ptltr.y = ptlbl.y;

                for ( i = 0; i < uscol; i++)
                    {
                    usbt = usbox_type;
                    if( (( usbox_type & BOX_LEFT) == BOX_LEFT) &&
                        (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                        (i == 0))
                        usbt = usbox_type & ~BOX_LEFT;

                    if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                        (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                        (i == (uscol - 1)))
                        usbt = usbox_type & ~BOX_RIGHT;

                    TST_TRACE(( "PrtEndRow: NOTE - Print box type %u for cell %u", usbox_type, i))
                    ptltr.x = ptable->aCol[ i].lrm_box;
                    ptlbl.x = ptable->aCol[ i].llm_box;
                    PrtBox( pjob,
                            ptlbl,
                            ptltr,
                            ptable->lline_type,
                            ptable->lfill,
                            usbt,
                            ptable->llcolor,
                            ptable->lfcolor);
                    } /* end of for */
                } // end of else

            } // end of if

        } // end of else

    do
        {

        bNofit = FALSE;

        /***** Find available space to bottom of page *******************/

        lvspace = ptable->ptltr.y - pjob->pdata->pt_bmargin;
        lvspace -= (ONE_MIL * 4);
        if ( lvspace <= 0)
            lvspace = 0;

        lvhigh = 0;

        TST_TRACE(( "PrtEndRow: NOTE - %ld twips till bottom of page", lvspace))

        /***** Check if the columns will fit on the page ****************/

        for ( i = 0; i < uscol; i++)
            {

            /***** If there are any lines to print **********************/

            if( ptable->aCol[ i].uslines > ptable->aCol[ i].usstart)
                {

                /***** Get the height of each line **********************/

                lline = ((ptable->aCol[ i].lpts * ONE_POINT) * pjob->usline_space) / 100;
                usclines = (ptable->aCol[ i].uslines - ptable->aCol[ i].usstart) + 1;

                /***** Check the font is not too big for the page *******/

                if ( lline > pjob->pdata->pt_graph_size.cy)
                    return PRTGR_ERR_INV_FONT;

                /***** Get the total height of the text in the cell *****/

                ltemp = lline * ( LONG) (usclines - 1);

                if ( ltemp > lvhigh)
                    {
                    lvhigh = ltemp;
                    ltemp = ( ULONG) (lline / 3);
                    ldrop = max( ldrop, ltemp);
                    } /* end of if */

                TST_TRACE(( "PrtEndRow: NOTE - cell %u is %u lines and %lu twips high", i, usclines,lvhigh))

                /***** If it does not fit *******************************/

                if ( lvhigh > lvspace)
                    {

                    /***** Calc how many lines will fit *****************/

                    uslines = ( USHORT) (lvspace / lline);

                    /***** Set the remaining lines field ****************/

                    ptable->aCol[ i].usnewpage = uslines;

                    bNofit = TRUE;

                    TST_TRACE(( "PrtEndRow: NOTE - Need new page"))
                    lvbot = ptable->ptltr.y - lvspace;
                    ptable->ly_pos = lvbot;

                    } /* end of if */

                else
                    {
                    TST_TRACE(( "PrtEndRow: NOTE - Column %u fits on page", i))
                    ptable->aCol[ i].usnewpage = ptable->aCol[ i].uslines;
                    lvbot = ptable->ptltr.y - lvhigh;
                    ptable->ly_pos = min( ptable->ly_pos, lvbot);
                    }

                }

            }

        /***** Draw any boxes round the cells ***************************/

        if( ptable->boxtype)
            {
            TST_TRACE(( "PrtEndRow: NOTE - Create boxes for cells"))
            ptable->ly_pos -= ldrop;
            ptltr.y = ptable->ptltr.y;
            ptlbl.y = ptable->ly_pos;

            if ( bNofitBefore)
                {
                if ( bNofit)
                    usbox_type = ptable->boxtype & ~BOX_TOPBOT;     /* No top No Bottom */
                else
                    if( ptable->bAllPages && ptable->bHeader && ptable->lhline_type)
                        usbox_type = ptable->boxtype;     /* Normal box */
                    else
                        usbox_type = ptable->boxtype & ~BOX_TOP;     /* No Top */
                }
            else
                {
                if ( bNofit )
                    usbox_type = ptable->boxtype & ~BOX_BOT;     /* No Bottom */
                else
                    usbox_type = ptable->boxtype;     /* Normal box */
                }

            for ( i = 0; i < uscol; i++)
                {
                usbt = usbox_type;
                if( (( usbox_type & BOX_LEFT) == BOX_LEFT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == 0))
                    usbt = usbox_type & ~BOX_LEFT;

                if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                    (( usbox_type & BOX_NOEDGE) == BOX_NOEDGE) &&
                    (i == (uscol - 1)))
                    usbt = usbox_type & ~BOX_RIGHT;

                TST_TRACE(( "PrtEndRow: NOTE - Print box type %u for cell %u", usbox_type, i))
                ptltr.x = ptable->aCol[ i].lrm_box;
                ptlbl.x = ptable->aCol[ i].llm_box;
                PrtBox( pjob,
                        ptlbl,
                        ptltr,
                        ptable->lline_type,
                        ptable->lfill,
                        usbt,
                        ptable->llcolor,
                        ptable->lfcolor);
                } /* end of for */
            }

        /***** Print the text in the cells ******************************/

        GpiSetColor( pjob->pdata->pt_hps, ptable->ltcolor);

        for ( i = 0; i < uscol; i++)
            {

            // ***** Print any bitmaps **********************************

            if( ptable->aCol[ i].bitmap)
                {
                HDC hdc = GpiQueryDevice( ptable->aCol[ i].bitmap->hps);

                high = ptable->aCol[ i].bitmap->aptl[ 0].y + ( 2 * ONE_MIL);
                TST_TRACE(( "EndRow: NOTE - Print bitmap in the cell %lu high", high))
                ptable->aCol[ i].bitmap->aptl[ 0].y = ptable->ptltr.y - high;
                ptable->aCol[ i].bitmap->aptl[ 1].y = ptable->ptltr.y - ( 2 * ONE_MIL);
                GpiSetBitmap( ptable->aCol[ i].bitmap->hps, 0L );
                PrtBitmapOut( pjob,
                              ptable->aCol[ i].bitmap->aptl,
                              ptable->aCol[ i].bitmap->hbm,
                              ptable->aCol[ i].bitmap->cColors,
                              ptable->aCol[ i].bitmap->alColors);
                GpiDeleteBitmap( ptable->aCol[ i].bitmap->hbm);
                GpiResetPS( ptable->aCol[ i].bitmap->hps, GRES_ALL);
                GpiAssociate( ptable->aCol[ i].bitmap->hps, NULLHANDLE);
                GpiDestroyPS( ptable->aCol[ i].bitmap->hps);
                DevCloseDC( hdc);
                FREE( ptable->aCol[ i].bitmap->alColors);
                FREE( ptable->aCol[ i].bitmap);
                }

            /***** If there are any lines to print **********************/

            if( ptable->aCol[ i].uslines > ptable->aCol[ i].usstart)
                {

                lline = ((ptable->aCol[ i].lpts * ONE_POINT) * pjob->usline_space) / 100;

                /***** Set the font for the cell ************************/

                idx = PrtFontAvailable( pjob, ptable->aCol[ i].cFont);
                if ( idx == -1)
                    idx = PrtNewFont( pjob, ptable->aCol[ i].cFont);
                PrtSetFontSize( pjob, idx, ptable->aCol[ i].lpts);
                pjob->pdata->pt_font_idx = idx;
                ptlprt.y = ptable->ptltr.y - lline;
                lcwide = ptable->aCol[ i].lrm_text - ptable->aCol[ i].llm_text;

                /***** Print each line for the cell *********************/

                TST_TRACE(( "PrtEndRow: NOTE - print %u to %u in cell %u",
                                ptable->aCol[ i].usstart, ptable->aCol[ i].usnewpage, i))
                cnt = ptable->aCol[ i].usnewpage - 1;
                for ( j = ptable->aCol[ i].usstart; j < ptable->aCol[ i].usnewpage; j++)
                    {
                    if( ptable->aCol[ i].alines[ j].pszLine)
                        {

                        switch ( ptable->aCol[ i].alines[ j].usJust)
                            {
                            case JUST_RIGHT :
                                lstr = PrtStringLen( pjob, ptable->aCol[ i].alines[ j].pszLine);
                                ptlprt.x = ptable->aCol[ i].lrm_text - lstr;
                                break;

                            case JUST_CENTRE :
                                lstr = PrtStringLen( pjob, ptable->aCol[ i].alines[ j].pszLine);
                                ptlprt.x = ptable->aCol[ i].llm_text + ((lcwide - lstr) / 2);
                                break;

                            default :
                                ptlprt.x = ptable->aCol[ i].llm_text;
                                break;

                            } /* end of switch  */

                        GpiMove( pjob->pdata->pt_hps, &ptlprt);

                        if ( ptable->aCol[ i].alines[ j].usJust == JUST_JUSTIFY)
                            PrtJustified( pjob,
                                          ptable->aCol[ i].alines[ j].pszLine,
                                          lcwide);
                        else
                            GpiCharString( pjob->pdata->pt_hps,
                                           (LONG)strlen( ptable->aCol[ i].alines[ j].pszLine),
                                           ptable->aCol[ i].alines[ j].pszLine);

                        TST_TRACE(( "PrtEndRow: NOTE - print '%s' in cell %u (%lu,%lu)",
                                    ptable->aCol[ i].alines[ j].pszLine,
                                    i, ptlprt.x, ptlprt.y))
                        if ( j < cnt)
                            ptlprt.y -= lline;
                        }

                    else
                        {
                        TST_TRACE(( "PrtEndRow: ERROR - in cell %u element %u is NULL", i, j))
                        j = ptable->aCol[ i].usnewpage;
                        }

                    } /* end of for */

                ptable->aCol[ i].usstart = ptable->aCol[ i].usnewpage;

                } /* if have any lines */

            } /* end of for */


        if ( bNofit)
            {
            TST_TRACE(( "PrtEndRow: NOTE - Print new page"))
            PrtNewPage( pjob);
            ptable->ptltr.y = pjob->pdata->pt_prt_top - ONE_MIL;
            ptable->ly_pos = ptable->ptltr.y;
            if( ptable->bAllPages)
                PrtWriteTableHeader( pjob);
            bNofitBefore = TRUE;
            } /* end of if */
        else
            ptable->ptltr.y = ptable->ly_pos;

        } while ( bNofit);

    /***** Free waiting text ********************************************/

    TST_TRACE(( "PrtEndRow: NOTE - Free up data"))
    for ( i = 0; i < pjob->pdata->pt_table->usCols; i++)
        {
        FREE( ptable->aCol[i].alines);

        ptable->aCol[i].uslines = 0;
        ptable->aCol[i].usstart = 0;
        ptable->aCol[i].usblock = 0;
        ptable->aCol[i].usnewpage = 0;
        } /* end of for */

    TST_TRACE(( "PrtEndRow: NOTE - successful completion"))

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    return PRTGR_OK;

    } // end of PrtEndRow()


// **********************************************************************

PJOB_TYPE PrtObjectInit( )

// **********************************************************************

    {
    PJOB_TYPE       pjob;

    /***** Allocate the job structure ***********************************/

    pjob = ( PJOB_TYPE) malloc( sizeof( JOB_TYPE));
    memset( pjob, 0, sizeof( JOB_TYPE));

    if( bPM)
        {
        char            loaderror[ 128];
        HMODULE         hmod;
        APIRET          rc;

        rc = DosLoadModule( loaderror, sizeof( loaderror), module_name, &hmod);

        if( rc)
            {
            WinAlarm( HWND_DESKTOP, WA_ERROR);
            TST_TRACE(( "PrtObjectInit: failed to load module (%s)", loaderror))
            FREE( pjob);
            return( pjob);
            }

        pjob->hmod = hmod;

        }

    pjob->lColor = CLR_DEFAULT;
    strcpy( pjob->pszForm, "");
    pjob->bPrinting = FALSE;
    pjob->bColor = TRUE;
    pjob->bProgress = TRUE;
    pjob->bWordBreak = TRUE;

    pjob->bMetric = TRUE;
    strcpy( pjob->pszMeasure, MSR_METRIC);

    pjob->tab_len = TAB_LEN_MM;
    pjob->one_unit = ONE_MIL;
    pjob->unit_conv = TWIPS_PER_MIL;

    pjob->def_bmar = DEF_BMAR_MM;
    pjob->def_tmar = DEF_TMAR_MM;
    pjob->def_rmar = DEF_RMAR_MM;
    pjob->def_lmar = DEF_LMAR_MM;

    /***** Allocate the printer structure *******************************/

    pjob->pdata = ( PPRINTER_TYPE) calloc( 1, sizeof( PRINTER_TYPE));

    /***** Set default settings *****************************************/

    pjob->usline_space = LINE_SPACE;
    pjob->pdata->pt_left_margin = pjob->def_lmar;
    pjob->pdata->pt_right_margin = pjob->def_rmar;
    pjob->pdata->pt_top_margin = pjob->def_tmar;
    pjob->pdata->pt_bot_margin = pjob->def_bmar;
    pjob->pdata->pt_border = 0;
    pjob->pdata->pt_fill = 0;
    TST_TRACE(( "PrtObjectInit: set default data"))

    /***** Allocate text buffers ****************************************/

    pjob->buffer1 = ( PSZ) malloc( BUF_SIZE);
    strcpy( pjob->buffer1, "");
    pjob->buffer2 = ( PSZ) malloc( BUF_SIZE);
    strcpy( pjob->buffer2, "");
    TST_TRACE(( "PrtObjectInit: Created buffers"))

    /***** Get the printer list from the system *************************/

    PrtGetPrinterList( );
    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    pjob->prt_idx = pPrtList.def_prt;
    PrtCreateDevStruct( pjob, pPrtList.def_prt);
    strcpy( pjob->szPrinter, pPrtList.szPrinterList[ pPrtList.def_prt]);
    DosReleaseMutexSem( pPrtList.hmtx);

    strcpy( pjob->szPrtDlgRet, "");

    strcpy( pjob->acDlgBut1, "~OK");
    strcpy( pjob->acDlgBut2, "~Job properties...");
    strcpy( pjob->acDlgBut3, "~Cancel");

    PrtQueryQueueInfo( pjob);

    TST_TRACE(( "PrtObjectInit: Set instance data from pjob"))

    return( pjob);

    } // end of PrtObjectInit()


// **********************************************************************

VOID PrtObjectDestroy( PJOB_TYPE pjob)

// **********************************************************************

    {
    USHORT      cnt;

    for ( cnt = 0; cnt < pjob->pdata->pt_hlines; cnt++)
        FREE( pjob->pdata->pt_psz[ cnt].pszLine);
    FREE( pjob->pdata->pt_psz);

    FREE( pjob->tabs);

    /***** free the buffers *********************************************/

    TST_TRACE(( "PrtObjectDestroy: NOTE - Free text buffer 1"))
    FREE( pjob->buffer1);
    TST_TRACE(( "PrtObjectDestroy: NOTE - Free text buffer 2"))
    FREE( pjob->buffer2);

    FREE( pjob->pszPrTitle);
    FREE( pjob->pszPrString1);
    FREE( pjob->pszPrString2);
    FREE( pjob->pszPrString3);

    /***** Free the printer data ****************************************/

    TST_TRACE(( "PrtObjectDestroy: NOTE - Free module"))
    DosFreeModule( pjob->hmod);

    TST_TRACE(( "PrtObjectDestroy: NOTE - Free pdata"))
    FREE( pjob->pdata);

    /***** free job data ************************************************/

    TST_TRACE(( "PrtObjectDestroy: NOTE - Free pjob"))
    FREE( pjob);

    } // end of PrtObjectDestroy()


// **********************************************************************

BOOL PrtWriteTableHeader( PJOB_TYPE pjob)

// **********************************************************************

    {
    USHORT          i;
    SHORT           idx;
    USHORT          usbt,
                    usbox_type;
    POINTL          ptlhere,
                    ptltr,
                    ptlbl;
    LONG            linterline,
                    lspace,
                    ldrop;
    SHORT           fd_idx;
    LONG            pts;

    fd_idx = pjob->pdata->pt_font_idx;
    pts = pjob->pdata->pt_point_size;
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    TST_TRACE(( "PrtWriteTableHeader: is called"))

    linterline = (( pjob->pdata->pt_table->lpts * ONE_POINT) * pjob->usline_space) / 100;
    ldrop = ( LONG) ( linterline / 3);
    lspace = ptlhere.y - (( linterline + ldrop) * 2);

    if ( lspace < pjob->pdata->pt_bmargin)
        {
        PrtNewPage( pjob);
        GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
        }

    ptltr.y = ptlhere.y;
    ptlhere.y -= linterline;
    ptlbl.y = ptlhere.y - ldrop;

    idx = PrtFontAvailable( pjob, pjob->pdata->pt_table->cFont);
    if ( idx == -1)
        {
        idx = PrtNewFont( pjob, pjob->pdata->pt_table->cFont);
        if ( idx == -1)
            return FALSE;
        }

    PrtSetFontSize( pjob, idx, pjob->pdata->pt_table->lpts);

    usbox_type = pjob->pdata->pt_table->hboxtype;

    for ( i = 0; i < pjob->pdata->pt_table->usCols; i++)
        {
        if( usbox_type > 0)
            {
            usbt = usbox_type;

            if(( usbox_type & BOX_NOEDGE) == BOX_NOEDGE)
                {
                if( (( usbox_type & BOX_LEFT) == BOX_LEFT) && (i == 0))
                    usbt = usbox_type & ~BOX_LEFT;

                if( (( usbox_type & BOX_RIGHT) == BOX_RIGHT) &&
                    (i == (pjob->pdata->pt_table->usCols - 1)))
                    usbt = usbox_type & ~BOX_RIGHT;

                }

            ptltr.x = pjob->pdata->pt_table->aCol[ i].lrm_box;
            ptlbl.x = pjob->pdata->pt_table->aCol[ i].llm_box;
            PrtBox( pjob,
                    ptlbl,
                    ptltr,
                    pjob->pdata->pt_table->lhline_type,
                    pjob->pdata->pt_table->lhfill,
                    usbt,
                    pjob->pdata->pt_table->lhlcolor,
                    pjob->pdata->pt_table->lhfcolor);
            } /* end of if */

        ptlhere.x = pjob->pdata->pt_table->aCol[ i].llm_text;
        GpiSetColor( pjob->pdata->pt_hps, pjob->pdata->pt_table->lhtcolor);
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        PrtWriteFormatted( pjob, pjob->pdata->pt_table->aCol[ i].pszHeader, TRUE, i);
        GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

        } /* end of for */

    PrtSetFontSize( pjob, fd_idx, pts);
    ptlhere.x = pjob->pdata->pt_table->aCol[ 0].llm_text;
    ptlhere.y = ptlbl.y;
    pjob->pdata->pt_table->ly_pos = ptlbl.y;
    pjob->pdata->pt_table->ptltr.y = ptlbl.y;
    pjob->pdata->pt_table->ptltr.x = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_table->usCols - 1].lrm_box;

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    return TRUE;

    } // end of PrtWriteTableHeader()


// **********************************************************************

HFILE FileReset( PSZ fName)

// **********************************************************************

    {
    ULONG           faction = 0;
    APIRET          ioerr = 0;
    HFILE           hfile = (HFILE)0;

    /********** Uppercase file name ******************/

    fName = strupr(fName);

    /****************** Open the file **********************************/

    ioerr = DosOpen( fName, &hfile, &faction, 0L,
                     FILE_NORMAL, FILE_OPEN,
                     OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
                     NULL);

    if (ioerr)
        hfile = (HFILE)0;

    return( hfile);

    } // end of FileReset()


// **********************************************************************

APIRET FileRead( HFILE hf,
                 PVOID pData,
                 USHORT usSize)

// **********************************************************************

    {
    ULONG           bytesread;
    APIRET          ioerr;

    ioerr = DosRead( hf, pData, usSize, &bytesread);

    if ( !ioerr)
        if ( usSize != bytesread)
            ioerr = FILE_BLK_SIZE_ERR;
    return( ioerr);

    } // end of FileRead()


// **********************************************************************

APIRET FileReadLn( HFILE hf, PSZ str)

// **********************************************************************

    {
    BOOL            eol;
    APIRET          ioerr;
    int             i;
    char            IOBuffer[ 10];

    /****** Init variables *******/

    *str = '\0';
    i = 0;
    eol = FALSE;

    if (hf == (HFILE)0)
        {
        return( 1);
        }

    /****** Read the string ********/

    do
        {
        ioerr = FileRead( hf, IOBuffer, 1);
        if (ioerr != 0)
            {
            str[i] = '\0';
            eol = TRUE;
            }

        /****** If CR end of string ********/

        else if ( *IOBuffer == '\r')
            {
            eol = TRUE;
            str[i] = '\0';
            }

        /****** Else another character ******/

        else
            {
            str[i] = *IOBuffer;
            i++;
            }
        } while (!eol);

    /****** Read the \n *******/

    ioerr = FileRead( hf, IOBuffer, 1);

    return(ioerr);

    } // end of FileReadLn()


// **********************************************************************

VOID PrtAbort( PJOB_TYPE pjob)

// **********************************************************************

    {

    DevEscape( pjob->pdata->pt_hdc, DEVESC_ABORTDOC, 0, NULL, (PLONG)NULL, (PBYTE)NULL);

    pjob->bPrinting = FALSE;

    PrtClose( pjob);

    } // end of PrtAbort()


BOOL PrtCheckFits( PJOB_TYPE pjob, PSZ szString)

    {
    POINTL          ptlhere,
                    ptl;
    LONG            linterline,
                    drop,
                    llen,
                    lstart,
                    lmargin,
                    ledge,
                    lspace;
    BOOL            bmore;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    lstart = ptlhere.x;

    /***** Get inter-line spacing from font metrics *********************/

    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;
    drop = linterline / 3;

    /***** check for new page *******************************/

    if ( pjob->check_page && ( ptlhere.y < ( pjob->pdata->pt_bmargin + drop)))
        return (FALSE);

    if ( ptlhere.y == pjob->pdata->pt_tmargin)
        {
        ptlhere.y -=linterline;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        } /* end of if */

    if ( pjob->pdata->pt_table)
        {
        ledge = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].lrm_text;
        lmargin = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].llm_text;
        } // end of if
    else
        {
        ledge = pjob->pdata->pt_rmargin - ONE_MIL;
        lmargin = pjob->pdata->pt_lmargin + ONE_MIL;
        } // end of else


    /***** Calculate the max string length in twips *********************/

    lspace = ledge - lstart;

    /***** Get the string length in twips *******************************/

    llen = PrtStringLen( pjob, szString);

    if (( llen > pjob->pdata->pt_wide) && ( strlen( szString) == 1))
        return FALSE;

    /***** If the string is too long, break it **************************/

    if ( lspace <= llen)
        {
        strcpy( pjob->buffer1, szString);
        do
            {
            bmore = FALSE;
            PrtWordBreak( pjob, ptlhere.x, ledge);

            if ( strlen( pjob->buffer2) != 0)
                {
                bmore = TRUE;
                ptlhere.x = lmargin;
                ptlhere.y -= linterline;

                /***** check for new page *******************************/

                if ( pjob->check_page && ( ptlhere.y < ( pjob->pdata->pt_bmargin + drop)))
                    {
                    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
                    return ( FALSE);
                    }

                GpiMove( pjob->pdata->pt_hps, &ptlhere);

                strcpy( pjob->buffer1, pjob->buffer2);

                } /* end of if */

            } while ( bmore);

        } /* end of if */

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    return TRUE;

    } // end of PrtCheckFits()


// **********************************************************************

BOOL PrtLineFits( PJOB_TYPE pjob, PSZ szString)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            llen,
                    lstart,
                    ledge,
                    lspace;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    if ( pjob->pdata->pt_table)
        {
        lstart = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].llm_text;
        ledge = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].lrm_text;
        }
    else
        {
        lstart = ptlhere.x;
        ledge = pjob->pdata->pt_rmargin - ONE_MIL;
        }

    /***** Calculate the max string length in twips *********************/

    lspace = ledge - lstart;

    /***** Get the string length in twips *******************************/

    llen = PrtStringLen( pjob, szString);

    /***** If the string is too long, break it **************************/

    if ( lspace <= llen)
        return( TRUE);
    else
        return( FALSE);

    } // end of PrtLineFits()


// **********************************************************************

BOOL PrtCheckMargins( PJOB_TYPE pjob)

// **********************************************************************

    {

    if (( pjob->pdata->pt_min_lmargin <= pjob->pdata->pt_left_margin) &&
        ( pjob->pdata->pt_min_rmargin <= pjob->pdata->pt_right_margin) &&
        ( pjob->pdata->pt_min_tmargin <= pjob->pdata->pt_top_margin) &&
        ( pjob->pdata->pt_min_bmargin <= pjob->pdata->pt_bot_margin))
        return TRUE;
    else
        return FALSE;

    } // end of PrtCheckMargins()


// **********************************************************************

VOID PrtSetProgressTexts( PJOB_TYPE pjob,
                          PSZ       pszTitle,
                          PSZ       pszT1,
                          PSZ       pszT2,
                          PSZ       pszT3,
                          PSZ       pszButton)

// **********************************************************************

    {
    if ( pszTitle)
        {
        FREE( pjob->pszPrTitle);
        pjob->pszPrTitle = strdup( pszTitle);
        } // end of if

    if ( pszT1)
        {
        pjob->pszPrString1 = strdup( pszT1);
        } // end of if
    else
        {
        FREE( pjob->pszPrString1);
        pjob->pszPrString1 = strdup( pjob->pdata->doc_name);
        } // end of else

    if ( pszT2)
        {
        pjob->pszPrString2 = strdup( pszT2);
        } // end of if
    else if ( !pjob->pszPrString2)
        {
        pjob->pszPrString2 = strdup( "Printing page %u");
        } // end of else

    if ( pszT3)
        {
        pjob->pszPrString3 = strdup( pszT3);
        } // end of if
    else if ( !pjob->pszPrString3)
        {
        pjob->pszPrString3 = strdup( pjob->szPrinter);
        } // end of else

    if ( pszButton)
        {
        FREE( pjob->pszPrButton);
        pjob->pszPrButton = strdup( pszButton);
        } // end of if

    } // end of PrtSetProgressTexts( )


// **********************************************************************

BOOL PrtStartDaemon()

// **********************************************************************

    {
    STARTDATA   startdata;
    ULONG       idsession;
    PID         processid;
    char        pgm_name[] = DAE_PROG_NAME;
    char        buffer[128];
    APIRET      rc;

    if ( DosOpenEventSem( SHR_HEV_NAME, &HevShr))
        {
        DosCreateEventSem( SHR_HEV_NAME, &HevShr, 0L, FALSE);

        printf( "starting PM Daemon\n");
        startdata.Length        = sizeof( STARTDATA);
        startdata.Related       = SSF_RELATED_INDEPENDENT;
        startdata.FgBg          = SSF_FGBG_BACK;
        startdata.TraceOpt      = SSF_TRACEOPT_NONE;
        startdata.PgmName       = pgm_name;
        startdata.PgmInputs     = 0;
        startdata.TermQ         = 0;
        startdata.Environment   = 0;
        startdata.InheritOpt    = SSF_INHERTOPT_SHELL;
        startdata.SessionType   = SSF_TYPE_PM;
        startdata.PgmTitle      = "PrtGraph PM daemon";
        startdata.IconFile      = 0;
        startdata.PgmHandle     = 0;
        startdata.PgmControl    = SSF_CONTROL_INVISIBLE;
        startdata.InitXPos      = 0;
        startdata.InitYPos      = 0;
        startdata.InitXSize     = 0;
        startdata.InitYSize     = 0;
        startdata.Reserved      = 0;
        startdata.ObjectBuffer  = buffer;
        startdata.ObjectBuffLen = 128;

        // ***** Start the session **************************************

        if((rc = DosStartSession( &startdata, &idsession, &processid)) != 0)
            {
            DosCloseEventSem( HevShr);
            printf( "Failed to start %s return %lu\n", pgm_name, rc);
            return FALSE;
            }

        // ***** Wait for the Semaphore to clear ************************

        if((rc = DosWaitEventSem( HevShr, 20000L)) != 0)
            {
            DosCloseEventSem( HevShr);
            printf( "Wait for %s failed return %lu\n", pgm_name, rc);
            return FALSE;
            }

        }

    if( ( rc = DosOpenMutexSem( SHR_HMTX_NAME, &HmtxShr)) != 0)
        {
        DosCloseEventSem( HevShr);
        printf( "Failed to open Mutex semaphore %s returns %lu\n", SHR_HMTX_NAME, rc);
        return FALSE;
        }

    if ( (rc = DosGetNamedSharedMem( &pvShrObject, SHR_MEM_NAME, PAG_READ | PAG_WRITE)) != 0)
        {
        DosCloseEventSem( HevShr);
        DosCloseMutexSem( HmtxShr);
        printf( "Failed to get shared memory %s returns %lu\n", SHR_MEM_NAME, rc);
        return FALSE;
        }

    pShrMem = ( PSHR_MEM_BLOCK)pvShrObject;

    hwndProg = WinQueryFocus( HWND_DESKTOP);

    return TRUE;

    } // end of PrtStartDaemon()


// **********************************************************************

VOID PrtReleaseDaemon( )

// **********************************************************************

    {
    DosCloseEventSem( HevShr);
    DosCloseMutexSem( HmtxShr);
    DosFreeMem( pvShrObject);

    } // end of PrtReleaseDaemon()


// **********************************************************************

VOID PrtSetupShrMem( PJOB_TYPE  pjob)

// **********************************************************************

    {

    pShrMem->prt_idx = pjob->prt_idx;

    pShrMem->hwndProg = hwndProg;

    if( pjob->pszfont)
        strcpy( pShrMem->pszfont, pjob->pszfont);
    else
        strcpy( pShrMem->pszfont, "");

    if( pjob->pszFace)
        strcpy( pShrMem->pszFace, pjob->pszFace);
    else
        strcpy( pShrMem->pszFace, "");

    strcpy( pShrMem->prt_tit, pjob->prt_tit);
    strcpy( pShrMem->szPrtDlgRet, "");
    strcpy( pShrMem->acDlgBut1, pjob->acDlgBut1);
    strcpy( pShrMem->acDlgBut2, pjob->acDlgBut2);
    strcpy( pShrMem->acDlgBut3, pjob->acDlgBut3);

    pShrMem->bProgress = pjob->bProgress;

    if( pjob->pszPrTitle)
        strcpy( pShrMem->pszPrTitle, pjob->pszPrTitle);
    else
        strcpy( pShrMem->pszPrTitle, "");

    if( pjob->pszPrString1)
        strcpy( pShrMem->pszPrString1, pjob->pszPrString1);
    else
        strcpy( pShrMem->pszPrString1, "");

    if( pjob->pszPrString2)
        strcpy( pShrMem->pszPrString2, pjob->pszPrString2);
    else
        strcpy( pShrMem->pszPrString2, "");

    if( pjob->pszPrString3)
        strcpy( pShrMem->pszPrString3, pjob->pszPrString3);
    else
        strcpy( pShrMem->pszPrString3, "");

    strcpy( pShrMem->pszLogAddress, pjob->DevStruct.pszLogAddress);
    strcpy( pShrMem->pszDriverName, pjob->DevStruct.pszDriverName);
    memset( &( pShrMem->drvData), 0, sizeof( DRVD));
    memcpy( &( pShrMem->drvData), pjob->DevStruct.pdriv, pjob->DevStruct.pdriv->cb);

    } // end of PrtSetupShrMem()


// **********************************************************************

VOID PrtLoadProgressDlg( PJOB_TYPE  pjob)

// **********************************************************************

    {
    ULONG       ulPC;

    if( !bPM)
        {
        DosRequestMutexSem( HmtxShr, SEM_INDEFINITE_WAIT);

        PrtSetProgressTexts( pjob, NULL, NULL, NULL, NULL, NULL);
        PrtSetupShrMem( pjob);

        DosResetEventSem( HevShr, &ulPC);

        WinPostMsg( pjob->hwnd, WM_PROGRESS, 0L, 0L);

        DosWaitEventSem( HevShr, SEM_INDEFINITE_WAIT);

        pjob->hwndProgress = pShrMem->hwndProgress;

        DosReleaseMutexSem( HmtxShr);

        }
    else
        {
        PrtSetProgressTexts( pjob, NULL, NULL, NULL, NULL, NULL);
        pjob->hwndProgress = WinLoadDlg( HWND_DESKTOP,
                                         pjob->hwnd,
                                         (PFNWP)PrtProgressDlgProc,
                                         pjob->hmod,
                                         PRT_DLG_PROGRESS,
                                         pjob);
        }

    } // end of PrtLoadProgressDlg()


// **********************************************************************

MRESULT EXPENTRY PrtPrinterDlgProc(  HWND hwnd,
                                     ULONG msg,
                                     MPARAM mp1,
                                     MPARAM mp2)


// **********************************************************************

    {
    ULONG           i;
    SHORT           idx;
    PJOB_TYPE       pjob;
    LONG            wcx,
                    wcy;
    SWP             swp;
    char            prtstr[ 128],
                    *p;

    switch( msg)
        {

        case WM_INITDLG :
            pjob = ( PJOB_TYPE)mp2;
            WinSetWindowPtr(hwnd, 0, pjob);
            WinSetWindowText( WinWindowFromID( hwnd, FID_TITLEBAR), pjob->prt_tit);
            WinSendDlgItemMsg( hwnd, PRT_DLG_PRT_LST,
                               EM_SETTEXTLIMIT,
                               MPFROMSHORT( 128), 0L);
            DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
            for ( i = 0; i < pPrtList.prt_count; i++)
                {
                strcpy( prtstr, pPrtList.szPrinterList[ i]);
                p = strchr( prtstr, 13);
                if( p)
                    *p = ' ';
                p = strchr( prtstr, 11);
                if( p)
                    *p = '^';
                WinSendDlgItemMsg(  hwnd, PRT_DLG_PRT_LST,
                                    LM_INSERTITEM,
                                    MPFROMSHORT( LIT_END),
                                    MPFROMP( prtstr));
                }
            DosReleaseMutexSem( pPrtList.hmtx);
            WinSendDlgItemMsg(  hwnd, PRT_DLG_PRT_LST,
                                LM_SELECTITEM,
                                MPFROMSHORT( pjob->prt_idx),
                                MPFROMLONG( 1));

            WinSetDlgItemText( hwnd, DID_OK, pjob->acDlgBut1);
            WinSetDlgItemText( hwnd, PRT_DLG_PROPS, pjob->acDlgBut2);
            WinSetDlgItemText( hwnd, DID_CANCEL, pjob->acDlgBut3);

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
                pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
                DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);

                idx =  SHORT1FROMMR( WinSendDlgItemMsg( hwnd,
                                                       PRT_DLG_PRT_LST,
                                                       LM_QUERYSELECTION,
                                                       0L, 0L));

                if (idx == LIT_NONE)
                    {
                    pjob->prt_idx = pPrtList.def_prt;
                    PrtCreateDevStruct( pjob, pPrtList.def_prt);
                    strcpy( pjob->szPrtDlgRet, "");
                    }
                else
                    {
                    pjob->prt_idx = idx;
                    PrtCreateDevStruct( pjob, idx);
                    WinSendDlgItemMsg( hwnd,
                                       PRT_DLG_PRT_LST,
                                       LM_QUERYITEMTEXT,
                                       MPFROM2SHORT( idx, 127),
                                       MPFROMP( pjob->szPrinter));
                    strcpy( pjob->szPrtDlgRet, pjob->szPrinter);
                    }
                DosReleaseMutexSem( pPrtList.hmtx);
                WinDismissDlg( hwnd, 0);
                return(0L);

                } /* end of if */

            break;

        case WM_COMMAND :
            switch(SHORT1FROMMP(mp1))
                {
                case DID_OK :
                    pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
                    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
                    idx = SHORT1FROMMR( WinSendDlgItemMsg( hwnd,
                                                          PRT_DLG_PRT_LST,
                                                          LM_QUERYSELECTION,
                                                          0L, 0L));
                    if (idx == LIT_NONE)
                        {
                        pjob->prt_idx = pPrtList.def_prt;
                        PrtCreateDevStruct( pjob, pjob->prt_idx);
                        strcpy( pjob->szPrtDlgRet, "");
                        }
                    else
                        {
                        pjob->prt_idx = idx;
                        PrtCreateDevStruct( pjob, idx);
                        WinSendDlgItemMsg( hwnd,
                                           PRT_DLG_PRT_LST,
                                           LM_QUERYITEMTEXT,
                                           MPFROM2SHORT( idx, 127),
                                           MPFROMP( pjob->szPrinter));
                        strcpy( pjob->szPrtDlgRet, pjob->szPrinter);
                        }
                    DosReleaseMutexSem( pPrtList.hmtx);
                    WinDismissDlg( hwnd, 0);
                    return(0L);

                case DID_CANCEL :
                    pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
                    strcpy( pjob->szPrtDlgRet, "");
                    WinDismissDlg( hwnd, 0);
                    return(0L);

                case PRT_DLG_PROPS :
                    pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);

                    idx = SHORT1FROMMR( WinSendDlgItemMsg( hwnd,
                                                          PRT_DLG_PRT_LST,
                                                          LM_QUERYSELECTION,
                                                          0L, 0L));
                    if (idx != LIT_NONE)
                        {

                        DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);

                        /* display job properties dialog and get updated */
                        /* job properties from driver */

                        DevPostDeviceModes( pjob->hab,
                                            pPrtList.aDevStruct[ idx].pdriv,
                                            pPrtList.aDevStruct[ idx].pszDriverName,
                                            pPrtList.aDevStruct[ idx].pdriv->szDeviceName,
                                            pPrtList.aDevStruct[ idx].pszLogAddress,
                                            DPDM_POSTJOBPROP);


                        DosReleaseMutexSem( pPrtList.hmtx);
                        }

                    return( 0);

                }
            break;

        default :
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        }

    return( WinDefDlgProc( hwnd, msg, mp1,mp2));

    }  // end of PrtPrinterDlgProc()


// **********************************************************************

MRESULT EXPENTRY PrtProgressDlgProc( HWND hwnd,
                                     ULONG msg,
                                     MPARAM mp1,
                                     MPARAM mp2)

// **********************************************************************

    {
    PJOB_TYPE       pjob;
    char            dlgstr[ 256];
    SWP             swp;
    LONG            wcx,
                    wcy;

    switch( msg)
        {

        case WM_INITDLG :
            pjob = ( PJOB_TYPE)mp2;
            WinSetWindowPtr(hwnd, 0, pjob);

            if( pjob->pszPrTitle)
                WinSetWindowText( WinWindowFromID( hwnd, FID_TITLEBAR), pjob->pszPrTitle);

            if( pjob->pszPrString1)
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT1, pjob->pszPrString1);

            if( pjob->pszPrString2)
                {
                sprintf( dlgstr, pjob->pszPrString2, pjob->pdata->pt_page);
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT2, dlgstr);
                }

            if( pjob->pszPrString3)
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT3, pjob->pszPrString3);

            if( pjob->pszPrButton)
                WinSetDlgItemText( hwnd, PRT_PROG_ABORT, pjob->pszPrButton);

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
            pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
            if( pjob->pszPrString2)
                {
                pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
                sprintf( dlgstr, pjob->pszPrString2, pjob->pdata->pt_page);
                WinSetDlgItemText( hwnd, PRT_PROG_TEXT2, dlgstr);
                }
            break;

        case WM_STOPME :
            WinDismissDlg( hwnd, 0);
            return(0L);

        case WM_COMMAND :
            if ( SHORT1FROMMP(mp1) == PRT_PROG_ABORT)
                {
                pjob = ( PJOB_TYPE)WinQueryWindowPtr( hwnd, 0);
                PrtAbort( pjob);
                WinDismissDlg( hwnd, 0);
                return(0L);
                }
            else
                return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        default :
            return( WinDefDlgProc( hwnd, msg, mp1,mp2));

        } // end of switch

    return( WinDefDlgProc( hwnd, msg, mp1,mp2));

    } // end of PrtprogressDlgProc()


// **********************************************************************

VOID PrtCreateDevStruct( PJOB_TYPE pjob, USHORT idx)

// **********************************************************************

    {
    PrtDeleteDevStruct( pjob);

    pjob->DevStruct.pszLogAddress = strdup( pPrtList.aDevStruct[ idx].pszLogAddress);

    pjob->DevStruct.pszDriverName = strdup( pPrtList.aDevStruct[ idx].pszDriverName);

    pjob->DevStruct.pszDataType = strdup( "PM_Q_STD");

    pjob->DevStruct.pdriv = ( PDRIVDATA) malloc((size_t) pPrtList.aDevStruct[ idx].pdriv->cb);
    memcpy( pjob->DevStruct.pdriv, pPrtList.aDevStruct[ idx].pdriv, pPrtList.aDevStruct[ idx].pdriv->cb);

    } // end of PrtCreateDevStruct()


// **********************************************************************

VOID PrtDeleteDevStruct( PJOB_TYPE pjob)

// **********************************************************************

    {
    FREE( pjob->DevStruct.pszLogAddress);
    FREE( pjob->DevStruct.pszDriverName);
    FREE( pjob->DevStruct.pdriv);
    FREE( pjob->DevStruct.pszDataType);
    FREE( pjob->DevStruct.pszQueueProcParams);

    } // end of

/*
 *  Set_LineSpace
 */

BOOL Set_LineSpace(PJOB_TYPE  pjob, USHORT val)

    {
    if ( val)
        pjob->usline_space = ( USHORT)val;
    else
        pjob->usline_space = LINE_SPACE;
    return TRUE;
    }

/*
 *  Set_Measures
 */

BOOL Set_Measures(PJOB_TYPE  pjob, const char *str)

    {
    UCHAR           cM;
    USHORT          i;
    BOOL            ok = FALSE;

    if ( str)
        {
        cM = ( UCHAR) toupper( *str);
        if ( cM == 'M')
            {
            pjob->bMetric = TRUE;
            strcpy( pjob->pszMeasure, MSR_METRIC);
            pjob->one_unit = ONE_MIL;
            pjob->unit_conv = TWIPS_PER_MIL;
            pjob->tab_len = TAB_LEN_MM;
            pjob->def_bmar = DEF_BMAR_MM;
            pjob->def_tmar = DEF_TMAR_MM;
            pjob->def_rmar = DEF_RMAR_MM;
            pjob->def_lmar = DEF_LMAR_MM;
            } /* end of if */
        else
            {
            pjob->bMetric = FALSE;
            strcpy( pjob->pszMeasure, MSR_INCH);
            pjob->one_unit = ONE_TENTH;
            pjob->unit_conv = TWIPS_PER_TEN;
            pjob->tab_len = TAB_LEN_IN;
            pjob->def_bmar = DEF_BMAR_IN;
            pjob->def_tmar = DEF_TMAR_IN;
            pjob->def_rmar = DEF_RMAR_IN;
            pjob->def_lmar = DEF_LMAR_IN;
            } /* end of else */

        if ( pjob->bPrinting)
            {
            FREE( pjob->tabs);

            /***** Allocate tabs ************************************************/

            pjob->numtabs = (pjob->pdata->pt_wide / pjob->tab_len) - 1;
            pjob->tabs = ( LONG*) calloc( pjob->numtabs, sizeof( LONG));
            memset( pjob->tabs, 0, pjob->numtabs * sizeof( LONG));

            /***** set tabs *****************************************************/

            pjob->tabs[ 0] = pjob->pdata->pt_lmargin + pjob->tab_len;

            for ( i = 1; i < pjob->numtabs; i++)
                pjob->tabs[ i] = pjob->tabs[ i-1] + pjob->tab_len;

            } /* end of if */

        ok = TRUE;
        } /* end of if */

    return ok;
    }

/*
 *  Set_PrintColor
 */

BOOL Set_RxPrintColor(PJOB_TYPE  pjob, PSZ str)

{
    LONG            lclr;
    BOOL            ok = FALSE;

    if ( str)
        {
        lclr = ColorToIndex( str);
        pjob->lColor = lclr;

        if( pjob->bPrinting)
            {
            if ( pjob->bColor)
                GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);
            else
                GpiSetColor( pjob->pdata->pt_hps, CLR_DEFAULT);
            }

        ok = TRUE;
        } /* end of if */

    return ok;
}

/*
 *  Set_PrintColor
 */

BOOL Set_PrintColor(PJOB_TYPE  pjob, LONG       lclr)

{
    pjob->lColor = lclr;

    if( pjob->bPrinting)
        {
        if ( pjob->bColor)
            GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);
        else
            GpiSetColor( pjob->pdata->pt_hps, CLR_DEFAULT);
        }

    return TRUE;
}


// **********************************************************************

VOID PrtSetPrinter( PJOB_TYPE   pjob,
                    int         idx)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {

    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    if (idx == 0)
        {
        pjob->prt_idx = pPrtList.def_prt;
        PrtCreateDevStruct( pjob, pPrtList.def_prt);
        strcpy( pjob->szPrinter, pPrtList.szPrinterList[ pPrtList.def_prt]);
        }
    else
        {
        pjob->prt_idx = idx - 1;
        PrtCreateDevStruct( pjob, idx - 1);
        strcpy( pjob->szPrinter, pPrtList.szPrinterList[ idx - 1]);
        }

    DosReleaseMutexSem( pPrtList.hmtx);

    } // end of PrtSetPrinter()



// **********************************************************************

BOOL PrtSetFont( PJOB_TYPE  pjob,
                 PSZ        szFont)

// **********************************************************************

    {
    SHORT       idx;

    if( !szFont)
        return TRUE;

    idx = PrtFontAvailable( pjob, szFont);

    if ( idx == -1)
        {
        idx = PrtNewFont( pjob, szFont);
        TST_TRACE(( "PrtGJustfied - PrtNewFont returned %d", idx))
        if ( idx == -1)
            return FALSE;
        } /* end of if */

    pjob->pdata->pt_font_idx = idx;

    return TRUE;

    } // end of PrtSetFont()


// **********************************************************************

BOOL PrtDrawWindow( PJOB_TYPE   pjob,
                    HWND        hwnd,
                    POINTL      bl,
                    POINTL      tr,
                    ULONG       th,
                    LONG        llc,
                    PSZ         title)

// **********************************************************************
//
// Description : Draw contents of a window
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    HBITMAP             hbm = (HBITMAP)0;
    HDC                 hdc;
    SWP                 swp;
    PSZ                 pszData[4] = { "Display", NULL, NULL, NULL };
    HPS                 hps,
                        hpsMem;
    SIZEL               sizlPage = {0, 0};
    PBITMAPINFOHEADER   pbmp;
    BITMAPINFOHEADER2   bmp;
    POINTL              aptl[ 4],
                        ptlhere;
    LONG                alData[2];
    LONG                lWidth,
                        lHeight;

    hps = WinGetPS( hwnd);
    WinQueryWindowPos( hwnd, &swp);

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    hdc = DevOpenDC( pjob->hab, OD_MEMORY, "*", 4L,
                     (PDEVOPENDATA)pszData,
                     NULLHANDLE);
    hpsMem = GpiCreatePS( pjob->hab,
                          hdc, &sizlPage,
                          GPIA_ASSOC | PU_PELS | GPIT_MICRO);

    GpiAssociate( hpsMem, hdc);

    GpiQueryDeviceBitmapFormats( hps, 2, alData);

    TST_TRACE(( "PrtDrawWindow: NOTE - Got %lu planes and %lu bits %lu wide %lu High",
                    alData[ 0], alData[ 1], swp.cx, swp.cy))

    /***** Shove the bitmap at the printer ******************************/

    aptl[ 0].x = 0;
    aptl[ 0].y = 0;
    aptl[ 1].x = swp.cx;
    aptl[ 1].y = swp.cy;

    aptl[ 2].x = 0;
    aptl[ 2].y = 0;
    aptl[ 3].x = swp.cx;
    aptl[ 3].y = swp.cy;

    lWidth = aptl[ 1].x - aptl[ 0].x;
    lHeight = aptl[ 1].y - aptl[ 0].y;

    memset( &bmp, 0, sizeof( BITMAPINFOHEADER));
    bmp.cbFix = (ULONG) sizeof( BITMAPINFOHEADER);
    bmp.cx = lWidth;
    bmp.cy = lHeight;
    bmp.cPlanes = alData[0];
    bmp.cBitCount = alData[1];

    hbm = GpiCreateBitmap( hpsMem, &bmp, 0L, NULL, NULL);
    if ( !hbm)
        {
        TST_TRACE(( "PrtDrawWindow: ERROR - failed to create bitmap"))
        WinReleasePS( hps);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        return TRUE;
        } /* end of if */

    GpiSetBitmap( hpsMem, hbm);

    if( GpiBitBlt( hpsMem, hps, 4L, aptl, ROP_SRCCOPY, BBO_IGNORE) == GPI_ERROR)
        {
        TRACEWINERRORN( "PrtDrawWindow: ERROR -GpiBitBlit to memory failed severity %X error %X")
        WinReleasePS( hps);
        GpiDeleteBitmap( hbm);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        return TRUE;
        } /* end of if */

    pbmp = ( PBITMAPINFOHEADER) calloc( 1, sizeof( BITMAPINFOHEADER));
    pbmp->cbFix = (ULONG) sizeof( BITMAPINFOHEADER);
    pbmp->cx = ( USHORT)bmp.cx;
    pbmp->cy = ( USHORT)bmp.cy;
    pbmp->cBitCount = bmp.cBitCount;
    pbmp->cPlanes = bmp.cPlanes;

    aptl[ 0].x = bl.x;
    aptl[ 0].y = bl.y;
    if( tr.x == 0)
        tr.x = bl.x + ( LONG)((double)bmp.cx * pjob->pdata->xpels * pjob->pdata->aspect);
    aptl[ 1].x = tr.x;
    if( tr.y == 0)
        tr.y = bl.y + ( LONG)((double)bmp.cy * pjob->pdata->ypels * pjob->pdata->aspect);
    aptl[ 1].y = tr.y;

    aptl[ 3].x = bmp.cx;
    aptl[ 3].y = bmp.cy;

    if( pjob->pdata->pt_table)
        {
        PrtSetCellBitmap( pjob, hbm, aptl, hpsMem, 0, NULL, &bmp, title);
        WinReleasePS( hps);
        return TRUE;
        }

    TST_TRACE(( "PrtDrawWindow: Source (%lu,%lu) to (%lu,%lu)", aptl[ 2].x, aptl[ 2].y, aptl[ 3].x, aptl[ 3].y))
    TST_TRACE(( "PrtDrawWindow: Target (%lu,%lu) to (%lu,%lu)", aptl[ 0].x, aptl[ 0].y, aptl[ 1].x, aptl[ 1].y))

    GpiSetBitmap( hpsMem, 0L);
    if ( !PrtBitmapOut( pjob, aptl, hbm, 0, NULL))
        {
        TST_TRACE(( "PrtDrawWindow: ERROR - GpiDrawBits to printer failed severity %X error %X", usSev, usCode))
        WinReleasePS( hps);
        GpiDeleteBitmap( hbm);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        FREE( pbmp);
        return TRUE;
        } /* end of if */

    if ( th > 0)
        PrtBox( pjob, bl, tr, th, 0, BOX_ALL, llc, pjob->lColor);

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);

    if( title)
        PrtWriteTitle( pjob, title, bl.x, tr.x);

    FREE( pbmp);
    WinReleasePS( hps);
    GpiDeleteBitmap( hbm);
    GpiAssociate( hpsMem, NULLHANDLE);
    GpiDestroyPS( hpsMem);
    DevCloseDC( hdc);
    return TRUE;

    } // end of PrtDrawWindow()


// **********************************************************************

VOID PrtMoveX( PJOB_TYPE   pjob,
               LONG        delta,
               BOOL        points)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    POINTL      ptl;

    if ( points)
        {
        delta *= ONE_POINT;
        TST_TRACE(( "PrtMoveY: %d points", delta))
        } // end of if
    else
        {
        delta *= pjob->one_unit;
        TST_TRACE(( "PrtMoveY: %d units", delta))
        } // end of else

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    ptl.x += delta;

    TST_TRACE(( "PrtMoveY: %d, %d TWIPS", ptl.x, ptl.y))

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);

    } // end of PrtMoveX()


// **********************************************************************

VOID PrtMoveY( PJOB_TYPE   pjob,
               LONG        delta,
               BOOL        points)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    POINTL      ptl;

    if ( points)
        {
        delta *= ONE_POINT;
        TST_TRACE(( "PrtMoveY: %d points", delta))
        } // end of if
    else
        {
        delta *= pjob->one_unit;
        TST_TRACE(( "PrtMoveY: %d units", delta))
        } // end of else

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    ptl.y += delta;

    TST_TRACE(( "PrtMoveY: %d, %d TWIPS", ptl.x, ptl.y))

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);

    } // end of PrtMoveY()


// **********************************************************************

VOID PrtGoto( PJOB_TYPE   pjob,
              LONG        x,
              LONG        y,
              BOOL        points)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    POINTL      ptl;

    if ( points)
        {
        x *= ONE_POINT;
        y *= ONE_POINT;
        TST_TRACE(( "PrtGoto: %d, %d points", x, y))
        } // end of if
    else
        {
        x *= pjob->one_unit;
        y *= pjob->one_unit;
        TST_TRACE(( "PrtGoto: %d, %d units", x, y))
        } // end of else

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    ptl.x = x + pjob->pdata->pt_lmargin;
    ptl.y = y + pjob->pdata->pt_bmargin;

    TST_TRACE(( "PrtGoto: %d, %d TWIPS", ptl.x, ptl.y))

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);

    } // end of PrtGoto()


// **********************************************************************

VOID PrtGotoX( PJOB_TYPE   pjob,
               LONG        x,
               BOOL        points)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    POINTL      ptl,
                here;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &here);

    if ( points)
        {
        x *= ONE_POINT;
        } // end of if
    else
        {
        x *= pjob->one_unit;
        TST_TRACE(( "PrtGoto: %d, %d units", x, y))
        } // end of else


    ptl.x = x + pjob->pdata->pt_lmargin;
    ptl.y = here.y;

    TST_TRACE(( "PrtGoto: %d, %d TWIPS", ptl.x, ptl.y))

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);

    } // end of PrtGotoX()


// **********************************************************************

VOID PrtGotoY( PJOB_TYPE   pjob,
               LONG        y,
               BOOL        points)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    POINTL      ptl,
                here;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &here);

    if ( points)
        {
        y *= ONE_POINT;
        } // end of if
    else
        {
        y *= pjob->one_unit;
        } // end of else

    ptl.x = here.x;
    ptl.y = y + pjob->pdata->pt_bmargin;

    TST_TRACE(( "PrtGoto: %d, %d TWIPS", ptl.x, ptl.y))

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptl);
    GpiMove( pjob->pdata->pt_hps, &ptl);

    } // end of PrtGotoY()


// **********************************************************************

BOOL PrtDrawBitMap2( PJOB_TYPE  pjob,
                     HMODULE    hmod,
                     ULONG      res,
                     POINTL     bl,
                     POINTL     tr,
                     LONG       th,
                     LONG       lcolor,
                     PSZ        title)

// **********************************************************************

    {
    HBITMAP             hbm = (HBITMAP)0;
    HDC                 hdc;
    HPS                 hpsMem;
    SIZEL               sizlPage = {0L, 0L};
    POINTL              aptl[ 4],
                        ptlhere;
    PBITMAPINFOHEADER   pbmp;

    if( pjob->pdata->pt_table && pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].bitmap)
        return FALSE;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    hdc = DevOpenDC( pjob->hab, OD_MEMORY, "*",
                     4L, ( PDEVOPENDATA)&(pjob->DevStruct), (HDC) 0);

    if ( hdc == DEV_ERROR)
        {
        TRACEWINERRORN( "PrtDrawBitMap2: ERROR - DevOpenDC  failed severity %X error %X")
        return( FALSE);
        }

    /***** Set the presentation space ***********************************/

    hpsMem = GpiCreatePS( pjob->hab,
                          hdc, &sizlPage,
                          PU_TWIPS | GPIA_ASSOC | GPIF_LONG );

    if ( hpsMem == GPI_ERROR)
        {
        TRACEWINERRORN( "PrtDrawBitMap2: ERROR - GpiCreatePS  failed severity %X error %X")
        DevCloseDC( hdc);
        return FALSE;
        }

    hbm = GpiLoadBitmap( hpsMem, hmod, res, 0L, 0L);

    if ( hbm == GPI_ERROR)
        {
        TRACEWINERROR( "PrtDrawBitMap2: ERROR - GpiLoadBitmap %lu from EXE failed severity %X error %X",
                        res)
        GpiResetPS( hpsMem, GRES_ALL);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        return FALSE;
        } // end of if


    pbmp = ( PBITMAPINFOHEADER) calloc( 1, sizeof( BITMAPINFOHEADER));
    pbmp->cbFix = (ULONG) sizeof( BITMAPINFOHEADER);

    if( !GpiQueryBitmapParameters( hbm, pbmp))
        {
        TRACEWINERRORN( "PrtDrawBitMap2: ERROR - GpiQueryBitmapParameters failed severity %X error %X")
        GpiDeleteBitmap( hbm);
        GpiResetPS( hpsMem, GRES_ALL);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        FREE( pbmp);
        return FALSE;
        } // end of if

    TST_TRACE(( "PrtDrawBitMap2: NOTE - Got BITMAPINFOHEADER cx = %lu, cy = %lu", pbmp->cx, pbmp->cy))
    TST_TRACE(( "PrtDrawBitMap2: NOTE - Got BITMAPINFOHEADER Bits = %lu, Planes = %lu size %lu",
                    pbmp->cBitCount, pbmp->cPlanes, pbmp->cbFix))

    if ( GpiSetBitmap( hpsMem, hbm) == HBM_ERROR)
        {
        TRACEWINERRORN( "PrtDrawBitMap2: ERROR - GpiSetBitmap failed severity %X error %X")
        GpiDeleteBitmap( hbm);
        GpiResetPS( hpsMem, GRES_ALL);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        FREE( pbmp);
        return FALSE;
        } // end of if


    aptl[ 2].x = 0;
    aptl[ 2].y = 0;
    aptl[ 3].x = pbmp->cx;
    aptl[ 3].y = pbmp->cy;

    aptl[ 0].x = bl.x;
    aptl[ 0].y = bl.y;
    if( tr.x == 0)
        tr.x = bl.x + ( LONG)((double)pbmp->cx * pjob->pdata->xpels * pjob->pdata->aspect);
    aptl[ 1].x = tr.x;
    if( tr.y == 0)
        tr.y = bl.y + ( LONG)((double)pbmp->cy * pjob->pdata->ypels * pjob->pdata->aspect);
    aptl[ 1].y = tr.y;

    TST_TRACE(( "PrtDrawBitMap2: NOTE - draw bitmap %lu (%lu, %lu) (%lu, %lu)",
                    res, aptl[ 0].x, aptl[ 0].y,  aptl[ 1].x, aptl[ 1].y))

    if( pjob->pdata->pt_table)
        {
        PrtSetCellBitmap( pjob, hbm, aptl, hpsMem, 0, NULL, (PBITMAPINFOHEADER2)pbmp, title);
        return TRUE;
        }

    GpiSetBitmap( hpsMem, 0L);
    if( !PrtBitmapOut( pjob, aptl, hbm, 0, NULL))
        {
        GpiDeleteBitmap( hbm);
        GpiResetPS( hpsMem, GRES_ALL);
        GpiAssociate( hpsMem, NULLHANDLE);
        GpiDestroyPS( hpsMem);
        DevCloseDC( hdc);
        FREE( pbmp);
        return FALSE;
        }

    TST_TRACE(( "PrtDrawBitMap2: NOTE - draw box (%lu, %lu) (%lu, %lu)",
                    bl.x, bl.y,  tr.x, tr.y))

    //***** Set the current position back to where we were ***************

    if ( th > 0)
        PrtBox( pjob, bl, tr, th, 0, BOX_ALL, lcolor, pjob->lColor);

    GpiDeleteBitmap( hbm);
    GpiResetPS( hpsMem, GRES_ALL);
    GpiAssociate( hpsMem, NULLHANDLE);
    GpiDestroyPS( hpsMem);
    DevCloseDC( hdc);
    FREE( pbmp);

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);

    if( title)
        PrtWriteTitle( pjob, title, bl.x, tr.x);

    return TRUE;

    } // end of PrtDrawBitMap2()


// **********************************************************************

VOID PrtSetCellBitmap( PJOB_TYPE            pjob,
                       HBITMAP              hbm,
                       PPOINTL              aptl,
                       HPS                  hps,
                       ULONG                cColors,
                       PLONG                alColors,
                       PBITMAPINFOHEADER2   pbmp,
                       PSZ                  title)

// **********************************************************************

    {
    LONG        wide;
    double      aspect,
                line_high,
                high;
    USHORT      lines,
                cnt,
                col = pjob->pdata->pt_col;
    PCOL_TYPE   aCol = pjob->pdata->pt_table->aCol;

    aCol[ col].bitmap = ( PBMAP)calloc( 1, sizeof( BMAP));
    aCol[ col].bitmap->hbm = hbm;
    aCol[ col].bitmap->hps = hps;
    aCol[ col].bitmap->cColors = cColors;
    aCol[ col].bitmap->alColors = alColors;

    wide = aCol[ col].lrm_text - aCol[ col].llm_text;

    aspect = (double)wide / ( double)pbmp->cx;

    aCol[ col].bitmap->aptl[ 0].x = aCol[ col].llm_text;
    aCol[ col].bitmap->aptl[ 1].x = aCol[ col].lrm_text;
    aCol[ col].bitmap->aptl[ 1].y = 0;
    aCol[ col].bitmap->aptl[ 2].x = 0;
    aCol[ col].bitmap->aptl[ 2].y = 0;
    aCol[ col].bitmap->aptl[ 3].x = aptl[ 3].x;
    aCol[ col].bitmap->aptl[ 3].y = aptl[ 3].y;

    high = (double)pbmp->cy * aspect;

    TST_TRACE(( "PrtSetCellBitmap: set bitmap %lu wide Aspect %g and %lu high", wide, aspect, high))
    if( aCol[ col].lpts <= 0L)
        aCol[ col].lpts = pjob->pdata->pt_table->lpts;

    if( !strlen( aCol[ col].cFont))
        strcpy( aCol[ col].cFont, pjob->pdata->pt_table->cFont);

    line_high = ((double)(ONE_POINT * aCol[ col].lpts) * ( double)pjob->usline_space) / 100.0;

    lines = ( USHORT)((high  + ( 2 * TWIPS_PER_MIL)) / line_high);

    TST_TRACE(( "PrtSetCellBitmap: bitmap equivalent of %u lines high in %s %lu",
               lines, aCol[ col].cFont, aCol[ col].lpts))

    aCol[ col].bitmap->aptl[ 0].y = ( LONG)( ((double)lines * line_high) - ( 2 * TWIPS_PER_MIL));

    for ( cnt = 0; cnt < lines; cnt++)
        PrtWriteCol( pjob, aCol[ col].cFont, aCol[ col].lpts, "", JUST_LEFT);

    if( title)
        PrtWriteCol( pjob, aCol[ col].cFont, aCol[ col].lpts, title, JUST_CENTRE);

    } // end of PrtSetCellBitmap()


// **********************************************************************

VOID PrtWriteTitle( PJOB_TYPE pjob,
                    PSZ       title,
                    LONG      ledge,
                    LONG      redge)

// **********************************************************************

    {
    POINTL          ptlhere;
    LONG            llen,
                    lspace,
                    linterline;
    BOOL            bmore;

    llen = PrtStringLen( pjob, title);
    lspace = redge - ledge;
    linterline = (( pjob->pdata->pt_point_size * ONE_POINT) * pjob->usline_space) / 100;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    ptlhere.y -= linterline;

    TST_TRACE(( "PrtWriteTitle - NOTE - input string is %lu twips long space %lu twips", llen, lspace))

    /***** If the string is too long, break it **************************/

    if ( lspace <= llen)
        {
        strcpy( pjob->buffer1, title);
        do
            {
            bmore = FALSE;
            PrtWordBreak( pjob, ledge, redge);

            TST_TRACE(( "PrtWriteTitle - NOTE - input string is split '%s'", pjob->buffer1))
            TST_TRACE(( "PrtWriteTitle - NOTE - input string is split '%s'", pjob->buffer2))

            llen = PrtStringLen( pjob, pjob->buffer1);
            ptlhere.x = ((lspace - llen) / 2) + ledge;
            GpiMove( pjob->pdata->pt_hps, &ptlhere);
            GpiCharString( pjob->pdata->pt_hps, strlen( pjob->buffer1), pjob->buffer1);

            if ( strlen( pjob->buffer2) != 0)
                {
                bmore = TRUE;
                ptlhere.x = ledge;
                ptlhere.y -= linterline;

                GpiMove( pjob->pdata->pt_hps, &ptlhere);

                strcpy( pjob->buffer1, pjob->buffer2);

                } /* end of if */

            } while ( bmore);

        } /* end of if */

    /***** else just write the string ***********************************/

    else
        {
        ptlhere.x = ((lspace - llen) / 2) + ledge;
        GpiMove( pjob->pdata->pt_hps, &ptlhere);
        GpiCharString( pjob->pdata->pt_hps, strlen( title), title);
        }

    } // end of PrtWriteTitle()


// **********************************************************************

PTABLE_TYPE PrtFreeTable( PTABLE_TYPE  ptable)

// **********************************************************************

    {
    USHORT          i;

    if( ptable)
        {

        // ***** Destroy each column ************************************

        for ( i = 0; i < ptable->usCols; i++)
            {

            // ***** Destroy any header data ****************************

            if ( ptable->bHeader)
                {
                TST_TRACE(( "PrtFreeTable: Destroy any header data"))
                FREE( ptable->aCol[ i].pszHeader);
                }

            // ***** Destroy any text ***********************************

            if ( ptable->aCol[ i].alines)
                {
                TST_TRACE(( "PrtFreeTable: Destroy %u lines", ptable->aCol[ i].usblock))
                TST_TRACE(( "PrtFreeTable: Destroy lines block"))
                FREE( ptable->aCol[i].alines);
                }

            // ***** Destroy any bitmaps ********************************

            if ( ptable->aCol[ i].bitmap)
                {
                TST_TRACE(( "PrtFreeTable: Destroy the bitmap"))
                GpiDeleteBitmap( ptable->aCol[ i].bitmap->hbm);
                GpiResetPS( ptable->aCol[ i].bitmap->hps, GRES_ALL);
                GpiAssociate( ptable->aCol[ i].bitmap->hps, NULLHANDLE);
                GpiDestroyPS( ptable->aCol[ i].bitmap->hps);
                DevCloseDC( ptable->aCol[ i].bitmap->hdc);
                FREE( ptable->aCol[ i].bitmap->alColors);
                FREE( ptable->aCol[ i].bitmap);
                } // end of if

            } // end of for

        // ***** Free colums and table **********************************

        TST_TRACE(( "PrtFreeTable: Destroy column array"))
        FREE( ptable->aCol);
        TST_TRACE(( "PrtFreeTable: Destroy the table struct"))
        FREE( ptable);

        } /* end of if */

    return( NULL);

    } // end of PrtFreeTable()


// **********************************************************************

PTABLE_TYPE PrtCreateTable( int     cols)

// **********************************************************************

    {
    PTABLE_TYPE     ptable;

    ptable = (PTABLE_TYPE) calloc(1, sizeof( TABLE_TYPE));
    ptable->bFirstRow = TRUE;

    ptable->usCols = (USHORT)cols;
    ptable->aCol = ( PCOL_TYPE) calloc( cols, sizeof( COL_TYPE));

    return( ptable);

    } // end of PrtCreateTable()


// **********************************************************************

VOID PrtFreeCells( PTABLE_TYPE ptable)

// **********************************************************************

    {
    USHORT      i;

    for( i=0; i < ptable->usCols; i++)
        {
        if ( ptable->aCol[ i].alines != NULL)
            {
            FREE( ptable->aCol[ i].alines);
            ptable->aCol[ i].alines = NULL;
            }
        ptable->aCol[ i].uslines = 0;
        ptable->aCol[ i].usstart = 0;
        ptable->aCol[ i].usnewpage = 0;
        ptable->aCol[ i].usblock = 0;
        ptable->aCol[ i].lpts = 0;
        strcpy( ptable->aCol[ i].cFont, "");
        } /* end of for */

    } // end of PrtFreeCells()


// **********************************************************************

VOID PrtInitHeader( PJOB_TYPE   pjob,
                    USHORT      lines)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    USHORT      cnt;

    if ( pjob->pdata->pt_psz)
        {
        for ( cnt = 0; cnt < pjob->pdata->pt_hlines; cnt++)
            FREE( pjob->pdata->pt_psz[ cnt].pszLine);

        FREE( pjob->pdata->pt_psz);
        }
    pjob->pdata->pt_hlines = lines;
    pjob->pdata->pt_psz = ( PH_LINE) calloc( lines, sizeof( H_LINE));

    } // end of PrtInitHeader()


// **********************************************************************

VOID PrtMakeTabs( PJOB_TYPE   pjob)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {
    USHORT      i;

    FREE( pjob->tabs);

    /***** Allocate tabs ************************************************/

    pjob->numtabs = (pjob->pdata->pt_wide / pjob->tab_len) - 1;

    pjob->tabs = ( PLONG) calloc( pjob->numtabs, sizeof( LONG));

    /***** set tabs *****************************************************/

    pjob->tabs[ 0] = pjob->pdata->pt_lmargin + pjob->tab_len;

    for ( i = 1; i < pjob->numtabs; i++)
        pjob->tabs[ i] = pjob->tabs[ i-1] + pjob->tab_len;


    } // end of PrtMakeTabs()


// **********************************************************************

VOID PrtResetColHdr( PJOB_TYPE   pjob,
                     USHORT      col,
                     PSZ         string)

// **********************************************************************

    {

    FREE( pjob->pdata->pt_table->aCol[ col].pszHeader);

    pjob->pdata->pt_table->aCol[ col].pszHeader = strdup( string);

    } // end of PrtResetColHdr()


// **********************************************************************

VOID PrtResetHeader( PJOB_TYPE  pjob,
                     LONG       argc,
                     PSZ        argv[])

// **********************************************************************

    {
    USHORT          usLines,
                    i, j;
    LONG            cnt,
                    parms;

    if( argv[ 0])
        usLines = ( USHORT)atoi( argv[ 0]);
    else
        usLines = pjob->pdata->pt_hlines;

    if ( usLines > pjob->pdata->pt_hlines)
        {
        pjob->pdata->pt_psz = ( PH_LINE) realloc( pjob->pdata->pt_psz, usLines * sizeof( H_LINE));
        j = usLines - 1;
        for ( i = j; i < pjob->pdata->pt_hlines; i++)
            {
            pjob->pdata->pt_psz[ i].pszLine = NULL;
            pjob->pdata->pt_psz[ i].lpts = pjob->pdata->pt_hpts;
            strcpy( pjob->pdata->pt_psz[ i].cfont, pjob->pdata->pt_hfont);
            }
        } /* end of if */

    if ( usLines < pjob->pdata->pt_hlines)
        {
        j = usLines;
        for ( i = j; i < pjob->pdata->pt_hlines; i++)
            FREE( pjob->pdata->pt_psz[ i].pszLine);
        } /* end of if */

    pjob->pdata->pt_hlines = usLines;

    parms = min( argc, (LONG) usLines);

    for ( cnt = 1; cnt < parms; cnt++)
        {
        if ( argv[ cnt])
            {
            FREE( pjob->pdata->pt_psz[ cnt - 1].pszLine);
            pjob->pdata->pt_psz[ cnt - 1].pszLine = strdup( argv[ cnt]);
            } /* end of if */

        } /* end of for */

    } // end of PrtResetHeader()



// **********************************************************************

BOOL PrtBitmapOut( PJOB_TYPE    pjob,
                   PPOINTL      aptl,
                   HBITMAP      hbm,
                   ULONG        cColors,
                   PLONG        alColors)

// **********************************************************************
//
// Description :
//
// Function    :
//
// Return      :
//
// **********************************************************************

    {

    if( alColors)
        {
// printf( "PrtBitmapOut: Setup Color table with %lu colors\n", cColors);
        GpiCreateLogColorTable( pjob->pdata->pt_hps,
                                0L, LCOLF_CONSECRGB,
                                0L, cColors, alColors);
        }

// printf( "PrtBitmapOut: Output bitmap...\n");
    if( GpiWCBitBlt( pjob->pdata->pt_hps,
                     hbm,
                     4L,
                     aptl,
                     ROP_SRCCOPY,
                     BBO_IGNORE ) != GPI_OK)

        {
        TRACEWINERRORN( "PrtBitmapout: ERROR - GpiBitBlt to printer failed severity %X error %X")
        return FALSE;
        }
    return TRUE;

    } // end of PrtBitmapOut()


// **********************************************************************

BOOL PrtDrawJPEG( PJOB_TYPE   pjob,
                  PSZ         file_name,
                  POINTL      bl,
                  POINTL      tr,
                  LONG        th,
                  LONG        lcolor,
                  PSZ         title)

// **********************************************************************

    {
    BOOL            ret = FALSE;
    PSZ             bmp_file;
    STARTDATA       startdata;
    ULONG           idsession;
    PID             processid;
    char            pgm_name[] = "djpeg.exe";
    char            pgm_args[128];
    char            buffer[128];
    PSZ             qname = "\\QUEUES\\VRPRINT.QUE";
    HQUEUE          hq;
    BYTE            prty;
    ES_TYPE         *pend;
    REQUESTDATA     rq;
    ULONG           dlen;

    bmp_file = tempnam( NULL, "vrp");

    DosCreateQueue( &hq, QUE_FIFO | QUE_CONVERT_ADDRESS, qname);

    sprintf( pgm_args, "-bmp -outfile %s %s", bmp_file, file_name);

    startdata.Length      = sizeof(STARTDATA);
    startdata.Related     = SSF_RELATED_CHILD;
//    startdata.FgBg        = SSF_FGBG_FORE;
    startdata.FgBg        = SSF_FGBG_BACK;
    startdata.TraceOpt    = SSF_TRACEOPT_NONE;
    startdata.PgmName     = pgm_name;
    startdata.PgmInputs   = pgm_args;
    startdata.TermQ       = qname;
    startdata.Environment = 0;
    startdata.InheritOpt  = SSF_INHERTOPT_SHELL;
    startdata.SessionType = SSF_TYPE_DEFAULT;
    startdata.PgmTitle    = 0;
    startdata.IconFile    = 0;
    startdata.PgmHandle   = 0;
    startdata.PgmControl  = SSF_CONTROL_INVISIBLE;
    startdata.InitXPos    = 0;
    startdata.InitYPos    = 0;
    startdata.InitXSize   = 0;
    startdata.InitYSize   = 0;
    startdata.Reserved    = 0;
    startdata.ObjectBuffer = buffer;
    startdata.ObjectBuffLen = 128;

    if( DosStartSession(&startdata, &idsession, &processid))
        {
        DosCloseQueue( hq);
        remove( bmp_file);
        return FALSE;
        }

    if( !DosReadQueue( hq, &rq, &dlen, ( PVOID)&pend, 0, DCWW_WAIT, &prty, 0L))
        {
        if( pend->ret_code == 0)
            ret = PrtDrawBitMap( pjob, bmp_file, bl, tr, th, lcolor, title);
        }

    DosCloseQueue( hq);
    remove( bmp_file);
    DosFreeMem( pend);
    return ret;

    } // end of PrtDrawJPEG()


// **********************************************************************

ULONG PrtStringLength( PJOB_TYPE  pjob,
                       PSZ        sz)

// **********************************************************************

    {
    LONG        twips;

    twips = (ULONG) PrtStringLen( pjob, sz);

    if ( twips >= pjob->pdata->pt_wide)
        twips = -1L;
    else if ( pjob->bMetric)
        twips = ( LONG)( ( double)twips / TWIPS_PER_MIL);
    else
        twips = ( LONG)( ( double)twips / TWIPS_PER_TEN);

    return twips;

    } // end of PrtStringLength()


// **********************************************************************

ULONG PrtXPos( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL      ptl;
    ULONG       here;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    here = ptl.x;
    here -= pjob->pdata->pt_lmargin;

    if ( pjob->bMetric)
        here = ( LONG)( ( double)here / TWIPS_PER_MIL);
    else
        here = ( LONG)( ( double)here / TWIPS_PER_TEN);

    return here;

    } // end of PrtXPos()


// **********************************************************************

ULONG PrtYPos( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL      ptl;
    ULONG       here;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    here = ptl.y;
    here -= pjob->pdata->pt_bmargin;

    if ( pjob->bMetric)
        here = ( LONG)( ( double)here / TWIPS_PER_MIL);
    else
        here = ( LONG)( ( double)here / TWIPS_PER_TEN);

    return here;

    } // end of PrtYPos()


// **********************************************************************

ULONG PrtXPosTwips( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL      ptl;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    return ptl.x;

    } // end of PrtXPosTwips()


// **********************************************************************

ULONG PrtYPosTwips( PJOB_TYPE pjob)

// **********************************************************************

    {
    POINTL      ptl;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);

    return ptl.y;

    } // end of PrtYPosTwips()

// **********************************************************************

VOID PrtLine( PJOB_TYPE pjob,
              POINTL bl,
              POINTL tr,
              LONG thickness,
              LONG lcl,
              LONG ltype)

// **********************************************************************

    {
    LONG    oldline,
            path_id = 1L;
    POINTL  ptlhere;                /* Here we are now */

    /***** Store the current current cursor position ********************/

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    GpiSetColor( pjob->pdata->pt_hps, lcl);

    GpiSetColor( pjob->pdata->pt_hps, lcl);

    if( thickness > 1)
        {
        GpiSetLineWidthGeom( pjob->pdata->pt_hps, thickness);
        GpiBeginPath( pjob->pdata->pt_hps, path_id);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);
        GpiLine( pjob->pdata->pt_hps, &tr);
        GpiEndPath( pjob->pdata->pt_hps);
        GpiStrokePath( pjob->pdata->pt_hps, 1, 0);
        }
    else
        {
        if( thickness == 0)
            GpiSetLineWidth( pjob->pdata->pt_hps, LINEWIDTH_NORMAL);
        else
            GpiSetLineWidth( pjob->pdata->pt_hps, LINEWIDTH_THICK);

        oldline = GpiQueryLineType( pjob->pdata->pt_hps);
        GpiSetLineType( pjob->pdata->pt_hps, ltype);
        GpiSetCurrentPosition( pjob->pdata->pt_hps, &bl);
        GpiLine( pjob->pdata->pt_hps, &tr);
        GpiSetLineType( pjob->pdata->pt_hps, oldline);

        } // end of else

    /***** Restore the original position etc. ***************************/

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    GpiSetCurrentPosition( pjob->pdata->pt_hps, &ptlhere);

    } // end of PrtLine()

/*
 * ColorToIndex
 */

LONG ColorToIndex( PSZ  pszCol)

    {
    BOOL        found = FALSE;
    LONG        lclr = CLR_DEFAULT;
    int         i = 0;

    strupr( pszCol);

    while ( (i < 17) && !found)
        {
        if ( !strcmp( pszCol, col_arr[ i].acClr))
            {
            lclr = col_arr[ i].lClr;
            found = TRUE;
            } // end of if
        i++;
        } // end of while

    return ( lclr);

    } // end of ColorToIndex()

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
