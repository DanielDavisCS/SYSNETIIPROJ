/**	@file 
 * 	@brief 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include <stdio.h>
#include <unistd.h>
#include <netdb.h> //for gethostbyname
#include <sys/socket.h>
#include <string.h> //for memset
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX_NUM_LISTENER_ALLOWED 1024
#define INTERFACE "eth0"
#define MAX_MESSAGE 256
#define IP_4 32

/**	@brief 	
*	@param 	
*	@return 
*/
int create_TCP_Socket(void);

/**	@brief 	
*	@param 	
*	@return 
*/
struct hostent *info_Host();

/**	@brief 	
*	@param 	
*	@return 
*/
void printErrorMessage( char *message );

/**	@brief 	
*	@param 	
*	@return 
*/
struct sockaddr_in destination_Address( struct hostent *hostptr);

/**	@brief 	
*	@param 	
*	@return 
*/
struct sockaddr_in bind_Socket(int listensockfd, struct sockaddr_in servaddr);

/**	@brief 	
*	@param 	
*	@return 
*/
struct sockaddr_in listen_On_Socket(int listensockfd, struct sockaddr_in servaddr);

/**	@brief 	
*	@param 	
*	@return 
*/
void print_Server_info(int listensockfd, struct hostent *hostptr, struct sockaddr_in servaddr);

/**	@brief 	
*	@param 	
*	@return 
*/
void run_Server(int listensockfd, struct sockaddr_in servaddr);




