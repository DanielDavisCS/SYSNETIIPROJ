/**	@file matrix.c
 * 	@brief  This program is to demonstrate efficiency differences in Row Major versus Column Major.
 *	These differences occur because pages in memory are laid out in row major.
 *	This program measures the differences by writing and reading via different algorithms. 
 *	Outputs the time required for the algorithm in seconds with a precision in nano-seconds. 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
 
/*	include the following libraries  */
#include <stdio.h>
#include <time.h>

/*	preprocessor directive  */
#define NUM_ROW 20480	//number of rows for matrix 
#define NUM_COL 4096 	//the number of columns and exactly 4096B for matrix 
#define COUNT 10 		//the number of times to repeat each function 
#define BILLION 1E9 	//1 billion 

/*	global matrix */
char MATRIX[NUM_ROW][NUM_COL];

/*	structure to hold matrix data */
typedef struct MatrixData {
  double writeRowTime;
  double writeColTime;
  double readRowTime;
  double readColTime;
  struct timespec timeStart, timeEnd;
}MatrixData_T, *MatrixData_P;

/**	@brief 	Writes by Row Major to each place in the global matrix array. 
*	@param 	is a pointer to the matrix containing the value for storing the time calculations. 
*	@return no value. 
*/
void writeRow(MatrixData_P);

/**	@brief 	Writes by Column Major to each place in the global matrix array. 
*	@param 	is a pointer to the matrix containing the value for storing the time calculations. 
*	@return no value. 
*/
void writeColumn(MatrixData_P);

/**	@brief 	Reads by Row Major each value in the global matrix array. 
*	@param 	is a pointer to the matrix containing the value for storing the time calculations. 
*	@return returns the last char read from the global matrix array. 
*/
char readRow(MatrixData_P);

/**	@brief 	Reads by Column Major each value in the global matrix array. 
*	@param 	is a pointer to the matrix containing the value for storing the time calculations. 
*	@return returns the last char read from the global matrix array. 
*/
char readColumn(MatrixData_P);

/**	@brief 	calculates the time required to run each matrix function from the start to end.
*	@param 	is a pointer to the matrix containing the time structures for start and end.
*	@return the time calculation in nano-seconds.
*/
double calcTime(MatrixData_P);

/**	@brief 	Prints out the result for column and row major for both read and write to the matrix. 
*	@param 	is a pointer to the matrix containing the time calculations for the each simulation run. 
*	@return no value. 
*/
void printMatrixData(MatrixData_P);


/**	@brief 	runs the matrix row and column major simulation. 
*	@param 	argc the command line argument count.
* 			**argv is the command line argument vector. 
*	@return to the operating system. 
*/
int main(int argc, char **argv){
  MatrixData_T matrixData_t;
  MatrixData_P matrixData_p = &matrixData_t;
  writeRow(matrixData_p);
  writeColumn(matrixData_p);
  readRow(matrixData_p);
  readColumn(matrixData_p);
  printMatrixData(matrixData_p);
  return 0;
}


double calcTime(MatrixData_P matrixData_p){
  return (matrixData_p->timeEnd.tv_sec - matrixData_p->timeStart.tv_sec) + (matrixData_p->timeEnd.tv_nsec - matrixData_p->timeStart.tv_nsec) / BILLION;
}

void printMatrixData(MatrixData_P matrixData_p){
  printf("Write row time: %.9lf \n", matrixData_p->writeRowTime / COUNT);
  printf("Write column time: %.9lf \n", matrixData_p->writeColTime / COUNT);
  printf("Read row time: %.9lf \n", matrixData_p->readRowTime / COUNT);
  printf("Read column time: %.9lf \n", matrixData_p->readColTime / COUNT); 
}

void writeRow(MatrixData_P matrixData_p){ 
  int i = 0, j = 0, count = 0;
  for(count = 0; count < COUNT; count++){
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeStart));	//start timer
    for(i = 0; i < NUM_ROW; i++)
      for(j = 0; j < NUM_COL; j++)
		MATRIX[i][j] = 'A';
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeEnd));	//stop timer
    matrixData_p->writeRowTime += calcTime(matrixData_p);		//calculate time and collect data 
  }
}

void writeColumn(MatrixData_P matrixData_p){ 
  int i = 0, j = 0, count = 0;
  for(count = 0; count < COUNT; count++){
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeStart));	//start timer
    for(i = 0; i < NUM_COL; i++)
      for(j = 0; j < NUM_ROW; j++)
		MATRIX[j][i] = 'A';
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeEnd));	//stop timer
    matrixData_p->writeColTime += calcTime(matrixData_p);		//calculate time and collect data 
  }
}

char readRow(MatrixData_P matrixData_p){ 
  int i = 0, j = 0, count = 0;
  char readChar;
  for(count = 0; count < COUNT; count++){
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeStart));	//start timer
    for(i = 0; i < NUM_ROW; i++)
      for(j = 0; j < NUM_COL; j++)
		readChar = MATRIX[i][j];
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeEnd));	//stop timer
    matrixData_p->readRowTime += calcTime(matrixData_p);		//calculate time and collect data 
  }
  return readChar;
}

char readColumn(MatrixData_P matrixData_p){ 
  int i = 0, j = 0, count = 0;
  char readChar;
  for(count = 0; count < COUNT; count++){
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeStart));	//start timer
    for(i = 0; i < NUM_COL; i++)
      for(j = 0; j < NUM_ROW; j++)
		readChar = MATRIX[j][i];
    clock_gettime(CLOCK_REALTIME, &(matrixData_p->timeEnd));	//stop timer
    matrixData_p->readColTime += calcTime(matrixData_p);		//calculate time and collect data 
  }
  return readChar;
}

