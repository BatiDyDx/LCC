#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    char* buf = malloc(1 << 20);
    memset(buf, 0, 1 << 19);
    // sleep(10);
  } else {
    do {
      sleep(5);
    } while (1);
  }
  return 0;
}
