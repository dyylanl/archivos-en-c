/*
 * Escriba un programa que, recibiendo por línea de comandos una IP y un PUERTO,
 * se conecte al puerto PUERTO del ordenador con ip IP y transmita la cadena “Aquí estoy”.
 * El programa debe terminar cuando reciba “Yo También”.
 */

/*
 * Compilación:         >>> gcc -o client client.c
 * Ejecución Cliente:   >>> .\client localhost 2020
 * Netcat Server:       >>> netcat -q 10 -l 2024 -v < yotambien
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#define TAM_MAX_PARAM 20
#define SALUDO_A_ENVIAR "Aqui estoy"
#define RESPUESTA_ESPERADA "Yo tambien"
#define MAX_MSG_LEN 100
#define FINCADENA '\0'

//LIBRERIAS EXTERNAS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]) {    
    char ip[TAM_MAX_PARAM];
    char port[TAM_MAX_PARAM];
    strncpy(ip, argv[1], TAM_MAX_PARAM);
    strncpy(port, argv[2], TAM_MAX_PARAM);
    
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    
    struct addrinfo* results;
    
    getaddrinfo(ip,port,&hints,&results);
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    
    connect(fdSkt,results->ai_addr,results->ai_addrlen);
    freeaddrinfo(results);
    
    char bufferSend[] = SALUDO_A_ENVIAR;
    char bufferRecv[MAX_MSG_LEN];
    send(fdSkt,bufferSend,sizeof(bufferSend),MSG_NOSIGNAL);
    printf("Mensaje enviado: %s\n", bufferSend);
    bool respuestaEsperada = false;
    bool mensajeRecibido;
    int recibidos;
    while (!respuestaEsperada) {
        mensajeRecibido = false;
        memset(bufferRecv,0,MAX_MSG_LEN);
        recibidos = 0;
        while (!mensajeRecibido) {
            recibidos += recv(fdSkt,&bufferRecv[recibidos],1,MSG_NOSIGNAL);
            if (bufferRecv[recibidos-1] == FINCADENA || recibidos == MAX_MSG_LEN)
                mensajeRecibido = true;
        }
        printf("Mensaje recibido: %s\n", bufferRecv);
        if (strcmp(bufferRecv,RESPUESTA_ESPERADA) == 0)
            respuestaEsperada = true;
    }
    printf("Respuesta esperada: \"%s\" recibida! => Fin del programa\n", RESPUESTA_ESPERADA);
    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}