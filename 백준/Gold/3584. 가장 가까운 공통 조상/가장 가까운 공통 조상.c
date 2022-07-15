#include <stdio.h>
#include <string.h>

#define Swap(a, b) {int t=a;a=b;b=t;}

int N;

typedef struct NODE{
	int idx;
	struct NODE *next;
}NODE;
NODE pool[20003];
NODE head[10003];
int pool_size;

int parent[10003][15];
int depth[10003];

void init()
{
	pool_size = 0;

	memset(head, 0, sizeof(head));
	memset(pool, 0, sizeof(pool));
	memset(parent, 0, sizeof(parent));
	memset(depth, 0, sizeof(depth));
}

void add_node(int a, int b)
{
	pool[pool_size].idx = b;
	pool[pool_size].next = head[a].next;
	head[a].next = &pool[pool_size++];
	head[a].idx = a;
}

void input()
{
	int a, b;
	scanf("%d", &N);

	for (int i = 0;i < N - 1;++i)
	{
		scanf("%d %d", &a, &b);
		parent[b][0] = a;
		add_node(a, b);
		add_node(b, a);
	}
}

void set_depth(int root, int d)
{
	depth[root] = d;

	NODE *nd = &head[root];
	while (nd->next)
	{
		nd = nd->next;

		if (depth[nd->idx])
			continue;

		set_depth(nd->idx, d + 1);
	}
}

int myLog2(int n)
{
	int cnt = 0;

	while (n)
	{
		cnt++;
		n /= 2;
	}

	return cnt;
}

void set_ancestor()
{
	int max = myLog2(N);

	for (int k = 1;k <= max;++k)
		for (int i = 1;i <= N;++i)
			parent[i][k] = parent[parent[i][k - 1]][k - 1];
}

int LCA(int a, int b)
{
	if (depth[a] < depth[b])
		Swap(a, b);

	int max = myLog2(N);
	int diff = depth[a] - depth[b];

	for (int i = 0;diff != 0;++i)
	{
		if (diff % 2 == 1)
			a = parent[a][i];
		diff /= 2;
	}

	if (a != b)
	{
		for (int i = max;i >=0;--i)
		{
			if (parent[a][i] != 0 && parent[a][i] != parent[b][i])
			{
				a = parent[a][i];
				b = parent[b][i];
			}
		}
		a = parent[a][0];
	}
	return a;
}

void solve()
{
	int root = 1;
	int a, b;

	while (parent[root][0] != 0)
		root = parent[root][0];
	
	set_depth(root, 1);
	set_ancestor();

	scanf("%d %d", &a, &b);
	printf("%d\n", LCA(a, b));
}

int main(void)
{
	int T;
	scanf("%d", &T);

	for (int t = 1;t <= T;t++)
	{
		init();
		input();
		solve();
	}
}