#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


/* Punteros */
// Definir una funcion swap que dadas dos variables enteras intercambie el contenido de las mismas.
void swap(int *x, int *y) {
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

// Definir versiones de las siguientes funciones sobre cadenas usando punteros:
// i) int strlen(char *c), que determina el largo de una cadena.
// ii) void strcpy(char *s, char *t), que copia la cadena t a s.

int strlen2(char *c) {
    int len;
    for (len = 0; c[len] != '\0'; len++);
    return len;
}

void strcpy2(char *s, char *t) {
    while ((*s++ = *t++));
    return ;
}
/* Estructuras */

// Ejercicios 3 y 4
typedef struct {
    float x, y;
} Punto;

typedef struct {
    /* 
    Un rectangulo esta determinado por dos puntos,
    el punto superior izquierdo y el punto inferior derecho
    */
    Punto *psi, *pid; 
} Rectangulo;

int inRect(Rectangulo *rec, Punto *p) {
    int inside = 0;
    if (rec->psi->x < p->x && p->x < rec->pid->x) {
        if (rec->pid->y < p->y && p->y < rec->psi->y) (inside = 1);
    }
    return inside;
}


// Ejercicios 5 y 6

#define MAX_CONTACTS 100

typedef struct {
    char *nombre, *telefono;
} Contacto;

struct Agenda {
    int numContactos;
    Contacto contactos[MAX_CONTACTS];
};

Contacto crearContacto() {
    char nombre[20], telefono[20];
    Contacto c;
    printf("Ingrese su nombre: ");
    scanf("%s", nombre);
    printf("Ingrese su numero de telefono: ");
    scanf("%s", telefono);

    c.nombre = malloc(sizeof(char) * (strlen2(nombre) + 1));
    c.telefono = malloc(sizeof(char) * (strlen2(telefono) + 1));
    strcpy2(c.nombre, nombre);
    strcpy2(c.telefono, telefono);
    return c;
}

void printContacto(Contacto *c) {
    if (!(c == NULL)){
        printf("Contacto: Nombre = %10s\tTelefono = %13s\n", c->nombre, c->telefono);
    } else {
        printf("El contacto esta vacio\n");
    }
}

void freeContact(Contacto *c) {
    free(c->nombre);
    free(c->telefono);
}


int agregarContacto(Contacto *c, struct Agenda *s) {
    if (s->numContactos == MAX_CONTACTS) {
        return 0;
    }
    s->contactos[s->numContactos] = *c;
    s->numContactos++;
    return 1;
}

void printAgenda(struct Agenda *s) {
    printf("Agenda: Numero de contactos = %d\n", s->numContactos);
    printf("Contactos: \n");
    for (int i = 0; i < s->numContactos; i++) {
        printContacto(&(s->contactos[i]));
    }
}
/* Archivos */

void filecopy(FILE *ifp, FILE *ofp) {
    char c;
    while ((c = fgetc(ifp)) != EOF) {
        fputc(c, ofp);
    }
}

#define MAX_CHARS_LINE 255

int countLines(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { perror("File Error"); exit(1);}

    int lines_number = 1;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') lines_number++;
    }
    fclose(fp);
    return lines_number;
}

char** readLines(char *filename, int nlines) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) { perror("File Error"); exit(1);}
    int len;
    char **lines = malloc(nlines * sizeof(char*));
    char *line = malloc(sizeof(char) * (MAX_CHARS_LINE+1));
    if (line == NULL) {perror("Malloc error in line pointer"); exit(1);}

    for (int i = 0; i < nlines; i++) {
        fgets(line, MAX_CHARS_LINE+1, fp);
        if (line == NULL) {
            perror("Error in fgets");
            exit(1);
        }
        len = strlen(line);
        lines[i] = malloc(sizeof(char) * (len+1));
        if (lines[i] == NULL) {
            perror("Malloc error in lines[i]");
            exit(1);
        }
        strcpy(lines[i], line);
    }
    free(line);
    fclose(fp);
    return lines;
}

int main() {
    /*
    char s[18] = "1,2,3 probando...", t[19] = "Aguante messi loco";
    char *from = "Probando probando";
    char *to = malloc(strlen2(from) + 1);
    assert(strlen2("Hello World") == 11);
    strcpy2(s, t);
    for (int i = 0; s[i] != '\0'; i++) {
        assert(s[i] == t[i]);
    }
    strcpy2(to, from);
    for (int i = 0; to[i] != '\0'; i++) {
        assert(to[i] == from[i]);
    }
    free(to)
    */
    /*
    Punto p, psi, pid;
    Rectangulo rec;
    p.x = 8.0;
    psi.x = 2.5;
    pid.x = 7.5;
    p.y = 3.0;
    pid.y = 2.0;
    psi.y = 4.0;
    rec.pid = &pid;
    rec.psi = &psi;
    assert(inRect(&rec, &p) == 0);
    */
    
    /*
    Contacto bati = crearContacto(), pauli = crearContacto();
    struct Agenda a;

    a.numContactos = 0;
    agregarContacto(&bati, &a);
    agregarContacto(&pauli, &a);
    
    printAgenda(&a);

    freeContact(&pauli);
    freeContact(&bati);
    */
    /*
    FILE *ifp = fopen("test_input.txt", "r");
    FILE *ofp = fopen("test_output.txt", "w");

    filecopy(ifp, ofp);

    assert(fclose(ifp) == 0);
    assert(fclose(ofp) == 0);
    */
    char *filename = "test_input.txt";
    int nlines = countLines(filename);
    char **lines = readLines(filename, nlines);
    if (lines == NULL) {
        perror("Error in main");
        exit(1);
    }
    for (int i = 0; i < nlines; i++) {
        printf("Line number %d:\t%s\n", i, lines[i]);
        free(lines[i]);
    }
    free(lines);
    return 0;
}