#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main() {
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];
	long milliseconds;

	//TODO 1: Populate the timeval structure with gettimeofday
	gettimeofday(&tv, NULL);

	//TODO 2: Use localtime to get struct tm
	ptm = localtime(&tv.tv_sec);

	//TODO 3: Use strftime to get the time in desired format
	strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm);

	milliseconds = tv.tv_usec / 1000;
	printf("%s.%03ld\n", time_string, milliseconds);
	return 0;
}
