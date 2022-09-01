/*
 * Escriba un ejemplo en el cual un thread genere los nros. de la serie de fibonacci
 * a razón de 1 cada 2 segundos; y otro thread del mismo proceso los imprima al
 * mismo ritmo. Ambos threads deben coordinar el acceso a la memoria y deben correr
 * sincronizados de forma que la serie se imprima correctamente.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>

std::mutex m;
bool turno; //falso Hilo 1, verdadero Hilo 2
std::vector<unsigned long int> fibonacci;

void fibo() {
    while (true) {
        m.lock();
        if (!turno) {
            if (fibonacci.empty() or (fibonacci.size() == 1))
                fibonacci.push_back(1);
            else
                fibonacci.push_back(fibonacci.at(fibonacci.size()-1)+fibonacci.at(fibonacci.size()-2));
            turno = true;
            sleep(2);
        }
        m.unlock();
    }
}
void imprimir() {
    while (true) {
        m.lock();
        if (turno) {
            std::cout << fibonacci.at(fibonacci.size()-1) << std::endl;
            turno = false;
        }
        m.unlock();
    }
}

int main() {
    turno = false;
    std::thread t1(fibo);
    std::thread t2(imprimir);
    t1.join();
    t2.join();
    return 0;
}