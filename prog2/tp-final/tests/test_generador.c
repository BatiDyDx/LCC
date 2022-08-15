#include "../src/generador_descripcion.h"


void test_random_int(void)
{
    int x, y;
    x = random_int(0, 5);
    y = random_int(-3, 3);
    assert(0 <= x && x <= 5);
    assert(-3 <= y && y <= 3);
}


void test_string_en_array(void)
{
    char* strings[5] = {"diputado", "control", "sombrilla", "reloj", "raqueta"};
    assert(string_en_array("reloj", strings, 5));
    assert(!string_en_array("reloj", strings, 3));
    assert(!string_en_array("futbol", strings, 5));
}


void test_leer_lineas(void)
{
    FILE *fp = abrir_archivo("tests/lemario_prueba.txt", "r");
    assert(fp != NULL);
    struct contenido_archivo lemario = leer_lineas(fp);
    assert(lemario.cant_lineas == 8);
    assert(strcmp(lemario.lineas[3], "desaplomar") == 0);
    assert(strcmp(lemario.lineas[7], "obturador") == 0);
    fclose(fp);
    free_contenido_archivo(&lemario);
}


void test_seleccionar_palabras(void)
{
    FILE *puntero_descripcion = abrir_archivo("tests/descripcion_prueba.txt", "r");
    struct contenido_archivo desc = leer_lineas(puntero_descripcion);

    assert(desc.cant_lineas == 10);
    assert(strcmp(desc.lineas[0], "DIMENSION") == 0);
    assert(strcmp(desc.lineas[3], "meteorizacion") == 0);
    assert(strcmp(desc.lineas[9], "2") == 0);

    fclose(puntero_descripcion);
    free_contenido_archivo(&desc);
}


int main(void)
{
    test_random_int();
    test_string_en_array();
    test_leer_lineas();
    test_seleccionar_palabras();
    printf("Todas las pruebas pasan\n");
    return 0;
}