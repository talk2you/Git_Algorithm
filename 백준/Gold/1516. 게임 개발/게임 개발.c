#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
int indegree[501];
int time[501];
int cost[501];

int que[501];
int end;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[250001];
NODE *head[501];
int pool_size;

void add_node(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &time[i]);

		while (1)
		{
			int p;
			scanf("%d", &p);
			if (p == -1)
			{
				if (!head[i])
					cost[i] = time[i];
				break;
			}

			add_node(i, p);
			indegree[p]++;
		}
	}
}

int search(int n)
{
	if (cost[n] != 0)
	{
		return cost[n];
	}

	NODE *nd = head[n];
	while (nd)
	{
		cost[n] = Max(cost[n], search(nd->n) + time[n]);

		nd = nd->next;
	}

	return cost[n];
}

void solve()
{
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			que[end++] = i;

	for (int i = 0; i < end; i++)
	{
		search(que[i]);
	}

	for(int i=1;i<=N;i++)
		printf("%d\n", cost[i]);

}

int main(void)
{
	input();
	solve();
}