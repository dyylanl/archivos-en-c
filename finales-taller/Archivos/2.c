/* 
 * Escribir un programa C que, sin crear archivos intermedios, procese el 
 * archivo “2.dat”. El procesamiento consiste en leer grupos de 
 * 2 enteros sin signo de 32 bits desde el archivo y escribir, en su lugar, 
 * la resta del grupo (es decir que el archivo se acortará).
 */

//El binario esta escrito en little endian
//x01x00x00x00 -> Nro 1

#include <stdio.h>
#include <stdint.h> //int32_t
#include <unistd.h> //ftruncate

#define FILENAME "2.dat"
//#define FILENAME_ "2_.dat" //Testeo

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(FILENAME,"rb"); //Lectura archivo binario
    //FILE* fdW = fopen(FILENAME_,"w+b"); //Testeo
    FILE* fdW = fopen(FILENAME,"r+b"); //Escritura archivo binario
    
    int32_t b[2]; //Buffer de valores
    int32_t resta;  //Hipotesis 32bits sin signo (no admite que buff[0]<buff[1])
    while (!feof(fdR)) {
        if (fread(b, sizeof(int32_t), 2, fdR) == 2) {
            resta = b[0]-b[1];
            printf("%u-%u = %u\n", b[0], b[1], resta);
            fwrite(&resta, sizeof(int32_t), 1, fdW);
        }
    }
    
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}
