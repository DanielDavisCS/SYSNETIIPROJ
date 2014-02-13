/**	@file 
 * 	@brief 
 * 	@author Cole Amick
 * 	@author Daniel Davis
 * 	@bug No known bugs!
 */
 
#include "TCPserver.h"

/**	@brief 	
*	@param 	
*	@return 
*/
int main(){

  int listensockfd;
  struct hostent *hostptr; 
  struct sockaddr_in servaddr;
 
  listensockfd = create_TCP_Socket();
  hostptr = info_Host();
  servaddr = destination_Address(hostptr);
  servaddr = bind_Socket(listensockfd, servaddr);
  servaddr = listen_On_Socket(listensockfd, servaddr);
  print_Server_info(listensockfd, hostptr, servaddr);
  run_Server(listensockfd, servaddr);

  return 0;
}
