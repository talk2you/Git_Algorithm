#include <stdio.h>

#define MOD 10007

int N;

short dp[1003];

void input()
{
	scanf("%d", &N);
}

void solve()
{
	dp[1] = 1;
	dp[2] = 2;

	for (register int i = 3;i <= N;++i)
		dp[i] = (dp[i - 2] + dp[i - 1]) % MOD;

	printf("%d\n", dp[N]);
}

int main(void)
{
	input();
	solve();
}