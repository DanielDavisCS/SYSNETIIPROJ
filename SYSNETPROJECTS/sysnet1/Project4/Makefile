CFLAGS = -g -Wall
CC = gcc

all: lizard

objects = lizard.o

lizard: $(objects)
	$(CC) -o lizard $(objects) -lpthread

lizard.o: lizard.c

.PHONY : clean
clean: 
	rm lizard $(objects)
