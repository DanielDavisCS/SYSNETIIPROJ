/**	@file
 * 	@brief
 *
 *
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include "UDPserver.h"

/**	@brief 	The main program for running the TCP server.
*	@param 	no parameters. 
*	@return returns 0 to the OS when main completes. 
*/
int main(int argc, char **argv){

  int sockfd;
  struct hostent *hostptr; 
  struct sockaddr_in servaddr;

  if(argc == 2){
    sockfd = create_UDP_Socket();  //create the TCP socket
    hostptr = info_Host(); //get the server host
    servaddr = destination_Address(hostptr, atoi(argv[1])); //argv[1] = server port number 
    servaddr = bind_Socket(sockfd, servaddr); //bind the socket
    print_Server_info(sockfd, hostptr, servaddr); //print the server info
  }
  


  return 0;
}

