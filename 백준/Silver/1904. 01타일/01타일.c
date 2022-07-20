#include <stdio.h>

#define Swap(a, b) {int t=a;a=b;b=t;}
#define MOD 15746
int N;

void input()
{
	scanf("%d", &N);
}

void solve()
{
	int temp[4] = { 0, };

	temp[0] = 1;
	temp[1] = 2;

	if (N == 1)
	{
		printf("1\n");
		return;
	}
	else if (N == 2)
	{
		printf("2\n");
		return;
	}

	for (int i = 2; i <= N; ++i)
	{
		temp[2] = (temp[0] + temp[1]) % MOD;
		Swap(temp[0], temp[1]);
		Swap(temp[1], temp[2]);
	}

	printf("%d\n", temp[0] % MOD);
}

int main(void)
{
	input();
	solve();
}