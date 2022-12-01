#include <stdio.h>

int list[5];
int sum;

void input()
{
	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &list[i]);
		sum += list[i];
	}
}

void merge(int start, int end)
{
	int temp[5];

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

	while (i <= mid) temp[k++] = list[i++];
	while (j <= end) temp[k++] = list[j++];

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
	sort(0, 4);

	printf("%d\n%d\n", sum / 5, list[2]);
}

int main(void)
{
	input();
	solve();
}