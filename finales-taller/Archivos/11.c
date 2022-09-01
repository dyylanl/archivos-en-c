/*
 * Escribir un programa ISO C que lea el archivo "11.txt" e invierta sus 
 * caracteres sin utilizar archivos intermedios. (el archivo mantiene tamaño).
 */

#include <stdio.h>
#define FILENAME "11.txt"

int main(int argc, char** argv) {
    FILE* fd1 = fopen(FILENAME, "r+");
    FILE* fd2 = fopen(FILENAME, "r+");
    unsigned char c1, c2;
    
    fseek(fd1, 0L, SEEK_SET); //Posiciono fd1 en primer caracter
    fseek(fd2, -1, SEEK_END); //Posiciono fd2 en ultimo caracter
    while (ftell(fd1)<ftell(fd2)) { //Mientras que no se crucen los punteros hacer SWAP
        c1 = fgetc(fd1); //fd1 Avanza 1
        c2 = fgetc(fd2); //fd2 Avanza 1
        
        fseek(fd1, -1, SEEK_CUR); //Como avanzó 1 retrocedo 1 antes de escribir
        fputc(c2, fd1); //fd1 Avanza 1
        fseek(fd2, -1, SEEK_CUR); //Como avanzó 1 retrocedo 1 antes de escribir
        fputc(c1, fd2); //fd2 Avanza 1
        
        //fd1 Ya avanzó 1 como queremos
        fseek(fd2, -2, SEEK_CUR); //Como fd2 avanzó 1 retrocedo 2
    }    
    
    fclose(fd1);
    fclose(fd2);
    return 0;
}