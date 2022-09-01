/*
 * Defina el operador int que trabaje con listas STL de tipos genéricos T.
 * El operador debe devolver la cantidad de elementos distintos que posee la lista.
 */

#include <iostream>
#include <list>

class T {
private:
    const int _id;
public:
    T(const int id);
    friend std::ostream& operator<<(std::ostream& os, const T& t);
};

T::T(const int id) : _id(id) {}

operator int() {
    return 1;
}

std::ostream& operator<<(std::ostream& os, const T& t) {
    os << t._id;
    return os;
}

int main(int argc, char** argv) {   
    //Creo una lista llamada ls con un template de lista para enteros
    //Se supone que en vez de ints son tipos de tipo generico T, y que la clase T tiene sobrecargado el operador ==
    std::list<T> ls = {T(1), T(2), T(3), T(3)};
    //Creo el itetador it para listas<int>
    std::list<T>::iterator it;
    //Recorro la lista usando el iterador it e imprimo salida
    for (it=ls.begin(); it!=ls.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    
    //std::cout << "Cantidad de elementos distintos: " << (int)ls << std::endl;
    
    return 0;
}