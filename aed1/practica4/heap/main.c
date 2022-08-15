#include "bheap.h"
#include "../../contact.h"
#include <stdio.h>
#include <assert.h>

#define INITIAL_SIZE 3

int main() {
  // Crear heap
  BHeap heap = bheap_init(INITIAL_SIZE, (CompareFunction) contact_compare,
              (CopyFunction) contact_copy, (DestroyFunction) contact_free);

  Contact* agenda[5];
  agenda[0] = contact_init("Lionel Messi", "3411234567", 35);
  agenda[1] = contact_init("Kun Aguero", "3454310447", 34);
  agenda[2] = contact_init("Angel Di Maria", "3415438384", 34);
  agenda[3] = contact_init("Rodri De Paul", "3429483939", 28);
  agenda[4] = contact_init("Gio Lo Celso", "3414324987", 26);

  // Insercion
  bheap_insert(heap, agenda[0]);
  bheap_insert(heap, agenda[1]);
  bheap_insert(heap, agenda[2]);
  bheap_insert(heap, agenda[3]);
  bheap_insert(heap, agenda[4]);

  // Imprimir
  bheap_iter(heap, (VisitFunction) contact_print);
  putchar('\n');

  // Remover
  bheap_remove(heap, agenda[2]);
  bheap_remove(heap, agenda[3]);
  for (unsigned i = 0; i < heap->last; ++i) {
    // Chequear que fueron eliminados
    assert(contact_compare(agenda[2], heap->arr[i]) != 0);
    assert(contact_compare(agenda[3], heap->arr[i]) != 0);
  }

  while (!bheap_empty(heap)) {
    puts("Maximo del heap");
    Contact* player = (Contact*) bheap_remove_max(heap);
    contact_print(player);
    contact_free(player);
  }
  putchar('\n');

  // Liberar
  bheap_destroy(heap);

  heap = bheap_from_array((void**) agenda, 5,
            (CompareFunction) contact_compare, (CopyFunction) contact_copy,
            (DestroyFunction) contact_free);
  bheap_iter(heap, (VisitFunction) contact_print);
  bheap_destroy(heap);

  for (int i = 0; i < 5; ++i)
    contact_free(agenda[i]);

  return 0;
}

