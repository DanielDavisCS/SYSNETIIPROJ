/***************************************************************/
/*                                                             */
/* lizard.c                                                    */
/*                                                             */
/* To compile, you need all the files listed below             */
/*   lizard.c                                                  */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   gcc -g -Wall lizard.c -o lizard -lpthread                 */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#ifdef __APPLE__
#include <mach/semaphore.h>
#include <mach/task.h>
#define sem_init(a,b,c)     semaphore_create(mach_task_self(), (semaphore_t *)a, SYNC_POLICY_FIFO, c)
#define sem_destroy(a)      semaphore_destroy(mach_task_self(), *((semaphore_t *)a))
#define sem_post(a)         semaphore_signal(*((semaphore_t *)a))
#define sem_wait(a)         semaphore_wait(*((semaphore_t *)a))
#define sem_t               semaphore_t
#else
#include <semaphore.h>
#endif

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */

/*
 * Function prototypes go here
 * You may need more functions, but I don't think so
 */
void * lizardThread( void * param );


/*
 * Define "constant" values here
 */

/*
 * Make this 1 to check for lizards traving in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             30
/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          20

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP     3

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT       5

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        2


/*
 * Declare global variables here
 */
/*	Modified: Cole Amick and Daniel Davis on 10/16/2013
 *	Changes Made: declared semaphores and mutex locks  
 */
sem_t GUARD;
pthread_mutex_t S2GMUTEX, G2SMUTEX;

/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass;
int numCrossingMonkeyGrass2Sago;
int debug;
int running;
/**************************************************/






/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv)
{
  /*
   * Declare local variables
   *
   *	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made: declared lizardNames for thread identfication, declared lizard threads 
   */

	int i; //for lizard thread count
	int lizardNames[NUM_LIZARDS]; //passed to lizardThread as lizard ID
	pthread_t lizards[NUM_LIZARDS];	
	int lizardThreadSuccess[NUM_LIZARDS]; //variables to check the successful completion of a lizard threads creation
  /*
   * Check for the debugging flag (-d)
   */
  debug = 0;
  if (argc > 1)
    if (strncmp(argv[1], "-d", 2) == 0)
      debug = 1;


  /*
   * Initialize variables
   */
  numCrossingSago2MonkeyGrass = 0;
  numCrossingMonkeyGrass2Sago = 0;
  running = 1;
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made:Initialized lizard IDs 
   */
	for(i = 0; i < NUM_LIZARDS; i++ ) lizardNames[i] = i+1;
	
  /*
   * Initialize random number generator
   */
  srandom( (unsigned int)time(NULL) );


  /*
   * Initialize locks and/or semaphores
   */


   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made:Initialized mutex locks and semephore
   */
  pthread_mutex_init(&S2GMUTEX, NULL);  
  pthread_mutex_init(&G2SMUTEX, NULL);  
  sem_init(&GUARD, 0, MAX_LIZARD_CROSSING);


  /*
   * Create NUM_LIZARDS lizard threads
   */
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made: code to create threads and run lizardThread function  
   *	ALSO checks thread creation success  
   */
	
	for(i = 0; i < NUM_LIZARDS; i++){
		lizardThreadSuccess[i]  = pthread_create(&(lizards[i]),NULL, &lizardThread , (void *) &lizardNames[i]);
	}

  /*
   * Now let the world run for a while
   */
  sleep( WORLDEND );

  /*
   * That's it - the end of the world
   */
  running = 0;


  /*
   * Wait until all threads terminate
   */
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made: main waites for threads to exit 
   */
	for(i = 0; i < NUM_LIZARDS; i++){
		if(lizardThreadSuccess[i] == 0 )
			pthread_join(lizards[i], NULL); //main stops until threads exit
	}
	
   /*
    * Delete the locks and semaphores
    */
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made: destroy semaphores and mutex 
   */
	sem_destroy(&GUARD);
	pthread_mutex_destroy(&S2GMUTEX);
	pthread_mutex_destroy(&G2SMUTEX);

  /*
   * Exit happily
   */
  return 0;
}


/*
 * These prototypes are declared here so that main()
 * can't use them directly.  Functions and variables
 * must be declared before they can be used.  Using them
 * below this point is fine.
 */

void lizard_sleep(int num);
void sago_2_monkeyGrass_is_safe(int num);
void cross_sago_2_monkeyGrass(int num);
void made_it_2_monkeyGrass(int num);
void lizard_eat(int num);
void monkeyGrass_2_sago_is_safe(int num);
void cross_monkeyGrass_2_sago(int num);
void made_it_2_sago(int num);


/*
 * lizardThread()
 *
 * Follows the algorithm provided in the assignment
 * description to simulate lizards crossing back and forth
 * between a sago palm and some monkey grass.  
 * input: lizard number
 * output: N/A
 * Status: completed 10.17.13 - Make changes as you see are necessary.
 */
void * lizardThread( void * param )
{
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
   *	Changes Made: pointer typdefing 
   */
	int *  num = (int * ) param;
  if (debug)
    {
   /*	Modified: Cole Amick and Daniel Davis on 10/16/2013
	Changes Made: dereference pointer error 10.16.13
   */
      printf("[%2d] lizard is alive\n", *num);
      fflush(stdout);
    }

  while(running)
    {
      /* 
       * Follow the algorithm given in the assignment
       * using calls to the functions declared above.
       * You'll need to complete the implementation of
       * some functions by filling in the code.  Some  
       * are already completed - see the comments.
       */
   	/*	Modified: Cole Amick and Daniel Davis on 10/16/2013
		Changes Made: implemented syncronzation algorithm
   	*/
	lizard_sleep(*num); //lizard sleeps in the sago
	sago_2_monkeyGrass_is_safe(*num);
	cross_sago_2_monkeyGrass( *num); //lizard taking his sweet a$$ time 
	made_it_2_monkeyGrass(*num); //includes sem_post
	//
	lizard_eat( *num); //made it to money grass and is eating
	monkeyGrass_2_sago_is_safe(*num);
	cross_monkeyGrass_2_sago(*num); // crossing
	made_it_2_sago(*num);
    }
  pthread_exit(NULL);
}


/*
 * lizard_sleep()
 *
 * Simulate a lizard sleeping for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_sleep(int num)
{
  int sleepSeconds;

  sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

  if (debug)
    {
      printf( "[%2d] sleeping for %d seconds\n", num, sleepSeconds );
      fflush( stdout );
    }

  sleep( sleepSeconds );

  if (debug)
    {
      printf( "[%2d] awake\n", num );
      fflush( stdout );
    }
}

 
/*
 * sago_2_monkeyGrass_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Complete - 10/17/13 - Lock Semaphore Guard 
 */
void sago_2_monkeyGrass_is_safe(int num)
{
  if (debug)
    {
      printf( "[%2d] checking  sago -> monkey grass\n", num );
      fflush( stdout );
    }
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Signal to lock the Semaphore Guard for the driveway by decrementing the guard counter
 	*/
	sem_wait(&GUARD); //wait to cross the driveway because do not want to be eatin!!
  if (debug)
    {
      printf( "[%2d] thinks  sago -> monkey grass  is safe\n", num );
      fflush( stdout );
    }
}


/*
 * cross_sago_2_monkeyGrass()
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 * input: lizard number
 * output: N/A
 * Status: Complete - 10/17/2013 - Lock and Unlock the Sago to Monkey Grass Mutex. 
 */
void cross_sago_2_monkeyGrass(int num)
{
  if (debug)
    {
      printf( "[%2d] crossing  sago -> monkey grass\n", num );
      fflush( stdout );
    }

  /*
   * One more crossing this way
   */
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Sago to Monkey Grass Mutex is thread safe for incrementing using a lock
 	*/
	pthread_mutex_lock(&S2GMUTEX);
  		numCrossingSago2MonkeyGrass++;
	pthread_mutex_unlock(&S2GMUTEX);

  /*
   * Check for too many lizards crossing
   */
  if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING)
    {
      printf( "\tThe cats are happy - they have toys.\n" );
      printf( "\t%d crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass );
      exit( -1 );
    }
  
  /*
   * Check for lizards cross both ways
   */
  if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL)
    {
      printf( "\tCrash!  We have a pile-up on the concrete.\n" );
      printf( "\t%d crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass );
      printf( "\t%d crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago );
      exit( -1 );
    }

  /*
   * It takes a while to cross, so simulate it
   */
  sleep( CROSS_SECONDS );

  /*
   * That one seems to have made it
   */
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Sago to Monkey Grass Mutex is thread safe for decrementing using a lock
 	*/
	pthread_mutex_lock(&S2GMUTEX);
  		numCrossingSago2MonkeyGrass--;
	pthread_mutex_unlock(&S2GMUTEX);
}


/*
 * made_it_2_monkeyGrass()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status:  Complete - 10/17/13 - Unlock Semaphore Guard
 */
void made_it_2_monkeyGrass(int num)
{
  /*
   * Whew, made it across
   */
  if (debug)
    {
      printf( "[%2d] made the  sago -> monkey grass  crossing\n", num );
      fflush( stdout );
    }
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Signal to unlock the Semaphore Guard for the driveway by incrementing the guard counter
 	*/
	sem_post(&GUARD); //now more can cross
}


/*
 * lizard_eat()
 *
 * Simulate a lizard eating for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_eat(int num)
{
  int eatSeconds;

  eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

  if (debug)
    {
      printf( "[%2d] eating for %d seconds\n", num, eatSeconds );
      fflush( stdout );
    }

  /*
   * Simulate eating by blocking for a few seconds
   */
  sleep( eatSeconds );

  if (debug)
    {
      printf( "[%2d] finished eating\n", num );
      fflush( stdout );
    }
}


/*
 * monkeyGrass_2_sago_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Complete - 10/17/13 - Lock Semaphore Guard 
 */
void monkeyGrass_2_sago_is_safe(int num)
{
  if (debug)
    {
      printf( "[%2d] checking  monkey grass -> sago\n", num );
      fflush( stdout );
    }
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Signal to lock the Semaphore Guard for the driveway by decrementing the guard counter
 	*/
	sem_wait(&GUARD); //wait to cross the driveway because do not want to be eatin!!
  if (debug)
    {
      printf( "[%2d] thinks  monkey grass -> sago  is safe\n", num );
      fflush( stdout );
    }
}



/*
 * cross_monkeyGrass_2_sago()
 *
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 * input: lizard number
 * output: N/A
 * Status: Complete - 10/17/2013 - Lock and Unlock the Monkey Grass to Sago Mutex. 
 */
void cross_monkeyGrass_2_sago(int num)
{
  if (debug)
    {
      printf( "[%2d] crossing  monkey grass -> sago\n", num );
      fflush( stdout );
    }

  /*
   * One more crossing this way
   */
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Monkey Grass to Sago Mutex is thread safe for incrementing using a lock
 	*/
	pthread_mutex_lock(&G2SMUTEX);
  		numCrossingMonkeyGrass2Sago++;
	pthread_mutex_unlock(&G2SMUTEX);

  /*
   * Check for too many lizards crossing
   */
  if (numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass > MAX_LIZARD_CROSSING)
    {
      printf( "\tThe cats say yum! - they love lizards.\n" );
      printf( "\t%d crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago );
      exit( -1 );
    }
  
   /*
   * Check for lizards cross both ways
   */
  if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL)
    {
      printf( "\tOh No!, the lizards have cats all over them.\n" );
      printf( "\t%d crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass );
      printf( "\t%d crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago );
      exit( -1 );
    }

  /*
   * It takes a while to cross, so simulate it
   */
  sleep( CROSS_SECONDS );

  /*
   * That one seems to have made it
   */
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Monkey Grass to Sago Mutex is thread safe for decrementing using a lock
 	*/
	pthread_mutex_lock(&G2SMUTEX);
  		numCrossingMonkeyGrass2Sago--;
	pthread_mutex_unlock(&G2SMUTEX);
}


/*
 * made_it_2_sago()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status: Complete - 10/17/2013 - Unlock Semaphore Guard
 */
void made_it_2_sago(int num)
{
  /*
   * Whew, made it across
   */
  if (debug)
    {
      printf( "[%2d] made the  monkey grass -> sago  crossing\n", num );
      fflush( stdout );
    }
	/*	Modified: Cole Amick and Daniel Davis on 10/17/2013
 	*	Changes: Signal to unlock the Semaphore Guard for the driveway by incrementing the guard counter
 	*/
	sem_post(&GUARD); //now more can cross
}
