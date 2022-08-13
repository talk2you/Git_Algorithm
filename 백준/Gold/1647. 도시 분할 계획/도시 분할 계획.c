#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

int N, M;

typedef struct NODE{
	int a, b;
	int cost;
}NODE;
NODE load[1000001];
NODE temp[1000001];
int parent[100001];

void init()
{
	for (int i = 1; i <= 100000; i++)
		parent[i] = i;
}

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
		scanf("%d %d %d", &load[i].a, &load[i].b, &load[i].cost);
}

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (load[i].cost < load[j].cost)
			memcpy(&temp[k++], &load[i++], sizeof(NODE));
		else
			memcpy(&temp[k++], &load[j++], sizeof(NODE));
	}

	while(i<=mid)	memcpy(&temp[k++], &load[i++], sizeof(NODE));
	while(j<=end)	memcpy(&temp[k++], &load[j++], sizeof(NODE));

	for(int i=start;i<=end;i++)
		memcpy(&load[i], &temp[i-start], sizeof(NODE));
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

	int sum = 0;
	int max = 0;

	for (int i = 0; i < M; i++)
	{
		int pa = find_parent(load[i].a);
		int pb = find_parent(load[i].b);

		if (pa == pb)
			continue;

		parent[pb] = pa;

		sum += load[i].cost;
		max = Max(max, load[i].cost);
	}

	printf("%d\n", sum - max);
}

int main(void)
{
	init();
	input();
	solve();
}