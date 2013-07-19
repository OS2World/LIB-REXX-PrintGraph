// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTGRAFC.C  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:09:24  $
//
// $Log:   M:\prtgraph\prtgrafc.c_v  $
// 
//    Rev 1.0   04 May 1996 21:09:24   KANIS
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

#include    <os2.h>
#include    <bseerr.h>
#include    <stdlib.h>
#include    <string.h>
#include    <stdio.h>
#include    <ctype.h>
#include    <tstngen.h>
#include    "prtgrafc.h"
#include    "prt_int.h"
#include    "prt_dlg.h"

extern PRT_LIST     pPrtList;       // List of printer data

char    tag1[] = "AAA4620";
ULONG   demo = 0XFFFFFFFF;
PSZ     module_name = "PRTGRAFC";
BOOL    use_hook = TRUE;

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetPrinter( HGRPRT      hp,
                                USHORT      idx)
 
/************************************************************************
*                                                                       *
* Description : Set the current printer using the index                 *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;

    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( pjob->bPrinting)    
        return PRTGR_ERR_PRINTING;

    PrtSetPrinter( pjob, ( int)idx);    
    PrtQueryQueueInfo( pjob);
    
    return PRTGR_OK;
    
    } /* end of PrtGSetPrinter() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetDlgButtonTexts( HGRPRT  hp,
                                       PSZ     pszBut1,
                                       PSZ     pszBut2,
                                       PSZ     pszBut3)
 
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
    PJOB_TYPE       pjob;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;

    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if( pszBut1)
        strcpy( pjob->acDlgBut1, pszBut1);
        
    if( pszBut2)
        strcpy( pjob->acDlgBut2, pszBut2);

    if( pszBut3)
        strcpy( pjob->acDlgBut3, pszBut3);

    return PRTGR_OK;
    
    } /* end of PrtGSetDlgButtonTexts() */

/*
*************************************************************************/
 
PSZ APIENTRY PrtGPrinterDialog( HGRPRT     hp,
                                HWND       hwnd,
                                PSZ        pszTitle)
 
/************************************************************************
*                                                                       *
* Description : Pop up the printer selection dialog                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return( NULL);
    
    if ( pjob->bPrinting)    
        return NULL;

    if ( pszTitle)
        strcpy( pjob->prt_tit, pszTitle);
    else
        strcpy( pjob->prt_tit, "Choose Printer");
  
    PrtGetPrinterList( );

    WinDlgBox( HWND_DESKTOP,
               hwnd,
               (PFNWP)PrtPrinterDlgProc,
               pjob->hmod,
               PRT_DLG_PRINTERS,
               pjob);
    
    PrtQueryQueueInfo( pjob);
    return( pjob->szPrtDlgRet);
    
    } /* end of PrtGPrinterDlg() */

/*
*************************************************************************/
 
PSZ APIENTRY PrtGVersion( )
 
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
    PSZ         dummy;
    
    dummy = strdup( VER_NUM);
    return( dummy);

    } /* end of PrtGVersion() */
/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintLine( HGRPRT         hp,
                               PSZ            szFont,
                               ULONG          points,
                               PSZ            szString)
 
/************************************************************************
*                                                                       *
* Description : Write a string on the printer, followed by a line feed  *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if( szString == NULL)
        return PRTGR_ERR_PARAMETER;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    /***** Check if font is set up **************************************/

    if( pjob->pdata->pt_table != NULL)
        PrtWriteCol( pjob, szFont, points, szString, JUST_LEFT);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

        PrtWriteln( pjob, szString);
        TST_TRACE(( "PrtGWriteln - printed '%s'", szString))

        }

    return PRTGR_OK;

    } /* end of PrtGWriteln() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintRight( HGRPRT       hp,
                                PSZ          szFont,
                                ULONG        points,
                                PSZ          szString)
 
/************************************************************************
*                                                                       *
* Description : Write a string on the printer, justified right and      *
*               followed by a carriage return.                          *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if( szString == NULL)
        return PRTGR_ERR_PARAMETER;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    /***** Check if font is set up **************************************/

    if( pjob->pdata->pt_table != NULL)
        PrtWriteCol( pjob, szFont, points, szString, JUST_RIGHT);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

        PrtJustRight( pjob, szString);

        TST_TRACE(( "PrtGJustRight - printed '%s'", szString))

        }

    return PRTGR_OK;

    } /* end of PrtGJustRight() */


/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintJustified( HGRPRT       hp,
                                    PSZ          szFont,
                                    ULONG        points,
                                    PSZ          szString)
 
/************************************************************************
*                                                                       *
* Description : Write a string on the printer, justified right and      *
*               followed by a carriage return.                          *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if( szString == NULL)
        return PRTGR_ERR_PARAMETER;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    TST_TRACE(( "PrtGJustified - %lupt %s on %p ('%s')", points, szFont, pjob, szString))

    /***** Check if font is set up **************************************/

    if( pjob->pdata->pt_table != NULL)
        PrtWriteCol( pjob, szFont, points, szString, JUST_JUSTIFY);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

        PrtWrite( pjob, szString, JUST_JUSTIFY);
        TST_TRACE(( "PrtGJustified - printed '%s'", szString))
        }

    return PRTGR_OK;

    } /* end of PrtGJustified() */


/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintCentered( HGRPRT      hp,
                                   PSZ         szFont,
                                   ULONG       points,
                                   PSZ         szString)
 
/************************************************************************
*                                                                       *
* Description : Write a string on the printer, centred and followed by  *
*               carriage return.                                        *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( szString == NULL)
        return PRTGR_ERR_PARAMETER;

    /***** Check if font is set up **************************************/

    if( pjob->pdata->pt_table != NULL)
        PrtWriteCol( pjob, szFont, points, szString, JUST_CENTRE);
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

        PrtCentre( pjob, szString);
        TST_TRACE(( "PrtGCentre - printed '%s'", szString))
        }

    return PRTGR_OK;

    } /* end of PrtGCentre() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetMargins( HGRPRT      hp,
                                ULONG       ullm,
                                ULONG       ulrm,
                                ULONG       ultm,
                                ULONG       ulbm,
                                ULONG       ulpb,
                                ULONG       ulfs)
 
/************************************************************************
*                                                                       *
* Description : Set the margins for the print job                       *
*                                                                       *
* Parameters  : job_pointer (from PrtGInit)                             *
*               left_margin (mm)                                        *
*               right_margin (mm)                                       *
*               top_margin(mm)                                          *
*               bottom_margin (mm)                                      *
*               page_border (twips)                                     *
*               page_fill_style                                         *
*                                                                       *
* Return      : 1 ok 0 error                                            *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( pjob->bPrinting)    
        return PRTGR_ERR_PRINTING;

    pjob->pdata->pt_left_margin = ullm;
    pjob->pdata->pt_right_margin = ulrm;
    pjob->pdata->pt_top_margin = ultm;
    pjob->pdata->pt_bot_margin = ulbm;
    pjob->pdata->pt_border = ulpb;
    pjob->pdata->pt_fill = ulfs;
    return PRTGR_OK;
    
    } /* end of PrtGSetMargins() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetPrintColors( HGRPRT    hp,
                                    LONG      lctext,
                                    LONG      lcborder,
                                    LONG      lcfill)
 
/************************************************************************
*                                                                       *
* Description : Set page printing colours                               *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if( lctext != CLR_NOINDEX)
        {
        pjob->bColor = TRUE;
        pjob->lColor = lctext;
        }

    if( lcborder != CLR_NOINDEX)
        {
        pjob->bColor = TRUE;
        pjob->pdata->pt_blcolor = lcborder;
        }

    if( lcfill != CLR_NOINDEX)
        {
        pjob->bColor = TRUE;
        pjob->pdata->pt_bfcolor = lcfill;
        }

    return PRTGR_OK;
    
    } /* end of PrtGSetPrintColors() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetLineSpace( HGRPRT        hp,
                                  USHORT        usSpace)
 
/************************************************************************
*                                                                       *
* Description : Set the line spacing for printing.                      *
*                                                                       *
* Parameters  : job_pointer (from PrtGInit)                             *
*               left_margin (mm)                                        *
*               right_margin (mm)                                       *
*               top_margin(mm)                                          *
*               bottom_margin (mm)                                      *
*               page_border (twips)                                     *
*               page_fill_style                                         *
*                                                                       *
* Return      : 1 ok 0 error                                            *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    pjob->usline_space = usSpace;

    return PRTGR_OK;
    
    } /* end of PrtGSetLineSpace() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetHeader( HGRPRT           hp,
                               HHEADER          hhdr)
 
/************************************************************************
*                                                                       *
* Description : Set the extra lines for the header                      *
*                                                                       *
* Parameters  : job_pointer (from PrtGInit)                           *
*               number of header lines                                  *
*               Extra_header_line_1                                     *
*               Extra_header_line_2                                     *
*               Extra_header_line_3                                     *
*               Extra_header_line_4                                     *
*               Extra_header_line_5                                     *
*                                                                       *
* Return      : 1 ok 0 error                                            *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    PHDR_DEF_TYPE   phdr;
    USHORT          i;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    phdr = ( PHDR_DEF_TYPE) hhdr;
    if ( phdr == NULL )
        return PRTGR_ERR_INV_HANDLE;

    pjob->pdata->pt_header = phdr->bHeader;

    if( !phdr->bHeader)
        return PRTGR_OK;

    if( pjob->pdata->pt_psz)
        {
        for ( i = 0; i < pjob->pdata->pt_hlines; i++)
            if( pjob->pdata->pt_psz[ i].pszLine)
                FREE( pjob->pdata->pt_psz[ i].pszLine);
        FREE( pjob->pdata->pt_psz);
        }

    pjob->pdata->pt_allpages = phdr->bAllpages;
    strcpy( pjob->pdata->pt_hfont, phdr->pszhFont);
    pjob->pdata->pt_hpts = phdr->ulpoints;
    pjob->pdata->pt_hbox_mode = phdr->ulbox_mode;
    pjob->pdata->pt_hbox_line = phdr->ulbox_line;
    pjob->pdata->pt_hlines = phdr->num_lines;
    pjob->pdata->pt_hlcolor = phdr->lhlcolor;
    pjob->pdata->pt_htcolor = phdr->lhtcolor;
    pjob->pdata->pt_hfcolor = phdr->lhfcolor;
    
    TST_TRACE(( "PrtGSetHeader: NOTE - Set hlines to %u", pjob->pdata->pt_hlines))

    PrtInitHeader( pjob, phdr->num_lines);
    
    for ( i = 0; i < pjob->pdata->pt_hlines; i++)
        {
        TST_TRACE(( "PrtGSetHeader: NOTE - Set header line (%u) %lu.%s '%s'", i, 
                    phdr->ppsz[ i].lpts, phdr->ppsz[ i].cfont,
                    phdr->ppsz[ i].pszLine))
        strcpy( pjob->pdata->pt_psz[ i].cfont, phdr->ppsz[ i].cfont);
        pjob->pdata->pt_psz[ i].lpts = phdr->ppsz[ i].lpts;
        pjob->pdata->pt_psz[ i].pszLine = strdup( phdr->ppsz[ i].pszLine);
        } /* end of for */
    
    TST_TRACE(( "PrtGSetHeader: returns set %u lines (%lu)", 
                pjob->pdata->pt_hlines, pjob->pdata->pt_header))
        
    return PRTGR_OK;
    
    } /* end of PrtGSetHeader() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetFooter( HGRPRT           hp,
                               HFOOTER          hftr)

/************************************************************************
*                                                                       *
* Description : Set the box style etc.. for the header                  *
*                                                                       *
* Parameters  : job_pointer (from PrtGInit)                           *
*               footer_font_name                                        *
*               footer_font_pts                                         *
*               footer_box_mode                                         *
*               footer_box_line (twips)                                 *
*               footer_text                                             *
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    PFTR_DEF_TYPE   pftr;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    pftr = ( PFTR_DEF_TYPE) hftr;
    if ( pftr == NULL )
        return PRTGR_ERR_INV_HANDLE;

    pjob->pdata->pt_footer = pftr->bFooter;
    
    if( !pftr->bFooter)
        return PRTGR_OK;
        
    strcpy( pjob->pdata->pt_ffont, pftr->pszfFont);
    pjob->pdata->pt_fpts = pftr->ulpoints;
    pjob->pdata->pt_fbox_mode = pftr->ulbox_mode;
    pjob->pdata->pt_fbox_line = pftr->ulbox_line;
    pjob->pdata->pt_flcolor = pftr->flcolor;
    pjob->pdata->pt_ffcolor = pftr->ffcolor;
    pjob->pdata->pt_ftcolor = pftr->ftcolor;
    
    strcpy( pjob->pdata->pt_footline, pftr->pszString);
    
   return PRTGR_OK;
    
    } /* end of PrtGSetFooter() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGAbortPrintJob( HGRPRT  hp)
 
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
    PJOB_TYPE       pjob;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    PrtAbort( pjob);
    
    return PRTGR_OK;
    
    } /* end of PrtGAbortPrintJob() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGOpenPrintJob( HGRPRT        hp,
                                  PSZ           pszTitle,
                                  USHORT        uspages,
                                  USHORT        copies)

/************************************************************************
*                                                                       *
* Description : Open a graphics print job on the chosen device          *
*                                                                       *
* Parameters  : job_pointer (from PrtGInit)                           *
*               printer index (from PrtGInitPrint)                    *
*               job_title                                               *
*               total_pages                                             *
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    LONG            i;
    
    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if( demo)
        {
        char    demo_str[ 256];
        PSZ     d_str = "This is an unregistered version of\n"
                        "PrtGraph C/C++ Library v%s\n\n"
                        "This product is shareware and can be "
                        "registered through CompuServe or by "
                        "contacting the address in the online "
                        "programming help\n\n"
                        "¸1996 ADD Consulting (CH)";
        sprintf( demo_str, d_str, VER_NUM);
        WinMessageBox( HWND_DESKTOP, 
                       HWND_DESKTOP,
                       demo_str,
                       "PRTGRAFC - Unregistered Version",
                       0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
        }

    if ( pjob->bPrinting)    
        return PRTGR_ERR_PRINTING;

    /***** get the job title ********************************************/
    
    strcpy( pjob->pdata->doc_name, pszTitle);
    pjob->pdata->pt_pages = uspages;

    if ( pjob->DevStruct.pszQueueProcParams)
        FREE( pjob->DevStruct.pszQueueProcParams);

    if ( copies)
        {
        pjob->DevStruct.pszQueueProcParams = ( PSZ) malloc( 64);
        sprintf( pjob->DevStruct.pszQueueProcParams, "COP=%u", copies);
        }

    /***** Open the printer job *****************************************/
    
    if ( !PrtOpen( pjob, copies))
        return PRTGR_ERR_JOB_OPEN;

    /***** Set Header box ***********************************************/
    
    PrtSetHeaderBox( pjob);
    
    /***** Set page borders *********************************************/
    
    if ( pjob->pdata->pt_border != 0)
        PrtSetBorder( pjob);
    
    /***** Allocate tabs ************************************************/
    
    pjob->numtabs = (pjob->pdata->pt_wide / pjob->tab_len) - 1;
    
    pjob->tabs = ( LONG*) malloc( pjob->numtabs * sizeof( LONG));
    memset( pjob->tabs, 0, pjob->numtabs * sizeof( LONG));
    
    /***** set tabs *****************************************************/
    
    pjob->tabs[ 0] = pjob->pdata->pt_lmargin + pjob->tab_len;
    
    for ( i = 1; i < pjob->numtabs; i++)
        pjob->tabs[ i] = pjob->tabs[ i-1] + pjob->tab_len;
    
    /***** Start the job ************************************************/

    pjob->pdata->pt_page = 0;

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);

    PrtNewPage( pjob);
    
    return PRTGR_OK;
    
    } /* end of PrtGOpenPrintJob() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGClosePrintJob( HGRPRT       hp)
 
/************************************************************************
*                                                                       *
* Description : Close the print job                                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    pjob = (PJOB_TYPE) hp;

    if ( pjob == NULL)
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    /******* 1. Close Print Job *****************************************/

    PrtClose( pjob);

    return PRTGR_OK;
    
    } /* end of PrtGClosePrintJob() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintBox( HGRPRT      hp,
                              ULONG       ulblx,
                              ULONG       ulbly,
                              ULONG       ultrx,
                              ULONG       ultry,
                              ULONG       ulline,
                              ULONG       ulfill,
                              LONG        lcborder,
                              LONG        lcfill)
 
/************************************************************************
*                                                                       *
* Description : Draw a box to the printer, coords in mm cartesian       *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE           pjob;
    USHORT              usbtype = 0;
    POINTL              bl,
                        tr;
    
    pjob = (PJOB_TYPE) hp;

    if ( pjob == NULL)
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( lcborder == -10)
        lcborder = pjob->lColor;

    if( lcfill == -10)
        lcfill = pjob->lColor;

    bl.x = ( ulblx * TWIPS_PER_MIL) + pjob->pdata->pt_lmargin;
    bl.y = ( ulbly * TWIPS_PER_MIL) + pjob->pdata->pt_bl_offset.cy;
    tr.x = ( ultrx * TWIPS_PER_MIL) + pjob->pdata->pt_lmargin;
    tr.y = ( ultry * TWIPS_PER_MIL) + pjob->pdata->pt_bl_offset.cy;

    PrtBox( pjob, bl, tr, ( LONG)ulline, ( LONG)ulfill, usbtype, lcborder, lcfill);

    GpiSetColor( pjob->pdata->pt_hps, pjob->lColor);
    
    return PRTGR_OK;

    } /* end of PrtGBoxColor() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintLeft( HGRPRT       hp,
                               PSZ          szFont,
                               ULONG        points,
                               PSZ          szString)
 
/************************************************************************
*                                                                       *
* Description : Write a string at current position in the font & point  *
*               given                                                   *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;

    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( szString == NULL)
        return PRTGR_ERR_PARAMETER;

    /***** Check if font is set up **************************************/
    
    if( pjob->pdata->pt_table != NULL)
        {
        PrtWriteCol( pjob, szFont, points, szString, JUST_LEFT);
        TST_TRACE(( "PrtGWrite: NOTE - Cell has %u lines", 
                   pjob->pdata->pt_table->aCol[ pjob->pdata->pt_col].uslines))
        }
    else
        {
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;

        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
        PrtWrite( pjob, szString, JUST_LEFT);
        }

    TST_TRACE(( "PrtGWrite - NOTE - finished printing"))

    return PRTGR_OK;

    } /* end of PrtGWrite() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGNewPage( HGRPRT     hp)
 
/************************************************************************
*                                                                       *
* Description : Force a form feed                                       *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( ! pjob->pdata->pt_table)
        PrtNewPage( pjob);
    else
        pjob->pdata->pt_table->bNewPage = TRUE;

    return PRTGR_OK;

    } /* end of PrtGNewPage() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGStartTable( HGRPRT          hp,
                                HTABLE          htbl)
 
/************************************************************************
*                                                                       *
* Description : Define a table                                          *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    {
    PJOB_TYPE       pjob;
    PTABLE_DEF_TYPE ptbl;
    int             j;
    POINTL          ptl;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    ptbl = ( PTABLE_DEF_TYPE) htbl;
    if ( ptbl == NULL)
        return PRTGR_ERR_INV_HANDLE;
        
    /***** Create table structure ***************************************/
    
    pjob->pdata->pt_table = PrtCreateTable( ptbl->usCols);
    
    TST_TRACE(( "PrtGStartTable: NOTE - created table structure %p", pjob->pdata->pt_table))
    
    /***** Fill internal table struct ***********************************/
    
    pjob->pdata->pt_table->bFirstRow = TRUE;
    pjob->pdata->pt_table->lfill = ptbl->lfill;
    pjob->pdata->pt_table->lline_type = ptbl->lline_type;
    pjob->pdata->pt_table->bHeader = ptbl->bHeader;
    pjob->pdata->pt_table->lhfill = ptbl->lhfill;
    pjob->pdata->pt_table->lhline_type = ptbl->lhline_type;
    pjob->pdata->pt_table->bAllPages = ptbl->bAllPages;
    pjob->pdata->pt_table->lpts = ptbl->lpts;

    pjob->pdata->pt_table->ltcolor = ptbl->ltcolor;
    pjob->pdata->pt_table->llcolor = ptbl->llcolor;
    pjob->pdata->pt_table->lfcolor = ptbl->lfcolor;

    pjob->pdata->pt_table->lhtcolor = ptbl->lhtcolor;
    pjob->pdata->pt_table->lhlcolor = ptbl->lhlcolor;
    pjob->pdata->pt_table->lhfcolor = ptbl->lhfcolor;

    strcpy( pjob->pdata->pt_table->cFont, ptbl->cFont);
    if( pjob->pdata->pt_table->lline_type > 0)
        pjob->pdata->pt_table->boxed = TRUE;

    /***** Get column definitions ***************************************/
    
    for ( j = 0; j < ptbl->usCols; j++)
        {
        pjob->pdata->pt_table->aCol[ j].llm_box = ptbl->aCol[ j].ulLeft  * TWIPS_PER_MIL;
        pjob->pdata->pt_table->aCol[ j].lrm_box = ( ptbl->aCol[ j].ulWide * TWIPS_PER_MIL)
                                                  + pjob->pdata->pt_table->aCol[ j].llm_box;
        if ( pjob->pdata->pt_table->boxed)
            {
            pjob->pdata->pt_table->aCol[ j].llm_text = pjob->pdata->pt_table->aCol[ j].llm_box + 
                                                       pjob->pdata->pt_table->lline_type;
            pjob->pdata->pt_table->aCol[ j].lrm_text = pjob->pdata->pt_table->aCol[ j].lrm_box - 
                                                       pjob->pdata->pt_table->lline_type;
            } /* end of if */
        else
            {
            pjob->pdata->pt_table->aCol[ j].llm_text = pjob->pdata->pt_table->aCol[ j].llm_box;
            pjob->pdata->pt_table->aCol[ j].lrm_text = pjob->pdata->pt_table->aCol[ j].lrm_box;
            } /* end of else */
        
        pjob->pdata->pt_table->aCol[ j].lrm_text -= (ONE_MIL * 2);
        pjob->pdata->pt_table->aCol[ j].llm_text += (ONE_MIL * 2);
        if( ptbl->aCol[ j].pszText)
            {
            pjob->pdata->pt_table->aCol[ j].pszHeader = ( PSZ) malloc( strlen( ptbl->aCol[ j].pszText) + 2);
            strcpy( pjob->pdata->pt_table->aCol[ j].pszHeader, ptbl->aCol[ j].pszText);
            }

        pjob->pdata->pt_table->aCol[ j].uslines = 0;
        pjob->pdata->pt_table->aCol[ j].usstart = 0;
        pjob->pdata->pt_table->aCol[ j].usnewpage = 0;
        pjob->pdata->pt_table->aCol[ j].lpts = 0;
        pjob->pdata->pt_table->aCol[ j].alines = NULL;
        strcpy( pjob->pdata->pt_table->aCol[ j].cFont, "");

        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    pjob->pdata->pt_table->ptltr.x = pjob->pdata->pt_table->aCol[ pjob->pdata->pt_table->usCols-1].lrm_box;
    pjob->pdata->pt_table->ptltr.y = ptl.y;
    pjob->pdata->pt_table->ly_pos = ptl.y;
    
    if( pjob->pdata->pt_table->bHeader)
        {
        if( PrtWriteTableHeader( pjob))    
            {
            TST_TRACE(( "PrtGRxBeginTable: NOTE - successful completion"))
            return PRTGR_OK;
            }
        else
            {
            TST_TRACE(( "PrtGRxBeginTable: ERROR - failed to print header"))
            return PRTGR_ERR_TABLE_HEADER;
            }
        }
    else
        {
        TST_TRACE(( "PrtGRxBeginTable: NOTE - successful completion"))
        return PRTGR_OK;
        }
    
    } /* end of PrtGStartTable() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGEndTable( HGRPRT        hp)
 
/************************************************************************
*                                                                       *
* Description : Terminate writing to a table                            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    {
    PJOB_TYPE       pjob;
    POINTL          ptl;
    USHORT          i;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( pjob->pdata->pt_table == NULL)  
        return PRTGR_ERR_NOT_TABLE;

    /***** Restore margins for page *************************************/
    
    pjob->pdata->pt_tmargin = pjob->pdata->pt_table->ptltr.y - (ONE_MIL * 2);

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptl);
    ptl.x = pjob->pdata->pt_lmargin;
    ptl.y = pjob->pdata->pt_tmargin;
    GpiMove( pjob->pdata->pt_hps, &ptl);

    pjob->pdata->pt_table = PrtFreeTable( pjob->pdata->pt_table);

    return PRTGR_OK;
    
    } /* end of PrtGEndTable() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGStartRow( HGRPRT        hp)
 
/************************************************************************
*                                                                       *
* Description : Start a new row in the table                            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    USHORT          i, j;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( pjob->pdata->pt_table == NULL)  
        return PRTGR_ERR_NOT_TABLE;

    /***** Initialise table parameters for new row **********************/
    
    pjob->pdata->pt_tmargin = pjob->pdata->pt_table->ly_pos;

    PrtFreeCells( pjob->pdata->pt_table);

    return PRTGR_OK;
    
    } /* end of PrtGStartRow() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGEndRow( HGRPRT      hp)
 
/************************************************************************
*                                                                       *
* Description : End a row and draw any boxes                            *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    PTABLE_TYPE     ptable;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    ptable = pjob->pdata->pt_table;
    if ( ptable == NULL )
        return PRTGR_ERR_NOT_TABLE;
    
    return( PrtEndRow( pjob));
    
    } /* end of PrtGEndRow() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGStartCol( HGRPRT        hp,
                              USHORT        uscols)
 
/************************************************************************
*                                                                       *
* Description : Start writing to a new column                           *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( pjob->pdata->pt_table == NULL)
        return PRTGR_ERR_NOT_TABLE;

    if( !uscols || ( uscols > pjob->pdata->pt_table->usCols))
        return PRTGR_ERR_PARAMETER;

    pjob->pdata->pt_col = uscols - 1;
    
    TST_TRACE(( "PrtGStartCol: NOTE - start printing for column %u", pjob->pdata->pt_col))
    
    return PRTGR_OK;
    
    } /* end of PrtGStartCol() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGGoto( HGRPRT        hp,
                          ULONG         ulx,
                          ULONG         uly,
                          BOOL          points)
 
/************************************************************************
*                                                                       *
* Description : Move graphic cursor to a position                       *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( pjob->pdata->pt_table != NULL)
        return PRTGR_ERR_NOT_TABLE;

    PrtGoto( pjob, ulx, uly, points);
   
    return PRTGR_OK;
        
    } /* end of PrtGGoto() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGTab( HGRPRT     hp)
 
/************************************************************************
*                                                                       *
* Description : Execute a tabulation                                    *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    POINTL          ptl;
    LONG            i;
    
    pjob = (PJOB_TYPE) hp;

    if ( pjob == NULL)
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

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
    
    return PRTGR_OK;
    
    } /* end of PrtGTab() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGJobProperties( HGRPRT       hp,
                                   HWND         hwnd)
 
/************************************************************************
*                                                                       *
* Description : Initialise for the test engine and register the prog.   *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    LONG            buflen;
    char            dlgstr[ 128],
                    titstr[ 128];
    ERRORID         errid;
    USHORT          usSev,
                    usCode;
    
    pjob = (PJOB_TYPE) hp;

    if ( pjob == NULL)
        return PRTGR_ERR_INV_HANDLE;
    
    if ( pjob->bPrinting)    
        return PRTGR_ERR_PRINTING;

    DevPostDeviceModes( pjob->hab,
                        pjob->DevStruct.pdriv,
                        pjob->DevStruct.pszDriverName,
                        pjob->DevStruct.pdriv->szDeviceName,
                        pjob->DevStruct.pszLogAddress,
                        DPDM_POSTJOBPROP);

    PrtQueryQueueInfo( pjob);

    return PRTGR_OK;

    } /* end of PrtGJobProps() */

/*
*************************************************************************/
 
VOID APIENTRY PrtGPrinterList( HGRPRT       hp,
                               BOOL         refresh,
                               PSZ          *pprts)
 
/************************************************************************
*                                                                       *
* Description : Initialise the DevOpenStruc array                       *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    USHORT          i;
    
    if ( refresh)
        PrtGetPrinterList();

    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    for ( i = 0; i < pPrtList.prt_count; i++)
        {
        strcpy( pprts[ i], pPrtList.szPrinterList[ i]);
        }
    DosReleaseMutexSem( pPrtList.hmtx);
    
    } /* end of PrtGPrinterList() */

/*
*************************************************************************/
 
VOID APIENTRY PrtGTerm( HGRPRT      hp)
 
/************************************************************************
*                                                                       *
* Description : Terminate use of the DLL                                *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return;

    PrtObjectDestroy( pjob);
      
    } /* end of PrtGTerm() */

/*
*************************************************************************/
 
HGRPRT APIENTRY PrtGInit( HWND  hwnd, PFNNP     pnpf)
 
/************************************************************************
*                                                                       *
* Description : Initialise use of the printer dll                       *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    HGRPRT          hp = NULLHANDLE;
    PJOB_TYPE       pjob;

    if( demo)
        {
        char    demo_str[ 256];
        PSZ     d_str = "This is an unregistered version of\n"
                        "PrtGraph C/C++ Library v%s\n\n"
                        "This product is shareware and can be "
                        "registered through CompuServe or by "
                        "contacting the address in the online "
                        "programming help\n\n"
                        "¸1996 ADD Consulting (CH)";
        sprintf( demo_str, d_str, VER_NUM);
        WinMessageBox( HWND_DESKTOP, 
                       HWND_DESKTOP,
                       demo_str,
                       "PRTGRAFC - Unregistered Version",
                       0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
        }

    pjob = PrtObjectInit();

    if( pjob)
        {
        pjob->pt_np_func = ( PVOID)pnpf;
        
        if( pjob->pt_np_func)
            pjob->bProgress = FALSE;

        pjob->hwnd = hwnd;
        pjob->hab = WinQueryAnchorBlock( hwnd);
        }

    hp = ( HGRPRT) pjob;
    return( hp);
    
    } /* end of PrtGInit() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintBitMap( HGRPRT      hp,
                                 PSZ         file_name,
                                 ULONG       xl,
                                 ULONG       yb,
                                 ULONG       xr,
                                 ULONG       yt,
                                 ULONG       ulline,
                                 LONG        lcborder,
                                 PSZ         title)
 
/************************************************************************
*                                                                       *
* Description : Print a bitmap sized to the given rectangle             *
*                                                                       *
* Parameters  : print_job                                               *
*               file_name containing bitmap                             *
*               lower_left_x (mm)                                       *
*               lower_left_y (mm)                                       *
*               upper_right_x (mm)                                      *
*               upper_right_y (mm)                                      *
*               frame_thickness (twips)                                 *
*               frame_color                                             *
*               title                                                   *
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    POINTL          bl, tr, ptlhere;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    if( xl > 0)
        bl.x = (xl * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yb > 0)
        bl.y = (yb * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    
    if( xr > 0)
        tr.x = (xr * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yt > 0)
        tr.y = (yt * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;


    TST_TRACE(( "PrtGBitMap: . NOTE print %s (%d, %d) (%d, %d)", file_name, bl.x, bl.y, tr.x, tr.y))

    if( !PrtDrawBitMap( pjob, file_name, bl, tr, ulline, lcborder, title))
        return PRTGR_ERR_INV_BITMAP;
        
    return PRTGR_OK;

    } /* end of PrtGPrintBitMap() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintBitMapRes( HGRPRT      hp,
                                    HMODULE     hmod,
                                    ULONG       resnum,
                                    ULONG       xl,
                                    ULONG       yb,
                                    ULONG       xr,
                                    ULONG       yt,
                                    ULONG       ulline,
                                    LONG        lcborder,
                                    PSZ         title)
 
/************************************************************************
*                                                                       *
* Description : Print a bitmap sized to the given rectangle             *
*                                                                       *
* Parameters  : print_job                                               *
*               Source module handle                                    *
*               Resource number                                         *
*               lower_left_x (mm)                                       *
*               lower_left_y (mm)                                       *
*               upper_right_x (mm)                                      *
*               upper_right_y (mm)                                      *
*               frame_thickness (twips)                                 *
*               frame_color                                             *
*               title                                                   *
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    POINTL          bl, tr, ptlhere;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    if( xl > 0)
        bl.x = (xl * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yb > 0)
        bl.y = (yb * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    
    if( xr > 0)
        tr.x = (xr * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yt > 0)
        tr.y = (yt * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;


    TST_TRACE(( "PrtGBitMap: . NOTE print %s (%d, %d) (%d, %d)", file_name, bl.x, bl.y, tr.x, tr.y))
    
    if( !PrtDrawBitMap2( pjob, hmod, resnum, bl, tr, ulline, lcborder, title))
        return PRTGR_ERR_INV_BITMAP;

    return PRTGR_OK;
    
    } /* end of PrtGPrintBitMapRes() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGPrintJPEG(   HGRPRT      hp,
                                 PSZ         file_name,
                                 ULONG       xl,
                                 ULONG       yb,
                                 ULONG       xr,
                                 ULONG       yt,
                                 ULONG       ulline,
                                 LONG        lcborder,
                                 PSZ         title)
 
/************************************************************************
*                                                                       *
* Description : Print a bitmap sized to the given rectangle             *
*                                                                       *
* Parameters  : print_job                                               *
*               file_name containing bitmap                             *
*               lower_left_x (mm)                                       *
*               lower_left_y (mm)                                       *
*               upper_right_x (mm)                                      *
*               upper_right_y (mm)                                      *
*               frame_thickness (twips)                                 *
*               frame_color                                             *
*               title                                                   *
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    POINTL          bl, tr, ptlhere;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    if( xl > 0)
        bl.x = (xl * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yb > 0)
        bl.y = (yb * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    
    if( xr > 0)
        tr.x = (xr * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yt > 0)
        tr.y = (yt * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;


    TST_TRACE(( "PrtGBitMap: . NOTE print %s (%d, %d) (%d, %d)", file_name, bl.x, bl.y, tr.x, tr.y))
    
    if( !PrtDrawJPEG( pjob, file_name, bl, tr, ulline, lcborder, title))
        return PRTGR_ERR_INV_BITMAP;

    return PRTGR_OK;

    } /* end of PrtGPrintJPEG() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGGetPageSize( HGRPRT     hp,
                                 PULONG     pulWide,
                                 PULONG     pulHigh)
 
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
    
    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;
    
    *pulWide = pjob->pdata->pt_page_size.cx - 
               (pjob->pdata->pt_right_margin + pjob->pdata->pt_left_margin);
    *pulHigh = pjob->pdata->pt_page_size.cy - 
               (pjob->pdata->pt_top_margin + pjob->pdata->pt_bot_margin);
    
    return PRTGR_OK;
   
    } /* end of PrtGGetPageSize() */

/*
*************************************************************************/
 
PSZ APIENTRY PrtGFontDialog( HGRPRT       hp,
                             PSZ          pszTitle,
                             PSZ          pszFamName)
 
/************************************************************************
*                                                                       *
* Description : Get a printer font with the dialog                      *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;
    PSZ             pszTit;

    /***** Get job pointer **********************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return NULL;
    
    if( pszTitle)
        strcpy( pjob->prt_tit, pszTitle);
    else
        strcpy( pjob->prt_tit, "Choose Font");

    if ( pszFamName)
        strcpy( pjob->pszFace, pszFamName);
    else
        strcpy( pjob->pszFace, "");
    
    PrtChooseFont( pjob, pjob->prt_tit, pjob->pszFace);
 
    return( pjob->pszfont);
    
    } /* end of PrtGFontDlg() */

/*
*************************************************************************/
 
HHEADER APIENTRY PrtGDefineHeader( BOOL       bHeader,
                                   BOOL       bAllPages,
                                   PSZ        pszFont,
                                   ULONG      ulPts,
                                   ULONG      ulFill,
                                   ULONG      ulLine,
                                   USHORT     usLines)
 
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
    PHDR_DEF_TYPE   phdr;
    
    phdr = ( PHDR_DEF_TYPE) calloc( 1, sizeof( HDR_DEF_TYPE));
    
    phdr->bHeader = bHeader;
    phdr->bAllpages = bAllPages;
    phdr->ulpoints = ulPts;
    phdr->ulbox_line = ulLine;
    phdr->ulbox_mode = ulFill;
    phdr->lhtcolor = CLR_DEFAULT;
    phdr->lhlcolor = CLR_DEFAULT;
    phdr->lhfcolor = CLR_DEFAULT;
    
    
    if( !usLines || ( usLines > PRTGR_MAX_HLINES))
        usLines = PRTGR_MAX_HLINES;
        
    phdr->num_lines = usLines;
    
    if( pszFont)
        strcpy( phdr->pszhFont, pszFont);
    else
        strcpy( phdr->pszhFont, "Helvetica");
    
    phdr->ppsz = ( PH_LINE) calloc( usLines, sizeof( H_LINE));
    
    return( ( HHEADER)phdr);
    
    } /* end of PrtGDefineHeader() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGDefineHdrColors( HHEADER   hhdr,
                                     LONG      lctext,
                                     LONG      lcborder,
                                     LONG      lcfill)
 
/************************************************************************
*                                                                       *
* Description : Set the colours for printing the headers                *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PHDR_DEF_TYPE   phdr;

    phdr = ( PHDR_DEF_TYPE) hhdr;
    if( !phdr)
        return PRTGR_ERR_INV_HANDLE;

    phdr->lhtcolor = lctext;    
    phdr->lhfcolor = lcfill;
    phdr->lhlcolor = lcborder;
    
    return PRTGR_OK;
    
    } /* end of PrtGDefineHdrColors() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGAddHeaderLine( HHEADER      hhdr,
                                   USHORT       usLine,
                                   PSZ          pszText)
 
/************************************************************************
*                                                                       *
* Description : Add a line for the header                               *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PHDR_DEF_TYPE    phdr;
    
    if( !usLine || ( usLine > PRTGR_MAX_HLINES))
        return PRTGR_ERR_PARAMETER;
    
    phdr = ( PHDR_DEF_TYPE) hhdr;
    if( !phdr)
        return PRTGR_ERR_INV_HANDLE;

    usLine--;

    if( pszText)
        {
        phdr->ppsz[ usLine].pszLine = ( PSZ) malloc( strlen( pszText) + 1);
        strcpy( phdr->ppsz[ usLine].pszLine, pszText);
        }

    strcpy( phdr->ppsz[ usLine].cfont, phdr->pszhFont);
    phdr->ppsz[ usLine].lpts = phdr->ulpoints;

    TST_TRACE(( "PrtGAddHeaderLine: (%u) %lu.%s '%s'", usLine,
                phdr->ppsz[ usLine].lpts,
                phdr->ppsz[ usLine].cfont,
                phdr->ppsz[ usLine].pszLine))

    return PRTGR_OK;
    
    } /* end of PrtGAddHeaderLine() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGSetHeaderLineFont( HHEADER     hhdr,
                                       USHORT      usLine,
                                       PSZ         pszFont,
                                       ULONG       ulPts)
 
/************************************************************************
*                                                                       *
* Description : Set the font for a given header line                    *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PHDR_DEF_TYPE    phdr;
    
    phdr = ( PHDR_DEF_TYPE) hhdr;
    if( !phdr)
        return PRTGR_ERR_INV_HANDLE;

    if( !usLine || ( usLine > phdr->num_lines))
        return PRTGR_ERR_PARAMETER;
    
    usLine--;
    
    if( pszFont)
        strcpy( phdr->ppsz[ usLine].cfont, pszFont);
    else
        strcpy( phdr->ppsz[ usLine].cfont, phdr->pszhFont);
    
    if( ulPts)
        phdr->ppsz[ usLine].lpts = ulPts;
    else
        phdr->ppsz[ usLine].lpts = phdr->ulpoints;
    
    return PRTGR_OK;
    
    } /* end of PrtGSetHeaderLineFont() */

/*
*************************************************************************/
 
HFOOTER APIENTRY PrtGDefineFooter( BOOL       bFooter,
                                   PSZ        pszFont,
                                   ULONG      ulPts,
                                   ULONG      ulFill,
                                   ULONG      ulLine,
                                   PSZ        pszText)

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
    PFTR_DEF_TYPE   pftr;
    
    pftr = ( PFTR_DEF_TYPE) calloc( 1, sizeof( FTR_DEF_TYPE));
    
    pftr->bFooter = bFooter;
    pftr->ulpoints = ulPts;
    pftr->ulbox_line = ulLine;
    pftr->ulbox_mode = ulFill;
    pftr->ftcolor = CLR_DEFAULT;    
    pftr->ffcolor = CLR_DEFAULT;    
    pftr->flcolor = CLR_DEFAULT;    

    if( pszFont)
        strcpy( pftr->pszfFont, pszFont);
    else
        strcpy( pftr->pszfFont, "Helvetica");
    
    if( pszText)
        {
        pftr->pszString = ( PSZ) malloc( strlen( pszText) + 2);
        strcpy( pftr->pszString, pszText);
        }
    else
        {
        pftr->pszString = ( PSZ) malloc( 128);
        strcpy( pftr->pszString, "");
        }
    
    return( ( HFOOTER)pftr);
    
    } /* end of PrtGDefineHeader() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGDefineFtrColors( HFOOTER   hftr,
                                     LONG      lctext,
                                     LONG      lcborder,
                                     LONG      lcfill)
 
/************************************************************************
*                                                                       *
* Description : Set the colours for printing the footers                *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PFTR_DEF_TYPE   pftr;

    pftr = ( PFTR_DEF_TYPE) hftr;
    if( !pftr)
        return PRTGR_ERR_INV_HANDLE;

    pftr->ftcolor = lctext;    
    pftr->ffcolor = lcfill;
    pftr->flcolor = lcborder;
    
    return PRTGR_OK;
    
    } /* end of PrtGDefineFtrColors() */

/*
*************************************************************************/

HTABLE APIENTRY PrtGDefineTable( BOOL      boxed,
                                 BOOL      bHeader,
                                 BOOL      bAllPages,
                                 ULONG     lLine,
                                 ULONG     lFill,
                                 ULONG     lHline,
                                 ULONG     lHfill,
                                 PSZ       pszFont,
                                 ULONG     lPts,
                                 USHORT    usCols,
                                 ULONG     ulLeft)

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
    PTABLE_DEF_TYPE ptbl;

    ptbl = ( PTABLE_DEF_TYPE) calloc( 1, sizeof( TABLE_DEF_TYPE));
    
    ptbl->boxed = boxed;
    ptbl->bHeader = bHeader;
    ptbl->bAllPages = bAllPages;
    ptbl->lline_type = lLine;
    ptbl->lfill = lFill;
    ptbl->lhline_type = lHline;
    ptbl->lhfill = lHfill;
    ptbl->lpts = lPts;
    ptbl->usCols = usCols;
    ptbl->aCol = ( PCOL_DEF_TYPE) calloc( (size_t)usCols, sizeof( COL_DEF_TYPE));
    if( pszFont)
        strcpy( ptbl->cFont, pszFont);
    else
        strcpy( ptbl->cFont, "Helvetica");

    ptbl->ulLeft = ulLeft;
    ptbl->ulCurLeft = ulLeft;

    ptbl->ltcolor = CLR_DEFAULT;
    ptbl->llcolor = CLR_DEFAULT;
    ptbl->lfcolor = CLR_DEFAULT;
    ptbl->lhtcolor = CLR_DEFAULT;
    ptbl->lhlcolor = CLR_DEFAULT;
    ptbl->lhfcolor = CLR_DEFAULT;

    return( ( HTABLE)ptbl);
    
    } /* end of PrtGDefineTable() */

/*
*************************************************************************/
 
USHORT APIENTRY PrtGDefineTableColors( HTABLE   htbl,
                                       LONG     lcct,
                                       LONG     lccl,
                                       LONG     lccf,
                                       LONG     lhct,
                                       LONG     lhcl,
                                       LONG     lhcf)
 
/************************************************************************
*                                                                       *
* Description : Set the colours to be used for printing a table         *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PTABLE_DEF_TYPE ptbl;

    ptbl = ( PTABLE_DEF_TYPE) htbl;
    
    if( !ptbl)
        return PRTGR_ERR_INV_HANDLE;

    ptbl->ltcolor = lcct;
    ptbl->llcolor = lccl;
    ptbl->lfcolor = lccf;

    ptbl->lhtcolor = lhct;
    ptbl->lhlcolor = lhcl;
    ptbl->lhfcolor = lhcf;

    return PRTGR_OK;
         
    } /* end of PrtGDefineTableColors() */

/*
*************************************************************************/

USHORT APIENTRY PrtGAddColumn( HTABLE           htbl,
                               USHORT           usCol,
                               ULONG            ulWide,
                               PSZ              pszHeader)

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
    PTABLE_DEF_TYPE  pTbl;
    
    pTbl = ( PTABLE_DEF_TYPE)htbl;
    
    if( !pTbl)
        return PRTGR_ERR_INV_HANDLE;

    if( !usCol || ( usCol > pTbl->usCols))
        return PRTGR_ERR_PARAMETER;
    
    usCol--;
    
    pTbl->aCol[ usCol].ulLeft = pTbl->ulCurLeft;
    pTbl->aCol[ usCol].ulWide = ulWide;
    pTbl->ulCurLeft += ulWide;
    if ( pszHeader)
        {
        pTbl->aCol[ usCol].pszText = ( PSZ)malloc( strlen( pszHeader) + 1);
        strcpy( pTbl->aCol[ usCol].pszText, pszHeader);
        } /* end of if */

    return PRTGR_OK;
    
    } /* end of PrtGAddColumn() */

/*
*************************************************************************/
 
HTABLE PrtGDestroyTblDef( HTABLE    htbl)
 
/************************************************************************
*                                                                       *
* Description : Destroy table definition structure                      *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PTABLE_DEF_TYPE  pTbl;
    USHORT              i;
    
    pTbl = ( PTABLE_DEF_TYPE)htbl;
    if( !pTbl)
        return( NULLHANDLE);
    
    for ( i = 0; i < pTbl->usCols; i++)
        if( pTbl->aCol[ i].pszText)
            FREE( pTbl->aCol[ i].pszText);
    
    FREE( pTbl->aCol);
    FREE( pTbl);
        
    return( NULLHANDLE);
    
    } /* end of PrtGDestroyTblDef() */

/*
*************************************************************************/
 
HHEADER PrtGDestroyHdrDef( HHEADER     hhdr)
 
/************************************************************************
*                                                                       *
* Description : Destroy Header definition structure                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PHDR_DEF_TYPE       phdr;
    USHORT              i;
    
    phdr = ( PHDR_DEF_TYPE)hhdr;
    
    if( !phdr)
        return( NULLHANDLE);

    if( phdr->ppsz)
        {
        for ( i = 0; i < phdr->num_lines; i++)
            FREE( phdr->ppsz[ i].pszLine);
        }
    FREE( phdr->ppsz);
    FREE( phdr);
    
    return( NULLHANDLE);
    
    } /* end of PrtGDestroyHdrDef() */

/*
*************************************************************************/
 
HFOOTER PrtGDestroyFtrDef( HFOOTER    hftr)
 
/************************************************************************
*                                                                       *
* Description : Destroy Footer definition structure                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PFTR_DEF_TYPE       pftr;
    
    pftr = ( PFTR_DEF_TYPE)hftr;
    
    if( !pftr)
        return( NULLHANDLE);
    
    if( pftr->pszString)
        FREE( pftr->pszString);
    FREE( pftr);

    return( NULLHANDLE);
    
    } /* end of PrtGDestroyFtrDef() */

/*
*************************************************************************/
 
PSZ APIENTRY PrtGCurrentPrinter( HGRPRT      hp)
 
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

    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return NULL;

    return( pjob->szPrinter);
        
    } /* end of PrtGCurrentPrinter() */
/*
*************************************************************************/
 
USHORT APIENTRY PrtGResetColHeader( HGRPRT     hp,
                                    USHORT     usCol,
                                    PSZ        pszText)
 
/************************************************************************
*                                                                       *
* Description : Change the header text for a column                     *
*                                                                       *
* Function    : 
*                                                                       *
* Return      :                                                         *
*                                                                       *
*************************************************************************/
 
    { 
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( !pjob->pdata->pt_table)
        return PRTGR_ERR_NOT_TABLE;
        
    if( !usCol || ( usCol > pjob->pdata->pt_table->usCols))
        return PRTGR_ERR_PARAMETER;
    
    usCol--;
    
    PrtResetColHdr( pjob, usCol, pszText);
    
    return PRTGR_OK;
    
    } /* end of PrtGResetColHeader() */

//
// **********************************************************************
 
USHORT APIENTRY PrtGSet( HGRPRT     hp,
                         USHORT     prop,
                         PROP_TYPE  value)
 
// **********************************************************************
// 
// Description : Set a property for the printer
// 
// Function    : 
// 
// Return      :
// 
// **********************************************************************
 
    { 
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;
 
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    switch ( prop)
        {
        case PRT_LINESPACE :
            Set_LineSpace( pjob, ( USHORT)value.numeric);
            break;

        case PRT_COLORENABLED :
            pjob->bColor = value.flag;
            break;

        case PRT_PRINTCOLOR :
            Set_PrintColor( pjob, value.numeric);
            break;

        case PRT_MEASURES :
            if( !Set_Measures( pjob, value.string))
                return PRTGR_ERR_INV_VALUE;
            break;

        case PRT_WORDBREAK :
            pjob->bWordBreak = value.flag;
            break;

        case PRT_SHOWPROGRESS :
            pjob->bProgress = value.flag;
            break;

        default :
            return PRTGR_ERR_READONLY;
            break;
        
        } // end of switch prop
    
    return PRTGR_OK;
    
    } // end of PrtGSet()

//
// **********************************************************************
 
PROP_TYPE APIENTRY PrtGGet( HGRPRT  hp,
                            USHORT  prop,
                            PUSHORT error)
 
// **********************************************************************
// 
// Description : Get the value of a printer property
// 
// Function    : 
// 
// Return      :
// 
// **********************************************************************
 
    { 
    PROP_TYPE       property;
    PJOB_TYPE       pjob;

    pjob = ( PJOB_TYPE) hp;
    property.flag = 0;
    *error = PRTGR_OK;
    
    if ( pjob == NULL )
        {
        *error = PRTGR_ERR_INV_HANDLE;
        return( property);
        }

    switch ( prop)
        {
        case PRT_LEFTMARGIN :
            property.numeric = pjob->pdata->pt_left_margin;
            break;

        case PRT_RIGHTMARGIN :
            property.numeric = pjob->pdata->pt_right_margin;
            break;

        case PRT_TOPMARGIN :
            property.numeric = pjob->pdata->pt_top_margin;
            break;

        case PRT_BOTTOMMARGIN :
            property.numeric = pjob->pdata->pt_bot_margin;
            break;

        case PRT_PAGEWIDTH :
            property.numeric = pjob->pdata->pt_page_size.cx - 
                    ( ULONG)( pjob->pdata->pt_right_margin + pjob->pdata->pt_left_margin);
            break;

        case PRT_PAGEHEIGHT :
            property.numeric = pjob->pdata->pt_page_size.cy - 
                    ( ULONG)( pjob->pdata->pt_top_margin + pjob->pdata->pt_bot_margin);
            break;

        case PRT_PRINTING :
            property.flag = pjob->bPrinting;
            break;

        case PRT_CURRENTPRINTER :
            property.string = ( PSZ) malloc( strlen( pjob->szPrinter) + 1);
            strcpy( property.string, pjob->szPrinter);
            break;

        case PRT_CURRENTDEVICE :
            property.string = ( PSZ) malloc( strlen( pjob->DevStruct.pszLogAddress) + 1);
            strcpy( property.string, pjob->DevStruct.pszLogAddress);
            break;

        case PRT_DEFAULTPRINTER :
            PrtGetPrinterList( );
            DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
            property.string = ( PSZ) malloc( strlen( pPrtList.szPrinterList[ pPrtList.def_prt]) + 1);
            strcpy( property.string, pPrtList.szPrinterList[ pPrtList.def_prt]);
            DosReleaseMutexSem( pPrtList.hmtx);
            break;

        case PRT_LINESPACE :
            property.numeric = ( ULONG)pjob->usline_space;
            break;

        case PRT_VERSION :
            property.string = strdup( VER_NUM);
            break;

        case PRT_PRINTCOLOR :
            property.numeric = pjob->lColor;
            break;

        case PRT_COLORENABLED :
            property.flag = pjob->bColor;
            break;

        case PRT_MEASURES :
            property.string = ( PSZ) malloc( strlen( pjob->pszMeasure) + 1);
            strcpy( property.string, pjob->pszMeasure);
            break;

        case PRT_PAGENUM :
            property.numeric = ( ULONG)pjob->pdata->pt_page;
            break;

        case PRT_JOBNAME :
            property.string = ( PSZ) malloc( strlen( pjob->pdata->doc_name) + 1);
            strcpy( property.string, pjob->pdata->doc_name);
            break;

        case PRT_MINLEFTMAR :
            property.numeric = pjob->pdata->pt_min_lmargin;
            break;

        case PRT_MINRIGHTMAR :
            property.numeric = pjob->pdata->pt_min_rmargin;
            break;

        case PRT_MINTOPMAR :
            property.numeric = pjob->pdata->pt_min_tmargin;
            break;

        case PRT_MINBOTTOMMAR :
            property.numeric = pjob->pdata->pt_min_bmargin;
            break;

        case PRT_FORMNAME :
            property.string = ( PSZ) malloc( strlen( pjob->pszForm) + 1);
            strcpy( property.string, pjob->pszForm);
            break;

        case PRT_FORMWIDTH :
            property.numeric = ( ULONG)pjob->pdata->pt_page_size.cx;
            break;

        case PRT_FORMHEIGHT :
            property.numeric = ( ULONG)pjob->pdata->pt_page_size.cy;
            break;

        case PRT_WORDBREAK :
            property.flag = pjob->bWordBreak;
            break;

        case PRT_SHOWPROGRESS :
            property.flag = pjob->bProgress;
            break;

        case PRT_PRINTERNUM :
            property.numeric = ( ULONG)pPrtList.prt_count;
            break;

        case PRT_XPOS :
            property.numeric = PrtXPos( pjob);
            break;

        case PRT_YPOS :
            property.numeric = PrtYPos( pjob);
            break;
            
        default :
            *error = PRTGR_ERR_INV_PROP;
            break;
        
        } // end of switch prop

    return( property);
        
    } // end of PrtGGet()

//
// **********************************************************************
 
LONG APIENTRY PrtGStringLength( HGRPRT hp,
                                PSZ    szFont,
                                ULONG  points,
                                PSZ    szString)
 
// **********************************************************************
// 
// Description : Check if the block will fit on the page
// 
// Function    : 
// 
// Return      :
// 
// **********************************************************************
 
    { 
    PJOB_TYPE       pjob;
    LONG            len = -1L;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return len;

    if( szString == NULL)
        return len;

    if ( !pjob->bPrinting)
        return len;

    /***** Check if font is set up **************************************/

    if( !PrtSetFont( pjob, szFont))
        return len;
    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    len = PrtStringLength( pjob, szString);

    return len;

    } // end of PrtGStringLength()

//
// **********************************************************************
 
BOOL APIENTRY PrtGBlockFits( HGRPRT hp,
                             PSZ    szFont,
                             ULONG  points,
                             PSZ    szString)
 
// **********************************************************************
// 
// Description : Check if the block will fit on the page
// 
// Function    : 
// 
// Return      :
// 
// **********************************************************************
 
    { 
    PJOB_TYPE       pjob;
    BOOL            ok = FALSE;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return ok;

    if( szString == NULL)
        return ok;

    if ( !pjob->bPrinting)
        return ok;

    /***** Check if font is set up **************************************/

    if( !PrtSetFont( pjob, szFont))
        return ok;
    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    ok = PrtCheckFits( pjob, szString);

    return ok;

    } // end of PrtGBlockFits()

//
// **********************************************************************
 
BOOL APIENTRY PrtGLineFits( HGRPRT  hp,
                            PSZ    szFont,
                            ULONG  points,
                            PSZ    szString)
 
// **********************************************************************
// 
// Description : Check if the block will fit on the line
// 
// Function    : 
// 
// Return      :
// 
// **********************************************************************
 
    { 
    PJOB_TYPE       pjob;
    BOOL            ok = FALSE;

    /***** Get printer handle *******************************************/
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return ok;

    if( szString == NULL)
        return ok;

    if ( !pjob->bPrinting)
        return ok;

    /***** Check if font is set up **************************************/

    if( !PrtSetFont( pjob, szFont))
        return ok;

    PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);
    
    ok = PrtLineFits( pjob, szString);

    return ok;
    
    } // end of PrtGLineFits()

//
// **********************************************************************
 
USHORT APIENTRY PrtGPrintFile( HGRPRT   hp,
                               PSZ      szFont,
                               ULONG    points,
                               USHORT   style,
                               PSZ      szFile)
 
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
    PJOB_TYPE   pjob;
    PSZ         pszBuffer;
    SHORT       idx;
    BOOL        bFont = FALSE;
    BOOL        bPoint = FALSE;
    HFILE       hf;
    
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if( szFile == NULL)
        return PRTGR_ERR_PARAMETER;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    if( szFont)
        if( strlen( szFont))
            bFont = TRUE;

    if( points > 0)
        bPoint = TRUE;

    TST_TRACE(( "PrtGPrintFile - %lupt %s on %p ('%s')", points, szFont, pjob, szFile))

    /***** Check if font is set up **************************************/

    if( bFont)
        if( !PrtSetFont( pjob, szFont))
            return PRTGR_ERR_INV_FONT;
    if( bPoint)
        PrtSetFontSize( pjob, pjob->pdata->pt_font_idx, points);

    TST_TRACE(( "PrintFle: %s in %lu.%s in style %c", szFile, points, szFont, style))
    hf = FileReset( szFile);
    TST_TRACE(( "PrintFile: opened file (%lu)", hf))

    if ( !hf)
        return PRTGR_ERR_INV_FILENAME;

    pszBuffer = ( PSZ) malloc( 8092);
    strcpy( pszBuffer, "");
    TST_TRACE(( "PrintFle: created buffer %p", pszBuffer))
    
    while ( !FileReadLn( hf, pszBuffer))
        {
        TST_TRACE(( "PrintFle: Read %s", pszBuffer))

        switch ( style)
            {
            case PRT_CENTER :
                PrtCentre( pjob, pszBuffer);
                break;
            
            case PRT_JUSTIFIED :
                PrtWrite( pjob, pszBuffer, JUST_JUSTIFY);
                break;
            
            case PRT_RIGHT :
                PrtJustRight( pjob, pszBuffer);
                break;
            
            case PRT_LEFT :
            default :
                PrtWriteln( pjob, pszBuffer);
                break;
            
            } /* end of switch style */
        
        } /* end of while */
    
    DosClose( hf);
    
    FREE( pszBuffer);
        
    return PRTGR_OK;
    
    } // end of PrtGPrintFile()

//
// **********************************************************************
 
USHORT APIENTRY PrtGPrintWinImage( HGRPRT  hp,
                                   HWND    hwnd,
                                   ULONG   xl,
                                   ULONG   yb,
                                   ULONG   xr,
                                   ULONG   yt,
                                   ULONG   th,
                                   LONG    llc,
                                   PSZ     title)
 
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
    PJOB_TYPE   pjob;
    POINTL      bl,
                tr,
                ptlhere;
                
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    GpiQueryCurrentPosition( pjob->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    
    if( xl > 0)
        bl.x = (xl * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yb > 0)
        bl.y = (yb * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    
    if( xr > 0)
        tr.x = (xr * pjob->unit_conv) + pjob->pdata->pt_lmargin;
        
    if( yt > 0)
        tr.y = (yt * pjob->unit_conv) + pjob->pdata->pt_bl_offset.cy;
    
    if( !PrtDrawWindow( pjob, hwnd, bl, tr, th, llc, title))
        return PRTGR_ERR_PARAMETER;

    return PRTGR_OK;
    
    } // end of PrtGPrintWinImage()

//
// **********************************************************************
 
USHORT APIENTRY PrtGMoveX( HGRPRT  hp,
                           LONG    delta,
                           BOOL    points)
 
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
    PJOB_TYPE   pjob;
                
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    PrtMoveX( pjob, delta, points);
    
    return PRTGR_OK;
    
    } // end of PrtGMoveX()

//
// **********************************************************************
 
USHORT APIENTRY PrtGMoveY( HGRPRT  hp,
                           LONG    delta,
                           BOOL    points)
 
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
    PJOB_TYPE   pjob;
                
    pjob = ( PJOB_TYPE) hp;
    
    if ( pjob == NULL )
        return PRTGR_ERR_INV_HANDLE;

    if ( !pjob->bPrinting)
        return PRTGR_ERR_NO_JOB;

    PrtMoveY( pjob, delta, points);
    
    return PRTGR_OK;
    
    } // end of PrtGMoveY()


// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
