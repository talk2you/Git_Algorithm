#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))

int N;
int ans;

int list[3][1003];
int dp[3][1003];

void input()
{
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
		scanf("%d %d %d", &list[0][i], &list[1][i], &list[2][i]);
}

void solve()
{
	dp[0][0] = list[0][0];
	dp[1][0] = list[1][0];
	dp[2][0] = list[2][0];

	for (int i = 1; i < N; i++)
	{
		dp[0][i] = Min(dp[1][i - 1], dp[2][i - 1]) + list[0][i];
		dp[1][i] = Min(dp[0][i - 1], dp[2][i - 1]) + list[1][i];
		dp[2][i] = Min(dp[0][i - 1], dp[1][i - 1]) + list[2][i];
	}

	ans = dp[0][N - 1];
	ans = Min(ans, dp[1][N - 1]);
	ans = Min(ans, dp[2][N - 1]);
	
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}