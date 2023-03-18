#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int fd = open("dummy.txt", O_RDWR);
	execl("./a.out", NULL);
	return 0;
}
