CFLAGS = -g -Wall
CC = gcc

all: server

objects = TCPserverMain.o TCPserver.o

server: $(objects)
	$(CC) -o server $(objects) 

TCPserver.o: TCPserver.c
TCPserverMain.o: TCPserverMain.c

.PHONY : clean
clean: 
	rm server $(objects)
