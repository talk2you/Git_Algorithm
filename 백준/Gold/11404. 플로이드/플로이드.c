#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))

int N, M;
int map[103][103];

void input()
{
	int a, b, cost;
	scanf("%d %d", &N, &M);

	for (int i = 0;i < M;i++)
	{
		scanf(" %d %d %d", &a, &b, &cost);
		if (map[a][b] == 0)
			map[a][b] = cost;
		else
			map[a][b] = Min(map[a][b], cost);
	}
}

void solve()
{
	for (int k = 1;k <= N;++k)
		for (int r = 1;r <= N;++r)
			for (int c = 1;c <= N;++c)
				if (map[r][k] != 0 && map[k][c] != 0)
				{
					if (r == c)
						continue;

					if (map[r][c] == 0)
						map[r][c] = map[r][k] + map[k][c];
					else
						map[r][c] = Min(map[r][c], map[r][k] + map[k][c]);
				}

	for (int r = 1;r <= N;++r)
	{
		for (int c = 1;c <= N;++c)
			printf("%d ", map[r][c]);
		printf("\n");
	}
}

int main(void)
{
	input();
	solve();
}