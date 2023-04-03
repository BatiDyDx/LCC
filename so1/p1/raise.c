#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  printf("Before pause\n");
  // pause();
  raise(SIGSTOP);
  printf("After pause\n");
  return 0;
}
