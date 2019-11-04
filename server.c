#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define PORT 8080

typedef struct _cir_client_context {
    pthread_t thread_id;
    int socket;
} cir_client_context;

void *clientHandler(void *vargp);

int main() {
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cir_client_context *client_context  = malloc(sizeof(cir_client_context));

    if ((client_context->socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    pthread_create(&client_context->thread_id, NULL, clientHandler, (void *)cir_client_context);

    return EXIT_SUCCESS;
}

void *clientHandler(void *vargp) {
    cir_client_context *client_context = (cir_client_context *)vargp;

    valread = read(client_context->socket, buffer, 1024);
    printf("%s\n",buffer );
    send(client_context->socket, hello, strlen(hello) , 0 );
    printf("Hello message sent\n");

    return NULL;
}
