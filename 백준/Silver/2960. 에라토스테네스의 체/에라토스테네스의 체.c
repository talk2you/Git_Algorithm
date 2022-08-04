#include <stdio.h>

int N, K;
int num[1001];

void input()
{
	scanf("%d %d", &N, &K);
}

void solve()
{
	int cnt = 0;
	for (int i = 2; i <= N; i++)
	{
		int j = 1;
		while (1)
		{
			if (num[i*j] == 0)
			{
				cnt++;
				num[i*j] = 1;
			}

			if (cnt == K)
			{
				printf("%d\n", i*j);
				return;
			}

			j++;
			if (i*j > N)
				break;
		}
	}
}

int main(void)
{
	input();
	solve();
}