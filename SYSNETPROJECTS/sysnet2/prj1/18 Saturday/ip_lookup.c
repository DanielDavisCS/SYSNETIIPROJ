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
  char hostname[255];
  struct hostent *hostptr; 
//-----------------------------------------------------------------------------------------
/*
 * Create Socket and get Host Name 
 */
  listensockfd = socket(AF_INET, SOCK_STREAM,0);
  gethostname(hostname, 255);
  hostptr = gethostbyname(hostname);  
//-----------------------------------------------------------------------------------------
 /*
 * Print INCORRECT IP
 */
  printf("Hostname %s\n", hostptr->h_name); 
  printf("JUNK IP =  %s\n", inet_ntoa(*((struct in_addr *) * hostptr->h_addr_list )));
  printf("JUNK IP =  %s\n\n\n", inet_ntoa(*((struct in_addr *) hostptr->h_addr)));
//-----------------------------------------------------------------------------------------
/*
 *Find Correct IP Address 
 */
 struct ifreq ifr;
 ifr.ifr_addr.sa_family = AF_INET;
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
 ioctl(listensockfd, SIOCGIFADDR, &ifr);
 printf(" AUTOMAGIC = %s\n\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
//-----------------------------------------------------------------------------------------
/*
 * Overwrite the host pointer
 */ 
 *((struct in_addr*)  hostptr->h_addr) = (((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr);
//-----------------------------------------------------------------------------------------
/*
 * Print CORRECT IP
 */
  printf("Hostname %s\n", hostptr->h_name); 
  printf("New IP =  %s\n", inet_ntoa(*((struct in_addr *) * hostptr->h_addr_list )));
  printf("New IP =  %s\n\n\n", inet_ntoa(*((struct in_addr *) hostptr->h_addr)));
//-----------------------------------------------------------------------------------------
  return 0;  
}
