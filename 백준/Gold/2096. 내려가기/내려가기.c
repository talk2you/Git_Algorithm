#include <stdio.h>
#include <string.h>

#define INF 1<<30
#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))

int N;

int minDP[3], maxDP[3];
int min_ans = INF;
int max_ans = -1;

void solve(int list[3])
{
	int tempDP[3] = { INF, INF, INF };

	for (int i = 0; i < 3; i++)
	{
		for (int j = i - 1; j <= i + 1; j++)
		{
			if (j < 0 || j >= 3)
				continue;

			tempDP[i] = Min(tempDP[i], minDP[j] + list[i]);
		}
	}

	for (int i = 0; i < 3; i++)
		minDP[i] = tempDP[i];

	for (int i = 0; i < 3; i++)
	{
		for (int j = i - 1; j <= i + 1; j++)
		{
			if (j < 0 || j >= 3)
				continue;

			tempDP[i] = Max(tempDP[i], maxDP[j] + list[i]);
		}
	}

	for (int i = 0; i < 3; i++)
		maxDP[i] = tempDP[i];	
}

void input()
{
	int list[3];

	scanf("%d", &N);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			scanf("%d", &list[c]);
		}

		solve(list);
	}

	for (int i = 0; i < 3; i++)
	{
		min_ans = Min(min_ans, minDP[i]);
		max_ans = Max(max_ans, maxDP[i]);
	}

	printf("%d %d\n", max_ans, min_ans);
}

int main(void)
{
	input();
}