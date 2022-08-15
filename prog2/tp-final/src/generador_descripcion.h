#ifndef GENERADOR_DESC_H
    #define GENERADOR_DESC_H

    #include <stdio.h> // fopen, fclose, fprintf, scanf, printf, fputs
    #include <time.h> // time
    #include <string.h> // strcmp, strlen, strcpy
    #include <stdlib.h> // malloc, realloc, free, rand, srand, atoi, exit
    #include <assert.h> // assert

    /*
    Estructura para guardar la cantidad y contenido de las
    lineas de un archivo
    */
    struct contenido_archivo {
        int cant_lineas;
        char** lineas;
    };

    /*
    Retorna un entero aleatorio entre el minimo y
    el maximo (ambos extremos estan incluidos)
    */
    int random_int(int min, int max);

    /*
    Retorna un puntero a un archivo, detiene la ejecucion
    del programa si este no puede ser abierto
    */
    FILE* abrir_archivo(const char nombre_archivo[], char* modo);

    /*
    Retorna un puntero a un array de memoria dinamica, donde
    los elementos son lineas del archivo seleccionadas de forma
    aleatoria sin repetir, y la cantidad es indicada por cant_palabras
    */
    char** seleccionar_palabras(int cant_palabras, struct contenido_archivo *archivo);

    /*
    Toma un puntero a una estructura contenido_archivo, recorre
    los elementos de lineas dentro de la estructura liberando la 
    memoria de cada una, y finalmente libera el array lineas.
    */
    void free_contenido_archivo(struct contenido_archivo *archivo);

    /*
    Toma un puntero a un archivo y retorna una estructura
    contenido_archivo que contiene la cantidad de lineas
    del archivo y un array con el contenido de estas
    */
    struct contenido_archivo leer_lineas(FILE* fp);

    /*
    Busca si str esta entre los primeros n elementos
    de strs_array
    */
    int string_en_array(char const *str, char** strs_array, int n);

    /*
    Escribe la descripcion del juego en el archivo out,
    con la informacion sobre la dimension, las palabras
    y la dificultad proveidas
    */
    void crear_descripcion_juego(char const *out, int dimension, int num_palabras, char** palabras, int dif);

#endif