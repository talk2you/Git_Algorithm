#include <stdio.h>

typedef unsigned short U16;

#define Swap(a, b) {int t=a;a=b;b=t;}

U16 N, M;

typedef struct NODE {
	U16 idx;
	struct NODE *next;
}NODE;
NODE pool[100003];
NODE node[50003];
int pool_size;

U16 parent[50003][20];
U16 depth[50003];

void add_node(U16 a, U16 b)
{
	pool[pool_size].idx = b;
	pool[pool_size].next = node[a].next;
	node[a].next = &pool[pool_size++];
	node[a].idx = a;
}

void input()
{
	U16 a, b;

	scanf("%hd", &N);

	for (int i = 0;i < N - 1;i++)
	{
		scanf("%hd %hd", &a, &b);
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

int myLog2(int a)
{
	int max = 0;
	while(a)
	{
		max++;
		a /= 2;
	}
	return max;
}

// 2^k 조상 체크
void set_ancestor()
{
	int max = myLog2(N) + 1; // logN

	// 2^(k-1)
	for (int k = 1;k <= max;k++)
		for (int cur = 1;cur <= N;cur++)
			parent[cur][k] = parent[parent[cur][k - 1]][k - 1];
}

int LCA(int a, int b)
{
	int max = myLog2(N) + 1; // logN
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
	U16 a, b;

	set_parent(1, 1);
	set_ancestor();

	scanf("%hd", &M);

	for (int i = 0;i < M;i++)
	{
		scanf("%hd %hd", &a, &b);
		printf("%d\n", LCA(a, b));
	}
}

int main(void)
{
	input();
	solve();
}