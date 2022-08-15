#include <assert.h>
#include <stdio.h>

#define BISIESTO 1
#define NO_BISIESTO 0

#define MAX(A, B) (A >= B ? A : B)
#define MAX3(A, B, C) (MAX(MAX(A, B), C))


void f1() {
    int a, b, c, d=6, e;
    a = b = 3;
    c = a*b+d;
    e = (c + 5) / 4-3;
    e+=5;
    assert(c == 15 && e == 7);
}

void f2() {
    int a, b, c, d=6, e;
    a = 3;
    b = a - d / 3; // b = 1
    a *= b;
    c = a + d / a - 3 / a * b; // c = 4
    e = c + 8 / 4-b; // e = 5
    e+=5; // e = 10
    assert(c == 4 && e == 10);
}

int año_bisiesto(int year) {
    if (year % 4 == 0) {
        if ((year % 400 == 0) || (year % 100 != 0)) {
            return BISIESTO;
        }
    }
    return NO_BISIESTO;
}

void imprimir_impares(int top) {
    int i = 1;
    while (i < top) {
        printf("%d\n", i);
        i += 2;
    }
}

void internados() {
    int n, ni = 0, no = 0; // Numero de pacientes, de internados y de operados
    int edad; // Edad de un paciente
    float indice; // Indice de un paciente
    float em = 0.0, emi = 0.0, emo = 0.0; // Edad media, edad media de ingresados y edad media de operados

    // Definimos el minimo de los indices para decidir si el paciente será internado,
    // operado, o ninguno
    const float MIN_INTERNADO = 0.6, MIN_OPERADO = 0.9;

    printf("Ingrese el numero de pacientes: ");
    scanf("%d", &n);

    int i = 0;
    while (i < n) {
        printf("Ingrese edad e indice del paciente: ");
        scanf("%d%f", &edad, &indice);
        
        em += edad;
        if (indice >= MIN_INTERNADO) {
            if (indice >= MIN_OPERADO) {
                emo += indice;
                no++;
            }
            emi += indice;
            ni++;
        }

        i++;
    }

    if (n > 0) {
        em /= n;
    }
    if (ni > 0) {
        emi /= ni;
    }
    if (no > 0) {
        emo /= no;
    }
    printf("Edad media de pacientes: %.2f\n", em);
    printf("Edad media de pacientes internados: %.2f\n", emi);
    printf("Edad media de pacientes operados: %.2f\n", emo);
}

int esRectangulo(int a, int b, int c) {
    int max = MAX3(a, b, c);
    if ((max * max) == (a*a + b*b + c*c - max*max)) {
        return 1;
    } else {
        return 0;
    }
}


unsigned int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main() {
    f1();
    f2();

    // imprimir_impares(5);

    assert(año_bisiesto(2500) == NO_BISIESTO);
    assert(año_bisiesto(2400) == BISIESTO);
    assert(año_bisiesto(1992) == BISIESTO);

    // internados();
    assert(esRectangulo(3,5,4) == 1);
    assert(esRectangulo(5,13,12) == 1);
    assert(esRectangulo(7,3,5) == 0);
}