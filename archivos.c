#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> //strlen()
#include <sys/stat.h> // tamanio del archivo


// FORMAS DE ACCESO AL CONTENIDO DEL ARCHIVO //
/*

    printf(" ------- Leyendo con fgetc ----------\n");
    FILE *fd2 = fopen(argv[1], "r");
    int leido = fgetc(fd2);
    while (leido != EOF){
        printf("%c",leido);
        total += (int)leido;
        leido = fgetc(fd2);
    }
    fclose(fd2);


    printf(" ------- Leyendo con fscanf ----------\n");
    FILE *fd3 = fopen(argv[1], "r"); 
    char str1[10], str2[10], str3[10];
    int data;
    fscanf(fd3, "%s %s %s %d", str1,str2,str3,&data);
    while (!feof(fd3)) {
        printf("%s ",str1);
        printf("%s ",str2);
        printf("%s ",str3);
        printf("%i\n",data);
        fscanf(fd3, "%s %s %s %d", str1,str2,str3,&data);
    }
    fclose(fd3);


    printf(" ----------- Leyendo con getline ----------\n");
    FILE *fd4 = fopen(argv[1], "r");
    if (fd4 == NULL) {
        fprintf(stderr, "Ocurrio un error abriendo el archivo.\n"); // el stderr es un archivo que trae el sistema ¿sistema linux?
        return(EXIT_FAILURE);
    }
    char *line;
    size_t tam;
    while (getline(&line, &tam, fd4) != EOF) {
        printf("%s",line);
    }

    free(line);
    fclose(fd4);
    
    */


/*
* Programa C que procesa el archivo texto.txt sobre sí mismo. 
* El proceso consiste en triplicar las palabras que tengan todas las vocales.
* */
#define MULTIPLO 3
#define MAX 20

int analizar_palabra(char *palabra) {
    size_t len = strlen(palabra);
    int flag[5];
    flag[0] = flag[1] = flag[2] = flag[3] = flag[4] = 0; 
    for (int i=0; i<len; i++) {
        char caracter = palabra[i];
        switch (caracter) {
        case 'a': flag[0]= 1;break;
        case 'e': flag[1]= 1;break;
        case 'i': flag[2]= 1;break;
        case 'o': flag[3]= 1;break;
        case 'u': flag[4]= 1;break;
        }
    }
    return (flag[0] && flag[1] && flag[2] && flag[3] && flag[4]);
}

int main(int argc, char** argv) {

    FILE* fd_read = fopen(argv[1], "r");
    FILE* fd_write = fopen(argv[1], "r+");
    if (fd_read == NULL) {
        fprintf(stderr, "Error al abrir el archivo.\n");
        return(EXIT_FAILURE);
    }

    while (!feof(fd_read)) {
        char buffer[MAX];
		memset(buffer, 0, MAX);
		int indice = 0;
		int c = fgetc(fd_read);
        int vocales = 0;
        int palabra = 0;
		while (!feof(fd_read) && c != ' '/* && c != '\n'*/) {
			buffer[indice++] = c;
			c = fgetc(fd_read);
            palabra = 1;
		}
        if (palabra) {
            int res = analizar_palabra(buffer);
            if (res) {
                fprintf(fd_write, "%s ", buffer);
                fprintf(fd_write, "%s ", buffer);
                fprintf(fd_write, "%s ", buffer);
                printf("La palabra '%s' fue triplicada en el archivo '%s'.\n",buffer, argv[1]);
            } else {
                fprintf(fd_write, "%s ", buffer);
            }
        }
        
    }
    long off = ftell(fd_write);
	ftruncate(fileno(fd_write), off);

    fclose(fd_read);
    fclose(fd_write);
    return(EXIT_SUCCESS);
}