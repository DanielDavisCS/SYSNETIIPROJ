/*
 * TCPclient.c
 * Systems and Networks II
 * Project 1
 *
 * This file implements the functions for the TCPclient.
 * and implements many auxillary functions we deem necessary.
 */

 //includes
 #include "TCPclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 


//???????????includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>


/*
 * Creates a streaming socket and connects to a server.
 *
 * serverName - the ip address or hostname of the server given as a string
 * port       - the port number of the server
 * dest       - the server's address information; the structure should be created with information
 *              on the server (like port, address, and family) in this function call
 *
 * return value - the socket identifier or a negative number indicating the error if a connection could not be established
 */
int createSocket(char * serverName, int port, struct sockaddr_in ** dest){
  int sockfd;
  struct hostent *hostptr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //creates tcp socket
  hostptr = gethostbyname(serverName); // getting information from host 
  return sockfd;
}

/*
 * Sends a request for service to the server. This is an asynchronous call to the server, 
 * so do not wait for a reply in this function.
 * 
 * sock    - the socket identifier
 * request - the request to be sent encoded as a string
 * dest    - the server's address information
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int sendRequest(int sock, char * request, struct sockaddr_in * dest){

}

/*
 * Receives the server's response formatted as an XML text string.
 *
 * sock     - the socket identifier
 * response - the server's response as an XML formatted string to be filled in by this function
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int receiveResponse(int sock, char ** response){
}

/*
 * Prints the response to the screen in a formatted way.
 *
 * response - the server's response as an XML formatted string
 *
 */
void printResponse(char* response){

}

/*
 * Closes the specified socket
 *
 * sock - the ID of the socket to be closed
 * 
 * return - 0, if no error; otherwise, a negative number indicating the error
 */
int closeSocket(int sock){


]
