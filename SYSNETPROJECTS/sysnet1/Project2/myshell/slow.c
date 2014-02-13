/**	@file slow.c
 * 	@brief Program for running slow
 *  Used in the myshell program to run a process slowly. 
 *	@author Cole Amick
 *	@author Daniel Davis
 *	@bug No known bugs!
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int i;
	int pid = getpid();
	for(i = 0; i < 10; i++) {
		sleep(1);
		printf("slow  %6d: %d\n", pid, i);
		fflush(NULL);
	}
	return 0;
}
