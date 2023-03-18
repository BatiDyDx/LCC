#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid = fork();
	if (pid == 0) {
		printf("I am your son\n");
		exit(0);
	} else {
	  while (1) {
			sleep(10);
		  printf("I am your father\n");
	  }
	}
	return 0;
}

