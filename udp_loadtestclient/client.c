#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "../include/netcommon.h"
#include "../include/mythreads.h"

#define PORT "8080"
#define BUFFER_SIZE 1024
#define CLIENT_COUNT 50

const char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
#define WORD_COUNT (sizeof(words) / sizeof(words[0]))

pthread_barrier_t barrier;

void *client_thread(void *arg) {
    int sock = 0;
    char buffer[BUFFER_SIZE] = {0};
    struct addrinfo hints, *res;

    // Set up hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    // Get address info
    if (getaddrinfo("127.0.0.1", PORT, &hints, &res) != 0) {
        perror("getaddrinfo error");
        return NULL;
    }
    // Create socket
    if (!ISVALIDSOCKET(sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
        fprintf(stderr, "Socket creation error: %d\n", GETSOCKETERRNO());
        freeaddrinfo(res);
        return NULL;
    }

    // Seed the random number generator
    srand(time(NULL));
    // Select a random word from the list
    const char *random_word = words[rand() % WORD_COUNT];

    // Wait for all threads to be ready
    pthread_barrier_wait(&barrier);
    
    // Send the random word to the server
    if (sendto(sock, random_word, strlen(random_word), 0, res->ai_addr, res->ai_addrlen) == -1) {
        fprintf(stderr, "Send error: %d\n", GETSOCKETERRNO());
        freeaddrinfo(res);
        CLOSESOCKET(sock);
        return NULL;
    }
    printf("Sent: %s\n", random_word);

    // Receive the server's response
    struct sockaddr_storage server_addr;
    socklen_t addr_len = sizeof(server_addr);
    int valread = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);
    } else {
        fprintf(stderr, "Read error: %d\n", GETSOCKETERRNO());
    }

    // Free address info and close the socket
    freeaddrinfo(res);
    CLOSESOCKET(sock);

    return NULL;
}

int main() {
    INIT_SOCKETS();
    pthread_t clients[CLIENT_COUNT];

    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, CLIENT_COUNT);

    // Create client threads
    for (int i = 0; i < CLIENT_COUNT; ++i) {
        if (pthread_create(&clients[i], NULL, client_thread, NULL) != 0) {
            perror("pthread_create error");
            return -1;
        }
    }

    // Wait for all client threads to finish
    for (int i = 0; i < CLIENT_COUNT; ++i) {
        pthread_join(clients[i], NULL);
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);

    return 0;
}
