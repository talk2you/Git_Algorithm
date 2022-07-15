#include <stdio.h>

#define Swap(a, b) {int t=a;a=b;b=t;}

int N, M;

typedef struct NODE {
	int idx;
	struct NODE *next;
}NODE;
NODE node[100003];
NODE pool[200003];
int pool_size;

int parent[100003][20];
int depth[100003];

void add_node(int a, int b)
{
	pool[pool_size].idx = b;
	pool[pool_size].next = node[a].next;
	node[a].next = &pool[pool_size++];
	node[a].idx = a;
}

void input()
{
	int a, b;

	scanf("%d", &N);
	for (int i = 0;i < N - 1;++i)
	{
		scanf("%d %d", &a, &b);
		add_node(a, b);
		add_node(b, a);
	}
}

void set_parent(int idx, int d)
{
	NODE *nd = &node[idx];
	depth[idx] = d;

	while (nd->next)
	{
		nd = nd->next;

		if (depth[nd->idx])
			continue;

		parent[nd->idx][0] = idx;
		set_parent(nd->idx, d + 1);
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

	set_parent(1, 1);
	set_ancestor();

	scanf("%d", &M);
	for (int i = 0;i < M;i++)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", LCA(a, b));
	}
}

int main(void)
{
	input();
	solve();
}