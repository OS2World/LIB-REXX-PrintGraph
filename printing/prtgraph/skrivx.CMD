/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
address CMD
trace off
"@ECHO OFF"

parse upper source . . cmd_id .
cmd_drive = filespec(Drive,cmd_id)
cmd_path  = filespec(Path,cmd_id)
cmd_id    = filespec(Name,cmd_id)
parse var cmd_id cmd_name "." cmd_extent .

/*------------------------------------------------------------------------*/
/* Setter opp noen variabler                                              */
/*------------------------------------------------------------------------*/
print_start    = 1

minprinter = "HP DeskJ"
/*
minprinter     = "RP79901C"
*/

/*
bilde_fil = "G:\Work\BruktBil\810\BD00068.Bmp"
bilde_fil = "W:\tstngn\exes\add24.bmp"
*/
bilde_fil = "X:\BD00068.Bmp"


call Init_printer                      /*  ...     printer                */

/*------------------------------------------------------------------------*/
/* Stor ramme rundt det hele                                              */
/*------------------------------------------------------------------------*/
/*
call PrtGRxPrintBox printer,0,0,170,258,28,2,"Blue","White"
call PrtGRxPrintBox printer,1,1,169,257,28,2,"Blue","White"
*/
/*------------------------------------------------------------------------*/
/* Bildet                                                                 */
/*-----------------------------------------LLx LLy URx URy----------------*/
/*                               LLx,LLy,URx,URY                          */
/*
call PrtGRxPrintBox      printer,003,088,167,207,28,5,"Red","White"


call PrtGRxPrintBitMap   printer,bilde_fil,004,089,166,206,28,""
*/
rcd = PrtGRxPrintBitMap( printer,bilde_fil,004,089,166,206,28,"");

call log "print bitmap ->" rcd
/**/
if rcd == 0 then
/**/
    call PrtGRxAbortPrintjob printer
/**/
else
    call PrtGRxClosePrintjob printer
/**/
Avslutt:

if print_start = 1 then
   do
      call Log "Avslutter print..."
      call prtgrxterm printer
      call prtgrxdropfuncs
      print_start = 0
   end

call Log "Avslutter..."

exit 0


Init_printer:
/*------------------------------------------------------------------------*/
/* Setter opp printeren                                                   */
/* - Load av Rexx DLL                                                     */
/*------------------------------------------------------------------------*/
/* call PrtGRxDropFuncs */
if RxFuncQuery("PrtGRxLoadFuncs") then
   do
      call RxFuncAdd "PrtGRxLoadFuncs","prtgraph","PrtGRxLoadFuncs"
      call PrtGRxLoadFuncs
      call Log "PrtGraph initert..."
   end

/*------------------------------------------------------------------------*/
/* - Initiering av printer                                                */
/*   PM Daemon startes                                                    */
/*------------------------------------------------------------------------*/
printer = PrtGRxInit()                 /* Init og skaff 'printer id'      */

call PrtGRxSet printer, "ColorEnambled", 1

rcd = PrtGRxGet( printer, "ColorEnabled")

call PrtGRxPrinterList printer,"printers."

/*------------------------------------------------------------------------*/
/* Tabellen 'printers.' inneholder alle de definerte skriverene           */
/* Loop runt til vi finner aktuell skriver.                               */
/*                                                                        */
/* N†r/hvis aktuelle skriver finnes, brukes 'PrtGRxSetPrinter' for †      */
/* markere at det er denne skriveren vi skal bruke.                       */
/*------------------------------------------------------------------------*/
/*
printer_funnet = 0
do i=1 to printers.0
   printer_id = strip(substr(printers.i,1,8))
   if printer_id = minprinter then
      do
         printer_funnet = 1
         call PrtGRxSetPrinter printer, i
      end
end
*/
call PrtGRxPrinterDialog printer
if printer_funnet = 0 then
   do
      call log "Aktuell printer '"minprinter"' ikke funnet..."
      exit 12
   end

/* call prtgrxjobproperties printer */
/*------------------------------------------------------------------------*/
/* Printer funnet og initiert...                                          */
/* Set marginer                                                           */
/*------------------------------------------------------------------------*/
venstremarg    = 45                    /* var 25, s† 15, s† 05            */
hoyremarg      = 45
topmarg        = 20
bunnmarg       = 20
rammebredde    = 28
fylltype       = 5
fylltype       = 1
rammefarge     = "Black"
bakgrunnsfarge = "Red"

call PrtGRxSetMargins printer,
                      venstremarg,
                      hoyremarg,
                      topmarg,
                      bunnmarg,
                      rammebredde,
                      fylltype,
                      rammefarge,
                      bakgrunnsfarge

call PrtGRxSet printer,"ShowProgress",0

/*------------------------------------------------------------------------*/
/* prtgrxprinterdialog                                                    */
/* prtgrxjobproperties                                                    */
/* prtgrxsetmargins                                                       */
/* prtgrxsetheadermode                                                    */
/* prtgrxsetheader                                                        */
/* prtgrxsetfooter                                                        */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Printer initiert...                                                    */
/*------------------------------------------------------------------------*/
call PrtGRxSet printer,"LeftMargin",1



call Log "Printer '" || minprinter || "' initert..."


say "TopMargin   :" PrtGRxGet(printer,"TopMargin"),
    "MinTopMar   :" PrtGRxGet(printer,"MinTopMar")

say "BottomMargin:" PrtGRxGet(printer,"BottomMargin"),
    "MinBotMar   :" PrtGRxGet(printer,"MinBotMar")

say "LeftMargin  :" PrtGRxGet(printer,"LeftMargin"),
    "MinLeftMar  :" PrtGRxGet(printer,"MinLeftMar")

say "RightMargin :" PrtGRxGet(printer,"RightMargin"),
    "MinRightMar :" PrtGRxGet(printer,"MinRightMar")

say "PageHeigth  :" PrtGRxGet(printer,"PageHeight"),
    "PageWidth   :" PrtGRxGet(printer,"PageWidht")

/*------------------------------------------------------------------------*/
/* Start opp printer job                                                  */
/*------------------------------------------------------------------------*/
job_id = cmd_id date(o) time()
call PrtGRxOpenPrintJob  printer,job_id,1
print_start = 1

return

/*------------------------------------------------------------------------*/
/* Log rutine                                                             */
/*------------------------------------------------------------------------*/
Log:
Parse arg log_tekst
say cmd_name date(o) time() "-" log_tekst
return
