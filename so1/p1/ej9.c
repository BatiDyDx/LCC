#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <setjmp.h>
#include <unistd.h>

int i = 0;
jmp_buf env;
int parent_pid;
int child_pid;

void sigaction_handler(int sig) {
  printf("Recibiendo señal\n");
  if (getpid() == parent_pid) {
    if (i < 100) {
      printf("Soy el padre\n");
      kill(child_pid, SIGUSR1);
    }
    i++;
  } else {
    printf("Soy el hijo\n");
    kill(parent_pid, SIGUSR1);
  }
  longjmp(env, 1);
}

void signal_handler(int sig) {
  printf("Recibiendo señal\n");
  if (getpid() == parent_pid) {
    if (i < 100) {
      printf("Soy el padre\n");
      kill(child_pid, SIGUSR1);
      signal(SIGUSR1, signal_handler); // Reinstall signal handler
    }
    i++;
  } else {
    printf("Soy el hijo\n");
    kill(parent_pid, SIGUSR1);
    signal(SIGUSR1, signal_handler); // Reinstall signal handler
  }
  longjmp(env, 1);
}

int main() {
  struct sigaction act = {sigaction_handler, 0, 0};
  sigaction(SIGUSR1, &act, NULL);
  parent_pid = getpid();
  pid_t pid = fork();
  if (pid == 0) {
    (void) setjmp(env);
    while (1) { sleep(5); printf("Estoy en el loop del hijo\n"); };
  } else {
    child_pid = pid;

    if (setjmp(env) == 0) {
      sleep(1);
      kill(pid, SIGUSR1);
    }
    // pause() will pause the process until a signal is received
    while (1) { sleep(5); printf("Estoy en el loop del padre\n"); };
  }
  return 0;
}

