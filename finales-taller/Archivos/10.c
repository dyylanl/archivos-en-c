/*
 * Escriba una aplicación C que modifique el archivo a.bin sobre sí mismo, 
 * eliminado los bytes en posiciones múltiplo de 178. (el archivo se acortará).
 */

#include <stdio.h>
#include <unistd.h> //ftruncate
#define FILENAME "10.dat"
#define FILENAME_ "10_.dat"
#define POS_MULTIPLO 3 //178 (lo cambiamos, muy grande para testear)

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "rb");
    //FILE* fdW = fopen(FILENAME_, "w+b"); //TESTEO
    FILE* fdW = fopen(FILENAME, "r+b");
    unsigned char c;    
    while (fread(&c, sizeof(unsigned char), 1, fdR) == 1) {
        if ((ftell(fdR)-1)%POS_MULTIPLO != 0) //Resto 1 xq avance 1 en el fread
            fputc(c, fdW); //No es multipli
    }
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}