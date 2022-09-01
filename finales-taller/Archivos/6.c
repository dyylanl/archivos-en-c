/*
 * Escribir un programa C que, sin crear archivos intermedios, procese el archivo “6.int”.
 * El procesamiento consiste en leer 3 enteros sin signo de 32 bits desde el archivo y escribir,
 * en su lugar, el promedio del grupo redondeado siempre para arriba (el archivo se acortará).
 */

//Compilar con libreria de math.h
//gcc 6.c -lm -o 6

//El binario esta escrito en little endian
//x01x00x00x00 -> Nro 1

#include <stdio.h>
#include <stdint.h>
#include <math.h> //ceil

#define FILENAME "6.int"
#define FILENAME_ "6_.int" //TESTEO
#define CANT_GRUPO 3

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "rb");
    FILE* fdW = fopen(FILENAME_, "w+b"); //TESTEO
    //FILE* fdW = fopen(FILENAME, "r+b");
    
    int32_t b[CANT_GRUPO]; //buffer de nros leidos por grupo
    int32_t acum, prom;
    while (!feof(fdR)) {
        if (fread(b, sizeof(int32_t), CANT_GRUPO, fdR) == CANT_GRUPO) {
            acum = 0;
            for (int i=0; i<CANT_GRUPO; ++i)
                acum+=b[i];
            prom = (int)ceil((double)(acum)/CANT_GRUPO); 
            printf("b0=%d   b1=%d   b2=%d\n", b[0], b[1], b[2]);
            printf("acum=%d   prom=%d\n", acum, prom);
            fwrite(&prom, sizeof(int32_t), 1, fdW);
        }
    }
    fclose(fdR);
    fclose(fdW);
    return 0;
}
