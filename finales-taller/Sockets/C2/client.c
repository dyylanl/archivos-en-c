/*
 * Implemente un programa C que reciba por línea de comandos 3 parámetros: IP, 
 * PUERTO y ARCHIVO; y que transmita el archivo binario <ARCHIVO>
 * al puerto <PUERTO> de la dirección <IP>, utilizando protocolo TCP/IP.
 * No valide errores.
 */

/*
Compilar con                                >>> gcc -o client client.c
Abrir server con netstat en una terminal    >>> netcat -l 2000 -v
Ejecutar en otra terminal                   >>> ./client "localhost" 2000 "archivo.txt"
*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#define TAM_MAX_PARAM_STR 20

//LIBRERIAS EXTERNAS
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char hostname[TAM_MAX_PARAM_STR];
    char port[TAM_MAX_PARAM_STR];
    char filename[TAM_MAX_PARAM_STR];
    FILE* fdFile;
    
    //Capturamos los parametros que son strings
    strncpy(hostname, argv[1], TAM_MAX_PARAM_STR);
    strncpy(port, argv[2], TAM_MAX_PARAM_STR);
    strncpy(filename, argv[3], TAM_MAX_PARAM_STR);
    
    //fdFile = fopen(filename, "r"); //CASO: ARCHIVO DE TEXTO
    fdFile = fopen(filename, "rb"); //CASO: ARCHIVO BINARIO

    printf("hostname: %s\n", hostname);
    printf("port: %s\n", port);
    printf("filename: %s\n", filename);
    
    struct addrinfo hints; //Creamos hints que es la estructura con la informacion del socket
    memset(&hints, 0, sizeof(struct addrinfo)); //Limpiamos la memoria en hints
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    struct addrinfo* results; //Creo un puntero con la misma estructura addrinfo

    getaddrinfo(hostname, port, &hints, &results);
    //Obtengo el file descriptor del socket
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    
    connect(fdSkt, results->ai_addr, results->ai_addrlen); //Conecto 
    freeaddrinfo(results);
    
    //Sirve para archivo de texto y para archivo binario
    /*char c;
    while ((c = fgetc(fdFile)) != EOF) {
        printf("%c",c);
        send(fdSkt, &c, 1, MSG_NOSIGNAL);
    }*/
    
    //Sirve para archivo de texto y para archivo binario
    /*int elementos;
    char buffer[1];
    while (!feof(fdFile)) {
        elementos = fread(buffer, sizeof(char), 1, fdFile);
        if (elementos > 0) {
            //printf("%s",buffer);
            send(fdSkt, buffer, sizeof(char), MSG_NOSIGNAL);
        }
    }*/  
    
    //Sirve para archivo binario
    int elementos;
    unsigned int buffer;
    while (!feof(fdFile)) {
        elementos = fread(&buffer, sizeof(unsigned int), 1, fdFile);
        //htonl() en netcat me invierte el resultado, lo estare usando bien?
        //buffer = htonl(buffer);
        if (elementos > 0) {
            send(fdSkt, &buffer, sizeof(unsigned int), MSG_NOSIGNAL);
        }
    }
    
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    fclose(fdFile);
    return 0;
}