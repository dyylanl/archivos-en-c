/*
Compilar con                                >>> gcc -o server server.c
Abrir cliente con netstat en una terminal   >>> netcat 127.0.0.1 2000 -v
Ejecutar en otra terminal                   >>> ./server
*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

//LIBRERIAS EXTERNAS
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define TAM_BUFFER_SERVER 10

int main(int argc, char* argv[]) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // Server
    struct addrinfo *results;
    getaddrinfo("127.0.0.1", "2000", &hints, &results);

    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    bind(fdSkt, results->ai_addr, results->ai_addrlen);
    freeaddrinfo(results);
    listen(fdSkt, 10);    
    int fdSktPeer = accept(fdSkt, NULL, NULL);  
    
    //Sumo 1 para dejar un \0 y el printf no escriba basura.
    char buffer[TAM_BUFFER_SERVER+1];
    memset(buffer, 0, TAM_BUFFER_SERVER+1);
    
    int received = 0;
    while (received < TAM_BUFFER_SERVER) //Recibo 1 paquete
        received += recv(fdSktPeer, &buffer[received], /*TAM_BUFFER_SERVER-received-1*/ 1, MSG_NOSIGNAL);

    printf("Mensaje en paquete recibido:\n%s\n", buffer);
    shutdown(fdSktPeer, SHUT_RDWR);
    close(fdSktPeer);
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}