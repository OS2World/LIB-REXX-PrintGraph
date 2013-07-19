;
; Class 'VRPrinter'
;

class VRPrinter VRDescriptiveText
filepath printer
prefix PRT
<passthru>
#include "vrprint.h"
#include "d:\prtgraph\prt_int.h"
#include "d:\prtgraph\prt_dlg.h"
#define  WM_INITCAP  (WM_USER + 10)
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
char        pszColor[ 32];
PJOB_TYPE   hPrt;

<endinstancedata>
<rexxmethods>
ClosePrintJob
DefineTable
EndRow
EndTable
GoTo
JobProperties
PrintJustified
PrintCentered
PrintRight
PrintLeft
PrintLine
PrintBox
PrintBitmap
PrintFile
StartCol
StartRow
StartTable
SetHeader
SetHeaderMode
SetFooter
SetMargins
SetPrinter
PrinterDialog
FontDialog
OpenPrintJob
NewPage
PrinterList
Tab
SetHeaderLineFont
PrintObjectImage
ResetColHeader
ResetHeader
AbortPrintJob
BlockFits
LineFits
SetProgressTexts
MoveX
MoveY
PrintWinImage
LoadResMod
FreeResMod
PrintJPEG
StringLength
GotoX
GotoY
GotoTab
DrawLine
PrintBullet
SaveJobProps
ReadJobProps
<endrexxmethods>
<messages>
WM_INITCAP
<endmessages>
<properties>
LeftMargin read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
RightMargin read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
TopMargin read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
BottomMargin read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
PageWidth read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
PageHeight read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
Printing read-only [type=boolean] [editGroup=] [editEnumValues=] [editType=boolean]
CurrentPrinter read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
CurrentDevice read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
LineSpace [type=whole] [editGroup=] [editEnumValues=] [editType=string]
Version read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
PrintColor create-time saveable [type=cstring] [editGroup=Color] [editEnumValues=] [editType=color]
ColorEnabled create-time saveable [type=boolean] [editGroup=Color] [editEnumValues=] [editType=boolean]
Measures create-time saveable [type=cstring] [editGroup=Style] [editEnumValues=;Metric;Inches] [editType=enumerated type]
PageNum read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
JobName read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
DefaultPrinter read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
MinLeftMar read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
MinRightMar read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
MinTopMar read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
MinBottomMar read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
FormName read-only [type=cstring] [editGroup=] [editEnumValues=] [editType=string]
FormWidth read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
FormHeight read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
WordBreak [type=boolean] [editGroup=] [editEnumValues=] [editType=string]
ShowProgress saveable [type=boolean] [editGroup=Style] [editEnumValues=] [editType=boolean]
XPos read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
YPos read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
XposTwips read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
YposTwips read-only [type=whole] [editGroup=] [editEnumValues=] [editType=string]
<endproperties>
<classmethods>
vrLocalClassInit [bool] 
vrLocalWindowClassInit [bool] 
somInit [void] 
somUninit [void] 
vrShowHelp [bool] HWND root_frame
<endclassmethods>
<instancemethods>
somInit [void] 
somUninit [void] 
vrLocalCreateWindow [HWND] PBOOL visible
vrStemFetchLong [ULONG] PSZ pszStem, ULONG index, PBOOL pOk
vrStemFetchString [PSZ] PSZ pszStem, ULONG index, PBOOL pOk
vrStemSetValue [BOOL] PSZ pszStem, ULONG index, PSZ pszValue
vrStemSetValueLong [BOOL] PSZ pszStem, ULONG index, ULONG ulValue
<endinstancemethods>
endclass

