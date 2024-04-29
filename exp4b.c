// Print i-node information using stat/fstat. Also identify type of a file (device file, pipe, directory, link etc.) 
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void printFileType(mode_t mode) {
    if (S_ISREG(mode))
        printf("Regular File\n");
    else if (S_ISDIR(mode))
        printf("Directory\n");
    else if (S_ISCHR(mode))
        printf("Character Device\n");
    else if (S_ISBLK(mode))
        printf("Block Device\n");
    else if (S_ISFIFO(mode))
        printf("FIFO/pipe\n");
    else if (S_ISLNK(mode))
        printf("Symbolic Link\n");
    else if (S_ISSOCK(mode))
        printf("Socket\n");
    else
        printf("Unknown File Type\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File Information:\n");
    printf("  File Path: %s\n", argv[1]);
    printf("  I-node Number: %ld\n", (long)fileStat.st_ino);
    printf("  File Size: %ld bytes\n", (long)fileStat.st_size);
    printf("  Number of Hard Links: %ld\n", (long)fileStat.st_nlink);
    printf("  Owner UID: %ld\n", (long)fileStat.st_uid);
    printf("  Group GID: %ld\n", (long)fileStat.st_gid);
    printf("  Device ID (if special file): %ld\n", (long)fileStat.st_rdev);
    printf("  Last Access Time: %ld\n", (long)fileStat.st_atime);
    printf("  Last Modification Time: %ld\n", (long)fileStat.st_mtime);
    printf("  Last Status Change Time: %ld\n", (long)fileStat.st_ctime);

    printf("File Type: ");
    printFileType(fileStat.st_mode);

    return 0;
}
