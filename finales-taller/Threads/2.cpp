/*
 * Escriba un ejemplo en el cual un thread use un contador global entero y lo 
 * incremente de a una unidad; y otro thread del mismo proceso lo imprima y lo 
 * decremente. Ambos threads deben coordinar el acceso a la memoria y deben 
 * correr sincronizados de forma que siempre se impriman los números 1,0,1,0..
 */

//Para salida 1,0,1,0 ambos threads deberian imprimir.

#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

std::mutex m;
int contador;
bool turno; //false 1er thread, true 2do thread

void fooHilo1() {
    while (true) {
        m.lock();
        if (!turno) {
            contador++;
            std::cout << contador << std::endl;
            turno = true;
            sleep(1);
        }
        m.unlock();
    }
}

void fooHilo2() {
    while (true) {
        m.lock();
        if (turno) {
            contador--;
            std::cout << contador << std::endl;
            turno = false;
            sleep(1);
        }
        m.unlock();
    }
}

int main() {
    contador = 0;
    turno = false;
    std::thread t1(fooHilo1);
    std::thread t2(fooHilo2);
    t1.join();
    t2.join();
    return 0;
}
