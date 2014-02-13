/**@file parse.c
 * @brief A console driver
 *	Asks the user for input stream and tokenizes the input using whitespace as the delimeter
 *
***************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* *************************** */
#define MAXARGS 3
#define MAXLENGTH 100
#define FALSE 0
#define TRUE 1
/* structure to hold input data */
struct PARAM
{
	char *inputRedirect; /* file name or NULL */
	char *outputRedirect; /* file name or NULL */
	int background; /* either 0 (false) or 1 (true) */
	int argumentCount; /* same as argc in main() */
	char *argumentVector[MAXARGS]; /* array of strings */
};
/* a typedef so we don’t need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;
/*****************/
typedef Param_t * Param_p;

/*************************/
void printParams(Param_t * param);
/************************************
 *Allocates memory for a new PARAM struct
 * **********************************/
Param_p newParam();
/*************************/
char *getInput(void);
/*************************/
void errorCheckAllocation(void *Data_name);
/*************************/
int  parse(char *buffer, Param_p param_p);
/*************************/
char * tokening(char *buffer, Param_p param_p);
/******************************/
int errorCheck(void);
/******************************/
void freeMemory(char *buffer, Param_p param_p);
/******************************/
int fileRedirection( char *token, Param_p param_p);

int main(int argc, char **argv){
	int done = 0;
	while(!done){
		Param_p param = newParam();
		char *input = getInput();
		if(!strcmp(input, "exit\n")) exit(0);
		else if(!strcmp(input, "clear\n")) system("clear");
		else if(parse(input, param)) printParams(param);
		freeMemory(input, param);
		}
	return 0;
}

/***********************************************
 *
 *
 * ********************************************/
void printParams(Param_t * param){
	int i;
	printf ("InputRedirect: [%s]\n",
		(param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	printf ("OutputRedirect: [%s]\n",
		(param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	printf ("Background: [%d]\n", param->background);
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
}

/************************************
 *Allocates memory for a new PARAM struct
 * **********************************/
Param_p newParam(){
	Param_p param_p = (Param_p) malloc(sizeof(Param_t));
	if(param_p == NULL) errorCheckAllocation(param_p);
	else{
		param_p->background = param_p->argumentCount = 0;
		param_p->inputRedirect = (char *) malloc(MAXLENGTH* sizeof(char));
		if(param_p->inputRedirect == NULL) errorCheckAllocation(param_p->inputRedirect);
		else param_p->inputRedirect = 0x00;
		param_p->outputRedirect = (char *) malloc(MAXLENGTH * sizeof(char));
		if(param_p->outputRedirect == NULL) errorCheckAllocation(param_p->outputRedirect);
		else param_p->outputRedirect = 0x00;
	}
	return param_p;
}
/*****************************************


*****************************************/
void errorCheckAllocation(void *Data_name){
	if(Data_name == NULL) {
		fprintf(stderr, "Stack allocation FAIL!\n");
		exit(1);
	}
}
int errorCheck(void){
	printf("\n\nInvalid Input! - - TRY Again!!\n\n");
	return FALSE;
}


/*************************

*************************/
char *getInput(void){
	char *buffer = malloc (MAXARGS * MAXLENGTH  *sizeof(char));
	if(buffer == NULL) errorCheckAllocation(buffer);
	printf("$$$ ");
	fgets(buffer, (MAXARGS*MAXLENGTH*sizeof(char)), stdin);	
	return buffer;

}
/******************************************************
 *
 *
 * ****************************************************/
int  parse(char *buffer, Param_p param_p) {
	char *token = strtok(buffer,"\n");
	token = tokening(buffer, param_p);
	while(token != NULL) {
		if(param_p->argumentCount >=  MAXARGS) return errorCheck();
		else if(!strcmp(token, "&")) param_p->background = 1;
		else if(token[0] == '<' || token[0] == '>') { 
			if(!fileRedirection(token, param_p)) return FALSE;
		} 
		else param_p->argumentVector[param_p->argumentCount++] = token;
		token = tokening(buffer,param_p);
		if(param_p->background == 1 && token != NULL) return errorCheck();

	}
	return TRUE;
}

/*************************************************


*************************************************/
int fileRedirection( char *token, Param_p param_p){
	if(token[0] == '<') {
		//check for existing input file
		//if true return error check
		if(param_p->inputRedirect != 0x00) return errorCheck();		
		//check for for bad characters
		if(token[1] == '&' || token[1] == '<' || token[1] == '>' || token[1] == 0x00){
			return errorCheck();
		}
		param_p->inputRedirect = ++token;	
	}
	else {
		//check for existing output file
		//if true return error check
		if(param_p->outputRedirect != 0x00) return errorCheck();
		if(token[1] == '&' || token[1] == '<' || token[1] == '>' || token[1] == 0x00){
			return errorCheck();
		}
		param_p->outputRedirect = ++token;	
	}
	return TRUE;
}
/***********************************************

***********************************************/
char *tokening(char *buffer, Param_p param_p) {
	if(param_p->argumentCount == 0) return strtok(buffer, " ");
	else return strtok(NULL, " ");
}
/*********************************************


*********************************************/
void freeMemory(char *buffer, Param_p param_p){
	free(buffer);
//	free(param_p->inputRedirect);
//	free(param_p->outputRedirect);
	free(param_p);
}


