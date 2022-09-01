/*
 * Escribir un programa ANSI C que, sin crear archivos intermedios, procese el
 * archivo “nros.bin”. El procesamiento consiste en leer 2 enteros con signo 
 * de 32 bits desde el archivo y escribir, en su lugar, el diferencia en valor 
 * absoluto (sin signo), la suma y el número resultante de hacer OR a nivel bits 
 * entre ambos números (es decir que el archivo se agrandará).
 */

//Resolución no válida ya que el fdW avanza más rapido que el fdR (porque agrandamos archivo)

#include <stdio.h>
#include <stdint.h>
#include <unistd.h> //ftruncate
#include <stdbool.h>

#define FILENAME "5.dat"
//#define FILENAME_ "5_.dat" //TESTEO

void procesar(FILE* fdR, FILE* fdW, bool escribir, int* ptrOffset, int* ptrOSize) {
    int32_t b[2]; //Buffer
    int32_t abs, sum, intOR;

    while (!feof(fdR)) {
        if (fread(b, sizeof(int32_t), 2, fdR) == 2) {
            if (escribir == false) { //Pasada para calcular tamaño final del archivo
                *ptrOSize+=2;
                *ptrOffset+=1; //Cantidad de elementos que se expande
            } else { //Pasada para escribir
                if (b[0]>b[1])
                    abs = b[0]-b[1];
                else
                    abs = b[1]-b[0];
                sum = b[0]+b[1];
                intOR = b[0] | b[1];
                printf("b0=%d b1=%d\n", b[0], b[1]);
                printf("abs = %d\n", abs);
                printf("sum = %d\n", sum);
                printf("intOR = %d\n",intOR);
                fwrite(&abs, sizeof(int32_t), 1, fdW);
                fwrite(&sum, sizeof(int32_t), 1, fdW);
                fwrite(&intOR, sizeof(int32_t), 1, fdW);
            }
        }
    }
}

int main(int argc, char** argv) {
    int offset = 0; //Indica cuantos bytes se agranda el archivo
    int* ptrOffset = &offset;
    int oSize = 0; //Tamaño original (no corrupto)
    int* ptrOSize = &oSize;

    //1er PASADA
    FILE* fdR = fopen(FILENAME, "rb");
    //FILE* fdW = fopen(FILENAME_, "w+b"); //TESTEO
    FILE* fdW = fopen(FILENAME, "r+b");

    procesar(fdR, fdW, false, ptrOffset, ptrOSize); //Calculo offset y tamaño original del archivo
    ftruncate(fileno(fdW), sizeof(int32_t)*(*ptrOffset + *ptrOSize)); //Expando el archivo
    //Desplazo en offset el contenido del archivo
    for (int i=*ptrOSize-1; i>=0; --i) { //Voy de atras para adelante, i es el nro de elemento a leer en el archivo
        int32_t buff;
        fseek(fdR, i*sizeof(int32_t), SEEK_SET); //Posiciono fdR en el elemento nro i
        fread(&buff, sizeof(int32_t), 1, fdR); //Leo el elemento nro i en el archivo
        fseek(fdW, (i+*ptrOffset)*sizeof(int32_t), SEEK_SET); //Posiciono fdW en el elemento nro i+offset
        fwrite(&buff, sizeof(int32_t), 1, fdW); //Escribo lo leido en la nueva posicion
    }
    //Cierro el archivo para guardar el desplazamiento del contenido
    fclose(fdR);
    fclose(fdW);

    //2da PASADA
    fdR = fopen(FILENAME, "rb");
    fseek(fdR, *ptrOffset*sizeof(int32_t), SEEK_SET); //Ubico el fdR en el offset para empezar a leer
    fdW = fopen(FILENAME, "r+b");
    procesar(fdR, fdW, true, ptrOffset, ptrOSize);
    fclose(fdR);
    fclose(fdW);

    return 0;
}
