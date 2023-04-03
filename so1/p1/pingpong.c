#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define CHILD 0
#define PARENT 1

int flag[2];

void handler(int sig) {
    if (sig == SIGUSR1) {
        flag[PARENT] = 1;
    } else {
        flag[CHILD] = 1;
    }   
    return;
}

void child_process() {
    while (1) {
        printf("Ping!\n");
        kill(getppid(), SIGUSR2);
        while (flag[PARENT] == 0) { }
    }
    return;
}

void parent_process(pid_t t) {
    while (1) {
        //kill(t, SIGUSR1);
        while (flag[CHILD] == 0) { }
        printf("Pong!\n");

        kill(t, SIGUSR1);
    }
    return;
}

void setup() {
    flag[CHILD] = 0;
    flag[PARENT] = 0;
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
}

int main(int argc, char* argv[]) {  
    setup();
    pid_t t = fork();
    if (t == 0) {
        child_process();
    } else {
        parent_process(t);
    }
    return 0;
}
