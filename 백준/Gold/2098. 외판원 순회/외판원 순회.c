#include <stdio.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))

int map[20][20];
int N;

int dp[16][1 << 16];

void input()
{
	scanf("%d", &N);

	for (int r = 0;r < N;++r)
		for (int c = 0;c < N;++c)
			scanf("%d", &map[r][c]);
}

int TSP(int curr, int visited)
{
	int ret = dp[curr][visited];

	if (ret != 0)
		return ret;

	if (visited == ((1 << N) - 1)) {
		if (map[curr][0] != 0)
			return map[curr][0];
		return INF;
	}

	ret = INF;

	for (int i = 0;i < N;++i)
	{
		if (map[curr][i] == 0 || (visited & (1 << i)))
			continue;

		ret = Min(ret, map[curr][i] + TSP(i, visited | 1 << i));
	}

	dp[curr][visited] = ret;
	return ret;
}

void solve()
{
	printf("%d\n", TSP(0, 1));
}

int main(void)
{
	input();
	solve();
}