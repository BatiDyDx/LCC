#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void ej4() {
    int *punt, i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *(punt + 2) = 9; // x = {1, 2, 9, 4, 5}
    *(x + 3) = 7; // x = {1, 2, 9, 7, 5}
    punt[1] = 11; // x = {1, 11, 9, 7, 5}
    
    int res[] = {1, 11, 9, 7, 5};

    for(i = 0; i < 5; i++) {
        assert(*(punt + i) == res[i]);
    }
}

void ej6() {
    int v[4] = {2, 4, 5, 7}, a, *p;
    p = v + 2;
    p--;
    a = *p + *(p + 1) + *(v + 1) + p[2];
    assert(a == 20);
}

void suma_dos (int *x, int *y, int z) {
    *x = *x + 2;
    *y = *y + 5;
    z = z + 4;
}

void ej7 () {
    int x, y, z;
    x = 3;
    y = 10;
    z = 15;
    suma_dos(&x, &y, z);
    assert(x == 5);
    assert(y == 15);
    assert(z == 15);
}

int* fun0(int x) {
    return &x;
}

void ej9() {
    int *ptr = NULL;
    ptr = fun0(2);
    // Imprime 2, ya que ptr apunta a la direccion de x,
    // creada en fun0
    printf("%d\n", *ptr); 
    /*
    Luego de la primer llamada a printf, el espacio de 
    memoria de las variables locales y argumentos de fun0
    se libera, luego el valor de la direccion donde apunta ptr
    sera basura
    */
    printf("%d\n", *ptr);
}

void ej10() {
    char textoA[30] = "Agarrate Catalina";
    char textoB[30] = "El Cuarteto de Nos"; 
    char *p = textoA;
    char *q = textoB;
    printf ("textoA : %s\ntextoB : %s\n", textoA , textoB ) ;
    /*
    *p asume el valor de *q, luego se incrementan ambos y se
    repite, hasta que se encuentra el valor '\0', el cual detiene el while
    */
    while (*p++ = *q++);
    for ((p = textoA, q = textoB); *p != '\0'; (p++, q++)) {
        assert(*p == *q);
    }
}

int main() {
    return 0;
}
