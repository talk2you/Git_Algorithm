#include <stdio.h>
#include <string.h>

int N;
char str[10][10];

typedef struct {
	char s;
	int n;
}NUM;
NUM num[26];

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", &str[i]);
		int len = strlen(str[i]);
		int prod = 1;

		for (int j = len - 1; j >= 0; j--)
		{
			num[str[i][j] - 'A'].n += prod;
			num[str[i][j] - 'A'].s = str[i][j];
			prod *= 10;
		}
	}
}

void merge(int start, int end)
{
	NUM temp[26];

	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (num[i].n > num[j].n)
			memcpy(&temp[k++], &num[i++], sizeof(NUM));
		else
			memcpy(&temp[k++], &num[j++], sizeof(NUM));
	}

	while(i<=mid)	memcpy(&temp[k++], &num[i++], sizeof(NUM));
	while(j<=end)	memcpy(&temp[k++], &num[j++], sizeof(NUM));

	for(int i=start;i<=end;i++)
		memcpy(&num[i], &temp[i-start], sizeof(NUM));
}

void sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int myAtoi(char s[10])
{
	int len = strlen(s);
	int result = 0;
	int prod = 1;

	for (int i = len - 1; i >= 0; i--)
	{
		result += (s[i]-'0') * prod;
		prod *= 10;
	}

	return result;
}

void solve()
{
	int ans = 0;

	sort(0, 25);

	for (int i = 0; i < N; i++)
	{
		int len = strlen(str[i]);

		for (int j = 0; j < 10; j++)
		{
			if (num[j].n == 0)
				break;

			for (int k = 0; k < len; k++)
			{
				if (str[i][k] == num[j].s)
					str[i][k] = '9' - j;
			}
		}
	}

	for (int i = 0; i < N; i++)
		ans += myAtoi(str[i]);

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}