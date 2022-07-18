#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

char str1[1005];
char str2[1005];
int len1, len2;

int dp[1005][1005];

void input()
{
	scanf("%s %s", str1, str2);
	len1 = strlen(str1);
	len2 = strlen(str2);
}

void solve()
{
	int flag = 0;

	for (int c = 0; c < len1; c++)
	{
		if (str2[0] == str1[c])
			flag = 1;
		if (flag)
			dp[0][c] = 1;
	}

	flag = 0;
	for (int r = 0; r < len2; r++)
	{
		if (str1[0] == str2[r])
			flag = 1;
		if (flag)
			dp[r][0] = 1;
	}

	for (int r = 1; r < len2; ++r)
	{
		for (int c = 1; c < len1; ++c)
		{
			dp[r][c] = Max(dp[r][c - 1], dp[r - 1][c]);
			if (str1[c] == str2[r])
				dp[r][c] = Max(dp[r][c], dp[r - 1][c - 1] + 1);
		}
	}
	
	printf("%d\n", dp[len2-1][len1-1]);
}

int main(void)
{
	input();
	solve();
}