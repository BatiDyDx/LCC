#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#ifndef FD_COPY
#include <string.h>
#define FD_COPY(src, dest) (memcpy(dest, src, sizeof(fd_set)))
#endif

/*
 * Para probar, usar netcat. Ej:
 *
 *      $ nc localhost 4040
 *      NUEVO
 *      0
 *      NUEVO
 *      1
 *      CHAU
 */

void quit(char *s) {
	perror(s);
	abort();
}

int U = 0;

int fd_readline(int fd, char *buf) {
	int rc;
	int i = 0;

	/*
	 * Leemos de a un caracter (no muy eficiente...) hasta
	 * completar una línea.
	 */
	while ((rc = read(fd, buf + i, 1)) > 0) {
		if (buf[i] == '\n')
			break;
		i++;
	}

	if (rc < 0)
		return rc;

	buf[i] = 0;
	return i;
}

int handle_conn(int csock) {
	char buf[200];
	int rc;

  /* Atendemos pedidos, uno por linea */
  rc = fd_readline(csock, buf);
  if (rc < 0)
    quit("read... raro");

  if (rc == 0) {
    /* linea vacia, se cerró la conexión */
    close(csock);
    return 1;
  }

  if (!strcmp(buf, "NUEVO")) {
    char reply[20];
    sprintf(reply, "%d\n", U);
    U++;
    write(csock, reply, strlen(reply));
    return 0;
  } else if (!strcmp(buf, "CHAU")) {
    close(csock);
    return 1;
  }

  return 0;
}

void wait_for_clients(int lsock) {
	int csock = 0, close, max_fd = lsock;
  fd_set rfds, rfds_copy;
  FD_ZERO(&rfds);
  FD_SET(lsock, &rfds);
	
  while (1) {
    max_fd = csock > max_fd ? csock : max_fd;

    FD_COPY(&rfds, &rfds_copy);
    int rc = select(max_fd + 1, &rfds_copy, NULL, NULL, NULL);
    if (rc < 0)
      quit("Error with select");

    if (FD_ISSET(lsock, &rfds_copy)) {
      /* Esperamos una conexión, no nos interesa de donde viene */
      csock = accept(lsock, NULL, NULL);
      if (csock < 0)
        quit("accept");
      FD_SET(csock, &rfds);
      continue;
    }

    for (int i = 0; i <= max_fd; i++) {
      if (FD_ISSET(i, &rfds_copy)) {
        close = handle_conn(i);
        if (close)
          FD_CLR(i, &rfds);
      }
    }
  }
}

void wait_for_clients_epoll(int lsock) {
	int csock = 0, close, max_fd = lsock;
  fd_set rfds, rfds_copy;
  FD_ZERO(&rfds);
  FD_SET(lsock, &rfds);
	
  while (1) {
    max_fd = csock > max_fd ? csock : max_fd;

    FD_COPY(&rfds, &rfds_copy);
    int rc = select(max_fd + 1, &rfds_copy, NULL, NULL, NULL);
    if (rc < 0)
      quit("Error with select");

    if (FD_ISSET(lsock, &rfds_copy)) {
      /* Esperamos una conexión, no nos interesa de donde viene */
      csock = accept(lsock, NULL, NULL);
      if (csock < 0)
        quit("accept");
      FD_SET(csock, &rfds);
      continue;
    }

    for (int i = 0; i <= max_fd; i++) {
      if (FD_ISSET(i, &rfds_copy)) {
        close = handle_conn(i);
        if (close)
          FD_CLR(i, &rfds);
      }
    }
  }
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
	sa.sin_port = htons(4040);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
	rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
	if (rc < 0)
		quit("bind");

	/* Setear en modo escucha */
	rc = listen(lsock, 10);
	if (rc < 0)
		quit("listen");

	return lsock;
}

int main() {
	/*
	 * Notar que esta implementacion si bien varios clientes pueden estar
	 * conectados al servidor al mismo tiempo, la forma en que se
	 * responde a estos es secuencial
	 */
	int lsock;
  
	lsock = mk_lsock();
	wait_for_clients(lsock);
	close(lsock);
}

