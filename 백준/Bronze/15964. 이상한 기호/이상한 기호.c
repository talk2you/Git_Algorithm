#include <stdio.h>

long long A, B;

void input()
{
	scanf("%lld %lld", &A, &B);
}

void solve()
{
	long long ans = (A + B)*(A - B);
	printf("%lld\n", ans);
}

int main(void)
{
	input();
	solve();
}