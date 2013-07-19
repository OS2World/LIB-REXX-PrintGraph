/***********************************************************************
**
** $Author$
** $Workfile$
** $Revision$
** $Date$
**
** $Log$
** 
***********************************************************************/

/*
 * printer.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\printer.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define     INCL_PM
#define     INCL_DOS
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

#include "vxrexx.h"
#include "vxfuncs.h"
#include    <tstngen.h>

#define VRPrinter_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "printer.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "printer.ph"
#include "vxcdata.h"

extern PSZ VRPrinterPicturePath;

char    tag1[] = "AAA4618";
ULONG   demo = 0XFFFFFFFF;
BOOL    bPM = TRUE;
PSZ     module_name = "VRPRINT";
BOOL    use_hook = FALSE;

extern PRT_LIST        pPrtList;       // List of printer data


/*
 *  VRPrinterInstance_somInit
 */

SOM_Scope void   SOMLINK VRPrinterInstance_somInit(VRPrinter *somSelf)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    
    parent_somInit(somSelf);

    strcpy( _pszColor, "<default>");

    _hPrt = PrtObjectInit( );

    TST_TRACE(( "_somInit: created _hPrt %p", _hPrt))
    
}

/*
 *  VRPrinterInstance_somUninit
 */

SOM_Scope void   SOMLINK VRPrinterInstance_somUninit(VRPrinter *somSelf)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    TST_TRACE(( "_somUninit: Calls PrtObjectDestroy"))
    PrtObjectDestroy( _hPrt);

    parent_somUninit(somSelf);
}

/*
 *  VRPrinterInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRPrinterInstance_vrLocalCreateWindow(VRPrinter *somSelf,
        PBOOL visible)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    HWND            hwnd;

    TST_TRACE(( "_vrLocalCreateWindow: Starts"))

    hwnd = parent_vrLocalCreateWindow(somSelf,visible);

    TST_TRACE(( "parent_vrLocalCreateWindow: created window %lu", hwnd))

    if ( hwnd)
        {
        if( VRQueryRunMode() == VR_DESIGN_MODE)
            WinPostMsg( hwnd, WM_INITCAP, 0, 0);
        else
            {
            _hPrt->hwnd = _vrGetWindowHandle( _vrFindAncestor( somSelf, NULL));
            _hPrt->hab = VRQueryAnchorBlock();
            TST_TRACE(( "VRPrinterInstance_vrLocalCreateWindow: hab = %lu hwnd = %lu", 
                       _hPrt->hab, _hPrt->hwnd))
            }

        } /* end of if */
        
    return ( hwnd);
}

/*
 *  VRPrinterInstance_vrStemFetchLong
 */

SOM_Scope ULONG   SOMLINK VRPrinterInstance_vrStemFetchLong(VRPrinter *somSelf,
        PSZ pszStem,
        ULONG index,
        PBOOL pOk)
{
    RXSTRING        var;
    LONG            flags;
    ULONG           retval = 0L;

    var.strlength = 0;
    var.strptr = NULL;
    *pOk = FALSE;
    
    TST_TRACE(( "vrStemFetchLong: %s%lu ", pszStem, index))
    flags = _vrVPIFetchStem( somSelf, pszStem, index, &var, 0);

    if ( flags == RXSHV_OK)
        *pOk = VRRXStringToULong( &var, &retval);
    
    if( var.strptr)
        DosFreeMem( var.strptr);

    return ( retval);

}

/*
 *  VRPrinterInstance_vrStemFetchString
 */

SOM_Scope PSZ   SOMLINK VRPrinterInstance_vrStemFetchString(VRPrinter *somSelf,
        PSZ pszStem,
        ULONG index,
        PBOOL pOk)
{
    RXSTRING        var;
    LONG            flags;
    PSZ             retstr = NULL;

    var.strlength = 0;
    var.strptr = NULL;
    *pOk = FALSE;
    
    TST_TRACE(( "vrStemFetchString: %s%lu ", pszStem, index))
    flags = _vrVPIFetchStem( somSelf, pszStem, index, &var, 0);
    if ( flags == RXSHV_OK)
        {
        *pOk = TRUE;
        retstr = VRMemAlloc( var.strlength + 1);
        strcpy( retstr, var.strptr);
        }

    if( var.strptr)
        DosFreeMem( var.strptr);

    return ( retstr);
}

/*
 *  VRPrinterInstance_vrStemSetValue
 */

SOM_Scope BOOL   SOMLINK VRPrinterInstance_vrStemSetValue(VRPrinter *somSelf,
        PSZ pszStem,
        ULONG index,
        PSZ pszValue)
{
    RXSTRING        var;
    BOOL            ok = FALSE;
    LONG            flags;

    var.strlength = 0;
    VRCopyResult( pszValue, strlen( pszValue), &var);
    
    flags = _vrVPISetStem( somSelf, pszStem, index, &var, 0);
    if( flags <= RXSHV_NEWV)
        ok = TRUE;

    return ok;
}

/*
 *  VRPrinterInstance_vrStemSetValueLong
 */

SOM_Scope BOOL   SOMLINK VRPrinterInstance_vrStemSetValueLong(VRPrinter *somSelf,
        PSZ pszStem,
        ULONG index,
        ULONG ulValue)
{
    RXSTRING        var;
    BOOL            ok = FALSE;
    LONG            flags;

    if ( !VRULongToRXString( ulValue, &var, TRUE))
        return ok;

    flags = _vrVPISetStem( somSelf, pszStem, index, &var, 0);
    if( flags <= RXSHV_NEWV)
        ok = TRUE;

    return ok;
}


/*
 *  VRPrinterInstance_vrGet_LeftMargin
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_LeftMargin(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_left_margin;
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_RightMargin
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_RightMargin(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_right_margin;
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_TopMargin
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_TopMargin(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_top_margin;
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_BottomMargin
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_BottomMargin(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_bot_margin;
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_PageWidth
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_PageWidth(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_page_size.cx - 
            ( ULONG)( _hPrt->pdata->pt_right_margin + _hPrt->pdata->pt_left_margin);
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_PageHeight
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_PageHeight(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_page_size.cy - 
            ( ULONG)( _hPrt->pdata->pt_top_margin + _hPrt->pdata->pt_bot_margin);
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_Printing
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_Printing(VRPrinter *somSelf,
        BOOL *on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *on = _hPrt->bPrinting;
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_CurrentPrinter
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_CurrentPrinter(VRPrinter *somSelf,
        PSZ *str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    bool            ok = FALSE;

    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    *str = VRMemAlloc( strlen( _hPrt->szPrinter ) + 1 );

    if( *str ){
        strcpy( *str, _hPrt->szPrinter );
        ok = TRUE;
    }

    DosReleaseMutexSem( pPrtList.hmtx);
    return ok;
}

/*
 *  VRPrinterInstance_vrGet_CurrentDevice
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_CurrentDevice(VRPrinter *somSelf,
        PSZ *str)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    bool  ok = FALSE;

    *str = VRMemAlloc( strlen( _hPrt->DevStruct.pszLogAddress ) + 1 );

    if( *str ){
        strcpy( *str, _hPrt->DevStruct.pszLogAddress );
        ok = TRUE;
    }

    return ok;
}

/*
 *  VRPrinterInstance_vrSet_LineSpace
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_LineSpace(VRPrinter *somSelf,
        ULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    if ( val)
        {
        _hPrt->usline_space = ( USHORT)val;
        } /* end of if */
    else
        {
        _hPrt->usline_space = LINE_SPACE;
        } /* end of else */
    
    return TRUE;
}

/*
 *  VRPrinterInstance_vrGet_LineSpace
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_LineSpace(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    *val = _hPrt->usline_space;
    
    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_ClosePrintJob
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_ClosePrintJob(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    if( _hPrt->bPrinting)
        {
        PrtClose( _hPrt);
        VRBooleanToRXString( retstr, TRUE );
        }
    else
        VRBooleanToRXString( retstr, FALSE );
        
    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_DefineTable
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_DefineTable(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    ULONG           i, 
                    j, 
                    k,
                    cols;
    POINTL          ptl;
    BOOL            bRes;
    ULONG           left_mar,
                    wide;
    PSZ             dummy,
                    tstem,
                    cstem;
    char            cstem_cpx[ 256];

    VRBooleanToRXString( retstr, FALSE );

    TST_TRACE(( "DefineTable: made default return value (FALSE)"))

    if ( !_hPrt->bPrinting)
        return TRUE;

    /***** Check Arguments (should be = 3) ******************************/
    
    if (argc != 2)
        return FALSE;
    
    if ( !RXNULLSTRING( argv[ 0]))
        tstem = argv[ 0].strptr;
    else
        return FALSE;

    if ( !RXNULLSTRING( argv[ 1]))
        cstem = argv[ 1].strptr;
    else
        return FALSE;

    if( cstem[ strlen( cstem) - 1] != '.' )
        cstem[ strlen( cstem) ] = '.';

    sprintf( cstem_cpx, "%s0.", cstem);

    TST_TRACE(( "DefineTable: get column data for %s", cstem_cpx))

    cols = _vrStemFetchLong( somSelf, cstem_cpx, 0, &bRes);
    if ( !bRes || !cols)  return TRUE;

    /***** Create table structure ***************************************/
    
    _hPrt->pdata->pt_table = PrtCreateTable( ( int)cols);

    TST_TRACE(( "DefineTable: Created table struct %p", _hPrt->pdata->pt_table))

    TST_TRACE(( "DefineTable: table def - %s column def %s", tstem, cstem))

    k = _vrStemFetchLong( somSelf, tstem, 0, &bRes);
    if ( !bRes || !(( k == 11) || ( k == 17))) goto ERROR_EXIT;
    
    _hPrt->pdata->pt_table->lfill = _vrStemFetchLong( somSelf, tstem, 1, &bRes);
    if ( !bRes) goto ERROR_EXIT;

    _hPrt->pdata->pt_table->lline_type = _vrStemFetchLong( somSelf, tstem, 2, &bRes);
    if ( !bRes) goto ERROR_EXIT;

    _hPrt->pdata->pt_table->bHeader = _vrStemFetchLong( somSelf, tstem, 3, &bRes);
    if ( !bRes)  goto ERROR_EXIT;
    
    if( _hPrt->pdata->pt_table->bHeader)
        {
        _hPrt->pdata->pt_table->lhfill = _vrStemFetchLong( somSelf, tstem, 4, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        _hPrt->pdata->pt_table->lhline_type = _vrStemFetchLong( somSelf, tstem, 5, &bRes);
        if ( !bRes) goto ERROR_EXIT;

        _hPrt->pdata->pt_table->bAllPages = _vrStemFetchLong( somSelf, tstem, 6, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        _hPrt->pdata->pt_table->lpts = _vrStemFetchLong( somSelf, tstem, 7, &bRes);
        if ( !bRes) goto ERROR_EXIT;

        dummy = _vrStemFetchString( somSelf, tstem, 8, &bRes);
        if ( !bRes)  goto ERROR_EXIT;

        strcpy( _hPrt->pdata->pt_table->cFont, dummy);
        VRMemFree( dummy);
        }

    left_mar = _vrStemFetchLong( somSelf, tstem, 9, &bRes) * _hPrt->unit_conv;
    if ( !bRes)  goto ERROR_EXIT;

    _hPrt->pdata->pt_table->boxtype = ( USHORT)_vrStemFetchLong( somSelf, tstem, 10, &bRes);
    if ( !bRes)  goto ERROR_EXIT;

    _hPrt->pdata->pt_table->hboxtype = ( USHORT)_vrStemFetchLong( somSelf, tstem, 11, &bRes);
    if ( !bRes)  goto ERROR_EXIT;

    if ( k == 17)
        {
        dummy = _vrStemFetchString( somSelf, tstem, 12, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->ltcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->ltcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
        
        dummy = _vrStemFetchString( somSelf, tstem, 13, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->llcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->llcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
        
        dummy = _vrStemFetchString( somSelf, tstem, 14, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->lfcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->lfcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
        
        dummy = _vrStemFetchString( somSelf, tstem, 15, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->lhtcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->lhtcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
        
        dummy = _vrStemFetchString( somSelf, tstem, 16, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->lhlcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->lhlcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
        
        dummy = _vrStemFetchString( somSelf, tstem, 17, &bRes);
        if ( !bRes)
            _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;
        else if ( dummy)
            {
            _hPrt->pdata->pt_table->lhfcolor = VRColorToIndex( dummy);
            if( _hPrt->pdata->pt_table->lhfcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;
            VRMemFree( dummy);
            } /* end of if */
        else
            _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;

        } /* end of if */
    else
        {
        _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
        _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
        _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
        _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
        _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
        _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;
        } /* end of else */
    

    left_mar += _hPrt->pdata->pt_lmargin;
    
    for ( j = 1; j <= cols; j++)
        {
        i = j - 1;
        sprintf( cstem_cpx, "%s%d.", cstem, j);
        TST_TRACE(( "DefineTable: create columns %lu from %s", i, cstem_cpx))
        wide = _vrStemFetchLong( somSelf, cstem_cpx, 1, &bRes) * _hPrt->unit_conv;
        if ( !bRes)
            {
            TST_TRACE(( "DefineTable: failed to get data from %s1", cstem_cpx))
            goto ERROR_EXIT;
            }
        _hPrt->pdata->pt_table->aCol[ i].llm_box = left_mar;
        left_mar += wide;

        _hPrt->pdata->pt_table->aCol[ i].lrm_box = left_mar;

        dummy = _vrStemFetchString( somSelf, cstem_cpx, 2, &bRes);
        if ( !bRes)
            {
            TST_TRACE(( "DefineTable: failed to get data from %s2", cstem_cpx))
            goto ERROR_EXIT;
            }

        _hPrt->pdata->pt_table->aCol[ i].pszHeader = strdup( dummy);
        TST_TRACE(( "DefineTable: free dummy (%s)", dummy))
        VRMemFree( dummy);
        
        _hPrt->pdata->pt_table->aCol[ i].llm_text = _hPrt->pdata->pt_table->aCol[ i].llm_box + 
                                                    _hPrt->pdata->pt_table->lline_type;
        _hPrt->pdata->pt_table->aCol[ i].lrm_text = _hPrt->pdata->pt_table->aCol[ i].lrm_box - 
                                                    _hPrt->pdata->pt_table->lline_type;

        _hPrt->pdata->pt_table->aCol[ i].lrm_text -= (ONE_MIL * 2);
        _hPrt->pdata->pt_table->aCol[ i].llm_text += (ONE_MIL * 2);

        _hPrt->pdata->pt_table->aCol[ i].uslines = 0;
        _hPrt->pdata->pt_table->aCol[ i].usstart = 0;
        _hPrt->pdata->pt_table->aCol[ i].usnewpage = 0;
        _hPrt->pdata->pt_table->aCol[ i].lpts = _hPrt->pdata->pt_table->lpts;
        _hPrt->pdata->pt_table->aCol[ i].alines = NULL;
        strcpy( _hPrt->pdata->pt_table->aCol[ i].cFont, _hPrt->pdata->pt_table->cFont);
        
        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    _hPrt->pdata->pt_table->ptltr.x = _hPrt->pdata->pt_table->aCol[ _hPrt->pdata->pt_table->usCols-1].lrm_box;
    _hPrt->pdata->pt_table->ptltr.y = ptl.y;
    _hPrt->pdata->pt_table->ly_pos = ptl.y;

    if( _hPrt->pdata->pt_table->bHeader)
        {
        if( PrtWriteTableHeader( _hPrt))    
            VRBooleanToRXString( retstr, TRUE );
        else
            goto ERROR_EXIT;
        }
    else
        VRBooleanToRXString( retstr, TRUE );

    TST_TRACE(( "DefineTable: completed successfully"))

    return TRUE ;

ERROR_EXIT:
    TST_TRACE(( "DefineTable: failed"))
    _hPrt->pdata->pt_table = PrtFreeTable( _hPrt->pdata->pt_table);
    return TRUE;

}

/*
 *  VRPrinterInstance_vrRXMethod_EndRow
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_EndRow(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    USHORT          rc;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    rc = PrtEndRow( _hPrt);
    
    if( rc == PRTGR_OK)
        VRBooleanToRXString( retstr, TRUE );

    TST_TRACE(( "EndRow: returns %u", rc))

    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_EndTable
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_EndTable(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    POINTL          ptl;

    VRBooleanToRXString( retstr, FALSE );

    TST_TRACE(( "EndTable: starts"))

    if ( !_hPrt->bPrinting)
        return TRUE;

    if( _hPrt->pdata->pt_table == NULL)  
        return TRUE ;

    /***** Restore margins for page *************************************/
    
    _hPrt->pdata->pt_tmargin = _hPrt->pdata->pt_table->ptltr.y - (ONE_MIL * 2);

    ptl.x = _hPrt->pdata->pt_lmargin;
    ptl.y = _hPrt->pdata->pt_tmargin;
    GpiSetCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    
    _hPrt->pdata->pt_table = PrtFreeTable( _hPrt->pdata->pt_table);
    
    TST_TRACE(( "EndTable: freed table struct"))

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_GoTo
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_GoTo(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            x, y;
    BOOL            bPoints = FALSE;
    
    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 2)
        return FALSE;
   
    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    if ( RXNULLSTRING( argv[ 1]))
        return TRUE;

    if( argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            bPoints = ( BOOL)atoi( argv[ 2].strptr);
        
    VRRXStringToLong( argv, &x);
    VRRXStringToLong( argv + 1, &y);

    PrtGoto( _hPrt, x, y, bPoints);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_JobProperties
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_JobProperties(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    VRBooleanToRXString( retstr, FALSE );

    DevPostDeviceModes( _hPrt->hab,
                        _hPrt->DevStruct.pdriv,
                        _hPrt->DevStruct.pszDriverName,
                        _hPrt->DevStruct.pdriv->szDeviceName,
                        _hPrt->DevStruct.pszLogAddress,
                        DPDM_POSTJOBPROP);

    PrtQueryQueueInfo( _hPrt);

    VRBooleanToRXString( retstr, TRUE );
    
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintJustified
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintJustified(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            rc;
    
    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( _hPrt->pdata->pt_table != NULL)
        rc = PrtWriteCol( _hPrt, szFont, points, szString, JUST_JUSTIFY);

    else
        {
        if( !PrtSetFont( _hPrt, szFont))
            return TRUE;

        PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
        rc = PrtWrite( _hPrt, szString, JUST_JUSTIFY);
        }

    VRBooleanToRXString( retstr, rc );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintCentered
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintCentered(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            rc;
    
    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    
    /***** Check if font is set up **************************************/
    
    if( _hPrt->pdata->pt_table != NULL)
        rc = PrtWriteCol( _hPrt, szFont, points, szString, JUST_CENTRE);

    else
        {
        if( !PrtSetFont( _hPrt, szFont))
            return TRUE;

        PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
        rc = PrtCentre( _hPrt, szString);
        }

    VRBooleanToRXString( retstr, rc );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintRight
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintRight(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            rc;

    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( _hPrt->pdata->pt_table != NULL)
        rc = PrtWriteCol( _hPrt, szFont, points, szString, JUST_RIGHT);

    else
        {
        if( !PrtSetFont( _hPrt, szFont))
            return TRUE;

        PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
        rc = PrtJustRight( _hPrt, szString);
        }

    VRBooleanToRXString( retstr, rc );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintLeft
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintLeft(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            rc;

    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    
    /***** Check if font is set up **************************************/
    
    if( _hPrt->pdata->pt_table != NULL)
        rc = PrtWriteCol( _hPrt, szFont, points, szString, JUST_LEFT);

    else
        {
        if( !PrtSetFont( _hPrt, szFont))
            return TRUE;

        PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
        rc = PrtWrite( _hPrt, szString, JUST_LEFT);
        }

    VRBooleanToRXString( retstr, rc );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintLine
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintLine(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            rc;

    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( _hPrt->pdata->pt_table != NULL)
        rc = PrtWriteCol( _hPrt, szFont, points, szString, JUST_LEFT);

    else
        {
        if( !PrtSetFont( _hPrt, szFont))
            return TRUE;

        PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
        rc = PrtWriteln( _hPrt, szString);
        }

    VRBooleanToRXString( retstr, rc);
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrintBox
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintBox(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData       *somThis = VRPrinterGetData(somSelf);
    POINTL              bl, tr, ptl;
    LONG                th, fill, llc, lfc;
    USHORT              bt;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    if (argc < 5)
        return FALSE;
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    
    if ( !RXNULLSTRING( argv[ 0]))
        bl.x = (atol( argv[ 0].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    else
        bl.x = ptl.x;

    if ( !RXNULLSTRING( argv[ 1]))
        bl.y = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;
    else
        bl.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 2]))
        tr.x = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    else
        tr.x = _hPrt->pdata->pt_rmargin;

    if ( !RXNULLSTRING( argv[ 3]))
        tr.y = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;
    else
        tr.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 4]))
        th = atol( argv[ 4].strptr);
    else
        th = 28;

    if (argc > 5)
        if ( !RXNULLSTRING( argv[ 5]))
            fill = atol( argv[ 5].strptr);
        else
            fill = 0;
    else
        fill = 0;

    if (argc > 6)
        if ( !RXNULLSTRING( argv[ 6]))
            {
            llc = VRColorToIndex( argv[ 6].strptr);
            if( llc == CLR_NOINDEX)
                llc = _hPrt->lColor;
            }
        else
            llc = _hPrt->lColor;
    else
        llc = _hPrt->lColor;

    if (argc > 7)
        if ( !RXNULLSTRING( argv[ 7]))
            {
            lfc = VRColorToIndex( argv[ 7].strptr);
            if( lfc == CLR_NOINDEX)
                lfc = _hPrt->lColor;
            }
        else
            lfc = _hPrt->lColor;
    else
        lfc = _hPrt->lColor;

    if( argc > 8)
        {
        if ( !RXNULLSTRING( argv[ 8]))
            {
            bt = ( USHORT)atoi( argv[ 8].strptr);
            }
        else
            bt = BOX_ALL;
        }
    else
        bt = BOX_ALL;

    PrtBox( _hPrt, bl, tr, th, fill, bt, llc, lfc);

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_PrintBitmap
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintBitmap(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    POINTL          bl, tr, ptlhere;
    LONG            th,
                    llc;
    ULONG           res;
    HMODULE         hmod = NULLHANDLE;
    PSZ             file_name, 
                    p,
                    title = NULL;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    if (argc < 1)
        return FALSE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;
    
    file_name = argv[ 0].strptr;
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = _hPrt->lColor;
    
    if(( argc > 1) && !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    
    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        {
        llc = VRColorToIndex( argv[ 6].strptr);
        if( llc == CLR_NOINDEX)
            llc = _hPrt->lColor;
        }

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        title = argv[ 7].strptr;

    if(( p = strchr( file_name, ( int)'$')) != NULL)
        {
        *p = '\0';
        p++;
        res = atol( p);
        if( strlen( file_name))
            hmod = ( HMODULE)atol( file_name);

        if ( !PrtDrawBitMap2( _hPrt, hmod, res, bl, tr, th, llc, title))
            VRBooleanToRXString( retstr, TRUE );
        }
    else
        {
        if ( !PrtDrawBitMap( _hPrt, file_name, bl, tr, th, llc, title))
            VRBooleanToRXString( retstr, TRUE );
        }

    return TRUE;

}

/*
 *  VRPrinterInstance_vrRXMethod_PrintFile
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintFile(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szFile,
                    pszBuffer,
                    szFont;
    LONG            points;
    char            cStyle;
    HFILE           hf;

    VRBooleanToRXString( retstr, FALSE );
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 4)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the printing style ***************************************/
    
    if( !RXNULLSTRING( argv[ 2]))
        cStyle = *argv[ 2].strptr;
    else
        cStyle = 'L';

    /***** Get the file to print ****************************************/
    
    szFile = argv[ 3].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( _hPrt, szFont))
        return TRUE;

    PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);

    TST_TRACE(( "PrintFle: %s in %lu.%s in style %c", szFile, points, szFont, cStyle))
    hf = FileReset( szFile);
    TST_TRACE(( "PrintFle: opened file (%lu)", hf))

    if ( !hf) return TRUE;

    pszBuffer = ( PSZ) VRMemAlloc( 8092);
    strcpy( pszBuffer, "");
    TST_TRACE(( "PrintFle: created buffer %p", pszBuffer))
    
    while ( !FileReadLn( hf, pszBuffer))
        {
        TST_TRACE(( "PrintFle: Read %s", pszBuffer))

        switch ( cStyle)
            {
            case 'C' :
                PrtCentre( _hPrt, pszBuffer);
                break;
            
            case 'J' :
                PrtWrite( _hPrt, pszBuffer, JUST_JUSTIFY);
                break;
            
            case 'R' :
                PrtJustRight( _hPrt, pszBuffer);
                break;
            
            default :
                PrtWriteln( _hPrt, pszBuffer);
                break;
            
            } /* end of switch cStyle */
        
        } /* end of while */
    
    DosClose( hf);
    
    VRMemFree( pszBuffer);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_StartCol
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_StartCol(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    USHORT          uscol;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if ( argc != 1)
        return FALSE;
    
    uscol = ( USHORT) atoi( argv[ 0].strptr);

    if(uscol > _hPrt->pdata->pt_table->usCols)
        return TRUE;

    _hPrt->pdata->pt_col = uscol - 1;

    TST_TRACE(( "StartCol: set current column to %u", _hPrt->pdata->pt_col))

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_StartRow
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_StartRow(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);

    VRBooleanToRXString( retstr, FALSE );
    if ( !_hPrt->bPrinting)
        return( TRUE);

    _hPrt->pdata->pt_tmargin = _hPrt->pdata->pt_table->ly_pos;

    PrtFreeCells( _hPrt->pdata->pt_table);

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_StartTable
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_StartTable(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    int             i, j, k;
    ULONG           left_mar,
                    wide;
    POINTL          ptl;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be >= 5) *****************************/
    
    if (argc < 5)
        return FALSE;
    
    /***** Create table structure ***************************************/
    
    if ( !RXNULLSTRING( argv[ 2]))
        {
        j = atoi( argv[ 2].strptr);
        _hPrt->pdata->pt_table = PrtCreateTable( j);
        }
    else
        return TRUE;

    if ( !RXNULLSTRING( argv[ 0]))
        _hPrt->pdata->pt_table->lfill = atol( argv[ 0].strptr);
    else
        _hPrt->pdata->pt_table->lfill = 0;

    if ( !RXNULLSTRING( argv[ 1]))
        _hPrt->pdata->pt_table->lline_type = atol( argv[ 1].strptr);
    else
        _hPrt->pdata->pt_table->lline_type = 0;

    if( _hPrt->pdata->pt_table->lline_type > 0)
        _hPrt->pdata->pt_table->boxtype = BOX_ALL;
    _hPrt->pdata->pt_table->hboxtype = 0;

    if ( RXNULLSTRING( argv[ 3]))
        left_mar = 0L;
    else
        left_mar = atol( argv[ 3].strptr) * _hPrt->unit_conv;

    left_mar += _hPrt->pdata->pt_lmargin;
    
    /***** Get column definitions ***************************************/
    
    if( argc != ( j + 4))
        {
        _hPrt->pdata->pt_table = PrtFreeTable( _hPrt->pdata->pt_table);
        return TRUE;
        }

    i = 4;  /* argument counter */

    for( k = 0; k < j; k++)
        {
        
        TST_TRACE(( "StartTable: create column entry %d", k))

        /***** No empty args allowed ************************************/
        
        if ( RXNULLSTRING( argv[ i]))
            {
            _hPrt->pdata->pt_table = PrtFreeTable( _hPrt->pdata->pt_table);
            return TRUE;
            }
        
        wide = atol( argv[ i].strptr) * _hPrt->unit_conv;
        
        /***** Get left margin for column *******************************/
        
        _hPrt->pdata->pt_table->aCol[ k].llm_box = left_mar;

        left_mar += wide;
        
        /***** Calc right margin for column *****************************/
        
        _hPrt->pdata->pt_table->aCol[ k].lrm_box = left_mar;
        
        /***** Calculate text margins ***********************************/
        
        _hPrt->pdata->pt_table->aCol[ k].llm_text = _hPrt->pdata->pt_table->aCol[ k].llm_box + 
                                                    _hPrt->pdata->pt_table->lline_type;
        _hPrt->pdata->pt_table->aCol[ k].lrm_text = _hPrt->pdata->pt_table->aCol[ k].lrm_box - 
                                                    _hPrt->pdata->pt_table->lline_type;
 
        _hPrt->pdata->pt_table->aCol[ k].lrm_text -= (ONE_MIL * 2);
        _hPrt->pdata->pt_table->aCol[ k].llm_text += (ONE_MIL * 2);

        _hPrt->pdata->pt_table->aCol[ k].uslines = 0;
        _hPrt->pdata->pt_table->aCol[ k].usstart = 0;
        _hPrt->pdata->pt_table->aCol[ k].usnewpage = 0;
        _hPrt->pdata->pt_table->aCol[ k].lpts = 0;
        _hPrt->pdata->pt_table->aCol[ k].alines = NULL;
        strcpy( _hPrt->pdata->pt_table->aCol[ k].cFont, "");

        i++;
        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    _hPrt->pdata->pt_table->ptltr.x = _hPrt->pdata->pt_table->aCol[ _hPrt->pdata->pt_table->usCols-1].lrm_box;
    _hPrt->pdata->pt_table->ptltr.y = ptl.y;
    _hPrt->pdata->pt_table->ly_pos = ptl.y;
    _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;

    VRBooleanToRXString( retstr, TRUE );
    TST_TRACE(( "StartTable: completed successfully"))
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_SetHeader
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetHeader(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            cnt;
    USHORT          lines;

    VRBooleanToRXString( retstr, FALSE );

    /***** Check Arguments (should be > 2) ******************************/
    
    if (argc < 1)
        return FALSE;

    if( _hPrt->bPrinting)
        return TRUE;

    if( !_hPrt->pdata->pt_header)
        return TRUE;

    lines = ( USHORT)atoi( argv[ 0].strptr);
    
    if ( argc < ( lines + 1))
        return TRUE;

    PrtInitHeader( _hPrt, lines);
    
    for ( cnt = 0; cnt < lines; cnt++)
        {
        if ( !RXNULLSTRING( argv[ cnt + 1]))
            _hPrt->pdata->pt_psz[ cnt].pszLine = strdup( argv[ cnt + 1].strptr);
        else            
            _hPrt->pdata->pt_psz[ cnt].pszLine = strdup( "");

        /***** Set the default font *************************************/
        
        strcpy( _hPrt->pdata->pt_psz[ cnt].cfont, _hPrt->pdata->pt_hfont);
        _hPrt->pdata->pt_psz[ cnt].lpts = _hPrt->pdata->pt_hpts;
        
        } /* end of for */
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_SetHeaderMode
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetHeaderMode(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    
    VRBooleanToRXString( retstr, FALSE );

    /***** Check Arguments (should be > 2) ******************************/
    
    if ( argc < 1)
        return FALSE;

    if( _hPrt->bPrinting)
        return TRUE;

    _hPrt->pdata->pt_header = ( BOOL) atol( argv[ 0].strptr);

    if ( _hPrt->pdata->pt_header)
        {
        if( argc > 1)
            {
            if ( !RXNULLSTRING( argv[ 1]))
                strcpy( _hPrt->pdata->pt_hfont, argv[ 1].strptr);
            else
                strcpy( _hPrt->pdata->pt_hfont, "Helvetica Bold");
            }

        if( argc > 2)
            {
            if ( !RXNULLSTRING( argv[ 2]))
                _hPrt->pdata->pt_hpts = atol( argv[ 2].strptr);
            else
                _hPrt->pdata->pt_hpts = 10;
            }

        if( argc > 3)
            {
            if ( !RXNULLSTRING( argv[ 3]))
                _hPrt->pdata->pt_hbox_mode = atol( argv[ 3].strptr);
            else
                _hPrt->pdata->pt_hbox_mode = 0;
            }

        if( argc > 4)
            {
            if ( !RXNULLSTRING( argv[ 4]))
                _hPrt->pdata->pt_hbox_line = atol( argv[ 4].strptr);
            else
                _hPrt->pdata->pt_hbox_line = 28;
            }

        if( argc > 5)
            {
            if ( !RXNULLSTRING( argv[ 5]))
                _hPrt->pdata->pt_allpages = ( BOOL) atol( argv[ 5].strptr);
            else
                _hPrt->pdata->pt_allpages = TRUE;
            }
                
        if( argc > 6)
            {
            if ( !RXNULLSTRING( argv[ 6]))
                {
                _hPrt->pdata->pt_hlcolor = VRColorToIndex( argv[ 6].strptr);
                if( _hPrt->pdata->pt_hlcolor == CLR_NOINDEX)
                    _hPrt->pdata->pt_hlcolor = _hPrt->lColor;
                }
            else
                _hPrt->pdata->pt_hlcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_hlcolor = _hPrt->lColor;
                
        if( argc > 7)
            {
            if ( !RXNULLSTRING( argv[ 7]))
                {
                _hPrt->pdata->pt_hfcolor = VRColorToIndex( argv[ 7].strptr);
                if( _hPrt->pdata->pt_hfcolor == CLR_NOINDEX)
                    _hPrt->pdata->pt_hfcolor = _hPrt->lColor;
                }
            else
                _hPrt->pdata->pt_hfcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_hfcolor = _hPrt->lColor;
                
        if( argc > 8)
            {
            if ( !RXNULLSTRING( argv[ 8]))
                {
                _hPrt->pdata->pt_htcolor = VRColorToIndex( argv[ 8].strptr);
                if( _hPrt->pdata->pt_htcolor == CLR_NOINDEX)
                    _hPrt->pdata->pt_htcolor = _hPrt->lColor;
                }
            else
                _hPrt->pdata->pt_htcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_htcolor = _hPrt->lColor;

        if( argc > 9)
            {
            if ( !RXNULLSTRING( argv[ 9]))
                {
                _hPrt->pdata->pt_boxtype = ( USHORT)atoi( argv[ 9].strptr);
                }
            else
                _hPrt->pdata->pt_boxtype = BOX_ALL;
            }
        else
            _hPrt->pdata->pt_boxtype = BOX_ALL;

        } /* end of if */

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

/*
 *  VRPrinterInstance_vrRXMethod_SetFooter
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetFooter(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);

    VRBooleanToRXString( retstr, FALSE );

    if( argc < 5)
        return FALSE;
        
    if( _hPrt->bPrinting)
        return TRUE;

    if ( !RXNULLSTRING( argv[ 0]))
        strcpy( _hPrt->pdata->pt_ffont, argv[ 0].strptr);
    else
        strcpy( _hPrt->pdata->pt_ffont, "Helvetica");
        
    if ( !RXNULLSTRING( argv[ 1]))
        _hPrt->pdata->pt_fpts = atol( argv[ 1].strptr);
    else
        _hPrt->pdata->pt_fpts = 8;

    if ( !RXNULLSTRING( argv[ 2]))
        _hPrt->pdata->pt_fbox_mode = atol( argv[ 2].strptr);
    else
        _hPrt->pdata->pt_fbox_mode = 0;

    if ( !RXNULLSTRING( argv[ 3]))
        _hPrt->pdata->pt_fbox_line = atol( argv[ 3].strptr);
    else
        _hPrt->pdata->pt_fbox_line = 0;

    if ( !RXNULLSTRING( argv[ 4]))
        strcpy( _hPrt->pdata->pt_footline, argv[ 4].strptr);
    else
        strcpy( _hPrt->pdata->pt_footline, "");
    
    if( argc > 5)
        {
        if ( !RXNULLSTRING( argv[ 5]))
            {
            _hPrt->pdata->pt_flcolor = VRColorToIndex( argv[ 5].strptr);
            if( _hPrt->pdata->pt_flcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_flcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_flcolor = _hPrt->lColor;
        }
    else
        _hPrt->pdata->pt_flcolor = _hPrt->lColor;
                
    if( argc > 6)
        {
        if ( !RXNULLSTRING( argv[ 6]))
            {
            _hPrt->pdata->pt_ffcolor = VRColorToIndex( argv[ 6].strptr);
            if( _hPrt->pdata->pt_ffcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_ffcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_ffcolor = _hPrt->lColor;
        }
    else
        _hPrt->pdata->pt_ffcolor = _hPrt->lColor;
                
    if( argc > 7)
        {
        if ( !RXNULLSTRING( argv[ 7]))
            {
            _hPrt->pdata->pt_ftcolor = VRColorToIndex( argv[ 7].strptr);
            if( _hPrt->pdata->pt_ftcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_ftcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_ftcolor = _hPrt->lColor;
        }
    else
        _hPrt->pdata->pt_ftcolor = _hPrt->lColor;

    if( argc > 8)
        {
        if ( !RXNULLSTRING( argv[ 8]))
            {
            _hPrt->pdata->pt_fboxtype = ( USHORT)atoi( argv[ 8].strptr);
            }
        else
            _hPrt->pdata->pt_fboxtype = BOX_ALL;
        }
    else
        _hPrt->pdata->pt_fboxtype = BOX_ALL;

    _hPrt->pdata->pt_footer = TRUE;

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_SetMargins
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetMargins(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);

    VRBooleanToRXString( retstr, FALSE );

    if( _hPrt->bPrinting)
        return TRUE;

    if (argc > 0)
        if ( !RXNULLSTRING( argv[ 0]))
            _hPrt->pdata->pt_left_margin = (ULONG) atol( argv[ 0].strptr);

    if (argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            _hPrt->pdata->pt_right_margin = (ULONG) atol( argv[ 1].strptr);

    if (argc > 2)
        if ( !RXNULLSTRING( argv[ 2]))
            _hPrt->pdata->pt_top_margin = (ULONG) atol( argv[ 2].strptr);

    if (argc > 3)
        if ( !RXNULLSTRING( argv[ 3]))
            _hPrt->pdata->pt_bot_margin = (ULONG) atol( argv[ 3].strptr);

    if (argc > 4)
        {
        if ( !RXNULLSTRING( argv[ 4]))
            _hPrt->pdata->pt_border = atol( argv[ 4].strptr);
        else
            _hPrt->pdata->pt_border = 0;
        }
    else
        _hPrt->pdata->pt_border = 0;

    if (argc > 5)
        {
        if ( !RXNULLSTRING( argv[ 5]))
            _hPrt->pdata->pt_fill = atol( argv[ 5].strptr);
        else
            _hPrt->pdata->pt_fill = 0;
        }
    else
        _hPrt->pdata->pt_fill = 0;

    if (argc > 6)
        {
        if ( !RXNULLSTRING( argv[ 6]))
            {
            _hPrt->pdata->pt_blcolor = VRColorToIndex( argv[ 6].strptr);
            if( _hPrt->pdata->pt_blcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_blcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_blcolor = _hPrt->lColor;
        }
    else
        _hPrt->pdata->pt_blcolor = _hPrt->lColor;

    if (argc > 7)
        {
        if ( !RXNULLSTRING( argv[ 7]))
            {
            _hPrt->pdata->pt_bfcolor = VRColorToIndex( argv[ 7].strptr);
            if( _hPrt->pdata->pt_bfcolor == CLR_NOINDEX)
                _hPrt->pdata->pt_bfcolor = _hPrt->lColor;
            }
        else
            _hPrt->pdata->pt_bfcolor = _hPrt->lColor;
        }
    else
        _hPrt->pdata->pt_bfcolor = _hPrt->lColor;

    if ( PrtCheckMargins( _hPrt))
        VRBooleanToRXString( retstr, TRUE );
            
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_SetPrinter
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetPrinter(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    int             idx = 0;

    VRBooleanToRXString( retstr, FALSE );

    if (argc < 1)
        return FALSE;
    
    if( !RXNULLSTRING( argv[ 0]))
        idx = atoi( argv[ 0].strptr);
    
    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    if (idx == 0)
        {
        _hPrt->prt_idx = pPrtList.def_prt;
        PrtCreateDevStruct( _hPrt, pPrtList.def_prt);
        strcpy( _hPrt->szPrinter, pPrtList.szPrinterList[ pPrtList.def_prt]);
        }
    else
        {
        _hPrt->prt_idx = idx - 1;
        PrtCreateDevStruct( _hPrt, idx - 1);
        strcpy( _hPrt->szPrinter, pPrtList.szPrinterList[ idx - 1]);
        }
    
    DosReleaseMutexSem( pPrtList.hmtx);
    PrtQueryQueueInfo( _hPrt);
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrinterDialog
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrinterDialog(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             pszBut;
    char            pszStem[ 128];
    ULONG           ulButs;
    BOOL            res;
    
    if ( argc > 0)
        {
        if( !RXNULLSTRING( argv[ 0]))
            strcpy( _hPrt->prt_tit, argv[ 0].strptr);
        else
            strcpy( _hPrt->prt_tit, "Choose Printer");
        }
    else        
        strcpy( _hPrt->prt_tit, "Choose Printer");
    
    if (( argc > 1) && !RXNULLSTRING( argv[ 1]))
        {
        strcpy( pszStem, argv[ 1].strptr);
        
        ulButs = _vrStemFetchLong( somSelf, pszStem, 0, &res);
        if( ( ulButs == 3) && res)
            {
            pszBut = _vrStemFetchString( somSelf, pszStem, 1, &res);
            if( res && pszBut)
                strcpy( _hPrt->acDlgBut1, pszBut);
            if( pszBut)
                VRMemFree( pszBut);

            pszBut = _vrStemFetchString( somSelf, pszStem, 2, &res);
            if( res && pszBut)
                strcpy( _hPrt->acDlgBut2, pszBut);
            if( pszBut)
                VRMemFree( pszBut);

            pszBut = _vrStemFetchString( somSelf, pszStem, 3, &res);
            if( res && pszBut)
                strcpy( _hPrt->acDlgBut3, pszBut);
            if( pszBut)
                VRMemFree( pszBut);

            } /* end of if */
        
        } /* end of if */
    
    WinDlgBox( HWND_DESKTOP,
               _hPrt->hwnd,
               (PFNWP)PrtPrinterDlgProc,
               _hPrt->hmod,
               PRT_DLG_PRINTERS,
               _hPrt);

    VRCopyResult( _hPrt->szPrtDlgRet, strlen( _hPrt->szPrtDlgRet), retstr);
    PrtQueryQueueInfo( _hPrt);
    return TRUE ;
}

/*
 *  VRPrinterInstance_vrRXMethod_FontDialog
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_FontDialog(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             prt_tit = "Choose Font";
    PSZ             pszFace = "";
    
    if(( argc > 0) && !RXNULLSTRING( argv[ 0]))
        prt_tit = argv[ 0].strptr;

    if(( argc > 1) && !RXNULLSTRING( argv[ 1]))
        pszFace = argv[ 1].strptr;

    PrtChooseFont( _hPrt, prt_tit, pszFace);
 
    VRCopyResult( _hPrt->pszfont, strlen( _hPrt->pszfont), retstr);
    
    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_OpenPrintJob
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_OpenPrintJob(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    USHORT          copies = 1;

    VRBooleanToRXString( retstr, FALSE );
    
    if ( _hPrt->bPrinting)
        {
        char    warning_str[ 256];
        
        if (argc > 0)
            if ( !RXNULLSTRING( argv[ 0]))
                sprintf( warning_str, "Cannot print job \"%s\"\n%s is busy\nJob \"%s\" is still printing", 
                         argv[ 0].strptr, _hPrt->szPrinter, _hPrt->pdata->doc_name);
            else
                sprintf( warning_str, "Cannot print new job\n%s is busy\nJob \"%s\" is still printing", 
                         _hPrt->szPrinter, _hPrt->pdata->doc_name);
        else
            sprintf( warning_str, "Cannot print new job\n%s is busy\nJob \"%s\" is still printing", 
                     _hPrt->szPrinter, _hPrt->pdata->doc_name);
        WinMessageBox( HWND_DESKTOP, 
                       _hPrt->hwnd,
                       warning_str,
                       "VRPrinter - WARNING",
                       0, MB_ERROR | MB_ENTER | MB_MOVEABLE);
        return TRUE;
        } /* end of if */
    
    if ( demo)
        {
        char    demo_str[ 256];
        PSZ     d_str = "This is an unregistered version of\n"
                        "VRPrinter VX-REXX Object v%s\n\n"
                        "This product is shareware and can be "
                        "registered through CompuServe or by "
                        "contacting the address in the "
                        "Programming Guide\n\n"
                        "¸1995-1996 ADD Consulting (CH)";

        sprintf( demo_str, d_str, VER_NUM);
        WinMessageBox( HWND_DESKTOP, 
                       _hPrt->hwnd,
                       demo_str,
                       "VRPrinter - Unregistered Version",
                       0, MB_INFORMATION | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
        
        } /* end of if */
    
    /***** get the job title ********************************************/
    
    if (argc > 0)
        if ( !RXNULLSTRING( argv[ 0]))
            strcpy( _hPrt->pdata->doc_name, argv[ 0].strptr);
        else
            strcpy( _hPrt->pdata->doc_name, "VRPrinter Document");
    else
        strcpy( _hPrt->pdata->doc_name, "VRPrinter Document");
    
    /***** Get the number of copies *************************************/
    
    if( argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            copies = (USHORT) atoi( argv[ 1].strptr);
    
    /***** Open the printer job *****************************************/
    
    if ( !PrtOpen( _hPrt, copies))
        return TRUE;

    /***** Set Header box ***********************************************/
    
    PrtSetHeaderBox( _hPrt);
    
    /***** Set page borders *********************************************/
    
    if ( _hPrt->pdata->pt_border != 0)
        PrtSetBorder( _hPrt);

    PrtMakeTabs( _hPrt);
        
    /***** Start the job ************************************************/

    _hPrt->pdata->pt_page = 0;

    GpiSetColor( _hPrt->pdata->pt_hps, _hPrt->lColor);

    PrtNewPage( _hPrt);
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE;

}

/*
 *  VRPrinterInstance_vrRXMethod_NewPage
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_NewPage(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return TRUE;
    
    if( !_hPrt->pdata->pt_table)
        PrtNewPage( _hPrt);
    else
        _hPrt->pdata->pt_table->bNewPage = TRUE;

    VRBooleanToRXString( retstr, TRUE );

    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_PrinterList
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrinterList(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    char            pStem[ 128];
    BOOL            ok = FALSE,
                    err = FALSE;
    ULONG           i, j;

    VRBooleanToRXString( retstr, ok);

    /***** Check Arguments (should be > 2) ******************************/
    
    if ( argc < 1)
        return FALSE;
    
    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    strcpy( pStem, argv[ 0].strptr);

    PrtGetPrinterList( );
    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    if( strlen( pStem))
        {
        if( _vrStemSetValueLong( somSelf, pStem, 0L, pPrtList.prt_count))
            {
            for ( i = 0; i < pPrtList.prt_count; i++)
                {
                j = i + 1;
                if ( !_vrStemSetValue( somSelf, pStem, j, pPrtList.szPrinterList[ i]))
                    err = TRUE;
                }
            ok = !err;
            }
        }

    DosReleaseMutexSem( pPrtList.hmtx);
    
    VRBooleanToRXString( retstr, ok);
    return TRUE;
}

/*
 *  VRPrinterInstance_vrRXMethod_Tab
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_Tab(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    POINTL          ptl;
    USHORT          i;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Get current position *****************************************/
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    
    /***** Find the nearest tabulator ***********************************/
    
    i = 0;
    while (i < _hPrt->numtabs)
        {
        if ( _hPrt->tabs[ i] > ptl.x)
            {
            ptl.x = _hPrt->tabs[ i];
            i = _hPrt->numtabs;
            } /* end of if */
        else
            i++;
        } /* end of while */
    
    /***** Move to new tabulator ****************************************/

    GpiMove( _hPrt->pdata->pt_hps, &ptl);
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRPrinterClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined 
 * in the .ph file for this class....           
 */


/*
 *  VRPrinterClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRPrinterClass_vrLocalWindowClassInit(M_VRPrinter *somSelf)
{
    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRPrinterClass_somInit
 */

SOM_Scope void   SOMLINK VRPrinterClass_somInit(M_VRPrinter *somSelf)
{
    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRPrinterPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }
}

/*
 *  VRPrinterClass_somUninit
 */

SOM_Scope void   SOMLINK VRPrinterClass_somUninit(M_VRPrinter *somSelf)
{
    parent_somUninit(somSelf);
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

/*
 *  VRPrinterClass_vrShowHelp
 */

SOM_Scope bool   SOMLINK VRPrinterClass_vrShowHelp(M_VRPrinter *somSelf,
        HWND root_frame)
{
    char                loaderror[ CCHMAXPATH];
    char                szArgs[] = { "view\0 VRPRINT.INF VRPrinter object\0"};
    RESULTCODES         rcodes;
    

    DosExecPgm( loaderror, 127L, EXEC_ASYNC, szArgs, NULL, &rcodes, "view.exe");
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_Version
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_Version(VRPrinter *somSelf,
        PSZ *str)
{
    bool            ok = FALSE;

    *str = VRMemAlloc( 10 );

    if( *str ){
        strcpy( *str,  VER_NUM);
        ok = TRUE;
    }

    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_SetHeaderLineFont
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetHeaderLineFont(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    int             index;
    
    VRBooleanToRXString( retstr, FALSE );

    if ( argc == 0)
        return FALSE;

    if( !_hPrt->pdata->pt_header)
        return TRUE;

    if ( RXNULLSTRING( argv[ 0]))
        return FALSE;

    if ( _hPrt->pdata->pt_header && _hPrt->pdata->pt_hlines)
        {
        index = atoi( argv[ 0].strptr);
        if( !index || ( index > _hPrt->pdata->pt_hlines))
            {
            return TRUE;
            }

        index--;
        
        if ( argc > 1)
            if ( !RXNULLSTRING( argv[ 1]))
                strcpy( _hPrt->pdata->pt_psz[ index].cfont, argv[ 1].strptr);
        
        if ( argc > 2)
            if ( !RXNULLSTRING( argv[ 2]))
                _hPrt->pdata->pt_psz[ index].lpts = atol( argv[ 2].strptr);
        
        VRBooleanToRXString( retstr, TRUE );

        if( _hPrt->bPrinting)
            PrtSetHeaderBox( _hPrt);
        }

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrSet_PrintColor
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_PrintColor(VRPrinter *somSelf,
        PSZ str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            lclr;
    BOOL            ok = FALSE;
    
    if ( str)
        {
        lclr = VRColorToIndex( str);
        if ( lclr == CLR_NOINDEX)
            {
            _hPrt->lColor = CLR_DEFAULT;
            strcpy( _pszColor, "<default>");
            } /* end of if */
        else
            {
            _hPrt->lColor = lclr;
            strcpy( _pszColor, str);
            } /* end of else */
        
        if( _hPrt->bPrinting)
            {
            if ( _hPrt->bColor)
                GpiSetColor( _hPrt->pdata->pt_hps, _hPrt->lColor);
            else
                GpiSetColor( _hPrt->pdata->pt_hps, CLR_DEFAULT);
            }

        ok = TRUE;
        } /* end of if */
    
    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_PrintColor
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_PrintColor(VRPrinter *somSelf,
        PSZ *str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    BOOL            ok = FALSE;
    
    *str = ( PSZ)VRMemAlloc( strlen( _pszColor) + 1);
    
    if ( *str)
        {
        strcpy( *str, _pszColor);
        ok = TRUE;
        } /* end of if */
    
    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrSet_ColorEnabled
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_ColorEnabled(VRPrinter *somSelf,
        BOOL on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    _hPrt->bColor = on;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_ColorEnabled
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_ColorEnabled(VRPrinter *somSelf,
        BOOL *on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *on = _hPrt->bColor;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_PrintObjectImage
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintObjectImage(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData       *somThis = VRPrinterGetData(somSelf);
    SOMAny              *object;
    TID                 tid;
    ULONG               qid;
    SWP                 swp;
    HWND                hwnd;
    POINTL              bl, tr,
                        ptlhere;
    LONG                th,
                        llc;
    PSZ                 title = NULL;
    
    TST_TRACE(( "PrintObjectImage (%s)", argv[ 0].strptr))

    VRBooleanToRXString( retstr, FALSE);

    if( argc < 1)
        return( FALSE);

    if ( !_hPrt->bPrinting)
        {
        TST_TRACE(( "PrintObjectImage (%s) Not printing", argv[ 0].strptr))
        return( TRUE);
        }

    _vrGetRexxIds( somSelf, &tid, &qid);
        
    if( !VRRXStringToSOMObject( argv, &object, tid))
        {
        TST_TRACE(( "%s on thread %lu not converted", argv[ 0].strptr, tid))
        return TRUE;
        }

    if( !object)
        {
        TST_TRACE(( "%s on thread %lu returned NULL pointer", argv[ 0].strptr, tid))
        return TRUE;
        }
    
    hwnd = _vrGetOuterWindow( object);
    if ( !hwnd)
        hwnd = _vrGetWindowHandle( object);
    
    if ( !hwnd)
        {
        TST_TRACE(( "%s on thread %lu failed to get window handle", argv[ 0].strptr, tid))
        return TRUE;
        }

    WinQueryWindowPos( hwnd, &swp);
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptlhere);
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = _hPrt->lColor;
    
    if(( argc > 1) && !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    
    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        {
        llc = VRColorToIndex( argv[ 6].strptr);
        if( llc == CLR_NOINDEX)
            llc = _hPrt->lColor;
        }

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        title = argv[ 7].strptr;
        
    TST_TRACE(( "PrintObjectImage: Draw at %ld, %ld, %ld, %ld", bl.x, bl.y, tr.x, tr.y))

    if ( !PrtDrawWindow( _hPrt, hwnd, bl, tr, th, llc, title))
        VRBooleanToRXString( retstr, TRUE);
    
    return TRUE;
    
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrSet_Measures
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_Measures(VRPrinter *somSelf,
        PSZ str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    UCHAR           cM;
    BOOL            ok = FALSE;
    
    if ( str)
        {
        cM = ( UCHAR) toupper( *str);
        if ( cM == 'M')
            {
            _hPrt->bMetric = TRUE;
            strcpy( _hPrt->pszMeasure, MSR_METRIC);
            _hPrt->one_unit = ONE_MIL;
            _hPrt->unit_conv = TWIPS_PER_MIL;
            _hPrt->tab_len = TAB_LEN_MM;
            _hPrt->def_bmar = DEF_BMAR_MM;
            _hPrt->def_tmar = DEF_TMAR_MM;
            _hPrt->def_rmar = DEF_RMAR_MM;
            _hPrt->def_lmar = DEF_LMAR_MM;
            } /* end of if */
        else
            {
            _hPrt->bMetric = FALSE;
            strcpy( _hPrt->pszMeasure, MSR_INCH);
            _hPrt->one_unit = ONE_TENTH;
            _hPrt->unit_conv = TWIPS_PER_TEN;
            _hPrt->tab_len = TAB_LEN_IN;
            _hPrt->def_bmar = DEF_BMAR_IN;
            _hPrt->def_tmar = DEF_TMAR_IN;
            _hPrt->def_rmar = DEF_RMAR_IN;
            _hPrt->def_lmar = DEF_LMAR_IN;
            } /* end of else */
        
        if ( _hPrt->bPrinting)
            PrtMakeTabs( _hPrt);
        
        ok = TRUE;
        } /* end of if */

    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_Measures
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_Measures(VRPrinter *somSelf,
        PSZ *str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    BOOL            ok = FALSE;

    *str = VRMemAlloc( strlen( _hPrt->pszMeasure) + 1);
    if ( *str)
        {
        strcpy( *str, _hPrt->pszMeasure);
        ok = TRUE;
        } /* end of if */
    
    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_ResetColHeader
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_ResetColHeader(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    USHORT          usCol;
    PSZ             string;
    
    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return TRUE;

    if (argc != 2)
        return FALSE;
    
    if( !_hPrt->pdata->pt_table)
        return TRUE;

    if ( !RXNULLSTRING( argv[ 0]))
        usCol = ( USHORT)atoi( argv[ 0].strptr);
    else
        return FALSE;

    if ( RXNULLSTRING( argv[ 1]))
        return FALSE;
    else
        string = argv[ 1].strptr;

    usCol--;
    
    PrtResetColHdr( _hPrt, usCol, string);
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_ResetHeader
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_ResetHeader(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             *strs;
    ULONG           cnt, i;
    
    if( argc < 1)
        return FALSE;


    cnt = argc;
    strs = ( PSZ *) calloc( cnt, sizeof( PSZ));
    for( i = 0; i < cnt; i++)
        strs[ i] = argv[ i].strptr;

    PrtResetHeader( _hPrt, cnt, strs);
    
    FREE( strs)
    
    if( _hPrt->bPrinting)
        PrtSetHeaderBox( _hPrt);

    return TRUE;
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_AbortPrintJob
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_AbortPrintJob(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    VRBooleanToRXString( retstr, FALSE );

    if( !_hPrt->bPrinting)
        return TRUE;
        
    PrtAbort( _hPrt);
    
    VRBooleanToRXString( retstr, TRUE );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_JobName
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_JobName(VRPrinter *somSelf,
        PSZ *str)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    BOOL            ok = FALSE;
    
    *str = ( PSZ) VRMemAlloc( strlen( _hPrt->pdata->doc_name) + 1);
    if ( *str)
        {
        strcpy( *str, _hPrt->pdata->doc_name);
        ok = TRUE;
        } /* end of if */
    
    return ( ok);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_PageNum
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_PageNum(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_page;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_DefaultPrinter
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_DefaultPrinter(VRPrinter *somSelf,
        PSZ *str)
{
    bool            ok = FALSE;

    PrtGetPrinterList( );
    DosRequestMutexSem( pPrtList.hmtx, SEM_INDEFINITE_WAIT);
    *str = VRMemAlloc( strlen( pPrtList.szPrinterList[ pPrtList.def_prt] ) + 1 );

    if( *str ){
        strcpy( *str, pPrtList.szPrinterList[ pPrtList.def_prt] );
        ok = TRUE;
    }

    DosReleaseMutexSem( pPrtList.hmtx);
    return ok;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_BlockFits
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_BlockFits(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            ok = FALSE;

    VRBooleanToRXString( retstr, ok);
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( _hPrt, szFont))
        return TRUE;

    PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
    ok = PrtCheckFits( _hPrt, szString);

    VRBooleanToRXString( retstr, ok);
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrWM_INITCAP
 */

SOM_Scope MRESULT   SOMLINK VRPrinterInstance_vrWM_INITCAP(VRPrinter *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    PSZ             pszTitle;
    
    _vrGet_Caption( somSelf, &pszTitle);
    if( !pszTitle || !strlen( pszTitle))
        _vrSet_Caption( somSelf, "Printer");

    VRMemFree( pszTitle);
    return (MRESULT) 0;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_MinLeftMar
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_MinLeftMar(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_min_lmargin;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_MinRightMar
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_MinRightMar(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_min_rmargin;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_MinTopMar
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_MinTopMar(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_min_tmargin;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_MinBottomMar
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_MinBottomMar(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_min_bmargin;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_FormName
 */

SOM_Scope bool  SOMLINK VRPrinterInstance_vrGet_FormName(VRPrinter *somSelf, 
                                                         PSZ *str)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *str = ( PSZ) VRMemAlloc( strlen( _hPrt->pszForm));
    strcpy( *str, _hPrt->pszForm);                    

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_FormWidth
 */

SOM_Scope bool  SOMLINK VRPrinterInstance_vrGet_FormWidth(VRPrinter *somSelf, 
                                                          PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    
    *val = _hPrt->pdata->pt_page_size.cx;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_FormHeight
 */

SOM_Scope bool  SOMLINK VRPrinterInstance_vrGet_FormHeight(VRPrinter *somSelf, 
                                                           PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = _hPrt->pdata->pt_page_size.cy;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrSet_WordBreak
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_WordBreak(VRPrinter *somSelf,
        BOOL on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    _hPrt->bWordBreak = on;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_WordBreak
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_WordBreak(VRPrinter *somSelf,
        BOOL *on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *on = _hPrt->bWordBreak;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrSet_ShowProgress
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrSet_ShowProgress(VRPrinter *somSelf,
        BOOL on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    _hPrt->bProgress = on;
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_ShowProgress
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_ShowProgress(VRPrinter *somSelf,
        BOOL *on)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *on = _hPrt->bProgress;
    
    return TRUE;
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_SetProgressTexts
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SetProgressTexts(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             pszStem,
                    pszTitle = NULL,
                    pszStr1 = NULL,
                    pszStr2 = NULL,
                    pszStr3 = NULL,
                    pszBut = NULL;
    ULONG           ul;
    BOOL            res;
    
    VRBooleanToRXString( retstr, FALSE);

    if ( argc < 1)
        return FALSE;
    
    pszStem = argv[ 0].strptr;

    ul = _vrStemFetchLong( somSelf, pszStem, 0, &res);
    if( ( ul == 5) && res)
        {
        pszTitle = _vrStemFetchString( somSelf, pszStem, 1, &res);

        pszStr1 = _vrStemFetchString( somSelf, pszStem, 2, &res);

        pszStr2 = _vrStemFetchString( somSelf, pszStem, 3, &res);

        pszStr3 = _vrStemFetchString( somSelf, pszStem, 4, &res);

        pszBut = _vrStemFetchString( somSelf, pszStem, 5, &res);

        PrtSetProgressTexts( _hPrt, pszTitle, pszStr1, pszStr2, pszStr3, pszBut);
        
        if( pszTitle)
            VRMemFree( pszTitle);

        if( pszStr1)
            VRMemFree( pszStr1);

        if( pszStr2)
            VRMemFree( pszStr2);

        if( pszStr3)
            VRMemFree( pszStr3);

        if( pszBut)
            VRMemFree( pszBut);

        } /* end of if */
    else
        return TRUE;

    VRBooleanToRXString( retstr, TRUE);
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_LineFits
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_LineFits(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    BOOL            ok = FALSE;

    VRBooleanToRXString( retstr, ok);
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
        
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( _hPrt, szFont))
        return TRUE;

    PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
    ok = PrtLineFits( _hPrt, szString);

    VRBooleanToRXString( retstr, ok);
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_MoveX
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_MoveX(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            x;
    BOOL            bPoints = FALSE;
    
    VRBooleanToRXString( retstr, FALSE );

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 1)
        return FALSE;
   
    if ( !_hPrt->bPrinting)
        return TRUE;

    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    bPoints = ( BOOL)RXGETLONG( argv[ 1]);
        
    x = atol( argv[ 0].strptr);

    PrtMoveX( _hPrt, x, bPoints);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_MoveY
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_MoveY(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            y;
    BOOL            bPoints = FALSE;
    
    VRBooleanToRXString( retstr, FALSE );

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 1)
        return FALSE;
   
    if ( !_hPrt->bPrinting)
        return TRUE;

    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    bPoints = ( BOOL)RXGETLONG( argv[ 1]);
        
    y = atol( argv[ 0].strptr);

    PrtMoveY( _hPrt, y, bPoints);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_PrintWinImage
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintWinImage(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    SWP             swp;
    HWND            hwnd;
    POINTL          bl, tr,
                    ptlhere;
    LONG            th,
                    llc;
    PSZ             title = NULL;
    
    TST_TRACE(( "PrintWinImage (%s)", argv[ 0].strptr))

    VRBooleanToRXString( retstr, FALSE);

    if( argc < 1)
        return FALSE;

    if ( !_hPrt->bPrinting)
        return( TRUE);

    VRRXStringToWindow( argv, &hwnd);
    
    if ( !hwnd)
        return TRUE;

    WinQueryWindowPos( hwnd, &swp);
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = _hPrt->lColor;
    
    if(( argc > 1) && !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    
    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        {
        llc = VRColorToIndex( argv[ 6].strptr);
        if( llc == CLR_NOINDEX)
            llc = _hPrt->lColor;
        }

    if( argc > 7)
        title = argv[ 7].strptr;
    
    TST_TRACE(( "PrintWinImage: Draw at %ld, %ld, %ld, %ld", bl.x, bl.y, tr.x, tr.y))

    if ( !PrtDrawWindow( _hPrt, hwnd, bl, tr, th, llc, title))
        VRBooleanToRXString( retstr, TRUE);
    
    return TRUE;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_LoadResMod
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_LoadResMod(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    HMODULE         hmod = NULLHANDLE;
    char            load_err[ 256];
    
    VRULongToRXString( ( ULONG)hmod, retstr, FALSE);

    if( argc < 1)
        return( FALSE);

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    if( DosLoadModule( load_err, sizeof( load_err), argv[ 0].strptr, &hmod))
        return TRUE;

    VRULongToRXString( ( ULONG)hmod, retstr, FALSE);

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_FreeResMod
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_FreeResMod(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    HMODULE         hmod;
    
    VRBooleanToRXString( retstr, FALSE);

    if( argc < 1)
        return( FALSE);

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    hmod = ( HMODULE)atol( argv[ 0].strptr);
    if( !DosFreeModule( hmod))
        VRBooleanToRXString( retstr, TRUE);

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_PrintJPEG
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintJPEG(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);

    POINTL          bl, tr, ptlhere;
    LONG            th,
                    llc;
    PSZ             file_name, 
                    title = NULL;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    if (argc < 1)
        return FALSE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;
    
    file_name = argv[ 0].strptr;
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptlhere);
    bl.x = ptlhere.x;
    bl.y = ptlhere.y;
    tr.x = 0;
    tr.y = 0;
    th = 0;
    llc = _hPrt->lColor;
    
    if(( argc > 1) && !RXNULLSTRING( argv[ 1]))
        bl.x = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    
    if(( argc > 2) && !RXNULLSTRING( argv[ 2]))
        bl.y = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 3) && !RXNULLSTRING( argv[ 3]))
        tr.x = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;

    if(( argc > 4) && !RXNULLSTRING( argv[ 4]))
        tr.y = (atol( argv[ 4].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;

    if(( argc > 5) && !RXNULLSTRING( argv[ 5]))
        th = atol( argv[ 5].strptr);

    if(( argc > 6) && !RXNULLSTRING( argv[ 6]))
        {
        llc = VRColorToIndex( argv[ 6].strptr);
        if( llc == CLR_NOINDEX)
            llc = _hPrt->lColor;
        }

    if(( argc > 7) && !RXNULLSTRING( argv[ 7]))
        title = argv[ 7].strptr;

    if ( !PrtDrawJPEG( _hPrt, file_name, bl, tr, th, llc, title))
        VRBooleanToRXString( retstr, TRUE );

    return TRUE;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_XPos
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_XPos(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = PrtXPos( _hPrt);
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_YPos
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_YPos(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);

    *val = PrtYPos( _hPrt);
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_StringLength
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_StringLength(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szFont;
    LONG            points = 0;
    LONG            res = -1L;

    VRLongToRXString( res, retstr, TRUE);
    
    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 3) ********************************/
    
    if (argc != 3)
        return FALSE;
    
    /***** Get the font *************************************************/
    
    szFont = argv[ 0].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 1]);

    /***** Get the string to print **************************************/
    
    szString = argv[ 2].strptr;
    
    /***** Check if font is set up **************************************/
    
    if( !PrtSetFont( _hPrt, szFont))
        return TRUE;

    PrtSetFontSize( _hPrt, _hPrt->pdata->pt_font_idx, points);
    
    res = PrtStringLength( _hPrt, szString);

    VRLongToRXString( res, retstr, TRUE);
    return TRUE ;
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_XposTwips
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_XposTwips(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    
    *val = PrtXPosTwips( _hPrt);
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrGet_YposTwips
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrGet_YposTwips(VRPrinter *somSelf,
        PULONG val)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    
    *val = PrtYPosTwips( _hPrt);
    
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_GotoX
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_GotoX(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            x;
    BOOL            bPoints = FALSE;
    
    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 1)
        return FALSE;
   
    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    if( argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            bPoints = ( BOOL)atoi( argv[ 1].strptr);
        
    VRRXStringToLong( argv, &x);

    PrtGotoX( _hPrt, x, bPoints);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_GotoY
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_GotoY(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            y;
    BOOL            bPoints = FALSE;
    
    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 1)
        return FALSE;
   
    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    if( argc > 1)
        if ( !RXNULLSTRING( argv[ 1]))
            bPoints = ( BOOL)atoi( argv[ 1].strptr);
        
    VRRXStringToLong( argv, &y);

    PrtGotoY( _hPrt, y, bPoints);
        
    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_GotoTab
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_GotoTab(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    LONG            i;
    POINTL          ptl;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    /***** Check Arguments (should be 1) ********************************/
    
    if (argc < 1)
        return FALSE;
   
    if( _hPrt->pdata->pt_table != NULL)
        return TRUE;

    if ( RXNULLSTRING( argv[ 0]))
        return TRUE;

    VRRXStringToLong( argv, &i);

    if( i > _hPrt->numtabs)
        return TRUE;

    /***** Get current position *****************************************/
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    ptl.x = _hPrt->tabs[ i];
    
    /***** Move to new tabulator ****************************************/

    GpiSetCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    GpiMove( _hPrt->pdata->pt_hps, &ptl);
    
    VRBooleanToRXString( retstr, TRUE);
    return TRUE;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_DrawLine
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_DrawLine(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    POINTL          bl, tr, ptl;
    LONG            th, llc, lt;

    VRBooleanToRXString( retstr, FALSE );

    if ( !_hPrt->bPrinting)
        return( TRUE);

    if (argc < 4)
        return FALSE;
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    
    if ( !RXNULLSTRING( argv[ 0]))
        bl.x = (atol( argv[ 0].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    else
        bl.x = ptl.x;

    if ( !RXNULLSTRING( argv[ 1]))
        bl.y = (atol( argv[ 1].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;
    else
        bl.y = ptl.y;

    if ( !RXNULLSTRING( argv[ 2]))
        tr.x = (atol( argv[ 2].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_lmargin;
    else
        tr.x = _hPrt->pdata->pt_rmargin;

    if ( !RXNULLSTRING( argv[ 3]))
        tr.y = (atol( argv[ 3].strptr) * _hPrt->unit_conv) + _hPrt->pdata->pt_bl_offset.cy;
    else
        tr.y = ptl.y;

    if (argc > 4)
        if ( !RXNULLSTRING( argv[ 4]))
            th = atol( argv[ 4].strptr);
        else
            th = 0;
    else
        th = 0;

    if (argc > 5)
        if ( !RXNULLSTRING( argv[ 5]))
            {
            llc = VRColorToIndex( argv[ 5].strptr);
            if( llc == CLR_NOINDEX)
                llc = _hPrt->lColor;
            }
        else
            llc = _hPrt->lColor;
    else
        llc = _hPrt->lColor;

    if (argc > 6)
        if ( !RXNULLSTRING( argv[ 6]))
            {
            lt = atol( argv[ 6].strptr);
            }
        else
            lt = 0;
    else
        lt = 0;

    PrtLine( _hPrt, bl, tr, th, llc, lt);

    VRBooleanToRXString( retstr, TRUE );
    return TRUE ;

}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_PrintBullet
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_PrintBullet(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData *somThis = VRPrinterGetData(somSelf);
    PSZ             szString,
                    szBullet,
                    szFont,
                    szBfont;
    char            justification = 'L';
    LONG            points = 0,
                    bpts = 0,
                    left_mar,
                    wide;
    USHORT          just = JUST_LEFT;
    int             i;
    POINTL          ptl;
    BOOL            rc;

    VRBooleanToRXString( retstr, FALSE );
    
    /***** Check Arguments (should be 9) ********************************/
    
    if (argc != 9)
        return FALSE;

    if ( !_hPrt->bPrinting)
        return TRUE;

    if( _hPrt->pdata->pt_table)
        return TRUE;

    // ***** Get the indent *********************************************
    
    if ( RXNULLSTRING( argv[ 0]))
        left_mar = 0L;
    else
        left_mar = atol( argv[ 0].strptr) * _hPrt->unit_conv;

    // ***** Get the hanging indent *************************************
    
    if ( !RXNULLSTRING( argv[ 1]))
        {
        wide = atol( argv[ 1].strptr) * _hPrt->unit_conv;
        }
    else
        wide = 560;
    
    /***** Get the bullet font ******************************************/
    
    szBfont = argv[ 2].strptr;

    /***** Get the bullet font size *************************************/
    
    bpts = RXGETLONG( argv[ 3]);
    
    /***** Get the bullet char ******************************************/

    szBullet = argv[ 4].strptr;

    /***** Get the font *************************************************/
    
    szFont = argv[ 5].strptr;

    /***** Get the font size ********************************************/
    
    points = RXGETLONG( argv[ 6]);
    
    // ***** Get the justification **************************************

    if ( !RXNULLSTRING( argv[ 7]))
        {
        justification = toupper( argv[ 7].strptr[ 0]);
        }

    /***** Get the string to print **************************************/
    
    szString = argv[ 8].strptr;

    // ***** Create a 2 column table ************************************
    
    _hPrt->pdata->pt_table = PrtCreateTable( 2);

    // ***** with no cells drawn ****************************************
    
    _hPrt->pdata->pt_table->bHeader = FALSE;
    _hPrt->pdata->pt_table->bAllPages = FALSE;
    _hPrt->pdata->pt_table->lfill = 0;
    _hPrt->pdata->pt_table->lline_type = 0;
    _hPrt->pdata->pt_table->hboxtype = 0;
    _hPrt->pdata->pt_table->boxtype = 0;
    
    // ***** Set up the columns *****************************************
    
    left_mar += _hPrt->pdata->pt_lmargin;
    
    _hPrt->pdata->pt_table->aCol[ 0].llm_box = left_mar;
    left_mar += wide;
        
    _hPrt->pdata->pt_table->aCol[ 0].lrm_box = left_mar;
    _hPrt->pdata->pt_table->aCol[ 1].llm_box = left_mar;
    _hPrt->pdata->pt_table->aCol[ 1].lrm_box = _hPrt->pdata->pt_rmargin;

    /***** Calculate text margins ***********************************/

    for( i = 0; i < 2; i++)
        {        
        _hPrt->pdata->pt_table->aCol[ i].llm_text = _hPrt->pdata->pt_table->aCol[ i].llm_box;
        _hPrt->pdata->pt_table->aCol[ i].lrm_text = _hPrt->pdata->pt_table->aCol[ i].lrm_box;
     
        _hPrt->pdata->pt_table->aCol[ i].uslines = 0;
        _hPrt->pdata->pt_table->aCol[ i].usstart = 0;
        _hPrt->pdata->pt_table->aCol[ i].usnewpage = 0;
        _hPrt->pdata->pt_table->aCol[ i].lpts = 0;
        _hPrt->pdata->pt_table->aCol[ i].alines = NULL;
        strcpy( _hPrt->pdata->pt_table->aCol[ i].cFont, "");

        } /* end of for */
    
    /***** Set positioning fields for the table *************************/
    
    GpiQueryCurrentPosition( _hPrt->pdata->pt_hps, &ptl);
    _hPrt->pdata->pt_table->ptltr.x = _hPrt->pdata->pt_table->aCol[ _hPrt->pdata->pt_table->usCols-1].lrm_box;
    _hPrt->pdata->pt_table->ptltr.y = ptl.y;
    _hPrt->pdata->pt_table->ly_pos = ptl.y;
    _hPrt->pdata->pt_table->ltcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->llcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lfcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhtcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhlcolor = _hPrt->lColor;
    _hPrt->pdata->pt_table->lhfcolor = _hPrt->lColor;
    
    // ***** Start the row **********************************************
    
    _hPrt->pdata->pt_tmargin = _hPrt->pdata->pt_table->ly_pos;
    PrtFreeCells( _hPrt->pdata->pt_table);

    // ***** Print the bullet *******************************************
    
    _hPrt->pdata->pt_col = 0;
    PrtWriteCol( _hPrt, szBfont, bpts, szBullet, just);
    
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
    
    _hPrt->pdata->pt_col = 1;
    rc = PrtWriteCol( _hPrt, szFont, points, szString, just);
    
    // ***** End the row ************************************************
    
    PrtEndRow( _hPrt);

    // ***** Free the table *********************************************
    
    _hPrt->pdata->pt_table = PrtFreeTable( _hPrt->pdata->pt_table);

    VRBooleanToRXString( retstr, rc);
    return TRUE ;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_SaveJobProps
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_SaveJobProps(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             AppName,
                    KeyName;
    HINI            prf;
    BOOL            rc = FALSE;
    PDRIVDATA       pdriv = _hPrt->DevStruct.pdriv;
    
    if (argc != 3)
        return FALSE;

    if ( RXNULLSTRING( argv[ 1]) || RXNULLSTRING( argv[ 2]))
        return FALSE;
    
    if ( !RXNULLSTRING( argv[ 0]))
        prf = PrfOpenProfile( _hPrt->hab, argv[ 0].strptr);
    else
        prf = HINI_USERPROFILE;

    AppName = argv[ 1].strptr;
    KeyName = argv[ 2].strptr;

    rc = PrfWriteProfileData( prf, AppName, KeyName, pdriv, pdriv->cb);

    VRBooleanToRXString( retstr, rc);

    if( prf != HINI_USERPROFILE)
        PrfCloseProfile( prf);

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRPrinterInstance_vrRXMethod_ReadJobProps
 */

SOM_Scope bool   SOMLINK VRPrinterInstance_vrRXMethod_ReadJobProps(VRPrinter *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRPrinterData   *somThis = VRPrinterGetData(somSelf);
    PSZ             AppName,
                    KeyName;
    HINI            prf;
    ULONG           rc,
                    datalen;
    PDRIVDATA       pdriv;
    
    if (argc != 3)
        return FALSE;

    if ( RXNULLSTRING( argv[ 1]) || RXNULLSTRING( argv[ 2]))
        return FALSE;
    
    if ( !RXNULLSTRING( argv[ 0]))
        prf = PrfOpenProfile( _hPrt->hab, argv[ 0].strptr);
    else
        prf = HINI_USERPROFILE;

    AppName = argv[ 1].strptr;
    KeyName = argv[ 2].strptr;

    if( PrfQueryProfileSize( prf, AppName, KeyName, &datalen))
        {
        pdriv = ( PDRIVDATA) calloc( 1, datalen);
    
        if( PrfQueryProfileData( prf, AppName, KeyName, pdriv, &datalen))
            {

            if( ( pdriv->cb == _hPrt->DevStruct.pdriv->cb) &&
                !strcmp( pdriv->szDeviceName, _hPrt->DevStruct.pdriv->szDeviceName) &&
                ( pdriv->lVersion == _hPrt->DevStruct.pdriv->lVersion))
                {
                memcpy( _hPrt->DevStruct.pdriv, pdriv, pdriv->cb);
                rc = 0L;
                }
            else
                rc = 1L;
            }
        else
            rc = 2L;
        }
    else
        rc = 3L;

    VRULongToRXString( rc, retstr, TRUE);

    if( prf != HINI_USERPROFILE)
        PrfCloseProfile( prf);

    return TRUE;
}

