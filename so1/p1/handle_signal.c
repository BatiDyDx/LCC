#include <signal.h>
#include <stdio.h>
#include <setjmp.h>

int denom = 0;

jmp_buf env;

void handler(int s) {
  printf("Ouch!\n");
  denom = 1;
  longjmp(env, 1);
}

int main() {
  int r;
  signal(SIGFPE, handler);
  (void) setjmp(env);
  r = 1 / denom;
  printf("r = %d\n", r);
  return 0;
}

