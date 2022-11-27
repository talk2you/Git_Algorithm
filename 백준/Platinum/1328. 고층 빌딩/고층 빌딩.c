#include <stdio.h>

#define MOD 1000000007

int N, L, R;
int dp[103][103][103];
int pascal[103][103];

// 대각선 파스칼 삼각형
void init()
{
	pascal[1][1] = 1;
	pascal[2][1] = 1;
	pascal[1][2] = 1;

	int r, c;
	int n = 3;

	r = n;
	c = 1;
	while (r <= 100)
	{
		while (c <= n)
		{
			pascal[r][c] = (pascal[r][c - 1] + pascal[r - 1][c]) % MOD;
			r--;
			c++;
		}
		n++;

		r = n;
		c = 1;
	}
}

int main(void)
{
	int r, c;

	init();

	scanf("%d %d %d", &N, &L, &R);

	// 초기값
	dp[1][1][1] = 1;
	dp[2][1][2] = 1;
	dp[2][2][1] = 1;
	dp[3][1][2] = 1;
	dp[3][1][3] = 1;
	dp[3][2][1] = 1;
	dp[3][2][2] = 2;
	dp[3][3][1] = 1;

	if (N > 3)
	{
		// 파스칼 삼각형 + 점화식 N[n-1] * (n-2) + N-1[n-1]
		for (int i = 4; i <= N; i++)
		{
			for (int j = 2; j < N; j++)
			{
				long long prd = ((long long)dp[i - 1][j][1] * (i - 2)) % MOD;
				prd += (dp[i - 1][j - 1][1]) % MOD;

				r = j;
				c = 1;
				while (c <= j)
				{
					dp[i][r][c] = ((long long)pascal[r][c] * prd) % MOD;
					r--;
					c++;
				}
			}			
		}

		r = N;
		c = 1;
		while (c <= N)
		{
			dp[N][r][c] = pascal[r][c];
			r--;
			c++;
		}

	}

	printf("%d\n", dp[N][L][R]);
}