/*
 * Escriba una aplicación C que modifique el archivo 9.dat eliminando 
 * los bytes mayores a 0xC3. (el archivo se acortará).
 */

#include <stdio.h>
#include <unistd.h> //ftruncate
#define FILENAME "9.dat"
#define FILENAME_ "9_.dat" //TESTEO
#define BYTEREF 0xC3

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "rb");
    //FILE* fdW = fopen(FILENAME_, "w+b"); //TESTEO
    FILE* fdW = fopen(FILENAME, "r+b");
    
    unsigned char c;
    
    while(!feof(fdR)) {
        c = fgetc(fdR);
        if (c <= BYTEREF)
            fputc(c, fdW);
    }
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}