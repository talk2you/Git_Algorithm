#include <stdio.h>

#define MAX_QUE 2500
#define Max(a, b) ((a>b)?(a):(b))

int N, M;
int ans;

char map[53][53];
int visit[53][53];
int dp[53][53];

typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

void input()
{
	scanf("%d %d", &N, &M);
	
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf(" %1c", &map[r][c]);
}

int search(int _r, int _c)
{
	if (_r <= 0 || _r > N || _c <= 0 || _c > M)
		return 0;

	if (map[_r][_c] == 'H')
		return 0;

	if (visit[_r][_c])
		return -1;

	if (dp[_r][_c] > 0)
		return dp[_r][_c];

	visit[_r][_c] = 1;
	dp[_r][_c] = 0;

	for (int i = 0; i < 4; i++)
	{
		int temp_r = _r + (dir.r[i] * (map[_r][_c] - '0'));
		int temp_c = _c + (dir.c[i] * (map[_r][_c] - '0'));

		int ret = search(temp_r, temp_c);

		if (ret == -1)
			return -1;

		dp[_r][_c] = Max(dp[_r][_c], ret + 1);
	}
	visit[_r][_c] = 0;
	return dp[_r][_c];
}

void solve()
{
	int ret = search(1, 1);

	printf("%d\n", ret);
}

int main(void)
{
	input();
	solve();
}