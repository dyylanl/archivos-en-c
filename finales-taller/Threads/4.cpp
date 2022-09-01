/*
 * Haciendo uso de un arreglo estático de 1000 posiciones, implemente una pila de enteros.
 * La librería debe contemplar su uso en ambientes multithreading. Por consiguiente se
 * espera que incorpore los recursos necesarios para garantizar la coherencia de la
 * estructura en todo momento.
 */

#include <iostream>
#include <mutex>

class Pila {
private:
    std::mutex &m;
    int array[1000];
    int cantElementos = 0;
public:
    Pila(std::mutex &m);
    void push(int elemento);
    int pop();
    friend std::ostream& operator<<(std::ostream& os, const Pila& p);
};

Pila::Pila(std::mutex &m):m(m) {}

void Pila::push(int elemento) {
    m.lock();
    array[cantElementos] = elemento;
    ++cantElementos;
    m.unlock();
}

int Pila::pop() {
    m.lock();
    int tmp = array[cantElementos-1];
    array[cantElementos-1] = 0;
    --cantElementos;
    m.unlock();
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Pila& p) {
    p.m.lock();
    for (int i=0; i<p.cantElementos; i++)
        os << p.array[i] << " ";
    p.m.unlock();
    return os;
}

int main() {
    std::mutex m;
    Pila p(m);
    p.push(1);
    p.push(2);
    p.push(3);
    std::cout << p << std::endl;
    int a = p.pop();
    std::cout << p << std::endl;
    std::cout << a << std::endl;
    return 0;
}