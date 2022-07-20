#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;

int list[2][100003];
int dp[2][100003];
int ans;

void init()
{
	ans = 0;
	memset(dp, 0, sizeof(dp));
}

void input()
{
	scanf("%d", &N);
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < N; ++c)
			scanf("%d", &list[r][c]);
}

void solve()
{
	dp[0][0] = list[0][0];
	ans = Max(ans, dp[0][0]);
	dp[1][0] = list[1][0];
	ans = Max(ans, dp[1][0]);
	dp[0][1] = list[1][0] + list[0][1];
	ans = Max(ans, dp[0][1]);
	dp[1][1] = list[0][0] + list[1][1];
	ans = Max(ans, dp[1][1]);

	for (int c = 2; c < N; ++c)
	{
		for (int r = 0; r < 2; ++r)
		{
			if (r == 0)
			{
				dp[r][c] = list[r][c] + dp[r][c - 2];
				dp[r][c] = Max(dp[r][c], list[r][c] + dp[r + 1][c - 2]);
				dp[r][c] = Max(dp[r][c], list[r][c] + dp[r + 1][c - 1]);
			}
			else
			{
				dp[r][c] = list[r][c] + dp[r][c - 2];
				dp[r][c] = Max(dp[r][c], list[r][c] + dp[r - 1][c - 2]);
				dp[r][c] = Max(dp[r][c], list[r][c] + dp[r - 1][c - 1]);
			}

			ans = Max(ans, dp[r][c]);
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		solve();
	}
}