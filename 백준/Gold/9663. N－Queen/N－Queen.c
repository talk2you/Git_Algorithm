#include <stdio.h>
#include <string.h>

#define Abs(a) ((a<0)?-(a):(a))

#define MAX 40000

int N;
int ans;
int list[20];

void init()
{
	memset(list, -1, sizeof(list));
}

void input()
{
	scanf("%d", &N);
}

void backtracking(int _cnt, int _idx)
{
	register int cont_flag = 0;

	if (_cnt >= N)
	{
		ans++;
		return;
	}

	for (register int i = 0;i < N;i++)
	{
		cont_flag = 0;
		for (int j = 0;j < _idx;j++)
		{
			if (i == list[j])
			{
				cont_flag = 1;
				break;
			}
			else if (Abs(_idx - j) == Abs(list[j] - i))
			{
				cont_flag = 1;
				break;
			}
		}

		if (cont_flag)
			continue;

		list[_idx] = i;
		backtracking(_cnt + 1, _idx + 1);
	}
}

void solve()
{
	int idx = 0;
	int cnt = 0;

	for (int i = 0;i < N;i++)
	{
		list[idx] = i;
		backtracking(cnt + 1, idx + 1);
	}
	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}