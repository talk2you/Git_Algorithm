#include <stdio.h>
#include <string.h>

#define MAX_QUE 10001

int N,K,L;
int map[102][102];
int map_cnt[102][102];

typedef struct {
	int y[4], x[4];
}DIR;
// 우, 하, 좌, 상
DIR dir = { {0,1,0,-1}, {1,0,-1,0} };

typedef struct {
	int time;
	char c;
}CMD;
CMD cmd[100];

typedef struct {
	int y, x;
}QUE;
QUE que[MAX_QUE];
int front, end;

void init_que()
{
	for (int i = 0; i < 10000; i++)
	{
		que[i].x = 0;
		que[i].y = 0;
	}
	front = 0;
	end = 0;
}

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
		temp = MAX_QUE - 1;
	if (temp == end)
		return 1;
	return 0;
}

int enque(int y, int x)
{
	if (!isFull())
	{
		que[end].y = y;
		que[end].x = x;
		end++;
		end %= MAX_QUE;
		return 1;
	}
	printf("full!\n");
	return 0;
}

int deque(int *y, int *x)
{
	
	if (!isEmpty())
	{
		*y = que[front].y;
		*x = que[front].x;
		front++;
		front %= MAX_QUE;
		return 1;
	}
	printf("empty!\n");
	return 0;
}

void print_map()
{
	for (int y = 0; y < N + 2; y++)
	{
		for (int x = 0; x < N + 2; x++)
		{
			printf("%c ", map[y][x]);
		}
		printf("\n");
	}
}

void print_map_cnt()
{
	for (int y = 0; y < N + 2; y++)
	{
		for (int x = 0; x < N + 2; x++)
		{
			printf("%2d ", map_cnt[y][x]);
		}
		printf("\n");
	}
	printf("-------------------\n");
}

void input()
{
	int apple_y, apple_x;
	// 보드 크기
	scanf("%d", &N);
	// 사과의 위치정보 개수
	scanf("%d", &K);
	
	// 벽 세팅
	for (int y = 0; y < N + 2; y++)
	{
		for (int x = 0; x < N + 2; x++)
		{
			if (y == 0 || x == 0)
			{
				map[y][x] = '#';
				map_cnt[y][x] = -1;
			}
			else if (y == N + 1 || x == N + 1)
			{
				map[y][x] = '#';
				map_cnt[y][x] = -1;
			}
			else
				map[y][x] = '.';
		}
	}

	// 사과 위치 세팅
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d", &apple_y, &apple_x);
		map[apple_y][apple_x] = 'A';
	}

	// 명령어 입력
	scanf("%d", &L);
	for (int i = 0; i < L; i++)
		scanf("%d %c", &cmd[i].time, &cmd[i].c);
	

	//print_map();
}

int solve()
{
	// 뱀 초기위치
	int baam_dir = 0;
	int baam_x = 1, baam_y = 1;
	int temp_x, temp_y;
	int time = 0;
	int cmd_idx = 0;
	int apple_cnt = 0;

	map_cnt[1][1] = 1;
	enque(baam_y, baam_x);
	//print_map_cnt();

	while (1)
	{
		time++;
		baam_x += dir.x[baam_dir];
		baam_y += dir.y[baam_dir];
		enque(baam_y, baam_x);
	
		// 벽 닿으면 종료
		if (map[baam_y][baam_x] == '#')
			return time;
		// 몸 닿으면 종료
		if (map_cnt[baam_y][baam_x] > 0)
			return time;
		
		map_cnt[baam_y][baam_x] = apple_cnt + 1;

		// 사과 먹을때
		if (map[baam_y][baam_x] == 'A')
		{
			apple_cnt++;
			map_cnt[baam_y][baam_x] = apple_cnt + 1;
			map[baam_y][baam_x] = '.';
		}
		// 문제없이 이동할 때
		else
		{
			// 큐에 저장된 위치의 뱀 꼬리 빼기
			for (int i = 0; i < apple_cnt + 1; i++)
			{
				deque(&temp_y, &temp_x);
				map_cnt[temp_y][temp_x] -= 1;
				if (map_cnt[temp_y][temp_x] != 0)
					enque(temp_y, temp_x);
			}
		}

		//printf("time : %d\n", time);
		//print_map_cnt();		

		// 명령어에 대한 방향 조절
		if (time == cmd[cmd_idx].time)
		{
			if (cmd[cmd_idx].c == 'D')
			{
				baam_dir += 1;
				baam_dir %= 4;
			}
			else
			{
				baam_dir -= 1;
				if (baam_dir < 0)
					baam_dir = 3;
			}
			cmd_idx++;
		}
	}
}

int main(void)
{
	int result = 0;
	input();
	result = solve();

	printf("%d\n", result);
}