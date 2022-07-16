#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))

int N;
int dp[1000003];

void input()
{
	scanf("%d", &N);
}

void solve()
{
	for (register int i = 2;i <= N;++i)
	{
		dp[i] = dp[i - 1] + 1;

		if (i % 3 == 0)
			dp[i] = Min(dp[i], dp[i / 3] + 1);
		if (i % 2 == 0)
			dp[i] = Min(dp[i], dp[i / 2] + 1);		
	}

	printf("%d\n", dp[N]);
}

int main(void)
{
	input();
	solve();
}