/*
 *     Escribir un algoritmo que procese el archivo x.dat
 *     invirtiendo los bytes xy por yx
 */

#include <stdio.h>
#define filename "1.dat"

void buscarY(FILE* fdR, FILE* fdW, char c);
void buscarX(FILE* fdR, FILE* fdW, char c);

void buscarY(FILE* fdR, FILE* fdW, char c) {
    if (c == EOF)
        return;
    else if (c == 'y') {
        fputc('y', fdW);
        fputc('x', fdW);
        c = fgetc(fdR);
        buscarX(fdR, fdW, c);
    } else {
        fseek(fdW, 1, SEEK_CUR);
        buscarX(fdR, fdW, c);
    }
}

void buscarX(FILE* fdR, FILE* fdW, char c) {
    if (c == EOF)
        return;
    else if (c == 'x') {
        c = fgetc(fdR);    
        buscarY(fdR, fdW, c);
    } else {
        fseek(fdW, 1, SEEK_CUR);
        c = fgetc(fdR);
        buscarX(fdR, fdW, c);
    }
}

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(filename,"rb"); //Lectura archivo binario
    FILE* fdW = fopen(filename,"r+b"); //Escritura archivo binario
    fseek(fdR, 0L, SEEK_SET);
    fseek(fdW, 0L, SEEK_SET); 
    
    char c = fgetc(fdR);
    buscarX(fdR, fdW, c);    
    
    fclose(fdR);
    fclose(fdW);
    return 0;
}