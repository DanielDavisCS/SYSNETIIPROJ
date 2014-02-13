/**	@file parse.c
 * 	@brief Parser for shell. 
 * 	Takes input from user and stores into buffer.
 *	Then parses the buffer and initalizes the required parameters in data structure.
 *	Before each iteration of user input the input buffer and data structure is freed.  
 * 	and the process continues until exit. 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */

#include "parse.h"
/**************************** */
#define MAXARGS 32
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
/* a pointer to the param_t structure */
typedef Param_t * Param_p;

/* structure to hold parser data */
struct PARSER
{
	Param_p param; /* pointer to the PARAM structure */
	char *input; /* pointer to the input buffer */
	int exit; /* boolean for exiting program */
	int error; /* boolean for error in user input */
};


/**	@brief prints the results in a predefined format. 
 *
 * 	@param	*param is a pointer to the PARAM structure.
 * 	@return void.
 */
void printParams(Param_t *param);


/**	@brief allocates memory for the PARAM structure. 
 *	Initalizes non-vector parameters. 
 * 	@return returns a pointer to the PARAM structure.
 */
Param_p newParam();


/**	@brief allocates memory for the PARSER structure. 
 *	Initalizes exit and error parameters. 
 * 	@return returns a pointer to the PARSER structure.
 */
Parser_p newParser(void);


/**	@brief allocates memory for the input buffer. 
 *	Display a user prompt and accepts user input. 
 * 	@return returns a pointer to a char array containing the input.
 */
char *getInput(void);


/**	@brief checks to make sure malloc allocated memory for structure. 
 * 	@param	*Data_name is the name of a pointer that data type does not matter.
 * 	@return void.
 */
void errorCheckAllocation(void *Data_name);


/**	@brief we tokenizer the input buffer into tokens based on "space", "tab" or "new line". 
 * 	It continues tokenizing and storing the results in the PARAM structure until 
 * 	the end of the input buffer. 
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure.
 * 	@return TRUE or 1 if it is a valid input.
 * 		False or 0 if it is a invalid input.
 */
int parse (char *buffer, Param_p param_p);


/**	@brief uses strtok to tokenize on "space", "tab", or "new line". 
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure.
 * 	@return a char array containing the next token from the input buffer.
 */
char *tokening(char *buffer, Param_p param_p);


/**	@brief Prints error message due to invalid input. 
 * 	@return FALSE or 0 because a invalid input was entered.
 */
int errorCheck(void);


/**	@brief	perform action based on the contexts of its call, i.e. if it was called because of a
 * 	input rederection or a output rederection. 
 * 	@param	*token is a char array containing the current token to check.
 *		param_p is a pointer to the PARAM structure.
 * 	@return TRUE or 1 if it is a valid file redirection entry in the input.
 * 		FALSE or 0 if it is a invalid file redirection entry in the input.
 */
int fileRedirection(char *token, Param_p param_p);


 /*********************************************/
Parser_p shellParser(void){
	Parser_p parser = newParser();
	parser->param = newParam();
	parser->input = getInput();
	if(!strcmp(parser->input, "exit\n")) parser->exit = 1;
	else if(parse(parser->input, parser->param)) parser->error = 0;
	else parser->error = 1;
	return parser;
}

 /*********************************************/
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

 /*********************************************/
Param_p newParam(){
	Param_p param_p = (Param_p) malloc(sizeof(Param_t));
	if(param_p == NULL) errorCheckAllocation(param_p);
	else{
		param_p->background = param_p->argumentCount = 0;
		param_p->inputRedirect = param_p->outputRedirect = 0x00;
		int i = 0;
		for(i = 0; i < MAXARGS; i++) param_p->argumentVector[i] = 0x00;
	}
	return param_p;
}

/*********************************************/
Parser_p newParser(void){
	Parser_p parser = (Parser_p) malloc(sizeof(struct PARSER));
	if(parser == NULL) errorCheckAllocation(parser);
	else parser->exit = parser->error = 0;
	return parser;
}

 /*********************************************/
void errorCheckAllocation(void *Data_name){
	if(Data_name == NULL) {
		fprintf(stderr, "Stack allocation FAIL!\n");
		exit(1);
	}
}
 /*********************************************/
int errorCheck(void){
	printf("\n\nInvalid Input! - - TRY Again!!\n\n");
	return FALSE;
}


 /*********************************************/
char *getInput(void){
	char *buffer = malloc (MAXARGS * MAXLENGTH  *sizeof(char));
	if(buffer == NULL) errorCheckAllocation(buffer);
	printf("$$$ ");
	return fgets(buffer, (MAXARGS*MAXLENGTH*sizeof(char)), stdin);	
}

 /*********************************************/
int  parse(char *buffer, Param_p param_p) {
	char *token = tokening(buffer, param_p);
	//continue tokenizing until end of buffer
	while(token != NULL) {
		if(!strcmp(token, "&")) {
			if(param_p->argumentCount == 0) return errorCheck();
			else param_p->background = 1;
		}
		else if(token[0] == '<' || token[0] == '>') { 
			if(!fileRedirection(token, param_p)) return FALSE;
		} 
		else if(param_p->argumentCount >= MAXARGS) return errorCheck();
		else param_p->argumentVector[param_p->argumentCount++] = token;
		token = tokening(buffer,param_p);
		if(param_p->background == 1 && token != NULL) return errorCheck();
	}
	return TRUE;
}

 /*********************************************/
int fileRedirection( char *token, Param_p param_p){
	if(param_p->argumentCount == 0) return errorCheck();
	if(token[0] == '<') {
		//check for existing input file
		//if true return error check
		if(param_p->inputRedirect != 0x00) return errorCheck();		
		//check for for bad characters
		if(token[1] == 0x00){
			return errorCheck();
		}
		param_p->inputRedirect = ++token;	
	}
	else {
		//check for existing output file
		//if true return error check
		if(param_p->outputRedirect != 0x00) return errorCheck();
		if(token[1] == 0x00){
			return errorCheck();
		}
		param_p->outputRedirect = ++token;	
	}
	return TRUE;
}

 /*********************************************/
char *tokening(char *buffer, Param_p param_p) {
	if(param_p->argumentCount == 0) return strtok(buffer, " \t\n");
	else return strtok(NULL, " \t\n");
}

 /*********************************************/
void freeMemory(Parser_p parser){
	free(parser->input);
	free(parser->param);
}

 /*********************************************/
char *getInputRedirect(Parser_p parser) {
	return parser->param->inputRedirect;
}

/*********************************************/
char *getOutputRedirect(Parser_p parser) {
	return parser->param->outputRedirect;
}

/*********************************************/
int getBackground(Parser_p parser) {
	return parser->param->background;
}

/*********************************************/
int getArgumentCount(Parser_p parser) {
	return parser->param->argumentCount;
}

/*********************************************/
char **getArgumentVector(Parser_p parser) {
	return parser->param->argumentVector;
}

/*********************************************/
int getError(Parser_p parser) {
	return parser->error;
}

/*********************************************/
int getExit(Parser_p parser) {
	return parser->exit;
}
