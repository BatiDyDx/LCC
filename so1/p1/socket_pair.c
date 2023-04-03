#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MSG "Hola hijo, yo soy tu padre"
#define MSG2 "Gracias padre"

int main() {
  char buf[30];
  int sv[2];
  socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
  pid_t pid = fork();

  if (pid == 0) {
    read(sv[0], buf, strlen(MSG));
    buf[strlen(MSG)] = 0;
    printf("El hijo recibio: %s\n", buf);
    write(sv[1], MSG2, strlen(MSG2));
    close(sv[0]);
    close(sv[1]);
  } else {
    write(sv[1], MSG, strlen(MSG));
    wait(NULL);
    read(sv[0], buf, strlen(MSG2));
    printf("El padre recibio: %s\n", buf);
    close(sv[0]);
    close(sv[1]);
  }
  return 0;
}
