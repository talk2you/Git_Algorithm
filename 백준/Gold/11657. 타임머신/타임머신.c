#include <stdio.h>

#define MAX_QUE	10000
#define INF	1<<30

int N, M;

typedef struct NODE{
	int n;
	int cost;
	int cnt;
	struct NODE *next;
}NODE;
NODE pool[6001];
NODE *head[501];
int pool_size;
long long cost[501];

int que[10000];
int start, end;

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
		temp += MAX_QUE;
	if (temp == end)
		return 1;
	return 0;
}

void push(int n)
{
	if (isFull())
		return;
	
	que[end++] = n;
	end %= MAX_QUE;
	return;
}

int pop(int *n)
{
	if (isEmpty())
		return 0;

	*n = que[start++];
	start %= MAX_QUE;
	return 1;
}

void init()
{
	// 1은 0
	for (int i = 2; i <= 500; i++)
		cost[i] = INF;
}

void add_node(int a, int b, int cost)
{
	pool[pool_size].n = b;
	pool[pool_size].cost = cost;
	pool[pool_size].next = head[a];	
	head[a] = &pool[pool_size++];
}

void input()
{
	int a, b, cost;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, &cost);
		add_node(a, b, cost);
	}
}

void solve()
{
	int n;
	push(1);

	while (pop(&n))
	{
		NODE *nd = head[n];

		while (nd)
		{
			if (cost[nd->n] > cost[n] + nd->cost)
			{
				push(nd->n);
				cost[nd->n] = cost[n] + nd->cost;
				nd->cnt++;

				if (nd->cnt > N)
				{
					printf("-1\n");
					return;
				}
			}
			nd = nd->next;
		}
	}

	for (int i = 2; i <= N; i++)
	{
		if (cost[i] == INF)
			cost[i] = -1;
		printf("%lld\n", cost[i]);
	}
}

int main(void)
{
	init();
	input();
	solve();
}