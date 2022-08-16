#include <stdio.h>

#define MAX	200010
#define Swap(a, b) {int t=a;a=b;b=t;}

int N;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[MAX];
NODE *head[MAX/2];
int pool_size;

int parent[MAX / 2][20];
int depth[MAX / 2];

void add_tree(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N-1; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		add_tree(a, b);
		add_tree(b, a);
	}
}

void set_parent(int root, int d)
{
	depth[root] = d;
	NODE *nd = head[root];

	while (nd)
	{
		if (depth[nd->n] != 0)
		{
			nd = nd->next;
			continue;
		}

		parent[nd->n][0] = root;
		set_parent(nd->n, d + 1);

		nd = nd->next;
	}
}

int mylog(int n) 
{
	int cnt = 0;
	while (n)
	{
		n /= 2;
		cnt++;
	}
	return cnt;
}

void set_ancestor()
{
	int limit = mylog(N);

	for (int k = 1; k <= limit; k++)
		for (int i = 1; i <= N; i++)
			parent[i][k] = parent[parent[i][k - 1]][k - 1];
}

int LCA2(int a, int b)
{
	if (depth[a] < depth[b])
		Swap(a, b);

	int limit = mylog(N);
	int diff = depth[a] - depth[b];

	for (int i = 0; diff != 0; ++i)
	{
		if (diff % 2 == 1)
			a = parent[a][i];
		diff /= 2;
	}

	if (a != b)
	{
		for (int i = limit; i >= 0; --i)
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
	set_parent(1, 1);
	set_ancestor();

	int M;
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);		
		printf("%d\n", LCA2(a, b));
	}
}

int main(void)
{
	input();
	solve();
}