#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	for (int i = 0; i < 10; i++) {
    printf("I am installing: %%%d\n", i * 10);
		sleep(5);
		printf("Proceed?[y/n]: ");
		fflush(stdout);
    char c = getchar();
		getchar();
		if (c != 'y')
		  exit(1);
	}

  return 0;
}
