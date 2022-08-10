#include <stdio.h>

int M, K;
int list[50];
int total;

void input()
{
	scanf("%d", &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d", &list[i]);
		total += list[i];
	}
	scanf("%d", &K);
}

void solve()
{
	double prod = 1;
	double ans = 0;

	for (int i = 0; i < M; i++)
	{
		prod = 1;

		if (list[i] < K)
			continue;

		for (int j = 0; j < K; j++)
			prod *= ((double)list[i] - j) / (total - j);
		ans += prod;
	}

	printf("%.15lf\n", ans);
}

int main(void)
{
	input();
	solve();
}