#include <stdio.h>

int N, M;
int parent[1000001];

void init()
{
	for (int i = 0; i <= 1000000; i++)
		parent[i] = i;
}

int find_parent(int n)
{
	if (parent[n] == n)
		return n;

	return parent[n] = find_parent(parent[n]);
}

void input()
{
	int cmd, a, b;
	int pa, pb;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &cmd, &a, &b);

		pa = find_parent(a);
		pb = find_parent(b);

		if (cmd == 0)
		{
			if (pa == pb)
				continue;
			else
				parent[pa] = pb;
		}
		else
		{
			if (pa == pb)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
}

int main(void)
{
	init();
	input();
}