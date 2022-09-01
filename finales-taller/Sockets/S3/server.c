/*
 * Escriba un programa que acepte conexiones por el puerto 2283. En cada conexión
 * abierta debe esperar paquetes de datos de 513 bytes y devolverlos al emisor. 
 * El programa debe terminar ordenadamente al recibir algún paquete de 513 letras 'Q'.
 */

/*
 * Compilación:         >>> gcc -o server server.c
 * Ejecución Cliente:   >>> ./server
 * Netcat Client       >>> netcat localhost 2283 -v < archivo
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

//LIBRERIAS EXTERNAS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define IP "localhost"
#define PUERTO "2287"
#define TAM_PAQUETE 3//513
#define CHAR_PAQ_FIN 'Q'
#define MAX_CONNECTIONS 10

int main(int argc, char* argv[]) {
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo* results;
    
    getaddrinfo(IP, PUERTO, &hints, &results);
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    bind(fdSkt, results->ai_addr, results->ai_addrlen);
    freeaddrinfo(results);
    listen(fdSkt, MAX_CONNECTIONS);
    
    int fdSktPeer = accept(fdSkt, NULL, NULL);
    char paqEsperado[TAM_PAQUETE] = {CHAR_PAQ_FIN};
    memset(paqEsperado, CHAR_PAQ_FIN, TAM_PAQUETE);
    printf("Paquete esperado: %s\n", paqEsperado);
    char paq[TAM_PAQUETE];
    bool paqEspRecv = false;
    while (!paqEspRecv) {
        int bytesRecibidos = 0;
        memset(paq, 0, TAM_PAQUETE);
        while (bytesRecibidos < TAM_PAQUETE)
            bytesRecibidos += recv(fdSktPeer, &paq[bytesRecibidos], 1, MSG_NOSIGNAL);
        printf("Paquete recibido: %s\n", paq);
        if (memcmp(paq, paqEsperado, TAM_PAQUETE) == 0) {
            paqEspRecv = true;
            printf("Paquete recibido!\n");
        }
        else {
            send(fdSktPeer, paq, TAM_PAQUETE, MSG_NOSIGNAL);
        }
    }   
    
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    
    return 0;
}