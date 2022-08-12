#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
int ans;
int dp[501][501];

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			int a;
			scanf("%d", &a);

			if (j - 1 >= 0)
				dp[i][j] = Max(dp[i][j], dp[i - 1][j - 1] + a);
			dp[i][j] = Max(dp[i][j], dp[i - 1][j] + a);

			ans = Max(ans, dp[i][j]);
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
}