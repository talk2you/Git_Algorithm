#include <stdio.h>

int R, C, M;

typedef struct SHARK{
	int r, c;
	int s, d, z;
	int live;
}SHARK;
SHARK shark[10003];
int shark_n;

int map[103][103];
SHARK *ptr[103][103];

typedef struct{
	int r[5], c[5];
}DIR;
DIR dir = { {0,-1,1,0,0},{0,0,0,1,-1} };

int start_c;
int get_fish;
int isfish;

void init_map()
{
	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
		{
			map[r][c] = 0;
			ptr[r][c] = 0;
		}
}

void input()
{
//	int r, c, s, d, z;
	scanf("%d %d %d", &R, &C, &M);
	
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d %d %d", &shark[i].r, &shark[i].c, &shark[i].s, &shark[i].d, &shark[i].z);
		map[shark[i].r][shark[i].c] = shark[i].z;
		ptr[shark[i].r][shark[i].c] = &shark[i];
		isfish++;
	}
}

void move_master()
{
	start_c++;
	for (int r = 1; r <= R; r++)
	{
		if (map[r][start_c] >= 1)
		{
			get_fish += map[r][start_c];
			ptr[r][start_c]->live = -1;

			return;
		}
	}
}
void move_shark()
{
	int temp_r, temp_c, temp_d, temp_s;

	init_map();

	for (int i = 0; i < M; i++)
	{
		if (shark[i].live == -1)
			continue;

		temp_r = shark[i].r;
		temp_c = shark[i].c;
		temp_d = shark[i].d;

		isfish++;

		// 가로
		if (temp_d >= 3)
			temp_s = shark[i].s % ((C - 1) * 2);
		else
			temp_s = shark[i].s % ((R - 1) * 2);

		for (int move = 0; move < temp_s; move++)
		{
			// 진행 방향으로 이동
			temp_r += dir.r[temp_d];
			temp_c += dir.c[temp_d];

			// 경계를 이탈하면 방향을 반대로 전환하고 두번 이동
			if (temp_r <= 0 || temp_r >= R + 1)
			{
				temp_d ^= 3;
				temp_r += (2 * dir.r[temp_d]);
			}
			if (temp_c <= 0 || temp_c >= C + 1)
			{
				temp_d ^= 7;
				temp_c += (2 * dir.c[temp_d]);
			}
		}

		shark[i].r = temp_r;
		shark[i].c = temp_c;
		shark[i].d = temp_d;

		if (map[temp_r][temp_c] < shark[i].z)
		{
			if (map[temp_r][temp_c] > 0)
				ptr[temp_r][temp_c]->live = -1;

			map[temp_r][temp_c] = shark[i].z;
			ptr[temp_r][temp_c] = &shark[i];
		}
		else
			shark[i].live = -1;
		
	}
}

void print_map()
{
	for (register r = 1; r <= R; r++)
	{
		for (register c = 1; c <= C; c++)
		{
			if(ptr[r][c] != 0 && ptr[r][c]->live != -1)
				printf("[%d %d] %d %d %d\n", ptr[r][c]->r, ptr[r][c]->c, ptr[r][c]->s, ptr[r][c]->d, ptr[r][c]->z);
		}
	}
}

void solve()
{
	for (int i = 1; i <= C; i++)
	{
		if (isfish == 0)
			break;

		move_master();
		move_shark();
		//print_map();
	}

	printf("%d\n", get_fish);
}

int main(void)
{
	input();
	solve();
}