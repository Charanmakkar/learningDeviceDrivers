/* WRITE LOCK TASK NUMBER 3*/

/*
    argv[0] = program name
    argv[1] = file to operate operation on
    argv[2] = start point of lock
    argv[3] = end point of lock
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char *file;
    int fd;
    int getlk_status = 0;
    struct flock lock;
    off_t startPoint = atol(argv[2]);
    off_t endPoint = atol(argv[3]);


    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    file = argv[1];
    printf("Opening %s\n", file);


    printf("start %ld\n", startPoint);
    printf("end   %ld\n", endPoint);

    // Open the file for read-write
    fd = open(file, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("\nLocking ... ");

    // Zero out the 'lock' struct and initialize fields
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK; // Write lock
    lock.l_whence = SEEK_SET; // From the beginning of the file
    lock.l_start = startPoint; // Start at the beginning
    lock.l_len = endPoint; // Lock the entire file


    // Invoke fcntl to lock the file
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Done. Hit <Enter> to unlock ...\n");
    getchar();

    printf("Unlocking ... ");

    // Invoke fcntl to unlock the file
    lock.l_type = F_UNLCK; // Unlock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Done.\n");

    close(fd);
    return 0;
}

