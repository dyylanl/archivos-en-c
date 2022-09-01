#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
  
int main(int argc, char const* argv[]) {
    int sock = 0;
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[4] = { 0 };

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error.\n");
        return -1;
    }

    uint16_t port = atoi(argv[2]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    printf("Intentando establecer conexion con el puerto: %u\n",port);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported.\n");
        return(-1);
    }

    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("Connection Failed \n");
        return(-1);
    }

    char buf[4];
    fscanf(stdin, "%s", &buf);
    send(sock, &buf, strlen(buf), 0);
    int valread = read(sock, buffer, 4);
    printf("[RECV]: %s\n", buffer);
    close(client_fd);
    return 0;
}