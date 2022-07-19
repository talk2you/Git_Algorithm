#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))

int N, M;

int list[100003];
typedef struct {
	int min, max;
}SEG_TREE;
SEG_TREE seg_tree[300000];

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

SEG_TREE* make_seg(int idx, int start, int end)
{
	if (start == end)
	{
		seg_tree[idx].min = list[start];
		seg_tree[idx].max = list[end];
		return &seg_tree[idx];
	}

	int mid = (start + end) >> 1;
	SEG_TREE* left = make_seg(idx * 2, start, mid);
	SEG_TREE* right = make_seg(idx * 2 + 1, mid + 1, end);

	seg_tree[idx].min = Min(left->min, right->min);
	seg_tree[idx].max = Max(left->max, right->max);
	return &seg_tree[idx];
}

void find(int start, int end, int idx, int a, int b, int *min, int *max)
{
	int left_min, left_max;
	int right_min, right_max;

	if (end < a || b < start)
	{
		*min = 1 << 30;
		*max = 0;
		return;
	}

	int mid = (start + end) >> 1;

	if (a <= start && end <= b)
	{
		*min = seg_tree[idx].min;
		*max = seg_tree[idx].max;
		return;
	}
	else
	{
		find(start, mid, idx * 2, a, b, &left_min, &left_max);
		find(mid+1, end, idx * 2+1, a, b, &right_min, &right_max);

		*min = Min(left_min, right_min);
		*max = Max(left_max, right_max);
	}
}

void solve()
{
	int a, b;
	int min, max;

	make_seg(1, 0, N - 1);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);

		find(0, N - 1, 1, a - 1, b-1, &min, &max);
		printf("%d %d\n", min, max);
	}
}

int main(void)
{
	input();
	solve();
}