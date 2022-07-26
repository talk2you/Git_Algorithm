#include <stdio.h>

#define LEN 100003

int N, M;
int list[LEN];

void input()
{
	scanf("%d", &N);
	for (int i = 0;i < N;i++)
		scanf("%d", &list[i]);
}

void merge(int start, int end)
{
	int temp[LEN];
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

	while (i <= mid)
		temp[k++] = list[i++];
	while (j <= end)
		temp[k++] = list[j++];

	for (int i = start;i <= end;i++)
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

int bin_search(int a)
{
	int start = 0, end = N - 1;
	int mid;

	while (start <= end)
	{
		mid = (start + end) >> 1;

		if (a < list[mid])
		{
			end = mid-1;
		}
		else if (a > list[mid])
		{
			start = mid + 1;
		}
		else
			return 1;
	}

	return 0;
}

void solve()
{
	int a;

	sort(0, N - 1);

	scanf("%d", &M);
	for (int i = 0;i < M;i++)
	{
		scanf("%d", &a);
		if (bin_search(a))
			printf("1\n");
		else
			printf("0\n");
	}
}

int main(void)
{
	input();
	solve();
}