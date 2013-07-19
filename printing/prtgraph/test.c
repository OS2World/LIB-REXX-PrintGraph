#include <xpf.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winspool.h>

void main(void)
    {
    ULONG           cbBuf;
    ULONG           cReturned;
    ULONG           cbNeeded;
    ULONG           ulCount;
    ULONG           level = 2L;
    ULONG           i;
    char            *computer_name = NULL;
    PBYTE           pbuffer = NULL;
    PRINTER_INFO_2  *prq;


    EnumPrinters( PRINTER_ENUM_NAME, computer_name, level,
                       pbuffer, 0, &cbNeeded, &cReturned);

    pbuffer = ( PBYTE)malloc( cbNeeded);
    cbBuf = cbNeeded;

    if( EnumPrinters( PRINTER_ENUM_NAME, computer_name, level,
                       pbuffer, cbBuf, &cbNeeded, &ulCount))
            {
            prq = (PRINTER_INFO_2*)pbuffer;

            for ( i = 0; i < ulCount; i++)
                {
                printf( "Printer %d\n", i);
                printf( "pServerName     = %s\n", prq->pServerName);
                printf( "pPrinterName    = %s\n", prq->pPrinterName);
                printf( "pShareName      = %s\n", prq->pShareName);
                printf( "pPortName       = %s\n", prq->pPortName);
                printf( "pDriverName     = %s\n", prq->pDriverName);
                printf( "pPrintProcessor = %s\n", prq->pPrintProcessor);
                printf( "pParameters     = %s\n", prq->pParameters);
                printf( "pComment        = %s\n", prq->pComment);

                printf( "dmDeviceName    = %s\n", prq->pDevMode->dmDeviceName);
                printf( "dmFormName      = %s\n\n", prq->pDevMode->dmFormName);
                prq++;
                }
            }

    free( pbuffer);

    }
