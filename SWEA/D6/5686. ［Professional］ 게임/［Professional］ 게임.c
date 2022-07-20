#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Swap(a, b) {int t=a;a=b;b=t;}
#define Max(a, b) ((a>b)?(a):(b))

int N, M;
int ans;
int **map;
int *dp;

void input()
{
	scanf("%d %d", &N, &M);
	
	map = (int**)malloc(sizeof(int*)*N);
	for (register int i = 0; i < N; ++i)
		map[i] = (int*)malloc(sizeof(int)*M);
	
	for (register int r = 0; r < N; ++r)
		for (register int c = 0; c < M; ++c)
			scanf("%d", &map[r][c]);

	dp = (int*)calloc(N, sizeof(int));
}

void solve()
{
	int temp[3] = { 0, };
	for (register int r = 0; r < N; ++r)
	{
		memset(temp, 0, sizeof(temp));
		for (register int c = 0; c < M; ++c)
		{
			temp[2] = temp[0] + map[r][c];
			temp[2] = Max(temp[1], temp[2]);

			Swap(temp[0], temp[1]);
			Swap(temp[1], temp[2]);
		}
		dp[r] = temp[1];
	}

	memset(temp, 0, sizeof(temp));
	for (register int i = 0; i < N; ++i)
	{
		temp[2] = temp[0] + dp[i];
		temp[2] = Max(temp[1], temp[2]);

		Swap(temp[0], temp[1]);
		Swap(temp[1], temp[2]);
	}

	printf("%d\n", temp[1]);

	free(dp);
	for (register int i = 0; i < N; ++i)
		free(map[i]);
	free(map);
}

int main(void)
{
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int t = 1; t <= T; ++t)
	{
		input();
		printf("#%d ", t);
		solve();
	}
}