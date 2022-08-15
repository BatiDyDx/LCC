#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "int_array.h"

// Funcion auxiliar de ordenado
void bubble_sort(float array[], int len) {
	for (int iter = 0 ; iter < len - 1 ; iter++) {
		for (int i = 0 ; i < len - iter - 1; i++) {
			if (array[i] > array[i + 1]) {
				float aux = array[i];
				array[i] = array[i + 1];
				array[i + 1] = aux;
			}
		}
	}
}

// Ejercicio 1
float mediana(float* array, int len) {
	float copy[len];
	for (int i = 0; i < len; i++)
		copy[i] = array[i];
	bubble_sort(copy, len);
	if (len % 2 == 0)
		return (copy[len/2 - 1] + copy[len/2]) / 2;
	else
		return copy[(len - 1) / 2];
}


// Ejercicio 2d
int string_compare(char* str1, char* str2) {
	while (*str1 || *str2) {
		if (*str1 < *str2)
			return -1;
		else if (*str1 > *str2)
			return 1;
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return 0;
	else if (*str1)
		return 1;
	else
		return -1;
	
}

void test_2() {
	assert(string_compare("hola", "holaa") == -1);
	assert(string_compare("chau", "chau") == 0);
	assert(string_compare("adios", "adeus") == 1);
}

// Ejercicios 3 y 4

void test_3_4() {
	size_t n = 10, insert_pos = 5;
	IntArray* arr = create(n);
	for (int i = 0; i < n; i++)
		write(arr, i, i * 2);
	for (int i = 0; i < n; i++)
		assert(read(arr, i) == 2 * i);
	print(arr);
	insert(arr, insert_pos, -1);
	for (int i = 0; i < n + 1; i++) {
		if (i < insert_pos)
			assert(read(arr, i) == 2 * i);
		else if (i > insert_pos)
			assert(read(arr, i) == 2 * (i - 1));
		else
			assert(read(arr, insert_pos) == -1);
	}
	assert(arr->size == n + 1);
	delete(arr, insert_pos);
	for (int i = 0; i < n; i++)
		assert(read(arr, i) == 2 * i);
	assert(arr->size == n);
	destroy(arr);
}

// Ejercicio 5
/* Se encuentra en los archivos matriz_uni.c y matriz_bi.c */

void test_5() {
	unsigned rows = 10, cols = 5;
	Matrix* m = create_matrix(rows, cols);
	write_matrix(m, 0, 0, 1);
	assert(read_matrix(m, 0, 0) == 1);
	change_rows(m, 0, 2);
	assert(read_matrix(m, 2, 0) == 1);
	double new_row[5] = {1,2,5,3,7};
	insert_row(m, new_row, 4);
	assert(row_numbers(m) == rows + 1);
	assert(read_matrix(m, 4, 1) == 2);

	print_matrix(m);

	destroy_matrix(m);
}

int main() {
	//test_2();
	//test_3_4();
	test_5();
	return 0;
}