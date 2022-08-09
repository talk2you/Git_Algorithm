#include <stdio.h>

int H, W, N;
char list[1001][1001];
int dp[1001][1001];

void input()
{
	scanf("%d %d %d", &H, &W, &N);

	for (int h = 1; h <= H; h++)
	{
		for (int w = 1; w <= W; w++)
		{
			scanf("%hhd", &list[h][w]);
		}
	}
}

void solve()
{
	dp[1][1] = N - 1;

	for (int h = 1; h <= H; h++)
	{
		for (int w = 1; w <= W; w++)
		{
			dp[h][w] += dp[h - 1][w] / 2;
			dp[h][w] += dp[h][w - 1] / 2;

			if (list[h - 1][w] == 0 && dp[h - 1][w] % 2 == 1)
				dp[h][w]++;
			if (list[h][w - 1] == 1 && dp[h][w - 1] % 2 == 1)
				dp[h][w]++;
		}
	}

	int h=1, w=1;
	while (1)
	{
		if (dp[h][w] % 2 == 1)
			list[h][w] ^= 1;

		if (list[h][w] == 1)
			w++;
		else
			h++;

		if (h > H || w > W)
		{
			printf("%d %d\n", h, w);
			return;
		}
	}
}

int main(void)
{
	input();
	solve();
}