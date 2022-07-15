#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
double mission[20][20];
double ans[1 << 20] = { 1, };

void input()
{
	scanf("%d", &N);
	for (int r = 0;r < N;r++)
	{
		for (int c = 0;c < N;c++)
		{
			scanf("%lf", &mission[r][c]);
			mission[r][c] /= 100;
		}
	}
}

void solve()
{
	int col_idx, temp;
	for (register int i = 0;i < (1<<N);++i)
	{
		col_idx = 0;
		temp = i;
		while (temp)
		{
			if (temp % 2 == 1)
				++col_idx;
			temp /= 2;
		}

		for (register int j = 0;j < N;++j)
		{
			if (i & (1 << j))	
				continue;

			ans[i | (1 << j)] = Max(ans[i | (1 << j)], ans[i] * mission[j][col_idx]);
		}
	}

	printf("%.8lf\n", ans[(1 << N) - 1]*100);
}

int main(void)
{
	input();
	solve();
}