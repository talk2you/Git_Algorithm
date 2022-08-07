#include <stdio.h>

int list[6];
int match[6] = { 1,1,2,2,2,8 };

int main(void)
{
	for (int i = 0; i < 6; i++)
		scanf("%d", &list[i]);

	for (int i = 0; i < 6; i++)
		printf("%d ", match[i] - list[i]);
	printf("\n");
}