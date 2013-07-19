// ***********************************************************************
//
// $Author$
// $Workfile$
// $Revision$
// $Date$
//
// $Log$
//
// ***********************************************************************

#ifndef PRTGRAPH_H
#define PRTGRAPH_H


#define     MSR_METRIC              "Metric"
#define     MSR_INCH                "Inch"

// **********************************************************************
// Error return Constants
// **********************************************************************

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

// **********************************************************************
// Fill Styles
// **********************************************************************

#define     FILL_NONE                   0L  /* No fill for box */
#define     FILL_FULL                   1L  /* full fill for box */
#define     FILL_90                     2L  /* 90% tone fill for box */
#define     FILL_80                     3L  /* 80% fill for box */
#define     FILL_75                     4L  /* 75% fill for box */
#define     FILL_70                     5L  /* 70% fill for box */
#define     FILL_60                     6L  /* 60% fill for box */
#define     FILL_HALF                   7L  /* Half tone fill for box */
#define     FILL_LIGHT                  8L  /* Light tone fill for box */
#define     FILL_VERT                   9L  /* Vertical line fill for box */
#define     FILL_HORIZ                  10L /* Horizontal line fill for box */
#define     FILL_DIAGR45                11L /* 45ø Diagonal left to right line fill for box */
#define     FILL_DIAGR33                12L /* 33ø Diagonal left to right line fill for box */
#define     FILL_DIAGL45                13L /* 45ø Diagonal right to left line fill for box */
#define     FILL_DIAGL33                14L /* 33ø Diagonal right to left line fill for box */

LONG    ColorToIndex( PSZ);

typedef LHANDLE   HGRPRT;

typedef VOID (APIENTRY FNNP)(HGRPRT, USHORT, BOOL);
typedef FNNP *PFNNP;


#endif

// ***********************************************************************
//
//                              END OF FILE.
//
// ***********************************************************************


