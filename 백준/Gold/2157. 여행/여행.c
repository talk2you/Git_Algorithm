#include <stdio.h>
#include <string.h>

#define MAX_QUE		1000
#define MAX(a, b)	(a>b)?(a):(b)
#define MINUS_INF	-987654321

int ans;
int N, M, K;

int dp[303][303];
int map[303][303];

void input()
{
	memset(dp, -1, sizeof(dp));
	scanf("%d %d %d", &N, &M, &K);

	int d, a, v;
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d %d", &d, &a, &v);
		if (d < a)
			map[d][a] = MAX(map[d][a], v);
	}
}

int back_tracking(int n, int cnt)
{
	if (n == N)
		return 0;
	if (cnt == M)
		return MINUS_INF;
	if (dp[n][cnt] != -1)
		return dp[n][cnt];

	int ret = MINUS_INF;

	for (int i = 1; i <= N; i++)
	{
		if (map[n][i])
		{
			ret = MAX(ret, map[n][i] + back_tracking(i, cnt + 1));
		}
	}

	dp[n][cnt] = ret;
	return ret;
}

void solve()
{
	ans = back_tracking(1, 1);
	if (ans < 0)
		ans = 0;
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}