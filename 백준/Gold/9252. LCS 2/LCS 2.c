#include <stdio.h>
#include <string.h>

#define Max(a, b)	((a>b)?(a):(b))

char str1[1004], str2[1004];
char ans[1004];
int dp[1004][1004];

void input()
{
	scanf("%s %s", &str1[1], &str2[1]);
}

void solve()
{
	int len1 = strlen(&str1[1]);
	int len2 = strlen(&str2[1]);
	int ans_cnt;

	for (int i = 1; i <= len2; i++)
	{
		for (int j = 1; j <= len1; j++)
		{				
			//printf("[%d][%d] %c %c\n", i, j, str1[i], str2[i])
			if (str1[j] == str2[i])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = Max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	ans_cnt = dp[len2][len1];
	printf("%d\n", ans_cnt);
	
	int i = len2, j = len1, k = 0;
	int now;
	while (i!=0 && j!=0)
	{
		now = dp[i][j];
		
		if (now == dp[i - 1][j])
			i--;
		else if (now == dp[i][j - 1])
			j--;
		else
		{
			ans[k++] = str2[i];
			i--;
			j--;
		}

		if (k >= ans_cnt)
			break;
	}

	for(int i=ans_cnt-1;i>=0;i--)
		printf("%c", ans[i]);
	printf("\n");
}

int main(void)
{
	input();
	solve();
}