#include <stdio.h>

#define MAX_VAL	(int)1E9

int X, Y;

void input()
{
	scanf("%d %d", &X, &Y);
}

int lower_bound(long long n)
{
	int start = 0;
	int end = MAX_VAL;
	int mid;
	long long ratio;

	while (start <= end)
	{
		mid = (start + end) >> 1;
		ratio = (long long)(Y + mid) * 100 / (X + mid);

		if (ratio < n)
			start = mid + 1;
		else if (ratio >= n)
			end = mid - 1;
	}

	return start;
}

void solve()
{
	long long ratio = (long long)Y * 100 / X;

	if (ratio >= 99)
	{
		printf("-1\n");
		return;
	}

	printf("%d\n", lower_bound(ratio + 1));
}

int main(void)
{
	input();
	solve();
}