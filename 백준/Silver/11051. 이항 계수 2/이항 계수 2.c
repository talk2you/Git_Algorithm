#include <stdio.h>

#define MOD	10007

int N, K;

short dp[1001][1001];

void input()
{
	scanf("%d %d", &N, &K);
}

void solve()
{
	dp[1][1] = 1;
	dp[1][0] = 1;
	for (int i = 2; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			if (j - 1 < 0)
				dp[i][j] = 1;
			else
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
		}

	printf("%d\n", dp[N][K]);
}

int main(void)
{
	input();
	solve();
}