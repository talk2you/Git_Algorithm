#include <stdio.h>

int N;
int list[1003];

int get_gcd(int num1, int num2)
{
	if (num2 == 0)
		return num1;

	return get_gcd(num2, num1 % num2);
}

void init()
{
	list[1] = 3;
	int r, c;

	for (int t = 2; t <= 1000; t++)
	{
		list[t] = list[t - 1];

		for (r = t; r >= 1; r--)
		{
			if (r == t)
				c = 1;
			else
				c = t;

			for (; c <= t; c++)
			{
				if (get_gcd(r, c) != 1)
					continue;

				list[t]++;
			}
		}
	}
}

void input()
{
	int a;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a);
		printf("%d\n", list[a]);
	}
}

int main(void)
{
	init();
	input();
}