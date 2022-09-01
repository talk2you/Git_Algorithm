#include <stdio.h>
#include <string.h>

char str[1002];
int N;

int main(void)
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", str);
		int len = strlen(str);
		if (6 <= len && len <= 9)
			printf("yes\n");
		else
			printf("no\n");
	}
}