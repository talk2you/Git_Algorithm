#include <stdio.h>
#include <string.h>

#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))

int N, M;
int ans = 0;

int map[1010][1010];

void input()
{
	char str[1010];
	scanf("%d %d", &N, &M);
	for (int r = 1; r <= N; r++)
	{
		scanf(" %s", str);
		int len = strlen(str);
		for (int c = 0; c < len; c++)
			map[r][c+1] = str[c] - '0';
	}
}

void solve()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (map[r][c] != 0)
			{
				map[r][c] = Min(map[r - 1][c - 1], Min(map[r - 1][c], map[r][c - 1])) + 1;
				ans = Max(ans, map[r][c]);
			}
		}
	}

	printf("%d\n", ans*ans);
}

int main(void)
{
	input();
	solve();
}