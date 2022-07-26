#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))

int N, K;

int student[101];
int locate[101];
int frame[21];
int older[21];
int size;

void merge(int start, int end)
{
	int temp[20];

	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (frame[i] < frame[j])
			temp[k++] = frame[i++];
		else
			temp[k++] = frame[j++];
	}

	while (i <= mid)	temp[k++] = frame[i++];
	while (j <= end)	temp[k++] = frame[j++];

	for (int i = start; i <= end; i++)
	{
		frame[i] = temp[i - start];
	}
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


void input()
{
	scanf("%d", &N);	// 1<=N<=20
	scanf("%d", &K);	// 1<=K<=1000
}

void solve()
{
	int a;
	int min_rec = 1<<20;
	int min_idx = 0;

	for (int i = 0; i < K; i++)
	{
		scanf("%d", &a);
		min_rec = 1 << 20;

		if (size != N)
		{
			if (student[a] == 0)
			{
				student[a] += 1;
				frame[size] = a;
				older[size] = i;
				locate[a] = size;
				size++;
			}
			else
				student[a] += 1;
		}
		else
		{
			int flag = 0;

			for (int j = 0; j < size; j++)
			{
				if (frame[j] == a)
				{
					flag = 1;
					break;
				}

				if (min_rec > student[frame[j]])
				{
					min_rec = student[frame[j]];
					min_idx = j;
				}
				else if (min_rec == student[frame[j]])
				{
					if (older[min_idx] > older[j])
					{
						min_rec = student[frame[j]];
						min_idx = j;
					}
				}
			}

			if (flag == 0)
			{
				student[frame[min_idx]] = 0;
				older[min_idx] = i;
				frame[min_idx] = a;
				student[a] += 1;
			}
			else
			{
				student[a] += 1;
			}
		}
	}

	sort(0, N - 1);

	for (int i = 0; i < N; i++)
	{
		if (frame[i] == 0)
			continue;
		printf("%d ", frame[i]);
	}
	printf("\n");
}

int main(void)
{
	input();
	solve();
}