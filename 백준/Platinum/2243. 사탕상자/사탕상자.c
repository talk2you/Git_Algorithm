#include <stdio.h>

#define MAX 1000001

int N;
int tree[4 * MAX];

void input()
{
	scanf("%d\n", &N);
}

void update(int start, int end, int idx, int what, int diff)
{
	if (what < start || what > end)
		return;

	tree[idx] += diff;

	if (start == end)
		return;

	int mid = (start + end) >> 1;
	update(start, mid, idx * 2, what, diff);
	update(mid + 1, end, idx * 2 + 1, what, diff);
}

int get_rank(int start, int end, int idx, int rank)
{
	if (start == end)
		return start;

	int mid = (start + end) >> 1;
	
	if (rank <= tree[idx * 2])
		return get_rank(start, mid, idx * 2, rank);
	else
		return get_rank(mid + 1, end, idx * 2 + 1, rank - tree[idx * 2]);
}

void solve()
{
	int a, b, c;

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a);

		if (a == 1)
		{
			scanf("%d", &b);
			int idx = get_rank(1, MAX, 1, b);
			update(1, MAX, 1, idx, -1);
			printf("%d\n", idx);
		}
		else if (a == 2)
		{
			scanf("%d %d", &b, &c);
			update(1, MAX, 1, b, c);
		}
	}
}

int main(void)
{
	input();
	solve();
}