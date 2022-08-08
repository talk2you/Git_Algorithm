#include <stdio.h>

#define INF	0x3fffffff

int N, M;
long long K;

int list[101][101];

void init()
{
	for (int r = 0; r <= 100; r++)
	{
		for (int c = 0; c <= 100; c++)
		{
			if (r == 0 && c == 0)
				list[r][c] = 0;
			else if (r == 0 || c == 0)
				list[r][c] = 1;
			else
			{
				if (list[r - 1][c] == INF || list[r][c - 1] == INF)
					list[r][c] = INF;
				else
				{
					list[r][c] = list[r - 1][c] + list[r][c - 1];

					if (list[r][c] >= INF)
						list[r][c] = INF;
				}
			}
		}
	}
}

void input()
{
	scanf("%d %d %lld", &N, &M, &K);
}

void solve()
{
	int r = M, c = N;
	long long k = K;

	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", list[i][j]);
		}
		printf("\n");
	}*/

	if (list[r][c] < k)
	{
		printf("-1\n");
		return;
	}

	while (1)
	{
		if (r == 0 || c == 0)
		{
			while(r--)
				printf("z");
			while(c--)
				printf("a");

			printf("\n");
			return;
		}

		/*printf("now : %d\n", list[r][c]);
		printf("left : %d\n", list[r][c - 1]);
		printf("up : %d\n", list[r - 1][c]);
		printf("k : %d\n", k);*/

		if (list[r][c - 1] >= k)
		{
			printf("a");
			c--;
		}
		else
		{
			printf("z");
			k = k - list[r][c - 1];
			r--;			
		}
	}
}

int main(void)
{
	init();
	input();
	solve();
}