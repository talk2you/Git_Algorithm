#include <stdio.h>
#include <string.h>

int T, N;
long long dp[100001][4];
int mod = (long)1e9 + 9;

void init()
{
	memset(&dp, 0, sizeof(dp));
}

void input()
{
	scanf("%d", &N);
}

void solve()
{
	dp[1][1] = dp[2][2] = dp[3][2] = dp[3][1] = dp[3][3] = 1;
	
	for (int i = 4; i <= 100000; i++)
	{
		
		dp[i][1] = (dp[i - 1][2] + dp[i - 1][3]) % mod;
		dp[i][2] = (dp[i - 2][1] + dp[i - 2][3]) % mod;
		dp[i][3] = (dp[i - 3][1] + dp[i - 3][2]) % mod;
	}
}

int main(void)
{
	int result;
	scanf("%d", &T);

	init();
	solve();

	for (int t = 1; t < T + 1; t++)
	{
		input();
		result = (dp[N][1] + dp[N][2] + dp[N][3]) % mod;
		printf("%ld\n", result);
	}

	return 0;
}