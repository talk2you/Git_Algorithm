#include <stdio.h>

int dp[20];
int T;

void input()
{
	scanf("%d", &T);
}

void solve()
{
	int N;

	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;

	for (int i = 4;i <= 11;++i)
		dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
	
	for (int i = 0;i < T;++i)
	{
		scanf("%d", &N);
		printf("%d\n", dp[N]);
	}
}

int main(void)
{
	input();
	solve();	
}