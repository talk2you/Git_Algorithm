#include <stdio.h>

int N, S;

void input()
{
	while (1)
	{
		if (scanf("%d %d", &N, &S) == EOF)
			return;
		printf("%d\n", S / (1 + N));
	}
}

int main(void)
{
	input();
}