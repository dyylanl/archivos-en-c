/*
 * Escriba un programa C que reciba como parámetros 2 cadenas (A y B) e imprima por
 * stdout la cadena A sin las ocurrencias de B. No utilice ninguna función de librería.
 */

//Compilo: >>> gcc 1.c -o 1
//Ejecuto: >>> ./1 AA__BB__CC__DD __

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc!=3) //Si no me pasan 2 parametros salgo
        return 1;
    
    char* cadA = argv[1];
    char* cadB = argv[2];

    char* cad = (char*)malloc(strlen(cadA)+1);      //Sumo 1 por el caracter de fin de linea '\0'
    char* cadA_ = cadA;                             //puntero auxiliar de donde leo
    char* cad_ = cad;                               //puntero auxiliar en donde escribo
    
    char* inicioOcurr = strstr(cadA_, cadB);        //Capturo 1er ocurrencia  
    while (inicioOcurr != NULL) {                   //Corto cuando no hay más ocurrencias.
        while (cadA_<inicioOcurr) {                 //Copio hasta la ocurrencia
            strncpy(cad_, cadA_, 1);
            ++cad_;
            ++cadA_;
        }
        cadA_ += strlen(cadB);                      //Salteo la ocurrencia
        inicioOcurr = strstr(cadA_, cadB);          //Calculo nueva ocurrencia
    }
    while (cadA_ < cadA+strlen(cadA)+1) {           //Copio lo que me falte copiar de cadA;
        strncpy(cad_, cadA_, 1);
        ++cad_;
        ++cadA_;
    }

    printf("Cadena A: %s\n", cadA);
    printf("Cadena B: %s\n", cadB);
    printf("Salida  : %s\n", cad);
    free(cad);
    return 0;
}