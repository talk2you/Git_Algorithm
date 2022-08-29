#include <stdio.h>

int L;

void input()
{
	scanf("%d", &L);
}

void solve()
{
	int ans = 0;

	ans = L / 5;
	if (L % 5)
		ans++;
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}