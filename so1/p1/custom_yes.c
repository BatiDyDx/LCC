#include <unistd.h>
#include <fcntl.h>

int main() {
	while (1) {
		write(1, "y\n", 2);
	}
	return 0;
}

