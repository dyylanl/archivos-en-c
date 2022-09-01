/*
 * Ejemplo en el cual un thread use un contador global entero y lo 
 * incremente de a una unidad; y otro thread del mismo proceso lo imprima y lo 
 * decremente. Ambos threads deben coordinar el acceso a la memoria y deben 
 * correr sincronizados de forma que siempre se impriman los números 1,0,1,0..
 */

//Para salida 1,0,1,0 ambos threads deberian imprimir.

// Compilar como: $ g++ -pthread hilos.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

std::mutex m;

void fooHilo1(int *contador, int *max) {
    while (*contador < *max) {
        m.lock();
        if (*contador%2 == 0) {
            std::cout << *contador << std::endl;
            (*contador)++;
        }
        m.unlock();
    }
}

void fooHilo2(int *contador, int *max) {
    while (*contador < *max) {
        m.lock();
        if (*contador%2 != 0) {
            std::cout << *contador << std::endl;
            (*contador)++;
        }
        m.unlock();
    }
}

int main() {
    int contador = 0;
    int max = 20;
    std::thread t1(fooHilo1,&contador,&max);
    std::thread t2(fooHilo2,&contador,&max);
    t1.join();
    std::cout << "Hilo1 joineado." << std::endl;
    t2.join();
    std::cout << "Hilo2 joineado." << std::endl;
    return 0;
}
