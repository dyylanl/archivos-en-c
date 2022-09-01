/*
 * Escriba un programa C que tome 3 cadenas por línea de comandos: A, B y C;
 * e imprima la cadena A después de haber reemplazado todas las ocurrencias de B por C.
 * ej.: reemp.exe “El ejercicio está mal hecho” mal bien -----> El ejercicio está bien hecho
 */

//Compilo: >>> gcc 2.c -lm -o 2
//Ejecuto: >>> ./2 "Está mal hecho" mal bien

#include <stdio.h>
#include <string.h>
#define TAM_BUFFER 1000

int main(int argc, char** argv) {
    if (argc != 4) //Si no son 3 parametros salgo
        return 1;
    char* cadA = argv[1];
    char* cadB = argv[2];
    char* cadC = argv[3];
    char cad[TAM_BUFFER];
    int irA = 0;
    int irB = 0;
    int irC = 0;
    int iw = 0;
    printf("CadenaA: %s\n", cadA);
    printf("CadenaB: %s\n", cadB);
    printf("CadenaC: %s\n", cadC);
    
    while (irA < strlen(cadA)) {
        if (irB == strlen(cadB)) {  //Si hubo match con cadB..
            irB = 0;                //Reseteo indice de lectura en cadB
            iw -= strlen(cadB);     //Retrocedo indice para pisar lo escrito de cadB
            
            while (irC < strlen(cadC)) { //Escribo cadC
                cad[iw] = cadC[irC];
                iw++;
                irC++;
            }
            irC = 0;
        }
        
        if (cadA[irA] == cadB[irB]) //Trato de armar el match
            irB++;
        else
            irB = 0;
        
        cad[iw] = cadA[irA];        //Escribo y adelanto indices
        irA++;
        iw++;
    }
    cad[iw] = '\0';                 //Escribo caracter de fin de linea
    
    printf("Cadena : %s\n", cad);
    
    return 0;
}