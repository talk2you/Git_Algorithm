#include <stdio.h>
#include <string.h>

#define INF 1<<30;
#define MAX 100001

int N, M;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[100001];
NODE *head[32001];
int pool_size;

int indegree[32001];
int priority_que[100001];
int que_size;

void push(int n)
{
	int temp;
	que_size++;
	priority_que[que_size] = n;

	for (int i = que_size; i > 1; i /= 2)
	{
		if (priority_que[i / 2] < priority_que[i])
			break;

		temp = priority_que[i / 2];
		priority_que[i / 2] = priority_que[i];
		priority_que[i] = temp;
	}
}

int pop(int *n)
{
	int temp;

	if (que_size == 0)
		return 0;

	*n = priority_que[1];
	priority_que[1] = priority_que[que_size];
	priority_que[que_size--] = INF;

	for (int i = 1; i * 2 <= que_size;)
	{
		if (priority_que[i] < priority_que[i * 2] && priority_que[i] < priority_que[i * 2 + 1])
			break;

		else if (priority_que[i * 2] < priority_que[i * 2 + 1])
		{
			temp = priority_que[i * 2];
			priority_que[i * 2] = priority_que[i];
			priority_que[i] = temp;
			i = i * 2;
		}
		else
		{
			temp = priority_que[i * 2 + 1];
			priority_que[i * 2 + 1] = priority_que[i];
			priority_que[i] = temp;
			i = i * 2 + 1;
		}
	}
	return 1;
}

void add_node(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);		
		add_node(a, b);
		indegree[b]++;
	}
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0)
			push(i);
	}

	int n;
	while(pop(&n))
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