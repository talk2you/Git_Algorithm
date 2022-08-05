#include <stdio.h>

char P[1000002];
int K;

int num[1000001];
int list[100000];
int list_size;

void init()
{
	for (int i = 2; i <= 1000000; i++)
	{
		if (num[i])
			continue;

		list[list_size++] = i;

		int j = 2;
		while (1)
		{
			if (i*j > 1000000)
				break;
			
			num[i*j] = 1;
			j++;
		}
	}
}

void input()
{
	scanf("%s %d", P, &K);
}

int check(int num)
{
	int sum = 0;
	for (int i = 0; P[i]; i++)
		sum = (sum * 10 + P[i] - '0') % num;

	if (sum == 0)
		return 1;
	return 0;
}

void solve()
{
	for (int i = 0; list[i] < K && i<list_size; i++)
	{
		if (check(list[i]))
		{
			printf("BAD %d\n", list[i]);
			return;
		}
	}

	printf("GOOD\n");
}

int main(void)
{
	init();
	input();
	solve();
}