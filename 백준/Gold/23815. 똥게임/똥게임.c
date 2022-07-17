#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
int ans;
int dp[2][100003];

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

	dp[0][0] = 1;
	dp[1][0] = 1;

	for (register int i = 1; i <= N; ++i)
	{
		scanf(" %1c%d %1c%d", &s1, &d1, &s2, &d2);
		
		// 광고 안봤을때 사람 수 계산
		int temp1, temp2;
		temp1 = temp2 = dp[0][i - 1];

		if (dp[0][i - 1] > 0)
		{
			symbol(s1, &temp1, d1);
			symbol(s2, &temp2, d2);

			dp[0][i] = Max(temp1, temp2);
		}
		// dp[0][i-1], dp[1][i-1] 둘다 0이하일경우 무조건 0
		else
			dp[0][i] = 0;

		// 이전에 광고를 한번이라도 봤을때 사람 수
		temp1 = dp[1][i - 1];
		temp2 = dp[1][i - 1];
				
		symbol(s1, &temp1, d1);
		symbol(s2, &temp2, d2);

		dp[1][i] = Max(temp1, temp2);
		dp[1][i] = Max(dp[1][i], dp[0][i-1]);

		// 둘다 0일때 똥게임
		if (dp[0][i] <= 0 && dp[1][i] <= 0)
		{
			printf("ddong game\n");
			return;
		}
	}

	ans = dp[0][N];
	ans = Max(ans, dp[1][N]);

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}