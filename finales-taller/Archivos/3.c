/*
 * Desarrolle un programa C que, sin crear archivos intermedios, procese  el archivo “3.bin”.
 * El procesamiento consiste en leer 5 enteros sin signo de 16 bits desde el archivo
 * y reemplazarlos por el promedio del grupo (es decir que el archivo se acortará).
 */

//Modo testeo escribe sobre otro archivo para no perder el del original

//El binario esta escrito en little endian
//x01x00x00x00 -> Nro 1

#include <stdio.h>
#include <stdint.h> //int16_T
#include <unistd.h> //ftruncate

#define FILENAME "3.bin"
//#define FILENAME_ "3_.bin" //Testeo
#define CANT_A_PROMEDIAR 5

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "rb");
    //FILE* fdW = fopen(FILENAME_, "w+b"); //Testeo
    FILE* fdW = fopen(FILENAME, "r+b"); //NO TESTEO
    
    int16_t acum;
    int16_t prom; //Hipotesis 16bits sin signo
    int16_t b[CANT_A_PROMEDIAR]; //Buffer de valores
    
    while (!feof(fdR)) {
        if (fread(b, sizeof(int16_t), CANT_A_PROMEDIAR, fdR) == CANT_A_PROMEDIAR) {
            acum = 0;
            for (int i = 0; i<CANT_A_PROMEDIAR; ++i)
                acum+=b[i];  
            prom = acum/CANT_A_PROMEDIAR;
            printf("%u %u %u %u %u | Promedio: %u\n", b[0], b[1], b[2], b[3], b[4], prom);
            fwrite(&prom, sizeof(int16_t), 1, fdW);
        }       
    }
    
    ftruncate(fileno(fdW), ftell(fdW)); //NO TESTEO
    fclose(fdR);
    fclose(fdW);
    return 0;
}
