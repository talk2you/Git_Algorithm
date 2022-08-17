#include <stdio.h>
#include <string.h>

#define max(a, b) ((a>b)?(a):(b))
#define min(a, b) ((a<b)?(a):(b))

int T, N;
int list[1001];

int dp[1001][1001];

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

int search(int left, int right, int turn)
{
	if (left > right)
		return 0;

	if (dp[left][right])
		return dp[left][right];

	if (turn % 2)
	{
		int res1 = list[left] + search(left + 1, right, turn + 1);
		int res2 = list[right] + search(left, right - 1, turn + 1);
		return dp[left][right] = max(res1, res2);
	}
	else
	{
		int res1 = search(left + 1, right, turn + 1);
		int res2 = search(left, right - 1, turn + 1);
		return dp[left][right] = min(res1, res2);
	}
}

void solve()
{
	search(0, N - 1, 1);

	printf("%d\n", dp[0][N-1]);
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		input();
		solve();
		memset(dp, 0, sizeof(dp));
	}
}