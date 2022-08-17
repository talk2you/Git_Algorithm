#include <stdio.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))

int N, K;
int dp[201][201];
int list[201];

void input()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

int search(int start, int end)
{
	if (start == end)
		return 0;

	if (dp[start][end])
		return dp[start][end];

	int ret = INF;

	for (int i = start; i < end; i++)
	{
		int temp;
		if (list[start] == list[i + 1])
			temp = 0;
		else 
			temp = 1;

		ret = Min(ret, search(start, i) + search(i + 1, end) + temp);
	}

	dp[start][end] = ret;
	return ret;
}

void solve()
{
	printf("%d\n", search(0, N - 1));
}

int main(void)
{
	input();
	solve();
}