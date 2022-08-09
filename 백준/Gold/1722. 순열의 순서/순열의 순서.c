#include <stdio.h>
#include <string.h>

int N, cmd;
long long k;
int list[21];
int visit[21];

void input()
{
	scanf("%d %d", &N, &cmd);

	if (cmd == 1)
		scanf("%lld", &k);
	else
		for (int i = 1; i <= N; i++)
			scanf("%d", &list[i]);
}

long long fact(long long n)
{
	if (n == 2)
		return n;

	return n * fact(n - 1);
}

void solve()
{
	if (cmd == 1)
	{
		if (N == 1)
		{
			printf("1\n");
			return;
		}

		long long limit = fact(N);
		int temp_n = N;
		long long temp_k = k;
		long long unit;

		int cnt = 0;

		while (1)
		{
			cnt++;
			if (cnt > N)
			{
				printf("\n");
				break;
			}

			unit = limit / temp_n;

			for (int i = 1; i*unit <= limit; i++)
			{
				if (temp_k <= i * unit)
				{
					int j = 1;
					int v_cnt = 0;
					while (i != v_cnt)
					{
						v_cnt++;
						while (visit[j])
							j++;
							
						if (v_cnt == i)
							break;

						j++;
					}

					visit[j] = 1;
					printf("%d ", j);

					limit /= temp_n;
					temp_n--;
					temp_k -= (i - 1)*unit;
					break;
				}
			}

			//printf("%lld %lld %d %lld\n", limit, unit, start, temp_k);
		}
	}
	else
	{
		if (N == 1)
		{
			printf("1\n");
			return;
		}

		long long limit = fact(N);
		long long start = 1;
		long long end = limit;
		long long unit;
		int temp_n = N;
			
		int a = 1;
		while (1)
		{
			unit = limit / temp_n;

			int v_cnt = 0;
			int j = 1;
			while (1)
			{
				if (visit[j] == 0)
					v_cnt++;

				if (j == list[a])
					break;

				j++;
			}

			visit[j] = 1;

			start = start + (v_cnt-1) * unit;
			end = start + unit - 1;

			if (start == end)
			{
				printf("%lld\n", start);
				return;
			}

			limit = unit;
			temp_n--;
			a++;
		}
	}
	
}

int main(void)
{
	input();
	solve();
}