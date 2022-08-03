#include <stdio.h>

int a, b;
int c, d;

int gcd(int num1, int num2)
{
	if (num2 == 0) 
		return num1;
	return gcd(num2, num1 % num2);
}

void input()
{
	scanf("%d %d %d %d", &a, &b, &c, &d);
}

void solve()
{
	int t, v;
	int div;

	t = (a*d) + (c*b);
	v = b * d;

	div = gcd(t, v);

	printf("%d %d\n", t / div, v / div);
}

int main(void)
{
	input();
	solve();
}