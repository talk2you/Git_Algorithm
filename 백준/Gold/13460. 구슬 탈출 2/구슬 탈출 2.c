#include <stdio.h>
#include <string.h>

typedef struct {
	int x[4], y[4];
}DIR;
DIR dir = { {0,0,-1,1},{-1,1,0,0} };

typedef struct {
	int x, y;
}COORD;

int N, M;
char map[11][11];
int visit[11][11][11][11];
int map_cnt[11][11][11][11];

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}

void print_visit()
{
	printf("visit : \n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < N; k++)
			{
				for (int l = 0; l < M; l++)
				{
					if (visit[i][j][k][l])
						printf("r(%d %d), b(%d %d)\n", i, j, k, l);
				}
			}
		}
	}
}

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", &map[i]);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < N; k++)
			{
				for(int l=0;l<M;l++)
					map_cnt[i][j][k][l] = 99999;
			}
		}
	}
}

void find_item(COORD *r, COORD *b, COORD *goal)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (map[y][x] == 'R')
			{
				r->x = x;
				r->y = y;
			}
			if (map[y][x] == 'B')
			{
				b->x = x;
				b->y = y;
			}
			if (map[y][x] == 'O')
			{
				goal->x = x;
				goal->y = y;
			}
		}
	}

	//printf("r(%d %d), b(%d %d), goal(%d %d)\n", r->x, r->y, b->x, b->y, goal->x, goal->y);
}

int rotate_result(COORD *temp, COORD *r, int i)
{
	int calc_x = 0, calc_y = 0;
	int cnt = 0;

	memcpy(temp, r, sizeof(COORD));
	calc_x = temp->x;
	calc_y = temp->y;

	while (1)
	{
		calc_x += dir.x[i];
		calc_y += dir.y[i];

		if (map[calc_y][calc_x] != '#' || map[calc_y][calc_x] == 'O')
		{
			temp->x = calc_x;
			temp->y = calc_y;
			cnt++;
			if (map[calc_y][calc_x] == 'O')
				break;
		}
		else
			break;
	}

	return cnt;
}

void solve(COORD *r, COORD *b, COORD *goal, int cnt)
{
	COORD temp_r, temp_b;
	int temp_cnt = cnt + 1;
	int r_cnt, b_cnt;

	visit[r->y][r->x][b->y][b->x] = 1;
	if (map_cnt[r->y][r->x][b->y][b->x] > temp_cnt)
		map_cnt[r->y][r->x][b->y][b->x] = temp_cnt;

	for (int i = 0; i < 4; i++)
	{
		r_cnt = rotate_result(&temp_r, r, i);
		b_cnt = rotate_result(&temp_b, b, i);

		if(temp_r.x == temp_b.x && temp_r.y == temp_b.y)
		{
			if (temp_r.x == goal->x && temp_r.y == goal->y)
				continue;
			if (r_cnt < b_cnt)
			{
				temp_b.x += -dir.x[i];
				temp_b.y += -dir.y[i];
			}
			else
			{
				temp_r.x += -dir.x[i];
				temp_r.y += -dir.y[i];
			}
		}
		if (temp_b.x == goal->x && temp_b.y == goal->y)
			continue;

		if (visit[temp_r.y][temp_r.x][temp_b.y][temp_b.x])
		{
			/*printf("cnt comp >> r: %d %d, b: %d %d | %d <> %d\n", temp_r.x, temp_r.y, temp_b.x, temp_b.y,
				map_cnt[temp_r.y][temp_r.x][temp_b.y][temp_b.x],temp_cnt);*/
			if(map_cnt[temp_r.y][temp_r.x][temp_b.y][temp_b.x] <= temp_cnt)
				continue;
		}

		visit[temp_r.y][temp_r.x][temp_b.y][temp_b.x] = 1;
		map_cnt[temp_r.y][temp_r.x][temp_b.y][temp_b.x] = temp_cnt;

		/*printf("r(%d %d) %d ", temp_r.x, temp_r.y, r_cnt);
		printf("b(%d %d) %d\n", temp_b.x, temp_b.y, b_cnt);
		printf("---- %d\n", temp_cnt);*/

		/*if (temp_r.x == goal->x && temp_r.y == goal->y)
		{
			if(!(temp_b.x == goal->x && temp_b.y == goal->y))
				printf("goal! %d\n", temp_cnt);
		}*/
		
		solve(&temp_r, &temp_b, goal, temp_cnt);
	}
}

int main(void)
{
	COORD r, b, goal;
	int result = 99999;

	input();
	find_item(&r, &b, &goal);
	solve(&r, &b, &goal, 0);
	//print_map();
	//print_visit();

	//printf("result:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if(result > map_cnt[goal.y][goal.x][i][j])
				result = map_cnt[goal.y][goal.x][i][j];
		}
	}
	if (result > 10)
		result = -1;
	printf("%d\n", result);
    
    return 0;
}