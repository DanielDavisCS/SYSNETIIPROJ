CFLAGS = -g -Wall
CC = gcc

all: proj6

objects = disk.o fileSystem.o inode.o

proj6: $(objects)
	$(CC) -o proj6 $(objects) 

disk.o: disk.c
fileSystem.o: fileSystem.c
inode.o: inode.c

.PHONY : clean
clean: 
	rm proj6 $(objects)
