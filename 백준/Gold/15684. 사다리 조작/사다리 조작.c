#include <stdio.h>

int N, M, H;
int map[32][12];
int min_cnt = 4;

void input()
{
	int row, col;
	scanf("%d %d %d", &N, &M, &H);

	for(int i=1;i<=M;i++)
	{
		scanf("%d %d", &row, &col);
		map[row][col] = 1;
	}
}

int check()
{
	for (int c = 1; c <= N; c++)
	{
		int ch = c;
		for (int r = 1; r <= H; r++)
		{
			// 사다리를 만나면 행 이동
			if (map[r][ch] == 1)
				ch++;
			else if (map[r][ch - 1] == 1)
				ch--;
		}
		if (ch != c)
			return 0;
	}
	return 1;
}

void dfs(int _n, int _r, int _c)
{
	if (min_cnt <= _n)
		return;

	if (check())
	{
		min_cnt = _n;
		return;
	}

	if (_n == 3)
		return;
	
	for (int r = _r; r <= H; r++)
	{
		for (int c = _c; c <= N; c++)
		{
			if (map[r][c] == 0 && map[r][c - 1] == 0 && map[r][c + 1] == 0)
			{
				map[r][c] = 1;
				dfs(_n + 1, r, c);
				map[r][c] = 0;
			}
		}
		_c = 1;
	}
	
}

void solve()
{
	dfs(0, 1, 1);
	if (min_cnt == 4)
		min_cnt = -1;
	printf("%d\n", min_cnt);
}

int main(void)
{
	input();
	solve();
}