/*
 * Escriba un programa C que reciba como parámetros 2 cadenas (A y B) e imprima por
 * stdout la cadena A sin las ocurrencias de B. No utilice ninguna función de librería.
 */

//Compilo: >>> gcc 1_.c -o 1_
//Ejecuto: >>> ./1_ AA___BB_-_CC ___

#include <stdio.h>
#include <string.h> //Solo use strlen() de libreria

int main(int argc, char* argv[]) {
    if (argc!=3) //Si no me pasan 2 parametros salgo
        return 1;
    char* cadA = argv[1];
    char* cadB = argv[2];
    printf("Cadena A: %s\n", cadA);
    printf("Cadena B: %s\n", cadB);
    int irA = 0;                    //Indice lectura de cadA
    int iwA = 0;                    //indice escritura de cadA
    int irB = 0;                    //Indice lectura de cadB
    while (irA < strlen(cadA)) {
        if (irB == strlen(cadB)) {  //Si hubo match con cadB..
            iwA -= strlen(cadB);    //Retrocedo indice de escritura para pisar cadB en cadA
            irB = 0;                //Reseteo indice de lectura B
        }
        if (cadA[irA] == cadB[irB]) //Si hay coincidencia de letra avanzo indice de lectura B
            irB++;
        else                        //Si falla el match con cadB reseteo el indice
            irB = 0;

        cadA[iwA] = cadA[irA];
        irA++;
        iwA++;
    }
    cadA[iwA] = '\0'; //Agrego el caracter de fin de linea
    printf("Cadena A: %s\n", cadA);
    return 0;
}
