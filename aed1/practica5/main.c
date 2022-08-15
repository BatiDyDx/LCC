#include "../contact.h"
#include "hashtable.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/** Capacidad inicial para la tabla hash */
#define INITIAL_SIZE 3

/**
 * Caso de prueba: Tabla hash para contactos
 */
int main() {

  // Iniciar tabla hash
  HashTable table = hashtable_init(
      INITIAL_SIZE, (CopyFunction) contact_copy,
      (CompareFunction) contact_compare,
      (DestroyFunction) contact_free, (HashFunction) contact_hash);

  // Contactos
  Contact *agenda[6];
  agenda[0] = contact_init("Pepe Argento", "3412695452", 61);
  agenda[1] = contact_init("Moni Argento", "3412684759", 60);
  agenda[2] = contact_init("Coqui Argento", "3415694286", 32);
  agenda[3] = contact_init("Paola Argento", "3416259862", 29);
  agenda[4] = contact_init("Maria Elena Fuseneco", "3416874594", 59);
  agenda[5] = contact_init("Dardo Fuseneco", "3416894526", 64);

  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Insertando contacto: ");
    contact_print(agenda[i]);
    printf(" en la casilla %d.\n",
            contact_hash(agenda[i]) % hashtable_size(table));
    unsigned nElems = hashtable_nelems(table);
    hashtable_insert(table, agenda[i]);
    if (hashtable_nelems(table) == nElems)
      printf("\tInsercion fallida: Colision.\n");
    else
      printf("\tInsercion exitosa.\n");
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contact_print(agenda[i]);
    puts("");
    Contacto *ret = hashtable_search(table, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Eliminar
  printf("\nEliminacion:\n");
  for (int i = 5; i > 2; --i) {
    printf("Eliminando el contacto: ");
    contact_print(agenda[i]);
    puts("");
    hashtable_remove(table, agenda[i]);
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contact_print(agenda[i]);
    puts("");
    Contacto *ret = hashtable_search(table, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Sobrescribir un contacto
  Contacto *nuevoContacto = contact_init("Pepe Argento", "3410000000", 71);
  printf("\nSobrescribiendo el contacto: ");
  contact_print(agenda[0]);
  printf("\n\tpor: ");
  contact_print(nuevoContacto);
  puts("");
  hashtable_insert(table, nuevoContacto);
  // Chequeamos que se haya sobrescrito
  Contacto *ret = hashtable_search(
      table, agenda[0]); // Es equivalente a buscar nuevoContacto porque se
                         // compara por nombre
  printf("El nuevo contacto es: ");
  contact_print(ret);
  puts("");

  // Liberar memoria
  hashtable_free(table);
  for (int i = 0; i < 6; ++i)
    contact_free(agenda[i]);
  contact_free(nuevoContacto);

  return 0;
}