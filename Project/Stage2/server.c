#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <sys/shm.h>

#include "sig.h"
#include "em_registers.h"
#include "sem.h"
#include "sock.h"

#define FIFO_NAME "myfifo"
#define KEY 0x12345 // Would retrieve the same if not detached
#define PORT_NUM 2000


void sig(int signum)
{
    printf("Received signal %d\n", signum);
}

int get_lib_count()
{
    int libcount;
    // TODO 6: Open the pipe with ls lib*.so and return the lib count
    
    return -1;
}

void *shm_allocate(key_t key, size_t shm_size,
        int flags, int *shm_id, void *addr)
{
    // TODO 7: Allocate the shared memory
    printf("The segment id: %d (0x%X)\n", *shm_id, *shm_id);

    // TODO 8: Attach the shared memory
	return NULL;
}

int main(int argc, char *argv[])
{
    int fd, num, libcount;
    struct em_registers reg;
    int shm_id;
    char *shm_addr = NULL;
    const int shm_size = sizeof(struct em_registers);
    int sem_id;
	// TODO 14: Uncomment the below declarations
/*
    int sock_fd;
    char *ip_addr;
    int eth_fd;
    char remote_ip[16];
*/
	// TODO 15: Uncomment the below lines to make sure that the ip address is passed and assign argv[1] to ip_addr
/*
	if (argc != 2)
    {
        printf("Usage: %s <ip addr>\n", argv[0]);
        return 1;
    }

    ip_addr = argv[1];
*/

    memset(&reg, 0, sizeof(struct em_registers));
    reg.va = 440;
    reg.vb = 438;
    reg.vc = 430;
    
    // TODO 1: Register handler sig for SIGINT and SIGPIPE

    // TODO 2: Get the count of lib*.so files using pipe
    if (libcount > 0)
    {
        printf("Library count = %d\n", libcount);
    }

	// TODO 9: Allocate the shared memory using shm_allocate
    printf("Shared memory attached at address %p\n", shm_addr);

    // TODO 10: Allocate the binary semaphore using binary_semaphore_allocate
    printf("Semaphore created with id: %d\n", sem_id);

    // TODO 11: Initialize the binary semaphore with binary_semaphore_set
    
    // TODO 3: Create the FIFO
	// TODO 16: Open the socket using open_socket, instead of creating the FIFO
    
    printf("Waiting for readers ...\n");
	// TODO 17: Replace opening FIFO with getting the client socket using get_socket assign it to eth_fd
    // TODO 4: Open the FIFO
	printf("Got a reader - Sending registers\n");

	// TODO 12: Get the semaphore using binary_semaphore_get
    while (1) 
    {
        // TODO 13: Synchronize the access to shared memory using semaphore and
		// Copy the EM registers from the shared memory

		// TODO 18: Write into the socket by suing write_eth instead of writing into the FIFO
        // TODO 5: Write EM Registers (struct em_registers) to the FIFO
        
        printf("Sent shared registers\n");
        sleep(5);
    }
	// TODO 19: Comment the below line
    close(fd);

    return 0;
}
