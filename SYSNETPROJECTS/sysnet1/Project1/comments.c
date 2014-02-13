/**	@file parse.c
 * 	@brief
 *
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */


/**	@brief
 *
 * 	@param	*param is a pointer to the PARAM structure. 
 * 	@return void. 
 */
void printParams(Param_t *param);


/**	@brief
 *
 * 	@return returns a pointer to the PARAM structure.  
 */
Param_p newParam();


/**	@brief
 *
 * 	@return returns a pointer to a char array containing the input.
 */
char *getInput(void);


/**	@brief
 *
 * 	@param	*Data_name is the name of a pointer that data type does not matter. 
 * 	@return void.
 */
void errorCheckAllocation(void *Data_name);


/**	@brief
 *
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure. 
 * 	@return TRUE or 1 if it is a valid input.
 * 		False or 0 if it is a invalid input.
 */
int parse (char *buffer, Param_p param_p);


/**	@brief
 *
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure. 
 * 	@return a char array containing the next token from the input buffer. 
 */
char *tokening(char *buffer, Param_p param_p);


/**	@brief
 *
 * 	@return FALSE or 0 because a invalid input was entered.  
 */
int errorCheck(void);


/**	@brief
 *
 * 	@param	*buffer contains the input stored in the char array.
 * 		param_p is a pointer to the PARAM structure. 
 * 	@return void. 
 */
void freeMemory(char *buffer, Param_p param_p);


/**	@brief
 *
 * 	@param	*token is a char array containing the current token to check. 
 *		param_p is a pointer to the PARAM structure. 
 * 	@return TRUE or 1 if it is a valid file redirection entry in the input. 
 * 		FALSE or 0 if it is a invalid file redirection entry in the input. 
 */
int fileRedirection(char *token, Param_P param_p);


/**	@brief
 *
 * 	@param
 *
 * 	@return
 */
int main(int argc, char **argv)
