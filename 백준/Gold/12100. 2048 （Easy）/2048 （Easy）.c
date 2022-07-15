#include <stdio.h>
#include <string.h>

int N;
typedef struct {
	int data;
	int flag;
}MAP;
MAP map[20][20];

typedef struct {
	int x[4], y[4];
}DIR;

DIR dir = { {0,0,-1,1},{-1,1,0,0} };
int max = 0;

void input()
{
	scanf("%d", &N);
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			scanf("%d", &map[y][x].data);
			if (max < map[y][x].data)
				max = map[y][x].data;
		}
}

void print_map(MAP pre_map[][20])
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			printf("(%d %d) ", pre_map[y][x].data, pre_map[y][x].flag);
		}
		printf("\n");
	}
	printf("-------------------\n");
}

void merge_table(MAP pre_map[][20], int i)
{
	switch (i)
	{
	case 0: // 상
		for (int x = 0; x < N; x++)
		{
			for (int y = 0; y < N-1; y++)
			{
				for (int k = y + 1; k < N; k++)
				{
					if (pre_map[y][x].data == 0 && pre_map[k][x].data != 0)
					{
						pre_map[y][x].data = pre_map[k][x].data;
						pre_map[y][x].flag = pre_map[k][x].flag;
						pre_map[k][x].data = 0;
						pre_map[k][x].flag = 0;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][x].data == pre_map[k][x].data )
					{
						pre_map[y][x].data *= 2;
						pre_map[y][x].flag = 1;
						pre_map[k][x].data = 0;
						pre_map[k][x].flag = 0;

						if (max < pre_map[y][x].data)
							max = pre_map[y][x].data;
						break;
					}
					else if (pre_map[y][x].data != 0 && pre_map[k][x].data != 0 && pre_map[y][x].data != pre_map[k][x].data)
						break;
				}
			}
		}
		break;
	case 1: // 하
		for (int x = 0; x < N; x++)
		{
			for (int y = N-1; y > 0; y--)
			{
				for (int k = y-1; k >= 0; k--)
				{
					if (pre_map[y][x].data == 0 && pre_map[k][x].data != 0)
					{
						pre_map[y][x].data = pre_map[k][x].data;
						pre_map[y][x].flag = pre_map[k][x].flag;
						pre_map[k][x].data = 0;
						pre_map[k][x].flag = 0;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][x].data == pre_map[k][x].data)
					{
						pre_map[y][x].data *= 2;
						pre_map[y][x].flag = 1;
						pre_map[k][x].data = 0;
						pre_map[k][x].flag = 0;
						if (max < pre_map[y][x].data)
							max = pre_map[y][x].data;
						break;
					}
					else if (pre_map[y][x].data != 0 && pre_map[k][x].data != 0 && pre_map[y][x].data != pre_map[k][x].data)
						break;
				}
			}
		}
		break;
	case 2: // 좌
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N-1; x++)
			{
				for (int k = x + 1; k <= N - 1; k++)
				{
					if (pre_map[y][x].data == 0 && pre_map[y][k].data != 0)
					{
						pre_map[y][x].data = pre_map[y][k].data;
						pre_map[y][x].flag = pre_map[y][k].flag;
						pre_map[y][k].data = 0;
						pre_map[y][k].flag = 0;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][x].data == pre_map[y][k].data)
					{
						pre_map[y][x].data *= 2;
						pre_map[y][x].flag = 1;
						pre_map[y][k].data = 0;
						pre_map[y][k].flag = 0;
						if (max < pre_map[y][x].data)
							max = pre_map[y][x].data;
						break;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][k].data != 0 && pre_map[y][x].data != pre_map[y][k].data)
						break;
				}
			}
		}
		break;
	case 3: // 우
		for (int y = 0; y < N; y++)
		{
			for (int x = N-1; x > 0; x--)
			{
				for (int k = x - 1; k >= 0; k--)
				{
					if (pre_map[y][x].data == 0 && pre_map[y][k].data != 0)
					{
						pre_map[y][x].data = pre_map[y][k].data;
						pre_map[y][x].flag = pre_map[y][k].flag;
						pre_map[y][k].data = 0;
						pre_map[y][k].flag = 0;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][x].data == pre_map[y][k].data)
					{
						pre_map[y][x].data *= 2;
						pre_map[y][x].flag = 1;
						pre_map[y][k].data = 0;
						pre_map[y][k].flag = 0;

						if (max < pre_map[y][x].data)
							max = pre_map[y][x].data;
						break;
					}
					else if (pre_map[y][x].data != 0 && pre_map[y][k].data != 0 && pre_map[y][x].data != pre_map[y][k].data)
						break;
				}
			}
		}
		break;
	}
}

void solve(MAP pre_map[][20], int cnt)
{
	MAP temp_map[20][20];
	int temp_cnt = cnt+1;

	if (temp_cnt > 5)
		return;

	for (int i = 0; i < 4; i++)
	{
		memcpy(temp_map, pre_map, sizeof(MAP)*20*20);
		merge_table(temp_map, i);

		solve(temp_map, temp_cnt);
		//print_map(temp_map);
	}
}

int main(void)
{
	input();
	solve(map, 0);
	printf("%d\n", max);

	return 0;
}