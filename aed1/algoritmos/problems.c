#include "problems.h"


/* AUXILIAR FUNCTIONS AND MACROS */

#define MIN(X, Y) (X < Y ? X : Y)

int ilog_2(Natural n) {
	int k;
	if (n == 0)
		return INT_MIN;
	// n = 1 * 2^k + a_(k-1) * 2^(k-1) + ... + a_1 * 2 + a_0 * 2^0
	// Then ilog_2(n) = log_2(2^k) <= log_2(n)
	// Dividing by 2 until n is 1 we get k
	for (k = 0; n >>= 1; k++);
	return k;
}

/* ################## */


Natural fib_recursive(unsigned n) {
	if (n <= 1)
		return n;
	return fib_recursive(n - 1) + fib_recursive(n - 2);
}

Natural fib_memo(unsigned n, Natural memo[]) {
	if (n <= 1)
		return n;

	if (memo[n] == 0)
		memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);

	return memo[n];
}

Natural fib_iterative(unsigned n) {
	Natural a = 0, b = 1;
	while (n-- > 0) {
		Natural tmp = a;
		a = b;
		b = b + tmp;
	}
	return a;
}

unsigned survivor_clist(const unsigned n) {
	assert(n >= 1);

	unsigned arr[n], result;
	for (int i = 0; i < n; i++)
		arr[i] = i + 1;
	
	CDList *list = cdlist_init((int*) arr, n);

	while (list->data != list->next->data)
		list = (cdlist_delete(list, 1))->next;

	result = list->data;
	cdlist_free(list);
	return result;
}

unsigned survivor_recursive(unsigned n) {
	assert(n >= 1);

	if (n == 1)
		return 1;

	if (n % 2 == 0)
		return 2 * survivor_recursive(n / 2);
	else
		return 2 * survivor_recursive((n - 1) / 2) + 1;
}

unsigned survivor_constant(unsigned n) {
	assert(n >= 1);
	unsigned k = ilog_2(n);
	unsigned m = n - power(2, k);
	return 2 * m + 1;
}

size_t find_peak_linear(int array[], size_t len) {
	size_t pos;
	int ge_left, le_right;
	if (len <= 1)
		pos = 0;
	else {
		for (size_t i = 0; i < len; i++) {
			ge_left = (i == 0) || array[i - 1] <= array[i]; // i != 0 -> array[i - 1] <= array[i]
			le_right = (i == len - 1) || array[i] <= array[i + 1]; // i != (len - 1) -> array[i] <= array[i + 1]
			if (ge_left && le_right) {
				pos = i;
				break;
			}
		}
	}
	return pos;
}

size_t find_peak_log(int array[], size_t len) {
	size_t mid_left, mid_right;
	if (len <= 1)
		return 0;
	mid_left = (len / 2) - 1;
	mid_right = len / 2;
	if (array[mid_left] < array[mid_right]) {
		// (len / 2) + (len % 2) is (len / 2) + 1 if len is odd,
		// (len / 2) otherwise. This matches with the length of the subarray
		return (len / 2) + \
			find_peak_log(array + mid_right, (len / 2) + (len % 2));
	} else
		return find_peak_log(array, len / 2);
}


int find_min_path_recursive(int **matrix, size_t i, size_t j) {
	if (i == 0 && j == 0)
		return matrix[i][j];
	else if (i == 0)
		return matrix[0][j] + \
			find_min_path_recursive(matrix, 0, j - 1);
	else if (j == 0)
		return matrix[i][0] + \
			find_min_path_recursive(matrix, i - 1, 0);
	return MIN(                                    \
		find_min_path_recursive(matrix, i - 1, j), \
		find_min_path_recursive(matrix, i, j - 1) );
}


int find_min_path_memo(int **matrix, size_t i, size_t j, int **memo) {
	if (memo[i][j] != -1)
		return memo[i][j];

	if (i != 0 && j != 0)
		return MIN(                                          \
			find_min_path_recursive(matrix, i - 1, j, memo), \
			find_min_path_recursive(matrix, i, j - 1, memo) );

	if (i == 0 && j == 0)
		memo[i][j] = matrix[i][j];
	else if (i == 0)
		memo[i][j] = matrix[i][j] + find_min_path_recursive(matrix, i, j - 1, memo);
	else if (j == 0)
		memo[i][j] = matrix[i][j] + find_min_path_recursive(matrix, i - 1, j, memo);
	return memo[i][j];
}

int find_min_path_iterative(int **matrix, size_t m, size_t n) {
	int *row = malloc(sizeof(int) * n), min_path;
	assert(row != NULL);

	// Array of min paths of the first row of the matrix
	row[0] = matrix[0][0];
	for (int j = 1; j < n; j++)
		row[j] = matrix[0][j] + row[j - 1];

	for (int i = 1; i < m; i++) {
		row[0] = row[0] + matrix[0];
		for (int j = 1; j < n; j++)
			row[j] = matrix[i][j] + MIN(row[j - 1], row[j]);
	}

	min_path = row[n];
	free(row);
	return min_path;
}

int find_sum(int n, int array[], size_t len) {
	if (len == 0)
		return 0;
	else if (len == 1)
		return *array == n;
	else if (*array == n)
		return 1;
	
	return ( find_sum(n, array + 1, len - 1) \
		|| find_sum(n - *array, array + 1, len - 1) );
}

double power(double base, unsigned n) {
	double tmp;
	if (n == 0)
		return base;
	tmp = power(base, n / 2);
	if (n % 2 == 0)
		return tmp * tmp;
	else
		return tmp * tmp * base;
}

double peval(double c[], const int n, const double x) {
	double res = 0;
	double y = 1; // Carries x^k to avoid calculating it every iteration

	for (int i = 0; i < n; i++) {
		res += c[i] * y;
		y *= x;
	}

	return res;
}