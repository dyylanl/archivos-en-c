/*
 * Defina el operador global + para obtener la unión de 2 listas STL 
 * de tipos genérico T (elementos de ambas listas, sin repeticiones).
 */

#include <iostream>
#include <list>

template < typename T >
std::list<T> operator+(const std::list<T>& t1, const std::list<T>& t2) {
    std::list<T> t;
    t.insert(t.end(), t1.begin(), t1.end());
    t.insert(t.end(), t2.begin(), t2.end());
    return t;
}

template < class T >
std::ostream& operator<<(std::ostream& os, std::list<T>& ls) {
    //Creo el itetador it para listas<int>
    typename std::list<T>::iterator it;
    //Recorro la lista usando el iterador it e imprimo salida
    for (it=ls.begin(); it!=ls.end(); ++it)
        os << *it << " ";
    return os;
}

int main() {
    std::list<char> ls1 = {'A', 'A', 'B'};
    std::list<char> ls2 = {'B', 'C', 'C'};
    std::list<char> ls3 = ls1 + ls2;
    
    std::cout << ls1 << std::endl;
    std::cout << ls2 << std::endl;
    std::cout << ls3 << std::endl;
    std::cout << (ls1 + ls2) << std::endl; //Falla nose porque
    return 0;
}
