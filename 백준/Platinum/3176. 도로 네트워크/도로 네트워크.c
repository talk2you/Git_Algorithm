#include <stdio.h>

#define Swap(a, b) {int t=a;a=b;b=t;}
#define Max(a, b) ((a>b)?(a):(b))
#define Min(a, b) ((a<b)?(a):(b))

int N;

typedef struct NODE{
	int idx;
	int dist;
	struct NODE *next;
}NODE;
NODE pool[200003];
NODE head[100003];
int pool_size;

int parent[100003][20];
int depth[100003];

int min_dist[100003][20];
int max_dist[100003][20];

void init()
{
	for (int i = 0;i < 100003;++i)
		for (int k = 0;k < 20;++k)
			min_dist[i][k] = 1 << 30;
}

void add_node(int a, int b, int dist)
{
	pool[pool_size].idx = b;
	pool[pool_size].dist = dist;
	pool[pool_size].next = head[a].next;
	head[a].next = &pool[pool_size++];
	head[a].idx = a;
}

void input()
{
	int a, b, c;
	scanf("%d", &N);

	for (int i = 0;i < N-1;i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		add_node(a, b, c);
		add_node(b, a, c);
	}
}

void set_parent(int idx, int d)
{
	depth[idx] = d;

	NODE *nd = &head[idx];
	while (nd->next)
	{
		nd = nd->next;
		if (depth[nd->idx])
			continue;

		parent[nd->idx][0] = idx;
		min_dist[nd->idx][0] = nd->dist;
		max_dist[nd->idx][0] = nd->dist;

		set_parent(nd->idx, d + 1);
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
		{
			parent[i][k] = parent[parent[i][k - 1]][k - 1];
			min_dist[i][k] = Min(min_dist[parent[i][k - 1]][k - 1], min_dist[i][k - 1]);
			max_dist[i][k] = Max(max_dist[parent[i][k - 1]][k - 1], max_dist[i][k - 1]);
		}
}

int LCA(int a, int b)
{
	if (depth[a] < depth[b])
		Swap(a, b);

	int diff = depth[a] - depth[b];
	int n_limit = myLog2(N);

	int min = 1<<30, max = 0;

	for (int i = 0;diff != 0;++i)
	{
		if (diff % 2 == 1)
		{
			min = Min(min, min_dist[a][i]);
			if (max_dist[a][i] != 1 << 30)
				max = Max(max, max_dist[a][i]);
			a = parent[a][i];
		}
		diff /= 2;
	}

	if (a != b)
	{
		for (int i = n_limit;i >= 0;--i)
		{
			if (parent[a][i] != 0 && parent[a][i] != parent[b][i])
			{
				if (min_dist[a][i] != 0)
					min = Min(min, min_dist[a][i]);
				if (min_dist[b][i] != 0)
					min = Min(min, min_dist[b][i]);

				if (max_dist[a][i] != 1 << 30)
					max = Max(max, max_dist[a][i]);
				if (max_dist[b][i] != 1 << 30)
					max = Max(max, max_dist[b][i]);

				a = parent[a][i];
				b = parent[b][i];
			}
		}

		min = Min(min, min_dist[a][0]);
		min = Min(min, min_dist[b][0]);

		if (max_dist[a][0] != 1 << 30)
			max = Max(max, max_dist[a][0]);
		if (max_dist[b][0] != 1 << 30)
			max = Max(max, max_dist[b][0]);

		a = parent[a][0];
	}

	if (min == 1 << 30)
		min = 0;

	printf("%d %d\n", min, max);

	return a;
}

void solve()
{
	int K;
	int a, b;
	int lca_idx;

	set_parent(1, 1);
	set_ancestor();

	scanf("%d", &K);
	for (int i = 0;i < K;++i)
	{
		scanf("%d %d", &a, &b);
		lca_idx = LCA(a, b);
	}
}

int main(void)
{
	init();
	input();
	solve();
}