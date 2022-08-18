#include <stdio.h>

#define INF 0x7FFFFFFFFFFF
#define Min(a, b) ((a<b)?(a):(b))
int N;

typedef struct {
	int r, c;
}MATRIX;
MATRIX matrix[501];

long long dp[501][501];

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &matrix[i].r, &matrix[i].c);
		dp[i][i] = 0;
	}
}

long long search(int start, int end)
{
	if (start == end)
		return dp[start][end];

	if (dp[start][end])
		return dp[start][end];

	long long ret = INF;

	for (int i = start; i < end; i++)
	{
		long long temp = search(start, i) + search(i + 1, end);
		temp += matrix[start].r * matrix[i].c * matrix[end].c;

		ret = Min(ret, temp);
	}
	
	return dp[start][end] = ret;
}

void solve()
{
	search(0, N-1);
	printf("%lld\n", dp[0][N - 1]);
}

int main(void)
{
	input();
	solve();
}