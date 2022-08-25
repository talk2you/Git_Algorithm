#include <stdio.h>
#include <string.h>

void input()
{
	int len1, len2;
	char str[1001];
	
	scanf("%s", str);
	len1 = strlen(str);
	scanf("%s", str);
	len2 = strlen(str);

	if (len1 >= len2)
		printf("go\n");
	else
		printf("no\n");
}

int main(void)
{
	input();
}