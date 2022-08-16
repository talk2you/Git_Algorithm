#include <stdio.h>

#define MOD	1000000007

int N;

int list[10001];
int dp[10001][2];

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &list[i]);
	}
}

void solve()
{
	dp[0][0] = 1;

	// 윈도우잉 인덱스
	int limit = 0;
	for (int i = 0; i < N; i++)
	{
		// 입력값이 -1일 때,
		if (list[i] == -1)
		{
			for (int j = 0; j <= limit; j++)
			{
				// 해당 열 위치 입력값이 -1일 때
				long long temp = 0;

				if (j - 1 >= 0)
					temp = dp[j - 1][0];
				temp += dp[j][0];
				temp += dp[j + 1][0];

				dp[j][1] = (int)(temp % MOD);

			}
		}
		// 제단 높이가 있을 때,
		else
		{
			long long temp = 0;
			if (list[i] - 1 >= 0)
				temp = dp[list[i] - 1][0];
			temp += dp[list[i]][0];
			temp += dp[list[i] + 1][0];
			dp[list[i]][1] = (int)(temp % MOD);
		}

		// 첫번째 열로 복사
		for (int j = 0; j <= limit; j++)
		{
			dp[j][0] = dp[j][1];
			dp[j][1] = 0;
		}		

		// 올라가는 제한값 구하기 (산모양으로 그려지게)
		if (i < (N - 1) / 2)
			limit++;
		else
		{
			if (N % 2 == 0)
			{
				if (i == N / 2 - 1)
					limit++;
			}
			limit--;
		}
	}

	printf("%d\n", dp[0][0]);
}

int main(void)
{
	input();
	solve();
}