#include <stdio.h>

int N, H;

int low_list[5000003];
int high_list[5000003];
int low_cnt, high_cnt;
int ans_min = 1 << 30;
int ans_num;

void input()
{
	scanf("%d %d", &N, &H);
}

void solve()
{
	int a;

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a);

		if (i % 2 == 0)
		{
			low_list[a]++;
			low_cnt++;
		}
		else
		{
			high_list[H + 1 - a]++;
			high_cnt++;
		}
	}

	low_list[0] = -low_cnt;
	high_list[H + 1] = -high_cnt;

	for (int i = 1; i <= H; i++)
		high_list[i] += high_list[i - 1];
	
	for (int i = H; i >= 0; i--)
		low_list[i] += low_list[i + 1];

	for (int i = 1; i <= H; i++)
	{
		int sum = high_list[i] + low_list[i];
		if (ans_min > sum)
		{
			ans_min = sum;
			ans_num = 1;
		}
		else if (ans_min == sum)
			ans_num++;
	}

	printf("%d %d\n", ans_min, ans_num);

	/*for (int i = 1; i <= H; i++)
		printf("%d ", high_list[i]);
	printf("\n");


	for (int i = 1; i <= H; i++)
		printf("%d ", low_list[i]);
	printf("\n");*/
}

int main(void)
{
	input();
	solve();
}