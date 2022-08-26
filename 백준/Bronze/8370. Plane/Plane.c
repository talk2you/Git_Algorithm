#include <stdio.h>

long long n1, n2, k1, k2;

void input()
{
	long long sum = 0;
	scanf("%lld %lld %lld %lld", &n1, &k1, &n2, &k2);
	sum = n1 * k1 + n2 * k2;
	printf("%lld\n", sum);
}

int main(void)
{
	input();
}