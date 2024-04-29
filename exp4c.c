// Find out whether file descriptors and file read pointer are shared or not by parent and  child process after fork()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    const char *filename = "demo.txt";

    // Create or open the text file
    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {  // Parent process
        // Read from the file in the parent
        char buffer[100];

        wait(NULL); 
        ssize_t bytes_read = read(file_descriptor, buffer, sizeof(buffer));

        if (bytes_read > 0) {
            printf("Parent read: %.*s", (int)bytes_read, buffer);
        } else {
            printf("Parent read nothing.\n");
        }

        // Wait for the child to finish
    } else {  // Child process
        // Read from the file in the child
        char buffer[100];
        ssize_t bytes_read = read(file_descriptor, buffer, 11);

        if (bytes_read > 0) {
            printf("Child read: %.*s\n", (int)bytes_read, buffer);
        } else {
            printf("Child read nothing.\n");
        }
    }
    close(file_descriptor);

    // Close the file descriptor

    return 0;
}