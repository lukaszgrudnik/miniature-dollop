/* Client uses IPv6 protocol */


#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void error(int ero){
  perror(strerror(ero));
  exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {

  // Arguments checking:

  if(argc < 2 || argc > 3){
    printf("%s\n", "error: invalid arguments\nType client --help to get more information.");
    exit(EXIT_FAILURE);
  }

  if(argc == 2 && !strcmp(argv[1], "--help")){
    printf("%s\n", "To run this program type: client <address> <port>");
    exit(0);
  }


  // Client implementation:

  int sfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sfd == -1)
    error(errno);

  struct sockaddr_in address;
  socklen_t addrlen;


  memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_port = htons(atoi(argv[2]));
  inet_pton(AF_INET, argv[1], &(address.sin_addr));

  addrlen = sizeof(address);

  if(connect(sfd, (struct sockaddr*) &address, addrlen) == -1)
    error(errno);

  printf("%s\n", "Connected to the server");

  // Receives message from server:

  char buffer[256];

  int rrv = recv(sfd, buffer, 256, 0);
  printf("%s\n", buffer );

  // Close connection

  close(sfd);




}
