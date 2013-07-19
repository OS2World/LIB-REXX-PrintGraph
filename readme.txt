This is the last available build of Peter Kanis' "Print Graph" and "VR Print" libraries
for OS/2 REXX.  These are powerful printer formatting libraries that allow the user
to print complex documents.  Tables, columns, textwrapping and graphics are some of
the major supported features.

The registration number is
F86F-AF19-8124-8F2B

These is the instructions received from Peter:

I donated all my OS/2 libraries to the public domain and no 
longer support them. However, the site www.CyberEnt.com seems to have closed, 
so all I can do is give you access to the source code I gave them 
through my site. This code includes all the source code for building VRPrinter, 
PrtRexx etc.. but it was about 5 years ago that I handed over the code 
so you'll have to work it out from the makefiles. I haven't any 
workstations running OS/2 anymore and really don't have time to install one, so I 
just added the files to my web site so you can get them.

You'll need the VX-ODK <snip>
You will need to install the VX-ODK by unzipping the diskette 
images and running the install. Then unzip the printing.zip into your 
source code directory. Make a new dir (prtgraph and unzip the prtgraph zip 
file there. If I remember correctly, you will need to set the environment 
variables DEFMAK and AMAK to point to the global make files in the make 
directory. You will have to have a VisualAge for C++ or CSet++ installed, 
you should then be able to build the whole thing using nmake. Again, if I 
remember right 'cos it's a long time ago, the VX-REXX version has to be 
built with a script in the directory, just poke around in the code; it 
should be reasonably well documented with comments.

I hope this helps, best regards,

Peter Kanis

