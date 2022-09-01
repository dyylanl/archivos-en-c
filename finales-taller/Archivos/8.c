/*
 * Escribir un algoritmo ANSI C que, sin crear archivos intermedios 
 * altere el archivo 8.txt reemplazando la secuencia '//' por '*'.
 * Excepto si se encuentra entre parentesis.
 */

#include <stdio.h>
#include <unistd.h>
#define FILENAME "8.txt"
#define FILENAME_ "8_.txt" //Testeo

void busco1raBarra(FILE* fdR, FILE* fdW, char* ptrC, int* ptrContador);
void busco2daBarra(FILE* fdR, FILE* fdW, char* ptrC, int* ptrContador);

void busco2daBarra(FILE* fdR, FILE* fdW, char* ptrC, int* ptrContador) {
    if (*ptrC == EOF) {
        return;
    } else if ((*ptrC == '/') && (*ptrContador == 0)) {
        fputc('*', fdW);
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    } else if (*ptrC == ')') {
        fputc(')', fdW);
        if (*ptrContador > 0)
            *ptrContador-=1;
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    } else if (*ptrC == '(') {
        fputc('(', fdW);
        *ptrContador+=1;
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    } else {
        fputc('/', fdW);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    }
}

void busco1raBarra(FILE* fdR, FILE* fdW, char* ptrC, int* ptrContador) {
    if (*ptrC == EOF) {
        return;
    } else if ((*ptrC == '/') && (*ptrContador == 0)) {
        *ptrC = fgetc(fdR);
        busco2daBarra(fdR, fdW, ptrC, ptrContador);
    } else if ((*ptrC == ')')) {
        fputc(')', fdW);
        if (*ptrContador > 0)
            *ptrContador-=1;
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    } else if (*ptrC == '(') {
        fputc('(', fdW);
        *ptrContador+=1;
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    } else {
        fputc(*ptrC, fdW);
        *ptrC = fgetc(fdR);
        busco1raBarra(fdR, fdW, ptrC, ptrContador);
    }
}

int main(int argc, char**argv) {
    FILE* fdR = fopen(FILENAME, "r");
    //FILE* fdW = fopen(FILENAME_, "w+"); //Testeo
    FILE* fdW = fopen(FILENAME, "r+");
    
    char c;
    char* ptrC = &c;
    *ptrC = fgetc(fdR);
    int contador = 0;
    int* ptrContador = &contador;
    busco1raBarra(fdR, fdW, ptrC, ptrContador); 
    
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}
