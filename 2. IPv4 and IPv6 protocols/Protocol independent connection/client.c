
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc, char *argv[]){

 // Determines which type of protocol user uses

 if(argc < 2 || argc > 4){
    printf("%s\n", "error: invalid arguments\nType client --help to get more information.");
    exit(EXIT_FAILURE);
  }

  if(argc == 2 && !strcmp(argv[1], "--help")){
    printf("%s\n", "To run this program type: client <address IPv6 or IPv4> <port>");
    exit(0);
  }



  struct addrinfo hints, *result = NULL;

  memset(&hints, '\0', sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_NUMERICHOST;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;


  if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
    perror("Address info error");
    exit(EXIT_FAILURE);
  };


  // App supports only IPv4 and IPv6
  if(result->ai_family != 2 && result->ai_family != 10){
    perror("Unsupported protocol");
    exit(EXIT_FAILURE);
  }



  int sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if(sfd == -1){
    perror("Socket error");
    exit(EXIT_FAILURE);
  }

  if(connect(sfd, result->ai_addr, result->ai_addrlen) == -1){
    perror("Connection error");
    exit(EXIT_FAILURE);
  };


  char buffer[256];

  recv(sfd, buffer, 256, 0);
  printf("%s\n", buffer );

  close(sfd);
  freeaddrinfo(result);



}
