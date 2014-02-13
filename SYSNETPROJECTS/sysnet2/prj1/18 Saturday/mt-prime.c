/**	@file mt-prime.c
 * 	@brief Runs a multi-thread program for calculating primality of numbers.
 *	User indicates the number to calculate up to for primality. User also 
 *	gives the number of threads to use for calculation. Prints out the time
 *	in nanoseconds for the threads to run. 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/**************************** */
#define TRUE 1
#define FALSE 0
#define BILLION 1E9;
/* prime number count */
int COUNTER = 0; 

/*	structure to hold thread data */
typedef struct mThreadData {
	int maxcount;
	int threadcount;	
	struct timespec timeStructStart, timeStructEnd;
}mThreadData_T ;

/* pointer to thread structure */
typedef mThreadData_T *mThreadData_P;


/**	@brief Creates the threads, calls the function to run the threads.
	Waits for threads to terminate and join them with the main thread.
	Prints out the time results for the threads to run. 
*	@param mThreadData_p is a pointer to the thread data structure. 
			argv is the argument vector
*	@return void. 
*/
void runPrime(mThreadData_P mThreadData_p, char **argv);

/**	@brief 	checks the arguments that user entered. 
*	@param 	argc is the argument count
*			argv is the argument vector
*	@return 0 if theere is an error, else returns 1. 
*/
int errorCheck(int argc, char **argv);

/**	@brief 	calculates the primality. 
*	@param 	count is the number to check for primality. 
*	@return returns the number if it is prime else returns 0. 
*/
int isPrime(int count);

/**	@brief Runs the threads and calls isPrime and prints out number if it is prime.
*	@param This void pointer should be of type mThreadData_P.
*	@return void.
*/
void *runThread(void *param);

/**	@brief 	Calculates the total time for the threads to run the primality test. 
*	@param 	timeStructStart struct containing the start time
*			timeStructEnd struct containing the end time 
*	@return returns real elapse time to nanosecond precision. 
*/
double calculateTime(struct timespec timeStructStart, struct timespec timeStructEnd);

/**	@brief
*	@param 	argc is the argument count
*			argv is the argument vector from the command line
*	@return to the operating system. 
*/
int main(int argc, char **argv)
{
	mThreadData_T mThreadData_t;
	mThreadData_P mThreadData_p = &mThreadData_t;	
	if(errorCheck(argc, argv))
		runPrime(mThreadData_p, argv);
	return 0;
}
 /*********************************************/
void runPrime(mThreadData_P mThreadData_p, char **argv) {
	mThreadData_p->maxcount = atoi(argv[1]);
	mThreadData_p->threadcount = atoi(argv[2]);
	pthread_t threads[mThreadData_p->threadcount];
	int i = 0, threadCount[mThreadData_p->threadcount];
	//start time 
	clock_gettime(CLOCK_REALTIME, &(mThreadData_p->timeStructStart));
	//creates the threads and call the function to run the threads
	for(i = 0; i < mThreadData_p->threadcount; i++)
		threadCount[i] = pthread_create(&(threads[i]), NULL, runThread, (void *) mThreadData_p);
	//joins the threads with the main thread 
	for(i = 0; i < mThreadData_p->threadcount; i++)
		if(threadCount[i] == 0) pthread_join(threads[i], NULL);
	//end time
	clock_gettime(CLOCK_REALTIME, &(mThreadData_p->timeStructEnd));
	fprintf(stderr, "%i,%i,", mThreadData_p->maxcount, mThreadData_p->threadcount);
	fprintf(stderr, "%.9lf\n",	calculateTime(mThreadData_p->timeStructStart, mThreadData_p->timeStructEnd));
}
/*********************************************/
double calculateTime(struct timespec timeStructStart, struct timespec timeStructEnd) {
	return (timeStructEnd.tv_sec - timeStructStart.tv_sec) + (timeStructEnd.tv_nsec - timeStructStart.tv_nsec) / BILLION; 
}
 /*********************************************/
int errorCheck(int argc, char **argv) {
	if(argc != 3) {
		printf("Invalid Number of Arguments!\n");
		return 0;
	}
	if(atoi(argv[2]) <= 0) {
		printf("Must have at least one thread!\n");
		return 0;
	}
	else return 1;
}
 /*********************************************/
void *runThread(void *param){
	mThreadData_P mThreadData_p = (mThreadData_P) param;
	while(COUNTER <= mThreadData_p->maxcount) { 
		int num = isPrime(COUNTER++);
		if(num) printf("%i\n", num);
   	}
	pthread_exit(0);
}
 /*********************************************/
int isPrime(int count){
	int div;
	if(count == 2) return count;
	if(count < 2 || fmod(count,2) == 0)return 0;
	for(div = 3; div <= sqrt((double)count); div = div + 2)
		if(fmod(count,div) == 0) return 0; 
	return count;
}