#include <stdio.h>

int N, M, K;
long long data[1000003];
long long tree[4000003];

long long init_segment_tree(int start, int end, int idx)
{
	if (start == end)
	{
		tree[idx] = data[start];
		return tree[idx];
	}

	int mid = (start + end) / 2;
	tree[idx] = init_segment_tree(start, mid, idx * 2) + init_segment_tree(mid + 1, end, idx * 2 + 1);
	return tree[idx];
}

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1;i <= N;i++)
		scanf("%lld", &data[i]);
}

long long interval_sum(int start, int end, int idx, int left, int right)
{
	if (left > end || right < start)
		return 0;

	if (left <= start && right >= end)
		return tree[idx];

	int mid = (start + end) / 2;
	return interval_sum(start, mid, idx * 2, left, right) + interval_sum(mid + 1, end, idx * 2 + 1, left, right);
}

void update(int start, int end, int idx, int what, long long value)
{
	if (what < start || what > end)
		return;

	tree[idx] += value;

	if (start >= end)
		return;

	int mid = (start + end) / 2;
	update(start, mid, idx * 2, what, value);
	update(mid + 1, end, idx * 2 + 1, what, value);
}

void solve()
{
	int a, b;
	long long c;
	
	init_segment_tree(1, N, 1);

	for (int i = 0;i < M + K;++i)
	{
		scanf("%d %d %lld", &a, &b, &c);

		if (a == 1)
		{
			long long diff = c - data[b];
			data[b] = c;
			update(1, N, 1, b, diff);
		}
		else
			printf("%lld\n", interval_sum(1, N, 1, b, (int)c));
	}
}

int main(void)
{
	input();
	solve();
}