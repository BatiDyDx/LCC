#include "problems.h"
#include <stdio.h>
#include <assert.h>

#define N 15

int main() {
	int ans[N] = {1, 1, 3, 1, 3, 5, 7, 1, 3, 5, 7, 1, 3, 13, 15};
	for (int i = 0; i < N; ++i) {
		assert(survivor_clist(i + 1) == ans[i]);
		assert(survivor_recursive(i + 1) == ans[i]);
		assert(survivor_constant(i + 1) == ans[i]);
	}
	return 0;
}
