/**	@file 
 * 	@brief 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include "TCPserver.h"

/*
 **************************************************
 **************************************************
 */
void printErrorMessage( char *message ) {
	fprintf(stderr, "ERROR: %s\n", message);
	exit(1);
}


/*
 **************************************************
 **************************************************
 */
int create_TCP_Socket(void)
{
  int listensockfd = socket(AF_INET, SOCK_STREAM,0);
  if(listensockfd == -1) 
	printErrorMessage("Cannot Open Socket to Listen");
  return listensockfd;
}


/*
 **************************************************
 **************************************************
 */
struct hostent *info_Host() {
  char hostname[128];
  struct hostent *hostptr; 
  if(gethostname(hostname, 128) == -1) 
	printErrorMessage("Cannot Get The Host Name");
  hostptr = gethostbyname(hostname);
  if(hostptr == NULL) 
	printErrorMessage("That Host Does Not Exist");
  return hostptr;
}


/*
 **************************************************
 **************************************************
 */
struct sockaddr_in destination_Address( struct hostent *hostptr) {
  struct sockaddr_in servaddr;
  memset((void *) &servaddr, 0, (size_t) sizeof(servaddr));
  memcpy((void *) &servaddr.sin_addr, (void *) hostptr->h_addr, hostptr->h_length);
  servaddr.sin_family = (AF_INET);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons((u_short) 0);
  return servaddr;
}


/*
 **************************************************
 **************************************************
 */
struct sockaddr_in bind_Socket(int listensockfd, struct sockaddr_in servaddr){
  if(bind(listensockfd, (struct sockaddr *) &servaddr, (socklen_t) sizeof(servaddr)) == -1)
	printErrorMessage("Failed to Bind To Socket");  
  return servaddr;
}



/*
 **************************************************
 **************************************************
 */
struct sockaddr_in listen_On_Socket(int listensockfd, struct sockaddr_in servaddr){
  int servaddrlen = sizeof(struct sockaddr_in);
  if(getsockname(listensockfd, (struct sockaddr *) &servaddr, (socklen_t *) &servaddrlen) == -1)
	printErrorMessage("Cannot Listen To This Port");
  listen(listensockfd, MAX_NUM_LISTENER_ALLOWED);
  return servaddr;
}


/*
 **************************************************
 **************************************************
 */
void print_Server_info(int listensockfd, struct hostent *hostptr, struct sockaddr_in servaddr){
  //printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)  hostptr->h_addr )));
  //printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *) &servaddr.sin_addr)));

  struct ifreq ifr;
  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, INTERFACE, IFNAMSIZ-1);
  ioctl(listensockfd, SIOCGIFADDR, &ifr);

  printf("\n");
  printf("Hostname Name : %s\n", hostptr->h_name);
  printf("Host IP Address : %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  printf("Host Port Number : %i\n", htons(servaddr.sin_port));
  printf("\n");
}




//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//		FOLLOWING STOLEN FROM THE INTERNET 
//		FOLLOWING STOLEN FROM THE INTERNET 

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------



/*
 **************************************************
 **************************************************
 */
void run_Server(int listensockfd, struct sockaddr_in servaddr){


 printf("Waiting for Clients ......\n");
 
  int n;
  struct sockaddr_in cliaddr;
  char mesg[1000];
  pid_t childpid;
  socklen_t clilen = sizeof(cliaddr);
 for(;;)
   {
      clilen=sizeof(cliaddr);
      int connfd = accept(listensockfd,(struct sockaddr *)&cliaddr,&clilen);

      if ((childpid = fork()) == 0)
      {
         close (listensockfd);

         while(1)
         {
            n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
            sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));


	    //Do something with the message here
	    


            printf("-------------------------------------------------------\n");
            mesg[n] = 0;
            printf("Received the following:\n");
            printf("%s",mesg);
            printf("-------------------------------------------------------\n");
         }
         
      }
      close(connfd);
   }


}












