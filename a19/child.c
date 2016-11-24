#include <unistd.h>
#include <stdio.h>

int main()
{
	int d;
	scanf("%d", &d);
	fprintf(stderr, "in child, read %d!\n", d);
	printf("%d\n", d);
	return 0;
}
