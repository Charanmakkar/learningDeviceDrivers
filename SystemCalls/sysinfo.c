#include <linux/kernel.h>
//#include <linux/sys.h>
#include <stdio.h>
#include <sys/sysinfo.h>


int main() {
	const long minute = 60;
	const long hour = minute *60;
	const long day = hour * 24;
	const long megabyte = 1024 * 1024;
	struct sysinfo si;
	
	//TODO 1: Get the system info using sysinfo system call
	sysinfo(&si);
	
	// printf("1 min Load %ld\n ", si.loads[0]);
	// printf("5 min Load %ld\n ", si.loads[1]);
	// printf("5 min Load %ld\n ", si.loads[2]);

	//TODO 2: Print the total up time
	printf("Uptime %ld minutes\n", si.uptime / minute );

	//TODO 3: Print the total RAM in MB
	// printf("Total RAM %ld\n", si.totalram / 1024 / 1024);
	printf("Total RAM %ld MB\n", si.totalram / megabyte);
	
	//TODO 4: Print the Free Ram 
	// printf("Free RAM %ld\n", si.freeram / 1024 / 1024);
	printf("Free RAM %ld MB\n", si.freeram / megabyte);
	
	//TODO 5: Print the process count 
	printf("Process : %d\n", si.procs);


	return 0;
}
