#include <stdio.h>

#define Abs(a)  ((a<0)?-(a):(a))

int main(void)
{
	long long a, b;
	scanf("%lld %lld", &a, &b);
	printf("%lld\n", Abs(a - b));
}