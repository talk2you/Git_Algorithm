#include <stdio.h>

#define MAX 1000003

int K, N;

int list[103];

long long heap[MAX];
int heap_size;
int pop_cnt;

void push(long long n)
{
	long long temp;
	heap_size++;
	heap[heap_size] = n;

	for (int i = heap_size; i > 1; i /= 2)
	{
		if (heap[i / 2] < heap[i])
			break;

		temp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = temp;
	}
}

int pop(long long *n)
{
	long long temp;

	if (heap_size == 0)
		return 0;

	pop_cnt++;

	*n = heap[1];
	heap[1] = heap[heap_size];
	heap[heap_size--] = (long long)2 << 30;

	for (int i = 1; i * 2 <= heap_size;)
	{
		if (heap[i] < heap[i * 2] && heap[i] < heap[i * 2 + 1])
			break;

		else if (heap[i * 2] < heap[i * 2 + 1])
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

void input()
{
	scanf("%d %d", &K, &N);

	for (int i = 0; i < K; i++)
	{
		scanf("%d", &list[i]);
		push((long long)list[i]);
	}
}

void solve()
{
	long long n;
	while (pop(&n))
	{
		if (pop_cnt >= N)
			break;
		
		for (int i = 0; i < K; i++)
		{
			long long value = n * list[i];

			if (value >= (long long)2 << 30)
				break;

			push(value);

			if (n % list[i] == 0)
				break;
		}
	}
	printf("%lld\n", n);
}

int main(void)
{
	input();
	solve();
}