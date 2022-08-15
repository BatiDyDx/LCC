#include "contact.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Crea un nuevo contacto.
 */
Contact *contact_init(char *name, char *phone, unsigned int age) {
  Contact *new = malloc(sizeof(Contact));

  new->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(new->name, name);

  new->phone = malloc(sizeof(char) * (strlen(phone) + 1));
  strcpy(new->phone, phone);

  new->age = age;

  return new;
}

/**
 * Crea una copia física del contacto.
 */
Contact *contact_copy(Contact *contact) {
  Contact *copia =
      contact_init(contact->name, contact->phone, contact->age);
  return copia;
}

/**
 * Compara el nombre de dos contactos en orden lexicográfico. Devuelve 0 si son
 * iguales, < 0 si el primero es menor que el segundo y > 0 si el primero es
 * mayor que el segundo.
 */
int contact_compare(Contact *c1, Contact *c2) {
  return (strcmp(c1->name, c2->name));
}

/**
 * Función destructora de un contacto.
 */
void contact_free(Contact *contact) {
  free(contact->name);
  free(contact->phone);
  free(contact);
}

/**
 * Imprime por pantalla un contacto.
 */
void contact_print(Contact *contact) {
  printf("%s, %s, %d.\n", contact->name, contact->phone, contact->age);
}

unsigned contact_hash(Contact *contact) {
  return KRHash(contact->name);
}
