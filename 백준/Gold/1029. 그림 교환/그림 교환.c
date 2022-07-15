#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
int map[16][16];
int cache[16][(1 << 17) + 1][10];

void input()
{
	char s[16];
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", s);
		
		for (int c = 0; c < N; c++)
			map[i][c] = s[c] - '0';
	}
}

int dfs(int cur, int visited, int prePrice)
{
	int *ret = &cache[cur][visited][prePrice];

	if (visited == (1 << N) - 1)
	{
		*ret = 1;
		return *ret;
	}

	if (*ret != 0)
		return *ret;

	*ret = 1;

	for (int next = 0; next < N; next++)
	{
		if (visited & (1 << next))
			continue;

		if (next == cur)
			continue;

		if (map[cur][next] >= prePrice)
		{
			*ret = Max(*ret, dfs(next, (visited | 1 << next), map[cur][next]) + 1);
		}
	}

	return *ret;
}

void solve()
{
	printf("%d\n", dfs(0, 1, 0));
}


int main()
{
	input();
	solve();

	return 0;
}