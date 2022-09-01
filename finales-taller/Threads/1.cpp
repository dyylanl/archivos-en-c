/*
 * Escriba un ejemplo en el cual un thread incremente un contador global
 * entero de a una unidad; y otro thread del mismo proceso lo imprima. 
 * Ambos threads deben coordinar el acceso a la memoria y deben correr
 * sincronizados de forma que siempre se impriman los números 1,2,3,4..
 */

#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>

std::mutex m;
int contador;
bool imprimir;

void incContador() {
    while (true) { //En el enunciado no se indica condición de corte
        m.lock();
        if (!imprimir) {
            contador++;
            imprimir = true;
            sleep(1);
        }
        m.unlock();
    }
}

void printContador() { 
    while (true) { //En el enunciado no se indica condición de corte
        m.lock();
        if (imprimir) {
            std::cout << contador << std::endl;
            imprimir = false;
            sleep(1);
        }
        m.unlock();
    }
}

int main() {
    std::thread t1;
    std::thread t2;
    contador = 0;
    imprimir = false;
    t1 = std::thread(incContador);
    t2 = std::thread(printContador);
    t1.join();
    t2.join();
    return 0;
}