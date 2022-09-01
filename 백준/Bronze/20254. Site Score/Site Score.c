#include <stdio.h>

void input()
{
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	printf("%d\n", a * 56 + b * 24 + c * 14 + d * 6);
}

int main(void)
{
	input();
}