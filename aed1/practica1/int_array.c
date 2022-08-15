#include "int_array.h"

IntArray* create(size_t size) {
    IntArray* arr = malloc(sizeof(IntArray));
    arr->size = size;
    arr->dir = malloc(sizeof(int) * size);
    assert(arr->dir != NULL);
    return arr;
}

void destroy(IntArray* arr) {
    free(arr->dir);
    free(arr);
}

int read(IntArray* arr, unsigned pos) {
    return arr->dir[pos];
}

void write(IntArray* arr, unsigned pos, int data) {
    arr->dir[pos] = data;
}

void print(IntArray* arr) {
    putchar('[');
    for (int i = 0; i < arr->size; i++)
        printf("%d, ", arr->dir[i]);
    putchar(']');
    putchar('\n');
}

void resize(IntArray* arr, size_t nsize) {
    arr->dir = realloc(arr->dir, sizeof(int) * nsize);
    assert(arr->dir != NULL);
    arr->size = nsize;
}

void insert(IntArray* arr, unsigned pos, int data) {
    resize(arr, arr->size + 1);
    for (int i = arr->size - 1; i >= pos; i--) {
        arr->dir[i + 1] = arr->dir[i];
    }
    arr->dir[pos] = data;
}

void delete(IntArray* arr, unsigned pos) {
    for (int i = pos; i < arr->size - 1; i++)
        arr->dir[i] = arr->dir[i + 1];
    resize(arr, arr->size - 1);
}