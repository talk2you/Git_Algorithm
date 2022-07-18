#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N, K;

typedef struct {
	int w, v;
}ITEM;
ITEM item[103];

int dp[103][1000003];

void input()
{
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++)
		scanf("%d %d", &item[i].w, &item[i].v);
}

void solve()
{
	for (int r = 1; r <= N; ++r)
	{
		for (int c = 1; c <= K; ++c)
		{
			if (c - item[r].w >= 0)
				dp[r][c] = Max(dp[r - 1][c], dp[r - 1][c - item[r].w] + item[r].v);
			else
				dp[r][c] = dp[r - 1][c];
		}
	}

	printf("%d\n", dp[N][K]);
}

int main(void)
{
	input();
	solve();
}