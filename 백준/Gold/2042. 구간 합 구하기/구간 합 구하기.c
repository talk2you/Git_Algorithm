#include <stdio.h>

int N, M, K;
long long data[1000003];
long long tree[4000003];

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; i++)
		scanf("%lld", &data[i]);
}

long long make_tree(int start, int end, int idx)
{
	int mid = (start + end) >> 1;
	if (start == end)
	{
		tree[idx] = data[start];
		return tree[idx];
	}

	tree[idx] = make_tree(start, mid, idx * 2) + make_tree(mid + 1, end, idx * 2 + 1);
	return tree[idx];
}

long long interval_sum(int start, int end, int idx, int left, int right)
{
	int mid = (start + end) >> 1;

	// 구간을 벗어나는 경우
	if (end < left || right < start)
		return 0;
	
	// 구간안에 있는 경우
	if (left <= start && end <= right)
		return tree[idx];

	// 한쪽씩 걸친 경우
	return interval_sum(start, mid, idx * 2, left, right) + interval_sum(mid + 1, end, idx * 2 + 1, left, right);
}

void update(int start, int end, int idx, int target_idx, long long diff_data)
{
	if (target_idx < start || end < target_idx)
		return;

	tree[idx] += diff_data;

	if (start >= end)
		return;

	int mid = (start + end) >> 1;
	update(start, mid, idx * 2, target_idx, diff_data);
	update(mid + 1, end, idx * 2 + 1, target_idx, diff_data);
}

void solve()
{
	int cmd, a, b;
	long long bb;

	make_tree(1, N, 1);

	for (int i = 0; i < M + K; i++)
	{
		scanf("%d", &cmd);

		// data[a] -> b로 바꾸기
		if (cmd == 1)
		{
			scanf(" %d %lld", &a, &bb);
			long long diff = bb - data[a];
			data[a] = bb;
			update(1, N, 1, a, diff);
		}
		// data[a] ~ data[b]의 부분합 출력
		else
		{
			scanf(" %d %d", &a, &b);
			printf("%lld\n", interval_sum(1, N, 1, a, b));
		}
	}
}

int main()
{
	input();
	solve();
}