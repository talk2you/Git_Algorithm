#include <stdio.h>

char num[31];

void input()
{
	int a;
	for (int i = 0; i < 28; i++)
	{
		scanf("%d", &a);
		num[a] = 1;
	}
}

void solve()
{
	for (int i = 1; i <= 30; i++)
	{
		if (num[i] == 0)
			printf("%d\n", i);
	}
}

int main(void)
{
	input();
	solve();
}