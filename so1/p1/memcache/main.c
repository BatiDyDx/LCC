#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <assert.h>

#include <signal.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "hashtable.h"

#define BACKLOG 10
#define VALUE_SIZE 100
#define CACHE_SIZE 1000

void quit(char *s) {
  perror(s);
  abort();
}

typedef enum {
  PUT,  /* Put takes key and value and writes it on cache
           (overwrites key if already in memory) */
  DEL,  // Delete key from cache
  GET,   // Get value associated with key
  /* Server always responds with OK, unless command is GET
   * and the key is not found on cache, in which case the
   * server responds with NOTFOUND
   */
  INVAL // Invalid command
} CommandType;

typedef struct {
  char *key, *value;
} KeyValue;

typedef struct {
  CommandType type;
  KeyValue kv;
} Command;

static HashTable cache;
static jmp_buf env;

static KeyValue* copy_kv(KeyValue *kv) {
    KeyValue *copy = malloc(sizeof(KeyValue));
    if (!copy)
      quit("malloc");
    
    copy->key = strdup(kv->key);
    copy->value = strdup(kv->value);
    return copy;
}

static unsigned hash_kv(KeyValue *kv) {
  unsigned hashval = 0;
  for (char *s = kv->key; *s != '\0'; ++s)
    hashval = *s + 31 * hashval;

  return hashval;
}

int cmp_kv(KeyValue *kv1, KeyValue *kv2) {
  return strcmp(kv1->key, kv2->key);
}

void destroy_kv(KeyValue *kv) {
  free(kv->key);
  free(kv->value);
  free(kv);
}

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

void shutdown_server(int sig) {
  puts("Shutting down server");
  hashtable_free(cache);
  exit(EXIT_SUCCESS);
}

Command parse(char* query) {
  char *tokens[3];
  const char *delim = " \t\n";
  Command cmd;
  cmd.type = INVAL;
  
  tokens[0] = strtok(query, delim);
  tokens[1] = strtok(NULL, delim);
  tokens[2] = strtok(NULL, delim);

   if (strtok(NULL, query)) // More than 3 arguments, not valid
     return cmd;

  if (!tokens[0] || !tokens[1]) // At least 2 arguments are needed
    return cmd;

  // Determine type of command
  if (!strcmp(tokens[0], "GET")) {
    if (tokens[2]) // Argument not expected
      return cmd;
    cmd.type = GET;
    cmd.kv.key = strdup(tokens[1]);
  } else if (!strcmp(tokens[0], "DEL")) {
    if (tokens[2]) // Argument not expected
      return cmd;
    cmd.type = DEL;
    cmd.kv.key = strdup(tokens[1]);
  } else if (!strcmp(tokens[0], "PUT")) {
    if (!tokens[2])
      return cmd;
    cmd.type = PUT;
    cmd.kv.key = strdup(tokens[1]);
    cmd.kv.value = strdup(tokens[2]);    
  }
  return cmd;
}

void perform_query(int client_sock, Command *cmd) {
  KeyValue *result = NULL;
  switch (cmd->type) {
    case PUT:
      hashtable_insert(cache, (void*) &cmd->kv);
      write(client_sock, "OK\n", 3);
      break;
    case DEL:
      hashtable_remove(cache, (void*) &cmd->kv);
      write(client_sock, "OK\n", 3);
      break;
    case GET:
      result = hashtable_search(cache, &cmd->kv);
      if (result) {
        write(client_sock, "OK ", 3);
        write(client_sock, result->value, strlen(result->value));
        write(client_sock, "\n", 1);
      } else
        write(client_sock, "NOT FOUND\n", 10);
      break;
    case INVAL:
      write(client_sock, "INVAL\n", 6);
      break;
  }
}

int handle_client(int client_sock) {
  int rc;
  char buf[100];
  rc = fd_readline(client_sock, buf);

  if (rc < 0)
    quit("read");
  
  if (rc == 0)
    return 1;

  Command cmd = parse(buf);
  perform_query(client_sock, &cmd);
  return 0;
}

void server(int listen_sock) {
  int client_sock, epollfd, nfds, stop = 0;
  struct epoll_event ev, events[BACKLOG];
  struct sigaction sa;

  epollfd = epoll_create1(0);
  if (epollfd < 0)
    quit("epoll_create1");

  ev.events = EPOLLIN;
  ev.data.fd = listen_sock;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) < 0)
    quit("epoll_ctl");

  ev.events = EPOLLIN | EPOLLET; // Settings for adding clients
  
  // Inmediately after receiving a SIGINT jumps here and starts cleaning up
  sa.sa_handler = shutdown_server;
  sigaction(SIGINT, &sa, NULL);

  while (1) {
    nfds = epoll_wait(epollfd, events, BACKLOG, -1);
    if (nfds < 0)
      quit("epoll_wait");

    for (int i = 0; i < nfds; i++) {
      if (events[i].data.fd == listen_sock) { // Accept client
        /* Esperamos una conexión, no nos interesa de donde viene */
        client_sock = accept(listen_sock, NULL, NULL);
        if (client_sock < 0)
          quit("accept");
        ev.data.fd = client_sock;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_sock, &ev) < 0)
          quit("epoll_ctl");
        write(client_sock, "Connection established\n", 23);
        puts("Client connected");
      } else { // Handle client
        client_sock = events[i].data.fd;
        int closed = handle_client(client_sock);
        if (closed) {
          write(client_sock, "Closing connection...\n", 22);
          epoll_ctl(epollfd, EPOLL_CTL_DEL, client_sock, NULL);
          close(client_sock);
          puts("Client disconnected");
        }
      }
    }
  }

  return;
}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_listen_sock() {
  struct sockaddr_in sa;
  int listen_sock;
  int rc;
  int yes = 1;

  /* Crear socket */
  listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_sock < 0)
    quit("socket");

  /* Setear opción reuseaddr... normalmente no es necesario */
  if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
    quit("setsockopt");

  sa.sin_family = AF_INET;
  sa.sin_port = htons(3942);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
  rc = bind(listen_sock, (struct sockaddr *)&sa, sizeof sa);
  if (rc < 0)
    quit("bind");

  /* Setear en modo escucha */
  rc = listen(listen_sock, BACKLOG);
  if (rc < 0)
    quit("listen");

  puts("Starting server");
  puts("Server listening on port 3942 ...");

  return listen_sock;
}

int main() {
  int listen_sock = mk_listen_sock();
  cache = hashtable_init(CACHE_SIZE, (void* (*)(void*))        copy_kv,
                                       (int (*)(void*, void*)) cmp_kv,
                                      (void (*)(void*))        destroy_kv,
                                  (unsigned (*)(void*))        hash_kv);
  server(listen_sock);
}
