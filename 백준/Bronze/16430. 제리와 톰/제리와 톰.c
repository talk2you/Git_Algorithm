#include <stdio.h>

int A, B;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a%b);
}


void input()
{
	scanf("%d %d", &A, &B);
	int ans1 = B - A;

	int div = gcd(ans1, B);
	printf("%d %d\n", ans1 / div, B / div);
}

int main(void)
{
	input();
}