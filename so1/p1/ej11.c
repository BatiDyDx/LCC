#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


#define BACKLOG 10
#define VALUE_SIZE 100
#define CACHE_SIZE 1000

void quit(char *s) {
	perror(s);
	abort();
}

int start_listening() {
  struct sockaddr_in sa;
  int lsock, rc, yes = 1;

  lsock = socket(AF_INET, SOCK_STREAM, 0);
  if (lsock < 0)
    quit("Error with listeting socket");

  if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
    quit("setsockopt");

  sa.sin_family = AF_INET;
  sa.sin_port = htons(3942);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  rc = bind(lsock, (const struct sockaddr*) &sa, sizeof(sa));
  if (rc < 0)
    quit("Error with bind");
  
  rc = listen(lsock, BACKLOG);
  if (rc < 0)
    quit("Error with listen");

  return lsock;

}

int main() {
  int lsock;
  lsock = start_listening();

  
}
