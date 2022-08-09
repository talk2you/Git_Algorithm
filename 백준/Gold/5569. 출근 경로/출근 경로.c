#include <stdio.h>

#define MOD 100000

int w, h;
int dp[101][101][4];

void input()
{
	scanf("%d %d", &w, &h);
}

void solve()
{
	for (int r = 1; r <= h; r++)
		dp[r][1][0] = 1;

	for (int c = 1; c <= w; c++)
		dp[1][c][2] = 1;

	for (int r = 2; r <= h; r++)
	{
		for (int c = 2; c <= w; c++)
		{
			dp[r][c][0] = (dp[r - 1][c][0] + dp[r - 1][c][1]) % MOD;
			dp[r][c][1] = dp[r - 1][c][2];
			dp[r][c][2] = (dp[r][c - 1][2] + dp[r][c - 1][3]) % MOD;
			dp[r][c][3] = dp[r][c - 1][0];
		}
	}

	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += dp[h][w][i];

	printf("%d\n", sum % MOD);
}

int main(void)
{
	input();
	solve();
}