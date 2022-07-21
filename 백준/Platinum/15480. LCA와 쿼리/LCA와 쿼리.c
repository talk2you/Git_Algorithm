#include <stdio.h>
#include <string.h>

#define Swap(a, b) {int t=a;a=b;b=t;}

int N, M;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[200003];
NODE head[100003];
int pool_size;

int parent[100003][20];
int depth[100003];

void add(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a].next;
	head[a].next = &pool[pool_size++];
	head[a].n = a;
}

void input()
{
	int a, b;

	scanf("%d", &N);

	for (int i = 0; i < N-1; i++)
	{
		scanf("%d %d", &a, &b);
		add(a, b);
		add(b, a);
	}
}

void set_parent(int root, int level)
{
	depth[root] = level;

	NODE *nd = &head[root];
	while (nd->next)
	{
		nd = nd->next;

		if (depth[nd->n])
			continue;

		parent[nd->n][0] = root;
		set_parent(nd->n, level + 1);
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
	int limit = myLog2(N);
	
	for (int k = 1; k <= limit; k++)
		for (int i = 1; i <= N; i++)
			parent[i][k] = parent[parent[i][k - 1]][k - 1];
}

int LCA(int a, int b)
{
	if (depth[a] < depth[b])
		Swap(a, b);

	int limit = myLog2(N);
	int diff = depth[a] - depth[b];

	for (int i = 0; diff != 0; i++)
	{
		if (diff % 2 == 1)
			a = parent[a][i];
		diff /= 2;
	}

	if (a != b)
	{
		for (int i = limit; i >= 0; i--)
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
	int r, u, v;
	int a, b, c;

	int max_depth;
	int max_idx;

	scanf("%d", &M);

	set_parent(1, 1);
	set_ancestor();

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &r, &u, &v);
		
		a = LCA(r, u);
		b = LCA(r, v);
		c = LCA(u, v);

		max_depth = depth[a];
		max_idx = a;

		if (max_depth < depth[b])
		{
			max_depth = depth[b];
			max_idx = b;
		}
		if (max_depth < depth[c])
		{
			max_depth = depth[c];
			max_idx = c;
		}

		printf("%d\n", max_idx);
	}
}

int main(void)
{
	input();
	solve();
}