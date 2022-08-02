#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MIN_INF -(1<<30)

int N, K;
long long ans;

typedef struct {
	int m, v;
}JEWEL;
JEWEL jewel[300003];
JEWEL temp_sort2[300003];
int bagpack[300003];
int temp_sort[300003];

int heap[300003];
int heap_size;

void push(int v)
{
	int temp;

	heap_size++;
	heap[heap_size] = v;
	
	for (int i = heap_size; i > 1; i /= 2)
	{
		if(heap[i/2] > heap[i])
			break;

		temp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = temp;
	}
}

int pop(int *v)
{
	int temp;

	if (heap_size == 0)
		return 0;

	*v = heap[1];
	heap[1] = heap[heap_size];
	heap[heap_size--] = MIN_INF;

	for (int i = 1; i * 2 <= heap_size;)
	{
		if (heap[i] > heap[i * 2] && heap[i] > heap[i * 2 + 1])
			break;
		
		else if (heap[i * 2] > heap[i * 2 + 1])
		{
			temp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = temp;
			i = i * 2;
		}
		else
		{
			temp = heap[i * 2 + 1];
			heap[i * 2 + 1] = heap[i];
			heap[i] = temp;
			i = i * 2 + 1;
		}
	}

	return 1;
}

void jewel_merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (jewel[i].m < jewel[j].m)
			memcpy(&temp_sort2[k++], &jewel[i++], sizeof(JEWEL));
		else
			memcpy(&temp_sort2[k++], &jewel[j++], sizeof(JEWEL));
	}

	while (i <= mid)	memcpy(&temp_sort2[k++], &jewel[i++], sizeof(JEWEL));
	while (j <= end)	memcpy(&temp_sort2[k++], &jewel[j++], sizeof(JEWEL));

	for (int i = start; i <= end; i++)
		memcpy(&jewel[i], &temp_sort2[i-start], sizeof(JEWEL));
}

void jewel_sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	jewel_sort(start, mid);
	jewel_sort(mid + 1, end);
	jewel_merge(start, end);
}

void bag_merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (bagpack[i] < bagpack[j])
			temp_sort[k++] = bagpack[i++];
		else
			temp_sort[k++] = bagpack[j++];
	}

	while (i <= mid)	temp_sort[k++] = bagpack[i++];
	while (j <= end)	temp_sort[k++] = bagpack[j++];

	for (int i = start; i <= end; i++)
		bagpack[i] = temp_sort[i - start];
}

void bag_sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	bag_sort(start, mid);
	bag_sort(mid + 1, end);
	bag_merge(start, end);
}

void input()
{
	int m, v;

	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &m, &v);
		jewel[i].m = m;
		jewel[i].v = v;
	}

	for (int i = 0; i < K; i++)
		scanf("%d", &bagpack[i]);
}

void solve()
{
	jewel_sort(0, N - 1);
	bag_sort(0, K - 1);

	int idx = 0;
	int pop_v;

	for (int i = 0; i < K; i++)
	{
		while (idx < N && jewel[idx].m <= bagpack[i])
			push(jewel[idx++].v);

		if (heap_size != 0)
		{
			pop(&pop_v);
			ans += pop_v;
		}
	}

	printf("%lld\n", ans);
}

int main(void)
{
	input();
	solve();
}