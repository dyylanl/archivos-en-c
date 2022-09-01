/*
 * Tratamos de hacer codigo thread-notsafe
 */

/*
 * Se compila con: >>> g++ -std=c++11 -pthread prueba.cpp -o prueba
 * Se ejecuta con: ./prueba
 */
/*
#include <iostream>
#include <thread>
#include <mutex>
#define VALOR 0
#define ITERACIONES 10000
#define N_THREADS 2
std::mutex m; //Mutex global
int a = VALOR; //Recurso compartido global

void foo(int tid){  
    for (int i=0; i<ITERACIONES; ++i) {
        a++;
        a--;
        m.lock();
        //Cuando haya solapamiento entre threads va a!=VALOR en esta linea
        //Esto va a suceder porque a++ y a-- no estan lockeadas (no protego el recurso compartido)
        if (a != VALOR) {
            std::thread::id realId = std::this_thread::get_id();
            std::cout << "Thread " << tid << " " << realId << " ITERACION " << i << " a = " << a << std::endl;
            a = VALOR; //Corrijo el error
        }
        m.unlock();
    }
}

int main() {
    std::thread t[N_THREADS]; 
    //Lanzo un grupo de N threads
    for (int i = 1; i <= N_THREADS; ++i) {
        t[i] = std::thread(foo, i);
    }
    //Se unen los threads al thread principal (main)
    for (int i = 1; i <= N_THREADS; ++i) {
        t[i].join();
    }
    return 0;
}
*/







#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 4

pthread_barrier_t mybarrier;

void* callback(void *id_ptr) {
  sleep(5);
  pthread_barrier_wait(&mybarrier); //Bloquea hasta que a la barrera lleguen los 4 hilos+ el principal.
  return NULL;
}

int main() {
    pthread_t ids[THREAD_COUNT];
    int short_ids[THREAD_COUNT];
    pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT+1); //Creo una barrera para 5 hilos (4+el principal).
    
    for (int i = 0; i < THREAD_COUNT; ++i) {//Lanzo 4 hilos en la funcion callback
        short_ids[i] = i;
        pthread_create(&ids[i], NULL, callback, &short_ids[i]); 
    }

    pthread_barrier_wait(&mybarrier); //Bloquea hasta que a la barrera lleguen los 4 hilos+ el principal.

    for (int j = 0; j < THREAD_COUNT; ++j) //Uno todos los hilos en el hilo principal
        pthread_join(ids[j], NULL);

    pthread_barrier_destroy(&mybarrier); //Destruyo la barrera
    return 0;
}