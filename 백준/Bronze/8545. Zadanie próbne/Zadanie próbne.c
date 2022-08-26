#include <stdio.h>

char str[4];

int main(void)
{
	scanf("%s", str);
	printf("%c%c%c\n", str[2], str[1], str[0]);
}