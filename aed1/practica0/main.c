#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

// Ejercicio 3
void set_in(int* n) {
    if (*n)
        *n = 1;
}

void test_3() {
    int x = 1, y = 5, z = 0;
    set_in(&x);
    set_in(&y);
    set_in(&z);
    assert(x == 1);
    assert(y == 1);
    assert(z == 0);
}


// Ejercicio 6
char* get_new_line(void) {
    int len = 20;
    char c;
    int i = 0;
    char* str = malloc(sizeof(char) * (len + 1));
    assert(str != NULL);
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i == len) {
            len *= 2;
            str = realloc(str, sizeof(char) * (len + 1));
            assert(str != NULL);
        }
        str[i++] = c;
    }
    str = realloc(str, sizeof(char) * (i + 1));
    assert(str != NULL);
    str[i] = '\0';
    return str;
}

// Ejercicio 8
// a)
int apply(int (*f)(int), int n) {
    return (*f)(n);
}

// b)
void apply_in(int (*f)(int), int* n) {
    *n = (*f)(*n);
}

// c)
typedef void (*func)(int);
void recorre(func f, int a[], int n) {
    for (int i = 0; i < n; i++) {
        (*f)(a[i]);
    }
}

// Funciones auxiliares
int sucesor(int n) {
    return n + 1;
}

void imprimir(int n) {
    printf("%d\n", n);
}

void test_8() {
    int n = 11;
    assert(apply(sucesor, n) == n + 1);
    apply_in(sucesor, &n);
    assert(n == 12);
    
    const int size = 10;
    int a[size] = {1, 2, 3, 1, 6, 2, 4, 2};
    recorre(imprimir, a, size);
}

// Ejercicio 13

#define VALORES 12
#define CARTAS_MAZO 48

typedef enum {ESPADA, ORO, BASTO, COPA} Palo;
typedef struct {
    Palo palo;
    unsigned short int valor;
} Carta;


typedef Carta Mazo[CARTAS_MAZO];

void llenar(Mazo m) {
    for (Palo palo = ESPADA; palo <= COPA; palo++) {
        for (int valor = 1; valor <= VALORES; valor++) {
            m[palo * 12 + (valor - 1)] = (Carta) {palo, valor};
        }
    }
}

Carta azar(Mazo m) {
    Palo palo = rand() % 4;
    unsigned int valor = rand() % VALORES + 1;
    return (Carta) {palo, valor};
}

void ver_carta(Carta c) {
    printf("Palo: %d, Valor: %d\n", c.palo, c.valor);
}

// Ejercicio 14

typedef struct {
    char *nombre, *tel;
    unsigned short edad;
} Contacto;

Contacto crear_contacto() {
    printf("Inserte el nombre del contacto: ");
    char* nombre = get_new_line();
    printf("Inserte el telefono del contacto: ");
    char* tel = get_new_line();
    printf("Inserte la edad del contacto: ");
    unsigned edad = atoi(get_new_line());
    return (Contacto) {nombre, tel, edad};
}

void actualizar_edad(Contacto *c) {
    printf("Inserte la nueva edad: ");
    c->edad = atoi(get_new_line());
}

void liberar_contacto(Contacto *c) {
    free(c->nombre);
    free(c->tel);
}

void imprimir_contacto(Contacto* c) {
    printf("Nombre: %s, Telefono: %s, Edad: %u\n", c->nombre, c->tel, c->edad);
}

typedef struct {
    unsigned cant;
    Contacto* contactos;
} Agenda;

void alta_contacto(Agenda *a) {
    const unsigned bloque = 15; // Tamaño del bloque de contactos
    if (a->cant == 0) {
        a->contactos = malloc(sizeof(Contacto) * bloque);
        assert(a->contactos != NULL);
    }
    else if (a->cant % bloque == 0) {
        a->contactos = realloc(a->contactos, sizeof(Contacto) * (a->cant + bloque));
        assert(a->contactos != NULL);
    }
    a->contactos[a->cant++] = crear_contacto();
}

void modificar_edad(Agenda *a) {
    printf("Inserte el nombre del contacto a actualizar: ");
    char* nombre = get_new_line();
    for (int i = 0; i < a->cant; i++) {
        if (strcmp(a->contactos[i].nombre, nombre) == 0) {
            actualizar_edad(&a->contactos[i]);
            break;
        }
    }
    printf("No se ha encontrado el contacto buscado\n");
}

void imprimir_contactos(Agenda* a) {
    for (int i = 0; i < a->cant; i++)
        imprimir_contacto(&a->contactos[i]);
}

double promedio_edad(Agenda *a) {
    unsigned suma_edades = 0;
    for (int i = 0; i < a->cant; i++)
        suma_edades += a->contactos[i].edad;
    return suma_edades / ((double) a->cant);
}

void liberar_agenda(Agenda *a) {
    for (int i = 0; i < a->cant; i++)
        liberar_contacto(&a->contactos[i]);
    free(a->contactos);
}

int main() {
    srand(time(NULL));
    Agenda *a;
    a->cant = 0;
    alta_contacto(a);
    alta_contacto(a);
    alta_contacto(a);
    imprimir_contactos(a);
    modificar_edad(a);
    imprimir_contactos(a);
    printf("Promedio de edad en agenda: %lf\n", promedio_edad(a));
    liberar_agenda(a);
    return 0;
}