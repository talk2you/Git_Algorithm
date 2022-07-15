#include <stdio.h>

int N, M;

int parent[1000003];

void init()
{
	for (int i = 0;i <= 1000000;i++)
		parent[i] = i;
}

int find(int a)
{
	if (parent[a] == a)
		return a;

	return parent[a] = find(parent[a]);
}

void merge(int a, int b)
{
	int pa = find(a);
	int pb = find(b);

	if (pa == pb)
		return;

	parent[pa] = pb;
}

void input()
{
	int cmd, a, b;

	scanf("%d %d", &N, &M);

	for (int i = 1;i <= M;++i)
	{
		scanf("%d %d %d", &cmd, &a, &b);

		if (cmd == 0)
		{
			merge(a, b);
		}
		else
		{
			int pa = find(a);
			int pb = find(b);

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