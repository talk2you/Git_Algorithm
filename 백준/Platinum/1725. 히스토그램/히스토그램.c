#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))
#define Min(a, b) ((a<b)?(a):(b))

int N;

long long list[100003] = { 0, };
int tree[400003];

void make_tree(int start, int end, int idx)
{
	if (start == end)
	{
		tree[idx] = start;
		return;
	}

	int mid = (start + end) >> 1;
	
	make_tree(start, mid, idx * 2);
	make_tree(mid + 1, end, idx * 2 + 1);
	
	if (list[tree[idx*2]] <= list[tree[idx*2+1]])
		tree[idx] = tree[idx * 2];
	else
		tree[idx] = tree[idx * 2 + 1];
}

int interval_minIdx(int start, int end, int idx, int left, int right)
{
	if (right < start || end < left)
		return -1;
	if (left <= start && end <= right)
		return tree[idx];

	int mid = (start + end) >> 1;
	int a = interval_minIdx(start, mid, idx * 2, left, right);
	int b = interval_minIdx(mid + 1, end, idx * 2 + 1, left, right);
	
	if (a == -1)
		return b;
	if (b == -1)
		return a;

	if (list[a] < list[b])
		return a;
	else
		return b;
}

long long maxArea(int left, int right)
{
	int minIdx = interval_minIdx(1, N, 1, left, right);

	long long ans = list[minIdx] * (right - left + 1);
	if (minIdx + 1 <= right)
	{
		long long area = maxArea(minIdx + 1, right);
		if (ans < area)
			ans = area;
	}
	if (minIdx - 1 >= left)
	{
		long long area = maxArea(left, minIdx - 1);
		if (ans < area)
			ans = area;
	}

	return ans;
}

int input()
{
	scanf("%d", &N);
	
	for (int i = 1; i <= N; i++)
		scanf("%lld", &list[i]);

	return 1;
}

void solve()
{
	make_tree(1, N, 1);

	printf("%lld\n", maxArea(1, N));
}

int main(void)
{
	input();
	solve();
	
	return 0;
}