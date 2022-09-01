#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;        // para prevenir errores (e.g.:address already in use)
    int addrlen = sizeof(address);
 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Invalid file descriptor.\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error en OPT.\n");
        exit(EXIT_FAILURE);
    }

    uint16_t port = atoi(argv[1]);

    address.sin_family = AF_INET;           // ipv4
    address.sin_addr.s_addr = INADDR_ANY;   // significa que escuchara en todas las direcciones.
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0) { // bind: vincula el socket a la direccion y el puerto especificado en addr
        perror("Error de vinculacion.\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Error en el listen.\n");
        exit(EXIT_FAILURE);
    }

    printf("Servidor en escucha desde el puerto: %u\n",(port));
    
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Error en el accept.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Conexion aceptada...\n");
    char buffer[4] = { 0 };
    char buf[4];
    fscanf(stdin, "%s", &buf);
    int valread = read(new_socket, buffer, 4);
    printf("[RECV]: %s\n", buffer);
    send(new_socket, &buf, strlen(buf), 0);

    close(new_socket);
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}