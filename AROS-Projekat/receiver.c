#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_MESSAGE_SIZE 2000

int main() {
    const char *pipeName = "/tmp/chat_pipe";
    sem_t *senderSemaphore, *receiverSemaphore;

    // Open the named pipe
    int pipe_fd = open(pipeName, O_RDONLY);
    if (pipe_fd == -1) {
        perror("Error opening the pipe for reading");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    senderSemaphore = sem_open("/chat_sender_semaphore", O_CREAT, 0644, 1);
    receiverSemaphore = sem_open("/chat_receiver_semaphore", O_CREAT, 0644, 1);
    if (senderSemaphore == SEM_FAILED || receiverSemaphore == SEM_FAILED) {
        perror("Error initializing semaphores");
        exit(EXIT_FAILURE);
    }

    char receivedMessage[MAX_MESSAGE_SIZE];

    while (1) {
        // Wait for the receiver semaphore
        sem_wait(receiverSemaphore);

        // Read a message from the pipe
        ssize_t bytesRead = read(pipe_fd, receivedMessage, MAX_MESSAGE_SIZE);
        if (bytesRead > 0) {
            printf("Received message: %s", receivedMessage);
        }

        // Post the sender semaphore
        sem_post(senderSemaphore);
    }

    close(pipe_fd);
    sem_close(senderSemaphore);
    sem_close(receiverSemaphore);
    return 0;
}