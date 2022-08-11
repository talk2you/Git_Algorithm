#include <stdio.h>
#include <string.h>

#define MAX	1000003

int N, M;
int ans;

int parent[1001];

typedef struct NODE{
	int a, b;
	int cost;
	struct NODE *next;
}NODE;
NODE node[MAX];
NODE temp[MAX];

void init()
{
	for (int i = 1; i <= N; i++)
		parent[i] = i;
}

void input()
{
	scanf("%d %d", &N, &M);

	init();

	for (int i = 0; i < M; i++)
		scanf("%d %d %d", &node[i].a, &node[i].b, &node[i].cost);
}

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (node[i].cost < node[j].cost)
			memcpy(&temp[k++], &node[i++], sizeof(NODE));
		else
			memcpy(&temp[k++], &node[j++], sizeof(NODE));
	}

	while(i<=mid)	memcpy(&temp[k++], &node[i++], sizeof(NODE));
	while(j<=end)	memcpy(&temp[k++], &node[j++], sizeof(NODE));

	for(int i=start;i<=end;i++)
		memcpy(&node[i], &temp[i-start], sizeof(NODE));

}

void sort(int start, int end)
{
	if (start >= end)
		return;

	int mid = (start + end) >> 1;
	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int find_parent(int n)
{
	if (parent[n] == n)
		return n;

	return parent[n] = find_parent(parent[n]);
}

void solve()
{
	sort(0, M - 1);
	
	for (int i = 0; i < M; i++)
	{
		if (node[i].a == node[i].b)
			continue;

		int pa = find_parent(node[i].a);
		int pb = find_parent(node[i].b);

		if (pa == pb)
			continue;

		parent[pb] = pa;
		ans += node[i].cost;
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}