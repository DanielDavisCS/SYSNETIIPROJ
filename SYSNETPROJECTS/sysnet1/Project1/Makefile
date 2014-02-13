CFLAGS = -g -Wall
CC = gcc

objects = parse.o

test: $(objects)
	$(CC) -o test $(objects)

parse.o: parse.c

clean: 
	rm test $(objects)
