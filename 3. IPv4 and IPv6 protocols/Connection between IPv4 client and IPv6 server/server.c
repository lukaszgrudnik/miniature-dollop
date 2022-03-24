/* Server uses IPv6 protocol */


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

  if(argc < 2 || argc > 2){
    printf("%s\n", "error: invalid arguments\nType server --help to get more information.");
    exit(EXIT_FAILURE);
  }

  if(argc == 2 && !strcmp(argv[1], "--help")){
    printf("%s\n", "To run this program type: server <port>");
    exit(0);
  }


  // Server implementation:

  int sfd = socket(AF_INET6, SOCK_STREAM, 0);

  if(sfd == -1)
    error(errno);

  struct sockaddr_in6 server_saddr_in6, client_saddr_in6;
  socklen_t server_saddr_len, client_saddr_len;

  memset(&server_saddr_in6, 0, sizeof(server_saddr_in6));
  memset(&client_saddr_in6, 0, sizeof(client_saddr_in6));

  server_saddr_in6.sin6_family = AF_INET6;
  server_saddr_in6.sin6_port = htons(atoi(argv[1]));
  server_saddr_in6.sin6_addr = in6addr_any;

  server_saddr_len = sizeof(server_saddr_in6);
  client_saddr_len = sizeof(client_saddr_in6);

  if(bind(sfd, (struct sockaddr*) &server_saddr_in6, server_saddr_len) == -1)
    error(errno);

  printf("%s\n", "Connected to the server");
  char buffer[256];
  strcpy(buffer, "Hello World!");


  if(listen(sfd, 50) == -1)
    error(errno);

  char address[INET6_ADDRSTRLEN];

  do {

      int arv = accept(sfd, (struct sockaddr *) &client_saddr_in6, &client_saddr_len);
      inet_ntop(AF_INET6, &client_saddr_in6, address, INET6_ADDRSTRLEN);

      printf("Client:\n\tIPv6 address: %s\n\tport: %d\n", address, client_saddr_in6.sin6_port);

      int isIPv4_mappedIPv6addresses = IN6_IS_ADDR_V4MAPPED(client_saddr_in6.sin6_addr.s6_addr);

      if(isIPv4_mappedIPv6addresses)
        printf("\tIPv4-mapped IPv6 addresses: true\n");
      else
       printf("\tIPv4-mapped IPv6 addresses: false\n");


      write(arv, buffer, strlen(buffer));
      close(arv);

  } while(1);



}
