#include <stdio.h>

int K, V, E;

typedef struct NODE{
	int idx;
	struct NODE *next;
}NODE;

NODE head[20003];
NODE pool[400003];

int visit[20003];
int pool_cnt;

void init()
{
	for (int i = 0; i < 20003; i++)
	{
		visit[i] = 0;
		head[i].idx = 0;
		head[i].next = 0;
	}
	pool_cnt = 0;
}

void make(int a, int b)
{
	NODE *nd = &pool[pool_cnt++];
	nd->idx = b;
	nd->next = head[a].next;
	head[a].next = nd;
}

void input()
{
	int a, b;
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		scanf("%d %d", &a, &b);
		make(a, b);
		make(b, a);
	}
}

int dfs(int n, int color)
{
	visit[n] = color;

	for(NODE *p = head[n].next; p ; p =p->next)
	{
		if (visit[p->idx] == color)
			return 0;
		if (!visit[p->idx])
		{
			if (!dfs(p->idx, 3 - color))
				return 0;
		}
	}

	return 1;
}

void solve()
{
	int flag = 0;
	for (int i = 0; i < V; i++)
	{
		if (visit[i] == 0)
		{
			flag = dfs(i, 1);
			if (!flag)
				break;
		}
	}

	if (flag)
		printf("YES\n");
	else
		printf("NO\n");
}

int main(void)
{
	scanf("%d", &K);

	for (int t = 1; t <= K; t++)
	{
		init();
		input();
		solve();
	}

	return 0;
}