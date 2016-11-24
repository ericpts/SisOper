#include <unistd.h>
#include <stdio.h>

int main()
{
	int d;
	scanf("%d", &d);
	fprintf(stderr, "in main, read %d!\n", d);
	printf("%d\n", d);
	fflush(stdout);

	execl("child", (char*)NULL);

	return 0;
}
