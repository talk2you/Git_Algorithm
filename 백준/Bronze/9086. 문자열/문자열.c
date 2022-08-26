#include <stdio.h>
#include <string.h>

int N;
char str[1002];

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", str);
		int len = strlen(str);
		printf("%c%c\n", str[0], str[len - 1]);
	}
}

int main(void)
{
	input();
}