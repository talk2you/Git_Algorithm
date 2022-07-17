#include <stdio.h>
#include <string.h>

#define MAX_QUE 100003

char list[100003];

int deque[100003];
int front, end;

void init()
{
	front = end = 0;
}

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
		temp += MAX_QUE;
	if (temp == end)	
		return 1;
	return 0;
}

int push_front(int idx)
{
	if (isFull())		
		return 0;
	
	if (--front < 0)	
		front += MAX_QUE;
	deque[front] = idx;
	return 1;
}

int pop_front(int *idx)
{
	if (isEmpty())
		return 0;

	*idx = deque[front++];
	front %= MAX_QUE;
	return 1;
}

int push_back(int idx)
{
	if (isFull())
		return 0;

	deque[end++] = idx;
	end %= MAX_QUE;
	return 1;
}

void input()
{
	scanf(" %s", list);	
}

void solve()
{
	register int i = 0;
	int idx, dummy;

	while (list[i])
	{
		if(list[i] == '1')
			push_back(i);
		++i;
	}
	
	while (pop_front(&idx))
	{
		list[idx] = 'X';

		if (list[idx + 1] == '0')
		{
			push_front(idx + 1);
			list[idx + 1] = '1';
		}
		else if (list[idx + 1] == '1')
		{
			pop_front(&dummy);
			list[idx + 1] = '0';
		}

		if (list[idx - 1] == '0')
		{
			push_front(idx - 1);
			list[idx - 1] = '1';
		}
	}

	for (register int i = strlen(list); i >= 0; --i)
	{
		if (list[i] == '0')
		{
			printf("no\n");
			return;
		}
	}
	printf("yes\n");
}

int main(void)
{
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		printf("#%d ", t);
		solve();
	}
}