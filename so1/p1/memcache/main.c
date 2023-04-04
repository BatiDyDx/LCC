#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/mman.h>
#include "hashtable.h"

#define BACKLOG 10
#define VALUE_SIZE 100
#define CACHE_SIZE 1000

static HashTable cache;

static char* copy_key(char* data) {
    size_t len = strlen(data);
    char* copy = malloc(sizeof(char) * (len + 1));
    memcpy(copy, data, sizeof(sizeof(char) * (len + 1)));
    return copy;
}

static unsigned hash_key(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}

void quit(char *s) {
	perror(s);
	abort();
}





void wait_for_clients(int lsock) {
	int csock;

	/* Esperamos una conexión, no nos interesa de donde viene */
	csock = accept(lsock, NULL, NULL);
	if (csock < 0)
		quit("accept");

	/* Atendemos al cliente */
	handle_conn(csock);

	/* Volvemos a esperar conexiones */
	wait_for_clients(lsock);
}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_lsock() {
	struct sockaddr_in sa;
	int lsock;
	int rc;
	int yes = 1;

	/* Crear socket */
	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0)
		quit("socket");

	/* Setear opción reuseaddr... normalmente no es necesario */
	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
		quit("setsockopt");

	sa.sin_family = AF_INET;
	sa.sin_port = htons(3942);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
	rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
	if (rc < 0)
		quit("bind");

	/* Setear en modo escucha */
	rc = listen(lsock, BACKLOG);
	if (rc < 0)
		quit("listen");

	return lsock;
}

int main() {
  int lsock = mk_lsock();
  cache = hashtable_init(CACHE_SIZE, copy_key, strcmp, free, hash_key);
  wait_for_clients(lsock);
  hashtable_free(cache);
  close(lsock);
  return 0;
}
