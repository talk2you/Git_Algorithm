#include <stdio.h>

int N, K;
int list[500003];
int temp[500003];
int cnt;
int ans = -1;

void input()
{
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		cnt++;
	
		if (list[i] < list[j])
			temp[k++] = list[i++];
		else
			temp[k++] = list[j++];

		if (cnt == K)
			ans = temp[k - 1];
	}

	while (i <= mid)
	{
		cnt++;
		temp[k++] = list[i++];
		if (cnt == K)
			ans = temp[k - 1];
	}
	while (j <= end)
	{
		cnt++;
		temp[k++] = list[j++];
		if (cnt == K)
			ans = temp[k - 1];
	}

	for (i = start; i <= end; i++)
		list[i] = temp[i - start];
}

void sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

void solve()
{
	sort(0, N - 1);

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}