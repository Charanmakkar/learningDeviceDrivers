#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file_path> <start_offset> <length>\n", argv[0]);
        return 1;
    }

    char *file = argv[1];
    off_t start = atol(argv[2]);   // Convert start offset to a long integer
    off_t length = atol(argv[3]); // Convert length to a long integer

    int fd = open(file, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 0;
    }

    printf("Opening %s\n", file);

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;   // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = start;    // Starting byte offset
    lock.l_len = length;     // Length of the lock (0 for till end of file)

    while (1) {
        // Check lock status using F_GETLK
        struct flock test_lock = lock;

        printf("-> %d\n", test_lock.l_type);
        printf("-> %d\n", lock.l_type);
        
        if (fcntl(fd, F_GETLK, &test_lock) == -1) {
            perror("Failed to check lock status");
            close(fd);
            return 0;
        }
        
        printf("%d\n", test_lock.l_type);
        printf("%d\n", lock.l_type);

        if (test_lock.l_type == F_UNLCK) {
            printf("-->> %d\n", test_lock.l_type);
            printf("-->> %d\n", lock.l_type);

            // Lock is available; acquire it
            if (fcntl(fd, F_SETLK, &lock) == -1) {
                perror("Failed to acquire write lock");
                close(fd);
                return 0;
            }

            printf("--->>> %d\n", test_lock.l_type);
            printf("--->>> %d\n", lock.l_type);

            printf("Done. Hit <Enter> to unlock ...\n");
            getchar();
            printf("Unlocking ... \n");
            
            break;
        } else {
            // Lock is held by another process
            printf("Lock held by process %d. Retrying in 2 seconds...\n", test_lock.l_pid);
            sleep(2); // Retry after a short delay
        }
    }

    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release write lock");
        close(fd);
    } 
    
    printf("Done.\n");

    close(fd);

    return 0;
}
