#include <stdio.h>

long long num[5];

void input()
{
	for (int i = 0; i < 5; i++)
		scanf("%lld", &num[i]);
}

void solve()
{
	long long sum = 0;
	for (int i = 0; i < 5; i++)
		sum += num[i];
	printf("%lld\n", sum);
}

int main(void)
{
	input();
	solve();
}