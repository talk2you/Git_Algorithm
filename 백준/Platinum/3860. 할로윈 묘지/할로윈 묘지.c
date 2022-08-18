#include <stdio.h>
#include <string.h>

#define QUE_SIZE 9000
#define INF 1<<30

int W, H;
int G, E;

typedef struct {
	int x, y;
	int stat;
	int toX, toY;
	int cnt;
	int in_cnt;
	int t;
}MAP;
MAP map[30][30];

enum STAT{empty, tomb, ghost_hole};

typedef struct {
	int x, y, cnt;
}QUE;
QUE que[QUE_SIZE];
int start, end;

typedef struct {
	int x[4], y[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

void init()
{
	memset(map, 0, sizeof(map));
	for (int r = 0; r < 30; r++)
		for (int c = 0; c < 30; c++)
			map[r][c].cnt = INF;
	
	map[0][0].cnt = 0;
	start = 0;
	end = 0;
}

int isEmpty()
{
	if (start == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = start - 1;
	if (temp < 0)
		temp += QUE_SIZE;

	if (temp == end)
		return 1;
	return 0;
}

int push(int x, int y, int cnt)
{
	if (isFull())
		return 0;

	que[end].x = x;
	que[end].y = y;
	que[end++].cnt = cnt;
	end %= QUE_SIZE;
	return 1;
}

int pop(int *x, int *y, int *cnt)
{
	if (isEmpty())
		return 0;

	*x = que[start].x;
	*y = que[start].y;
	*cnt = que[start++].cnt;
	start %= QUE_SIZE;
	return 1;
}

int input()
{
	int x, y, toX, toY, t;
	scanf("%d %d", &W, &H);

	if (W == 0 && H == 0)
		return 0;

	scanf("%d", &G);

	for (int i = 0; i < G; i++)
	{
		scanf("%d %d", &x, &y);
		map[y][x].stat = 1;
	}

	scanf("%d", &E);
	for (int i = 0; i < E; i++)
	{
		scanf("%d %d %d %d %d", &x, &y, &toX, &toY, &t);
		map[y][x].stat = 2;
		map[y][x].toX = toX;
		map[y][x].toY = toY;
		map[y][x].t = t;

	}

	return 1;
}

void solve()
{
	push(0, 0, 0);

	int x, y, cnt;

	while (pop(&x, &y, &cnt))
	{
		if (x == W - 1 && y == H - 1)
			continue;

		for (int i = 0; i < 4; i++)
		{
			int temp_x = x + dir.x[i];
			int temp_y = y + dir.y[i];

			if (temp_x < 0 || temp_y < 0 || temp_x >= W || temp_y >= H)
				continue;

			if (map[temp_y][temp_x].stat != tomb)
			{
				if (map[temp_y][temp_x].stat == ghost_hole)
				{
					int temp_cnt = cnt + 1;
					while (1)
					{						
						if (map[temp_y][temp_x].stat != ghost_hole)
						{
							if (map[temp_y][temp_x].cnt > temp_cnt)
							{
								map[temp_y][temp_x].cnt = temp_cnt;
								//printf("push : %d %d %d\n", temp_x, temp_y, temp_cnt);
								push(temp_x, temp_y, temp_cnt);
							}
							break;
						}

						//printf("%d %d %d %d >> ", temp_x, temp_y, map[temp_y][temp_x].cnt, temp_cnt);

						if (map[temp_y][temp_x].cnt <= temp_cnt)
						{
							//printf("break\n");
							break;
						}

						map[temp_y][temp_x].in_cnt++;
						if (map[temp_y][temp_x].in_cnt > W*H)
						{
							printf("Never\n");
							return;
						}
						/*if (temp_cnt < (W*H*map[temp_y][temp_x].t))
						{
							printf("Never\n");
							return;
						}*/

						map[temp_y][temp_x].cnt = temp_cnt;

						int toX = map[temp_y][temp_x].toX;
						int toY = map[temp_y][temp_x].toY;
						int toCnt = temp_cnt + map[temp_y][temp_x].t;

						//printf("%d %d %d\n", toX, toY, toCnt);

						temp_x = toX;
						temp_y = toY;
						temp_cnt = toCnt;
					}
				}
				else
				{
					//printf("%d %d %d %d\n", temp_x, temp_y, map[temp_y][temp_x].cnt, cnt);
					if (map[temp_y][temp_x].cnt > cnt + 1)
					{
						map[temp_y][temp_x].cnt = cnt + 1;
						push(temp_x, temp_y, cnt + 1);
					}
				}				
			}
		}
	}
		
	if (map[H - 1][W - 1].cnt == INF)
		printf("Impossible\n");
	else
		printf("%d\n", map[H - 1][W - 1].cnt);
}

int main(void)
{
	while (1)
	{
		init();
		int ret = input();
		if (ret == 0)
			return;
		solve();
	}
}
