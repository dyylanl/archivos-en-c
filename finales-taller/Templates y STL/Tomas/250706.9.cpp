/*
 *      Ejercicio [9] coloquio 25/07/06
 * 		Declarar una clase Arreglo<T> que permita organizar una
 * 		coleccion de objetos T en un arreglo. Incluya constructor
 *		default, de copia, operador <<, =, [] e int.
 * 	    Compilar con:
 * 		g++ -o ej9 -g  -Wno-non-template-friend -ansi 250706.9.cpp
 */


#include <iostream>
#include "250706.9.h"
int main(int argc, char** argv)
{
    Arreglo<int> arreglo;
	
	arreglo.agregar(10);
	arreglo.agregar(20);
	arreglo.agregar(30);

	Arreglo<int> arreglo2;
	arreglo2 = arreglo;

    std::cout << "Arreglo: " << arreglo << std::endl;
    std::cout << "Arreglo2: " << arreglo2 << std::endl;
	Arreglo<int> arreglo3 = arreglo2+arreglo;
	std::cout << "Arreglo2: " << arreglo2 << std::endl;
	std::cout << "Arreglo3: " << arreglo3 << std::endl;
	return 0;
}
