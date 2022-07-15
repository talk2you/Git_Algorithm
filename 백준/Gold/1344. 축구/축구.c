#include <stdio.h>
#include <math.h>
int pascal[20][20];

int idx[20] = { 0,1,4,6,8,9,10,12,14,15,16,18};
int A, B;

void init()
{
	pascal[0][0] = 1;
	pascal[1][0] = 1;
	pascal[1][1] = 1;

	for (int r = 2;r <= 18;r++)
		for (int c = 0;c <= 18;c++)
			pascal[r][c] = pascal[r - 1][c - 1] + pascal[r - 1][c];
}

void input()
{
	scanf("%d %d", &A, &B);
}

void solve()
{
	double sum_a = 0;
	double sum_b = 0;

	double a = (double)A / 100;
	double b = (double)B / 100;

	for (int i = 0;i < 12;i++)
	{
		sum_a += pascal[18][idx[i]] * pow(a, idx[i]) * pow(1 - a, 18 - idx[i]);
		sum_b += pascal[18][idx[i]] * pow(b, idx[i]) * pow(1 - b, 18 - idx[i]);	
	}

	printf("%lf\n", 1-sum_a*sum_b);
}

int main(void)
{
	init();
	input();
	solve();
}