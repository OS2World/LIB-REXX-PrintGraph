// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   VARPOOL.H  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:10:20  $
//
// $Log:   M:\prtgraph\varpool.h_v  $
// 
//    Rev 1.0   04 May 1996 21:10:20   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#ifndef     VARPOOL_DEFINED
    #define     VARPOOL_DEFINED

LONG    StemFetchLong( PSZ, USHORT, PBOOL);
PSZ     StemFetchString( PSZ, USHORT, PBOOL);
BOOL    StemSetValue( PSZ, USHORT, PSZ);
BOOL    StemSetValueLong( PSZ, USHORT, LONG);

#endif

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
