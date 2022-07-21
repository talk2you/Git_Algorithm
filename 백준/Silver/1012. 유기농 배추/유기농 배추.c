#include <stdio.h>
#include <string.h>

#define MAX_QUE 3000

int M, N, K;
int map[53][53];
int visit[53][53];

typedef struct {
	int r, c;
}QUE;
QUE que[3000];
int front, end;

typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

int ans;

void init()
{
	ans = 0;
	front = 0, end = 0;

	memset(map, 0, sizeof(visit));
	memset(visit, 0, sizeof(visit));
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
		temp += MAX_QUE;
	if (temp == end)
		return 1;
	return 0;
}

int push(int r, int c)
{
	if (isFull())
		return 0;

	que[end].r = r;
	que[end++].c = c;
	end %= MAX_QUE;
	return 1;
}

int pop(int *r, int *c)
{
	if (isEmpty())
		return 0;

	*r = que[front].r;
	*c = que[front++].c;
	front %= MAX_QUE;
	return 1;
}

void input()
{
	int a, b;
	scanf("%d %d %d", &M, &N, &K);
	
	for (int i = 0; i < K; ++i)
	{
		scanf("%d %d", &a, &b);
		map[b][a] = 1;
	}
}

void BFS(int r, int c)
{
	int pop_r, pop_c;
	int temp_r, temp_c;

	push(r, c);

	visit[r][c] = 1;

	while (pop(&pop_r, &pop_c))
	{
		visit[pop_r][pop_c] = 1;

		for (int i = 0; i < 4; i++)
		{
			temp_r = pop_r + dir.r[i];
			temp_c = pop_c + dir.c[i];

			if (temp_r < 0 || temp_r >= N || temp_c < 0 || temp_c >= M)
				continue;

			if (visit[temp_r][temp_c])
				continue;

			if (map[temp_r][temp_c] == 0)
				continue;
			
			push(temp_r, temp_c);
		}
	}
}

void solve()
{
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			if (visit[r][c])
				continue;

			if (map[r][c] == 0)
				continue;

			BFS(r, c);
			ans++;
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		solve();
	}
}