#include <stdio.h>

int map[10][10];
int max;
int max_r = 1, max_c = 1;

void input()
{
	for (int r = 1; r < 10; r++)
	{
		for (int c = 1; c < 10; c++)
		{
			scanf("%d", &map[r][c]);
			if (max < map[r][c])
			{
				max = map[r][c];
				max_r = r;
				max_c = c;
			}
		}
	}
}

void solve()
{
	printf("%d\n%d %d\n", max, max_r, max_c);
}

int main(void)
{
	input();
	solve();
}