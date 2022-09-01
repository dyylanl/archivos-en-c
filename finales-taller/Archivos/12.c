/*
 * Escriba un programa C que procese el archivo a.bin sobre sí mismo. El procesamiento consiste
 * en invertir el orden de los bytes del archivo en grupos de 3. (el archivo mantiene tamaño).
 * Ejemplo:
 * Archivo original:    abc def ghi ... xyz
 * Archivo salida:      cba fed ihg ... zyx       
 */

/* Hipotesis, el archivo tiene una cantidad de bytes multiplos de 3, 
 * y en caso de no ser asi lo que sobre se descartar por ser "corrupto"
 */

#include <stdio.h>
#define FILENAME "12.txt"
#define FILENAME_ "12_.txt" //TESTEO

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "r");
    //FILE* fdW = fopen(FILENAME_, "w+"); //TESTEO
    FILE* fdW = fopen(FILENAME, "r+");
    
    unsigned char c[3];
    while (fread(c, sizeof(unsigned char), 3, fdR) == 3) {
        printf("%c%c%c -> %c%c%c\n", c[0], c[1], c[2], c[2], c[1], c[0]);
        fwrite(&c[2], sizeof(unsigned char), 1, fdW);
        fwrite(&c[1], sizeof(unsigned char), 1, fdW);
        fwrite(&c[0], sizeof(unsigned char), 1, fdW);
    }
    
    fclose(fdR);
    fclose(fdW);
    return 0;
}