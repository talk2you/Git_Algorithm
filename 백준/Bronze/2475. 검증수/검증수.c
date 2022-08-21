#include <stdio.h>

int list[5];
int ans;

void input()
{
	for (int i = 0; i < 5; i++)
		scanf("%d", &list[i]);
}

void solve()
{
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		list[i] *= list[i];
		sum += list[i];
	}

	ans = sum % 10;
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}