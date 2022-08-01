#include <stdio.h>

int main(void)
{
	char s[101];
	while (1)
	{
		if (scanf(" %[^\n]s", s) == EOF)
			return;
		printf("%s\n", s);
	}
}