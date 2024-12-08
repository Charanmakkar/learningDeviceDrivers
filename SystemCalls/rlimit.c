#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	struct rlimit r1, r2;

	//TODO 1: Get the current cpu limit with getrlimit
	// printf("current LIMIT %d and %d\n", );
	getrlimit(RLIMIT_CPU, &r1);
	printf("Current limit is %lu and Max limit is %lu\n", r1.rlim_cur, r1.rlim_max);
	
	//TODO 2: set the current limit to 1 sec with setrlimit
	r1.rlim_cur = 1;
	r1.rlim_max = 1;
	setrlimit(RLIMIT_CPU, &r1);

	getrlimit(RLIMIT_CPU, &r2);
	printf("Current limit is %lu and Max limit is %lu\n", r2.rlim_cur, r2.rlim_max);
	
	
	while (1);
	return 0;
}

