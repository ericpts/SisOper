#include <stdio.h>
#include <stdbool.h>

int main()
{
	int sum = 0;
	int x;
	while (scanf("%d\n", &x) == 1) {
		printf("read %d in acum\n", x);
		sum += x;
	}
	
	printf("summed up to %d\n", sum);
	return 0;
}
