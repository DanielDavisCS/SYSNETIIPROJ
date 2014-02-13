@mainpage System and Networks I Project 3
@last modified October 8, 2013

@author Cole Amick
@author Daniel Davis

@files required
mt-prime.c
Makefile

@how to compile
make

@how to run
./mt-prime <maximum number for primality> <number of threads>

Ex) ./mt-prime 1000 8
The above command runs 8 threads calculating primality between 0 to 1000. 

@description of program
Takes the second command line argument as the number to calculate up to for primality. 
Takes the third command line arugment as the number of threads to run the primality check. 
Displays all the prime numbers in that range to the display or stdout.
When finish calculating the primality, the program will display the user entered primality number, 
the number of threads that was given for the program to run with, and also the time that it took 
to complete the primality test for the given range. This can also be sent to stderr. The time is
in seconds with a precision in nanoseconds. 

@additional notes
Enter only numbers for the second and third command line arguments. 
Limiting the number of threads to 100 is recommend. Anything over 100 threads might cause the 
program to cause fail (This depends upon the machine that the threads are created on). 
