/*
 * Escribir un programa ANSI C que, sin crear archivos intermedios, procese el
 * archivo “nros.bin”. El procesamiento consiste en leer 2 enteros con signo 
 * de 32 bits desde el archivo y escribir, en su lugar, el diferencia en valor 
 * absoluto (sin signo), la suma y el número resultante de hacer OR a nivel bits 
 * entre ambos números (es decir que el archivo se agrandará).
 */

//El binario esta escrito en little endian
//x01x00x00x00 -> Nro 1

//Resolución no válida ya que el fdW avanza más rapido que el fdR (porque agrandamos archivo), ver 5_.c

#include <stdio.h>
#include <stdint.h> //int32_t
#include <unistd.h> //ftruncate

#define FILENAME "5.dat"
//#define FILENAME_ "5_.dat" //TESTEO

int main(int argc, char** argv) {
    FILE* fdR = fopen(FILENAME, "rb");
    //FILE* fdW = fopen(FILENAME_, "w+b"); //TESTEO
    FILE* fdW = fopen(FILENAME, "r+b");
    
    int32_t b[2]; //Buffer
    int32_t abs, sum, intOR;
    
    while (!feof(fdR)) {
        if (fread(b, sizeof(int32_t), 2, fdR) == 2) {
            if (b[0]>b[1])
                abs = b[0]-b[1];
            else
                abs = b[1]-b[0];
            sum = b[0]+b[1];
            intOR = b[0] | b[1];
            printf("b0=%d b1=%d\n", b[0], b[1]);
            printf("abs = %d\n", abs);
            printf("sum = %d\n", sum);
            printf("intOR = %d\n", intOR);
            fwrite(&abs, sizeof(int32_t), 1, fdW);
            fwrite(&sum, sizeof(int32_t), 1, fdW);
            fwrite(&intOR, sizeof(int32_t), 1, fdW);
        }
    }
    
    //ftruncate(fileno(fdW), ftell(fdW)); //Como agrandamos no es necesario
    fclose(fdR);
    fclose(fdW);
    return 0;
}
