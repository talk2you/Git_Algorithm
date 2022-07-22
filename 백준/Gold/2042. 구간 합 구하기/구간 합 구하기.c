#include <stdio.h>

int N, M, K;

long long list[1000003];
long long tree[4000003];

void input()
{
	scanf("%d %d %d", &N, &M, &K);

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

void update(int start, int end, int idx, int setIdx, long long diff)
{
	if (setIdx < start || end < setIdx)
		return;

	tree[idx] += diff;

	if (start >= end)
		return;

	int mid = (start + end) >> 1;
	update(start, mid, idx * 2, setIdx, diff);
	update(mid+1, end, idx * 2 + 1, setIdx, diff);
}

void solve()
{
	int cmd, a, b;
	long long bb;

	make_tree(1, N, 1);

	for (int i = 0; i < M + K; i++)
	{
		scanf(" %d", &cmd);
		if (cmd == 1)
		{
			scanf(" %d %lld", &a, &bb);
			long long diff = bb - list[a];
			list[a] = bb;

			update(1, N, 1, a, diff);
		}
		else
		{
			scanf(" %d %d", &a, &b);
			printf("%lld\n", interval_sum(1, N, 1, a, b));
		}
	}
}

int main(void)
{
	input();
	solve();
}