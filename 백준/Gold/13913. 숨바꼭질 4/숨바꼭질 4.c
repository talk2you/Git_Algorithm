#include <stdio.h>
#include <string.h>
#define MAX_QUE 100002

typedef struct {
	int d;
	int w;
}QUE;

typedef struct NODE{
	int cnt;
	int pre;
}NODE;

int N, K;
NODE visit[100001];
QUE que[100001];
int front, end;
int route[100001];

int isFull()
{
	int temp;
	temp = front - 1;
	if (temp < 0)
		temp = MAX_QUE - 1;

	if (temp == end)
		return 1;
	return 0;
}

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int enque(int d, int w)
{
	QUE temp = { d, w };
	if (!isFull())
	{
		memcpy(&que[end++], &temp, sizeof(QUE));
		end %= MAX_QUE;
	}
	else
		return 0;
	return 1;
}

int deque(int *d, int *w)
{
	QUE temp;

	if (!isEmpty())
	{
		memcpy(&temp, &que[front++], sizeof(QUE));
		front %= MAX_QUE;

		*d = temp.d;
		*w = temp.w;
	}
	else
		return 0;
	return 1;
}

void input()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i <= 100000; i++)
	{
		visit[i].cnt = 999999;
		visit[i].pre = N;
	}
}

void bfs(int start)
{
	int d = start, w = 0;
	visit[N].cnt = 0;
	visit[N].pre = 0;

	enque(start, 0);

	while (deque(&d, &w))
	{
		//printf("%d %d\n", d, w);
		if (0 <= d - 1 && d-1 <= 100000)
		{
			if (visit[d - 1].cnt > w + 1)
			{
				visit[d - 1].cnt = w + 1;
				visit[d - 1].pre = d;
				enque(d - 1, w+1);
				//printf("visit[%d] %d\n", d - 1, visit[d - 1].cnt);
			}
		}
		if (0 <= d + 1 && d+1<= 100000)
		{
			
			if (visit[d + 1].cnt > w + 1)
			{
				visit[d + 1].cnt = w + 1;
				visit[d + 1].pre = d;
				enque(d + 1, w + 1);
				//printf("visit[%d] %d\n", d + 1, visit[d + 1].cnt);
			}
		}
		if (0 <= d * 2 && d*2 <= 100000)
		{
			if (visit[d * 2].cnt > w + 1)
			{
				visit[d * 2].cnt = w + 1;
				visit[d * 2].pre = d;
				enque(d * 2, w + 1);
				//printf("visit[%d] %d\n", d * 2, visit[d * 2].cnt);
			}
		}

		if (visit[K].cnt != 999999)
		{
			break;
		}
	}
}

int main(void)
{
	int t;
	input();
	bfs(N);

	printf("%d\n", visit[K].cnt);
	
	route[visit[K].cnt] = K;
	t = K;
	for (int i = visit[K].cnt-1; i >= 0; i--)
	{
		route[i] = visit[t].pre;
		t = visit[t].pre;
		//printf("%d\n", route[i]);
	}

	for (int i = 0; i <= visit[K].cnt; i++)
		printf("%d ", route[i]);
	printf("\n");
	return 0;
}