#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void mezclar_con_numeros(char* entrada, char* respuesta) {
  int len = strlen(entrada);
  for (int i = 0; i < len; i++) {
    char c = entrada[i];
    switch (c) {
      case 'a':
        respuesta[i] = '4';
        break;
      case 'e':
        respuesta[i] = '3';
        break;
      case 'i':
        respuesta[i] = '1';
        break;
      case 'o':
        respuesta[i] = '0';
        break;
      case 'u':
        respuesta[i] = '5';
        break;
      case ' ':
        respuesta[i] = '*';
        break;
      default:
        respuesta[i] = c;
        break;
    }
  }
  respuesta[len] = '\0'; // Marcar fin de la cadena
}

void mezclar_con_numeros_punteros(char* entrada, char* respuesta) {
  // Puntero que avanza con la iteracion, modificando la cadena respuesta
  char* s;
  for (s = respuesta; *entrada != '\0'; s++, entrada++) {
    switch (*entrada) {
      case 'a':
        *s = '4';
        break;
      case 'e':
        *s = '3';
        break;
      case 'i':
        *s = '1';
        break;
      case 'o':
        *s = '0';
        break;
      case 'u':
        *s = '5';
        break;
      case ' ':
        *s = '*';
        break;
      default:
        *s = *entrada;
        break;
    }
  }
  *s = '\0'; // Marcar fin de la cadena
}

char* tomar_input() {
  char c;
  int i = 0, tam = 20;
  char* entrada = malloc(sizeof(char) * (tam + 1));
  assert(entrada != NULL);
  printf("Ingrese la cadena: ");
  while ((c = getchar()) != '\n') {
    if (i == tam) {
      tam *= 2;
      entrada = realloc(entrada, sizeof(char) * (tam + 1));
      assert(entrada != NULL);
    }
    entrada[i++] = c;
  }
  entrada[i] = '\0';
  return entrada;
}

int continuar() {
  char c;
  printf("Desea continuar? (S para si, N para no): ");
  c = getchar();
  getchar(); // Consumir el caracter '\n'
  while (c != 'S' && c != 'N') {
    printf("Desea continuar? (S para si, N para no): ");
    c = getchar();
    getchar(); // Consumir el caracter '\n'
  }
  // Con opcion de usar el operador ternario: return c == 'N' ? 0 : 1
  if (c == 'N')
    return 0;
  else
    return 1; 
}

int main() {
  while (continuar()) {
    char* entrada = tomar_input();
    char* modificada = malloc(sizeof(char) * (strlen(entrada) + 1));
    assert(modificada != NULL); // Chequeamos que la memoria pedida sea correcta
    mezclar_con_numeros(entrada, modificada);
    
    printf("Original: %s, Modificada: %s\n", entrada, modificada);

    free(entrada);
    free(modificada);
  }

  return 0;
}