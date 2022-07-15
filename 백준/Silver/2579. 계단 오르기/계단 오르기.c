#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;

short stair[303];
int DP[2][303];

void input()
{
	scanf("%d", &N);

	for (register int i = 0;i < N;++i)
		scanf("%hd", &stair[i]);
}

void solve()
{
	DP[0][0] = stair[0];
	DP[1][0] = 0;

	DP[0][1] = stair[1] + stair[0];
	DP[1][1] = stair[1];

	DP[0][2] = stair[2] + stair[1];
	DP[1][2] = stair[2] + stair[0];

	for (register int i = 3;i < N;++i)
	{
		DP[0][i] = (int)stair[i] + DP[1][i - 1];
		DP[1][i] = (int)stair[i] + Max(DP[0][i-2], DP[1][i-2]);
	}

	printf("%d\n", Max(DP[0][N - 1], DP[1][N - 1]));	
}

int main(void)
{
	input();
	solve();
}