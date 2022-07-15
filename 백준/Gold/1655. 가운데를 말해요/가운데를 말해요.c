#include <stdio.h>

int N;

typedef struct {
	int heap[100003];
	int end;
}PRIORITY_QUE;
PRIORITY_QUE low_que, high_que;

enum lh{low, high};

void push(PRIORITY_QUE *que, enum lh flag, int data)
{
	int temp;

	que->heap[++(que->end)] = data;

	for (int i = que->end; i > 1; i /= 2)
	{
		if (flag == high)
		{
			if (que->heap[i] > que->heap[i / 2])
				break;
		}
		else
		{
			if (que->heap[i] < que->heap[i / 2])
				break;
		}

		temp = que->heap[i];
		que->heap[i] = que->heap[i / 2];
		que->heap[i / 2] = temp;
	}
}

int pop(PRIORITY_QUE *que, enum lh flag)
{
	int temp, ret;

	if (que->end == 0)
		return -1;

	ret = que->heap[1];
	que->heap[1] = que->heap[que->end];

	if(flag == high)
		que->heap[(que->end)--] = (int)(((long long)1 << 31) - 1);
	else
		que->heap[(que->end)--] = (1 << 31);

	for (int i = 1; i*2 <= que->end;)
	{
		if (flag == high)
		{
			if (que->heap[i] < que->heap[i * 2] && que->heap[i] < que->heap[i * 2 + 1])
				break;
			else if (que->heap[i * 2] < que->heap[i * 2 + 1])
			{
				temp = que->heap[i];
				que->heap[i] = que->heap[i * 2];
				que->heap[i * 2] = temp;

				i = i * 2;
			}
			else
			{
				temp = que->heap[i];
				que->heap[i] = que->heap[i * 2 + 1];
				que->heap[i * 2 + 1] = temp;

				i = i * 2 + 1;
			}
		}
		else
		{
			if (que->heap[i] > que->heap[i * 2] && que->heap[i] > que->heap[i * 2 + 1])
				break;
			else if (que->heap[i * 2] > que->heap[i * 2 + 1])
			{
				temp = que->heap[i];
				que->heap[i] = que->heap[i * 2];
				que->heap[i * 2] = temp;

				i = i * 2;
			}
			else
			{
				temp = que->heap[i];
				que->heap[i] = que->heap[i * 2 + 1];
				que->heap[i * 2 + 1] = temp;

				i = i * 2 + 1;
			}
		}
	}

	return ret;
}

void input()
{
	scanf("%d", &N);
}

void solve()
{
	int n, temp = 0, comp;
	int input_cnt = 0;

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &n);
		input_cnt++;

		if (input_cnt == 1)
		{
			temp = n;
			printf("%d\n", temp);
			continue;
		}

		if (temp > n)
			push(&low_que, low, n);
		else
			push(&high_que, high, n);

		if (input_cnt % 2 == 0)
		{
			if (high_que.end > low_que.end)
			{
				comp = high_que.heap[1];
				if (temp > comp)
				{					
					comp = pop(&high_que, high);
					push(&high_que, high, temp);
					temp = comp;
				}
			}
			else
			{
				comp = low_que.heap[1];
				if (temp > comp)
				{
					comp = pop(&low_que, low);
					push(&high_que, high, temp);
					temp = comp;
				}
			}
		}
		else
		{	
			if (high_que.end > low_que.end)
			{
				push(&low_que, low, temp);
				temp = pop(&high_que, high);
			}
			else if(high_que.end < low_que.end)
			{
				push(&high_que, high, temp);
				temp = pop(&low_que, low);
			}
		}

		printf("%d\n", temp);
	}
}

int main(void)
{
	input();
	solve();
}