#include <stdio.h>
#include <string.h>

#define MAX	100000

char ans[11];
char num[11];
int K;

typedef struct HASH {
	char num[11];
	struct HASH *next;
}HASH;
HASH pool[MAX];
HASH *head[MAX];
int pool_size;

typedef struct QUE {
	char num[11];
	int stage;
}QUE;
QUE que[MAX];
int start, end;

void input()
{
	scanf("%s", num);
	scanf("%d", &K);
}

int make_hash(char n[11])
{
	int h = 5381;
	int i = 0;
	while (n[i])
		h += ((h << 5) + 5 + n[i++]) % MAX;
	h %= MAX;
	return h;
}

int check_hash(char n[11])
{
	int h = make_hash(n);
	HASH *nd = head[h];
	while (nd)
	{
		if (strcmp(nd->num, n) == 0)
			return 0;
		nd = nd->next;
	}

	strcpy(pool[pool_size].num, n);
	pool[pool_size].next = head[h];
	head[h] = &pool[pool_size++];
	return 1;
}

int isFull()
{
	int temp = start - 1;
	if (temp < 0)
		temp += MAX;

	if (temp == end)
		return 1;
	return 0;
}

int isEmpty()
{
	if (start == end)
		return 1;
	return 0;
}

void push(char n[11], int stage)
{
	if (isFull())
		return;

	que[end].stage = stage;
	strcpy(que[end++].num, n);
	end %= MAX;
}

int pop(char n[11], int *stage)
{
	if (isEmpty())
		return 0;

	*stage = que[start].stage;
	strcpy(n, que[start++].num);
	start %= MAX;
	return 1;
}

void max_value(char num[11])
{
	if (strcmp(ans, num) < 0)
		strcpy(ans, num);
}

void solve()
{
	int str_size = strlen(num);
	push(num, 0);

	char pop_num[11], temp_num[11];
	int now_stage = 0, pop_stage = 0;
	while (pop(pop_num, &pop_stage))
	{
		if (pop_stage > K)
		{
			printf("%s\n", ans);
			return;
		}

		if (pop_stage == K)
		{
			max_value(pop_num);
		}

		if (now_stage != pop_stage)
		{
			memset(head, 0, sizeof(head));
			memset(pool, 0, sizeof(pool));
			now_stage = pop_stage;
		}

		for (int i = 0; i < str_size - 1; i++)
		{
			for (int j = i + 1; j < str_size; j++)
			{
				strcpy(temp_num, pop_num);
				char temp = pop_num[i];
				temp_num[i] = temp_num[j];
				temp_num[j] = temp;

				if (temp_num[0] == '0')
					continue;

				if (check_hash(temp_num))
					push(temp_num, now_stage+1);
			}
		}
	}

	printf("-1\n");
}

int main(void)
{
	input();
	solve();
}