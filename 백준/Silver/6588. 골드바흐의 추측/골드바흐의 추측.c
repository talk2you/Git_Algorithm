#include <stdio.h>

char num[1000001];
int list[100000];
int list_cnt;
int N;

void init()
{
	for (int i = 2; i <= 1000000; i++)
	{
		if (num[i] == 1)
			continue;

		if(i != 2)
			list[list_cnt++] = i;

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

int input()
{
	scanf("%d", &N);
	if (N == 0)
		return 0;
	return 1;
}

void solve()
{
	int i = 0;
	while(1)
	{
		if (list[i] > N / 2)
		{
			printf("Goldbach's conjecture is wrong.\n");
			break;
		}

		if (num[N - list[i]] == 0)
		{
			printf("%d = %d + %d\n", N, list[i], N-list[i]);
			break;
		}

		i++;
	}
}

int main(void)
{	
	init();

	while(1)
	{
		int ret = input();
		if (ret == 0)
			return 0;

		solve();
	}
}