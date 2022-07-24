#include <stdio.h>

#define MAX_QUE 500000

int R, C;
char map[53][53];

typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

typedef struct {
	int r, c;
	int who;
	int time;
}QUE;
QUE que[MAX_QUE];
int front, end;

typedef struct {
	int r, c;
}LOC;
LOC hedgehog;
LOC pool[2500];
int pool_size;

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = front - 1;
	if (temp < 0)
		temp += MAX_QUE;

	if (temp == end)
		return 1;
	return 0;
}

int push(int r, int c, int who, int time)
{
	if (isFull())
	{
		printf("full\n");
		return 0;
	}

	que[end].r = r;
	que[end].c = c;
	que[end].who = who;
	que[end++].time = time;
	end %= MAX_QUE;
	return 1;
}

int pop(int *r, int *c, int *who, int *time)
{
	if (isEmpty())
	{
		printf("empty\n");
		return 0;
	}

	*r = que[front].r;
	*c = que[front].c;
	*who = que[front].who;
	*time = que[front++].time;
	front %= MAX_QUE;
	return 1;
}

void input()
{
	scanf("%d %d", &R, &C);

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf(" %1c", &map[r][c]);

			if (map[r][c] == 'S')
				hedgehog.r = r, hedgehog.c = c;
			if (map[r][c] == '*')
				pool[pool_size].r = r, pool[pool_size++].c = c;
		}
	}
}

void solve()
{
	// 고슴도치랑 물웅덩이 넣어줌
	push(hedgehog.r, hedgehog.c, 1, 0);
	for (int i = 0; i < pool_size; i++)
		push(pool[i].r, pool[i].c, 2, 0);

	int r, c, who, prev_time = 0, time = 0;
	int temp_r, temp_c;
	int move_flag = 0;

	while (pop(&r, &c, &who, &time))
	{
		if (time > 0 && time - prev_time == 1)
		{
			/*for (int i = 0; i < R; i++)
			{
				for (int j = 0; j < C; j++)
					printf("%c ", map[i][j]);
				printf("\n");
			}
			printf("---------------\n");*/

			if (move_flag == 0)
			{
				printf("KAKTUS\n");
				return;
			}
			move_flag = 0;
		}

		prev_time = time;

		for (int i = 0; i < 4; i++)
		{
			temp_r = r + dir.r[i];
			temp_c = c + dir.c[i];

			if (temp_r < 0 || temp_r >= R || temp_c < 0 || temp_c >= C)
				continue;

			//고슴도치일때
			if (who == 1)
			{
				if (map[r][c] == '*')
					continue;

				if (map[temp_r][temp_c] == '.')
				{
					move_flag = 1;
					push(temp_r, temp_c, 1, time + 1);
					map[temp_r][temp_c] = '0';
				}
				else if (map[temp_r][temp_c] == 'D')
				{
					printf("%d\n", time + 1);
					return;
				}
			}
			// 물 웅덩이일때
			else if (who == 2)
			{
				if (map[temp_r][temp_c] == 'X' || map[temp_r][temp_c] == 'D' || map[temp_r][temp_c] == '*')
					continue;

				push(temp_r, temp_c, 2, time + 1);
				map[temp_r][temp_c] = '*';
			}
		}
	}
}

int main(void)
{
	input();
	solve();
}