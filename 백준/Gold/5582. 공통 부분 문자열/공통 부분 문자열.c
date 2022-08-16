#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

char str1[4002], str2[4002];
int dp[4002][4002];
int ans;

void input()
{
	scanf("%s %s", &str1[1], &str2[1]);
}

void solve()
{
	int len1 = strlen(&str1[1]);
	int len2 = strlen(&str2[1]);

	for (int i = 1; i <= len2; i++)
	{
		for (int j = 1; j <= len1; j++)
		{
			if (str2[i] == str1[j])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				ans = Max(ans, dp[i][j]);
			}
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}