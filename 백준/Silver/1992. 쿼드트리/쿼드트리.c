#include <stdio.h>
#include <string.h>

#define MAX_STR 10000

int N;
char map[70][70];

typedef struct {
	char str[MAX_STR];
	int n;
}STACK;
STACK stack[32];
int stack_size;

char temp_str[MAX_STR];

int push(char str[MAX_STR], int n)
{
	if (stack_size >= 32)
		return 0;

	strcpy(stack[stack_size].str, str);
	stack[stack_size].n = n;
	stack_size++;

	return 1;
}

int pop(char str[MAX_STR], int *n)
{
	if (stack_size == 0)
		return 0;

	stack_size--;
	strcpy(str, stack[stack_size].str);
	*n = stack[stack_size].n;

	return 1;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0;i < N;i++)
		scanf("%s", &map[i]);
}

char conquer(int r1, int r2, int c1, int c2, char ret[4], int idx)
{
	// 전부 다 같은 문자열인 경우
	int cnt = 0;
	char check = ret[0];

	if (check != 'X')
	{
		for (int i = 0;i < 4;i++)
			if (ret[i] == check)
				cnt++;

		if (cnt == 4)
		{
			/*for (int i = 0;i < 4;i++)
				printf("%c", ret[i]);
			printf(" idx:%d\n", idx);*/

			return check;
		}
	}

	// 1개 이상 다른 문자열이 있는 경우
	char temp[4][MAX_STR] = { 0, };
	int visit[4] = { 0, };
	int temp_idx;

	while (stack_size)
	{
		char wait_idx = stack[stack_size - 1].n;
		if (ret[wait_idx] == 'X' && visit[wait_idx] == 0)
		{
			visit[wait_idx] = 1;
			pop(temp[wait_idx], &temp_idx);
			//printf("%d << %s\n", wait_idx, temp[wait_idx]);
		}
		else
			break;
	}
	

	int temp_size = 0;
	memset(temp_str, 0, sizeof(temp_str));
	for (int i = 0;i < 4;i++)
	{
		if (ret[i] == 'X')
		{
			temp_str[temp_size++] = '(';
			strcat(temp_str, temp[i]);
			temp_size += strlen(temp[i]);
			temp_str[temp_size++] = ')';
		}
		else
			temp_str[temp_size++] = ret[i];
	}
	temp_str[temp_size] = 0;

	//printf("push : ");
	push(temp_str, idx);
	//printf("%s", temp_str);
	//printf(" idx:%d\n", idx);
	return 'X';
}

void divide(int r1, int r2, int c1, int c2, char *ret, int idx)
{
	int r_mid = (r2 + r1) >> 1;
	int c_mid = (c2 + c1) >> 1;
	char stat[4];

	if (r1 >= r2 || c1 >= c2)
	{
		*ret = map[r1][c1];
		return;
	}

	divide(r1, r_mid, c1, c_mid, &stat[0], 0);
	divide(r1, r_mid, c_mid + 1, c2, &stat[1], 1);
	divide(r_mid + 1, r2, c1, c_mid, &stat[2], 2);
	divide(r_mid + 1, r2, c_mid + 1, c2, &stat[3], 3);
	*ret = conquer(r1, r2, c1, c2, stat, idx);
}

void solve()
{
	char ret;
	int idx;
	divide(0, N - 1, 0, N - 1, &ret, 0);

	if (stack_size)
	{
		pop(temp_str, &idx);
		printf("(%s)\n", temp_str);
	}
	else
		printf("%c\n", ret);
}


int main(void)
{
	input();
	solve();
}