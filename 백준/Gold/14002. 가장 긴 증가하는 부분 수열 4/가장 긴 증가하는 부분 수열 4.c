#include <stdio.h>
#include <string.h>

#define MAX_STACK 1001

int N;
int A[1001];
int dp[1001][1001];
int max_cnt = 1;
int idx = 1;

typedef struct {
	int d[MAX_STACK];
	int end;
	int(*push)(int);
	int(*pop)(int*);
}STACK;
STACK stack;

int stack_push(int d)
{
	if (stack.end >= MAX_STACK)
		return 0;
	stack.d[stack.end++] = d;
	return 1;
}
int stack_pop(int *d)
{
	if (stack.end == 0)
		return 0;
	*d = stack.d[--stack.end];
	return 1;
}

void init_stack()
{
	memset(&stack, 0, sizeof(STACK));
	stack.push = stack_push;
	stack.pop = stack_pop;
}

void init()
{
	memset(dp, 0, sizeof(dp));
	init_stack();
}

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
}

void solve()
{
	int flag = 0;

	for (int i = 1; i <= N; i++)
		dp[1][i] = 1;

	for (int i = 2; i <= N; i++)
	{
		flag = 0;
		for (int j = 1; j <= N; j++)
		{
			if (dp[i - 1][j] == 0)
				continue;

			for (int k = j; k <= N; k++)
			{
				if (A[j] < A[k])
				{
					dp[i][k] = j;
					flag = 1;
					idx = k;
				}
			}
		}
		if (flag == 0)
		{
			max_cnt = i - 1;
			return;
		}
		else
			max_cnt = i;
	}
}

int main(void)
{
	int temp;

	init();
	input();
	solve();

	/*for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}*/

	int temp_i = idx;
	int temp_cnt = max_cnt;
	//printf("%d %d\n", idx, max_cnt);
	while (temp_cnt != 0)
	{
		stack.push(A[temp_i]);
		temp_i = dp[temp_cnt--][temp_i];
	}

	printf("%d\n", max_cnt);
	while (stack.pop(&temp) == 1)
		printf("%d ", temp);
	printf("\n");	
}