#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
int ans;
int dp[4][100003];

void input()
{
	scanf("%d", &N);
}

void symbol(char s, int *p, int n)
{
	if (s == '+')	*p += n;
	else if (s == '*') *p *= n;
	else if (s == '-') *p -= n;
	else if (s == '/') *p /= n;
}

void solve()
{
	char s1, s2;
	int d1, d2;
	int prev_max;
	int prev_using_ad;
	int ret_cnt;

	dp[0][0] = 1;
	dp[1][0] = 1;
	dp[2][0] = 1;
	dp[3][0] = 1;

	for (int i = 1; i <= N; i++)
	{
		ret_cnt = 0;

		scanf(" %1c%d %1c%d", &s1, &d1, &s2, &d2);
		
		// 광고 안봤을때 사람 수
		prev_max = Max(dp[0][i - 1], dp[1][i - 1]);

		dp[0][i] = dp[1][i] = dp[2][i] = prev_max;

		if (prev_max > 0)
		{
			symbol(s1, &dp[0][i], d1);
			symbol(s2, &dp[1][i], d2);
		}		
		// dp[0][i-1], dp[1][i-1] 둘다 0이하일경우 무조건 0
		else
			dp[1][i] = dp[0][i] = 0;			

		// 이전에 광고를 한번이라도 봤을때 사람 수
		int temp;
		temp = prev_using_ad = Max(dp[2][i - 1], dp[3][i - 1]);

		dp[3][i] = prev_using_ad;
		symbol(s1, &dp[3][i], d1);
		symbol(s2, &temp, d2);

		dp[3][i] = Max(dp[3][i], temp);

		for (int j = 0; j < 4; j++)
		{
			if (dp[j][i] <= 0)
				ret_cnt++;
		}

		if (ret_cnt == 4)
		{
			printf("ddong game\n");
			return;
		}
	}

	ans = dp[0][N];
	ans = Max(ans, dp[1][N]);
	ans = Max(ans, dp[2][N]);
	ans = Max(ans, dp[3][N]);

	if (ans <= 0)
		printf("ddong game\n");
	else
		printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}