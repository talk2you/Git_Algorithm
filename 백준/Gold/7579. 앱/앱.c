#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N, M;
int ans = -1;

int memory[101];
int cost[101];
int dp[101][10001];
int sum;

void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &memory[i]);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &cost[i]);
		sum += cost[i];
	}
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j <= sum; j++)
		{
			if (j - cost[i] >= 0)
				dp[i][j] = Max(dp[i][j], dp[i - 1][j - cost[i]] + memory[i]);

			dp[i][j] = Max(dp[i][j], dp[i - 1][j]);

			if (i == N)
			{
				if (ans == -1)
				{
					if (dp[i][j] >= M)
						ans = j;
				}
			}
		}
	}
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}