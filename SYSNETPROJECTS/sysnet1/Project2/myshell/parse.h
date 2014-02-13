/**	@file parse.h
 * 	@brief "parse.h" is the header file attributed to "parse.c"
 *	Inside the "parse.h" header file is the declaration for the data structure 
 * 	used when parsing user input. The functions that are declared in "parse.h" are designed
 * 	to give the data structure complete functinality in the myshell.c program.   
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**	@brief The PARSE struct, and its related functions, are
 *	the interface for accessing data from user input stored in the PARAM struct.
 *	Additional data stored in the shellParser struct includes, a boolean variables for the exit command,
 * 	and a boolean variable indicating if an error has occured in user input.
 */
typedef struct PARSER *Parser_p;

/**	@brief initiates prompt for user input, and allocation of memory for data structures
 *	used in storing parsed user input. Additionaly checks for exit command, and if an error has occured.   
 * 	See the @additional notes section in the README.txt file for the correct format for user input         
 * 	@param void
 * 	@return Parser_P 
 */
Parser_p shellParser(void);

/**	@brief frees the memory allocated for the buffer and PARAM structure. 
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure.
 * 	@return void.
 */
void freeMemory(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 *	in this case the function is returning the inputRedirect data from the PARAM struct 
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the PARAM struct that stores the file name of input redirection	
 * 	@return returns a pointers to the input redirection char string
 */
char *getInputRedirect(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the PARAM struct that stores the file name of output redirection	
 * 	@return returns a pointers to the output redirection char string
 */
char *getOutputRedirect(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 * 	a program in the background  
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the PARAM struct that stores the boolean variable for background	
 * 	@return returns a int indicating if a process is to run in the background
 */
int getBackground(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the PARAM struct the contains the argument count	
 * 	@return returns a int indicating the number of arguments
 */
int getArgumentCount(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 *	the function is returning the argumentVector stored in a PARAM struct
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the PARAM struct that stores the argument vector	
 * 	@return returns a pointer to an array of strings
 */
char **getArgumentVector(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the boolean variable indicating if an error has occured in user input	
 * 	@return returns an int indicating if an error has occured
 */
int getError(Parser_p parser);

/**	@brief this function provides access to the data stored in the PARSER struct 
 * 	@param parser is a pointer to a PARSER struct
 *		parser contains the boolean variable indicating if an error has occured	
 * 	@return returns an int indicating if the exit command has been entered
 */
int getExit(Parser_p parser);


