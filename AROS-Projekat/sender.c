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

    // Define and initialize semaphores
    senderSemaphore = sem_open("/chat_sender_semaphore", O_CREAT, 0644, 1);
    receiverSemaphore = sem_open("/chat_receiver_semaphore", O_CREAT, 0644, 1);
    if (senderSemaphore == SEM_FAILED || receiverSemaphore == SEM_FAILED) {
        perror("Error initializing semaphores");
        exit(EXIT_FAILURE);
    }

    // Create a named pipe (FIFO)
    mkfifo(pipeName, 0644);

    // Open the pipe for writing
    int pipe_fd = open(pipeName, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Error opening the pipe for writing");
        exit(EXIT_FAILURE);
    }

    char message[MAX_MESSAGE_SIZE];

    while (1) {
        // User input
        printf("Enter a message: ");
        fgets(message, MAX_MESSAGE_SIZE, stdin);

        // Wait for the sender semaphore
        sem_wait(senderSemaphore);

        // Write the message to the pipe
        write(pipe_fd, message, strlen(message) + 1);

        // Post the receiver semaphore
        sem_post(receiverSemaphore);
    }

    close(pipe_fd);
    sem_close(senderSemaphore);
    sem_close(receiverSemaphore);
    return 0;
}