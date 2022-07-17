#include <stdio.h>

#define MOD 10007

int N;
int ans;
int dp[103][103];

void input()
{
	scanf("%d", &N);
}

void solve()
{
	dp[2][1] = 2;

	for (register int r = 3; r <= N; ++r)
		for (register int c = 1; c <= N - 1; ++c)
		{
			dp[r][c] = dp[r - 1][c] * 2 + dp[r - 1][c - 1] + dp[r - 1][c + 1];
			dp[r][c] %= MOD;
		}

	for (register int i = 1; i < N; ++i)
	{
		ans += dp[N][i];
		ans %= MOD;
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}