#include <stdio.h>

#define MAX_N 1001
#define Max(a, b) a>b?a:b

int N;
int A[MAX_N];
int dp[MAX_N][3];
int max_l;

// 0, 1, 2
enum rel { big, bi, small };

void input()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
}

void solve()
{
	dp[1][big] = 1;
	dp[1][bi] = 1;
	dp[1][small] = 1;
	max_l = 1;

	for (int i = 2; i <= N; i++)
	{
		dp[i][big] = 1;
		dp[i][bi] = 1;
		dp[i][small] = 1;

		for (int j = 1; j < i; j++)
		{
			if (A[j] < A[i])
			{
				dp[i][big] = Max(dp[i][big], dp[j][big] + 1);
				dp[i][bi] = Max(dp[i][bi], dp[j][big] + 1);
			}
			if (A[j] > A[i])
			{
				dp[i][bi] = Max(dp[i][bi], dp[j][bi] + 1);
				dp[i][small] = Max(dp[i][small], dp[j][small] + 1);
			}
		}
		max_l = Max(max_l, dp[i][big]);
		max_l = Max(max_l, dp[i][bi]);
		max_l = Max(max_l, dp[i][small]);
	}
}

int main(void)
{
	input();
	solve();

	/*for (int i = 0; i < 3; i++)10
1 5 2 1 4 3 4 5 2 1
	{
		for (int j = 1; j <= N; j++)
		{
			printf("%d ", dp[j][i]);
		}
		printf("\n");
	}*/
	printf("%d\n", max_l);
}