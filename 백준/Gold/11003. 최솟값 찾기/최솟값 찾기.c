#include <stdio.h>
#include <string.h>

#define INF 1<<30
#define MAX_SIZE 50000003

int N, L;

typedef struct {
	int idx;
	int n;
}QUE;
QUE deque[5000003];
int front, end;
int list[5000003];

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = front - 1;
	if (temp < 0)
		temp += MAX_SIZE;

	if (temp == end)
		return 1;
	return 0;
}

int push_back(int idx, int n)
{
	if (isFull())
		return 0;

	deque[end].idx = idx;
	deque[end++].n = n;
	end %= MAX_SIZE;
	return 1;
}

int push_front(int idx, int n)
{
	if (isFull())
		return 0;

	int front = front - 1;
	if (front < 0)
		front += MAX_SIZE;

	deque[front].idx = idx;
	deque[front].n = n;
	return 1;
}

int pop_front()
{
	if (isEmpty())
		return 0;

	++front;
	front %= MAX_SIZE;
	return 1;
}

int pop_back()
{
	if (isEmpty())
		return 0;

	--end;
	if (end < 0)
		end += MAX_SIZE;
	return 1;
}


void input()
{
	scanf("%d %d", &N, &L);
	for (register int i = 1; i <= N; ++i)
		scanf("%d", &list[i]);
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		if (isEmpty())
		{
			push_back(i, list[i]);
			printf("%d\n", deque[front].n);
			continue;
		}

		while (!isEmpty() && i - deque[front].idx >= L) pop_front();
		while (!isEmpty() && deque[end - 1].n > list[i]) pop_back();

		push_back(i, list[i]);
		printf("%d ", deque[front].n);
	}
	printf("\n");
}

int main(void)
{
	input();
	solve();
}