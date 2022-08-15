#include "generador_descripcion.h"


FILE* abrir_archivo(const char nombre_archivo[], char *modo)
{
    FILE *fp = fopen(nombre_archivo, modo);
    // Si no se pudo abrir el archivo, imprimimos un mensaje
    // avisandolo y terminamos el programa
    if (fp == NULL)
    {
        printf("No se puede abrir el archivo %s\n", nombre_archivo);
        exit(1);
    }
    return fp;
}


void free_contenido_archivo(struct contenido_archivo *archivo)
{
    // Liberamos cada uno de los elementos del array lineas
    // junto con el array lineas
    for (int i = 0; i < archivo->cant_lineas; free(archivo->lineas[i++]));
    free(archivo->lineas);
}


struct contenido_archivo leer_lineas(FILE* fp)
{
    /* 
    max_lineas es en principio el numero de
    lineas a leer del archivo. Si este tuviese mas,
    entonces ampliamos max_lineas, alojamos mas memoria
    dinamica, y seguimos hasta finalizar el archivo
    */
    int max_lineas = 50000;
    
    // LARGO_MAX_LINEA será el largo maximo que aceptaremos para
    // una palabra en el vector de palabras
    const int LARGO_MAXIMO_PALABRAS = 30;

    struct contenido_archivo archivo;
    archivo.lineas = malloc(sizeof(char*) * max_lineas);

    // Pedimos memoria para almacenar linea, la cual servira de buffer
    char* linea = malloc(sizeof(char) * (LARGO_MAXIMO_PALABRAS + 1));

    for (archivo.cant_lineas = 0; fscanf(fp, "%s\n", linea) != EOF; archivo.cant_lineas++)
    {
        if (archivo.cant_lineas == max_lineas)
        {
            /*
                Si la cantidad de lineas es mayor que max_lineas
                duplicamos su valor y pedimos memoria para el nuevo
                numero de lineas
            */
            max_lineas = max_lineas * 2;
            archivo.lineas = realloc(archivo.lineas, sizeof(char*) * max_lineas);
            assert(archivo.lineas != NULL);
        }
        // Pedimos memoria para almacenar la linea
        archivo.lineas[archivo.cant_lineas] = malloc(sizeof(char) * (strlen(linea) + 1));
        // Guardamos la linea numero i en la posicion i del array
        strcpy(archivo.lineas[archivo.cant_lineas], linea);
    }
    // Liberamos el buffer linea
    free(linea);
    return archivo;
}


int random_int(int min, int max)
{   
    // Cantidad de enteros en el intervalo [min, max]
    int rango = max - min + 1;

    // Tomamos un numero en este rango
    int n = (rand() % rango) + min;
    return n;
}


void crear_descripcion_juego(char const *out, int dimension, int num_palabras, char** palabras, int dif)
{
    FILE *fpo = abrir_archivo(out, "w"); // Puntero al archivo salida
    // Escribimos la dimension al archivo de salida
    fprintf(fpo, "DIMENSION\n%d\n", dimension);
    fputs("PALABRAS\n", fpo);
    // Escribimos todas las palabras seleccionadas
    for (int i = 0; i < num_palabras; i++)
    {
        fprintf(fpo, "%s\n", palabras[i]);
    }
    // Escribimos la complejidad
    fprintf(fpo, "COMPLEJIDAD\n%d", dif);

    fclose(fpo);
}


int string_en_array(char const *str, char** strs_array, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Comparamos str con los primeros n elementos
        // del array
        // Si se encuentra, retorna 1
        if (!strcmp(str, strs_array[i])) return 1;
    }
    // Si no se encuentra, retorna 0
    return 0;
}


char** seleccionar_palabras(int cant_palabras, struct contenido_archivo *archivo)
{
    int n;
    int palabras_elegidas = 0;
    char** palabras = malloc(sizeof(char*) * cant_palabras);
    
    // Chequeamos que no se esten pidiendo mas palabras
    // de las que hay en el archivo
    assert(archivo->cant_lineas >= cant_palabras);

    // Repetimos hasta haber elegido tantas palabras como requeridas
    while (palabras_elegidas < cant_palabras)
    {
        // Elejimos un numero aleatorio entre el 0 y el numero
        // de lineas menos uno
        n = random_int(0, archivo->cant_lineas - 1);
        
        // Si la palabra en la linea n ya esta en el array, continuamos
        // con la proxima iteracion hasta encontrar una que no lo este
        if (string_en_array(archivo->lineas[n], palabras, palabras_elegidas))
        {
            continue;
        }
        // Pedimos memoria dinamica para guardar la palabra
        palabras[palabras_elegidas] = malloc(sizeof(char) * (strlen(archivo->lineas[n]) + 1)); 
        // Guardamos la palabra de la linea n en el array palabras y aumentamos
        // en uno la cantidad de palabras elegidas
        strcpy(palabras[palabras_elegidas], archivo->lineas[n]);
        palabras_elegidas++;
    }
    return palabras;
}
