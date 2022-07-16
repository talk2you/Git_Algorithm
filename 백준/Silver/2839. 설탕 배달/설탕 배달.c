#include <stdio.h>

int N;

void input()
{
	scanf("%d", &N);
}

void solve()
{
	int dp5 = N / 5;

	if (N - dp5 * 5 == 0)
	{
		printf("%d\n", dp5);
		return;
	}

	while (dp5)
	{
		if ((N - dp5 * 5) % 3 == 0)
		{
			printf("%d\n", dp5 + (N - dp5 * 5) / 3);
			return;
		}
		dp5--;
	}

	if (N % 3 == 0)
	{
		printf("%d\n", N / 3);
		return;
	}

	printf("-1\n");
}

int main(void)
{
	input();
	solve();
}