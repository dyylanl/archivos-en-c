/*
 * Escribir un programa ISO C que, sin crear archivos intermedios, altere el 
 * archivo “7.dat” reemplazando todas las secuencias de 3 bytes 0x34 0x43 0x44
 * por la secuencia de 2 bytes 0x34 0x43. Cabe destacar que el programa debe
 * reprocesar el reemplazo efectuado.
 * Ejemplo: 0x34 0x43 0x44 0x44 ---> 0x34 0x43 0x44 ---> 0x34 0x43
 */

#include <stdio.h>
#include <stdbool.h>
#define FILENAME "7.dat"
#define FILENAME_ "7_.dat"

void buscarx44(FILE* fdR, FILE* fdW, char* ptrC, bool reproc);
void buscarx43(FILE* fdR, FILE* fdW, char* ptrC);
void buscarx34(FILE* fdR, FILE* fdW, char* ptrC);

void buscarx44(FILE* fdR, FILE* fdW, char* ptrC, bool reproc) {
    if (*ptrC == EOF) {
        if (reproc == true) {
            fputc(0x34, fdW);
            fputc(0x43, fdW);
        } 
        return;  
    } else if (*ptrC == 0x44) {
        *ptrC = fgetc(fdR);
        buscarx44(fdR, fdW, ptrC, true);
    } else {
        fputc(0x34, fdW);
        fputc(0x43, fdW);
        buscarx34(fdR, fdW, ptrC);
    }
}

void buscarx43(FILE* fdR, FILE* fdW, char* ptrC) {
    if (*ptrC == EOF)
        return;
    else if (*ptrC == 0x43) {
        *ptrC = fgetc(fdR);
        buscarx44(fdR, fdW, ptrC, false);
    }
    else {
        fputc(0x34, fdW);
        buscarx34(fdR, fdW, ptrC);
    }
}

void buscarx34(FILE* fdR, FILE* fdW, char* ptrC) {
    if (*ptrC == EOF)
        return;
    else if (*ptrC == 0x34) {
        *ptrC = fgetc(fdR);
        buscarx43(fdR, fdW, ptrC);
    }
    else {
        fputc(*ptrC, fdW);
        *ptrC = fgetC(fdR);
        buscarx34(fdR, fdW, ptrC);
    }
}

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(FILENAME,"rb"); //Lectura archivo binario
    //FILE* fdW = fopen(FILENAME,"r+b"); //Escritura archivo binario
    FILE* fdW = fopen(FILENAME_,"w+b"); //Escritura archivo binario
    
    char c;
    char* ptrC = &c;
    *ptrC = fgetc(fdR);
    buscarx34(fdR, fdW, ptrC);
    
    fclose(fdR);
    fclose(fdW);
    return 0;
}
