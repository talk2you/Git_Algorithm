#include <stdio.h>
#include <string.h>

char arr[50];
typedef struct {
	char c;
	int rank;
}STACK;
STACK stack[50];
int stack_size;

int temp_sum[50];

void push(char c, int rank)
{
	stack[stack_size].c = c;
	stack[stack_size++].rank = rank;
}

int pop(char *c, int *rank)
{
	if (stack_size == 0)
	{
		*c = 'X';
		*rank = -1;

		return 0;
	}

	--stack_size;
	*c = stack[stack_size].c;
	*rank = stack[stack_size].rank;

	return 1;
}

void input()
{
	scanf("%s", arr);
}

void solve()
{
	int len = strlen(arr);
	int now_rank = 1;

	for (int i = 0; i < len; i++)
	{
		if (arr[i] == '(' || arr[i] == '[')
			push(arr[i], now_rank++);
		else
		{
			char pop_c;
			int pop_rank;

			if (pop(&pop_c, &pop_rank) == 0)
			{
				printf("0\n");
				return;
			}

			if (arr[i] == ')' && pop_c == '(')
			{
				--now_rank;
				temp_sum[now_rank] += temp_sum[now_rank + 1] > 0 ? temp_sum[now_rank + 1] * 2 : 2;
				temp_sum[now_rank + 1] = 0;
			}
			else if (arr[i] == ']' && pop_c == '[')
			{
				--now_rank;
				temp_sum[now_rank] += temp_sum[now_rank + 1] > 0 ? temp_sum[now_rank + 1] * 3 : 3;
				temp_sum[now_rank + 1] = 0;
			}
			else
			{
				printf("0\n");
				return;
			}
		}
	}


	if (stack_size != 0)
	{
		printf("0\n");
		return;
	}

	printf("%d\n", temp_sum[1]);
}

int main(void)
{
	input();
	solve();
}