#include <stdio.h>

int N;
int ans;

char num[4000001];
int list[300000];
int list_size;

void init()
{
	for (int i = 2; i <= 4000000; i++)
	{
		if (num[i])
			continue;

		list[list_size++] = i;

		int j = 2;
		while (1)
		{
			if (i*j > 4000000)
				break;

			num[i*j] = 1;
			j++;

		}
	}
}

void input()
{
	scanf("%d", &N);
}

void solve()
{
	int sum = 0;
	int j = 0;

	for (int i = 0; list[i] <= N; i++)
	{
		while (1)
		{
			if (sum == N)
			{
				ans++;
				sum -= list[i];
				break;
			}
			else if (sum > N)
			{
				sum -= list[i];
				break;
			}

			sum += list[j++];
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}