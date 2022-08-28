#include <stdio.h>

int N, K;

void input()
{
	scanf("%d %d", &N, &K);

	int a, b;
	for (int i = 0; i < N; i++)
		scanf("%d %d", &a, &b);

	printf("비와이\n");
}

int main(void)
{
	input();
}