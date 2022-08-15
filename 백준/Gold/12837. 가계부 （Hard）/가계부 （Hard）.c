#include <stdio.h>

int N, Q;

long long tree[4000000];

void input()
{
	scanf("%d %d", &N, &Q);
}

void update(int start, int end, int idx, int what, int diff)
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

long long interval_sum(int start, int end, int idx, int left, int right)
{
	if (right < start || end < left)
		return 0;

	if (left <= start && end <= right)
		return tree[idx];

	int mid = (start + end) >> 1;

	return interval_sum(start, mid, idx * 2, left, right) + interval_sum(mid + 1, end, idx * 2 + 1, left, right);
}

void solve()
{
	int cmd;

	for (int i = 0; i < Q; i++)
	{
		scanf("%d", &cmd);

		if (cmd == 1)
		{
			int p, x;
			scanf(" %d %d", &p, &x);
			update(1, N, 1, p, x);
		}
		else
		{
			int p, q;
			scanf("%d %d", &p, &q);
			printf("%lld\n", interval_sum(1, N, 1, p, q));
		}
	}
}

int main(void)
{
	input();
	solve();
}