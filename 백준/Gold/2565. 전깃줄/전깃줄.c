#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;

int line[503];
int list[103];
int dp[103];
int ans;

void input()
{
	int a, b;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a, &b);
		line[a] = b;
	}

	int size = 1;
	for (int i = 0; i <= 501; i++)
	{
		if (line[i] != 0)
			list[size++] = line[i];
	}
}

void solve()
{
	int flag = 0;
	
	for (int i = 1; i <= N; i++)
	{
		dp[i] = 1;

		for (int j = 1; j < i; j++)
		{
			if (list[i] > list[j])
				dp[i] = Max(dp[i], dp[j] + 1);
		}
		ans = Max(ans, dp[i]);
	}
	
	printf("%d\n", N - ans);
}

int main(void)
{
	input();
	solve();
}