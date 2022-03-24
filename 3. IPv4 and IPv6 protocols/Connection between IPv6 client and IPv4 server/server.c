
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {

  int sfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sfd == -1)
      handle_error(strerror(errno));

  struct sockaddr_in addr;

  // Reset address structe:
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);  // port in network byte order
  addr.sin_addr.s_addr = INADDR_ANY; // address in network byte order

  socklen_t addrlen;
  addrlen = sizeof(addr);

  if(bind(sfd, (struct sockaddr *) &addr, addrlen) == -1)
      handle_error(strerror(errno));


  if(listen(sfd, 50) == -1)
    handle_error(strerror(errno));


  do {

    int arv = accept(sfd, NULL, NULL);



    if(arv > 0)
      printf("%s\n","new connection" );

  } while(1);


}
