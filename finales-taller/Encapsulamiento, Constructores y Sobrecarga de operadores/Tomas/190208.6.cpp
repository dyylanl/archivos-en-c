/*
 *    Ejercicio [6] final 19/02/08
 *    Defina el operador » de forma que cargue el contenido de una
      lista de STL. La carga se iniciará con el ingreso del número
      de elementos a ingresar. (Suponer que la clase contenida en la
      lista implementa el operador » ).
 */


#include <iostream>
#include <list>
#include <cstdlib>

std::istream& operator>>(std::istream& is, list<int>& lista) {
	std::string entry;
	//Paso el contenido de is (capturado del cin) a entry
	std::getline(is, entry);
	//Convierto el string entry a char* y luego a int para meterlo en la lista 
	lista.push_back(atoi(entry.c_str()));
	return is;
}

//De aca para abajo el ejercicio no se pide, pero lo usamos para verificar
int main(int argc, char** argv) {
	//Valido cantidad de parámetros
	if (argc<2) {
		cout << "Faltan parametros" << endl;
		return 1;
	}
	
	//Convierto a int la cantidad de elementos a cargar
	int cantidad=atoi(argv[1]);
	//Creo una lista llamada listaEnteros con un template de lista para enteros
	list<int> listaEnteros;
	
	//Capturo cin y meto enteros en la lista
	//Mientras la cantidad>0 pido un entero para cargar en la lista
	while ((cantidad>0) && (cin >> listaEnteros))
		cantidad--;

	//Creo el itetador it para listas<int>
	list<int>::iterator it;
	//Recorro la lista usando el iterador it e imprimo salida
	for (it=listaEnteros.begin(); it!=listaEnteros.end(); ++it)
		std::cout << *it << std::endl;
	
	return 0;
}
