// Lectura del archivo
/*
FILE* fd_read = fopen(argv[1], "r");
    if (fd_read == NULL) {
        fprintf(stderr, "Error abriendo el archivo.\n");
        return(EXIT_FAILURE);
    }

    while (!feof(fd_read)) {
        char buffer[MAX_LEN];
        memset(buffer, 0, MAX_LEN);
        int indice = 0;
        int c = fgetc(fd_read);
        int palabra = 0;
        while (!feof(fd_read) && c != ' ' && c != '\n') {
            buffer[indice++] = c;
            c = fgetc(fd_read);
            palabra = 1;
        }
        if (palabra) {
            printf("%s\n",buffer);
        }
    }

    fclose(fd_read);
*/


/*
    Este programa lo que hace es procesar un archivo
    y por cada * que encuentre la reemplazara por //
    si el * esta dentro de un parentesis de debe ignorar el reemplazo
*/

#include <stdio.h> // printf
#include <stdlib.h> // macros de C
#include <string.h> // memset()
#include <assert.h> // check del rdptr > wrptr
#include <sys/stat.h> // tamanio del archivo

#define MAX_LEN 30 // tamanio maximo de la linea a leer

int main(int argc, char** argv) {

    
    FILE* fd_read = fopen(argv[1], "rt");
    FILE* fd_write = fopen(argv[2], "r+"); // asi no lo hago 20 veces
    if (fd_read == NULL || fd_write == NULL) {
        fprintf(stderr, "Error abriendo el archivo %s.\n",argv[1]);
        return(EXIT_FAILURE);
    }

    int parentesis = 0;
    int reemplazar = 0;
    char reemplazo = '/';
    char c = fgetc(fd_read);
    while (!feof(fd_read)) {
        if (c == '(') {
            parentesis = 1;
        }
        else if (c == ')') {
            parentesis = 0;
        }
        if (!parentesis) {
            // mientras lea * reemplazo por // en fd_write
            while (c == '*') {
                fprintf(fd_write, "%c", reemplazo);
                char aux = fgetc(fd_read);
                fprintf(fd_write, "%c", reemplazo);
                c = aux;
            }
        }
        fprintf(fd_write, "%c", c);
        c = fgetc(fd_read);
    }
        
/*
        else if (c == '*' && !parentesis) {
            reemplazar = 1;
        }
        char aux;
        if (reemplazar) {
            reemplazar = 0;
            fprintf(fd_write, "%c", reemplazo); // pongo /
            aux = fgetc(fd_read);
            fprintf(fd_write, "%c", reemplazo); // pongo // aca piso la siguiente informacion => antes de pisarla me la guardo
            fprintf(fd_write,"%c",aux);         // pongo lo que seguia despues del *
        } else {
            fprintf(fd_write, "%c",c);
        }
        c = fgetc(fd_read);
    }
*/
    fclose(fd_read);
    fclose(fd_write);
    return(EXIT_SUCCESS);
}