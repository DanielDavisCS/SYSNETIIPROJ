CFLAGS = -g -Wall
CC = gcc

all: myshell slow

objects = parse.o myshell.o

myshell: $(objects)
	$(CC) -o myshell $(objects)

slow: slow.o
	$(CC) -o slow slow.o

parse.o: parse.c parse.h

myshell.o: myshell.c parse.h

slow.o: slow.c

.PHONY : clean
clean: 
	rm myshell $(objects) slow slow.o
