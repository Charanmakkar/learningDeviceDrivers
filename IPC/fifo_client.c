#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define FIFO_FILE "fifo"

void broken_pipe(int sno)
{
    printf("Broken Pipe %d. Let's continue ...\n", sno);
}

int main(int argc, char *argv[])
{
    int cnt = 1, i;
    FILE *fp;
	struct sigaction sa;

    if ((argc != 2) && (argc != 3))
    {
        printf("Usage: fifoclient <string> [ <cnt> ]\n");
        return 1;
    }
    if (argc == 3)
    {
        cnt = atoi(argv[2]);
    }
    //TODO 1: Register the handler for SIGPIPE

    //TODO 2: Create the FIFO using mknod
	//Use flags S_IFIFO, S_IRUSR and S_IWUSR

    printf("\nSending %d \"%s\" to %s ", cnt, argv[1], FIFO_FILE);
    fflush(stdout);
    //TODO 3: Open the FIFO file using fopen in write mode

	for (i = 0; i < cnt; i++)
    {
        // TODO 4: Write to the FIFO using fputs
		fflush(fp);
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(" done\n");
    fclose(fp);

    return 0;
}
