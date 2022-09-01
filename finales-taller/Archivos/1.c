/*
 * Escribir un algoritmo que procese el archivo 1.dat
 * invirtiendo los bytes xy por yx
 */

#include <stdio.h>
#define FILENAME "1.dat"

void buscarY(FILE* fdR, FILE* fdW, char* ptrC);
void buscarX(FILE* fdR, FILE* fdW, char* ptrC);

void buscarY(FILE* fdR, FILE* fdW, char* ptrC) {
    if (*ptrC == EOF)
        return;
    else if (*ptrC == 'y') {
        fputc('y', fdW);
        fputc('x', fdW);
        *ptrC = fgetc(fdR);  //Capturo char y avanza 1 en fdR
        buscarX(fdR, fdW, ptrC);
    } else {
        fputc('x', fdW);
        //fseek(fdW, 1, SEEK_CUR); //Avanzo en 1 el fdW
        buscarX(fdR, fdW, ptrC);
    }
}

void buscarX(FILE* fdR, FILE* fdW, char* ptrC) {
    if (*ptrC == EOF)
        return;
    else if (*ptrC == 'x') {
        *ptrC = fgetc(fdR);  //Capturo char y avanza 1 en fdR
        buscarY(fdR, fdW, ptrC);
    } else {
        fputc(*ptrC, fdW);
        //fseek(fdW, 1, SEEK_CUR); //Avanzo en 1 el fdW
        *ptrC = fgetc(fdR);  //Capturo char y avanza 1 en fdR
        buscarX(fdR, fdW, ptrC);
    }
}

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(FILENAME,"rb"); //Lectura archivo binario
    FILE* fdW = fopen(FILENAME,"r+b"); //Escritura archivo binario
    
    char c;
    char* ptrC = &c;
    *ptrC = fgetc(fdR);
    buscarX(fdR, fdW, ptrC);
    
    fclose(fdR);
    fclose(fdW);
    return 0;
}
