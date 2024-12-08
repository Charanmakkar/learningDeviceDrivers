/* READ LOCK TASK 4*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char *file;
	int fd;
	struct flock lock;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}
	file = argv[1];
	printf("Opening %s\n", file);

	//TODO: Open the File for read write
	fd = open(file, O_RDONLY);
    if (-1 == fd){
        printf("Error in opening file\n");
        return 1;
    }

	printf("Locking ... \n");

	//TODO: Zero out the 'lock' and initialize the various fields to lock the
	memset(&lock, 0, sizeof(lock));
    lock.l_type = F_RDLCK;    //Entire file
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

	//TODO: Invoke fcntl to lock the file
    if(fcntl(fd, F_SETLK, &lock) == -1){
        perror("fcntl-1");
        close(fd);
        return 1;
    }

	printf("Done. Hit <Enter> to unlock ...\n");
	getchar();
	printf("Unlocking ... \n");

	//TODO: Invoke fcntl to unlock the file
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_UNLCK, &lock) == -1){
        perror("fcntl");
        close(fd);
        return 1;
    }


	printf("Done.\n");

	close(fd);
	return 0;
}