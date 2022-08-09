#include <stdio.h>

#define MAX 1000000

int N, M;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[100003];
NODE *head[100003];
int pool_size;

int indegree[32001];

int que[100000];
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
		temp += MAX;
	if (temp == end)
		return 1;
	return 0;
}

void push(int n)
{
	if (isFull())
		return;

	que[end++] = n;
	end %= MAX;
}

int pop(int *n)
{
	if (isEmpty())
		return 0;

	*n = que[start++];
	start %= MAX;
	return 1;
}

void add_pool(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	int a, b;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);
		add_pool(a, b);
		indegree[b] += 1;
	}
}

void solve()
{
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			push(i);

	int n;
	while (pop(&n))
	{
		printf("%d ", n);

		NODE *nd = head[n];
		while (nd)
		{
			indegree[nd->n] -= 1;

			if (indegree[nd->n] == 0)
				push(nd->n);

			nd = nd->next;
		}
	}
	printf("\n");
}

int main(void)
{
	input();
	solve();
}