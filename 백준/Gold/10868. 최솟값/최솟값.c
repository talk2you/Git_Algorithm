#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))

int list[100003];
int tree[400003];
int N, M;

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++)
		scanf("%d", &list[i]);
}

int make_tree(int start, int end, int idx)
{
	int mid = (start + end) >> 1;
	
	if (start >= end)
	{
		tree[idx] = list[start];
		return tree[idx];
	}

	int a = make_tree(start, mid, idx * 2);
	int b = make_tree(mid + 1, end, idx * 2 + 1);

	tree[idx] = Min(a, b);
	return tree[idx];
}

int interval_min(int start, int end, int idx, int left, int right)
{
	if (right < start || end < left)
		return 1<<30;

	if (left <= start && end <= right)
	{
		return tree[idx];
	}

	int mid = (start + end) >> 1;
	int a = interval_min(start, mid, idx*2, left, right);
	int b = interval_min(mid + 1, end, idx*2+1, left, right);

	return Min(a, b);
}

void solve()
{
	int a, b;

	make_tree(1, N, 1);
	
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", interval_min(1, N, 1, a, b));
	
	}
}

int main(void)
{
	input();
	solve();
}