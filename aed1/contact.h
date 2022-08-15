#ifndef __CONTACTO_H__
#define __CONTACTO_H__

/**
 * Estructura que representa un contacto.
 */
typedef struct {
  char *name;
  char *phone;
  unsigned age;
} Contact;

/**
 * Crea un nuevo contacto.
 */
Contact *contact_init(char *name, char *phone, unsigned int age);

/**
 * Crea una copia física del contacto.
 */
Contact *contact_copy(Contact *contact);

/**
 * Compara el nombre de dos contactos en orden lexicográfico. Devuelve 0 si son
 * iguales, < 0 si el primero es menor que el segundo y > 0 si el primero es
 * mayor que el segundo.
 */
int contact_compare(Contact *c1, Contact *c2);

/**
 * Función destructora de un contacto.
 */
void contact_free(Contact *contact);

/**
 * Imprime por pantalla un contacto.
 */
void contact_print(Contact *contact);

/*
 * Hashea un contacto por su nombre
*/
unsigned contact_hash(Contact *contact);

#endif /* __CONTACTO_H__ */