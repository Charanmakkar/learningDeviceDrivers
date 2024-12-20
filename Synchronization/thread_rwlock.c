#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define READERS_CNT 3
#define DONE return NULL
//#define DONE do { printf("Error: %d\n", rc); return NULL; } while (0)

static pthread_rwlock_t rwlock;
static char resource[100] = "Default value";

void *reader(void *arg)
{
	int no = (int)(long)(arg);
	int rc, i;

	printf("Reader #%d\n", no);
	while (1)
	{
		//TODO 4: Acquire the read lock

		printf("r%d: ", no);
		for (i = 0; resource[i]; i++)
		{
			printf("%c", resource[i]);
			if (i % 5 == 4)
			{
				printf("\nr%d: ", no);
				sleep(1 + no);
			}
		}
		if ((i - 1) % 5 != 4)
		{
			printf("\n");
		}

		//TODO 5: Release the read lock

		sleep(5);
	}
	printf("r%d: Done\n", no);

	return NULL;
}

void *writer(void *arg)
{
	int rc, i;

	printf("Writer\n");
	while (1)
	{
		//TODO 2: Acquire the write lock

		sprintf(resource, "%u", rand());
		for (i = 0; resource[i]; i++)
		{
			resource[i] += (- '0' + 'A');
		}
		printf(" w: Updated resource with \"%s\"\n", resource);

		//TODO 3: Release the write lock
		sleep(2);
	}
	printf(" w: Done\n");

	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	pthread_t thread_rd[READERS_CNT], thread_wr;

	printf("main: Initialize the read write lock\n");
	//TODO 1: Initialize the reader/writer lock

	printf("main: Create the reader threads\n");
	for (i = 0; i < READERS_CNT; i++)
	{
		if (pthread_create(&thread_rd[i], NULL, &reader, (void *)(long)i))
		{
			pthread_rwlock_destroy(&rwlock);
			return 2;
		}
	}

	printf("main: Create the writer thread\n");
	if (pthread_create(&thread_wr, NULL, &writer, NULL))
	{
		pthread_rwlock_destroy(&rwlock);
		return 3;
	}

	printf("main: Wait for the threads\n");
	pthread_join(thread_wr, NULL);
	for (i = READERS_CNT - 1; i >= 0; i--)
	{
		pthread_join(thread_rd[i], NULL);
	}

	//TODO 6: Deallocate the lock

	printf("main: Completed\n");

	return 0;
}
