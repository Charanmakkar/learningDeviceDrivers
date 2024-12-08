// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// int main(int argc, char* argv[])
// {
// 	char *file;
// 	int fd;
// 	struct flock lock;

// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
// 		return 1;
// 	}
// 	file = argv[1];
// 	printf("Opening %s\n", file);
// 	//TODO: Open the File for read write
// 	fopen(file, "rw");
// 	printf("\nLocking ... ");
// 	//TODO: Zero out the 'lock' and initialize the various fields to lock the
// 	//Entire file
// 	//TODO: Invoke fcntl to lock the file

// 	printf("Done. Hit <Enter> to unlock ...\n");
// 	getchar();
// 	printf("Unlocking ... ");
// 	//TODO: Invoke fcntl to unlock the file
// 	printf("Done.\n");

// 	close(fd);
// 	return 0;
// }

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char *file;
    int fd;
    struct flock lock;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    file = argv[1];
    printf("Opening %s\n", file);

    // Open the file for read-write
    fd = open(file, O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("\nLocking ... ");

    // Zero out the 'lock' struct and initialize fields
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK; // Write lock
    lock.l_whence = SEEK_SET; // From the beginning of the file
    lock.l_start = 0; // Start at the beginning
    lock.l_len = 0; // Lock the entire file

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
