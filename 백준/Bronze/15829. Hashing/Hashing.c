#include <stdio.h>

#define MOD 1234567891

int n;
char str[53];

void input()
{
	scanf("%d", &n);
	scanf("%s", str);
}

void solve()
{
	int i = 0;
	long long h = 0;
	long long prod;

	while (str[i])
	{
		prod = 1;
		for (int j = 0; j < i; j++)
		{
			prod *= 31;
			prod %= MOD;
		}
		h += (((str[i]-'a'+1) * prod) % MOD);
		i++;
	}
	h %= MOD;
	printf("%lld\n", h);
}

int main(void)
{
	input();
	solve();
}