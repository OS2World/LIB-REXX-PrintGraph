.**********************************************************************
.*
.* $Author:   KANIS  $
.* $Workfile:   PRTGRAPH.IPF  $
.* $Revision:   1.0  $
.* $Date:   04 May 1996 21:10:46  $
.*
.* $Log:   M:\prtgraph\prtgraph.ipv  $
.* 
.*    Rev 1.0   04 May 1996 21:10:46   KANIS
.* First VCS store for v2.2
.* 
.**********************************************************************

:userdoc.
:docprof toc=123.
:title.PrtGraph v2.3 REXX Programming Reference

.***** Introduction *****************************************************

:h1 res=100.PrtGraph REXX Library
:i1 id=INTRO.PrtGraph REXX Library
:font facename=Helv size=16x12.

:p.The :hp2.PrtGraph REXX Library:ehp2. gives you access to complex graphic printing functionality 
from command line :hp2.REXX:ehp2. scripts.

:p.With this library you will be able to create professional style reports and outputs for 
your :hp2.REXX:ehp2. programs with images, boxes and text that can be justified, right or 
left aligned or centred. and with documents that use up to 25 different font faces.

:p.The :hp2.PrtGraph REXX Library:ehp2. allows you to define headers and footers and gives you 
access to a list of the printers connected to your work-station, their :hp2.Job 
Properties:ehp2. dialogs and their available printing fonts.

.***** What's New *******************************************************

:h2 res=101.Whats new in version 2.3
:i2 refid=INTRO.Whats new in version 2.3
:font facename=Helv size=16x12.
:p.:hp2.The Daemon is only started for command line REXX, for graphical interface REXX products 
like Gpf REXX and VisPro/REXX the PM Engine for the product is used.:ehp2.
.br
This means that :link reftype=hd res=1070.PrtGRxInit:elink. has been changed.

:p.In version 2.3 we have introduced the following new functions&colon.
:ul compact.
:li.:link reftype=hd res=2088.PrtGRxDrawLine:elink.
:li.:link reftype=hd res=2084.PrtGRxGotoTab:elink.
:li.:link reftype=hd res=2076.PrtGRxGotoX:elink.
:li.:link reftype=hd res=2080.PrtGRxGotoY:elink.
:li.
:li.
:eul.

:p.In version 2.3 we have modified the methods that draw boxes to allow you to define which sides 
are drawn by combining the following flags&colon.
:lm margin=5.
:ul compact.
:li.1  Left edge
:li.2  Right edge
:li.4  Top edge
:li.8  Bottom edge
:li.16 Do NOT draw the far left and far right edges edges of a table
:eul.
:lm margin=1.
:p.This means that the following methods have been modified&colon.
:lm margin=5.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:eul.
:lm margin=1.


.***** Shareware Software ***********************************************

:h2 res=400.Shareware Software
:i2 refid=INTRO.Shareware Software
:font facename=Helv size=16x12.

:p.:hp2.DEFINITION OF SHAREWARE SOFTWARE:ehp2.

:p.Shareware Software distribution gives users a chance to try software before buying it. If 
you try a Shareware software program and continue using it, you are expected to register.  
Individual programs differ on details -- some request registration while others require it, 
some specify a maximum trial period.  With registration, you  get anything from the simple 
right to continue using the software to an updated program with printed manual. 

:p.Copyright laws apply to both Shareware and commercial software, and the copyright holder 
retains all rights, with a few specific exceptions as stated below. Shareware software authors 
are accomplished programmers, just like commercial authors, and the programs are of comparable 
quality. (In both cases, there are good programs and bad ones!)  The main difference is in the 
method of distribution. The author specifically grants the right to copy and distribute the 
software, either to all and sundry or to a specific group. For example, some authors require 
written permission before a commercial disk vendor may copy their Shareware software. 

:p.Shareware software is a distribution method, not a type of software. You should find 
software that suits your needs and pocketbook, whether it's commercial or Shareware software.  
The Shareware software system makes fitting your needs easier, because you can try before you 
buy. And because the overhead is low, prices are low also. Shareware software has the ultimate 
money-back guarantee -- if you don't use the product, you don't pay for it. 

:p.When you :link reftype=hd res=410.register:elink. the :hp2.PrtGraph REXX Library:ehp2. you will be sent a 
registered version of the DLL by e-mail. This version has the "nag" popup removed and you have 
the right to freely distribute software that includes the DLL.

:p.If you are satisfied with the :hp2.PrtGraph REXX Library:ehp2. we ask you to freely distribute the 
shareware version to your freinds and colleagues.

:p.If you have any suggestions for enhancements or find any bugs in the software please 
contact us at one of our :link reftype=hd res=600.Contact Addresses:elink.

.***** Registering  *****************************************************

:h2 res=410.Registering your license
:i2 refid=INTRO.Registering your license
:font facename=Helv size=16x12.

:p.Printer is a "Shareware software program" and is provided at no charge to the user for 
evaluation. Feel free to share it with your friends, but please do not give it away altered or 
as part of another system. The essence of "user-supported" software is to provide personal 
computer users with quality software without high prices, and yet to provide incentive for 
programmers to continue to develop new products. If you find this program useful and find 
that you are using Printer and continue to use Printer after a reasonable trial period 
of 30  days, you must make a registration payment of $45.00 to ADD Consulting (CH).
:p.If you have already registered either PrtGraph Class Library, PrtGraph C Library or 
VRPrinter you can register for $20.00. :p.You can register through the :hp2.CompuServe:ehp2. 
Shareware Registration facility&colon.
:lm margin=5.
:p.GO SWREG registration Number 5602 for new registrations
:p.GO SWREG registration Number 6350 for registered users of another ADD Consulting printing library
:lm margin=1.

:p.The registration fee will license one copy for use on any one computer at any one time. You 
must treat this software just like a book. An example is that this software may be used by 
any number of people and may be freely moved from one computer location to another, so long 
as there is no possibility of it being used at one location while it's being used at another. 
Just as a book cannot be read by two different persons at the same time. 

:p.Payment of the registration fee gives you the right to distribute programs that include 
the object and the DLL without paying any other "run-time" licenses.

:p.Site-License arrangements may be made by :link reftype=hd res=600.contacting:elink. 
ADD Consulting (CH). 

.***** Distributing *****************************************************

:h2 res=420.Distributing the PrtGraph REXX Library
:i2 refid=INTRO.Distributing the PrtGraph REXX Library
:font facename=Helv size=16x12.

:p.Anyone distributing the :hp2.PrtGraph REXX Library:ehp2. for any kind of remuneration must first 
contact ADD Consulting (CH) at our :link reftype=hd res=600.address:elink. below for authorization. 
This authorization will be automatically granted to distributors recognized by the (ASP) as 
adhering to its guidelines for shareware distributors, and such distributors may begin 
offering Printer immediately, however ADD Consulting (CH) should still be advised so that 
the distributor can be kept up-to-date with the latest version of Printer. 

:p.Registered users are free to distribute programs that use the the :hp2.PrtGraph REXX Library:ehp2. with 
no additional run-time fees.

.***** Address **********************************************************

:h2 res=600.Contact Address
:i2 refid=INTRO.Contact Address
:font facename=Helv size=16x12.

:p.You can contact ADD Consulting at the addresses below&colon.
:lm margin=5.
:lines.:font facename=Courier size=18x12.
ADD Consulting (CH)
Mr. Peter Kanis
Via Suro 9
CH-7403 RhÑzÅns
Switzerland

Tel&colon. +41 (0)81 630 2011
Fax&colon. +41 (0)81 630 2015
CompuServe&colon. 100275,350 (Peter Kanis)
INTERNET&colon. kanis@ibm.net

ADD Consulting (RUS)
Mr. Michael V. Schelkin
18-29 Molodezhnaya Street
Jukovsky 
140160 Moscow Region
Russia

Tel&colon. +7 095 556 8533
Internet&colon. michael@schelkin.msk.ru

:elines.:font facename=default.

:h2 res=430.Rights And Limitations
:i2 refid=INTRO.Rights and Limitations
:font facename=Helv size=16x12.

:p.ADD Consulting makes no warranties as to the information in this guide. Additionally, 
ADD Consulting is not responsible or liable for any loss or damage of any kind resulting from 
use of this product. 

:p.The Software is protected by international copyright laws. All rights reserved. No part of 
the computer program, documentation or related files may be reproduced photocopied, stored 
on a retrieval system, or transmitted except as provided by copyright law or by express 
permission of the copyright owner.

:p.DISCLAIMER - AGREEMENT 

:p.Users of the :hp1.PrtGraph REXX Library:ehp1. shall accept this disclaimer of warranty&colon.

:p.ADD CONSULTING SUPPLIES THIS PRODUCT AS IS WITHOUT WARANTY OF ANY KIND, EITHER EXPRESS OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARANTIES OF MERCANTABILITY OR FITNESS FOR 
A PARTICULAR PURPOSE. ADD CONSULTING ASSUMES NO LIABILITY FOR DAMAGES, DIRECT OR CONSEQUENTIAL, 
WHICH MAY RESULT FROM THE USE OF THE PRODUCT.

:p.Some jurisdictions do not allow the exclusion or limitations for consequential or 
incidental damages, so the above may not apply to you.

.***** Demo program *****************************************************

:h2 res=105.The DEMO program
:i2 refid=INTRO.Demo Program
:font facename=Helv size=16x12.

:p.Included in this package is a demonstration program in :hp2.REXX:ehp2..

:p.The demo shows you many of the possibilities offered by the object, but the limits are set 
by your imagination.

.***** Setting up a print job *******************************************

:h2 res=120.Setting up a print job
:i2 refid=INTRO.Setting up a print job
:font facename=Helv size=16x12.

:p.Setting up a print job requires several steps&colon.
:p.Setting up a print job requires several steps&colon.
:lm margin=5.
:ul compact.
:li.Load the functions with :link reftype=hd res=1090.PrtGRxLoadFuncs:elink.
:li.Intialise the printing environment with :link reftype=hd res=1070.PrtGRxInit:elink.
:li.Choose a printer with :link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:li.If necessary set the job properties with :link reftype=hd res=211.PrtGrxJobProperties:elink.
:li.Set the page margins with :link reftype=hd res=222.PrtGRxSetMargins:elink.
:li.Set up the aspect of header with :link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.Set up any header text with :link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.Set up any footer with :link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.Open the print job with :link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.Print your texts, tables, bitmaps etc..
:li.Close the print job with :link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:li.Destroy the printer object with :link reftype=hd res=1080.PrtGRxTerm:elink.
:li.If you wish, drop the functions with :link reftype=hd res=2000.PrtGRxDropFuncs:elink.
:eul.
:lm margin=1.
:p.Since headers and footers often contain constants like the date or the document title and 
variables like the page number, the texts defined for these can contain special 
:link reftype=hd res=130.formatting characters:elink..
:p.:hp2.NOTE:ehp2.
:p.All the input parameters that denote positions are by default in millimetres  or 1/10 inch 
depending on the :link reftype=hd res=314.Measures:elink. property. You can convert from 
inches using the formula&colon.
:lm margin=5.
:p.mm = 254 * inch
:lm margin=1.
:p.All the line widths are defined in TWIPS&colon.
:lm margin=5.
:p.1 Point = 20 TWIPS
.br
1 mm = 56.7 TWIPS (rounded to 57 for internal calculation)
:lm margin=1.
:warning.
.br
If you wish to print several documents concurrently (i.e. in parrallel threads) you must 
initialise and terminate the environment for each thead with :link reftype=hd 
res=1070.PrtGRxInit:elink. and :link reftype=hd res=1080.PrtGRxTerm:elink..
:ewarning.

.***** Formatting Characters ********************************************

:h2 res=130.Formatting Characters
:i2 refid=INTRO.Formatting Characters
:font facename=Helv size=16x12.

:p.To help define header and footer texts with :link reftype=hd res=219.PrtGRxSetFooter:elink. and 
:link reftype=hd res=220.PrtGRxSetHeader:elink. the following special formatting flags are 
defined&colon.

:font facename=Courier size=16x12.
:table cols='8 56' rules=both frame=box.
:row.
:c.$
:c.If followed by one of the other characters in this table it indicates a formatting 
character follows, otherwise it is taken as a literal '$'
:row.
:c.l
:c.Left align the following text
:row.
:c.r
:c.Right align the following text
:row.
:c.c
:c.Centre the following text
:row.
:c.@
:c.Insert the current date formatted acording to the system settings. This is read every time 
a job is started; so you can change the date format from job to job in the same sesssion.
:row.
:c.?
:c.Insert the current time ( taken when the job is opened) formatted acording to the system 
settings. This is read every time a job is started; so you can change the time format from 
job to job in the same sesssion.
:row.
:c.!
:c.Insert the current date and time ( taken when the job is opened) formatted acording to the 
system settings. This is read every time a job is started; so you can change the time format from 
job to job in the same sesssion.
:row.
:c.#
:c.insert the current page number (always arabic)
:row.
:c.› or |
:c.Insert the title of the document (see :link reftype=hd res=216.PrtGRxOpenPrintJob:elink.)
:etable.

:font facename=Helv size=16x12.
:p.:hp2.Example:ehp2.
:p.'$›$rpage $#' would give&colon.
:p.:hp2.Document Title                                        page 1:ehp2.
:p.'$r@ page $#' would give (where date is defined as ISO with '/' separator)&colon.
:p.:hp2.                                                          1995/03/18 page 1:ehp2.

:warning.
.br
:hp2.Formatting characters only apply to the page and table header and page footer texts.:ehp2.
:ewarning.

.***** Fill Styles ******************************************************

:h2 res=135.Fill Syles
:i2 refid=INTRO.Fill Syles
:font facename=Helv size=16x12.

:p.Several of the Printer functions refer to a fill style. You can see the effect of a style 
for any printer by running the :link reftype=hd res=105.DEMO program:elink. and printing the 
:hp2.box styles:ehp2. option. The numbers you pass to any of these functions is translated into 
a :hp2.PATSYM_?????:ehp2. constant, and the output is, to a certain extent, device dependent.
For an idea of what you will obtain see the pictures below.
:p.
:artwork name='w:\prtgraph\bitmaps\styles1.bmp' align=left.
:artwork name='w:\prtgraph\bitmaps\styles2.bmp' align=left.

.***** Properties *******************************************************

:h1 res=300.Printer Properties
:i1 id=PROPS.Printer Properties
:font facename=Helv size=16x12.
:p.The following sections describe the properties that you can "Get" or "Set" with 
:link reftype=hd res=1050.PrtGRxGet:elink. or :link reftype=hd res=1060.PrtGRxSet:elink. 
for a :hp2.Printer Object:ehp2..

:lm margin=5.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=313.ColorEnabled:elink.
:li.:link reftype=hd res=302.CurrentDevice:elink.
:li.:link reftype=hd res=303.CurrentPrinter:elink.
:li.:link reftype=hd res=704.DefaultPrinter:elink.
:li.:link reftype=hd res=709.FormHeight:elink.
:li.:link reftype=hd res=710.FormName:elink.
:li.:link reftype=hd res=711.FormWidth:elink.
:li.:link reftype=hd res=317.JobName:elink.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=305.LineSpace:elink.
:li.:link reftype=hd res=314.Measures:elink.
:li.:link reftype=hd res=705.MinBottomMar:elink.
:li.:link reftype=hd res=706.MinLeftMar:elink.
:li.:link reftype=hd res=707.MinRightMar:elink.
:li.:link reftype=hd res=708.MinTopMar:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:li.:link reftype=hd res=316.PageNum:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:li.:link reftype=hd res=308.Printing:elink.
:li.:link reftype=hd res=312.PrintColor:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=712.ShowProgress:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=311.Version:elink.
:li.:link reftype=hd res=713.WordBreak:elink.
:li.
:li.
:eul.
:lm margin=1.

.***** BottomMargin ************************************************
 
:h2 res=301.BottomMargin
:i2 refid=PROPS.BottomMargin
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=716.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=717.

:h2 hide res=716.BottomMargin - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:eul.

:h2 hide res=717.BottomMargin - Description
:font facename=Helv size=16x12.
:p.The distance of the bottom margin from the lower edge of the page. The measure is in mm or 
1/10 inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** ColorEnabled *****************************************************

:h2 res=313.ColorEnabled
:i2 refid=PROPS.ColorEnabled
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=718.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=719.

:h2 hide res=718.ColorEnabled - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Boolean
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.1 (TRUE)
:li.0 (FALSE)
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=312.PrintColor:elink.
:eul.

:h2 hide res=719.ColorEnabled - Description
:font facename=Helv size=16x12.
:p.Boolean property indicating whether color printing is enabled or not.

.***** CurrentDevice ************************************************
 
:h2 res=302.CurrentDevice
:i2 refid=PROPS.CurrentDevice
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=720.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=721.

:h2 hide res=720.CurrentDevice - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=303.CurrentPrinter:elink.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:eul.

:h2 hide res=721.CurrentDevice - Description
:font facename=Helv size=16x12.
:p.The name of the printer device selected for the printer object. This is the same as the 
Physical Name seen in printer settings notebook.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** CurrentPrinter ************************************************
 
:h2 res=303.CurrentPrinter
:i2 refid=PROPS.CurrentPrinter
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=722.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=723.

:h2 hide res=722.CurrentPrinter - list
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=302.CurrentDevice:elink.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:eul.

:h2 hide res=723.CurrentPrinter - Description
:font facename=Helv size=16x12.
:p.The name of the printer selected for the printer object. This is the same as the name seen on 
the desktop printer object.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** DefaultPrinter ***************************************************

:h2 res=704.DefaultPrinter
:i2 refid=PROPS.DefaultPrinter
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=724.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=725.


:h2 hide res=724.DefaultPrinter - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=302.CurrentDevice:elink.
:li.:link reftype=hd res=303.CurrentPrinter:elink.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:eul.

:h2 hide res=725.DefaultPrinter - Description
:font facename=Helv size=16x12.
:p.The name of the default system printer. This is the same as the name seen on the desktop 
printer object.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** FormHeight *********************************************************

:h2 res=709.FormHeight
:i2 refid=PROPS.FormHeight
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=726.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=727.


:h2 hide res=726.FormHeight - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=710.FormName:elink.
:li.:link reftype=hd res=711.FormWidth:elink.
:eul.

:h2 hide res=727.FormHeight - Description
:font facename=Helv size=16x12.
:p.The height of the currently selected form for the current printer in mm or 1/10 inch 
depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** FormName *********************************************************

:h2 res=710.FormName
:i2 refid=PROPS.FormName
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=728.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=729.

:h2 hide res=728.FormName - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=709.FormHeight:elink.
:li.:link reftype=hd res=711.FormWidth:elink.
:eul.


:h2 hide res=729.FormName - Description
:font facename=Helv size=16x12.
:p.The name of the currently selected form for the current printer.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** FormWidth *********************************************************

:h2 res=711.FormWidth
:i2 refid=PROPS.FormWidth
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=730.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=731.

:h2 hide res=730.FormWidth - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=709.FormHeight:elink.
:li.:link reftype=hd res=710.FormName:elink.
:eul.

:h2 hide res=731.FormWidth - Description
:font facename=Helv size=16x12.
:p.The width of the currently selected form for the current printer in mm or 1/10 inch 
depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** JobName **********************************************************

:h2 res=317.JobName
:i2 refid=PROPS.JobName
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=732.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=733.

:h2 hide res=732.JobName - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.

:h2 hide res=733.JobName - Description
:font facename=Helv size=16x12.
:p.The document name of the current print job.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** LeftMargin ************************************************
 
:h2 res=304.LeftMargin
:i2 refid=PROPS.LeftMargin
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=734.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=735.

:h2 hide res=734.LeftMargin - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:eul.

:h2 hide res=735.LeftMargin - Description
:font facename=Helv size=16x12.
:p.The distance of the left margin from the left edge of the page. The measure is in mm or 1/10 
inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.


.***** LineSpace ******************************************************
 
:h2 res=305.LineSpace
:i2 refid=PROPS.LineSpace
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=736.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=737.

:h2 hide res=736.LineSpace - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:eul.

:h2 hide res=737.LineSpace - Description
:font facename=Helv size=16x12.
:p.Line spacing as a percentage of the font size. The default value is set to single space = 120%. 
All writes following this call will use this inter-line spacing.

.***** Measures ********************************************************

:h2 res=314.Measures
:i2 refid=PROPS.Measures
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=738.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=739.

:h2 hide res=738.Measures - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.Metric
:li.Inch
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:eul.

:h2 hide res=739.Measures - Description
:font facename=Helv size=16x12.
:p.The units to use for distances on the printing page. These can be either mm (the default) 
or in 1/10 inch units.

.***** MinBottomMar ************************************************

:h2 res=705.MinBottomMar
:i2 refid=PROPS.MinBottomMar
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=740.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=741.

:h2 hide res=740.MinBottomMar - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=706.MinLeftMar:elink.
:li.:link reftype=hd res=707.MinRightMar:elink.
:li.:link reftype=hd res=708.MinTopMar:elink.
:eul.

:h2 hide res=741.MinBottomMar - Description
:font facename=Helv size=16x12.
:p.The minimum bottom margin allowed for the selected printer. The measure is in mm or 1/10 
inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** MinLeftMar ************************************************

:h2 res=706.MinLeftMar
:i2 refid=PROPS.MinLeftMar
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=742.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=743.

:h2 hide res=742.MinLeftMar - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=705.MinBottomMar:elink.
:li.:link reftype=hd res=707.MinRightMar:elink.
:li.:link reftype=hd res=708.MinTopMar:elink.
:eul.

:h2 hide res=743.MinLeftMar - Description
:font facename=Helv size=16x12.
:p.The minimum left margin allowed for the selected printer. The measure is in mm or 1/10 
inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** MinRightMar ************************************************

:h2 res=707.MinRightMar
:i2 refid=PROPS.MinRightMar
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=744.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=745.

:h2 hide res=744.MinRightMar - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=705.MinBottomMar:elink.
:li.:link reftype=hd res=706.MinLeftMar:elink.
:li.:link reftype=hd res=708.MinTopMar:elink.
:eul.

:h2 hide res=745.MinRightMar - Description
:font facename=Helv size=16x12.
:p.The minimum right margin allowed for the selected printer. The measure is in mm or 1/10 
inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** MinTopMar ************************************************

:h2 res=708.MinTopMar
:i2 refid=PROPS.MinTopMar
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=746.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=747.

:h2 hide res=746.MinTopMar - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=705.MinBottomMar:elink.
:li.:link reftype=hd res=706.MinLeftMar:elink.
:li.:link reftype=hd res=707.MinRightMar:elink.
:eul.

:h2 hide res=747.MinTopMar - Description
:font facename=Helv size=16x12.
:p.The minimum top margin allowed for the selected printer. The measure is in mm or 1/10 inch 
depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** PageHeight ************************************************
 
:h2 res=306.PageHeight
:i2 refid=PROPS.PageHeight
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=748.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=749.

:h2 hide res=748.PageHeight - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:eul.

:h2 hide res=749.PageHeight - Decsription
:font facename=Helv size=16x12.
:p.The height of the printing area of the page (bottom to top margin) in mm or 1/10 inch 
depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** PageNum **********************************************************

:h2 res=316.PageNum
:i2 refid=PROPS.PageNum
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=750.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=751.


:h2 hide res=750.PageNum - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=317.JobName:elink.
:eul.

:h2 hide res=751.PageNum - Description
:font facename=Helv size=16x12.
:p.This property contains the number of the page that is currently being printed.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** PageWidth ************************************************
 
:h2 res=307.PageWidth
:i2 refid=PROPS.PageWidth
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=752.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=753.

:h2 hide res=752.PageWidth - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:eul.

:h2 hide res=753.PageWidth - Description
:font facename=Helv size=16x12.
:p.The width of the printing area of the page (left to right margin) in mm or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** Printing ************************************************
 
:h2 res=308.Printing
:i2 refid=PROPS.Printing
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=754.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=755.

:h2 hide res=754.Printing - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Boolean
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.1 (TRUE)
:li.0 (FALSE)
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:eul.

:h2 hide res=755.Printing - Description
:font facename=Helv size=16x12.
:p.This property is set to 1 when a print job is open on the printer object. Otherwise this 
property is set to 0.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** PrintColor *******************************************************

:h2 res=312.PrintColor
:i2 refid=PROPS.PrintColor
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=756.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=757.

:h2 hide res=756.PrintColor - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.String
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.See Description
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=313.ColorEnabled:elink.
:eul.

:h2 hide res=757.PrintColor - Description
:font facename=Helv size=16x12.
:p.This property is only relevant for colour printers. It contains the current colour being used 
for printing. This color can be any of the followng values&colon.
:font facename=Courier size=16x12.
:table cols='15 15 15' rules=none frame=none.
:row.
:c.White:c.Black:c.Blue
:row.
:c.Red:c.Pink:c.Green
:row.
:c.Cyan:c.Yellow:c.DarkGray
:row.
:c.DarkBlue:c.DarkRed:c.DarkPink
:row.
:c.DarkGreen:c.DarkCyan:c.Brown
:row.
:c.PaleGrey:c.<default>
:etable.

.***** RightMargin ************************************************
 
:h2 res=309.RightMargin
:i2 refid=PROPS.RightMargin
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=758.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=759.

:h2 hide res=758.RightMargin - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=310.TopMargin:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:eul.

:h2 hide res=759.RightMargin - Description
:font facename=Helv size=16x12.
:p.The distance of the right margin from the right edge of the page. The measure is in mm or 
1/10 inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** ShowProgress *****************************************************

:h2 res=712.ShowProgress
:i2 refid=PROPS.ShowProgress
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=760.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=761.

:h2 hide res=760.ShowProgress - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Boolean
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.1 (TRUE)
:li.0 (FALSE)
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=715.PrtGRxSetProgressTexts:elink.
:eul.

:h2 hide res=761.ShowProgress - Description
:font facename=Helv size=16x12.
:p.This is boolean property that when set enables the progress dialog to pop up when a 
job is printing.
:artwork name='w:\prtgraph\bitmaps\progress.bmp' align=left.
:p.:hp2.Figure&colon. Default Progress Dialog.:ehp2.

.***** TopMargin ************************************************
 
:h2 res=310.TopMargin
:i2 refid=PROPS.TopMargin
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=762.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=763.

:h2 hide res=762.TopMargin - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=301.BottomMargin:elink.
:li.:link reftype=hd res=304.LeftMargin:elink.
:li.:link reftype=hd res=309.RightMargin:elink.
:li.:link reftype=hd res=306.PageHeight:elink.
:li.:link reftype=hd res=307.PageWidth:elink.
:eul.

:h2 hide res=763.TopMargin - Description
:font facename=Helv size=16x12.
:p.The distance of the top margin from the upper edge of the page. The measure is in mm or 1/10 
inch depending on the :link reftype=hd res=314.Measures:elink. property.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** Version ************************************************
 
:h2 res=311.Version
:i2 refid=PROPS.Version
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=764.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=765.

:h2 hide res=764.Version - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=765.Version - Description
:font facename=Helv size=16x12.
:p.Version number of the object.
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** WordBreak ********************************************************

:h2 res=713.WordBreak
:i2 refid=PROPS.WordBreak
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=766.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=767.

:h2 hide res=766.WordBreak - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Boolean
:esl.
:p.:hp2.Possible Values:ehp2.
:sl compact.
:li.1 (TRUE)
:li.0 (FALSE)
:esl.

:h2 hide res=767.WordBreak - Description
:font facename=Helv size=16x12.
:p.The :hp2.WordBreak:ehp2. property allows you to control the way the :hp2.Printer 
Object:ehp2. performs word wrapping on a block of text. By default this property is set to 
1 (TRUE) so that the breaks occur between words. By setting this property off (0), line 
wrapping will occur with breaks between characters.

.***** XPos ********************************************************

:h2 res=2004.XPos
:i2 refid=PROPS.XPos
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=2005.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=2006.

:h2 hide res=2005.XPos - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=2006.XPos - Description
:font facename=Helv size=16x12.
:p.The :hp2.XPos:ehp2. property contains the current X axis position of the printing 
cursor relative to the left margin in the chosen :link reftype=hd res=314.Measures:elink..
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** XPos ********************************************************

:h2 res=2007.YPos
:i2 refid=PROPS.YPos
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=2008.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=2009.

:h2 hide res=2008.YPos - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=2009.YPos - Description
:font facename=Helv size=16x12.
:p.The :hp2.XPos:ehp2. property contains the current Y axis position of the printing 
cursor relative to the bottom margin in the chosen :link reftype=hd res=314.Measures:elink..
:warning.
This property is read only and cannot be set with a call to :link reftype=hd res=1060.PrtGRxSet:elink..
:ewarning.

.***** Methods ********************************************************

:h1 res=199.Printer Functions
:i1 id=FUNC.Printer Functions
:font facename=Helv size=16x12.
:p.The following sections describe each of the functions available for a :hp2.Printer 
Object:ehp2. in the :hp2.PrtGraph REXX Library:ehp2.. In the following list, the names of the 
old functions are given where applicacable. These old function names are maintained for 
backward compatibility.
:ul compact.
:li.:link reftype=hd res=245.PrtGRxAbortPrintJob:elink.
:li.:link reftype=hd res=702.PrtGRxBlockFits:elink.
:li.:link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=2000.PrtGRxDropFuncs:elink.
:li.:link reftype=hd res=206.PrtGRxEndRow:elink.
:li.:link reftype=hd res=207.PrtGRxEndTable:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink. or PrtGRxFontDlg
:li.:link reftype=hd res=1050.PrtGRxGet:elink.
:li.:link reftype=hd res=209.PrtGRxGoto:elink.
:li.:link reftype=hd res=1070.PrtGRxInit:elink.
:li.:link reftype=hd res=211.PrtGrxJobProperties:elink. or PrtGRxJobProps
:li.:link reftype=hd res=714.PrtGRxLineFits:elink.
:li.:link reftype=hd res=1090.PrtGRxLoadFuncs:elink.
:li.:link reftype=hd res=215.PrtGRxNewPage:elink.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.:link reftype=hd res=201.PrtGRxPrintBitMap:elink. or PrtGRxBitmap
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink. or PrtGRxBox
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink. or PrtGRxCentre
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink. or PrtGRxPrinterDlg
:li.:link reftype=hd res=218.PrtGRxPrinterList:elink.
:li.:link reftype=hd res=237.PrtGRxPrintFile:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink. or PrtGRxJustified
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink. or PrtGRxWrite
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink. or PrtGRxWriteln
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink. or PrtGRxJustRight
:li.:link reftype=hd res=240.PrtGRxResetColHeader:elink.
:li.:link reftype=hd res=246.PrtGRxResetHeader:elink.
:li.:link reftype=hd res=1060.PrtGRxSet:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink. or PrtGRxSetHdrLineFont
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:li.:link reftype=hd res=715.PrtGRxSetProgressTexts:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=227.PrtGRxTab:elink.
:li.:link reftype=hd res=1080.PrtGRxTerm:elink.
:eul.

.***** PrtGRxAbortPrintJob ****************************************************

:h2 res=245.PrtGRxAbortPrintJob
:i2 refid=FUNC.PrtGRxAbortPrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=768. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=769.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=770.

:h2 hide res=768.PrtGRxAbortPrintJob - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=769.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=770.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=771.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.:link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:eul.


:h2 hide res=769.PrtGRxAbortPrintJob - Description
:xmp.
ok = PrtGRxAbortPrintJob( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Aborts the print job and deletes the document from the print queue.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=770.PrtGRxAbortPrintJob - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

:h2 hide res=771.PrtGRxAbortPrintJob - Example
:xmp.
/********************************************************************/
/* Abort the print job                                              */
/********************************************************************/

ok = PrtGRxAbortPrintJob( printer);

:exmp.

.***** PrtGRxBlockFits ********************************************************

:h2 res=702.PrtGRxBlockFits
:i2 refid=FUNC.PrtGRxBlockFits
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=772. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=773.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=774.

:h2 hide res=772.PrtGRxBlockFits - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=773.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=774.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=775.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=714.PrtGRxLineFits:elink.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=773.PrtGRxBlockFits - Description
:xmp.
ok = PrtGRxBlockFits( printer, 
                      face_name, 
                      points, 
                      string);
:exmp.
:font facename=Helv size=16x12.
:p.Checks whether the text will fit as one block onto the page or needs a new page to complete.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if the block of text will fit on the page else FALSE (0).
:note.
.br
:hp2.No text is actually printed.:ehp2.


:h2 hide res=774.PrtGRxBlockFits - parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, the 
previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=775.PrtGRxBlockFits - Example
:xmp.

    facename = 'Helvetica';

    /**** Text is long block of text */    
    fnt = 8
    rcy = PrtGRxPrintLine( printer, facename, fnt, text);
    rcy = PrtGRxPrintLine( printer, , fnt, '');
    do fnt = 10 to 24 by 2
        if PrtGRxBlockFits( printer, facename, fnt, text) then
            rcy = PrtGRxPrintLine( printer, , fnt, text);
        else do
            rcy = PrtGRxGoto( printer, 0, 10, 1);
            rcy = PrtGRxPrintRight( printer, , 10, "Continued...");
            rcy = PrtGRxPrintLine( printer, , fnt, text);
        end
        if PrtGRxBlockFits( printer, facename, fnt, '') then
            rcy = PrtGRxPrintLine( printer, , fnt, '');
        else
            rcy = PrtGRxPrintRight( printer, , 10, "Continued...");
    end

:exmp.

.***** PrtGRxClosePrintJob *************************************************
 
:h2 res=204.PrtGRxClosePrintJob
:i2 refid=FUNC.PrtGRxClosePrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=776. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=777.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=778.

:h2 hide res=776.PrtGRxClosePrintJob - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=777.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=778.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=779.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.:link reftype=hd res=245.PrtGRxAbortPrintJob:elink.
:eul.


:h2 hide res=777.PrtGRxClosePrintJob - Description
:xmp.
ok = PrtGRxClosePrintJob( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Close the print job and end the document.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).


:h2 hide res=778.PrtGRxClosePrintJob - parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.


:h2 hide res=779.PrtGRxClosePrintJob - Example
:xmp.
/********************************************************************/
/* Close the print job                                              */
/********************************************************************/

ok = PrtGRxClosePrintJob( printer);

:exmp.

.***** PrtGRxDefineTable ****************************************************

:h2 res=200.PrtGRxDefineTable
:i2 refid=FUNC.PrtGRxDefineTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=780. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=781.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=782.

:h2 hide res=780.PrtGRxDefineTable - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=781.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=782.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=783.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=206.PrtGRxEndRow:elink.
:li.:link reftype=hd res=207.PrtGRxEndTable:elink.
:eul.

:h2 hide res=781.PrtGRxDefineTable - Description
:xmp.
ok = PrtGRxDefineTable( printer, 
                        "table.", 
                        "Cols.");
:exmp.
:font facename=Helv size=16x12.
:p.Defines a table for printing. If there are not the right number of elements in the stem vars 
the function will return FALSE.
:p.This call only prepares the internal structures for handling a table, to start printing the 
table you must call :link reftype=hd res=225.PrtGRxStartRow:elink. and :link reftype=hd 
res=224.PrtGRxStartCol:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=782.PrtGRxDefineTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt."table."
:pd.Quoted name of a stem variable containing the definition of the table&colon.
:lm margin=5.
:parml compact tsize=15 break=none.
:pt.table.0
:pd.Must be 11 (originally 9) for monochrome printing or 17 (originally 15) if you use colour 
support
:pt.table.1
:pd.fill style for the table (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.table.2
:pd.line thickness in TWIPS for the outlines of the cells in the table
:pt.table.3
:pd.Flag indicating that table has column headers
:pt.table.4
:pd.fill style for the table header (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.table.5
:pd.line thickness in TWIPS for the outlines of the table headers
:pt.table.6
:pd.Flag indicating that the table header should be printed on all pages. 
.br
(1 = TRUE, 0 = FALSE)
:pt.table.7
:pd.Point size of text for column header texts
:pt.table.8
:pd.Font face name for column header texts
.br
:pt.table.9
:pd.Left edge of the table from the left margin in mm or 1/10 inch depending on the :link 
reftype=hd res=314.Measures:elink. property
:pt.table.10
:pd.A combination of the following flags that defines which sides of the box around the cells are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
.br
16 = Do not draw the far left and far right edges of the table
:pt.table.11
:pd.A combination of the above flags that defines which sides of the box around the column headers are drawn.
:pt.table.12
:pd.Colour for the text in the table cells
:pt.table.13
:pd.Colour for the line around table cells
:pt.table.14
:pd.Colour for the fill pattern in table cells
:pt.table.15
:pd.Colour for the text in the table headers
:pt.table.16
:pd.Colour for the line around table headers
:pt.table.17
:pd.Colour for the fill pattern in table headers
:eparml.
:lm margin=1.
:pt."Cols."
:pd.Quoted name of a complex stem variable containing the definitions for the columns in the 
table. it has the form Cols.x.y
.br
where
.br
:lm margin=5.
x is the column reference starting with 1
y is the field number
:lm margin=1.
:lm margin=5.
:parml compact tsize=15 break=none.
:pt.Cols.0.0
:pd.Number of columns in the table
:pt.Cols.x.1
:pd.Width of the column in mm or 1/10 inch depending on the :link 
reftype=hd res=314.Measures:elink. property
:pt.Cols.x.2
:pd.Column header text
:eparml.
:eparml.

:h2 hide res=783.PrtGRxDefineTable - Example
:xmp.
/************************************************************************/
/* Declare a table with no fill style, 0.5 mm separator lines, 1mm      */
/* lines around headers on all pages and 3 columns                      */
/************************************************************************/

table.0 = 15
table.1 = 0
table.2 = 28
table.3 = 1
table.4 = 0
table.5 = 56
table.6 = 1
table.7 = 12
table.8 = 'Helvetica Bold'
table.9 = 10
table.10 = "Red"
table.11 = "Cyan"
table.12 = "Black"
table.13 = "Blue"
table.14 = "White"
table.15 = "Black"

Cols.0.0 = 3

Cols.1.1 = 45
Cols.1.2 = 'Column 1'

Cols.2.1 = 75
Cols.2.2 = 'Column 2'

Cols.3.1 = 40
Cols.3.2 = 'Column 3'
                       
ok = PrtGRxDefineTable( printer, "table.", "Cols.");

if ok then do

    /**** Start printing in the table **********************************/
    
    ok = PrtGRxStartRow( printer);
    
    /**** Start printing in column 1 ***********************************/
    
    ok = PrtGRxStartCol( printer, 1);
    ok = PrtGRxPrintRight( printer, 'Helvetica', 10, textvar);
    
    /**** Start printing in column 2 ***********************************/
    
    ok = PrtGRxStartCol( printer, 2);
    ok = PrtGRxPrintJustified( printer, 'Helvetica Bold', 10, textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    
    /**** Start printing in column 3 ***********************************/
    
    ok = PrtGRxStartCol( printer, 3);
    ok = PrtGRxPrintCentered( printer, 'Helvetica Bold', 14, textvar);
    
    /**** Print the row ************************************************/
    
    ok = PrtGRxEndRow( printer);
    
    /**** Start a new row **********************************************/
    
    ok = PrtGRxStartRow( printer);
    ok = PrtGRxStartCol( printer, 1);
    ok = PrtGRxPrintRight( printer, 'Times New Roman', 10, textvar);
    ok = PrtGRxStartCol( printer, 2);
    ok = PrtGRxPrintLeft( printer, 'Helvetica Bold', 10, textvar);
    ok = PrtGRxPrintCentered( printer,,,textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    ok = PrtGRxPrintRight( printer,,,textvar);
    ok = PrtGRxStartCol( printer, 3);
    ok = PrtGRxPrintJustified( printer, 'Times New Roman', 8, textvar);
    
    /**** Print the row ************************************************/
    
    ok = PrtGRxEndRow( printer);
    
    /**** Destroy the table data structures ****************************/
    
    ok = PrtGRxEndTable( printer);
end
:exmp.
 

.***** PrtGRxDrawLine ***************************************************

:h2 res=2088.PrtGRxDrawLine
:i2 refid=FUNC.PrtGRxDrawLine
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2089.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2090.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2091.

:h2 hide res=2089.PrtGRxDrawLine - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2090.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2091.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink.
:li.:link reftype=hd res=201.PrtGRxPrintBitMap:elink.
:li.:link reftype=hd res=2020.PrtGRxPrintWinImage:elink.
:li.:link reftype=hd res=2010.PrtGRxPrintJPEG:elink.
:eul.

:h2 hide res=2090.PrtGRxDrawLine - Description
:xmp.
ok = PrtGRxDrawLine( printer,
                     lx, ly, 
                     tx, ty, 
                     th, 
                     line_color, 
                     line_style);
:exmp.
:font facename=Helv size=16x12.
:p.Draws a line from lx,ly to tx,ty with the given thickness, colour and style. The style is only 
valid if the thickness parameter is 0 (default PM line) or 1 (Thick PM line), otherwise the line 
is always solid. This is a restriction of the GPI interface.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
The position of the cursor is unaffected by this method.

:h2 hide res=2091.PrtGRxDrawLine - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.th
:pd.The thickness of the line&colon.
.br
0 = LINEWIDTH_NORMAL
.br
1 = LINEWIDTH_THICK
.br
>1 width in TWIPS ( 56.7 TWIPS = 1mm)
:pt.line_color
:pd.The colour of the line. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.line_style
:pd.The PM line style&colon.
.br
0 = LINETYPE_DEFAULT 
.br
1 = LINETYPE_DOT 
.br
2 = LINETYPE_SHORTDASH 
.br
3 = LINETYPE_DASHDOT 
.br
4 = LINETYPE_DOUBLEDOT 
.br
5 = LINETYPE_LONGDASH 
.br
6 = LINETYPE_DASHDOUBLE DOT 
.br
7 = LINETYPE_SOLID 
.br
8 = LINETYPE_INVISIBLE 
.br
9 = LINETYPE_ALTERNATE 
:eparml.

.***** PrtGRxDropFuncs **************************************************

:h2 res=2000.PrtGRxDropFuncs
:i2 refid=FUNC.PrtGRxDropFuncs
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2001. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2002.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2003.
 
:h2 hide res=2001.PrtGRxDropFuncs - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2002.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2003.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=2075.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1090.PrtGRxLoadFuncs:elink.
:eul.

:h2 hide res=2002.PrtGRxDropFuncs - Description
:xmp.
ok = PrtGRxDropFuncs( );
:exmp.
:font facename=Helv size=16x12.
:p.Drops all the functions for the :hp2.PrtGraph REXX Library:ehp2..
:p.:hp2.Return:ehp2.
:p.Always returns 1 (TRUE).

:h2 hide res=2003.PrtGRxDropFuncs - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

:h2 hide res=2075.PrtGRxDropFuncs - Example
:xmp.

rc = PrtGRxDropFuncs

:exmp.

.***** PrtGRxEndRow ********************************************************
 
:h2 res=206.PrtGRxEndRow
:i2 refid=FUNC.PrtGRxEndRow
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=784. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=785.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=786.

:h2 hide res=784.PrtGRxEndRow - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=785.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=786.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=207.PrtGRxEndTable:elink.
:eul.

:h2 hide res=785.PrtGRxEndRow - Description
:xmp.
ok = PrtGRxEndRow( printer);
:exmp.
:font facename=Helv size=16x12.
:p.End the current row in a table and print it. This will cause the table to wrap over page 
if any of the columns will not fit. Cells will be split over the page not forced onto the next 
page. If you have defined running headers for the table, these will be printed at the top of 
the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=786.PrtGRxEndRow - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.
 
.***** PrtGRxEndTable ******************************************************
 
:h2 res=207.PrtGRxEndTable
:i2 refid=FUNC.PrtGRxEndTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=787. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=788.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=789.

:h2 hide res=787.PrtGRxEndTable - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=788.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=789.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=206.PrtGRxEndRow:elink.
:eul.

:h2 hide res=788.PrtGRxEndTable - Description
:xmp.
ok = PrtGRxEndTable( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Terminate table mode printing and return to normal text printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=789.PrtGRxEndTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

.***** PrtGRxFontDialog ****************************************************
 
:h2 res=234.PrtGRxFontDialog
:i2 refid=FUNC.PrtGRxFontDialog
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=790. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=791.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=792.

:h2 hide res=790.PrtGRxFontDialog - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=791.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=792.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=793.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:li.:link reftype=hd res=218.PrtGRxPrinterList:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:eul.

:h2 hide res=791.PrtGRxFontDialog - Description
:xmp.
font = PrtGRxFontDialog( printer, 
                         title, 
                         familyname);
:exmp.
:font facename=Helv size=16x12.
:p.Pops up a dialog with a list of fonts available on your work station for the selected 
printer.
:p.:hp2.Return:ehp2.
:p.Name of the selected font if successful, otherwise an empty string.
:artwork name='w:\prtgraph\bitmaps\fontdlg.bmp' align=left.
:p.:hp2.Figure&colon. Font Dialog.:ehp2.

:h2 hide res=792.PrtGRxFontDialog - parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.title
:pd.Title to appear in the font dialog.
:pt.familyname
:pd.This will set the default selected font in the dialog. This is the name of the font e.g. 
Helvetica and should not include the point size or attributes.
:eparml.

:h2 hide res=793.PrtGRxFontDialog - Example
:xmp.

fntstr = PrtGRxFontDialog( printer, "Choose printer font", "CG Times");

:exmp.

.***** PrtGRxFreeResMod *****************************************************
 
:h2 res=2060.PrtGRxFreeResMod
:i2 refid=FUNC.PrtGRxFreeResMod
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2061. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2062.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2063.

:h2 hide res=2061.PrtGRxFreeResMod - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2062.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2063.Parameters:elink. 
:eul.

:h2 hide res=2062.PrtGRxFreeResMod - Description
:xmp.
ok = PrtGRxFreeResMod( hmod); 
:exmp.
:font facename=Helv size=16x12.
:p.Frees a DLL that was loaded using :link reftype=hd res=2050.PrtGRxLoadResMod:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2063.PrtGRxFreeResMod - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.hmod
:pd.Module handle returned by :link reftype=hd res=2050.PrtGRxLoadResMod:elink..
:eparml.

.***** PrtGRxGet ********************************************************

:h2 res=1050.PrtGRxGet
:i2 refid=FUNC.PrtGRxGet
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1051. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1052.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1053.
 
:h2 hide res=1051.PrtGRxGet - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1052.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1053.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1054.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1060.PrtGRxSet:elink.
:li.:link reftype=hd res=300.Printer properties:elink.
:eul.

:h2 hide res=1052.PrtGRxGet - Description
:xmp.
ok = PrtGRxGet( printer, 
                Property);
:exmp.
:font facename=Helv size=16x12.
:p.Retrieves the value of the given property for the printer object.
:p.:hp2.Return:ehp2.
:p.A string represenation of the property.

:h2 hide res=1053.PrtGRxGet - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.Property
:pd.name of the property. see :link reftype=hd res=300.Printer properties:elink.
:eparml.

:h2 hide res=1054.PrtGRxGet - Example
:xmp.

prtstr = PrtGRxGet( printer, "CurrentPrinter");

say prtstr

:exmp.

.***** PrtGRxGoto **********************************************************
 
:h2 res=209.PrtGRxGoto
:i2 refid=FUNC.PrtGRxGoto
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=794. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=795.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=796.

:h2 hide res=794.PrtGRxGoto - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=795.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=796.Parameters:elink. 
:eul.

:h2 hide res=795.PrtGRxGoto - Description
:xmp.
ok = PrtGRxGoto( printer, 
                 x, 
                 y, 
                 use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor to the given position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=796.PrtGRxGoto - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.x
:pd.X coordinate in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from the left margin, unless :hp2.use_points:ehp2. 
is :hp2.1:ehp2.
:pt.y
:pd.Y coordinate in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from the bottom margin, unless :hp2.use_points:ehp2. 
is :hp2.1:ehp2.
:pt.use_points
:pd.flag indicating whether to use the default :link reftype=hd res=314.Measures:elink. 
or points.
.br
0 (or parameter absent) = Use default measure
.br
1 = use Points
:eparml.

.***** PrtGRxGotoTab **********************************************************
 
:h2 res=2084.PrtGRxGotoTab
:i2 refid=FUNC.PrtGRxGotoTab
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2085. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2086.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2087.

:h2 hide res=2085.PrtGRxGotoTab - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2086.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2087.Parameters:elink. 
:eul.

:h2 hide res=2086.PrtGRxGotoTab - Description
:xmp.
ok = PrtGRxGotoZTab( printer, 
                     TabNumber);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor to the given tab.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2087.PrtGRxGotoTab - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.TabNumber
:pd.Number of the tab.
:eparml.

.***** PrtGRxGotoX **********************************************************
 
:h2 res=2076.PrtGRxGotoX
:i2 refid=FUNC.PrtGRxGotoX
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2077. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2078.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2079.

:h2 hide res=2077.PrtGRxGotoX - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2078.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2079.Parameters:elink. 
:eul.

:h2 hide res=2078.PrtGRxGotoX - Description
:xmp.
ok = PrtGRxGotoX( printer, 
                  x, 
                  use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor on the x-axis to the given position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2079.PrtGRxGotoX - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.x
:pd.X coordinate in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from the left margin, unless :hp2.use_points:ehp2. 
is :hp2.1:ehp2.
:pt.use_points
:pd.flag indicating whether to use the default :link reftype=hd res=314.Measures:elink. 
or points.
.br
0 (or parameter absent) = Use default measure
.br
1 = use Points
:eparml.

.***** PrtGRxGotoY **********************************************************
 
:h2 res=2080.PrtGRxGotoY
:i2 refid=FUNC.PrtGRxGotoY
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2081. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2082.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2083.

:h2 hide res=2081.PrtGRxGotoY - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2082.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2083.Parameters:elink. 
:eul.

:h2 hide res=2082.PrtGRxGotoY - Description
:xmp.
ok = PrtGRxGotoY( printer, 
                  y, 
                  use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor on the Y-axis to the given position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2083.PrtGRxGotoY - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.y
:pd.Y coordinate in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from the bottom margin, unless :hp2.use_points:ehp2. 
is :hp2.1:ehp2.
:pt.use_points
:pd.flag indicating whether to use the default :link reftype=hd res=314.Measures:elink. 
or points.
.br
0 (or parameter absent) = Use default measure
.br
1 = use Points
:eparml.

.***** PrtGRxInit ********************************************************

:h2 res=1070.PrtGRxInit
:i2 refid=FUNC.PrtGRxInit
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1071. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1072.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1073.
 
:h2 hide res=1071.PrtGRxInit - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1072.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1073.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1074.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1080.PrtGRxTerm:elink.
:eul.
 

:h2 hide res=1072.PrtGRxInit - Description
:xmp.
ok = PrtGRxInit( hWnd);
:exmp.
:font facename=Helv size=16x12.
:p.Initialises a new printer object for use and if running from commnd line REXX, starts the PM Daemon if necessary.
:p.:hp2.Return:ehp2.
:p.A unique identifier for a printer object or :hp2.0:ehp2. if there was an error.

:h2 hide res=1073.PrtGRxInit - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.hWnd
:pd.For Command line REXX processes, this :hp2.MUST:ehp2. be :hp2.0:ehp2.. For PM REXX environements this is the parent Window handle (see example code for VX-REXX).
:eparml.

:h2 hide res=1074.PrtGRxInit - Example
:xmp.

printer = PrtGRxInit( 0); /* Command line REXX */

:exmp.

.***** PrtGrxJobProperties ******************************************************
 
:h2 res=211.PrtGrxJobProperties
:i2 refid=FUNC.PrtGrxJobProperties
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=797. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=798.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=799.

:h2 hide res=797.PrtGrxJobProperties - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=795.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=796.Parameters:elink.
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:li.:link reftype=hd res=218.PrtGRxPrinterList:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:eul.

:h2 hide res=798.PrtGrxJobProperties - Description
:xmp.
ok = PrtGrxJobProperties( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Pops up the job properties dialog for the printer selected with :link reftype=hd 
res=217.PrtGRxPrinterDialog:elink. or with :link reftype=hd res=223.PrtGRxSetPrinter:elink.. 
If there is no selected printer, an error dialog is popped up and the function returns FALSE.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:artwork name='w:\prtgraph\bitmaps\jobprops.bmp' align=left.
:p.:hp2.Figure&colon. Printer Job Properties Dialog for a Laserjet IIIP.:ehp2.

:h2 hide res=799.PrtGrxJobProperties - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

.***** PrtGRxLineFits *********************************************************

:h2 res=714.PrtGRxLineFits
:i2 refid=FUNC.PrtGRxLineFits
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=800. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=801.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=802.

:h2 hide res=800.PrtGRxLineFits - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=801.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=802.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=702.PrtGRxBlockFits:elink.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=801.PrtGRxLineFits - Description
:xmp.
ok = PrtGRxLineFits( printer, 
                     face_name, 
                     points, 
                     string);
:exmp.
:font facename=Helv size=16x12.
:p.Checks whether the text will fit onto the line or needs to be wrapped.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if the block of text will fit on the line else FALSE (0).
:note.
.br
:hp2.No text is actually printed.:ehp2.

:h2 hide res=802.PrtGRxLineFits - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

.***** PrtGRxLoadFuncs **************************************************

:h2 res=1090.PrtGRxLoadFuncs
:i2 refid=FUNC.PrtGRxLoadFuncs
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1091. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1092.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1093.
 
:h2 hide res=1091.PrtGRxLoadFuncs - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1092.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1093.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1094.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=2000.PrtGRxDropFuncs:elink.
:eul.

:h2 hide res=1092.PrtGRxLoadFuncs - Description
:xmp.
ok = PrtGRxLoadFuncs( );
:exmp.
:font facename=Helv size=16x12.
:p.Loads all the functions for the :hp2.PrtGraph REXX Library:ehp2..
:p.:hp2.Return:ehp2.
:p.Always returns 1 (TRUE).

:h2 hide res=1093.PrtGRxLoadFuncs - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

:h2 hide res=1094.PrtGRxLoadFuncs - Example
:xmp.

rc = PrtGRxLoadFuncs

:exmp.

.***** PrtGRxLoadResMod *****************************************************
 
:h2 res=2050.PrtGRxLoadResMod
:i2 refid=FUNC.PrtGRxLoadResMod
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2051. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2052.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2053.

:h2 hide res=2051.PrtGRxLoadResMod - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2052.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2053.Parameters:elink. 
:eul.

:h2 hide res=2052.PrtGRxLoadResMod - Description
:xmp.
hmod = PrtGRxLoadResMod( dll_name); 
:exmp.
:font facename=Helv size=16x12.
:p.Loads a DLL to make the resources available to your program.
:p.:hp2.Return:ehp2.
:p.The module handle of the DLL.

:h2 hide res=2053.PrtGRxLoadResMod - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.dll_name
:pd.Either the name of the DLL if it is on the LIBPATH, or the full path name of the file.
:eparml.

.***** PrtGRxMoveX **********************************************************
 
:h2 res=2030.PrtGRxMoveX
:i2 refid=FUNC.PrtGRxMoveX
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2031. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2032.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2033.

:h2 hide res=2031.PrtGRxMoveX - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2032.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2033.Parameters:elink. 
:eul.

:h2 hide res=2032.PrtGRxMoveX - Description
:xmp.
ok = PrtGRxMoveX( printer, 
                  x, 
                  use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor by :hp2.x:ehp2. units on the X axis relative to the current position.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2033.PrtGRxMoveX - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.x
:pd.Number of measurement units to move. If :hp2.x:ehp2. is negative, the cursor moves left
:pt.use_points
:pd.flag indicating whether to use the default :link reftype=hd res=314.Measures:elink. 
or points for the :hp2.x:ehp2. units
.br
0 (or parameter absent) = Use default measure
.br
1 = use Points
:eparml.

.***** PrtGRxMoveX **********************************************************
 
:h2 res=2040.PrtGRxMoveY
:i2 refid=FUNC.PrtGRxMoveY
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2041. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2042.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2043.

:h2 hide res=2041.PrtGRxMoveY - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2042.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2043.Parameters:elink. 
:eul.

:h2 hide res=2042.PrtGRxMoveY - Description
:xmp.
ok = PrtGRxMoveY( printer, 
                  y, 
                  use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor by :hp2.y:ehp2. units on the Y axis relative to the current position. 
You can use this function to create subscripts and superscripts.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2043.PrtGRxMoveY - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.y
:pd.Number of measurement units to move.  If :hp2.y:ehp2. is negative, the cursor moves up
:pt.use_points
:pd.flag indicating whether to use the default :link reftype=hd res=314.Measures:elink. 
or points for the :hp2.y:ehp2. units
.br
0 (or parameter absent) = Use default measure
.br
1 = use Points
:eparml.

.***** PrtGRxNewPage *******************************************************
 
:h2 res=215.PrtGRxNewPage
:i2 refid=FUNC.PrtGRxNewPage
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=803. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=804.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=805.

:h2 hide res=803.PrtGRxNewPage - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=801.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=802.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:eul.

:h2 hide res=804.PrtGRxNewPage - Description
:xmp.
ok = PrtGRxNewPage( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Forces a new page to be printed with its header and footer. If this function is called 
inside a table, any headers defined for the table will also be printed.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=805.PrtGRxNewPage - Parameters
:p.:hp2.Parameters:ehp2.
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.
 
.***** PrtGRxOpenPrintJob **************************************************
 
:h2 res=216.PrtGRxOpenPrintJob
:i2 refid=FUNC.PrtGRxOpenPrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=806.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=807.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=808.

:h2 hide res=806.PrtGRxOpenPrintJob - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=807.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=808.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=809.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:eul.

:h2 hide res=807.PrtGRxOpenPrintJob - Description
:xmp.
ok = PrtGRxOpenPrintJob( printer, 
                         doc_name, 
                         num_copies);
:exmp.
:font facename=Helv size=16x12.
:p.Opens the print job with the spooler. You should previously define the margins, header and 
and footer and, if you do not want to use the default printer, have selected a printer. 
:note.
If you have not selected a printer and there is no default printer for the system, an error 
dialog is popped up and the function returns FALSE.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=808.PrtGRxOpenPrintJob - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.doc_name
:pd.The title of the document. This will aslo be passed to the spooler ad the document name.
:pt.num_copies
:pd.The number of copies to print (some drivers do not accept this parameter).
:eparml.

:h2 hide res=809.PrtGRxOpenPrintJob - Example
:xmp.

ok = PrtGRxSetMargins( printer, 25, 20, 20, 25, 0, 0);
ok = PrtGRxSetHeaderMode( printer, header, facename, 10, 8, 28, 0);
ok = PrtGRxSetHeader( printer, 3, ,
                       "$c|", "$lADD Consulting (CH)$r@",,
                       'Demo for PrtGraph REXX Library for VX-REXX');
ok = PrtGRxSetFooter( printer, facename, 8, 0, 14, '$|$rpage $#');
ok = PrtGRxOpenPrintJob( printer, 'Document Title');
                              
if \ok then
   return

:exmp.
 
.***** PrtGRxPrintBitMap ********************************************************

:h2 res=201.PrtGRxPrintBitMap
:i2 refid=FUNC.PrtGRxPrintBitMap
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=810.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=811.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=812.

:h2 hide res=810.PrtGRxPrintBitMap - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=811.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=812.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=813.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink.
:eul.

:h2 hide res=811.PrtGRxPrintBitMap - Description
:xmp.
ok = PrtGRxPrintBitMap( printer, 
                        bitmap_file, 
                        lx, ly, 
                        tx, ty, 
                        th, 
                        border_color,
                        title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints a bitmap from a file in the box given by the coordinates and framed in the given 
line style. This function will also print a bitmap from a resource ( see :link reftype=hd 
res=812.Parameters:elink.).
:p.The bit map will be stretched or compressed to fit and, if the printer supports colour, 
will be printed in colour.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=812.PrtGRxPrintBitMap - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.bitmap_file
:pd.Full path to the bitmap file you want to print, or a string made up of&colon.
.br
:hp2.hmod:ehp2.$:hp2.res:ehp2.
.br
where
.br
:hp2.hmod:ehp2. is the module handle number id loading from a DLL, or nothing if loading from an executable
.br
:hp2.res:ehp2. is the resource number
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.border_color
:pd.The colour of the line around the bitmap. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.title
:pd.The title text to be printed centered under the image
:eparml.

:h2 hide res=813.PrtGRxPrintBitMap - Example
:xmp.

/********************************************************************/
/* Print the OS/2 logo in a box with a thick outline                */
/********************************************************************/

/**** Get the path to the bit map ***********************************/

set_path = VALUE( 'PATH', , 'OS2ENVIRONMENT');
bootdrive = substr( set_path, pos( '\OS2\SYSTEM', set_path ) -2, 2);
bmp_name = bootdrive || '\os2\bitmap\os2logo.bmp'

/**** Print the bit map with a blue border **************************/

ok = PrtGRxPrintBitMap( printer, bmp_name, 40, 20, ,
                        130, 110, 200, "Blue", ,
                        'Fig 1. - OS/2 Logo');
 
/********************************************************************/
/* Load a resource DLL and then print a bitmap from it              */
/********************************************************************/

hmod = PrtGRxLoadResMod( 'z&colon.\resource\mydll.dll');
bmpname = hmod || '$1023'
ok = PrtGRxPrintBitMap( printer, bmp_name, 40, 20, ,
                        130, 110, 200, "Blue", ,
                        'Fig 2. - My bitmap');

call PrtGRxFreeResMod hmod
:exmp.
 
.***** PrtGRxPrintBox ***********************************************************

:h2 res=202.PrtGRxPrintBox
:i2 refid=FUNC.PrtGRxPrintBox
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=820.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=821.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=822.

:h2 hide res=820.PrtGRxPrintBox - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=811.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=812.Parameters:elink. 
:eul.



:h2 hide res=821.PrtGRxPrintBox - Description
:xmp.
ok = PrtGRxPrintBox( printer, 
                     lx, ly, 
                     tx, ty, 
                     th, st, 
                     line_color, 
                     fill_color,
                     box_style);
:exmp.
:font facename=Helv size=16x12.
:p.Prints a box at the given coordinates and framed in the given line thickness and filled 
with the given style.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
The position of the cursor is unaffected by this function.

:h2 hide res=822.PrtGRxPrintBox - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.st
:pd.Style used for filling the box (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.line_color
:pd.The colour of the line around the box. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.fill_color
:pd.The colour used for the foregound of the fill pattern. One of the colour strings defined 
by :hp2.VX-REXX:ehp2.
:pt.box_style
:pd.A combination of the following flags that defines which sides of the box are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.
 
.***** PrtGRxPrintCentered ********************************************************
 
:h2 res=203.PrtGRxPrintCentered
:i2 refid=FUNC.PrtGRxPrintCentered
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=830.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=831.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=832.

:h2 hide res=830.PrtGRxPrintCentered - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=831.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=832.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=833.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.


:h2 hide res=831.PrtGRxPrintCentered - Description
:xmp.
ok = PrtGRxPrintCentered( printer, 
                          face_name, 
                          points, 
                          string);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given text in the given font and point size centred between the declared margins 
of the page. All the parameters must be present. 
:p.The text will be wrapped over several lines if it is too long to fit on one line and the 
cursor is placed at the beginning of the next line at the end of the printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=832.PrtGRxPrintCentered - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, the 
previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=833.PrtGRxPrintCentered - Examples
:xmp.
/********************************************************************/
/* Print a text centred on the page (or in a cell) in Helvetica 10  */
/********************************************************************/

ok = PrtGRxPrintCentered( printer, "Helvetica", 10, "whatever you want to print");

/**** The following text will have the same font and size ***********/

ok = PrtGRxPrintCentered( printer,,,"Here is some more");

:exmp.

.***** PrtGRxPrinterDialog ****************************************************
 
:h2 res=217.PrtGRxPrinterDialog
:i2 refid=FUNC.PrtGRxPrinterDialog
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=840.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=841.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=842.

:h2 hide res=840.PrtGRxPrinterDialog - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=841.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=842.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=211.PrtGrxJobProperties:elink.
:li.:link reftype=hd res=218.PrtGRxPrinterList:elink.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:eul.

:h2 hide res=841.PrtGRxPrinterDialog - Description
:xmp.
ok = PrtGRxPrinterDialog( printer, 
                          title,
                          "Buttons.");
:exmp.
:font facename=Helv size=16x12.
:p.Pops up a dialog with a list of printers available on your work station. You can set the 
current printer by either double-clicking on a printer or by selecting an item and clicking on 
the OK button.
:p.Initially the default printer will be highlighted.
:p.You can set the properties to use for any of the printers in the list with :hp2.Properties:ehp2. 
button. These properties will be valid until you next call the Dialog.
:p.:hp2.Return:ehp2.
:p.Name of the printer that was selected or an empty string if the :hp2.Cancel:ehp2. button 
was pressed.
:warning.
If you change the button texts, take care that the text will fit on the button as the buttons 
are not resized to the text. :hp2.ALL BUTTON TEXTS ARE LIMITED TO 32 CHARACTERS:ehp2.
:ewarning.
:artwork name='w:\prtgraph\bitmaps\prtdlg.bmp' align=left.
:p.:hp2.Figure&colon. Printer Dialog.:ehp2.


:h2 hide res=842.PrtGRxPrinterDialog - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.title
:pd.Title to appear in the printers dialog.
:pt.Buttons.
:pd.Stem variable containing the texts for the buttons in the dialog.
:lm margin=5.
:parml compact tsize=15 break=none.
:pt.Buttons.0
:pd.Must be 3
:pt.Buttons.1
:pd.New text for the :hp2.OK:ehp2. button in the dialog.
:pt.Buttons.2
:pd.New text for the :hp2.Job properties...:ehp2. button in the dialog.
:pt.Buttons.3
:pd.New text for the :hp2.Cancel:ehp2. button in the dialog.
:eparml.
:lm margin=1.
:eparml.

.***** PrtGRxPrinterList ***************************************************
 
:h2 res=218.PrtGRxPrinterList
:i2 refid=FUNC.PrtGRxPrinterList
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=850.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=851.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=852.

:h2 hide res=850.PrtGRxPrinterList - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=851.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=852.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=853.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=217.PrtGRxPrinterDialog:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:eul.

:h2 hide res=851.PrtGRxPrinterList - Description
:xmp.
ok = PrtGRxPrinterList( printer, 
                        "printers.");
:exmp.
:font facename=Helv size=16x12.
:p.This function returns a list of printer names that you can use to create your own printer 
selection dialog. You can set the selected printer with a call to :link reftype=hd 
res=223.PrtGRxSetPrinter:elink. using the index of the printer name.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=852.PrtGRxPrinterList - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt."printers."
:pd.Quoted name of a stem variable to contain the list of available printers.
.br
:hp2.printers.0:ehp2. will contain the number of printers in the list.
:eparml.

:h2 hide res=853.PrtGRxPrinterList - Example
:xmp.
/****************************************************************/
/* Get the list of printers into a stem variable                */
/****************************************************************/

ok = PrtGRxPrinterList( printer, "printers.");

:exmp.
 
.***** PrtGRxPrintFile ********************************************************

:h2 res=237.PrtGRxPrintFile
:i2 refid=FUNC.PrtGRxPrintFile
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=860.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=861.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=862.

:h2 hide res=860.PrtGRxPrintFile - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=861.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=862.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:li.:link reftype=hd res=204.PrtGRxClosePrintJob:elink.
:li.:link reftype=hd res=201.PrtGRxPrintBitMap:elink.
:eul.


:h2 hide res=861.PrtGRxPrintFile - Description
:xmp.
ok = PrtGRxPrintFile( printer, 
                      face_name, 
                      points, 
                      style, 
                      file_name);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given file in the given font, point size and style. All the parameters must be 
present. 
:p.A print job must have been opened prior to calling this function.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:warning.
:hp2.Only print plain text files with this function.:ehp2. printing any other kind of file 
could produce unexpected results.
:ewarning.

:h2 hide res=862.PrtGRxPrintFile - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.style
:pd.The style to print in&colon.
.br
"L" or empty = Left aligned
.br
"R" = Right aligned
"C" = Centred
"J" = Justified
:pt.file_name
:pd.fully qualified name of the file to print.
:eparml.

.***** PrtGRxPrintJPEG ********************************************************

:h2 res=2010.PrtGRxPrintJPEG
:i2 refid=FUNC.PrtGRxPrintJPEG
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2011.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2012.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2013.

:h2 hide res=2011.PrtGRxPrintJPEG - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2012.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2013.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=2014.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink.
:eul.

:h2 hide res=2012.PrtGRxPrintJPEG - Description
:xmp.
ok = PrtGRxPrintJPEG( printer, 
                      jpeg_file, 
                      lx, ly, 
                      tx, ty, 
                      th, 
                      border_color,
                      title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints a jpeg image from a file in the box given by the coordinates and framed in the given 
line style.
:p.The image will be stretched or compressed to fit and, if the printer supports colour, 
will be printed in colour.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2013.PrtGRxPrintJPEG - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.bitmap_file
:pd.Full path to the jpeg file you want to print
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.border_color
:pd.The colour of the line around the bitmap. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.title
:pd.The title text to be printed centered under the image
:eparml.

:h2 hide res=2014.PrtGRxPrintJPEG - Example
:xmp.

/**** Get the path to the jpeg **************************************/

jpg_name = 'c&colon.\jpeg\images\roses.jpg'

/**** Print the image with a blue border ****************************/

ok = PrtGRxPrintJPEG( printer, jpg_name, 40, 20, ,
                      130, 110, 200, "Blue", ,
                      'Fig 1. - Red Roses');
 
:exmp.
 
.***** PrtGRxPrintJustified ********************************************************
 
:h2 res=212.PrtGRxPrintJustified
:i2 refid=FUNC.PrtGRxPrintJustified
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=870.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=871.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=872.

:h2 hide res=870.PrtGRxPrintJustified - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=871.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=872.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=873.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=871.PrtGRxPrintJustified - Description
:xmp.
ok = PrtGRxPrintJustified( printer, 
                           face_name, 
                           points, 
                           string);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given text in the given font and point size justified between the declared 
margins of the page. All the parameters must be present. 
:p.The text will be wrapped over several lines if it is too long to fit on one line and 
the cursor is placed at the beginning of the next line at the end of the printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=872.PrtGRxPrintJustified - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=873.PrtGRxPrintJustified - Example
:xmp.
/********************************************************************/
/* Print a text justified on the page (or in a cell) in Helv 10     */
/********************************************************************/

ok = PrtGRxPrintJustified( printer, "Helvetica", 10, "whatever you want to print");

/**** The following text will have the same font and size ***********/

ok = PrtGRxPrintJustified( printer,,,"Here is some more");

:exmp.

.***** PrtGRxPrintLeft *********************************************************
 
:h2 res=230.PrtGRxPrintLeft
:i2 refid=FUNC.PrtGRxPrintLeft
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=880.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=881.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=882.

:h2 hide res=880.PrtGRxPrintLeft - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=881.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=882.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=883.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=881.PrtGRxPrintLeft - Description
:xmp.
ok = PrtGRxPrintLeft( printer, 
                      face_name, 
                      points, 
                      string);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given text in the given font and point size. All the parameters must be present. 
:p.The text will be wrapped over several lines if it is too long to fit on one line and the 
cursor is placed at the end of the text at the end of the printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
.br
Remember to add a space at the end of a string if you call this function several times, otherwise 
the texts will be "stuck" together.

:h2 hide res=882.PrtGRxPrintLeft - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=883.PrtGRxPrintLeft - Example
:xmp.
/********************************************************************/
/* Print a text on the page (or in a cell) in Helvetica 10          */
/********************************************************************/

ok = PrtGRxPrintLeft( printer, 'Helvetica', 10, 'whatever you want to print. ');

/**** The following text will have the same font and size ***********/

ok = PrtGRxPrintLeft( printer,,,'Here is some more');

:exmp.
 
.***** PrtGRxPrintLine *******************************************************
 
:h2 res=231.PrtGRxPrintLine
:i2 refid=FUNC.PrtGRxPrintLine
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=890.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=891.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=892.

:h2 hide res=890.PrtGRxPrintLine - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=891.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=892.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=893.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=891.PrtGRxPrintLine - Description
:xmp.
ok = PrtGRxPrintLine( printer, 
                      face_name, 
                      points, 
                      string);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given text in the given font and point size aligned on the left margin of the 
page. All the parameters must be present. 
:p.The text will be wrapped over several lines if it is too long to fit on one line and the 
cursor is placed at the beginning of the next line at the end of the printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=892.PrtGRxPrintLine - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=893.PrtGRxPrintLine - Example
:xmp.
/********************************************************************/
/* Print a text on the page (or in a cell) in Helvetica 10          */
/********************************************************************/

ok = PrtGRxPrintLine( printer, 'Helvetica', 10, 'whatever you want to print');

/**** The following text will have the same font and size ***********/

ok = PrtGRxPrintLine( printer,,,'Here is some more');

:exmp.

.***** PrtGRxPrintRight *****************************************************
 
:h2 res=213.PrtGRxPrintRight
:i2 refid=FUNC.PrtGRxPrintRight
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=910.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=911.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=912.

:h2 hide res=910.PrtGRxPrintRight - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=911.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=912.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=913.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=231.PrtGRxPrintLine:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:li.
:eul.

:h2 hide res=911.PrtGRxPrintRight - Description
:xmp.
ok = PrtGRxPrintRight( printer, 
                       face_name, 
                       points, 
                       string);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given text in the given font and point size right justified with relation to the 
right margin of the page. All the parameters must be present. 
:p.The text will be wrapped over several lines if it is too long to fit on one line and the 
cursor is placed at the beginning of the next line at the end of the printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=912.PrtGRxPrintRight - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=913.PrtGRxPrintRight - Example
:xmp.
/********************************************************************/
/* Print a text right aligned on the page (or in a cell)            */
/********************************************************************/

ok = PrtGRxPrintRight( printer, 'Helvetica', 10, 'whatever you want to print');

/**** The following text will have the same font and size ***********/

ok = PrtGRxPrintRight( printer,,,'Here is some more');

:exmp.
 
.***** PrtGRxPrintWinImage ****************************************************

:h2 res=2020.PrtGRxPrintWinImage
:i2 refid=FUNC.PrtGRxPrintWinImage
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2021.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2022.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2023.

:h2 hide res=2021.PrtGRxPrintWinImage - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2012.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2013.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=2014.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=202.PrtGRxPrintBox:elink.
:eul.

:h2 hide res=2022.PrtGRxPrintWinImage - Description
:xmp.
ok = PrtGRxPrintWinImage( printer, 
                          hwnd, 
                          lx, ly, 
                          tx, ty, 
                          th, 
                          border_color,
                          title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the image of a window from the screen in the box given by the coordinates and framed in 
the given line style.
:p.The image will be stretched or compressed to fit and, if the printer supports colour, 
will be printed in colour.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2023.PrtGRxPrintWinImage - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.hwnd
:pd.Numeric string representation of the handle of the window to print
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.border_color
:pd.The colour of the line around the bitmap. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.title
:pd.The title text to be printed centered under the image
:eparml.

:h2 hide res=2024.PrtGRxPrintWinImage - Example
:xmp.

ok = PrtGRxPrintWinImage( printer, hwnd, 40, 20, ,
                          130, 110, 200, "Blue", 
                          'Fig 1. - Window Image');
 
:exmp.

.***** PrtGRxReadJobProps ***********************************************

:h2 res=2092.PrtGRxReadJobProps
:i2 refid=FUNC.PrtGRxReadJobProps
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2093.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2094.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2095.

:h2 hide res=2093.PrtGRxReadJobProps - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2094.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2095.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=2096.PrtGRxSaveJobProps:elink.
:eul.

:h2 hide res=2094.PrtGRxReadJobProps - Description
:xmp.
ok = PrtGRxReadJobProps( printer, 
                         ini_file, 
                         AppName,
                         KeyName);
:exmp.
:font facename=Helv size=16x12.
:p.Reads the Job properties from an OS/2 ini file using the given application and key name. The printer Must be the same as the one used when the data was saved.
:p.:hp2.Return:ehp2.
:p.0 = Success
.br
1 = KeyName or AppName is invalid
.br
2 = Cannot read from inin file
.br
3 = The data in the ini file is for a different printer from that selected.

:h2 hide res=2095.PrtGRxReadJobProps - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.ini_file
:pd.mname of the ini file where the job properties atr read from. If this is an empty parameter 
then the job properties are read from OS2.INI.
:pt.AppName
:pd.Application name (see PrfQueryprofileData()). :hp2.This is case sensiive:ehp2.
:pt.KeyName
:pd.Key name (see PrfQueryprofileData()). :hp2.This is case sensiive:ehp2.
:eparml.

.***** PrtGRxResetColHeader ***************************************************

:h2 res=240.PrtGRxResetColHeader
:i2 refid=FUNC.PrtGRxResetColHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=920.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=921.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=922.

:h2 hide res=920.PrtGRxResetColHeader - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=921.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=922.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:eul.

:h2 hide res=921.PrtGRxResetColHeader - Description
:xmp.
ok = PrtGRxResetColHeader( printer, 
                           col_num, 
                           text);
:exmp.
:font facename=Helv size=16x12.
:p.Changes the text in the table header for the given column.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=922.PrtGRxResetColHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.col_num
:pd.Number of the column (1..n) whose header text you want to change
:pt.text
:pd.New header text for the column
:eparml.

.***** PrtGRxResetHeader ***************************************************

:h2 res=246.PrtGRxResetHeader
:i2 refid=FUNC.PrtGRxResetHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=930.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=931.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=932.

:h2 hide res=930.PrtGRxResetHeader - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=931.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=932.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:eul.

:h2 hide res=931.PrtGRxResetHeader - Description
:xmp.
ok = PrtGRxResetHeader( printer, 
                        numlines, 
                        text 
                        [, text]);
:exmp.
:font facename=Helv size=16x12.
:p.Redefines the text lines for the header printed on each page of document. The :hp2.text:ehp2. 
variable can contain :link reftype=hd res=120.Formatting Flags:elink..
:p.If you declare less lines than were originally defined for the header, the extra lines will 
be destroyed and cannot be re-used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:warning.
:hp2.You should only call this function after opening a print job to modify the header for the 
following pages:ehp2.
:ewarning.

:h2 hide res=932.PrtGRxResetHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.numlines
:pd.The number of lines in the header ( 1 to 5)
:pt.text
:pd.The text to printed on the line. there should be :hp2.numlines:ehp2. text variables. An 
empty variable will leave the original header text for that line.
:eparml.


.***** PrtGRxSaveJobProps ***********************************************

:h2 res=2096.PrtGRxSaveJobProps
:i2 refid=FUNC.PrtGRxSaveJobProps
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2097.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2098.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2099.

:h2 hide res=2097.PrtGRxSaveJobProps - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2098.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2099.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=2092.PrtGRxReadJobProps:elink.
:eul.

:h2 hide res=2098.PrtGRxSaveJobProps - Description
:xmp.
ok = PrtGRxSaveJobProps( printer, 
                         ini_file, 
                         AppName,
                         KeyName);
:exmp.
:font facename=Helv size=16x12.
:p.Saves the job properties for the current printer to the given ini file under the given application and key names.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=2099.PrtGRxReadJobProps - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.ini_file
:pd.mname of the ini file where the job properties atr read from. If this is an empty parameter 
then the job properties are read from OS2.INI.
:pt.AppName
:pd.Application name (see PrfQueryprofileData()). :hp2.This is case sensiive:ehp2.
:pt.KeyName
:pd.Key name (see PrfQueryprofileData()). :hp2.This is case sensiive:ehp2.
:eparml.

.***** PrtGRxSet ********************************************************

:h2 res=1060.PrtGRxSet
:i2 refid=FUNC.PrtGRxSet
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1061. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1062.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1063.
 
:h2 hide res=1061.PrtGRxSet - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1062.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1063.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1064.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1050.PrtGRxGet:elink.
:li.:link reftype=hd res=300.Printer properties:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=222.PrtGRxSetMargins:elink.
:li.:link reftype=hd res=223.PrtGRxSetPrinter:elink.
:eul.
 

:h2 hide res=1062.PrtGRxSet - Description
:xmp.
ok = PrtGRxGoto( printer, 
                 Property,
                 value);
:exmp.
:font facename=Helv size=16x12.
:p.Sets the value of the given property for the printer object.
:warning.
If you try to set a read-only(see :link reftype=hd res=300.Printer properties:elink.) an 
invalid function call error will be generated.
:ewarning.
:p.:hp2.Return:ehp2.
:p.A string represenation of the property.
:note.
.br
You can only set the fillowing properties&colon.
:ul compact.
:li.:link reftype=hd res=313.ColorEnabled:elink.
:li.:link reftype=hd res=314.Measures:elink.
:li.:link reftype=hd res=712.ShowProgress:elink.
:li.:link reftype=hd res=713.WordBreak:elink.
:eul.
:p.All the other :link reftype=hd res=300.printer properties:elink. are read only or set 
using library functions.

:h2 hide res=1063.PrtGRxSet - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object. 
:pt.Property
:pd.The name of the property. see :link reftype=hd res=300.Printer properties:elink.
:pt.value
:pd.The value that you want to assign to the property.
:eparml.

:h2 hide res=1064.PrtGRxSet - Example
:xmp.

/***** Set Word Breaking off ***********************************/

ok = PrtGRxSet( printer, "WordBreak", 0);

:exmp.

.***** PrtGRxSetFooter *****************************************************
 
:h2 res=219.PrtGRxSetFooter
:i2 refid=FUNC.PrtGRxSetFooter
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=940.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=941.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=942.

:h2 hide res=940.PrtGRxSetFooter - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=941.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=942.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=943.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=941.PrtGRxSetFooter - Description
:xmp.
ok = PrtGRxSetFooter( printer, 
                      facename, 
                      points, 
                      fill, 
                      line, 
                      text,
                      line_color,
                      fill_color,
                      text_color,
                      box_style);
:exmp.
:font facename=Helv size=16x12.
:p.Defines the footer printed on each page of document. The :hp2.text:ehp2. variable can contain 
:link reftype=hd res=120.Formatting Flags:elink..  If you don't define any colours, the default 
colour will be used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=942.PrtGRxSetFooter - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.facename
:pd.name of the font used in printing the footer text
:pt.points
:pd.Point size for the font
:pt.fill
:pd.Fill style for the footer area (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.line
:pd.Line thickness for a box surrounding the footer
:pt.text
:pd.Text to be printed in the footer
:pt.line_color
:pd.The colour of the line around the header. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.fill_color
:pd.The colour used for the foregound of the fill pattern. One of the colour strings defined 
by :hp2.VX-REXX:ehp2.
:pt.text_color
:pd.The colour for printing the text. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.box_style
:pd.A combination of the following flags that defines which sides of the box are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=943.PrtGRxSetFooter - Example
:xmp.
/****************************************************************/
/* Set the footer with the page number right justified and the  */
/* document title left aligned with an unfilled blue box around */
/* it and with black text.                                      */
/****************************************************************/

ok = PrtGRxSetFooter( printer, 'Helvetica', 8, 0, 14, '$|$rpage $#', "Blue", , "Black");
:exmp.

.***** PrtGRxSetHeader *****************************************************
 
:h2 res=220.PrtGRxSetHeader
:i2 refid=FUNC.PrtGRxSetHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=950.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=951.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=952.

:h2 hide res=950.PrtGRxSetHeader - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=951.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=952.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=953.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=246.PrtGRxResetHeader:elink.
:li.:link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:eul.

:h2 hide res=951.PrtGRxSetHeader - Description
:xmp.
ok = PrtGRxSetHeader( printer, 
                      numlines, 
                      text 
                      [, text]);
:exmp.
:font facename=Helv size=16x12.
:p.Defines the text lines for the header printed on each page of document. The :hp2.text:ehp2. 
variable can contain :link reftype=hd res=120.Formatting Flags:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0). FALSE is also returned if there has been no previous 
call to :link reftype=hd res=221.PrtGRxSetHeaderMode:elink..
:warning.
:hp2.You MUST make a call to the :link reftype=hd res=221.PrtGRxSetHeaderMode:elink. function before 
calling this function:ehp2.
:ewarning.

:h2 hide res=952.PrtGRxSetHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.numlines
:pd.The number of lines in the header ( 1 to 5)
:pt.text
:pd.The text to printed on the line. there should be :hp2.numlines:ehp2. text variables
:eparml.

:h2 hide res=953.PrtGRxSetHeader - Example
:xmp.
/****************************************************************/
/* Set the header with the doc title on the first line centred, */
/* the date on the second line right justified and some other   */
/* text. There are 3 lines in the header.                       */
/****************************************************************/

ok = PrtGRxSetHeader( printer, 3, ,
                       "$c|",, 
                       "$lADD Consulting (CH)$r@",,
                       'Demo for PrtGraph REXX Library for VX-REXX');

:exmp.
 
.***** PrtGRxSetHeaderLineFont ************************************************

:h2 res=235.PrtGRxSetHeaderLineFont
:i2 refid=FUNC.PrtGRxSetHeaderLineFont
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=960.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=961.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=962.

:h2 hide res=960.PrtGRxSetHeaderLineFont - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=961.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=962.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=963.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:eul.

:h2 hide res=961.PrtGRxSetHeaderLineFont - Description
:xmp.
ok = PrtGRxSetHeaderLineFont( printer, 
                              linenum, 
                              font, 
                              points);
:exmp.
:font facename=Helv size=16x12.
:p.Sets the font for one line in the header to a different size or font from that defined 
in :link reftype=hd res=221.PrtGRxSetHeaderMode:elink.. 
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0). FALSE is also returned if there has been no previous 
call to :link reftype=hd res=221.PrtGRxSetHeaderMode:elink. and :link reftype=hd 
res=220.PrtGRxSetHeader:elink..
:warning.
:hp2.You MUST make a call to the :link reftype=hd res=221.PrtGRxSetHeaderMode:elink. 
and :link reftype=hd res=220.PrtGRxSetHeader:elink. functions before calling this function:ehp2.
:ewarning.

:h2 hide res=962.PrtGRxSetHeaderLineFont - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.linenum
:pd.The line number in the header whose font is to be set
:pt.font
:pd.The font to use for printing the line
:pt.points
:pd.The point size to be used for printing
:eparml.

:h2 hide res=963.PrtGRxSetHeaderLineFont - Example
:xmp.

/****************************************************************/
/* Print the header on all the pages with default 10 pt         */
/* Helvetica bold, a .05mm line around and halftone fill.       */
/****************************************************************/

ok = PrtGRxSetHeaderMode( printer, 1, 'Helvetica Bold', 10, 8, 28, 1);

/****************************************************************/
/* Set the header with the doc title on the first line centred, */
/* the date on the second line right justified and some other   */
/* text. There are 3 lines in the header.                       */
/****************************************************************/

ok = PrtGRxSetHeader( printer, 3, ,
                       "$c|",, 
                       "$lADD Consulting (CH)$r@",,
                       'Demo for PrtGraph REXX Library for VX-REXX');

/****************************************************************/
/* Change the point size for the first line.                    */
/****************************************************************/

ok = PrtGRxSetHeaderLineFont( printer, 1, , 12);

/****************************************************************/
/* Change the font and point size for the third line.           */
/****************************************************************/

ok = PrtGRxSetHeaderLineFont( printer, 3, "Helvetica", 8);

:exmp.

.***** PrtGRxSetHeaderMode *************************************************
 
:h2 res=221.PrtGRxSetHeaderMode
:i2 refid=FUNC.PrtGRxSetHeaderMode
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=970.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=971.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=972.

:h2 hide res=970.PrtGRxSetHeaderMode - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=971.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=972.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=973.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=971.PrtGRxSetHeaderMode - Description
:xmp.
ok = PrtGRxSetHeaderMode( printer, 
                          print, 
                          facename, 
                          points, 
                          fill, 
                          line, 
                          all_pages,
                          line_color,
                          fill_color,
                          text_color,
                          box_style);
:exmp.
:font facename=Helv size=16x12.
:p.Define the way the header is printed. Unless you specify different fonts for each line 
with :link reftype=hd res=235.PrtGRxSetHeaderLineFont:elink., the text will be printed in the font 
and point size defined with this function. If you don't define any colours, the default colour 
will be used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=972.PrtGRxSetHeaderMode - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.print
:pd.0 = Never print the header
.br
1 = print the header
:pt.facename
:pd.name of the default font used in printing the header text.
:pt.points
:pd.Default point size for printing the header.
:pt.fill
:pd.Fill style for the header area (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.line
:pd.Line thickness for a box surrounding the header
:pt.all_pages
:pd.0 = print header on first page only
.br
1 = print header on all the pages
:pt.line_color
:pd.The colour of the line around the header. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.fill_color
:pd.The colour used for the foregound of the fill pattern. One of the colour strings defined 
by :hp2.VX-REXX:ehp2.
:pt.text_color
:pd.The colour for printing the text. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.box_style
:pd.A combination of the following flags that defines which sides of the box are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=973.PrtGRxSetHeaderMode - Example
:xmp.

/****************************************************************/
/* Print the header on all the pages in 10 pt Helvetica bold    */
/* with a .05mm blue line around and filled with cyan halftone. */
/****************************************************************/

ok = PrtGRxSetHeaderMode( printer, 1, 'Helvetica Bold', 10, 8, 28, 1, "Blue", "Cyan");

:exmp.

.***** PrtGRxSetMargins ****************************************************
 
:h2 res=222.PrtGRxSetMargins
:i2 refid=FUNC.PrtGRxSetMargins
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=980.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=981.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=982.

:h2 hide res=980.PrtGRxSetMargins - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=981.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=982.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=983.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=219.PrtGRxSetFooter:elink.
:li.:link reftype=hd res=220.PrtGRxSetHeader:elink.
:li.:link reftype=hd res=221.PrtGRxSetHeaderMode:elink.
:eul.

:h2 hide res=981.PrtGRxSetMargins - Description
:xmp.
ok = PrtGRxSetMargins( printer, 
                       lm, rm, 
                       tm, bm, 
                       pb, ps, 
                       line_color, 
                       fill_color,
                       box_style);
:exmp.
:font facename=Helv size=16x12.
:p.Defines the printing margins for the job and whether the printing area has a border and a 
fill style. If you don't define any colours, the default colour will be used.
:p.The border, if defined, will be printed just outside the margins.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=982.PrtGRxSetMargins - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.lm
:pd.Left margin in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from page edge
:pt.rm
:pd.Right margin in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from page edge 
:pt.tm
:pd.Top margin in millimeteres from page edge
:pt.bm
:pd.Bottom margin in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from page edge 
:pt.pb
:pd.Thickness of line making a border around the page
:pt.ps
:pd.Fill style for the page (see :link reftype=hd res=135.Fill Syles:elink.)
:pt.line_color
:pd.The colour of the line around the header. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.fill_color
:pd.The colour used for the foregound of the fill pattern. One of the colour strings defined 
by :hp2.VX-REXX:ehp2.
:pt.box_style
:pd.A combination of the following flags that defines which sides of the box are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=983.PrtGRxSetMargins - Example
:xmp.
/****************************************************************/
/* Set the margins to left 25mm right 20mm top 20mm bottom 25mm */
/* and set the page to filled with green halftone with a black  */
/* 1mm border.                                                  */
/****************************************************************/

ok = PrtGRxSetMargins( printer, 25, 20, 20, 25, 56, 8, "Black", "Green");
 
:exmp.
 
.***** PrtGRxSetPrinter ****************************************************
 
:h2 res=223.PrtGRxSetPrinter
:i2 refid=FUNC.PrtGRxSetPrinter
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=990.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=991.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=992.

:h2 hide res=990.PrtGRxSetPrinter - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=991.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=992.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=218.PrtGRxPrinterList:elink.
:li.:link reftype=hd res=216.PrtGRxOpenPrintJob:elink.
:eul.

:h2 hide res=991.PrtGRxSetPrinter - Description
:xmp.
ok = PrtGRxSetPrinter( printer, 
                       idx);
:exmp.
:font facename=Helv size=16x12.
:p.For programs that do not use :link reftype=hd res=217.PrtGRxPrinterDialog:elink., the printer MUST 
be set using this function if you do not want to use the default printer. The index refers to the 
position of the chosen printer name in the the stem variable returned by :link reftype=hd 
res=218.PrtGRxPrinterList:elink. and is 1 based.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=992.PrtGRxSetPrinter - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.idx
:pd.Index of the printer in the list returned by :link reftype=hd res=218.PrtGRxPrinterList:elink. If 
this variable is missing or set to 0, the default printer will be selected.
:eparml.


.***** PrtGRxSetProgressTexts *************************************************

:h2 res=715.PrtGRxSetProgressTexts
:i2 refid=FUNC.PrtGRxSetProgressTexts
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1000.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1001.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1002.

:h2 hide res=1000.PrtGRxSetProgressTexts - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1001.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1002.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=712.ShowProgress:elink.
:eul.

:h2 hide res=1001.PrtGRxSetProgressTexts - Description
:xmp.
ok = PrtGRxSetProgressTexts( printer, 
                             "texts.");
:exmp.
:font facename=Helv size=16x12.
:p.This function allows to customise the Progress dialog. Any of the input stem parameter fields 
may be left blank, in which case they assume the defaut values.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1002.PrtGRxSetProgressTexts - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.texts.
:pd.Stem variable containing the new title and texts for the progress dialog.
:lm margin=5.
:parml compact tsize=15 break=none.
:pt.texts.0
:pd.Must be 5
:pt.texts.1
:pd.New text for the title of the dialog. By default this is&colon. "Printing - Progress".
:pt.texts.2
:pd.New text for the 1st line in the dialog. By default this is the document name.
:pt.texts.3
:pd.New text for the 2nd line in the dialog. by default this test is&colon. "Printing page %u". 
If you replace this text, you must include the :hp2.%u:ehp2. flag for the page number that is 
printing.
:pt.texts.4
:pd.New text for the 3rd line in the dialog. By default this is the name of the printer where 
he job is printing.
:pt.texts.5
:pd.New text for the :hp2.Abort:ehp2. button in the dialog.
:eparml.
:lm margin=1.
:eparml.

.***** PrtGRxStartCol ******************************************************
 
:h2 res=224.PrtGRxStartCol
:i2 refid=FUNC.PrtGRxStartCol
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1010.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1011.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1012.

:h2 hide res=1010.PrtGRxStartCol - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1011.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1012.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:eul.

:h2 hide res=1011.PrtGRxStartCol - Description
:xmp.
ok = PrtGRxStartCol( printer, 
                     column);
:exmp.
:font facename=Helv size=16x12.
:p.Instructs the program to direct all text printing calls to print within the borders set for 
the column.
:p.Columns are numbers start at 1.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
.br
A PrtGRxTable must have been previously declared.

:h2 hide res=1012.PrtGRxStartCol - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.column
:pd.Number of the column to start printing.
:eparml.

.***** PrtGRxStartRow ******************************************************
 
:h2 res=225.PrtGRxStartRow
:i2 refid=FUNC.PrtGRxStartRow
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1020.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1021.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1022.

:h2 hide res=1020.PrtGRxStartRow - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1021.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1022.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=226.PrtGRxStartTable:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=206.PrtGRxEndRow:elink.
:eul.

:h2 hide res=1021.PrtGRxStartRow - Description
:xmp.
ok = PrtGRxStartRow( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Instructs the program that a new row in a table is to be started. All printing commands 
following this call will be directed into the last column that was declared. You :hp2.MUST:ehp2. 
follow this call by a call to :link reftype=hd res=224.PrtGRxStartCol:elink. otherwise you may 
generate an Access Violation.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
.br
A table must have been previously declared.

:h2 hide res=1022.PrtGRxStartRow - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

.***** PrtGRxStartTable ****************************************************
 
:h2 res=226.PrtGRxStartTable
:i2 refid=FUNC.PrtGRxStartTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1030.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1031.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1032.

:h2 hide res=1030.PrtGRxStartTable - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1031.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1032.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1033.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=200.PrtGRxDefineTable:elink.
:li.:link reftype=hd res=225.PrtGRxStartRow:elink.
:li.:link reftype=hd res=224.PrtGRxStartCol:elink.
:li.:link reftype=hd res=206.PrtGRxEndRow:elink.
:li.:link reftype=hd res=207.PrtGRxEndTable:elink.
:li.:link reftype=hd res=240.PrtGRxResetColHeader:elink.
:eul.

:h2 hide res=1031.PrtGRxStartTable - Description
:xmp.
ok = PrtGRxStartTable( printer, 
                       fill, 
                       line, 
                       numcols, 
                       lm, 
                       width 
                       [, width]);
:exmp.
:font facename=Helv size=16x12.
:p.Defines a table for printing. If there are not the right number of :hp2.lm, rm:ehp2. pairs 
the function will return FALSE.
:p.This call only prepares the internal structures for handling a table, to start printing 
the table you must call :link reftype=hd res=225.PrtGRxStartRow:elink. and :link reftype=hd 
res=224.PrtGRxStartCol:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1032.PrtGRxStartTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.fill
:pd.Fill style used for the table. This applies to all the cells.
:pt.line
:pd.Thickness of the separator lines for the table in TWIPS
:pt.numcols
:pd.The number of columns in the table; There MUST be a :hp2.width:ehp2. variable for each column
:pt.lm
:pd.Left edge of the table in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property from the left margin
:pt.width
:pd.Width of the column in millimetres or 1/10 inch depending on the :link reftype=hd 
res=314.Measures:elink. property. There must be :hp2.numcols:ehp2. width variables
:eparml.

:h2 hide res=1033.PrtGRxStartTable - Example
:xmp.
/************************************************************************/
/* Declare a table with no fill style, 0.5 mm separator lines and       */
/* 3 columns                                                            */
/************************************************************************/

ok = PrtGRxStartTable( printer, 0, 24, 3, 30, 30, 45, 40);

if rcy then do

    /**** Start printing in the table **********************************/
    
    ok = PrtGRxStartRow( printer);
    
    /**** Start printing in column 2 ***********************************/
    
    ok = PrtGRxStartCol( printer, 1);
    ok = PrtGRxPrintRight( printer, 'Helvetica', 10, textvar);
    
    /**** Start printing in column 2 ***********************************/
    
    ok = PrtGRxStartCol( printer, 2);
    ok = PrtGRxPrintJustified( printer, 'Helvetica Bold', 10, textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    
    /**** Start printing in column 3 ***********************************/
    
    ok = PrtGRxStartCol( printer, 3);
    ok = PrtGRxPrintCentered( printer, 'Helvetica Bold', 14, textvar);
    
    /**** Print the row ************************************************/
    
    ok = PrtGRxEndRow( printer);
    
    /**** Start a new row **********************************************/
    
    ok = PrtGRxStartRow( printer);
    ok = PrtGRxStartCol( printer, 1);
    ok = PrtGRxPrintRight( printer, 'Times New Roman', 10, textvar);
    ok = PrtGRxStartCol( printer, 2);
    ok = PrtGRxPrintLeft( printer, 'Helvetica Bold', 10, textvar);
    ok = PrtGRxPrintCentered( printer,,,textvar);
    ok = PrtGRxPrintJustified( printer,,,textvar);
    ok = PrtGRxPrintRight( printer,,,textvar);
    ok = PrtGRxStartCol( printer, 3);
    ok = PrtGRxPrintJustified( printer, 'Times New Roman', 8, textvar);
    
    /**** Print the row ************************************************/
    
    ok = PrtGRxEndRow( printer);
    
    /**** Destroy the table data structures ****************************/
    
    ok = PrtGRxEndTable( printer);
end

:exmp.
 
.***** PrtGRxPrintLine *******************************************************
 
:h2 res=2070.PrtGRxStringLength
:i2 refid=FUNC.PrtGRxStringLength
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=2071.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=2072.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2073.

:h2 hide res=2071.PrtGRxStringLength - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=2072.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=2073.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=2074.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=203.PrtGRxPrintCentered:elink.
:li.:link reftype=hd res=212.PrtGRxPrintJustified:elink.
:li.:link reftype=hd res=213.PrtGRxPrintRight:elink.
:li.:link reftype=hd res=230.PrtGRxPrintLeft:elink.
:li.:link reftype=hd res=234.PrtGRxFontDialog:elink.
:eul.

:h2 hide res=2072.PrtGRxStringLength - Description
:xmp.
len = PrtGRxStringLength( printer, 
                          face_name, 
                          points, 
                          string);
:exmp.
:font facename=Helv size=16x12.
:p.Returns the length of the given text in the given font and point size aligned on the left margin 
of the page or cell. All the parameters must be present. 
:p.:hp2.Return:ehp2.
:p.-1 if the string will not fit on line or the in the current cell, otherwise the length of the 
string in the current :link reftype=hd res=314.Measures:elink..

:h2 hide res=2073.PrtGRxStringLength - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be measured.
:eparml.

:h2 hide res=2074.PrtGRxStringLength - Example
:xmp.

/********************************************************************/
/* Print a text on the page (or in a cell) if it fits               */
/********************************************************************/
font = 'Helvetica'
pts = 10
text = 'whatever you want to print'
len = PrtGRxStringLength( printer, font, pts, text)
if len >= 0 then 
    ok = PrtGRxPrintLine( printer, font, pts, text);

:exmp.

.***** PrtGRxTab *******************************************************
 
:h2 res=227.PrtGRxTab
:i2 refid=FUNC.PrtGRxTab
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1040.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1041.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1042.

:h2 hide res=1040.PrtGRxTab - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1041.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1042.Parameters:elink. 
:eul.

:h2 hide res=1041.PrtGRxTab - Description
:xmp.
ok = PrtGRxTab( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Move to the next tab position on the line. PrtGRxTabs are set when a print job is opened and 
are placed every 10 millimetres or 1/2 inch depending on the :link reftype=hd 
res=314.Measures:elink. property starting at the left margin.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1042.PrtGRxTab - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

.***** PrtGRxTerm ********************************************************

:h2 res=1080.PrtGRxTerm
:i2 refid=FUNC.PrtGRxTerm
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1081. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1082.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1083.
 
:h2 hide res=1081.PrtGRxTerm - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1082.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1083.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1083.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1070.PrtGRxInit:elink.
:eul.
 
:h2 hide res=1082.PrtGRxTerm - Description
:xmp.
ok = PrtGRxTerm( printer);
:exmp.
:font facename=Helv size=16x12.
:p.Destroys the given printer printer object.
:p.:hp2.Return:ehp2.
:p.0.

:h2 hide res=1083.PrtGRxTerm - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.printer
:pd.Identifier for the printer object from :link reftype=hd res=1070.PrtGRxInit:elink.. 
:eparml.

:h2 hide res=1084.PrtGRxTerm - Example
:xmp.

printer = PrtGRxTerm( printer);

:exmp.

:euserdoc.

.************************************************************************
.*
.*  (c)1996 ADD Consulting
.*
.*  END OF FILE.
.*
.* ***********************************************************************
