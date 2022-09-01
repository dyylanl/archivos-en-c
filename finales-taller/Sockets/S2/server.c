/*
 * Escriba un programa que escuche conexiones TCP en el puerto 3280 y guarde en disco
 * con nombres correlativos (1.html, 2.html , ...) cada uno de los HTML recibidos.
 * <simil>
 * Escriba un programa que escuche conexiones TCP en el puerto 1180 y guarde en disco
 * con nombres correlativos (1.txt, 2.txt, ...) cada una de las páginas HTML recibidas
 * (1 página por conexión).
 */

/*
 * Con la siguiente linea enviamos el contendi de generador.html por la red y luego
 * cierra la conexion a los 0 segundos de llegar al EndOfFile del archivo.
 * netcat -q 0 localhost 3280 -v < generador.html
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

#define HOSTNAME "localhost"
#define PORT "3292"

#define TAM_BUFFER_SERVER 1
#define TAM_MAX_PARAM_STR 20

int main (int argc, char* argv[]) {  
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo* results;
    getaddrinfo(HOSTNAME, PORT, &hints, &results);
    
    int fdSkt = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    bind(fdSkt, results->ai_addr, results->ai_addrlen);
    listen(fdSkt, 10);
    int fdSktPeer;
    char filename[TAM_MAX_PARAM_STR];
    FILE* fdFile;
    int fileCounter = 0;
        
    bool finalizarPrograma = false;
    char c;
    char buffer;
    while (!finalizarPrograma) {
        fdSktPeer = accept(fdSkt, NULL, NULL);
        fileCounter++;
        snprintf(filename, TAM_MAX_PARAM_STR, "%d.html", fileCounter);
        printf("%s\n",filename);
        fdFile = fopen(filename, "w");
        buffer = '\0';
        while (recv(fdSktPeer, &buffer, sizeof(buffer), MSG_NOSIGNAL) > 0) {
            printf("%c",buffer);
            fputc(buffer, fdFile);
            buffer = '\0';
        }
        fclose(fdFile);

        //Una buena solucion seria usar threads para tener en un hilo separado
        //las conexiones y el bucle para el quit.
        c = 0;
        printf("Pulse q si no quiere recibir otro archivo: ");
        c = getchar();
        if (c == 'q')
            finalizarPrograma = true;
        printf("\n");

        shutdown(fdSktPeer, SHUT_RDWR); //Tantos Shutdown y close estan demas
        close(fdSktPeer);
    }

    shutdown(fdSkt, SHUT_RDWR);
    close(fdSkt);
    return 0;
}
