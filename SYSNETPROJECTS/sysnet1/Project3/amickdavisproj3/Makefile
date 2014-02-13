CFLAGS = -g -Wall
CC = gcc

all: mt-prime

objects = mt-prime.o

mt-prime: $(objects)
	$(CC) -o mt-prime $(objects) -lm -lpthread -lrt

mt-prime.o: mt-prime.c

.PHONY : clean
clean: 
	rm mt-prime $(objects)
