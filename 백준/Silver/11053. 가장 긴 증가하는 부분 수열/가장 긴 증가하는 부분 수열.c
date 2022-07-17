#include <stdio.h>

#define MAX_QUE 1003

int N;
int ans =1;
int list[1003];

typedef struct {
	int n[1003];
	int idx[1003];
	int front, end;
}DEQUE;
DEQUE deque;
DEQUE temp_deque;

int isEmpty(DEQUE *deq)
{
	if (deq->front == deq->end)
		return 1;
	return 0;
}

int isFull(DEQUE *deq)
{
	int temp = deq->front - 1;
	if (temp < 0)
		temp += MAX_QUE;

	if (temp == deq->end)
		return 1;
	return 0;
}

int push_end(DEQUE *deq, int n, int idx)
{
	if (isFull(deq))
		return 0;

	deq->idx[deq->end] = n;
	deq->n[deq->end++] = n;
	deq->end %= MAX_QUE;
	return 1;
}

int pop_end(DEQUE *deq, int *n, int *idx)
{
	if (isEmpty(deq))
		return 0;

	--(deq->end);
	if (deq->end < 0)
		deq->end += MAX_QUE;

	*idx = deq->idx[deq->end];
	*n = deq->n[deq->end];
	return 1;
}

int push_front(DEQUE *deq, int n, int idx)
{
	if (isFull(deq))
		return 0;

	--(deq->front);
	if (deq->front < 0)
		deq->front += MAX_QUE;

	deq->idx[deq->front] = idx;
	deq->n[deq->front] = n;

	return 1;
}

int pop_front(DEQUE *deq, int *n, int *idx)
{
	if (isEmpty(deq))
		return 0;

	*idx = deq->n[deq->front];
	*n = deq->n[deq->front++];
	deq->front %= MAX_QUE;
	return 1;
}

void input()
{ 
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		if (isEmpty(&deque))
		{
			push_end(&deque, list[i], i);
			continue;
		}
		
		if (list[i] > deque.n[deque.end - 1])
		{
			push_end(&deque, list[i], i);
			ans++;
			continue;
		}

		int temp_front = deque.front;
		while (list[i] > deque.n[temp_front])
		{
			if(temp_front < deque.end)
				temp_front++;
			else 
				break;
		}
		
		int temp_n, temp_idx;
		temp_n = deque.n[temp_front];
		temp_idx = deque.idx[temp_front];
		deque.n[temp_front] = list[i];
		deque.idx[temp_front] = i;
		push_end(&temp_deque, temp_n, temp_idx);
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}