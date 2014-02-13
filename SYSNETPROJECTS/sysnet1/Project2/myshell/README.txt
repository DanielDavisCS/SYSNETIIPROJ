@mainpage System and Networks I Project 2
@last modified September 29, 2013

@author Cole Amick
@author Daniel Davis

@files required
parse.c
parse.h
Makefile
myshell.c

@how to compile
make

@how to run
./myshell

@description of program

Takes input from user and stores into buffer.
Then parses the buffer and initalizes the required parameters in data
structures. Before each iteration of user input the input buffer and data
structure is freed.


Runs a basic shell program for processing basic system commands. 
Calls the parser program to get the user input and then runs myshell.c program
to create child processes of the main shell to run system commands. Can run
both foreground and background processes. Program waits for all children processes
to finish that are running. All memory is freed. 

@additional notes
We set a predefined size of 100 for the size of each token or name deliminted
by only spaces. 
There is a set limit of only 32 arguments that can be entered into input.
There are no spaces allowed between file redirection symbols (< or >) and the
name of the file. Acceptable file names include any non-white spaced
characters. 
The first name of the input cannot be a file redirection symbol or a
ampersand. 
Type only exit and then the program will terminate. 
