/*
 * Escriba una pequeña aplicación C/C++ que se conecte al puerto 2000 del
 * equipo 192.168.1.2, transmita la cadena “hola” y se cierre ordenadamente
 * sin esperar respuesta alguna.
 * 
Compilar con
>>> gcc -o client client.c
Abrir server con netcat en una terminal
>>> netcat -l 2000 -v
Ejecutar en otra terminal
>>> ./client
*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

//LIBRERIAS EXTERNAS
//#include <stdio.h>
#include <string.h>
//#include <stdbool.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define IP "localhost"
#define PORT "2001"
#define CADENA "hola"

int main(int argc, char** argv) {
    if (argc!=1)
        return 1;
    
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;
    struct addrinfo* results;
    getaddrinfo(IP, PORT, &hints, &results);

    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    connect(fdSkt, results->ai_addr, results->ai_addrlen);
    freeaddrinfo(results);

    const char cad[] = CADENA;
    send(fdSkt, cad, strlen(cad), MSG_NOSIGNAL);

    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}
