#include <stdio.h>

long long f[100];
int N;

int main(void)
{
	scanf("%d", &N);
	
	f[0] = 0;
	f[1] = 1;
	
	for (int i = 2; i <= N; i++)
		f[i] = f[i - 1] + f[i - 2];

	printf("%lld\n", f[N]);
}