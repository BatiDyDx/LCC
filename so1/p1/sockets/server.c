#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "socket_server_config.h"
#include <stdio.h>
#include <fcntl.h>

#define MSG "Hola capo"

char buffer[MAX_MSG + 1];

int main() {
  int socket_client = socket(AF_UNIX, SOCK_DGRAM, 0);
  int size;
  struct sockaddr_un cli_name;
  struct sockaddr_un server_name;

  cli_name.sun_family = AF_UNIX;
  server_name.sun_family = AF_UNIX;

  strcpy(cli_name.sun_path, CLI_NAME);
  strcpy(server_name.sun_path, SERVER_NAME);
  
  socklen_t server_size = sizeof(server_name);

  unlink(SERVER_NAME);
  // Asignar nombre al socket
  (void) bind(socket_client, (const struct sockaddr*) &server_name, server_size);
  recvfrom(socket_client, buffer, MAX_MSG, 0, &cli_name, &size);
  printf("Recibiendo: %s\n", buffer);
  sendto(socket_client, MSG, strlen(MSG), 0, (const struct sockaddr*) &cli_name, sizeof(cli_name));
  printf("Mensaje enviado\n");
  close(socket_client);
  return 0;
}

