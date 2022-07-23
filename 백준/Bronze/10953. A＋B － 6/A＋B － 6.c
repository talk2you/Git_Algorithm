#include <stdio.h>

int main(void)
{
	int T;
	int a, b;
	char dot;

	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf(" %d%1c%d", &a, &dot, &b);
		printf("%d\n", a + b);
	}
}