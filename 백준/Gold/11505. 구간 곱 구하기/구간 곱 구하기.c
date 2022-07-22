#include <stdio.h>

#define MOD	1000000007

int N, M, K;

int list[1000003];
int tree[4000003];

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; i++)
		scanf("%d", &list[i]);
}

int make_tree(int start, int end, int idx)
{
	if (start == end)
	{
		tree[idx] = list[start];
		return tree[idx];
	}

	int mid = (start + end) >> 1;

	tree[idx] = ((long long)make_tree(start, mid, idx * 2) * (long long)make_tree(mid + 1, end, idx * 2 + 1)) % MOD;
	return tree[idx];
}

int interval_prod(int start, int end, int idx, int left, int right)
{
	if (right < start || end < left)
		return 1;

	if (left <= start && end <= right)
	{
		return tree[idx];
	}

	int mid = (start + end) >> 1;

	return ((long long)interval_prod(start, mid, idx * 2, left, right) * (long long)interval_prod(mid+1, end, idx*2+1, left, right)) % MOD;
}

int update(int start, int end, int idx, int setIdx, int oldVal, int newVal)
{
	if (setIdx < start || end < setIdx)
		return tree[idx];

	if (start == end)
	{
		tree[idx] = newVal;
		return tree[idx];
	}
	
	int mid = (start + end) >> 1;
	int a = update(start, mid, idx * 2, setIdx, oldVal, newVal);
	int b = update(mid + 1, end, idx * 2 + 1, setIdx, oldVal, newVal);

	tree[idx] = ((long long)a*(long long)b) % MOD;
	return tree[idx];
}

void solve()
{
	int cmd, a, b;
	make_tree(1, N, 1);

	for (int i = 0; i < M + K; i++)
	{
		scanf("%d %d %d", &cmd, &a, &b);

		if (cmd == 1)
		{
			update(1, N, 1, a, list[a], b);
		}
		else
			printf("%d\n", interval_prod(1, N, 1, a, b));
	}
}

int main(void)
{
	input();
	solve();
}