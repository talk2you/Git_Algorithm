#include <stdio.h>

int N, M, K;
int x, y;
int cmd[1000];
int map[20][20];
int top_list[1000];

typedef struct {
	int y[4], x[4];
}DIR;
// 우, 좌, 상, 하
DIR dir = { {0,0,-1,1}, {1,-1,0,0} };

int face0, face1, face2, face3, face4, face5;
int *dice[6] = {&face0, &face1, &face2, &face3, &face4, &face5};

void input()
{
	scanf("%d %d %d %d %d", &N, &M, &y, &x, &K);
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 0; i < K; i++)
		scanf("%d", &cmd[i]);
}

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

void dice_roll(int cmd)
{
	int *temp;

	if (cmd == 1)
	{
		temp = dice[1];
		dice[1] = dice[5];
		dice[5] = dice[3];
		dice[3] = dice[2];
		dice[2] = temp;
	}
	else if (cmd == 2)
	{
		temp = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[3];
		dice[3] = dice[5];
		dice[5] = temp;
	}
	else if (cmd == 3)
	{
		temp = dice[0];
		dice[0] = dice[2];
		dice[2] = dice[4];
		dice[4] = dice[5];
		dice[5] = temp;
	}
	else if (cmd == 4)
	{
		temp = dice[0];
		dice[0] = dice[5];
		dice[5] = dice[4];
		dice[4] = dice[2];
		dice[2] = temp;
	}
}

void solve()
{
	int now_x, now_y;
	int idx = 0;

	for (int i = 0; i < K; i++)
	{
		now_x = x; 
		now_y = y;

		now_x += dir.x[cmd[i] - 1];
		now_y += dir.y[cmd[i] - 1];
		//printf("%d %d\n", now_x, now_y);
		if (now_x >= M || now_x < 0 || now_y >= N || now_y < 0)
		{
			//printf("out!\n");
			continue;
		}

		x = now_x;
		y = now_y;
		dice_roll(cmd[i]);

		if (map[y][x] == 0)
			map[y][x] = *dice[5];
		else
		{
			*dice[5] = map[y][x];
			map[y][x] = 0;
		}
		/*printf("top: %d, bottom: %d, front: %d, back: %d, left: %d, right: %d\n",
			*dice[2], *dice[5], *dice[4], *dice[0], *dice[1], *dice[3]);*/
		//printf("%d ", *dice[2]);
		top_list[idx++] = *dice[2];
	}
	//printf("\n");

	if (idx == 0)
		printf("0\n");
	else
	{
		for (int i = 0; i < idx; i++)
		{
			printf("%d ", top_list[i]);
		}
		printf("\n");
	}
}

int main(void)
{
	input();
	//print_map();
	solve();
	return 0;
}