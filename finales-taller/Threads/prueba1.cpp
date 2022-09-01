#include <mutex>
#include <thread>
std::mutex m; //Mutex global
int recursoCompartido = 0;

void foo(){
    m.lock(); // Se solicita el mutex
    recursoCompartido++; //Accedo al recurso protegido
    m.unlock(); // Se libera el mutex
}

int main() {
    std::thread tA, tB;
    tA = std::thread(foo); //Instancio el hilo A que corre en la funcion foo()
    tB = std::thread(foo); //Instancio el hilo B que corre en la funcion foo()
    tA.join(); //Espera a que el hilo A termine y luego lo une al hilo principal (main)
    tB.join(); //Espera a que el hilo B termine y luego lo une al hilo principal (main)
    return 0;
}
