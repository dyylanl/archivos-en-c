/*
 * Implemente un programa que reciba por línea de comandos una dirección IP y un PUERTO;
 * y transmita 50 paquetes de 10 bytes aleatorios a esa dirección/puerto a intervalos de 2 segundos.
 */

/*
 * Compilación:         >>> gcc -o client client.c
 * Ejecución Cliente:   >>> ./client localhost 2024
 * Netcat Server:       >>> netcat -l 2024 -v
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

//LIBRERIAS EXTERNAS
#include <stdio.h>
#include <string.h>
//#include <stdbool.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define TAM_MAX_PARAM 20
#define INTERVALO 2
#define CANT_PAQUETES 50
#define TAM_PAQUETE 10

int main(int argc, char* argv[]) {
    char ip[TAM_MAX_PARAM];
    char port[TAM_MAX_PARAM];
    strncpy(ip,argv[1],TAM_MAX_PARAM);
    strncpy(port,argv[2],TAM_MAX_PARAM);
    
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    
    struct addrinfo* results;
    getaddrinfo(ip, port, &hints, &results);
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    connect(fdSkt, results->ai_addr, results->ai_addrlen);
    freeaddrinfo(results);
    
    int paquetesEnviados;
    char paquete[TAM_PAQUETE];
    paquetesEnviados = 0;
    while (paquetesEnviados < CANT_PAQUETES) {
        for(int i = 0; i < TAM_PAQUETE; i++)
            paquete[i] = rand();
        //Fuerzo el ultimo byte del paquete como \n asi se visualiza mejor en netcat
        paquete[TAM_PAQUETE-1] = '\n';
        send(fdSkt, &paquete, TAM_PAQUETE, MSG_NOSIGNAL);
        /*int bytesEnviados = 0;
        while (bytesEnviados < TAM_PAQUETE)
            bytesEnviados += send(fdSkt, &paquete[bytesEnviados], 1, MSG_NOSIGNAL);*/
        paquetesEnviados++;
        sleep(INTERVALO);
    }
    
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}