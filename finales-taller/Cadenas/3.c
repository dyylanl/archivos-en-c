/*
 * Escriba una aplicación C que reciba una frase de la línea de comandos (en 1 sólo segmento) e imprima:
 * a) cantidad de consonantes;
 * b) cantidad de palabras;
 * c) cantidad de palabras con, al menos, 3 vocales distintas.
 */

//Cuento vocales>= 3, distintas se me complicaba mucho

//Compilo: >>> gcc 3.c -o 3
//Ejecuto: >>> ./3 "Estaa maaal hechooo"
/*Salida Esperada:
Consonantes: 7
Palabras: 3
Palabras con >=3 vocales: 3
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool esVocal(char c) {
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
        return true;
    if (c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
        return true;
    return false;
}

bool esConsonante(char c) {
    if (c=='b' || c=='c' || c=='d' || c=='f' || c=='g' || c=='h' || c=='j' || c=='k' || c=='l' || c=='m' || c=='n')
        return true;
    if (c=='p' || c=='q' || c=='r' || c=='s' || c=='t' || c=='v' || c=='w' || c=='x' || c=='y' || c=='z')
        return true;
    if (c=='B' || c=='C' || c=='D' || c=='F' || c=='G' || c=='H' || c=='J' || c=='K' || c=='L' || c=='M' || c=='N')
        return true;
    if (c=='P' || c=='Q' || c=='R' || c=='S' || c=='T' || c=='V' || c=='W' || c=='X' || c=='Y' || c=='Z')
        return true;
    return false;   
}

int main(int argc, char** argv) {
    if (argc != 2)
        return 1;
    char* frase = argv[1];
    int consonantes = 0, palabras = 0, palabras2 = 0;
    bool habiaEspacio = true;
    int vocales = 0;
    
    char c;
    int i;
    while (i < strlen(frase)+1) {
        c = frase[i];        
        
        //Cuento vocales y consonantes
        if (esConsonante(c))
            consonantes++;
        if (esVocal(c))
            vocales++;
        
        //Cuando termina una palabra
        if ((c==' ' || c=='\0') && !habiaEspacio) {
            palabras++;
            if (vocales >= 3)
                palabras2++;
            vocales = 0;
        }

        //Indico para la siguiente iteracion si habia un espacio o no antes
        if (c!=' ' && c!='\0')
            habiaEspacio = false;
        if (c==' '|| c=='\0')
            habiaEspacio = true;
            
        i++;
    }
    
    printf("Consonantes: %d\n", consonantes);
    printf("Palabras: %d\n", palabras);
    printf("Palabras con >=3 vocales: %d\n", palabras2);
    return 0;
}