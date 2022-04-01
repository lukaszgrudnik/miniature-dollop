// IPv4  server:

#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>


#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {


  if(argc < 2 || argc > 3){
    printf("%s\n", "error: invalid arguments\nType server --help to get more information.");
    exit(EXIT_FAILURE);
  }

  if(argc == 2 && !strcmp(argv[1], "--help")){
    printf("%s\n", "To run this program type: server <port>");
    exit(0);
  }


  int sfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sfd == -1)
      handle_error(strerror(errno));

  struct sockaddr_in server_addr_in, client_addr_in;

  memset(&server_addr_in, 0, sizeof(server_addr_in));

  server_addr_in.sin_family = AF_INET;
  server_addr_in.sin_port = htons(atoi(argv[1]));  // port in network byte order
  server_addr_in.sin_addr.s_addr = INADDR_ANY; // address in network byte order

  socklen_t server_addrlen, client_addrlen;

  server_addrlen = sizeof(server_addr_in);
  client_addrlen = sizeof(client_addr_in);

  if(bind(sfd, (struct sockaddr *) &server_addr_in, server_addrlen) == -1)
      handle_error(strerror(errno));


  if(listen(sfd, 50) == -1)
    handle_error(strerror(errno));

  char buffer[256];
  char address[INET_ADDRSTRLEN];

  strcpy(buffer, "Hello world");



  do {

    int arv = accept(sfd, (struct sockaddr *) &client_addr_in, &client_addrlen);

    if(arv == -1)
      break;

    inet_ntop(AF_INET, &client_addr_in, address, INET_ADDRSTRLEN);

    printf("Client:\n\tIPv4 address: %s\n\tport: %d\n", address, client_addr_in.sin_port);

    write(arv, buffer, strlen(buffer));

    close(arv);

  } while(1);

  close(sfd);

}
