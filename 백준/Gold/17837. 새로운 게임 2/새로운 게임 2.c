#include <stdio.h>

int N, K;
int map[17][17];

typedef struct LL{
	int list[5];
	int end;	
}LL;
LL ll[17][17];

typedef struct {
	int r, c;
	int dir;
	int n;
}CHIP;
CHIP chip[11];

typedef struct {
	int r[5], c[5];
}DIR;
// 우, 좌, 상, 하
DIR dir = { {0,0,0,-1,1},{0,1,-1,0,0} };

void input()
{
	LL *p_ll;
	scanf("%d %d", &N, &K);

	for (int r = 0; r <= N+1; r++)
	{
		for (int c = 0; c <= N+1; c++)
		{
			// 범위 밖은 파란색
			if (r == 0 || c == 0 || r == N + 1 || c == N + 1)
				map[r][c] = 2;
			else
				scanf("%d", &map[r][c]);
		}
	}

	for (int i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &chip[i].r, &chip[i].c, &chip[i].dir);
		chip[i].n = 0;
		// 각 칸마다 리스트에 추가
		p_ll = &ll[chip[i].r][chip[i].c];
		p_ll->list[p_ll->end] = i;
		p_ll->end += 1;
	}
}

void print_ll()
{
	LL *p_ll;
	for (int r = 0; r <= N + 1; r++)
	{
		for (int c = 0; c <= N + 1; c++)
		{
			p_ll = &ll[r][c];
			for (int i = 0; i < p_ll->end; i++)
				printf("[%d %d], %d %d, idx:%d\n", c, r, p_ll->list[i], chip[p_ll->list[i]].dir, chip[p_ll->list[i]].n);
		}
	}
}

int move_white(int i, int temp_r, int temp_c, LL *p_ll, LL *dst_ll)
{
	int temp_front = chip[i].n;
	int temp_end = p_ll->end;

	for (int j = temp_front; j < temp_end; j++)
	{
		dst_ll->list[dst_ll->end] = p_ll->list[j];

		chip[p_ll->list[j]].r = temp_r;
		chip[p_ll->list[j]].c = temp_c;
		chip[p_ll->list[j]].n = dst_ll->end;

		dst_ll->end += 1;

		p_ll->list[j] = 0;
		p_ll->end -= 1;
	}
	//printf("list cnt %d\n", dst_ll->end);

	if (dst_ll->end >= 4)
		return 1;
	return 0;
}

int move_red(int i, int temp_r, int temp_c, LL *p_ll, LL *dst_ll)
{
	int temp_front = chip[i].n;
	int temp_end = p_ll->end;

	int temp;
	temp = p_ll->list[temp_front];
	p_ll->list[temp_front] = p_ll->list[(p_ll->end) - 1];
	p_ll->list[(p_ll->end) - 1] = temp;

	chip[p_ll->list[0]].n = 0;
	chip[p_ll->list[(p_ll->end) - 1]].n = (p_ll->end) - 1;

	for (int j = temp_front; j < temp_end; j++)
	{
		dst_ll->list[dst_ll->end] = p_ll->list[j];

		chip[p_ll->list[j]].r = temp_r;
		chip[p_ll->list[j]].c = temp_c;
		chip[p_ll->list[j]].n = dst_ll->end;

		dst_ll->end += 1;

		p_ll->list[j] = 0;
		p_ll->end -= 1;
	}
	
	if (dst_ll->end >= 4)
		return 1;

	return 0;
}

void solve()
{
	int temp_r, temp_c, temp_dir;
	LL *p_ll, *dst_ll;
	int temp_front, temp_end;
	int ret_flag = 0;
	
	for (int cnt = 1; cnt <= 1000; cnt++)
	{
		for (int i = 1; i <= K; i++)
		{
			temp_dir = chip[i].dir;
			temp_r = chip[i].r + dir.r[temp_dir];
			temp_c = chip[i].c + dir.c[temp_dir];
			p_ll = &ll[chip[i].r][chip[i].c];
			dst_ll = &ll[temp_r][temp_c];

			temp_front = chip[i].n;
			temp_end = p_ll->end;

			// 이동할 칸이 흰색인 경우
			if (map[temp_r][temp_c] == 0)
				ret_flag = move_white(i, temp_r, temp_c, p_ll, dst_ll);
			// 이동할 칸이 빨간색인 경우
			else if (map[temp_r][temp_c] == 1)
				ret_flag = move_red(i, temp_r, temp_c, p_ll, dst_ll);
			// 이동할 칸이 파란색인 경우
			else if (map[temp_r][temp_c] == 2)
			{
				// 방향 전환
				temp_dir = ((temp_dir - 1) ^ 1) + 1;
				chip[i].dir = temp_dir;

				temp_r += (dir.r[temp_dir] * 2);
				temp_c += (dir.c[temp_dir] * 2);

				dst_ll = &ll[temp_r][temp_c];

				// 이동할 칸이 흰색인 경우
				if (map[temp_r][temp_c] == 0)
					ret_flag = move_white(i, temp_r, temp_c, p_ll, dst_ll);
				// 이동할 칸이 빨간색인 경우
				else if (map[temp_r][temp_c] == 1)
					ret_flag = move_red(i, temp_r, temp_c, p_ll, dst_ll);
			}
			
			if (ret_flag)
			{
				printf("%d\n", cnt);
				return;
			}
		}
	}

	printf("-1\n");
}

int main(void)
{
	input();
	solve();
    
    return 0;
}