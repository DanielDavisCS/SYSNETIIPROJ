/**
 *  parse.c
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>

/* Don't test program with more than this many tokens for input  */
#define MAXARGS 32

/* Structure to hold input data                                  */
struct PARAM
{
  char *inputRedirect;           /* file name or NULL            */
  char *outputRedirect;          /* file name or NULL            */
  int   background;              /* either 0 (false) or 1 (true) */
  int   argumentCount;           /* same as argc in main()       */
  char *argumentVector[MAXARGS]; /* array of strings             */
};

/* A typedef so we don't need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;

/* declare a buffer for the input                                */
#define BUFFSIZE 4096
char buffer[BUFFSIZE];

/**
 * This function prompts for input using the specified text for the prompt itself and then parses the input
 * into the specified structure.
 *
 * @param promp the text string to be used as prompt
 * @param param the parameter that will hold the parsed information.
 *
 * @return 0, if exit was entered; a negative value for invalid entries, 
 *            a positive value for a correct parse.
 */
int promptAndParse( const char * prompt, Param_t * param );

/**
 * Parses the specified text string into the parameter structure.
 *
 * @param buffer the text string to be parsed
 * @param param  the parameter structure
 *
 */
int parseTokens ( char * buffer, Param_t * param );

/**
 * Determines if an input error has occurred based on the specified token and the existing parse result.
 *
 * @param token the next tokne
 * @param param the parameter structure
 * 
 * @return a negative value if an error has occurred
 */
int handleErrorCases(char * token, Param_t * param);

/**
 * Handles the case of the specified token being an input redirect.
 *
 * @param token the token that specifies an input redirect
 * @param param the parameter structure
 *
 * @return a positive value if no error has occured or a negative number if an error has occurred
 */
int handleInputRedirect(char * token, Param_t * param);


/**
 * Handles the case of the specified token being an output redirect.
 *
 * @param token the token that specifies an output redirect
 * @param param the parameter structure
 *
 * @return a positive value if no error has occured or a negative number if an error has occurred
 */
int handleOutputRedirect(char * token, Param_t * param);

/**
 * Handles the case of the specified token being a background indicator.
 *
 * @param param the parameter structure
 *
 * @return a positive value if no error has occurred or a negative number if an error has occurred
 */
int handleBackground(Param_t * param);

/**
 * Initializes the parameter structure with default values.
 *
 * @param param the parameter structure
 */
void initParams( Param_t * param );

/**
 * This function prints the information in the specified structure to standard out.
 *
 * @param param the parameter structure
 */
void printParams( Param_t * param );


int main(int argc, char ** argv)
{
  Param_t p;
  int     status;

  printf("*****************************************************************\n");
  printf("** This program demonstrates several things that have been     **\n");
  printf("** asked. This program will continue to prompt until exit is   **\n");
  printf("** entered at the start of the prompt.                         **\n");
  printf("*****************************************************************\n\n");
  
  while ((status = promptAndParse( ">>> ", &p ))) {
    if (status < 0)
	printf ("Error in input. Unable to parse structure.\n");
    else 
	printParams( &p );
  }
    
  return 0;
}


int promptAndParse(const char * prompt, Param_t * param)
{
  int status; // flag indicated that some token was extracted
  
  /* don't declare the buffer locally - it will vanish */
  /* when the function returns                         */
  
  /* initialize the param structure */
  initParams ( param );
 
  /* display the prompt */
  printf( prompt );
  
  /* get user input */
  fgets( buffer, BUFFSIZE, stdin );
  
  /* parse the input */
  status = parseTokens ( buffer, param );
  
  return status;
}

int parseTokens (char * buffer, Param_t * param)
{
  char * token;
  int    statusParse = 0;

  token = strtok( buffer, " \t\n" );

  /* special case of first token being exit */
  if (strcasecmp(token, "exit") == 0)
	return statusParse;	

  while (token != NULL )
  {
    if ((statusParse = handleErrorCases(token, param)) < 0)
	return statusParse;
    
    /* check the first character of the token */
    switch (*token)
    {
      case '<': 
        statusParse = handleInputRedirect (token, param);
        break;
      case '>':
        statusParse = handleOutputRedirect (token, param);
        break;
      case '&':
        statusParse = handleBackground (param); 
        break;
      default:
        param->argumentVector[param->argumentCount] = token;
        param->argumentCount++;
    }

    // interrupt parse because an error has occurred
    if (statusParse < 0)
	return statusParse;

    token = strtok( NULL, " \t\n" );
  }
  
  /* be sure the last entry is NULL */
  param->argumentVector[param->argumentCount] = NULL;
  
  return statusParse;
}

int handleErrorCases(char * token, Param_t * param)
{
  if (param->background == 1)
	return -1; // background symbol not the last symbol;

  return 1;
}

int handleInputRedirect(char * token, Param_t * param)
{
  if (strlen(token) <= 1) 
	return -1; // empty token

  if (param->argumentCount == 0)
	return -1; // first token

  if (param->inputRedirect != NULL)
	return -1; // more thna one input redirect

  param->inputRedirect = token+1;

  return 1;	
}

int handleOutputRedirect(char * token, Param_t * param)
{
  if (strlen(token) <= 1)
	return -1; // empty token

  if (param->argumentCount == 0)
	return -1; // first token

  if (param->outputRedirect != NULL)
	return -1; // more than one output redirect

  param->outputRedirect = token+1;

  return 1;
}

int handleBackground(Param_t * param)
{
  if (param->background != 0)
  	return -1; // background already seen

  param->background = 1;

  return 1;
}
	
void initParams (Param_t * param)
{
  /* initialize the param structure */
  param->inputRedirect = NULL;
  param->outputRedirect = NULL;
  param->background = 0;
  param->argumentCount = 0;
}

void printParams(Param_t * param) 
{ 
  int i; 
  printf("InputRedirect: [%s]\n", 
         (param->inputRedirect != NULL)?param->inputRedirect:"NULL"); 
  printf("OutputRedirect: [%s]\n", 
         (param->outputRedirect != NULL)?param->outputRedirect:"NULL"); 
  printf("Background: [%d]\n", param->background); 
  printf("ArgumentCount: [%d]\n", param->argumentCount); 
  for(i = 0; i < param->argumentCount; i++) 
    printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]); 
} 
