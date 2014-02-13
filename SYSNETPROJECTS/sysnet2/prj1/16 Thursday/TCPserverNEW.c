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


int main(){

  int listensockfd;
  //char *hostname = "cs-ssh1.cs.uwf.edu"; 
  //char hostname[32] = "cs-ssh3.cs.uwf.edu";
   char hostname[32];
   // strcpy(hostname, "cs-ssh3.cs.uwf.edu");
  printf("%s\n", hostname);

  struct hostent *hostptr; 
  struct sockaddr_in servaddr; //socket address structure

 
  listensockfd = socket(AF_INET, SOCK_STREAM,0);
  printf("11 - %s\n", hostname);
   gethostname(hostname, 32);
 printf("12 - %s\n", hostname);
  hostptr = gethostbyname(hostname);
  


//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
/*
 *Find Correct IP Address 
 */
 struct ifreq ifr;
 ifr.ifr_addr.sa_family = AF_INET;
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
 ioctl(listensockfd, SIOCGIFADDR, &ifr);
 printf("\n\n AUTOMAGIC = %s\n\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
//-----------------------------------------------------------------------------------------
/*
 * Overwrite the host pointer
 */ 
 *((struct in_addr*)  hostptr->h_addr) = (((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr);

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------




  //fill in destination address structure
  memset((void *) &servaddr, 0, (size_t)sizeof(servaddr));
  
  servaddr.sin_family = (short)(AF_INET);
  
  memcpy((void *)& servaddr.sin_addr, (void *) hostptr->h_addr, hostptr->h_length);
  
  servaddr.sin_port = htons((u_short)8000);
  

  printf("Hostname %s\n", hostptr->h_name);
  printf("and the host address isissss %s\n", inet_ntoa(*((struct in_addr *)  hostptr->h_addr )));


  return 0;  
}
