#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Casos de prueba para arboles AVL
*/

/**
  * Funciones para usar arboles AVL con datos de tipo int *
*/
static void* copy_int(void* i) {
  int* p = malloc(sizeof(int));
  *p = *(int*)i;
  return p;
}
static int cmp_int_pointer(void* i1, void* i2) {
  return (*(int*)i1 - *(int*)i2);
}

static void print_int_pointer(void* i,
  __attribute__((unused)) void* extra) {
  printf("%d ", *(int*)i);
}

int main() {
  // Caso de prueba 1:
  // se insertan 500 enteros aleatorios entre 0 y 999,
  // validando que cada arbol intermedio sea AVL
  AVL tree = avl_init(copy_int, cmp_int_pointer, free);
  for (int i = 0; i < 500; ++i) {
    int k = rand() % 1000;
    avl_insert(tree, &k);
    assert(avl_check(tree) == 1);
  }
  avl_destroy(tree);

  // Caso de prueba 2:
  // arbol AVL de la practica,
  // imprimiendo en preorden cada arbol intermedio
  tree = avl_init(copy_int, cmp_int_pointer, free);
  int numbers[] = { 10, 20, 15, 25, 30, 16, 18, 19 };
  for (int i = 0; i < 8; ++i) {
    avl_insert(tree, numbers + i);
    printf("Se inserto %d. Recorrido preorden: ", numbers[i]);
    avl_visit(tree, AVL_PREORDER, print_int_pointer, NULL);
    puts("");
  }

  // caso de prueba 3:
  // buscar numbers en el arbol
  int other_numbers[] = { -50, -4, 5, 14, 27, 56 };
  for (int i = 0; i < 8; ++i)
    assert(avl_search(tree, numbers + i) == 1);
  for (int i = 0; i < 6; ++i)
    assert(avl_search(tree, other_numbers + i) == 0);

  avl_destroy(tree);

  puts("Ok");

  return 0;
}