// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   initterm.c  $
// $Revision:   1.1  $
// $Date:   23 Oct 1996 19:18:40  $
//
// $Log:   M:\prtgraph\initterm.c_v  $
// 
//    Rev 1.1   23 Oct 1996 19:18:40   KANIS
// Changed for global dll init with no #ifdefs
// 
//    Rev 1.0   04 May 1996 21:06:22   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#define     INCL_DOS
#define     INCL_DOSMODULEMGR
#define     INCL_DOSPROCESS
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
#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <testngen.h>

#include    "prt_int.h"

extern PRT_LIST pPrtList;

int  _CRT_init( void );
void _CRT_term( void );

ULONG DLLModule = 0;

int __dll_initialize( void )

    {
    char    dlgstr[] = "There are no printers available on this work-station\n"
                       "Aborting DLL load....";

    DosCreateMutexSem( NULL, &pPrtList.hmtx, DC_SEM_SHARED, FALSE);
    PrtGetPrinterList( );
    if ( pPrtList.prt_count == 0)
        {
        WinMessageBox( HWND_DESKTOP, 
                       HWND_DESKTOP, 
                       dlgstr,
                       "SYSTEM - ERROR",
                       0, MB_ERROR | MB_ENTER | MB_SYSTEMMODAL | MB_MOVEABLE);
        return FALSE;       
        } // end of if
    
    return( TRUE );
    
    } // end of __dll_initialize()


int __dll_terminate( void )

    {
    int     cnt;
    
    for ( cnt = 0; cnt < MAX_OPEN_DEVS; cnt++)
        FREE( pPrtList.szPrinterList[ cnt]);
    
    for ( cnt = 0; cnt < MAX_OPEN_DEVS; cnt++)
        {
        FREE( pPrtList.aDevStruct[ cnt].pszLogAddress);
        FREE( pPrtList.aDevStruct[ cnt].pszDriverName);
        FREE( pPrtList.aDevStruct[ cnt].pdriv);
        FREE( pPrtList.aDevStruct[ cnt].pszDataType);
        } /* end of for */

    DosCloseMutexSem( pPrtList.hmtx);

    return( TRUE );
    
    } // end of __dll_terminate()


unsigned long _System _DLL_InitTerm( unsigned long hModule,
                                     unsigned long ulFlag )

    {
    if( ulFlag == 0 )
        {
        if( _CRT_init() == -1 )
            return( FALSE );

        DLLModule = hModule;

        if( !__dll_initialize() )
            return( FALSE );
        }
    else if( ulFlag == 1 )
        {
        __dll_terminate();

        _CRT_term();
        }

    return( TRUE );
    
    } // end of _DLL_InitTerm()

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
