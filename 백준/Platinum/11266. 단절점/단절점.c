#include <stdio.h>
#include <string.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))

int V, E;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[200001];
NODE *head[10001];
int pool_size;

int visit[10001];
int visit_cnt = 1;
int ans[10001];
int ans_size;

void add_tree(int a, int b)
{
	pool[pool_size].n = b;
	pool[pool_size].next = head[a];
	head[a] = &pool[pool_size++];
}

void input()
{
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		add_tree(a, b);
		add_tree(b, a);
	}
}

int search(int start, int root)
{
	NODE *nd = head[start];
	int flag = 0;
	int min_ret = visit_cnt;
	int child_cnt = 0;

	visit[start] = visit_cnt++;

	while (nd)
	{
		if (visit[nd->n] == 0)
		{
			child_cnt++;

			int ret = search(nd->n, root);
			min_ret = Min(min_ret, ret);

			if (ret == visit[start])
				flag = 1;
		}
		else
		{
			int ret = visit[nd->n];
			min_ret = Min(min_ret, ret);
		}

		nd = nd->next;
	}

	if (flag)
	{
		if (start == root)
		{
			if (child_cnt < 2)
				return 0;
		}

		ans[ans_size++] = start;
	}

	return min_ret;
}

void merge(int start, int end)
{
	int temp[10001];
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (ans[i] < ans[j])
			temp[k++] = ans[i++];
		else
			temp[k++] = ans[j++];
	}

	while(i<=mid) temp[k++] = ans[i++];
	while(j<=end) temp[k++] = ans[j++];

	for (int i = start; i <= end; i++)
		ans[i] = temp[i - start];
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

void solve()
{
	for (int i = 1; i <= V; i++)
	{
		if (visit[i] == 0)
		{
			visit_cnt = 1;
			search(i, i);
		}
	}

	sort(0, ans_size - 1);

	printf("%d\n", ans_size);
	for (int i = 0; i < ans_size; i++)
		printf("%d ", ans[i]);
	printf("\n");
}

int main(void)
{
	input();
	solve();
}