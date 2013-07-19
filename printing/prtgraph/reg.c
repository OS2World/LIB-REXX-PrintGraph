/***********************************************************************
**
** $Author:   KANIS  $
** $Workfile:   reg.c  $
** $Revision:   1.0  $
** $Date:   28 Sep 1996 13:07:50  $
**
** $Log:   M:\prtgraph\reg.c_v  $
** 
**    Rev 1.0   28 Sep 1996 13:07:50   KANIS
** Change of file extension for new make
** 
***********************************************************************/

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>

#define LONG    unsigned long

void    command_line( void);
int     CheckReg( char *, char *);
int     ReadBuf( char *, char *);

const char  tag1[] = "AAA";

int main( int argc, char *argv[])

    {
    char    *dll_name;
    char    *reg_num;
 
    printf( "Shareware registration utility\n\n");
    printf( "Copyright (c)1996 ADD Consuling\n\n");
    if ( argc < 2)
        {
        printf( "ERROR - Incorrect parameters\n");
        command_line();
        exit( 1);
        } // end of if

    dll_name = argv[ 1];
    reg_num = strupr( argv[ 2]);
    
printf( "dll = %s\nnumber = %s\n", dll_name, reg_num);

    if( ReadBuf( dll_name, reg_num))
        {
        printf( "Your library %s has been registered\n", dll_name);
        exit( 0);
        }
    else
        {
        printf( "Failed to register library %s\n", dll_name);
        exit( 1);
        }
    return 0;
    }

void command_line()
    {
    printf( "\n");
    printf( "USAGE:\n");
    printf( "\treg <dll name> <registration number>\n");
    printf( "\n");
    printf( "where:\n");
    printf( "\tdll name = VRPRINT.DLL | PRTGRAPH.DLL | PRTGRAFC.DLL | PRTGRCPP.DLL\n");
    printf( "\tregistration number = The number you received to register the shareware\n");
    printf( "\n");
    }

int CheckReg( char *rn, char *cn)
    {
    int         cnt;
    if( strlen( rn) != 19)
        return 0;
    for ( cnt = 0; cnt < 4; cnt++)
        {
        if( !strchr( rn, (int)cn[ cnt]))
            return 0;
        } // end of for
     
    return 1;
    }

int ReadBuf( char *fn, char *rn)

    {
    char    *buf,
            *num,
            *p;
    FILE    *pf;
    LONG    len, 
            l, pos,
            cnt;
    LONG    flag = 0L;

    if(( pf = fopen( fn, "r+b")) == NULL)
        {
        printf( "ERROR - Failed to open %s\n", fn);
        return 0;
        }
    if( fseek( pf, 0L, SEEK_END))
        {
        printf( "ERROR - Failed to find EOF for %s\n", fn);
        fclose( pf);
        return 0;
        }

    len = ftell( pf);
        
    if( !len)
        {
        printf( "ERROR - File %s has Zero length?!!\n", fn);
        fclose( pf);
        return 0;
        }
    
    buf = ( char *)malloc( len + 1);
    
    if( fseek( pf, 0L, SEEK_SET))
        {
        printf( "ERROR - Failed to find start of %s\n", fn);
        free( buf);
        fclose( pf);
        return 0;
        }
    
    l = fread( buf, sizeof( char), len, pf);
    
    if( l != len)
        {
        printf( "ERROR - Only got %lu bytes from %s (%lu)\n", l, fn, len);
        free( buf);
        fclose( pf);
        return 0;
        }
    
    l = len - 3;
    p = buf;
    for ( cnt = 0; cnt < l; cnt++)
        {
        if( !memcmp( p, "AAA", 3))
            {
            pos = cnt + 8;
            num = (char*)buf + (cnt + 3);
            cnt = l;
            }
        else
            p++;
        } // end of for
    
    if( fseek( pf, pos, SEEK_SET))
        {
        printf( "ERROR - Failed to find pos %lu in %s\n", pos, fn);
        free( buf);
        fclose( pf);
        return 0;
        }

    if ( !CheckReg( rn, num))
        {
        printf( "[%s] - Is not a valid registration number\n", rn);
        free( buf);
        fclose( pf);
        return 0;
        } // end of if
    
    l = fwrite( &flag, sizeof( LONG), 1, pf);
    free( buf);
    fclose( pf);
    
    return l;
    }

/*************************************************************************
**
**  (c)1996 ADD Consulting
**
**  END OF FILE.
**
*************************************************************************/
