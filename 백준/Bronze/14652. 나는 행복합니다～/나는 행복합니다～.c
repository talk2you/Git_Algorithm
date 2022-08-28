#include <stdio.h>

int N, M, K;

void input()
{
	scanf("%d %d %d", &N, &M, &K);
	printf("%d %d\n", K / M, K%M);
}

int main(void)
{
	input();
}