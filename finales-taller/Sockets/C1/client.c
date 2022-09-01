/*
 * Escriba una pequeña aplicación C/C++ que se conecte al puerto 2000 del
 * equipo 192.168.1.2, transmita la cadena “hola” y se cierre ordenadamente
 * sin esperar respuesta alguna.
 */

/*
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

//CONSTANTES
#define PUERTO "2000"
#define IP "localhost" //"localhost" para testear
#define CADENA "hola"

int main(int argc, char* argv[]) {
    const char hostname[] = IP;
    const char* port = PUERTO;
    const char cad[] = CADENA;

    struct addrinfo hints; //Creamos hints que es la estructura con la informacion del socket
    memset(&hints, 0, sizeof(struct addrinfo)); //Limpiamos la memoria en hints
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = 0; // Client
    struct addrinfo* results; //Creo un puntero que apunta a hints
    
    getaddrinfo(hostname, port, &hints, &results);
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol); //Obtengo el file descriptor del socket
    
    connect(fdSkt, results->ai_addr, results->ai_addrlen); //Conecto 
    freeaddrinfo(results);
    
    send(fdSkt, cad, strlen(cad), MSG_NOSIGNAL);
    
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}
