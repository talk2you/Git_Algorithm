#include <stdio.h>

int N, K;
int list[100003];
int B[100003];
int ans;

void input()
{
	scanf("%d %d", &N, &K);

	for (int i = 1;i <= N;i++)
		scanf("%d", &list[i]);
}

void solve()
{
	for(int i = 1;i <= N;++i)
		B[i] = list[i - 1] ^ list[i];
	
	for (int i = 1;i <= N - K + 2;++i)
		if (B[i])
		{
			B[i] ^= 1, B[i + K] ^= 1;
			ans++;
		}

	for (int i = N - K + 2;i <= N;i++)
		if (B[i])
		{
			printf("Insomnia\n");
			return;
		}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}