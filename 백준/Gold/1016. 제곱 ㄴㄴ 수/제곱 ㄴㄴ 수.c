#include <stdio.h>

long long min, max;
char nn[1000001];

void input()
{
	scanf("%lld %lld", &min, &max);
}

void solve()
{
	register long long cnt = max - min + 1;
	register long long div;

	for (register long long t = 2; t*t <= max; t++)
	{
		div = min / (t * t);
		if (min % (t*t) != 0)
			div += 1;
		
		while (div * t*t <= max)
		{
			if (nn[div*t*t - min] == 0)
			{
				nn[div*t*t - min] = 1;
				cnt--;
			}
			div++;
		}
	}

	printf("%lld\n", cnt);
}

int main(void)
{
	input();
	solve();
}