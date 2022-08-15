#include "main.h"


int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        printf("Uso: %s <archivo_lemario> <tamaño> <cant_palabras> <complejidad>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    // Tomamos input del usuario para almacenar
    // el nombre del archivo de salida
    char out[50];
    printf("Ingrese el nombre del archivo de salida: ");
    scanf("%s", out);

    // Tamaño de la sopa de letras, cant de palabras y dificultad
    int dimension, num_palabras, dif; 

    // Convertimos los argumentos a enteros
    dimension = atoi(argv[2]);
    num_palabras = atoi(argv[3]);
    dif = atoi(argv[4]);

    // Chequeamos que los argumentos sean validos
    assert(dimension > 1);
    assert(num_palabras > 0);
    assert(0 <= dif && dif <= 3);

    // Abrimos el archivo correspondiente al lemario
    FILE *fp = abrir_archivo(argv[1], "r");

    // Alamcenamos en la estructura su numero de lineas
    // y el contenido de ellas
    struct contenido_archivo lemario = leer_lineas(fp);
    fclose(fp);
    
    // Seleccionamos la cantidad de palabras pedidas
    // de la estructura y escribimos el archivo descripcion
    char** palabras = seleccionar_palabras(num_palabras, &lemario);
    crear_descripcion_juego(out, dimension, num_palabras, palabras, dif);

    // Liberamos el array que contiene las palabras elegidas
    for (int i = 0; i < num_palabras; i++)
    {
        free(palabras[i]);
    }
    free(palabras);
    // Liberamos las lineas almacenadas en la estructura
    free_contenido_archivo(&lemario);

    return 0;
}
