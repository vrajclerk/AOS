//Day time server
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int main() {
    int a = fork();
    time_t t;
    const char *name = "file";
    int fd;
    int size = 4096;
    void *ptr;

    if (a == 0) {
        // Child Process
        fd = shm_open(name, O_RDONLY, 0777);
        ftruncate(fd, size);
        ptr = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
        while (1) {
            printf("content from server: %s\n", (char *)ptr);
            usleep(200000); // Sleep for 200 milliseconds before reading again
        }
    } else {
        // Parent Process
        fd = shm_open(name, O_CREAT | O_RDWR, 0777);
        ftruncate(fd, size);
        ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
        while (1) {
            time(&t);
            sprintf(ptr, "%s", ctime(&t));
            usleep(1000000); // Sleep for 1 second before updating again
        }
    }

    return 0;
}
