#include <stdio.h>

int main(void)
{
	int sum = 0;
	int a;

	for (int i = 0; i < 6; i++)
	{
		scanf("%d", &a);
		sum += a;
	}
	printf("%d\n", sum * 5);
}