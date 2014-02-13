@mainpage System and Networks I Project 5
@last modified November 4, 2013

@author Cole Amick
@author Daniel Davis

@files required
matrix.c
Makefile

@how to compile
make

@how to run
./matrix

@description of program
This program is to demonstrate efficiency differences in Row Major versus Column Major.
These differences occur because pages in memory are laid out in row major.
This program measures the differences by writing and reading via different algorithms. 
The rows and columns are written to first and then the row and columns are read into a temporary variable. 
Each algorithm runs 10 times and the average time required for the algorithm is outputted in 
seconds with a precision in nano-seconds. 

@additional notes
A character matrix was created as a global variable. 
The size of each row is 4096B or 4096 chars.
There are 20480 rows created for the matrix.
We used "clock_gettime" to calculate the time required for the algorithms. 