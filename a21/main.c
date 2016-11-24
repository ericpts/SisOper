#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void print_usage(char* prog_name)
{
	printf("Usage: %s p1 p2 [pn...]", prog_name);
}

int main(int argc, char** argv)
{

	if (argc < 3) {
		print_usage(argv[0]);
		return -1;
	}

	int total_length = 0;
	for(int i = 1; i < argc; ++i) 
		total_length += strlen(argv[i]);

	total_length += (argc - 2) * 3 + 1;
	char* buffer = (char*) malloc(total_length);

	if (buffer == NULL) {
		printf("Could not allocate memory!");
		return -2;
	}

	int rem = total_length;
	char* cur = buffer;
	char* const end = buffer + total_length;

	for(int i = 1; i < argc; ++i) {
		const char* fmt = (i + 1 < argc) ? "%s | " : "%s";
		int cnt = snprintf(cur, rem, fmt, argv[i]);

		cur += cnt;
		rem -= cnt;

		assert(cur < end);
		assert(rem >= 0);
	}

	printf("%s\n", buffer);
	system(buffer);
	
	return 0;
}
