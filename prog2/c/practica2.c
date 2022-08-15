#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SECRET_NUMBER 255

void cara_opuesta_dado(void) {
    int cara;
    char* cara_opuesta;
    printf("Inserte el numero del dado: ");
    scanf("%d", &cara);

    switch (cara)
    {
    case 1:
        cara_opuesta = "seis";
        break;
    case 2:
        cara_opuesta = "cinco";
        break;
    case 3:
        cara_opuesta = "cuatro";
        break;
    case 4:
        cara_opuesta = "tres";
        break;
    case 5:
        cara_opuesta = "dos";
        break;
    case 6:
        cara_opuesta = "uno";
        break;
    default:
        printf("Numero incorrecto\n");
        return;
    }

    printf("El opuesto de %d en el dado es: %s\n", cara, cara_opuesta);
}

double sumatoria(void) {
    // Calcula la sumatoria de (1/i), con 1 <= i <= 100
    double result = 0;
    for (int i = 1; i <= 100; i++) {
        result += (1. / i);
    }
    return result;
}

int adivinar_numero() {
    const int INTENTOS = 15;
    for (int i = INTENTOS; 0 < i; i--) {
        int guess = 0;
        printf("\nNumero de intentos %d\n", i);
        while (!(guess <= 500 && 1 <= guess)) {
            printf("Elija un entero en el rango [1, 500]: ");
            scanf("%d", &guess);
        }
        if (guess == SECRET_NUMBER) {
            return 1;
        } else if (guess < SECRET_NUMBER) {
            printf("El numero secreto es mayor\n");
        } else {
            printf("El numero secreto es menor\n");
        }
    }
    return 0;
}

void collatz_function() {
    int n, num_ops;
    printf("Inserte un entero positivo: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("ERROR");
        return;
    }
    printf("El valor inicial es %d\n", n);
    for (num_ops = 0; n != 1; num_ops++) {
        if ((n % 2) == 0) {
            n = n / 2;
        } else {
            n = (3 * n) + 1;
        }
        printf("El siguiente valor es %d\n", n);
    }
    printf("Numero de operaciones: %d\n", num_ops);
}

int indexof(int n, int a[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (a[i] == n) {
            return i;
        }
    }
    return -1;
}

int sumaArr(int n, int a[]) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += a[i];
    }
    return result;
}

int prodAlt(int n, int a[]) {
    int result = 1;
    for (int i = 0; i < (n/2); i++) {
        result *= a[2 * i];
    }
    return result;
}

/* 
char_in_string toma un caracter y una cadena de caracteres,
y retorna 0 si el caracter se encuentra en la cadena o 1 en caso contrario 
*/
int char_in_string(char c, char s[]) {
    int len = strlen(s);
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == c) {
            return 0;
        }
    }
    return 1;
}

int main() {
    //cara_opuesta_dado();
    //printf("El valor de la sumatoria es: %F\n", sumatoria());
    /*if (adivinar_numero()) {
        printf("Adivinaste!!\n");
    } else {
        printf("Mas suerte la proxima\n");
    }*/
    //collatz_function();

    /*
    int a[10] = {1,2,3,4,5,-1,6,3,6,10};
    printf("%d %d \n", indexof(-1, a), indexof(99, a));
    printf("%d\n", sumaArr(10, a));
    printf("%d\n", prodAlt(10, a));
    */
    assert(char_in_string('h', "hola") == 0);
    assert(char_in_string('c', "abdf") == 1);
}