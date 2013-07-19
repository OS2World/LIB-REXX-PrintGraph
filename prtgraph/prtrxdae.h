// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   PRTRXDAE.H  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:10:08  $
//
// $Log:   M:\prtgraph\prtrxdae.h_v  $
// 
//    Rev 1.0   04 May 1996 21:10:08   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#ifndef PRT_DAEMON_H
#define PRT_DAEMON_H

#define     ID_WINDOW               2

typedef struct
    {
    char            pszPrTitle[ 128];               // progress dialog Title
    char            pszPrString1[ 128];             // progress dialog display string
    char            pszPrString2[ 128];             // progress dialog display string
    char            pszPrString3[ 128];             // progress dialog display string
    } PROG_DLG_DATA, *PPROG_DLG_DATA;

#endif

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
