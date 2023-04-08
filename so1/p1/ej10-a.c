#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <semaphore.h> // Deprecated on OS X :(

#define SHMEM_FILE "ej10_shm"
#define SHM_SIZE (sizeof(unsigned) + sizeof(sem_t))

void quit(char *s) {
  perror(s);
  abort();
}

int *n;
sem_t *mutex;

int fd_readline(int fd, char *buf) {
  int rc;
  int i = 0;

  /*
   * Leemos de a un caracter (no muy eficiente...) hasta
   * completar una línea.
   * */
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

void cleanup(int sig) {
  puts("Cleaning up...");
  puts("Shutting down server");
  sem_destroy(mutex);
  munmap(n, SHM_SIZE);
  shm_unlink(SHMEM_FILE);
  exit(EXIT_SUCCESS);
}

void handle_conn(int csock) {
  char buf[200];
  int rc;

  write(csock, "Connected to server\n", 20);

  while (1) {
    /* Atendemos pedidos, uno por linea */
    rc = fd_readline(csock, buf);
    if (rc < 0)
      quit("read... raro");

    if (rc == 0)
      /* linea vacia, cerramos la conexion */
      break;

    if (!strcmp(buf, "NUEVO")) {
      char reply[20];
      sem_wait(mutex);
      sprintf(reply, "%d\n", (*n)++);
      sem_post(mutex);
      write(csock, reply, strlen(reply));

    } else if (!strcmp(buf, "CHAU"))
      break;
  }
  write(csock, "Closing connection\n", 19);
  close(csock);
}

void wait_for_clients(int lsock, int shmfd) {
  int conn_sock;
  *n = 0;

  while (1) {
    conn_sock = accept(lsock, NULL, NULL);
    puts("Client connected");
    if (fork() == 0) {
      handle_conn(conn_sock);
      puts("Client disconnected");
      munmap(n, SHM_SIZE);
      close(shmfd);
      exit(EXIT_SUCCESS);
    }
    close(conn_sock);
  }

  // TODO Implement signal handler to execute clean up code
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

  /* Bindear al puerto 4040 TCP, en todas las direcciones
   * disponibles */
  rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
  if (rc < 0)
    quit("bind");

  /* Setear en modo escucha */
  rc = listen(lsock, 10);
  if (rc < 0)
    quit("listen");

  puts("Starting server...");

  return lsock;

}

int main() {
  int lsock = mk_lsock();
  int shmfd = shm_open(SHMEM_FILE, O_RDWR | O_CREAT, 0664);
  struct sigaction sa;
  ftruncate(shmfd, SHM_SIZE);
  
  n = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
  mutex = n + 1; // mutex is next to n in memory
  
  sa.sa_handler = cleanup;
  sigaction(SIGINT, &sa, NULL);

  sem_init(mutex, 1, 1); // 1 for using between processes
  wait_for_clients(lsock, shmfd);
  
}

