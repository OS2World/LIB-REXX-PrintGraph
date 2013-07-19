/*** Run Command File out of VX-REXX ***/

'@echo off'

parse source s1 s2 s3

parse arg proc

s1 = substr(  s3, 1, lastpos( '\', s3) - 1)
s2 = substr(  s3, 1, pos( '\', s3) - 1)
s2
'cd' s1

'start /f /c' proc

exit

