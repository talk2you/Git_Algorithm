#include <stdio.h>
#include <string.h>

int V, E;

typedef struct {
	int a, b, w;
}NODE;
NODE node[100003];
NODE temp[100003];

int parent[10003];
int ans;

void init()
{
	for (int i = 0;i <= 10000;i++)
		parent[i] = i;
}

void input()
{
	scanf("%d %d", &V, &E);

	for (int i = 0;i < E;i++)
		scanf("%d %d %d", &node[i].a, &node[i].b, &node[i].w);
}

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (node[i].w < node[j].w)
			memcpy(&temp[k++], &node[i++], sizeof(NODE));
		else
			memcpy(&temp[k++], &node[j++], sizeof(NODE));
	}

	while(i<=mid)
		memcpy(&temp[k++], &node[i++], sizeof(NODE));
	while(j<=end)
		memcpy(&temp[k++], &node[j++], sizeof(NODE));

	for(int i=start;i<=end;i++)
		memcpy(&node[i], &temp[i-start], sizeof(NODE));
}

void sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int find_parent(int idx)
{
	if (parent[idx] == idx)
		return idx;

	return parent[idx] = find_parent(parent[idx]);
}

void solve()
{
	sort(0, E - 1);

	for (int i = 0;i < E;i++)
	{
		int pa = find_parent(node[i].a);
		int pb = find_parent(node[i].b);

		if (pa == pb)
			continue;

		parent[pb] = pa;
		ans += node[i].w;
	}
	
	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}