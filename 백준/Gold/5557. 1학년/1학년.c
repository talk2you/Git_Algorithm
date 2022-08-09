#include <stdio.h>

int N;
int ans;

long long dp[101][21];
int arr[101];

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
}

void solve()
{
	int res;
	dp[1][arr[1]] = 1;

	for (int i = 2; i <= N-1; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			if (dp[i - 1][j])
			{
				res = j + arr[i];
				if (res >= 0 && res <= 20)
					dp[i][res] += dp[i - 1][j];

				res = j - arr[i];
				if (res >= 0 && res <= 20)
					dp[i][res] += dp[i - 1][j];
			}
		}
	}

	printf("%lld\n", dp[N-1][arr[N]]);
}

int main(void)
{
	input();
	solve();
}