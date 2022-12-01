#include <stdio.h>

int map[101][101];
int N;

void input()
{
	scanf("%d", &N);

	int pr, pc;

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &pr, &pc);

		for (int r = pr; r < pr + 10; r++)
		{
			for (int c = pc; c < pc + 10; c++)
			{
				map[r][c] = 1;
			}
		}
	}
}

void solve()
{
	int ans = 0;

	for (int r = 0; r <= 100; r++)
	{
		for (int c = 0; c <= 100; c++)
		{
			if (map[r][c])
				ans++;
		}
	}	
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}