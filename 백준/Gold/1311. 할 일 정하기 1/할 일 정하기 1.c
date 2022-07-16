#include <stdio.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))

int N;
int dp[1 << 20];

int map[25][25];
int ans = INF;

void init()
{
	for (int i = 0;i < 1 << 20;i++)
		dp[i] = INF;
}

void input()
{
	scanf("%d", &N);

	for (int r = 0;r < N;r++)
		for (int c = 0;c < N;c++)
			scanf("%d", &map[r][c]);
}

void solve()
{
	for (int i = 0;i < N;i++)
		dp[1 << i] = map[i][0];

	for (int i = 1;i < 1 << N;i++)
	{
		int temp = i;
		int cnt = 0;
		while (temp)
		{
			if(temp%2==1)
				cnt++;
			temp /= 2;
		}

		for (int j = 0;j < N;j++)
		{
			if (i & 1 << j)
				continue;
			
			dp[i | 1 << j] = Min(dp[i | 1 << j], dp[i] + map[j][cnt]);
			//printf("dp[%d] %d, dp[%d] %d + map[%d][%d] %d\n", i | 1 << j, dp[i | 1 << j], i, dp[i], j, cnt, map[j][cnt]);
		}
	}

	printf("%d\n", dp[(1<<N)-1]);
}

int main(void)
{
	init();
	input();
	solve();
}