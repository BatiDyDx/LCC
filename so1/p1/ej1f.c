#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main() {
  size_t MB = 1 << 20;
	size_t GB = MB << 10;
  char* buffer = malloc(GB);
  assert(buffer != NULL);
  
	for (int i = 0; i < GB; i += MB) {
    memset(buffer + i, 0, i);
		sleep(5);
	}

	return 0;
}

