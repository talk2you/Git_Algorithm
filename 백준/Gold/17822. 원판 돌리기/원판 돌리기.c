#include <stdio.h>
#include <string.h>

int N, M, T;
int map[53][53];
int visit[53][53];

typedef struct {
	int x, d, k;
}CMD;
CMD cmd[53];

int ans = 0;

void rotate(int i, int dir, int n);
void check();

typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

void input()
{
	scanf("%d %d %d", &N, &M, &T);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	for (int i = 0; i < T; i++)
	{
		scanf("%d %d %d", &cmd[i].x, &cmd[i].d, &cmd[i].k);
	}
}

void print_map()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}
	printf("----------------\n");
}

void rotate(int i, int dir, int n)
{
	int temp[53];
	int idx = 1;
	int temp_n = n;
	int temp_i = i;

	for (temp_i = i; temp_i <= N; temp_i += i)
	{
		temp_n = n ;
		idx = 1;

		if (dir == 0)
			temp_n = M + 1 - (n % M);
		else
			temp_n = 1+ n % M;

		for (int t = M; t >= 1; t--)
		{
			temp[idx] = map[temp_i][temp_n++];
			if (temp_n > M)
				temp_n = 1;
			idx++;
		}

		for (int t = 1; t <= M; t++)
		{
			map[temp_i][t] = temp[t];
		}
	}
}

int dfs(int val, int _r, int _c)
{
	int temp_r, temp_c;

	// 찾는 값이 다르거나 방문한적이 있으면 탈출
	if (map[_r][_c] != val || visit[_r][_c] == 1)
		return -1;

	map[_r][_c] = 0;
	visit[_r][_c] = 1;
	
	for (int i = 0; i < 4; i++)
	{
		temp_r = _r + dir.r[i];
		temp_c = _c + dir.c[i];

		if (temp_c <= 0)
			temp_c = M;
		else if (temp_c >= M + 1)
			temp_c = 1;

		if (temp_r <= 0 || temp_r >= N + 1)
			continue;

		dfs(val, temp_r, temp_c);
	}

	return 1;
}

float avg()
{
	int sum = 0, sum_cnt = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (map[r][c] > 0)
			{
				sum += map[r][c];
				sum_cnt++;
			}
		}
	}
		
	return (float)sum / (float)sum_cnt;
}

void check()
{
	int temp_r, temp_c;
	int flag = 0, init_flag = 0;;

	memset(visit, 0, sizeof(visit));

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			init_flag = 0;
			if (visit[r][c] || map[r][c] == 0)
				continue;

			visit[r][c] = 1;

			// 4방향으로 이동
			for (int i = 0; i < 4; i++)
			{
				temp_r = r + dir.r[i];
				temp_c = c + dir.c[i];

				if (temp_c <= 0)
					temp_c = M;
				else if (temp_c >= M + 1)
					temp_c = 1;

				if (temp_r <= 0 || temp_r >= N + 1)
					continue;
				
				if (dfs(map[r][c], temp_r, temp_c) == 1)
				{
					init_flag = 1;
					flag = 1;
				}
			}
			if(init_flag == 1)
				map[r][c] = 0;
		}
	}
	
	float average = avg();
	ans = 0;

	//printf("%.1f %d\n", average, flag);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (map[r][c] > 0)
			{
				// 인접한 수가 없는 경우
				if (flag == 0)
				{					
					if (map[r][c] < average)
						map[r][c] += 1;
					else if (map[r][c] > average)
						map[r][c] -= 1;
				}

				ans += map[r][c];
			}
		}
	}
	
}

void solve()
{
	for (int i = 0; i < T; i++)
	{
		rotate(cmd[i].x, cmd[i].d, cmd[i].k);
		check();
	}
}

int main(void)
{
	input();
	solve();

	printf("%d\n", ans);

	return 0;
}