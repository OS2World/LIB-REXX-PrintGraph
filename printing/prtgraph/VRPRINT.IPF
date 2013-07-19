.* Version of 95/06/14 by Peter Kanis
.************************************************************************
.*  Project     : VRPRINT                 Date    : 95/06/08            *
.*  Module      : Guide                                                 *
.*  Filename    : vrprint.ipf             Author  : Peter Kanis         *
.************************************************************************
 
:userdoc.
:docprof toc=123.
:title.VRPrinter v2.3 Programming Reference

.***** Introduction *****************************************************

:h1 res=100.VRPrinter Object
:i1 id=INTRO.VRPrinter Object
:font facename=Helv size=16x12.

:p.The :hp2.VRPrinter Object:ehp2. for :hp2.VX-REXX*:ehp2. gives you access to complex graphic 
printing functionality with :hp2.VX-REXX v2.1:ehp2. or greater.

:p.With this library you will be able to create professional style reports and outputs for 
your :hp2.VX-REXX:ehp2. programs with images, boxes and text that can be justified, right or 
left aligned or centred. and with documents that use up to 25 different font faces.

:p.The :hp2.VRPrinter Object:ehp2. allows you to define headers and footers and gives you 
access to a list of the printers connected to your work-station, their :hp2.Job 
Properties:ehp2. dialogs and their available printing fonts.

:p.:hp2.*:ehp2. VX-REXX is a registered trade mark of :hp2.Watcom International 
Corporation:ehp2..

:h2 res=101.Whats new in version 2.3
:i2 refid=INTRO.Whats new in version 2.3
:font facename=Helv size=16x12.

:p.The :hp2.VRPrinter Object:ehp2. has been ported to :hp2.VX-REXX:ehp2. version 2.1. This 
means that if you still have :hp2.VX-REXX:ehp2. version 2.0, you should stay with version 
1.x of the :hp2.VRPrinter Object:ehp2..

:p.In version 2.3 we have introduced the following new properties&colon.
:lm margin=5.
:ul compact.
:li.:link reftype=hd res=1080.XPosTwips:elink. 
:li.:link reftype=hd res=1083.YPosTwips:elink.
:eul.
:lm margin=1.

:p.In version 2.3 we have introduced the following new methods&colon.
:lm margin=5.
:ul compact.
:li.:link reftype=hd res=1120.DrawLine:elink.
:li.:link reftype=hd res=1090.GotoTab:elink.
:li.:link reftype=hd res=1100.GotoX:elink.
:li.:link reftype=hd res=1110.GotoY:elink.
:eul.
:lm margin=1.

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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=222.SetMargins:elink.
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

:p.When you :link reftype=hd res=410.register:elink. the :hp2.VRPrinter Object:ehp2. you will be sent a 
registered version of the DLL by e-mail. This version has the "nag" popup removed and you have 
the right to freely distribute software that includes the DLL.

:p.If you are satisfied with the :hp2.VRPrinter Object:ehp2. we ask you to freely distribute the 
shareware version to your freinds and colleagues.

:p.If you have any suggestions for enhancements or find any bugs in the software please 
contact us at one of our :link reftype=hd res=600.Contact Addresses:elink.

.***** Registering  *****************************************************

:h2 res=410.Registering your license
:i2 refid=INTRO.Registering your license
:font facename=Helv size=16x12.

:p.VRPrinter is a "Shareware software program" and is provided at no charge to the user for 
evaluation. Feel free to share it with your friends, but please do not give it away altered or 
as part of another system. The essence of "user-supported" software is to provide personal 
computer users with quality software without high prices, and yet to provide incentive for 
programmers to continue to develop new products. If you find this program useful and find 
that you are using VRPrinter and continue to use VRPrinter after a reasonable trial period 
of 30  days, you must make a registration payment of $45.00 to ADD Consulting (CH).
:p.If you have already registered either PRTGRAPH for REXX or PRTGRAFC for C/C++ you can 
register for $20.00. :p.You can register through the :hp2.CompuServe:ehp2. Shareware 
Registration facility&colon.
:lm margin=5.
:p.GO SWREG registration Number 6200 for new registrations
:p.GO SWREG registration Number 6330 for registered owners of PrtGraph for C or the PrtGraph C++ 
Class Library
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

:h2 res=420.Distributing the VRPrinter Object
:i2 refid=INTRO.Distributing the VRPrinter Object
:font facename=Helv size=16x12.

:p.Anyone distributing the :hp2.VRPrinter Object:ehp2. for any kind of remuneration must first contact 
ADD Consulting (CH) at our :link reftype=hd res=600.address:elink. below for authorization. 
This authorization will be automatically granted to distributors recognized by the (ASP) as 
adhering to its guidelines for shareware distributors, and such distributors may begin 
offering VRPrinter immediately, however ADD Consulting (CH) should still be advised so that 
the distributor can be kept up-to-date with the latest version of VRPrinter. 

:p.:hp2.Registered users are free to distribute programs that use the the :hp2.VRPrinter Object:ehp2. with 
no additional run-time fees:ehp2..

.***** Address **********************************************************

:h2 res=600.Contact Address
:i2 refid=INTRO.Contact Address
:font facename=Helv size=16x12.

:p.You can contact ADD Consulting at the addresses below, at our Web site 
:hp2.http&colon.//www.addc.com:ehp2. or on the :hp2.OS/2 Other Vendors:ehp2. 
on :hp2.CompuServe:ehp2. (GO OS2AVEN).
:lm margin=5.
:lm margin=5.
:lines.:font facename=Courier size=18x12.
ADD Consulting (CH)
Mr. Peter Kanis
Rauenmattenweg 45F
CH-3225 Muentschemier
Switzerland

Until November, 9 1996
Tel&colon. +41 (0)32 83 4581
Fax&colon. +41 (0)32 83 4584

After November, 9 1996

Tel&colon. +41 (0)32 313 4581
Fax&colon. +41 (0)32 313 4584

CompuServe&colon. 100275,350 (Peter Kanis)
INTERNET&colon. kanis@addc.com

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

:p.Users of :hp1.VRPrinter:ehp1. shall accept this disclaimer of warranty&colon.

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

:p.Included in this package is a demonstration program in :hp2.VX-REXX:ehp2. and its source code. 

The demo shows you many of the possibilities offered by the object, but the limits are set 
by your imagination.

:artwork name='t:\vxodk\projects\vrprint\rc\demo.bmp' align=left.
:p.:hp2.Figure&colon. Demo Program.:ehp2.

.***** Setting up a print job *******************************************

:h2 res=120.Setting up a print job
:i2 refid=INTRO.Setting up a print job
:font facename=Helv size=16x12.

:p.Setting up a print job requires several steps&colon.
:lm margin=5.
:ul compact.
:li.Include a Printer object on the main window
:li.Choose a printer with the :link reftype=hd res=217.PrinterDialog:elink. method
:li.If necessary set the job properties with the :link reftype=hd res=211.JobProperties:elink. method
:li.Set the page margins with the :link reftype=hd res=222.SetMargins:elink. method
:li.Set up the aspect of header with the :link reftype=hd res=221.SetHeaderMode:elink. method
:li.Set up any header text with the :link reftype=hd res=220.SetHeader:elink. method
:li.Change any fonts for the lines in the header with the :link reftype=hd 
res=235.SetHeaderLineFont:elink. method
:li.Set up any footer with the :link reftype=hd res=219.SetFooter:elink. method
:li.Open the print job with the :link reftype=hd res=216.OpenPrintJob:elink. method
:li.Print your texts, tables, bitmaps etc..
:li.Close the print job with the :link reftype=hd res=204.ClosePrintJob:elink. method
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
If you wish to print several documents concurrently (i.e. in parrallel threads or windows) 
you must include a printer object on each window.
:ewarning.

.***** Formatting Characters ********************************************

:h2 res=130.Formatting Characters
:i2 refid=INTRO.Formatting Characters
:font facename=Helv size=16x12.

:p.To help define header and footer texts with :link reftype=hd res=219.SetFooter:elink. and 
:link reftype=hd res=220.SetHeader:elink. the following special formatting flags are 
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
:c.Ý or |
:c.Insert the title of the document (see :link reftype=hd res=216.OpenPrintJob:elink.)
:etable.

:font facename=Helv size=16x12.
:p.:hp2.Example:ehp2.
:p.'$Ý$rpage $#' would give&colon.
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

:p.Several of the VRPrinter methods refer to a fill style. You can see the effect of a style 
for any printer by running the :link reftype=hd res=105.DEMO program:elink. and printing the 
:hp2.box styles:ehp2. option. The numbers you pass to any of these methods is translated into 
a :hp2.PATSYM_?????:ehp2. constant, and the output is, to a certain extent, device dependent.
For an idea of what you will obtain see the pictures below.
:p.
:artwork name='w:\prtgraph\bitmaps\styles1.bmp' align=left.
:artwork name='w:\prtgraph\bitmaps\styles2.bmp' align=left.


.***** Printing on a separate thread ************************************

:h2 res=703.Printing on a separate thread
:i2 refid=PROPS.Printing on a separate thread
:font facename=Helv size=16x12.

:p.Printing is often a lengthy operation and is a good candidate for multi-threading. However, 
the :hp2.Printer Object:ehp2. needs to be present on a Window. The technique to use if you 
want to write a :hp2.code file:ehp2. to perform the actual printing operation in your 
:hp2.VX-REXX:ehp2. program is this

:p.Start a thread passing the "Self" property of the :hp2.Printer Object:ehp2. NOT THE 
NAME&colon.
:font facename=Courier size=16x12.
:xmp.
PB_Print_Click: 
    somSelf = VRGet( "PRT_1", "Self");
    threadID = VRMethod( "Application", "StartThread", "printit", somSelf )
return
:exmp.
:font facename=Helv size=16x12.
:p.In the :hp2.main:ehp2. section of :hp2.printit.vrx:ehp2.&colon.
:font facename=Courier size=16x12.
:xmp.
Main:
    signal on halt

    parse arg somSelf
    .
    .
exit
:exmp.
:font facename=Helv size=16x12.
:p.When calling VRPrinter methods use :hp2.somSelf:ehp2. as the object name&colon.
:font facename=Courier size=16x12.
:xmp.
PrintStuff: 

    /***** Open the print job *******************************************/
    
    ok = VRMethod( somSelf, "OpenPrintJob", 'Test Printing');

    /***** Print out with text, pictures or anything ********************/
    
    ok = VRMethod( somSelf, "PrintLine", facename, fnt, text);
    ok = VRMethod( somSelf, "PrintLine", , fnt, '');
    .
    .
    .

    /***** Close the job ************************************************/
    
    ok = VRMethod( somSelf, "ClosePrintJob");
    
return
:exmp.
:font facename=Helv size=16x12.
:note.This technique can be used to access methods and properties of many other objects in 
:hp2.VX-REXX:ehp2..

.***** Properties *******************************************************

:h1 res=300.VRPrinter properties
:i1 id=PROPS.VRPrinter properties
:font facename=Helv size=16x12.
:p.The following sections describe the properties specific to the :hp2.VRPrinter Object:ehp2..
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
:li.:link reftype=hd res=1070.XPos:elink.
:li.:link reftype=hd res=1073.YPos:elink.
:li.:link reftype=hd res=1080.XPosTwips:elink.
:li.:link reftype=hd res=1083.YPosTwips:elink.
:eul.
:lm margin=1.

:p.The :hp2.VRPrinter Object:ehp2. inherits its properties from the Descriptive Text object 
in :hp2.VX-REXX:ehp2.. The behaviour of the following properties is the standard (see VX-REXX programming 
guide for Descriptive Text)&colon.
:lm margin=5.
:ul compact.
:li.:link reftype=launch object='view.exe' data='a2z Autosize'.Autozize:elink.
:li.:link reftype=launch object='view.exe' data='a2z BackColor'.BackColor:elink.
:li.:link reftype=launch object='view.exe' data='a2z Caption'.Caption:elink.
:li.:link reftype=launch object='view.exe' data='a2z ClassName'.ClassName:elink.
:li.:link reftype=launch object='view.exe' data='a2z ClipSiblings'.ClipSiblings:elink.
:li.:link reftype=launch object='view.exe' data='a2z Enabled'.Enabled:elink.
:li.:link reftype=launch object='view.exe' data='a2z FirstChild'.FirstChild:elink.
:li.:link reftype=launch object='view.exe' data='a2z Font'.Font:elink.
:li.:link reftype=launch object='view.exe' data='a2z ForeColor'.ForeColor:elink.
:li.:link reftype=launch object='view.exe' data='a2z Height'.Height:elink.
:li.:link reftype=launch object='view.exe' data='a2z HelpTag'.HelpTag:elink.
:li.:link reftype=launch object='view.exe' data='a2z HelpText'.HelpText:elink.
:li.:link reftype=launch object='view.exe' data='a2z HintText'.HintText:elink.
:li.:link reftype=launch object='view.exe' data='a2z Justification'.Justification:elink.
:li.:link reftype=launch object='view.exe' data='a2z HWnd'.HWnd:elink.
:li.:link reftype=launch object='view.exe' data='a2z Left'.Left:elink.
:li.:link reftype=launch object='view.exe' data='a2z Name'.Name:elink.
:li.:link reftype=launch object='view.exe' data='a2z Painting'.Painting:elink.
:li.:link reftype=launch object='view.exe' data='a2z Parent'.Parent:elink.
:li.:link reftype=launch object='view.exe' data='a2z Self'.Self:elink.
:li.:link reftype=launch object='view.exe' data='a2z Sibling'.Sibling:elink.
:li.:link reftype=launch object='view.exe' data='a2z SiblingOrder'.SiblingOrder:elink.
:li.:link reftype=launch object='view.exe' data='a2z Top'.Top:elink.
:li.:link reftype=launch object='view.exe' data='a2z UserData'.UserData:elink.
:li.:link reftype=launch object='view.exe' data='a2z VertJustification'.VertJustification:elink.
:li.:link reftype=launch object='view.exe' data='a2z Visible'.Visible:elink.
:li.:link reftype=launch object='view.exe' data='a2z Width'.Width:elink.
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
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:eul.

:h2 hide res=721.CurrentDevice - Description
:font facename=Helv size=16x12.
:p.The name of the printer device selected for the printer object. This is the same as the 
Physical Name seen in printer settings notebook. This is the name used for printing charts.
:warning.
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:eul.

:h2 hide res=723.CurrentPrinter - Description
:font facename=Helv size=16x12.
:p.The name of the printer selected for the printer object. This is the same as the name seen on 
the desktop printer object.
:warning.
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:eul.

:h2 hide res=725.DefaultPrinter - Description
:font facename=Helv size=16x12.
:p.The name of the default system printer. This is the same as the name seen on the desktop 
printer object.
:warning.
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
:li.String
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=222.SetMargins:elink.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=204.ClosePrintJob:elink.
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:eul.

:h2 hide res=755.Printing - Description
:font facename=Helv size=16x12.
:p.This property is set to 1 when a print job is open on the printer object. Otherwise this 
property is set to 0.
:warning.
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
:li.:link reftype=hd res=715.SetProgressTexts:elink.
:eul.

:h2 hide res=761.ShowProgress - Description
:font facename=Helv size=16x12.
:p.This is boolean property that when set enables the progress dialog to pop up when a 
job is printing.
:artwork name='t:\vxodk\projects\vrprint\rc\progress.bmp' align=left.
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
This property is read only and cannot be set with a call to VRSet.
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
This property is read only and cannot be set with a call to VRSet.
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
:p.The :hp2.WordBreak:ehp2. property allows you to control the way the :hp2.VRPrinter 
Object:ehp2. performs word wrapping on a block of text. By default this property is set to 
1 (TRUE) so that the breaks occur between words. By setting this property off (0), line 
wrapping will occur with breaks between characters.

.**** XPos ************************************************************

:h2 res=1070.XPos
:i2 refid=PROPS.XPos
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=1071.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=1072.

:h2 hide res=1071.XPos - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=1072.XPos - Description
:font facename=Helv size=16x12.
:p.The :hp2.XPos:ehp2. property contains the current X coordinate of the printing cursor in the 
chosen :link reftype=hd res=314.Measures:elink..
:note.
.br
The coordinate system has its origin at the intersection of the bottom margin and the left margin.

.**** YPos ************************************************************

:h2 res=1073.YPos
:i2 refid=PROPS.YPos
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=1074.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=1075.

:h2 hide res=1074.YPos - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=1075.YPos - Description
:font facename=Helv size=16x12.
:p.The :hp2.YPos:ehp2. property contains the current Y coordinate of the printing cursor in the 
chosen :link reftype=hd res=314.Measures:elink..
:note.
.br
The coordinate system has its origin at the intersection of the bottom margin and the left margin.

.**** XPosTwips *******************************************************

:h2 res=1080.XPosTwips
:i2 refid=PROPS.XPosTwips
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=1081.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=1082.

:h2 hide res=1081.XPosTwips - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=1082.XPosTwips - Description
:font facename=Helv size=16x12.
:p.The :hp2.XPosTwips:ehp2. property contains the current X coordinate of the printing cursor in 
global coordinates (TWIPS).
:note.
.br
The global coordinate system has its origin at the the bottom left of the printing presentation space.

.**** YPos ************************************************************

:h2 res=1083.YPosTwips
:i2 refid=PROPS.YPosTwips
:link reftype=hd auto split group=1 vpx=left vpy=top vpcx=30% vpcy=100% scroll=vertical titlebar=none rules=border res=1084.
:link reftype=hd auto split group=2 vpx=right vpy=top vpcx=70% vpcy=100% scroll=vertical titlebar=yes rules=border res=1085.

:h2 hide res=1084.YPosTwips - List
:font facename=Helv size=16x12.
:p.:hp2.Data Type:ehp2.
:sl compact.
:li.Numeric
:esl.

:h2 hide res=1085.YPosTwips - Description
:font facename=Helv size=16x12.
:p.The :hp2.YPosTwips:ehp2. property contains the current Y coordinate of the printing cursor in 
global coordinates (TWIPS).
:note.
.br
The global coordinate system has its origin at the the bottom left of the printing presentation space.

.***** Events ***********************************************************

:h1 res=700.VRPrinter events
:i1 id=EVENT.VRPrinter events
:font facename=Helv size=16x12.
:p.No events are triggred by the :hp2.VRPrinter Object:ehp2..

.***** Methods ********************************************************

:h1 res=199.VRPrinter methods
:i1 id=FUNC.VRPrinter methods
:font facename=Helv size=16x12.
:p.The following sections describe each of the methods available for the :hp2.VRPrinter Object:ehp2..
:ul compact.
:li.:link reftype=hd res=245.AbortPrintJob:elink.
:li.:link reftype=hd res=702.BlockFits:elink.
:li.:link reftype=hd res=204.ClosePrintJob:elink.
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=1120.DrawLine:elink.
:li.:link reftype=hd res=206.EndRow:elink.
:li.:link reftype=hd res=207.EndTable:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:li.:link reftype=hd res=209.Goto:elink.
:li.:link reftype=hd res=1090.GotoTab:elink.
:li.:link reftype=hd res=1100.GotoX:elink.
:li.:link reftype=hd res=1110.GotoY:elink.
:li.:link reftype=hd res=211.JobProperties:elink.
:li.:link reftype=hd res=714.LineFits:elink.
:li.:link reftype=hd res=1043.MoveX:elink.
:li.:link reftype=hd res=1047.MoveY:elink.
:li.:link reftype=hd res=215.NewPage:elink.
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=217.PrinterDialog:elink.
:li.:link reftype=hd res=218.PrinterList:elink.
:li.:link reftype=hd res=237.PrintFile:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=240.ResetColHeader:elink.
:li.:link reftype=hd res=246.ResetHeader:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=235.SetHeaderLineFont:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=222.SetMargins:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:li.:link reftype=hd res=715.SetProgressTexts:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=227.Tab:elink.
:eul.

.***** AbortPrintJob ****************************************************

:h2 res=245.AbortPrintJob
:i2 refid=FUNC.AbortPrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=768. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=769.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=770.

:h2 hide res=768.AbortPrintJob - List
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
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:li.:link reftype=hd res=204.ClosePrintJob:elink.
:eul.


:h2 hide res=769.AbortPrintJob - Description
:xmp.
ok = VRMethod( object, "AbortPrintJob");
:exmp.
:font facename=Helv size=16x12.
:p.Aborts the print job and deletes the document from the print queue.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=770.AbortPrintJob - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

:h2 hide res=771.AbortPrintJob - Example
:xmp.
/********************************************************************/
/* Abort the print job                                              */
/********************************************************************/

ok = VRMethod( "PRT_1", "AbortPrintJob");

:exmp.

.***** BlockFits ********************************************************

:h2 res=702.BlockFits
:i2 refid=FUNC.BlockFits
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=772. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=773.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=774.

:h2 hide res=772.BlockFits - List
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
:li.:link reftype=hd res=714.LineFits:elink.
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=773.BlockFits - Description
:xmp.
ok = VRMethod( object, "BlockFits", 
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


:h2 hide res=774.BlockFits - parameters
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

:h2 hide res=775.BlockFits - Example
:xmp.

    facename = 'Helvetica';

    /**** Text is long block of text */    
    fnt = 8
    rcy = VRMethod( "PRT_1", "PrintLine", facename, fnt, text);
    rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
    do fnt = 10 to 24 by 2
        if VRMethod( "PRT_1", "BlockFits", facename, fnt, text) then
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, text);
        else do
            rcy = VRMethod( "PRT_1", "Goto", 0, 10, 1);
            rcy = VRMethod( "PRT_1", "PrintRight", , 10, "Continued...");
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, text);
        end
        if VRMethod( "PRT_1", "BlockFits", facename, fnt, '') then
            rcy = VRMethod( "PRT_1", "PrintLine", , fnt, '');
        else
            rcy = VRMethod( "PRT_1", "PrintRight", , 10, "Continued...");
    end

:exmp.

.***** ClosePrintJob *************************************************
 
:h2 res=204.ClosePrintJob
:i2 refid=FUNC.ClosePrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=776. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=777.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=778.

:h2 hide res=776.ClosePrintJob - List
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
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:li.:link reftype=hd res=245.AbortPrintJob:elink.
:eul.


:h2 hide res=777.ClosePrintJob - Description
:xmp.
ok = VRMethod( object, "ClosePrintJob");
:exmp.
:font facename=Helv size=16x12.
:p.Close the print job and end the document.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).


:h2 hide res=778.ClosePrintJob - parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.


:h2 hide res=779.ClosePrintJob - Example
:xmp.
/********************************************************************/
/* Close the print job                                              */
/********************************************************************/

ok = VRMethod( "PRT_1", "ClosePrintJob");

:exmp.

.***** DefineTable ****************************************************

:h2 res=200.DefineTable
:i2 refid=FUNC.DefineTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=780. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=781.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=782.

:h2 hide res=780.DefineTable - List
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
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=206.EndRow:elink.
:li.:link reftype=hd res=207.EndTable:elink.
:eul.

:h2 hide res=781.DefineTable - Description
:xmp.
ok = VRMethod( object, "DefineTable", 
                       "table.", 
                       "Cols.");
:exmp.
:font facename=Helv size=16x12.
:p.Defines a table for printing. If there are not the right number of elements in the stem vars 
the method will return FALSE.
:p.This call only prepares the internal structures for handling a table, to start printing the 
table you must call :link reftype=hd res=225.StartRow:elink. and :link reftype=hd 
res=224.StartCol:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=782.DefineTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt."table."
:pd.Quoted name of a stem variable containing the definition of the table&colon.
:lm margin=5.
:parml compact tsize=15 break=none.
:pt.table.0
:pd.Must be 11 for monochrome printing or 17 if you use colour support
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

:h2 hide res=783.DefineTable - Example
:xmp.
/************************************************************************/
/* Declare a table with no fill style, 0.5 mm separator lines, 1mm      */
/* lines around headers on all pages and 3 columns                      */
/************************************************************************/

right = 2
bottom = 8
noedge = 16

table.0 = 17
table.1 = 0
table.2 = 28
table.3 = 1
table.4 = 0
table.5 = 56
table.6 = 1
table.7 = 12
table.8 = 'Helvetica Bold'
table.9 = 10
table.10 = right + bottom + noedge
table.11 = bottom
table.12 = "Red"
table.13 = "Cyan"
table.14 = "Black"
table.15 = "Blue"
table.16 = "White"
table.17 = "Black"

Cols.0.0 = 3

Cols.1.1 = 45
Cols.1.2 = 'Column 1'

Cols.2.1 = 75
Cols.2.2 = 'Column 2'

Cols.3.1 = 40
Cols.3.2 = 'Column 3'
                       
ok = VRMethod( "PRT_1", "DefineTable", "table.", "Cols.");

if ok then do

    /**** Start printing in the table **********************************/
    
    ok = VRMethod( "PRT_1", "StartRow");
    
    /**** Start printing in column 1 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 1);
    ok = VRMethod( "PRT_1", "PrintRight", 'Helvetica', 10, textvar);
    
    /**** Start printing in column 2 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 2);
    ok = VRMethod( "PRT_1", "PrintJustified", 'Helvetica Bold', 10, textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    
    /**** Start printing in column 3 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 3);
    ok = VRMethod( "PRT_1", "PrintCentered", 'Helvetica Bold', 14, textvar);
    
    /**** Print the row ************************************************/
    
    ok = VRMethod( "PRT_1", "EndRow");
    
    /**** Start a new row **********************************************/
    
    ok = VRMethod( "PRT_1", "StartRow");
    ok = VRMethod( "PRT_1", "StartCol", 1);
    ok = VRMethod( "PRT_1", "PrintRight", 'Times New Roman', 10, textvar);
    ok = VRMethod( "PRT_1", "StartCol", 2);
    ok = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 10, textvar);
    ok = VRMethod( "PRT_1", "PrintCentered",,,textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    ok = VRMethod( "PRT_1", "PrintRight",,,textvar);
    ok = VRMethod( "PRT_1", "StartCol", 3);
    ok = VRMethod( "PRT_1", "PrintJustified", 'Times New Roman', 8, textvar);
    
    /**** Print the row ************************************************/
    
    ok = VRMethod( "PRT_1", "EndRow");
    
    /**** Destroy the table data structures ****************************/
    
    ok = VRMethod( object, "EndTable");
end
:exmp.

.***** DrawLine *********************************************************

:h2 res=1120.DrawLine
:i2 refid=FUNC.DrawLine
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1121.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1122.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1123.

:h2 hide res=1121.DrawLine - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1122.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1123.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
;li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=1064.PrintJPEG:elink.
:eul.

:h2 hide res=1122.DrawLine - Description
:xmp.
ok = VRMethod( object, "DrawLine", 
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

:h2 hide res=1123.DrawLine - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** EndRow ********************************************************
 
:h2 res=206.EndRow
:i2 refid=FUNC.EndRow
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=784. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=785.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=786.

:h2 hide res=784.EndRow - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=207.EndTable:elink.
:eul.

:h2 hide res=785.EndRow - Description
:xmp.
ok = VRMethod( object, "EndRow");
:exmp.
:font facename=Helv size=16x12.
:p.End the current row in a table and print it. This will cause the table to wrap over page 
if any of the columns will not fit. Cells will be split over the page not forced onto the next 
page. If you have defined running headers for the table, these will be printed at the top of 
the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=786.EndRow - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.
 
.***** EndTable ******************************************************
 
:h2 res=207.EndTable
:i2 refid=FUNC.EndTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=787. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=788.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=789.

:h2 hide res=787.EndTable - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=206.EndRow:elink.
:eul.

:h2 hide res=788.EndTable - Description
:xmp.
ok = VRMethod( object, "EndTable");
:exmp.
:font facename=Helv size=16x12.
:p.Terminate table mode printing and return to normal text printing.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=789.EndTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

.***** FontDialog ****************************************************
 
:h2 res=234.FontDialog
:i2 refid=FUNC.FontDialog
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=790. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=791.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=792.

:h2 hide res=790.FontDialog - List
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:li.:link reftype=hd res=218.PrinterList:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:eul.

:h2 hide res=791.FontDialog - Description
:xmp.
font = VRMethod( object, "FontDialog", 
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

:h2 hide res=792.FontDialog - parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.title
:pd.Title to appear in the font dialog.
:pt.familyname
:pd.This will set the default selected font in the dialog. This is the name of the font e.g. 
Helvetica and should not include the point size or attributes.
:eparml.

:h2 hide res=793.FontDialog - Example
:xmp.

fntstr = VRMethod( "PRT_1", "FontDialog", "Choose printer font", "CG Times");

ok = VRSet( "EF_1", "Value", fntstr);

:exmp.

:h2 res=1060.FreeResMod
:i2 refid=FUNC.FreeResMod
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1061.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1062.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1063.

:h2 hide res=1061.FreeResMod - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1062.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1063.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1055.LoadResMod:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:eul.


:h2 hide res=1062.FreeResMod - Description
:xmp.
hmod = VRMethod( object, "FreeResMod", hmod);
:exmp.
:font facename=Helv size=16x12.
:p.Frees a dll module that was loaded with :link reftype=hd res=1055.LoadResMod:elink..
:p.:hp2.Return:ehp2.
:p.always returns 0.

:h2 hide res=1063.FreeResMod - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.hmod
:pd.Module handle returned from :link reftype=hd res=1055.LoadResMod:elink..
:eparml.

.***** Goto **********************************************************
 
:h2 res=209.Goto
:i2 refid=FUNC.Goto
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=794. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=795.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=796.

:h2 hide res=794.Goto - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=795.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=796.Parameters:elink. 
:eul.

:h2 hide res=795.Goto - Description
:xmp.
ok = VRMethod( object, "Goto", 
                       x, 
                       y, 
                       use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor to the given position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=796.Goto - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** GotoTab *******************************************************
 
:h2 res=1090.GotoTab
:i2 refid=FUNC.GotoTab
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1091. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1092.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1093.

:h2 hide res=1091.GotoTab - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1092.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1093.Parameters:elink. 
:eul.

:h2 hide res=1092.GotoTab - Description
:xmp.
ok = VRMethod( object, "GotoTab", tabnum);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor to the given tab stop.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1093.Goto - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.tabnum
:pd.The number of the tab stop starting at tab 0 on the left margin the tabs are set at every 10mm.
:eparml.

.***** GotoX *********************************************************
 
:h2 res=1100.GotoX
:i2 refid=FUNC.GotoX
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1101. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1102.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1103.

:h2 hide res=1101.GotoX - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1102.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1103.Parameters:elink. 
:eul.

:h2 hide res=1102.GotoX - Description
:xmp.
ok = VRMethod( object, "GotoX", 
                       x, 
                       use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor horizontally to the given X position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1103.GotoX - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** GotoY *********************************************************
 
:h2 res=1110.GotoY
:i2 refid=FUNC.GotoY
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1111. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1112.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1113.

:h2 hide res=1111.GotoY - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1112.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1113.Parameters:elink. 
:eul.

:h2 hide res=1112.GotoY - Description
:xmp.
ok = VRMethod( object, "GotoY", 
                       y, 
                       use_points);
:exmp.
:font facename=Helv size=16x12.
:p.Move the GPI cursor vertically to the given Y position on the page.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1113.Goto - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** JobProperties ******************************************************
 
:h2 res=211.JobProperties
:i2 refid=FUNC.JobProperties
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=797. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=798.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=799.

:h2 hide res=797.JobProperties - List
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:li.:link reftype=hd res=218.PrinterList:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:eul.

:h2 hide res=798.JobProperties - Description
:xmp.
ok = VRMethod( object, "JobProperties");
:exmp.
:font facename=Helv size=16x12.
:p.Pops up the job properties dialog for the printer selected with :link reftype=hd 
res=217.PrinterDialog:elink. or with :link reftype=hd res=223.SetPrinter:elink.. 
If there is no selected printer, an error dialog is popped up and the method returns FALSE.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:artwork name='w:\prtgraph\bitmaps\jobprops.bmp' align=left.
:p.:hp2.Figure&colon. Printer Job Properties Dialog for a Laserjet IIIP.:ehp2.

:h2 hide res=799.JobProperties - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

.***** LineFits *********************************************************

:h2 res=714.LineFits
:i2 refid=FUNC.LineFits
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=800. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=801.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=802.

:h2 hide res=800.LineFits - List
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
:li.:link reftype=hd res=702.BlockFits:elink.
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:li.:link reftype=hd res=1076.StringLength:elink.
:eul.

:h2 hide res=801.LineFits - Description
:xmp.
ok = VRMethod( object, "LineFits", 
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

:h2 hide res=802.LineFits - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 res=1055.LoadResMod
:i2 refid=FUNC.LoadResMod
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1056.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1057.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1058.

:h2 hide res=1056.LoadResMod - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1057.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1058.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=1060.FreeResMod:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:eul.

:h2 hide res=1057.LoadResMod - Description
:xmp.
hmod = VRMethod( object, "LoadResMod", DLLName);
:exmp.
:font facename=Helv size=16x12.
:p.Loads the given dll to access any resources therein (see DosLoadModule).
:p.:hp2.Return:ehp2.
:p.The handle to the module if successful otherwise 0.

:h2 hide res=1058.LoadResMod - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.DLLName
:pd.The full path name of the dll otr its symbolic name (the one following the LIBRARY statement 
in the def file).
:eparml.

.***** MoveX *********************************************************

:h2 res=1043.MoveX
:i2 refid=FUNC.MoveX
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1044. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1045.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1046.

:h2 hide res=1044.MoveX - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1045.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1046.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=209.Goto:elink.
:li.:link reftype=hd res=1047.MoveY:elink.
:eul.

:h2 hide res=1045.MoveX - Description
:xmp.
ok = VRMethod( object, "MoveX",
                       relX, 
                       points);
:exmp.
:font facename=Helv size=16x12.
:p.Moves the x position of the graphics printing cursor :hp2.relX:ehp2. units relative to the 
current position. If :hp2.points:ehp2. is TRUE (1), the cursor is moved :hp2.relX:ehp2. points,
otherwise the current :link reftype=hd res=314.Measures:elink. are used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if the cursor was moved else FALSE (0).

:h2 hide res=1046.MoveX - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.relX
:pd.Number of measurement units to move the cursor. This may be a negative value, in which case the 
cursor is moved to the left.
:pt.points
:pd.Boolean (1 or 0) indicating whether the measures should be in points (TRUE) or default 
:link reftype=hd res=314.Measures:elink. (FALSE).
:eparml.

.***** MoveY *********************************************************

:h2 res=1047.MoveY
:i2 refid=FUNC.MoveY
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1048. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1049.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1050.

:h2 hide res=1048.MoveY - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1049.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1050.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=209.Goto:elink.
:li.:link reftype=hd res=1043.MoveX:elink.
:eul.

:h2 hide res=1049.MoveY - Description
:xmp.
ok = VRMethod( object, "MoveY",
                       relY, 
                       points);
:exmp.
:font facename=Helv size=16x12.
:p.Moves the y position of the graphics printing cursor :hp2.relY:ehp2. units relative to the 
current position. If :hp2.points:ehp2. is TRUE (1), the cursor is moved :hp2.relY:ehp2. points,
otherwise the current :link reftype=hd res=314.Measures:elink. are used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if the cursor was moved else FALSE (0).

:h2 hide res=1050.MoveY - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.relY
:pd.Number of measurement units to move the cursor. This may be a negative value, in which case the 
cursor is moved to the left.
:pt.points
:pd.Boolean (1 or 0) indicating whether the measures should be in points (TRUE) or default 
:link reftype=hd res=314.Measures:elink. (FALSE).
:eparml.

.***** NewPage *******************************************************
 
:h2 res=215.NewPage
:i2 refid=FUNC.NewPage
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=803. 
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=804.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=805.

:h2 hide res=803.NewPage - List
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
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=222.SetMargins:elink.
:eul.

:h2 hide res=804.NewPage - Description
:xmp.
ok = VRMethod( object, "NewPage");
:exmp.
:font facename=Helv size=16x12.
:p.Forces a new page to be printed with its header and footer. If this method is called 
inside a table, any headers defined for the table will also be printed.
:warning.
This method will not function when called within a table. Tables handle the wrapping over pages 
internally.
:ewarning.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=805.NewPage - Parameters
:p.:hp2.Parameters:ehp2.
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.
 
.***** OpenPrintJob **************************************************
 
:h2 res=216.OpenPrintJob
:i2 refid=FUNC.OpenPrintJob
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=806.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=807.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=808.

:h2 hide res=806.OpenPrintJob - List
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:li.:link reftype=hd res=222.SetMargins:elink.
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=204.ClosePrintJob:elink.
:eul.

:h2 hide res=807.OpenPrintJob - Description
:xmp.
ok = VRMethod( object, "OpenPrintJob", 
                       doc_name, 
                       num_copies);
:exmp.
:font facename=Helv size=16x12.
:p.Opens the print job with the spooler. You should previously define the margins, header and 
and footer and, if you do not want to use the default printer, have selected a printer. 
:note.
If you have not selected a printer and there is no default printer for the system, an error 
dialog is popped up and the method returns FALSE.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=808.OpenPrintJob - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.doc_name
:pd.The title of the document. This will aslo be passed to the spooler ad the document name.
:pt.num_copies
:pd.The number of copies to print (some drivers do not accept this parameter).
:eparml.

:h2 hide res=809.OpenPrintJob - Example
:xmp.

ok = VRMethod( "PRT_1", "SetMargins", 25, 20, 20, 25, 0, 0);
ok = VRMethod( "PRT_1", "SetHeaderMode", header, facename, 10, 8, 28, 0);
ok = VRMethod( "PRT_1", "SetHeader", 3, ,
                       "$c|", "$lADD Consulting (CH)$r@",,
                       'Demo for VRPrinter Object for VX-REXX');
ok = VRMethod( "PRT_1", "SetFooter", facename, 8, 0, 14, '$|$rpage $#');
ok = VRMethod( "PRT_1", "OpenPrintJob", 'Document Title');
                              
if \ok then
   return

:exmp.
 
.***** PrintBitMap ********************************************************

:h2 res=201.PrintBitMap
:i2 refid=FUNC.PrintBitMap
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=810.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=811.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=812.

:h2 hide res=810.PrintBitMap - List
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
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=1064.PrintJPEG:elink.
:eul.

:h2 hide res=811.PrintBitMap - Description
:xmp.
ok = VRMethod( object, "PrintBitMap", 
                        bitmap_file, 
                        lx, ly, 
                        tx, ty, 
                        th, 
                        border_color,
                        title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints a bitmap from a file in the box given by the coordinates and framed in the given 
line style.
:p.The bit map will be stretched or compressed to fit and, if the printer supports colour, 
will be printed in colour.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=812.PrintBitMap - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.bitmap_file
:pd.Full path to the bitmap file you want to print or a string of the following format:
.br
:hp2.x$y:ehp2. where
.br
:hp2.x:ehp2. is the module handle returned from :link reftype=hd res=1055.LoadResMod:elink. for a dll or 
nothing if loading from the exe.
.br
:hp2.y:ehp2. is the resource number of the bitmap to print.
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
:pd.A title that will be printed centered under the image.
:eparml.

:h2 hide res=813.PrintBitMap - Example
:xmp.

/********************************************************************/
/* Print the OS/2 logo in a box with a thick outline                */
/********************************************************************/

/**** Get the path to the bit map ***********************************/

set_path = VALUE( 'PATH', , 'OS2ENVIRONMENT');
bootdrive = substr( set_path, pos( '\OS2\SYSTEM', set_path ) -2, 2);
bmp_name = bootdrive || '\os2\bitmap\os2logo.bmp'

/**** Print the bit map with a blue border **************************/

ok = VRMethod( "PRT_1", "PrintBitMap", bmp_name, 40, 20,,
               130, 110, 200, "Blue", "Figure 1. OS/2 Logo");

/********************************************************************/
/* Load a dll and print a resource bitmat                           */
/********************************************************************/

hmod = VRMethod( "PRT_1", "LoadResMod", "RESOURCE");
res = hmod || '$100'
ok = VRMethod( "PRT_1", "PrintBitMap", res, 40, 20,, 
               130, 110, 200, "Blue", "Figure 2. A DLL resource Bitmap");
call VRMethod "PRT_1", "FreeResMod", hmod

/********************************************************************/
/* Print resource bitmap 200 from the current exe file              */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintBitMap", '$200', 40, 20,, 
               130, 110, 200, "Blue", "Figure 3. A bitmap from the exe");

:exmp.
 
.***** PrintBox ***********************************************************

:h2 res=202.PrintBox
:i2 refid=FUNC.PrintBox
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=820.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=821.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=822.

:h2 hide res=820.PrintBox - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=821.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=822.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=1064.PrintJPEG:elink.
:eul.

:h2 hide res=821.PrintBox - Description
:xmp.
ok = VRMethod( object, "PrintBox", 
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
The position of the cursor is unaffected by this method.

:h2 hide res=822.PrintBox - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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
:pd.Style used for filling the box (see :link reftype=hd res=135.Fill Styles:elink.)
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
 
.***** PrintCentered ********************************************************
 
:h2 res=203.PrintCentered
:i2 refid=FUNC.PrintCentered
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=830.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=831.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=832.

:h2 hide res=830.PrintCentered - List
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
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.


:h2 hide res=831.PrintCentered - Description
:xmp.
ok = VRMethod( object, "PrintCentered", 
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

:h2 hide res=832.PrintCentered - Parameters
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

:h2 hide res=833.PrintCentered - Examples
:xmp.
/********************************************************************/
/* Print a text centred on the page (or in a cell) in Helvetica 10  */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintCentered", "Helvetica", 10, "whatever you want to print");

/**** The following text will have the same font and size ***********/

ok = VRMethod( "PRT_1", "PrintCentered",,,"Here is some more");

:exmp.

.***** PrinterDialog ****************************************************
 
:h2 res=217.PrinterDialog
:i2 refid=FUNC.PrinterDialog
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=840.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=841.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=842.

:h2 hide res=840.PrinterDialog - List
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
:li.:link reftype=hd res=211.JobProperties:elink.
:li.:link reftype=hd res=218.PrinterList:elink.
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:eul.

:h2 hide res=841.PrinterDialog - Description
:xmp.
ok = VRMethod( object, "PrinterDialog", 
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


:h2 hide res=842.PrinterDialog - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** PrinterList ***************************************************
 
:h2 res=218.PrinterList
:i2 refid=FUNC.PrinterList
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=850.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=851.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=852.

:h2 hide res=850.PrinterList - List
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
:li.:link reftype=hd res=217.PrinterDialog:elink.
:li.:link reftype=hd res=223.SetPrinter:elink.
:eul.

:h2 hide res=851.PrinterList - Description
:xmp.
ok = VRMethod( object, "PrinterList", 
                       "printers.");
:exmp.
:font facename=Helv size=16x12.
:p.This method returns a list of printer names that you can use to create your own printer 
selection dialog. You can set the selected printer with a call to :link reftype=hd 
res=223.SetPrinter:elink. using the index of the printer name.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=852.PrinterList - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt."printers."
:pd.Quoted name of a stem variable to contain the list of available printers.
.br
:hp2.printers.0:ehp2. will contain the number of printers in the list.
:eparml.

:h2 hide res=853.PrinterList - Example
:xmp.
/****************************************************************/
/* Get the list of printers into a stem variable                */
/****************************************************************/

ok = VRMethod( "PRT_1", "PrinterList", "printers.");

:exmp.
 
.***** PrintFile ********************************************************

:h2 res=237.PrintFile
:i2 refid=FUNC.PrintFile
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=860.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=861.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=862.

:h2 hide res=860.PrintFile - List
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
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:li.:link reftype=hd res=204.ClosePrintJob:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:eul.


:h2 hide res=861.PrintFile - Description
:xmp.
ok = VRMethod( object, "PrintFile", 
                       face_name, 
                       points, 
                       style, 
                       file_name);
:exmp.
:font facename=Helv size=16x12.
:p.Prints the given file in the given font, point size and style. All the parameters must be 
present. 
:p.A print job must have been opened prior to calling this method.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:warning.
:hp2.Only print plain text files with this method.:ehp2. printing any other kind of file 
could produce unexpected results.
:ewarning.

:h2 hide res=862.PrintFile - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** PrintJPEG ********************************************************

:h2 res=1064.PrintJPEG
:i2 refid=FUNC.PrintJPEG
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1065.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1066.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1067.

:h2 hide res=1065.PrintJPEG - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1066.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1067.Parameters:elink. 
:li.:link reftype=hd group=3 scroll=both split vpx=right vpy=top vpcx=70% vpcy=100%
res=1068.Example:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:eul.

:h2 hide res=1066.PrintJPEG - Description
:xmp.
ok = VRMethod( object, "PrintJPEG", 
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
:note.You must have a copy of :hp2.djpeg.exe:ehp2. for DOS or OS/2 on your PATH for this function 
to work correctly.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1067.PrintJPEG - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.jpeg_file
:pd.Full path to the jpeg file you want to print.
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
:pd.A title that will be printed centered under the image.
:eparml.

:h2 hide res=1068.PrintJPEG - Example
:xmp.

/********************************************************************/
/* Print a jpeg image in a box with a thick outline                */
/********************************************************************/

jpeg_name = 'testorig.jpg'

/**** Print the jpeg with a blue border **************************/

ok = VRMethod( "PRT_1", "PrintJPEG", jpeg_name, 40, 20,,
               130, 110, 200, "Blue", "Figure 1. JPEG image");

:exmp.
 
.***** PrintJustified ********************************************************
 
:h2 res=212.PrintJustified
:i2 refid=FUNC.PrintJustified
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=870.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=871.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=872.

:h2 hide res=870.PrintJustified - List
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
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=871.PrintJustified - Description
:xmp.
ok = VRMethod( object, "PrintJustified", 
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

:h2 hide res=872.PrintJustified - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=873.PrintJustified - Example
:xmp.
/********************************************************************/
/* Print a text justified on the page (or in a cell) in Helv 10     */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintJustified", "Helvetica", 10, "whatever you want to print");

/**** The following text will have the same font and size ***********/

ok = VRMethod( "PRT_1", "PrintJustified",,,"Here is some more");

:exmp.

.***** PrintLeft *********************************************************
 
:h2 res=230.PrintLeft
:i2 refid=FUNC.PrintLeft
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=880.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=881.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=882.

:h2 hide res=880.PrintLeft - List
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
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=881.PrintLeft - Description
:xmp.
ok = VRMethod( object, "PrintLeft", 
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
Remember to add a space at the end of a string if you call this method several times, otherwise 
the texts will be "stuck" together.

:h2 hide res=882.PrintLeft - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=883.PrintLeft - Example
:xmp.
/********************************************************************/
/* Print a text on the page (or in a cell) in Helvetica 10          */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintLeft", 'Helvetica', 10, 'whatever you want to print. ');

/**** The following text will have the same font and size ***********/

ok = VRMethod( "PRT_1", "PrintLeft",,,'Here is some more');

:exmp.
 
.***** PrintLine *******************************************************
 
:h2 res=231.PrintLine
:i2 refid=FUNC.PrintLine
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=890.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=891.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=892.

:h2 hide res=890.PrintLine - List
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
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=891.PrintLine - Description
:xmp.
ok = VRMethod( object, "PrintLine", 
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

:h2 hide res=892.PrintLine - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=893.PrintLine - Example
:xmp.
/********************************************************************/
/* Print a text on the page (or in a cell) in Helvetica 10          */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintLine", 'Helvetica', 10, 'whatever you want to print');

/**** The following text will have the same font and size ***********/

ok = VRMethod( "PRT_1", "PrintLine",,,'Here is some more');

:exmp.

.***** PrintObjectImage *************************************************

:h2 res=241.PrintObjectImage
:i2 refid=FUNC.PrintObjectImage
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=900.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=901.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=902.

:h2 hide res=900.PrintObjectImage - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=901.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=902.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=1051.PrintWinImage:elink.
:li.:link reftype=hd res=1064.PrintJPEG:elink.
:eul.

:h2 hide res=901.PrintObjectImage - Description
:xmp.
ok = VRMethod( prt, "PrintObjectImage", 
                    object, 
                    lx, ly, 
                    tx, ty, 
                    th, 
                    border_color,
                    title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints an image of the object. If you pass the name of a window the client area will be 
printed without any frame controls.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=902.PrintObjectImage - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.object
:pd.Name of the :hp2.VX-REXX:ehp2. visible object to print e.g. "Window1"
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property. if this parameter is left out the 
image will be printed with the same width as the object on the screen.
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property. if this parameter is left out the 
image will be printed with the same height as the object on the screen.
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.border_color
:pd.The colour of the line around the image. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.title
:pd.A title that will be printed centered under the image.
:eparml.


.***** PrintRight *****************************************************
 
:h2 res=213.PrintRight
:i2 refid=FUNC.PrintRight
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=910.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=911.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=912.

:h2 hide res=910.PrintRight - List
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
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:li.
:eul.

:h2 hide res=911.PrintRight - Description
:xmp.
ok = VRMethod( object, "PrintRight", 
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

:h2 hide res=912.PrintRight - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

:h2 hide res=913.PrintRight - Example
:xmp.
/********************************************************************/
/* Print a text right aligned on the page (or in a cell)            */
/********************************************************************/

ok = VRMethod( "PRT_1", "PrintRight", 'Helvetica', 10, 'whatever you want to print');

/**** The following text will have the same font and size ***********/

ok = VRMethod( "PRT_1", "PrintRight",,,'Here is some more');

:exmp.
 
.***** PrintWinImage *************************************************

:h2 res=1051.PrintWinImage
:i2 refid=FUNC.PrintWinImage
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1052.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1053.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1054.

:h2 hide res=1052.PrintWinImage - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1053.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1054.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=201.PrintBitMap:elink.
:li.:link reftype=hd res=202.PrintBox:elink.
:li.:link reftype=hd res=241.PrintObjectImage:elink.
:li.:link reftype=hd res=1064.PrintJPEG:elink.
:eul.

:h2 hide res=1053.PrintWinImage - Description
:xmp.
ok = VRMethod( prt, "PrintWinImage", 
                    hwnd, 
                    lx, ly, 
                    tx, ty, 
                    th, 
                    border_color,
                    title);
:exmp.
:font facename=Helv size=16x12.
:p.Prints an image of the contents of a window.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1054.PrintWinImage - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.hwnd
:pd.Handle of the window whose contents you want to print. This should be in the form ?HWNDxxxxx 
as returned by VX-REXX "screen" methods etc..
:pt.lx
:pd.Lower left X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.ly
:pd.Lower left Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property
:pt.tx
:pd.Upper right X coordinate taken from the left margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property. if this parameter is left out the 
image will be printed with the same width as the object on the screen.
:pt.ty
:pd.Upper right Y coordinate taken from the bottom margin in millimetres or 1/10 inch depending 
on the :link reftype=hd res=314.Measures:elink. property. if this parameter is left out the 
image will be printed with the same height as the object on the screen.
:pt.th
:pd.Thickness of the box line in TWIPS ( 56.7 TWIPS = 1mm)
:pt.border_color
:pd.The colour of the line around the image. One of the colour strings defined by :hp2.VX-REXX:ehp2.
:pt.title
:pd.A title that will be printed centered under the image.
:eparml.

.***** ResetColHeader ***************************************************

:h2 res=240.ResetColHeader
:i2 refid=FUNC.ResetColHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=920.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=921.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=922.

:h2 hide res=920.ResetColHeader - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:eul.

:h2 hide res=921.ResetColHeader - Description
:xmp.
ok = VRMethod( object, "ResetColHeader", 
                       col_num, 
                       text);
:exmp.
:font facename=Helv size=16x12.
:p.Changes the text in the table header for the given column.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=922.ResetColHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.col_num
:pd.Number of the column (1..n) whose header text you want to change
:pt.text
:pd.New header text for the column
:eparml.

.***** ResetHeader ***************************************************

:h2 res=246.ResetHeader
:i2 refid=FUNC.ResetHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=930.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=931.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=932.

:h2 hide res=930.ResetHeader - List
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
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=235.SetHeaderLineFont:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:eul.

:h2 hide res=931.ResetHeader - Description
:xmp.
ok = VRMethod( object, "ResetHeader", 
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
:hp2.You should only call this method after opening a print job to modify the header for the 
following pages:ehp2.
:ewarning.

:h2 hide res=932.ResetHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.numlines
:pd.The number of lines in the header ( 1 to 5)
:pt.text
:pd.The text to printed on the line. there should be :hp2.numlines:ehp2. text variables. An 
empty variable will leave the original header text for that line.
:eparml.

.***** SetFooter *****************************************************
 
:h2 res=219.SetFooter
:i2 refid=FUNC.SetFooter
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=940.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=941.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=942.

:h2 hide res=940.SetFooter - List
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
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=941.SetFooter - Description
:xmp.
ok = VRMethod( object, "SetFooter", 
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

:h2 hide res=942.SetFooter - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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
:pd.A combination of the following flags that defines which sides of the box around the footer are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=943.SetFooter - Example
:xmp.
/****************************************************************/
/* Set the footer with the page number right justified and the  */
/* document title left aligned with an unfilled blue box around */
/* it and with black text.                                      */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetFooter", 'Helvetica', 8, 0, 14, '$|$rpage $#', "Blue", , "Black");
:exmp.

.***** SetHeader *****************************************************
 
:h2 res=220.SetHeader
:i2 refid=FUNC.SetHeader
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=950.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=951.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=952.

:h2 hide res=950.SetHeader - List
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
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=246.ResetHeader:elink.
:li.:link reftype=hd res=235.SetHeaderLineFont:elink.
:li.:link reftype=hd res=219.SetFooter:elink.
:eul.

:h2 hide res=951.SetHeader - Description
:xmp.
ok = VRMethod( object, "SetHeader", 
                       numlines, 
                       text 
                       [, text]);
:exmp.
:font facename=Helv size=16x12.
:p.Defines the text lines for the header printed on each page of document. The :hp2.text:ehp2. 
variable can contain :link reftype=hd res=120.Formatting Flags:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0). FALSE is also returned if there has been no previous 
call to :link reftype=hd res=221.SetHeaderMode:elink..
:warning.
:hp2.You MUST make a call to the :link reftype=hd res=221.SetHeaderMode:elink. method before 
calling this method:ehp2.
:ewarning.

:h2 hide res=952.SetHeader - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.numlines
:pd.The number of lines in the header ( 1 to 5)
:pt.text
:pd.The text to printed on the line. there should be :hp2.numlines:ehp2. text variables
:eparml.

:h2 hide res=953.SetHeader - Example
:xmp.
/****************************************************************/
/* Set the header with the doc title on the first line centred, */
/* the date on the second line right justified and some other   */
/* text. There are 3 lines in the header.                       */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeader", 3, ,
                       "$c|",, 
                       "$lADD Consulting (CH)$r@",,
                       'Demo for VRPrinter Object for VX-REXX');

:exmp.
 
.***** SetHeaderLineFont ************************************************

:h2 res=235.SetHeaderLineFont
:i2 refid=FUNC.SetHeaderLineFont
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=960.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=961.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=962.

:h2 hide res=960.SetHeaderLineFont - List
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
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:li.:link reftype=hd res=220.SetHeader:elink.
:eul.

:h2 hide res=961.SetHeaderLineFont - Description
:xmp.
ok = VRMethod( object, "SetHeaderLineFont", 
                       linenum, 
                       font, 
                       points);
:exmp.
:font facename=Helv size=16x12.
:p.Sets the font for one line in the header to a different size or font from that defined 
in :link reftype=hd res=221.SetHeaderMode:elink.. 
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0). FALSE is also returned if there has been no previous 
call to :link reftype=hd res=221.SetHeaderMode:elink. and :link reftype=hd 
res=220.SetHeader:elink..
:warning.
:hp2.You MUST make a call to the :link reftype=hd res=221.SetHeaderMode:elink. 
and :link reftype=hd res=220.SetHeader:elink. methods before calling this method:ehp2.
:ewarning.

:h2 hide res=962.SetHeaderLineFont - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.linenum
:pd.The line number in the header whose font is to be set
:pt.font
:pd.The font to use for printing the line
:pt.points
:pd.The point size to be used for printing
:eparml.

:h2 hide res=963.SetHeaderLineFont - Example
:xmp.

/****************************************************************/
/* Print the header on all the pages with default 10 pt         */
/* Helvetica bold, a .05mm line around and halftone fill.       */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeaderMode", 1, 'Helvetica Bold', 10, 8, 28, 1);

/****************************************************************/
/* Set the header with the doc title on the first line centred, */
/* the date on the second line right justified and some other   */
/* text. There are 3 lines in the header.                       */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeader", 3, ,
                       "$c|",, 
                       "$lADD Consulting (CH)$r@",,
                       'Demo for VRPrinter Object for VX-REXX');

/****************************************************************/
/* Change the point size for the first line.                    */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeaderLineFont", 1, , 12);

/****************************************************************/
/* Change the font and point size for the third line.           */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeaderLineFont", 3, "Helvetica", 8);

:exmp.

.***** SetHeaderMode *************************************************
 
:h2 res=221.SetHeaderMode
:i2 refid=FUNC.SetHeaderMode
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=970.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=971.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=972.

:h2 hide res=970.SetHeaderMode - List
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
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=235.SetHeaderLineFont:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:eul.

:h2 hide res=971.SetHeaderMode - Description
:xmp.
ok = VRMethod( object, "SetHeaderMode", 
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
with :link reftype=hd res=235.SetHeaderLineFont:elink., the text will be printed in the font 
and point size defined with this method. If you don't define any colours, the default colour 
will be used.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=972.SetHeaderMode - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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
:pd.A combination of the following flags that defines which sides of the box around the header are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=973.SetHeaderMode - Example
:xmp.

/****************************************************************/
/* Print the header on all the pages in 10 pt Helvetica bold    */
/* with a .05mm blue line around and filled with cyan halftone. */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetHeaderMode", 1, 'Helvetica Bold', 10, 8, 28, 1, "Blue", "Cyan");

:exmp.

.***** SetMargins ****************************************************
 
:h2 res=222.SetMargins
:i2 refid=FUNC.SetMargins
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=980.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=981.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=982.

:h2 hide res=980.SetMargins - List
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
:li.:link reftype=hd res=219.SetFooter:elink.
:li.:link reftype=hd res=220.SetHeader:elink.
:li.:link reftype=hd res=221.SetHeaderMode:elink.
:eul.

:h2 hide res=981.SetMargins - Description
:xmp.
ok = VRMethod( object, "SetMargins", 
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

:h2 hide res=982.SetMargins - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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
:pd.A combination of the following flags that defines which sides of the box around the page are drawn&colon.
.br
1 = Left side
.br
2 = Right side
.br
4 = Top side
.br
8 = Bottom side
:eparml.

:h2 hide res=983.SetMargins - Example
:xmp.
/****************************************************************/
/* Set the margins to left 25mm right 20mm top 20mm bottom 25mm */
/* and set the page to filled with green halftone with a black  */
/* 1mm border.                                                  */
/****************************************************************/

ok = VRMethod( "PRT_1", "SetMargins", 25, 20, 20, 25, 56, 8, "Black", "Green");
 
:exmp.
 
.***** SetPrinter ****************************************************
 
:h2 res=223.SetPrinter
:i2 refid=FUNC.SetPrinter
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=990.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=991.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=992.

:h2 hide res=990.SetPrinter - List
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
:li.:link reftype=hd res=218.PrinterList:elink.
:li.:link reftype=hd res=216.OpenPrintJob:elink.
:eul.

:h2 hide res=991.SetPrinter - Description
:xmp.
ok = VRMethod( object, "SetPrinter", 
                       idx);
:exmp.
:font facename=Helv size=16x12.
:p.For programs that do not use :link reftype=hd res=217.PrinterDialog:elink., the printer MUST 
be set using this method if you do not want to use the default printer. The index refers to the 
position of the chosen printer name in the the stem variable returned by :link reftype=hd 
res=218.PrinterList:elink. and is 1 based.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=992.SetPrinter - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.idx
:pd.Index of the printer in the list returned by :link reftype=hd res=218.PrinterList:elink. If 
this variable is missing or set to 0, the default printer will be selected.
:eparml.


.***** SetProgressTexts *************************************************

:h2 res=715.SetProgressTexts
:i2 refid=FUNC.SetProgressTexts
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1000.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1001.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1002.

:h2 hide res=1000.SetProgressTexts - List
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

:h2 hide res=1001.SetProgressTexts - Description
:xmp.
ok = VRMethod( object, "SetProgressTexts", 
                       "texts.");
:exmp.
:font facename=Helv size=16x12.
:p.This method allows to customise the Progress dialog. Any of the input stem parameter fields 
may be left blank, in which case they assume the defaut values.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1002.SetProgressTexts - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

.***** StartCol ******************************************************
 
:h2 res=224.StartCol
:i2 refid=FUNC.StartCol
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1010.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1011.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1012.

:h2 hide res=1010.StartCol - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:eul.

:h2 hide res=1011.StartCol - Description
:xmp.
ok = VRMethod( object, "StartCol", 
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
A Table must have been previously declared.

:h2 hide res=1012.StartCol - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.column
:pd.Number of the column to start printing.
:eparml.

.***** StartRow ******************************************************
 
:h2 res=225.StartRow
:i2 refid=FUNC.StartRow
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1020.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1021.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1022.

:h2 hide res=1020.StartRow - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=226.StartTable:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=206.EndRow:elink.
:eul.

:h2 hide res=1021.StartRow - Description
:xmp.
ok = VRMethod( object, "StartRow");
:exmp.
:font facename=Helv size=16x12.
:p.Instructs the program that a new row in a table is to be started. All printing commands 
following this call will be directed into the last column that was declared. You :hp2.MUST:ehp2. 
follow this call by a call to :link reftype=hd res=224.StartCol:elink. otherwise you may 
generate an Access Violation.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).
:note.
.br
A table must have been previously declared.

:h2 hide res=1022.StartRow - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

.***** StartTable ****************************************************
 
:h2 res=226.StartTable
:i2 refid=FUNC.StartTable
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1030.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1031.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1032.

:h2 hide res=1030.StartTable - List
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
:li.:link reftype=hd res=200.DefineTable:elink.
:li.:link reftype=hd res=225.StartRow:elink.
:li.:link reftype=hd res=224.StartCol:elink.
:li.:link reftype=hd res=206.EndRow:elink.
:li.:link reftype=hd res=207.EndTable:elink.
:li.:link reftype=hd res=240.ResetColHeader:elink.
:eul.

:h2 hide res=1031.StartTable - Description
:xmp.
ok = VRMethod( object, "StartTable", 
                       fill, 
                       line, 
                       numcols, 
                       lm, 
                       width 
                       [, width]);
:exmp.
:font facename=Helv size=16x12.
:p.Defines a table for printing. If there are not the right number of :hp2.lm, rm:ehp2. pairs 
the method will return FALSE.
:p.This call only prepares the internal structures for handling a table, to start printing 
the table you must call :link reftype=hd res=225.StartRow:elink. and :link reftype=hd 
res=224.StartCol:elink..
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1032.StartTable - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
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

:h2 hide res=1033.StartTable - Example
:xmp.
/************************************************************************/
/* Declare a table with no fill style, 0.5 mm separator lines and       */
/* 3 columns                                                            */
/************************************************************************/

ok = VRMethod( "PRT_1", "StartTable", 0, 24, 3,,
                        30,45,,
                        75,50,,
                        125,40);

if rcy then do

    /**** Start printing in the table **********************************/
    
    ok = VRMethod( "PRT_1", "StartRow");
    
    /**** Start printing in column 2 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 1);
    ok = VRMethod( "PRT_1", "PrintRight", 'Helvetica', 10, textvar);
    
    /**** Start printing in column 2 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 2);
    ok = VRMethod( "PRT_1", "PrintJustified", 'Helvetica Bold', 10, textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    
    /**** Start printing in column 3 ***********************************/
    
    ok = VRMethod( "PRT_1", "StartCol", 3);
    ok = VRMethod( "PRT_1", "PrintCentered", 'Helvetica Bold', 14, textvar);
    
    /**** Print the row ************************************************/
    
    ok = VRMethod( "PRT_1", "EndRow");
    
    /**** Start a new row **********************************************/
    
    ok = VRMethod( "PRT_1", "StartRow");
    ok = VRMethod( "PRT_1", "StartCol", 1);
    ok = VRMethod( "PRT_1", "PrintRight", 'Times New Roman', 10, textvar);
    ok = VRMethod( "PRT_1", "StartCol", 2);
    ok = VRMethod( "PRT_1", "PrintLeft", 'Helvetica Bold', 10, textvar);
    ok = VRMethod( "PRT_1", "PrintCentered",,,textvar);
    ok = VRMethod( "PRT_1", "PrintJustified",,,textvar);
    ok = VRMethod( "PRT_1", "PrintRight",,,textvar);
    ok = VRMethod( "PRT_1", "StartCol", 3);
    ok = VRMethod( "PRT_1", "PrintJustified", 'Times New Roman', 8, textvar);
    
    /**** Print the row ************************************************/
    
    ok = VRMethod( "PRT_1", "EndRow");
    
    /**** Destroy the table data structures ****************************/
    
    ok = VRMethod( object, "EndTable");
end

:exmp.

.***** StringLength **********************************************

:h2 res=1076.StringLength
:i2 refid=FUNC.StringLength
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1077.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1078.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1079.

:h2 hide res=1077.StringLength - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1078.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1079.Parameters:elink. 
:eul.
:p.:hp2.See Also:ehp2.
:ul compact.
:li.:link reftype=hd res=702.BlockFits:elink.
:li.:link reftype=hd res=203.PrintCentered:elink.
:li.:link reftype=hd res=212.PrintJustified:elink.
:li.:link reftype=hd res=213.PrintRight:elink.
:li.:link reftype=hd res=230.PrintLeft:elink.
:li.:link reftype=hd res=231.PrintLine:elink.
:li.:link reftype=hd res=234.FontDialog:elink.
:li.:link reftype=hd res=714.LineFits:elink.
:eul.

:h2 hide res=1078.StringLength - Description
:xmp.
len = VRMethod( object, "StringLength", 
                         face_name, 
                         points, 
                         string);
:exmp.
:font facename=Helv size=16x12.
:p.Returns the length of the given string in the chosen :link reftype=hd res=314.Measures:elink..
:p.:hp2.Return:ehp2.
:p.-1 if the string is longer than the width of the page (left to right margins), otherwise length 
of the string in mm or tenths of an inch.
:note.
.br
:hp2.No text is actually printed.:ehp2.

:h2 hide res=1079.StringLength - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.face_name
:pd.Name of the font used to print. This MUST be an outline font. If this is left empty, 
the previous font is used.
:pt.points
:pd.Point size of the font, If this is left empty, the previous font size is used.
:pt.string
:pd.The string to be printed.
:eparml.

.***** Tab *******************************************************
 
:h2 res=227.Tab
:i2 refid=FUNC.Tab
:link reftype=hd auto split group=1 scroll=vertical vpx=left vpy=top vpcx=30% vpcy=100% 
titlebar=none rules=border res=1040.
:link reftype=hd auto split group=2 scroll=vertical vpx=right vpy=top vpcx=70% vpcy=60% 
res=1041.
:link reftype=hd auto split group=3 scroll=vertical vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1042.

:h2 hide res=1040.Tab - List
:font facename=Helv size=16x12.
:p.:hp2.Topics:ehp2.
:ul compact.
:li.:link reftype=hd group=2 scroll=vertical split vpx=right vpy=top vpcx=70% vpcy=60% 
res=1041.Description:elink. 
:li.:link reftype=hd group=3 scroll=vertical split vpx=right vpy=bottom vpcx=70% vpcy=40% 
res=1042.Parameters:elink. 
:eul.

:h2 hide res=1041.Tab - Description
:xmp.
ok = VRMethod( object, "Tab");
:exmp.
:font facename=Helv size=16x12.
:p.Move to the next tab position on the line. Tabs are set when a print job is opened and 
are placed every 10 millimetres or 1/2 inch depending on the :link reftype=hd 
res=314.Measures:elink. property starting at the left margin.
:p.:hp2.Return:ehp2.
:p.TRUE (1) if successful else FALSE (0).

:h2 hide res=1042.Tab - Parameters
:font facename=Helv size=16x12.
:parml compact tsize=20 break=none.
:pt.None
:eparml.

:euserdoc.
.************************************************************************
.*                                                                      *
.*                         (c) ADD Consulting 1995                      *
.*                                                                      *
.*                               END OF FILE.                           *
.*                                                                      *
.************************************************************************