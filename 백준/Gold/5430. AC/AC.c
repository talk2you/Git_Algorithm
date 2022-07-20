#include <stdio.h>
#include <string.h>

#define MAX_QUE 100003

int N;

char cmd[100003];
int deque[MAX_QUE];
int front, end;

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

int front_push(int n)
{
	if (isFull())
		return 0;

	front--;
	if (front < 0)
		front += MAX_QUE;
	deque[front] = n;
	
	return 1;
}

int front_pop(int *n)
{
	if (isEmpty())
		return 0;

	*n = deque[front++];
	front %= MAX_QUE;

	return 1;
}

int back_push(int n)
{
	if (isFull())
		return 0;

	deque[end++] = n;
	end %= MAX_QUE;
	return 1;
}

int back_pop(int *n)
{
	if (isEmpty())
		return 0;

	--end;
	if (end < 0)
		end += MAX_QUE;
	*n = deque[end];
	return 1;
}

void init()
{
	memset(deque, 0, sizeof(deque));
	front = 0;
	end = 0;
}

void input()
{
	char temp;
	int a;

	scanf("%s", cmd);
	scanf("%d", &N);
	
	scanf(" %1c", &temp);
	if(N == 0)
		scanf(" %1c", &temp);
	for (int i = 0; i < N; i++)
	{
		scanf(" %d %1c", &a, &temp);		
		back_push(a);
	}
}

void solve()
{
	int flag = 0, result = 0;;
	int able_cmd;

	for (int i = 0; cmd[i]; ++i)
	{
		if (cmd[i] == 'R')
			flag ^= 1;
		else if (cmd[i] == 'D')
		{
			if (flag == 0)
			{
				able_cmd = front_pop(&result);

				if (!able_cmd)
				{
					printf("error\n");
					return;
				}
			}
			else
			{
				able_cmd = back_pop(&result);

				if (!able_cmd)
				{
					printf("error\n");
					return;
				}
			}
		}
	}

	if (flag == 0)
	{
		int a;
		printf("[");
		
		if(front_pop(&a))
			printf("%d", a);

		while (front_pop(&a))
			printf(",%d", a);
		printf("]\n");
	}
	else
	{
		int a;
		printf("[");
		
		if(back_pop(&a))
			printf("%d", a);

		while (back_pop(&a))
			printf(",%d", a);
		printf("]\n");
	}
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t)
	{
		init();
		input();
		solve();
	}
}