CFLAGS = -g -Wall -O0
CC = gcc

all: matrix

objects = matrix.o

matrix: $(objects)
	$(CC) -o matrix $(objects) -lrt

matrix.o: matrix.c

.PHONY : clean
clean: 
	rm matrix $(objects)
