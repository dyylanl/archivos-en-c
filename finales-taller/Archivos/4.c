/* 
 * Escriba un programa ANSI C que modifique el archivo datos.bin sobre si mismo.
 * El procesamiento consiste en leer 2 enteros de 32 bits y reemplazarlos con un
 * único entero que resulte de hacer la operación OR entre los nros leídos.
 */

//El binario esta escrito en little endian
//x01x00x00x00 -> Nro 1

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>

#define FILENAME "4.dat"
#define FILENAME_ "4_.dat" //Testeo

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(FILENAME,"rb"); //Lectura archivo binario
    //FILE* fdW = fopen(FILENAME_,"w+b"); //Testeo
    FILE* fdW = fopen(FILENAME,"r+b"); //Escritura archivo binario
    
    int32_t b[2]; //Buffer de valores
    int32_t res;  //Hipotesis 32bits sin signo (no admite que buff[0]<buff[1])
    while (!feof(fdR)) {
        if (fread(b, sizeof(int32_t), 2, fdR) == 2) {
            res = b[0] | b[1];
            printf("%u|%u = %u\n", b[0], b[1], res);
            fwrite(&res, sizeof(int32_t), 1, fdW);
        }
    }
    
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}
