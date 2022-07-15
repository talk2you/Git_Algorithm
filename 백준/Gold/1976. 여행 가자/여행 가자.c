#include <stdio.h>

int N, M;
int map[203][203];
int list[1003];

void input()
{
	scanf("%d %d", &N, &M);

	for (register int r = 1;r <= N;r++)
		for (register int c = 1;c <= N;c++)
			scanf("%d", &map[r][c]);

	for (int i = 0;i < M;i++)
		scanf("%d", &list[i]);
}

void solve()
{
	for(register int k=1;k<=N;++k)
		for(register r=1;r<=N;++r)
			for (register c = 1;c <= N;++c)
			{
				if (r == c)
				{
					map[r][c] = 1;
					continue;
				}
				if (map[r][k] == 1 && map[k][c] == 1)
					map[r][c] = 1;
			}

	int prev = list[0];
	for (register i = 1;i < M;i++)
	{
		if (map[prev][list[i]])
			prev = list[i];
		else
		{
			printf("NO\n");
			return;
		}
	}

	printf("YES\n");
	return;
}

int main(void)
{
	input();
	solve();
}