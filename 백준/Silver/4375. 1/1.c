#include <stdio.h>
#include <string.h>

void input()
{
	int n;
	int sum = 0;

	while (scanf("%d", &n) != EOF)
	{
		int i = 1;

		while(1)
		{
			sum = (sum * 10 + 1) % n;
			if (sum == 0)
			{
				printf("%d\n", i);
				break;
			}
			i++;
		}
	}
}

int main(void)
{
	input();
}