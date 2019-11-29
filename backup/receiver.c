#include "receiver.h"

void *client_handler(void *arg);

void *receiver_start(void *arg) {

    int server_socket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    int server_port = 9000;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(server_port);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Bind the address struct to the socket ----*/
    bind(server_socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if(listen(server_socket,5)==0) {
        printf("Server Listening to port %d.\n", server_port);
    }
    else {
        printf("Error\n");
    }


    while (1) {
        /*---- Accept call creates a new socket for the incoming connection ----*/
        int *client_socket = malloc(sizeof(int));
        addr_size = sizeof serverStorage;
        (*client_socket) = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size);


        pthread_t receiver_thread;
        pthread_create(&receiver_thread, NULL, &client_handler, NULL);

    }


    return NULL;
}


void *client_handler(void *arg) {

    int client_socket = *((int *) arg);

    printf("Thread started to comunicate with client %x. \n", client_socket);


    return NULL;
}

