/*
 * Sumponga que está programando una aplicación multi-thread y necesita lanzar
 * un thread pasándole 3 parámetros. ¿Cómo lo hace?. Ejemplifique.
 */

#include <iostream>
#include <thread>

void foo(int arg1, char arg2, bool arg3) {
    std::cout << arg1 << " " << arg2 << " " << arg3 << std::endl;
}

int main() {
    std::thread t1(foo, 33, 'c', true);
    t1.join();
    return 0;
}