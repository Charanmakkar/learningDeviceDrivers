#include <stdlib.h>

int main()
{
	int return_value;

	return_value = system("ps -x");
	return return_value;
}