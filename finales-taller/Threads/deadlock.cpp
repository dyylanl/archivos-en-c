/*
 * Se generó un deadlock porque ambos hilos quedaron bloqueados a la 
 * espera de un evento que nunca va a suceder.
 */

#include <mutex>
#include <thread>
std::mutex m; //Mutex global

void callback() {
    m.lock(); //Se bloquea a la espera que se libere el mutex tomado por el hilo principal
    //Hace cosas
    m.unlock(); //Nunca llega a liberar el mutex porque se bloqueo esperando para tomarlo
}

int main() {  
    std::thread t;
    m.lock(); //Toma el mutex
    t = std::thread(callback); //Lanza un hilo
    t.join(); //Se bloquea a la espera que el hilo termine su ejecución
    m.unlock(); //Nunca llega a liberar el mutex porque se bloqueo en el join
    return 0;
}