#include <stdio.h>

int N, M;
int ans;

int list[10003];

void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

void solve()
{
	long long sum;
	for (int i = 0; i < N; i++)
	{
		sum = 0;

		for (int j = i; j < N; j++)
		{
			sum += (long long)list[j];

			if (sum == M)
			{
				ans++;
				break;
			}
			else if (sum > M)
				break;
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}