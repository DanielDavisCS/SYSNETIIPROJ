@mainpage System and Networks I Project 4
@last modified October 22, 2013

@author Cole Amick
@author Daniel Davis

@files required
lizard.c
Makefile

@how to compile
make

@how to run
./lizard 
OR
./lizard -d

@description of program
This program creates multiple threads representing lizards and these lizards attempt to cross
a driveway between sago palm trees where they sleep and monkey grass where they eat. However,
only a limited number of lizards are able to cross the driveway at one time. If too many lizards
cross the driveway at the same time, then another thread that represents a cat will come out
and eat the lizards and the program will terminate. A error message will be displayed indicating 
that the cat thread found too many lizard threads running and crossing the driveway. If no message
is indicated, then the program ran successfully. Use the -d option when running the program to 
display debugging messages about the location of each lizard and what action the lizard is 
attempting to perform. We used to semaphores to implement safety for the lizards to cross
the driveway. Unfortunately, the cat must starve to DEATH :). 

@additional notes
In the lizard.c file there are predefined values representing conditions for the program to run with.
*) UNIDIRECTIONAL - Set to 0 to allow bidirectional travel on the driveway else set to 1. 
*) WORLDEND - Indicate how long to let the program run for. 
*) NUM_LIZARDS - Sets the number of threads representing lizards to create.
*) MAX_LIZARD_CROSSING - Sets the maximum number of lizards allowed to cross the driveway at one time. 
*) MAX_LIZARD_SLEEP - Sets the maximum amount of time a lizard can sleep. 
*) MAX_LIZARD_EAT - Sets the maximum amount of time a lizard can eat. 
*) CROSS_SECONDS - Sets the amount of time it takes a lizard to cross the driveway. 

NOTE: The program is only implemented with BIDIRECTIONAL travel across the driveway. 
