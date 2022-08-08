#include <stdio.h>

int N;

int dp[31][31];

void init()
{
	dp[1][0] = 1;
	dp[1][1] = 1;

	for (int i = 2; i <= 30; i++)
		for (int j = 0; j <= i; j++)
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
}

void input()
{
	int a, b;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", dp[b][a]);
	}
}

int main(void)
{
	init();
	input();
}