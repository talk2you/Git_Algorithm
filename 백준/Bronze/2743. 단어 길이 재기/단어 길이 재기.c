#include <stdio.h>

char str[101];

void input()
{
	int i = 0, cnt = 0;
	scanf("%s", str);
	while (str[i++])
		cnt++;
	printf("%d\n", cnt);
}

int main(void)
{
	input();
}