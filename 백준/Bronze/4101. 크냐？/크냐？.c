#include <stdio.h>

void input()
{
	int a, b;
	while (1)
	{
		scanf("%d %d", &a, &b);
		if (a == b && b == 0)
			return;

		if (a > b)
			printf("Yes\n");
		else
			printf("No\n");
	}
}

int main(void)
{
	input();
}