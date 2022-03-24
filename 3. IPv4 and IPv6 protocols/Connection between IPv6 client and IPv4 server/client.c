
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <net/if.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {

  int sfd = socket(AF_INET6, SOCK_STREAM, 0);


  struct sockaddr_in6 addr;

  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(atoi(argv[2]));  // port in network byte order
  addr.sin6_scope_id = if_nametoindex(argv[3]);

  inet_pton(AF_INET6, argv[1], &(addr.sin6_addr));

  socklen_t addrlen;
  addrlen = sizeof(addr);

  connect(sfd, (struct sockaddr *) &addr, addrlen);


}
