#include <stdio.h>

int N;
int dp[31];

void input()
{
	scanf("%d", &N);
}

void solve()
{
	dp[0] = 1;
	dp[2] = 3;
	dp[4] = 11;
	
	for(int i = 4; i <= N; i += 2)
	{
		for (int j = i-2; j >= 0; j -= 2)
		{
			if (i - 2 == j)
				dp[i] = dp[j] * 3;
			else
				dp[i] += dp[j] * 2;
		}
	}
}

int main(void)
{
	input();
	solve();
	printf("%d\n", dp[N]);

	return 0;
}