/**	@file 
 * 	@brief 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//		FOLLOWING STOLEN FROM THE INTERNET 
//		FOLLOWING STOLEN FROM THE INTERNET 

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "TCPserver.h"


#include "TCPclient.h" 


int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];

   if (argc != 3)
   {
      printf("usage:  client <IP address> <port>\n");
      exit(1);
   }

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   struct hostent *hostptr; 
   hostptr = gethostbyname(argv[1]);
   servaddr.sin_addr.s_addr=inet_addr(inet_ntoa(*((struct in_addr *) hostptr->h_addr)));
   //servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(atoi(argv[2]));




 //-----------------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------------
  char str[128];
  inet_ntop(AF_INET, &(servaddr.sin_addr), str, INET_ADDRSTRLEN);
  printf("\n");
  printf("Host IP Address : %s\n", str);
  printf("\n");
 //-----------------------------------------------------------------------------------------



   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
printf("Enter Messsage: ");
   while (fgets(sendline, 10000,stdin) != NULL)
   {
	printf("Sending Message %s\n", sendline);

	//remove new line
	sendline[strlen(sendline) - 1] = '\0';

      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      printf("Message from Server ");
      fputs(recvline,stdout);
	printf("\n");
printf("Enter Messsage: ");
   }
}
