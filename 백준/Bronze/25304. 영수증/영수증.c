#include <stdio.h>

int X, N, a, b;
int sum;

void input()
{
	scanf("%d %d", &X, &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a, &b);
		sum += a * b;
	}
}

void solve()
{
	if (sum == X)
		printf("Yes\n");
	else
		printf("No\n");
}

int main(void)
{
	input();
	solve();
}