#include <stdio.h>

int R, S;

int main(void)
{
	scanf("%d %d", &R, &S);
	int temp = R * 8 + S * 3 - 28;
	if (temp < 0)
		temp = 0;
	printf("%d\n", temp);
}