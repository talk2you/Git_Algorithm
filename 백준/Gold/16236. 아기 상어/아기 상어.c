#include <stdio.h>
#include <time.h>

#define MAX_QUE 403
#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))
#define Abs(a) ((a)<0?-(a):(a))

int N, M;
int map[23][23];
int visit[23][23];

typedef struct {
	int r, c;
	int n;
	int feed_cnt;
}LOC;
LOC shark;
int min_dist;
int min_r, min_c;
int total_dist;


typedef struct {
	int r, c;
}QUE;
QUE que[MAX_QUE];
int head, tail;

void init_visit()
{
	for (int r = 1; r <= 20; r++)
		for (int c = 1; c <= 20; c++)
			visit[r][c] = -1;
}

int isEmpty()
{
	if (head == tail)
		return -1;
	return 1;
}

int isFull()
{
	int temp = head - 1;
	
	if (temp < 0)
		temp = MAX_QUE - 1;

	if (temp == tail)
		return -1;
	return 1;
}

int enque(int r, int c)
{
	if (isFull() == -1)
		return -1;

	que[tail].r = r;
	que[tail].c = c;

	tail++;
	tail %= MAX_QUE;

	return 1;
}

int deque(int *r, int *c)
{
	if (isEmpty() == -1)
		return -1;

	*r = que[head].r;
	*c = que[head].c;
	head++;
	head %= MAX_QUE;
	return 1;
}


typedef struct {
	int r[4], c[4];
}DIR;
// 상,우,하,좌
DIR dir = { {-1,0,1,0},{0,1,0,-1} };

void print_map()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (r == shark.r && c == shark.c)
				printf("@ ");
			else
				printf("%d ", map[r][c]);
		}
		printf("\n");
	}
	printf("size : %d\n", shark.n);
}


void input()
{
	int a;
	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &a);
			if (a == 9)
			{
				shark.r = r;
				shark.c = c;
				shark.n = 2;
				shark.feed_cnt = 0;
			}
			else
				map[r][c] = a;
		}
}

void bfs(int _r, int _c)
{
	int que_r, que_c;
	int temp_r, temp_c;

	// 변수 초기화
	min_r = _r;
	min_c = _c;
	min_dist = 999;
	init_visit();

	enque(_r, _c);
	
	visit[_r][_c] = 0;
	while (deque(&que_r, &que_c) == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			temp_r = que_r + dir.r[i];
			temp_c = que_c + dir.c[i];
		
			if (visit[temp_r][temp_c] != -1 || map[temp_r][temp_c] > shark.n)
				continue;

			if (temp_r <= 0 || temp_r >= N + 1 || temp_c <= 0 || temp_c >= N + 1)
				continue;
						
			visit[temp_r][temp_c] = visit[que_r][que_c] + 1;

			if (0 < map[temp_r][temp_c] && map[temp_r][temp_c] < shark.n)
			{
				if (min_dist > visit[temp_r][temp_c])
				{
					min_r = temp_r;
					min_c = temp_c;
					min_dist = visit[temp_r][temp_c];
				}
				else if (min_dist == visit[temp_r][temp_c])
				{
					if (min_r > temp_r)
					{
						min_r = temp_r;
						min_c = temp_c;
					}
					else if (min_r == temp_r)
					{
						if (min_c > temp_c)
						{
							min_r = temp_r;
							min_c = temp_c;
						}
					}
				}
			}

			enque(temp_r, temp_c);
		}
	}
}

void solve()
{
	while (1)
	{
		// 가장 가까운 거리 찾기
		bfs(shark.r, shark.c);

		// 최단거리를 찾을수 없으면 탈출
		if (min_dist == 999)
			break;

		// 이동거리 합산
		total_dist += min_dist;

		map[min_r][min_c] = 0;
		shark.r = min_r;
		shark.c = min_c;
		shark.feed_cnt++;
		if (shark.feed_cnt == shark.n)
		{
			shark.n++;
			shark.feed_cnt = 0;
		}
	}
	
	printf("%d\n", total_dist);
}

int main(void)
{
	input();
	solve();
}