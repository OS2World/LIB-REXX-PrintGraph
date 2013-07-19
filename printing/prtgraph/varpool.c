// *********************************************************************
//
// $Author:   KANIS  $
// $Workfile:   VARPOOL.C  $
// $Revision:   1.0  $
// $Date:   04 May 1996 21:09:44  $
//
// $Log:   M:\prtgraph\varpool.c_v  $
// 
//    Rev 1.0   04 May 1996 21:09:44   KANIS
// First VCS store for v2.2
// 
// *********************************************************************

#define INCL_REXXSAA

#include <os2.h>
#include <rexxsaa.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "varpool.h"

/*
*************************************************************************/

PSZ StemFetchString( PSZ    stem, 
                     USHORT count, 
                     PBOOL  pretval )

/************************************************************************
*                                                                       *
* Description : Return string entry from a stem variable.               *
*                                                                       *
*************************************************************************/

    {
    SHVBLOCK    shv;
    PSZ         varbuf,
                retstr;
    USHORT      varlen;

    *pretval = FALSE;
    
    if( !stem ) 
        return NULL;

    /* Convert to uppercase, make sure there's enough room for a ULONG
       value, and add a '.' if necessary */

    varlen = strlen( stem );
    varbuf = alloca( varlen + 12 );

    if( varbuf == NULL ) 
        return NULL;

    strcpy( varbuf, stem );
    strupr( varbuf );

    if( varbuf[ varlen - 1 ] != '.' )
        {
        varbuf[ varlen ] = '.';
        varlen++;
        }

    retstr = ( PSZ)malloc( 512);
    
    /* Convert the index */

    sprintf( &varbuf[ varlen ], "%d", count );

    /* Request the value... */

    shv.shvnext            = NULL;
    shv.shvname.strptr     = varbuf;
    shv.shvname.strlength  = strlen( varbuf );
    shv.shvvalue.strptr    = retstr;
    shv.shvvalue.strlength = 512;
    shv.shvvaluelen        = 512;
    shv.shvcode            = RXSHV_FETCH;

    RexxVariablePool( &shv );

    if( shv.shvret == RXSHV_OK || shv.shvret == RXSHV_TRUNC )
        {
        *pretval = TRUE;
        return( retstr);
        }

    return NULL;

    } /* end of StemFetchString() */

/*
*************************************************************************/

LONG StemFetchLong( PSZ     stem, 
                    USHORT  count, 
                    PBOOL   pretval )

/************************************************************************
*                                                                       *
* Description : Return numeric entry from a stem variable.              *
*                                                                       *
*************************************************************************/

    {
    SHVBLOCK    shv;
    PSZ         varbuf,
                retstr;
    USHORT      varlen;
    LONG        retval;
    
    *pretval = FALSE;
    
    if( !stem ) 
        return 0;

    /* Convert to uppercase, make sure there's enough room for a ULONG
       value, and add a '.' if necessary */

    varlen = strlen( stem );
    varbuf = alloca( varlen + 12 );

    if( varbuf == NULL ) 
        return 0;

    strcpy( varbuf, stem );
    strupr( varbuf );

    if( varbuf[ varlen - 1 ] != '.' )
        {
        varbuf[ varlen ] = '.';
        varlen++;
        }

    /* Convert the index */

    sprintf( &varbuf[ varlen ], "%d", count );
    retstr = ( PSZ) malloc( 32);
    
    /* Request the value... */

    shv.shvnext            = NULL;
    shv.shvname.strptr     = varbuf;
    shv.shvname.strlength  = strlen( varbuf );
    shv.shvvalue.strptr    = retstr;
    shv.shvvalue.strlength = 32;
    shv.shvvaluelen        = 32;
    shv.shvcode            = RXSHV_FETCH;

    RexxVariablePool( &shv );

    if( shv.shvret == RXSHV_OK || shv.shvret == RXSHV_TRUNC )
        {
        *pretval = TRUE;
        retval = atol( shv.shvvalue.strptr);
        free( retstr); 
        return( retval);
        }

    free( retstr); 
    return 0;

    } /* end of StemFetchLong() */

/*
*************************************************************************/

BOOL StemSetValue( PSZ      name, 
                   USHORT   count, 
                   PSZ      value)

/************************************************************************
*                                                                       *
* Description : Set the value of a stem variable in the Var Pool.       *
*                                                                       *
*************************************************************************/

    {
    SHVBLOCK shv;
    PSZ      varname;
    ULONG    len;

    if( !name ) 
        return( FALSE);

    len     = strlen( name );
    varname = alloca( len + 12 );

    if( varname == NULL )
        return( FALSE);

    strcpy( varname, name );
    strupr( varname );

    if( varname[ len - 1 ] != '.' ){
        varname[ len ] = '.';
        len++;
    }

    sprintf( &varname[ len ], "%d", count );

    shv.shvnext            = NULL;
    shv.shvname.strptr     = varname;
    shv.shvname.strlength  = strlen( varname );
    shv.shvvalue.strptr    = value;
    shv.shvvalue.strlength = strlen( value);
    shv.shvvaluelen        = strlen( value);
    shv.shvcode            = RXSHV_SET;

    RexxVariablePool( &shv );

    if( shv.shvret <= RXSHV_NEWV)
        return( TRUE);
    else
        return( FALSE);
    
    } /* end of StemSetValue() */


/*
*************************************************************************/

BOOL StemSetValueLong( PSZ      name, 
                       USHORT   count, 
                       LONG     lvalue)

/************************************************************************
*                                                                       *
* Description : Set the value of a stem variable in the Var Pool.       *
*                                                                       *
*************************************************************************/

    {
    SHVBLOCK shv;
    PSZ      varname,
             value;
    ULONG    len;

    if( !name ) 
        return( FALSE);

    len     = strlen( name );
    varname = alloca( len + 12 );

    if( varname == NULL )
        return( FALSE);

    strcpy( varname, name );
    strupr( varname );

    if( varname[ len - 1 ] != '.' ){
        varname[ len ] = '.';
        len++;
    }

    value = ( PSZ) malloc( 12);
    sprintf( value, "%d", lvalue);
    
    sprintf( &varname[ len ], "%d", count );

    shv.shvnext            = NULL;
    shv.shvname.strptr     = varname;
    shv.shvname.strlength  = strlen( varname );
    shv.shvvalue.strptr    = value;
    shv.shvvalue.strlength = strlen( value);
    shv.shvvaluelen        = strlen( value);
    shv.shvcode            = RXSHV_SET;

    RexxVariablePool( &shv );

    if( shv.shvret <= RXSHV_NEWV)
        return( TRUE);
    else
        return( FALSE);
    
    } /* end of StemSetValueLong() */

// ***********************************************************************
//
//  (c)1996 ADD Consulting
//
//  END OF FILE.
//
// ***********************************************************************
