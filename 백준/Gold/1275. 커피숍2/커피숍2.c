#include <stdio.h>

#define Swap(a, b) {int t=a;a=b;b=t;}

int N, Q;
long long list[100003];
long long tree[400003];

void input()
{
	scanf("%d %d", &N, &Q);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &list[i]);
}

long long make_tree(int start, int end, int idx)
{
	if (start == end)
	{
		tree[idx] = list[start];
		return tree[idx];
	}

	int mid = (start + end) >> 1;

	tree[idx] = make_tree(start, mid, idx * 2) + make_tree(mid + 1, end, idx * 2 + 1);
	return tree[idx];
}

long long interval_sum(int start, int end, int idx, int left, int right)
{
	if (right < start || end < left)
		return 0;

	if (left <= start && end <= right)
		return tree[idx];

	int mid = (start + end) >> 1;

	return interval_sum(start, mid, idx * 2, left, right) + interval_sum(mid + 1, end, idx * 2 + 1, left, right);
}

void update(int start, int end, int idx, long long what, long long diff)
{
	if (what < start || end < what)
		return;

	tree[idx] += diff;

	if (start == end)
		return;

	int mid = (start + end) >> 1;
	update(start, mid, idx * 2, what, diff);
	update(mid + 1, end, idx * 2 + 1, what, diff);
}

void solve()
{
	int x, y;
	long long a, b;
	make_tree(1, N, 1);

	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d %lld %lld", &x, &y, &a, &b);
		if (x > y)
			Swap(x, y);
		printf("%lld\n", interval_sum(1, N, 1, x, y));
		long long diff = b - list[a];
		list[a] = b;
		update(1, N, 1, a, diff);

	}
}

int main(void)
{
	input();
	solve();
}