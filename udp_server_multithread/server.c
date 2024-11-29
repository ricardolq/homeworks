#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "../include/netcommon.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

typedef struct Request{
    socklen_t fromlen;
	struct sockaddr_in from;
	char buf[BUFFER_SIZE];
} Request;

int server_fd;

void * process_request(void * arg) {
    Request *request = (Request *)arg;

    // Converting message to uppercase
    to_uppercase(request->buf);
    // Sending uppercase message back to client
    sendto(server_fd, request->buf, strlen(request->buf), 0, (struct sockaddr *)&request->from, request->fromlen);
    printf("Uppercase message sent: %s\n", request->buf);
    free(request);
    return NULL;
}

int main() {
    INIT_SOCKETS();

    struct addrinfo hints, *address;
    char buffer[BUFFER_SIZE] = {0};

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "8080", &hints, &address) != 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    // Creating socket file descriptor
    server_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
    if (!ISVALIDSOCKET(server_fd)) {
        fprintf(stderr, "socket failed: %d\n", GETSOCKETERRNO());
        exit(EXIT_FAILURE);
    }

    // Binding the socket to the network address and port
    if (bind(server_fd, address->ai_addr, address->ai_addrlen) < 0) {
        fprintf(stderr, "bind failed: %d\n", GETSOCKETERRNO());
        CLOSESOCKET(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);
    while(1){
        struct Request *request = (Request*)malloc(sizeof(Request));
        request->fromlen = sizeof(struct sockaddr_in);

        // Receiving message from client
        int valread = recvfrom(server_fd, request->buf, BUFFER_SIZE, 0, (struct sockaddr *)&request->from, &request->fromlen);
        if (valread < 0) {
            fprintf(stderr, "recvfrom failed: %d\n", GETSOCKETERRNO());
            CLOSESOCKET(server_fd);
            exit(EXIT_FAILURE);
        }
        request->buf[valread] = '\0';
        printf("Received: %s\n", request->buf);

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, (void *)process_request, (void *)request) != 0) {
            fprintf(stderr, "Failed to create thread\n");
            CLOSESOCKET(server_fd);
            exit(EXIT_FAILURE);
        }
        pthread_detach(thread_id);
    }
    // Closing the socket
    CLOSESOCKET(server_fd);

    return 0;
}
