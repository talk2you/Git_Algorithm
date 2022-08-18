#include <stdio.h>
#include <string.h>

#define INF	1<<30
#define QUE_SIZE	300000

int V, E;
int root;

typedef struct NODE{
	int n, w;
	struct NODE *next;
}NODE;
NODE pool[300001];
NODE *head[20001];
int pool_size;

int ans[20001];

typedef struct {
	int n, w;
}PRIORITY_QUE;
PRIORITY_QUE priority_que[QUE_SIZE];
int que_size;

void push(int n, int w)
{
	PRIORITY_QUE temp;
	que_size++;
	priority_que[que_size].n = n;
	priority_que[que_size].w = w;

	for (int i = que_size; i > 1; i /= 2)
	{
		if (priority_que[i / 2].w < priority_que[i].w)
			break;

		memcpy(&temp, &priority_que[i / 2], sizeof(PRIORITY_QUE));
		memcpy(&priority_que[i / 2], &priority_que[i], sizeof(PRIORITY_QUE));
		memcpy(&priority_que[i], &temp, sizeof(PRIORITY_QUE));
	}
}

int pop(int *n, int *w)
{
	if (que_size == 0)
		return 0;

	PRIORITY_QUE temp;
	*n = priority_que[1].n;
	*w = priority_que[1].w;

	memcpy(&priority_que[1], &priority_que[que_size], sizeof(PRIORITY_QUE));
	priority_que[que_size--].w = INF;

	for (int i = 1; i * 2 <= que_size;)
	{
		if (priority_que[i].w < priority_que[i * 2].w && priority_que[i].w < priority_que[i * 2 + 1].w)
			break;

		else if (priority_que[i * 2].w < priority_que[i * 2 + 1].w)
		{
			memcpy(&temp, &priority_que[i * 2], sizeof(PRIORITY_QUE));
			memcpy(&priority_que[i * 2], &priority_que[i], sizeof(PRIORITY_QUE));
			memcpy(&priority_que[i], &temp, sizeof(PRIORITY_QUE));
			i = i * 2;
		}
		else
		{
			memcpy(&temp, &priority_que[i * 2 + 1], sizeof(PRIORITY_QUE));
			memcpy(&priority_que[i * 2 + 1], &priority_que[i], sizeof(PRIORITY_QUE));
			memcpy(&priority_que[i], &temp, sizeof(PRIORITY_QUE));
			i = i * 2 + 1;
		}
	}

	return 1;
}


void init()
{
	for (int i = 0; i <= 20000; i++)
		ans[i] = INF;
}

void add_node(int a, int b, int w)
{
	pool[pool_size].n = b;
	pool[pool_size].w = w;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	scanf("%d %d", &V, &E);
	scanf("%d", &root);

	ans[root] = 0;

	for (int i = 0; i < E; i++)
	{
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		add_node(a, b, w);
	}
}

void solve()
{
	push(root, 0);

	int n, w;
	while (pop(&n, &w))
	{
		NODE *nd = head[n];
		while (nd)
		{
			if (ans[nd->n] > ans[n] + nd->w)
			{
				ans[nd->n] = ans[n] + nd->w;
				push(nd->n, ans[nd->n]);
			}
			nd = nd->next;
		}
	}

	for (int i = 1; i <= V; i++)
	{
		if (ans[i] == INF)
			printf("INF\n");
		else
			printf("%d\n", ans[i]);
	}
}

int main(void)
{
	init();
	input();
	solve();
}