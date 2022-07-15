#include <stdio.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))

int N, P;
int map[20][20];
int DP[1 << 16];
char power[20];
int ans = INF;

void init()
{
	for (int i = 1;i < (1 << 16);i++)
		DP[i] = INF;
}

void input()
{
	scanf("%d", &N);

	for (int r = 0;r < N;r++)
		for (int c = 0;c < N;c++)
			scanf("%d", &map[r][c]);

	scanf("%s %d", power, &P);
}

void solve()
{
	int temp, cnt;
	int y_cnt = 0;
	
	// 예외 1. P == 0일 경우, 출력 0
	if (P == 0)
	{
		printf("0\n");
		return;
	}

	// 예외 2. Y 개수 >= P 일경우, 출력 0
	for (int i = 0;i < N;i++)
	{
		if (power[i] == 'Y')
			y_cnt++;
	}
	if (y_cnt >= P)
	{
		printf("0\n");
		return;
	}

	// DP 발전소가 켜있는 상태만 고를때 0으로 초기화
	for (int t = 0;t < N;t++)
		if (power[t] == 'Y')
			DP[1 << t] = 0;
	
	for (int i = 1;i < 1<<N;i++)
	{
		temp = i;
		cnt = 0;

		while (temp)
		{
			if (temp % 2 == 1)
				cnt++;
			temp /= 2;
		}

		// 현재 기준값이 INF면 다음 상태로 이동
		if (DP[i] == INF)
			continue;

		//printf("%d %d\n", i, cnt);

		for (int j = 0;j < N;j++)
		{
			if (i & (1 << j))
				continue;
			
			for (int k = 0;k < N;k++)
			{
				if (i & (1<<k))
				{
					int add;
					if (power[j] == 'Y')
						add = 0;
					else
						add = map[k][j];

					//printf("DP[%d] %d %d ", i | (1 << j), DP[i | (1 << j)], DP[i] + add);
					DP[i | (1 << j)] = Min(DP[i | (1 << j)], DP[i] + add);

					if (cnt + 1 == P)
						ans = Min(ans, DP[i | (1 << j)]);

					//printf("\t\t>> min DP[%d] %d\n", i | (1 << j), DP[i | (1 << j)]);
				}
			}
		}
	}

	if (ans == INF)
		ans = -1;
	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}