#include <stdio.h>

int N, k;
int score[1002];

void input()
{
	scanf("%d %d", &N, &k);

	for (int i = 0; i < N; i++)
		scanf("%d", &score[i]);
}

void merge(int start, int end)
{
	int temp[1002];
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (score[i] > score[j])
			temp[k++] = score[i++];
		else
			temp[k++] = score[j++];
	}

	while(i<=mid)	temp[k++] = score[i++];
	while(j<=end)	temp[k++] = score[j++];

	for (int i = start; i <= end; i++)
		score[i] = temp[i - start];
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

void solve()
{
	sort(0, N);
	printf("%d\n", score[k - 1]);
}

int main(void)
{
	input();
	solve();
}