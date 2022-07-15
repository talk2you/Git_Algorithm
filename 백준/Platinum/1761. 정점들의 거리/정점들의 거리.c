#include <stdio.h>

#define Swap(a, b) {int t=a;a=b;b=t;}

int N, M;

typedef struct NODE {
	int idx, dist;
	struct NODE *next;
}NODE;
NODE node[40003];
NODE pool[80003];
int pool_size;

int parent[40003][20];
int depth[40003];
int distance[40003];

void add_node(int a, int b, int dist)
{
	pool[pool_size].idx = b;
	pool[pool_size].dist = dist;
	pool[pool_size].next = node[a].next;	
	node[a].next = &pool[pool_size++];
	node[a].idx = a;
}

void input()
{
	int a, b, dist;

	scanf("%d", &N);
	for (int i = 0;i < N - 1;++i)
	{
		scanf("%d %d %d", &a, &b, &dist);
		add_node(a, b, dist);
		add_node(b, a, dist);
	}
}

void set_parent(int idx, int d, int dist)
{
	NODE *nd = &node[idx];
	depth[idx] = d;

	while (nd->next)
	{
		nd = nd->next;

		if (depth[nd->idx])
			continue;

		parent[nd->idx][0] = idx;
		distance[nd->idx] = dist + nd->dist;
		set_parent(nd->idx, d + 1, dist + nd->dist);
	}
}

// (Log2(N)) + 1 로 계산
int myLog2(int a)
{
	int max = 0;
	while (a)
	{
		max++;
		a /= 2;
	}
	return max;
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
	int max = myLog2(N);
	int diff;

	if (depth[a] < depth[b])
		Swap(a, b);

	diff = depth[a] - depth[b];

	for (int i = 0;diff != 0;++i)
	{
		if (diff % 2 == 1)
			a = parent[a][i];
		diff /= 2;
	}

	if (a != b)
	{
		for (int i = max - 1;i >= 0;--i)
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
	int a, b;
	int lca_idx;
	int ans;

	set_parent(1, 1, 0);
	set_ancestor();

	scanf("%d", &M);
	for (int i = 0;i < M;i++)
	{
		scanf("%d %d", &a, &b);
		lca_idx = LCA(a, b);

		ans = distance[a] + distance[b] - 2 * distance[lca_idx];
		printf("%d\n", ans);
	}
}

int main(void)
{
	input();
	solve();
}