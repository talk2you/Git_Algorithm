#include <stdio.h>

int N;

int main(void)
{
	scanf("%d", &N);
	printf("%d %d\n", N * 78 / 100, N - N * 22 / 5 / 100);
}