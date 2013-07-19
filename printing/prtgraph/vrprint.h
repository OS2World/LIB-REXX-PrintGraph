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
#ifndef VRPRINT_INCLUDED
#define VRPRINT_INCLUDED
 

#define     USE_HOOK                FALSE
#define     PFNNP                   PVOID

#define     MOD_NAME                "VRPRINT"

#define     RXGETLONG( r)           ( RXNULLSTRING(r) ? 0L : atol( (r).strptr) )

#define     MSR_METRIC              "Metric"
#define     MSR_INCH                "Inch"

/************************************************************************/
/* Error return Constants                                               */
/************************************************************************/

#define     PRTGR_OK                    0   /* Success */
#define     PRTGR_ERR_INV_HANDLE        1   /* Invalid handle passed to function */
#define     PRTGR_ERR_NO_PRINTER        2   /* No printer has been defined */
#define     PRTGR_ERR_PARAMETER         3   /* Parameter was out of range */
#define     PRTGR_ERR_INV_BITMAP        4   /* Not a valid bitmap */
#define     PRTGR_ERR_INV_FILENAME      5   /* File not found */
#define     PRTGR_ERR_INV_FONT          6   /* Failed to load font */
#define     PRTGR_ERR_JOB_OPEN          7   /* Failed to open job */
#define     PRTGR_ERR_NOT_TABLE         8   /* Col/row func outside of table */
#define     PRTGR_ERR_TABLE_HEADER      9   /* Col/row func outside of table */
#define     FILE_BLK_SIZE_ERR           1000


/************************************************************************/
/* Fill Styles                                                          */
/************************************************************************/

#define     FILL_NONE           ( ULONG)0   /* No fill for box */
#define     FILL_FULL           ( ULONG)1   /* full fill for box */
#define     FILL_90             ( ULONG)2   /* 90% tone fill for box */
#define     FILL_80             ( ULONG)3   /* 80% fill for box */
#define     FILL_75             ( ULONG)4   /* 75% fill for box */
#define     FILL_70             ( ULONG)5   /* 70% fill for box */
#define     FILL_60             ( ULONG)6   /* 60% fill for box */
#define     FILL_HALF           ( ULONG)7   /* Half tone fill for box */
#define     FILL_LIGHT          ( ULONG)8   /* Light tone fill for box */
#define     FILL_VERT           ( ULONG)9   /* Vertical line fill for box */
#define     FILL_HORIZ          ( ULONG)10  /* Horizontal line fill for box */
#define     FILL_DIAGR45        ( ULONG)11  /* 45ø Diagonal left to right line fill for box */
#define     FILL_DIAGR33        ( ULONG)12  /* 33ø Diagonal left to right line fill for box */
#define     FILL_DIAGL45        ( ULONG)13  /* 45ø Diagonal right to left line fill for box */
#define     FILL_DIAGL33        ( ULONG)14  /* 33ø Diagonal right to left line fill for box */

typedef LHANDLE HGRPRT;

#endif

/*************************************************************************
**
**  (c)1996 ADD Consulting
**
**  END OF FILE.
**
*************************************************************************/
