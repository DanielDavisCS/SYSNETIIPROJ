/**	@file myshell.c
 * 	@brief runs a basic shell program for processing basic system commands. 
 * 	Calls the parser program to get the user input and then runs this program
 * 	to create child processes of the main shell to run system commands. Can run
 * 	both foreground and background processes. Program waits for all children processes
 * 	to finish that are running. 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug NO known bugs
 */
 
#include "parse.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/****************************/
#define TRUE 1

/* structure to hold the count of background process */
struct childProcesses {
	int childCount;
};
/* a typedef to the childProcesses structure */
typedef struct childProcesses * childProcesses_p;


/**	@brief	allocates memory for the childProcesses structure.
 *	Performs error checking for malloc. 
 * 	@return a pointer to the childProcesses structure. 
 */
childProcesses_p newChildProcesses(void);

/**	@brief	creates the child process and handles background and foreground processing. 
 * 	@param 	parser is a pointer to the parser structure from the parse program.
 *		children_p is a pointer to the count of how many background processes need to be waited on. 
 * 	@return void. 
 */
void runshell(Parser_p parser, childProcesses_p children_p);

/**	@brief runs the children process of the current input. It executes the 
 * 	command that user inputted. Handles file redirection and error on invalid command. 
 * 	@param parser is a pointer to the parser structure from the parse program.
 * 	@return void. 
 */
void runChildProcess(Parser_p parser);

/**	@brief	frees the structure that contains the number of running background processes. 
 * 	@param children_p is a pointer to the count of how many background processes need to be waited on. 
 * 	@return void. 
 */
void freeChildProcesses(childProcesses_p children_p);

/**	@brief	makes the shell wait until all background child processes have termianted 
 * 	before terminating the shell. 
 * 	@param children_p is a pointer to the count of how many background processes need to be waited on. 
 * 	@returni returns TRUE or 1 to terminate the program.
 */
int exitCommand(childProcesses_p children_p);


/**	@brief	is the main shell and uses the shell parser. 
 * 	runs basic linux shell commands. 
 * 	@param	argc is the command line argument count.
 * 		**argv is the command line argument vector. 
 * 	@return to the operating system. 
 */
int main(int argc, char ** argv){
	int done = 0;
	childProcesses_p children_p = newChildProcesses();
	while(!done){ 
		Parser_p parser =  shellParser();
		if(getExit(parser)) done = exitCommand(children_p);
		else if(!getError(parser)) runshell(parser, children_p);
		freeMemory(parser);
		free(parser);
	}
	freeChildProcesses(children_p);
	return 0;
}


/**********************************************/
childProcesses_p newChildProcesses(void) {
	childProcesses_p children_p = (childProcesses_p) malloc(sizeof(struct childProcesses));
	if(children_p == NULL) {
		fprintf(stderr, "Stack Allocation Failed\n");
		exit(1);
	}
	else children_p->childCount = 0;
	return children_p;
}

/**********************************************/
void freeChildProcesses(childProcesses_p children_p){
	free(children_p);
}

/**********************************************/
void runshell(Parser_p parser, childProcesses_p children_p) {
	int status;
	pid_t cpid = fork();
	//background process
	if(getBackground(parser) == 1) children_p->childCount++;	
	//child is executing 
	if(cpid == 0) runChildProcess(parser);
	//foreground process
	if(getBackground(parser) == 0) waitpid(cpid,&status,0);
}

/**********************************************/
void runChildProcess(Parser_p parser) {
	FILE *fp;
	if(getInputRedirect(parser) != NULL) {
		fp = freopen(getInputRedirect(parser), "r", stdin);
		if(fp == NULL) {
			fprintf(stderr, "-bash: %s: No such file or directory\n", getInputRedirect(parser));
			freopen("stdin", "r", stdin);
			return;
		}
	}
	if(getOutputRedirect(parser) != NULL)
		 freopen(getOutputRedirect(parser), "w+", stdout);
	//execute commands
	execvp(getArgumentVector(parser)[0], getArgumentVector(parser));
	//error with invalid command
	fprintf(stderr, "-bash: %s: command not found\n", getArgumentVector(parser)[0]);
	freopen("stdin", "r", stdin);
}

/**********************************************/
int exitCommand(childProcesses_p children_p) {
	int status, i = 0;
	for (i = 0; i < children_p->childCount; i++)
		 waitpid(-1,&status,0);
	return TRUE;
}


