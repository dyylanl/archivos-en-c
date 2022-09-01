/*
 * Escriba una aplicación C que solicite una dirección IP, un puerto y un mensaje
 * (string) por teclado. El programa debe conectarse al destino indicado, transmitir
 * el mensaje y cerrar las conexiones ordenadamente antes de terminar.
 */

/*
 * Compilación:         >>> gcc -o client client.c
 * Ejecución Cliente:   >>> ./client localhost 2024 "Soy un mensaje."
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

#define MAX_IP_LEN 17//(15 chars) (ej: 127.127.127.127) + \n + \0
#define MAX_PORT_LEN 7 //5 cifras (ej: 20300) + \n + \0
#define MAX_MSG_LEN 102 //100 char + \n + \0

int main(int argc, char* argv[]) {
    char ip[MAX_IP_LEN];
    char port[MAX_PORT_LEN];
    char msg[MAX_MSG_LEN];
    
    printf("Ingrese IP: ");
    fgets (ip, MAX_IP_LEN, stdin);
    ip[strlen(ip)-1] = '\0'; //Pisamos el \n con un \0
    printf("Ingrese Puerto: ");
    fgets (port, MAX_PORT_LEN, stdin);
    port[strlen(port)-1] = '\0'; //Pisamos el \n con un \0
    printf("Ingrese Mensaje a Enviar: ");
    fgets (msg, MAX_MSG_LEN, stdin);
    msg[strlen(msg)-1] = '\0'; //Pisamos el \n con un \0
    
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
    
    send(fdSkt, msg, strlen(msg), MSG_NOSIGNAL);    
    
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
}