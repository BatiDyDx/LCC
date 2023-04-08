#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define MAX_EVENTS 10

void quit(char *s) {
  perror(s);
  abort();
}

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

  if (rc == 0)
    return 1;

  if (!strcmp(buf, "NUEVO")) {
    char reply[20];
    sprintf(reply, "%d\n", U++);
    write(csock, reply, strlen(reply));
  } else if (!strcmp(buf, "CHAU")) {
    fflush(stdout);
    return 1;
  }
  return 0;
}

void wait_for_clients_epoll(int lsock) {

  struct epoll_event ev, events[MAX_EVENTS];
  int conn_sock, nfds, epollfd;

  size_t memsize = sizeof(unsigned);

  epollfd = epoll_create1(0);
  if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  ev.events = EPOLLIN;
  ev.data.fd = lsock;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, lsock, &ev) == -1) {
    perror("epoll_ctl: lsock");
    exit(EXIT_FAILURE);
  }

  while (1) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < nfds; ++i) {
      if (events[i].data.fd == lsock) { // Client waiting to connect
        conn_sock = accept(lsock, NULL, NULL);
        if (conn_sock == -1)
          quit("accept");
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = conn_sock;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev);
      } else { // Client waiting for response
        conn_sock = events[i].data.fd;
        if (handle_conn(conn_sock)) { // Returns 1 if client is done
          epoll_ctl(epollfd, EPOLL_CTL_DEL, conn_sock, NULL);
          close(conn_sock);
        }
      }
    }
  }
  close(epollfd);
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
  int lsock;
  
  lsock = mk_lsock();
  wait_for_clients_epoll(lsock);
  close(lsock);
}

