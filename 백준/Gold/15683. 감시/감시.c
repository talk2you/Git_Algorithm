#include <stdio.h>
#include <string.h>

#define Min(a,b) a<b?a:b

int N, M;
char map[8][8];

typedef struct {
	int r, c;
	char n;
}LOC;
LOC cctv[8];
int cctv_cnt;

// 상우하좌
typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,0,1,0},{0,1,0,-1} };
int min_space = 64;

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			scanf(" %c", &map[r][c]);
			if ('1' <= map[r][c] && map[r][c] <= '5')
			{
				cctv[cctv_cnt].r = r;
				cctv[cctv_cnt].c = c;
				cctv[cctv_cnt].n = map[r][c];
				cctv_cnt++;
			}
		}
	}
}

void print_map(char _map[][8])
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			printf("%c ", _map[r][c]);
		}
		printf("\n");
	}
	printf("---------------\n");
}

void print_cctv()
{
	for (int i = 0; i < cctv_cnt; i++)
	{
		printf("[%d] (%d %d)\n", i, cctv[i].r, cctv[i].c);
	}
}

void draw_cctv(int _n, int _dir, char _map[][8])
{
	int temp_r, temp_c;

	temp_r = cctv[_n].r;
	temp_c = cctv[_n].c;

	switch (cctv[_n].n)
	{
	case '1':
		while (1)
		{
			temp_r += dir.r[_dir];
			temp_c += dir.c[_dir];

			if (temp_r >= 8 || temp_c >= 8 || temp_r < 0 || temp_c < 0)
				break;

			if (_map[temp_r][temp_c] == '6')
				break;
			else if (_map[temp_r][temp_c] != '0')
				continue;

			_map[temp_r][temp_c] = '#';
		}
		break;
	case '2':
		for (int i = 0; i < 2; i++)
		{
			_dir = _dir + i*2;
			_dir %= 4;
			temp_r = cctv[_n].r;
			temp_c = cctv[_n].c;
			while (1)
			{
				temp_r += dir.r[_dir];
				temp_c += dir.c[_dir];

				if (temp_r >= 8 || temp_c >= 8 || temp_r < 0 || temp_c < 0)
					break;

				if (_map[temp_r][temp_c] == '6')
					break;
				else if (_map[temp_r][temp_c] != '0')
					continue;

				_map[temp_r][temp_c] = '#';
			}
		}
		break;
	case '3':
		for (int i = 0; i < 2; i++)
		{
			_dir = _dir + i;
			_dir %= 4;
			temp_r = cctv[_n].r;
			temp_c = cctv[_n].c;
			while (1)
			{
				temp_r += dir.r[_dir];
				temp_c += dir.c[_dir];

				if (temp_r >= 8 || temp_c >= 8 || temp_r < 0 || temp_c < 0)
					break;
				if (_map[temp_r][temp_c] == '6')
					break;

				else if (_map[temp_r][temp_c] != '0')
					continue;

				_map[temp_r][temp_c] = '#';
			}
		}
		break;
	case '4':
		for (int i = 0; i < 3; i++)
		{
			_dir = _dir + i;
			_dir %= 4;
			temp_r = cctv[_n].r;
			temp_c = cctv[_n].c;
			while (1)
			{
				temp_r += dir.r[_dir];
				temp_c += dir.c[_dir];

				if (temp_r >= 8 || temp_c >= 8 || temp_r < 0 || temp_c < 0)
					break;

				if (_map[temp_r][temp_c] == '6')
					break;
				else if (_map[temp_r][temp_c] != '0')
					continue;

				_map[temp_r][temp_c] = '#';
			}
		}
		break;
	case '5':
		for (int i = 0; i < 4; i++)
		{
			_dir = _dir + i;
			_dir %= 4;
			temp_r = cctv[_n].r;
			temp_c = cctv[_n].c;
			while (1)
			{
				temp_r += dir.r[_dir];
				temp_c += dir.c[_dir];

				if (temp_r >= 8 || temp_c >= 8 || temp_r < 0 || temp_c < 0)
					break;

				if (_map[temp_r][temp_c] == '6')
					break;
				else if (_map[temp_r][temp_c] != '0')
					continue;

				_map[temp_r][temp_c] = '#';
			}
		}
		break;
	}
}

void dfs(int _n, char _map[8][8])
{
	char temp_map[8][8];
	int temp_r, temp_c;
	int space_cnt = 0;

	if (_n >= cctv_cnt)
	{
		for (int r = 0; r < N; r++)
			for (int c = 0; c < M; c++)
				if (_map[r][c] == '0')
					space_cnt++;

		//print_map(_map);
		min_space = Min(space_cnt, min_space);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		memcpy(temp_map, _map, sizeof(temp_map));
		temp_r = cctv[_n].r;
		temp_c = cctv[_n].c;
		
		if (cctv[_n].n == '2' && i >= 2)
			return;
		if (cctv[_n].n == '5' && i >= 1)
			return;
		
		draw_cctv(_n, i, temp_map);
		
		dfs(_n + 1, temp_map);
	}
}

void solve()
{
	dfs(0, map);
}

int main(void)
{
	input();
	solve();
	printf("%d\n", min_space);
}