#include <stdio.h>

char str[101];

void input()
{
	int i = 0;
	scanf("%s", str);

	while (str[i])
	{
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] += ('A' - 'a');
		else
			str[i] += ('a' - 'A');
		i++;
	}

	printf("%s\n", str);
}

int main(void)
{
	input();
}