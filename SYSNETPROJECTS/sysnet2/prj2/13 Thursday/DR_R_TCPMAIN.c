#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "UDPclient.h"

/**
 * Runs a test by sending a message to the server and comparing the result to the expected result.
 *
 * hostname  - the ip address or hostname of the server given as a string
 * portNum   - the port number of the server
 * req       - the message for the server
 * expctResp - the expected response from the server or null if any response is accepted
 * 
 * returns a positive value if the expected value matches the return value and zero otherwise
 */
int runTest(char *hostname, int portNum, char *req, char *expctResp)
{
	int                sockfd;
	struct sockaddr_in servaddr;
	char               response[256];
	
	// create a streaming socket
	sockfd = createSocket(hostname, portNum, &servaddr);
	if (sockfd < 0) {
		return 0;
	}
	
	// send request to server
	if (sendRequest (sockfd, req, &servaddr) < 0) {
		close (sockfd);
		return 0;
	}

	if (receiveResponse(sockfd, response) < 0) {
		close (sockfd);
		return 0;
	}
	close (sockfd);
	
	// display response from server
	printResponse(response);
	
	if (expctResp == NULL)
		return 1; // accept any response
		
	if (strcmp(response, expctResp) == 0)
		return 1;

	return 0;
}

/*
 * A test program to start a client and connect it to a specified server.
 * Usage: client <hostname> <portnum>
 *    client is this client program
 *    <hostname> IP address or name of a host that runs the server
 *    <portnum> the numeric port number on which the server listens
 */
int main(int argc, char** argv) 
{
	if (argc != 3) {
		fprintf (stderr, "Usage: client <hostname> <portnum>\n");
		exit (1);
	}
	
	// parse input parameters for host and port information
	char *hostname = argv[1];
	int portNum = atoi (argv[2]);

	// run tests
	if (!runTest (hostname, portNum, "<loadavg/>", NULL))
		printf ("Failed test 1.\n");
	else
		printf ("Passed test 1.\n\n");
	
	if (!runTest (hostname, portNum, "<echo>Hello World!</echo>", "<reply>Hello World!</reply>"))
		printf ("Failed test 2.\n");
	else
		printf ("Passed test 2.\n\n");
	
	if (!runTest (hostname, portNum, "<echo></echo>", "<reply></reply>")) 
		printf ("Failed test 3.\n");
	else
		printf ("Passed test 3.\n\n");
	
	if (!runTest (hostname, portNum, "<echo>Bye Bye World...<echo>", "<error>unknown format</error>"))
		printf ("Failed test 4.\n");
	else
		printf ("Passed test 4.\n\n");
	
	if (!runTest (hostname, portNum, "", "<error>unknown format</error>"))
		printf ("Failed test 5.\n");
	else
		printf ("Passed test 5.\n");
		
		
	/*
	*	Additional Test
	*/
	
	if (!runTest (hostname, portNum, "<echo></echo> ", "<error>unknown format</error>"))
		printf ("Failed test 6.\n");
	else
		printf ("Passed test 6.\n");
	
	if (!runTest (hostname, portNum, "\n", "<error>unknown format</error>"))
		printf ("Failed test 7.\n");
	else
		printf ("Passed test 7.\n");
		
	if (!runTest (hostname, portNum, "<shutdown/>", ""))
		printf ("Failed test 8 - Shutdown.\n");
	else
		printf ("Passed test 8 - Shutdown.\n");
	
	if (!runTest (hostname, portNum, "<shutdown/>", ""))
		printf ("Failed test 9 - Time Out.\n");
	else
		printf ("Passed test 9 - Time Out.\n");
	
	
	exit(0);
}

