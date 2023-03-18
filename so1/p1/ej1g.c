#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  size_t MB = 1 << 20;
  char stack[MB];
  memset(stack, 0, MB);
  pid_t pid = fork();

	while (1) {
    sleep(10);
    printf("I am the %s", pid == 0 ? "child" : "father");
    putchar('\n');
    memset(stack, 0, MB);
  }

  return 0;
}

