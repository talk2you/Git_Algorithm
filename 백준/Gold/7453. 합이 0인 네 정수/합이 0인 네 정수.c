#include <stdio.h>

#define MAX_SIZE	16000001

int N;
int map[4001][5];
int list[MAX_SIZE];
int temp[MAX_SIZE];
int list_size;

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < 4; j++)
			scanf("%d", &map[i][j]);
}

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (list[i] < list[j])
			temp[k++] = list[i++];
		else
			temp[k++] = list[j++];
	}

	while(i<=mid)	temp[k++] = list[i++];
	while(j<=end)	temp[k++] = list[j++];

	for (int i = start; i <= end; i++)
		list[i] = temp[i - start];
}

void sort(int start, int end)
{
	if (start >= end)
		return;

	int mid = (start + end) >> 1;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int lower_bound(int n, int size)
{
	int start = 0;
	int end = size;
	int mid;

	while (start < end)
	{
		mid = (start + end) >> 1;

		if (n <= list[mid])
			end = mid;
		else
			start = mid + 1;			
	}

	return end;
}

int upper_bound(int n, int size)
{
	int start = 0;
	int end = size;
	int mid;

	while (start < end)
	{
		mid = (start + end) >> 1;
		if (n < list[mid])
			end = mid;
		else
			start = mid + 1;
	}

	return end;
}

void solve()
{
	long long ans = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int sum = map[i][2] + map[j][3];
			list[list_size++] = sum;
		}
	}

	sort(0, list_size - 1);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int sum = map[i][0] + map[j][1];
			int lb = lower_bound(-sum, list_size);
			int ub = upper_bound(-sum, list_size);

			ans += (long long)(ub - lb);
		}
	}

	printf("%lld\n", ans);
}

int main(void)
{
	input();
	solve();
}