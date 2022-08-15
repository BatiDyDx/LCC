#include "gtree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Casos de prueba para arboles generales
 */

/**
 * Funciones para usar arboles generales con datos de tipo int *
 */
static void *copy_int(void *i) {
  int *p = malloc(sizeof(int));
  *p = *(int *)i;
  return p;
}

static int cmp_int_pointer(void *i1, void *i2) {
  return (*(int *)i1 - *(int *)i2);
}

static void print_int_pointer(void *i, __attribute__((unused)) void *extra) {
  printf("%d ", *(int *)i);
}

int main() {

  /** Construimos el siguiente arbol:
   *     1
   *  /  |  \
   * 2   3   4
   *    / \   \
   *   5   6   7
   *         / | \
   *        8  9  10
   */
  int datos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTree tree = gtree_init();
  tree = gtree_add(tree, NULL, datos, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos, datos + 3, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos, datos + 2, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos, datos + 1, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 2, datos + 5, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 2, datos + 4, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 3, datos + 6, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 6, datos + 9, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 6, datos + 8, copy_int,
                       cmp_int_pointer);
  tree = gtree_add(tree, datos + 6, datos + 7, copy_int,
                       cmp_int_pointer);
  puts("El arbol es:");
  gtree_iter(tree, print_int_pointer, NULL);
  puts("");
  printf("El arbol tiene %d nodos\n", gtree_nnodes(tree));
  gtree_destroy(tree, free);
  return 0;
}