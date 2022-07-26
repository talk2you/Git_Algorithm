#include <stdio.h>

int L, C;
char list[20];

char vowel[10] = { 'a', 'e', 'i', 'o', 'u' };

char stack[20];
int stack_size;

void push(char c)
{
	stack[stack_size++] = c;
}

void pop()
{
	stack_size--;
}

void merge(int start, int end)
{
	char temp[20];
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (list[i] < list[j])
			temp[k++] = list[i++];
		else 
			temp[k++] = list[j++];
	}

	while(i<=mid)	temp[k++] = list[i++];
	while(j<=end)	temp[k++] = list[j++];

	for (int i = start; i <= end; i++)
		list[i] = temp[i - start];
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

void input()
{
	scanf("%d %d", &L, &C);

	for (int i = 0; i < C; i++)
		scanf(" %c", &list[i]);

	sort(0, C - 1);
}

void search(int start, int cnt)
{
	if (cnt >= L)
	{
		int vowel_cnt = 0;
		int consonant_cnt = 0;

		for (register int i = 0; i < stack_size; ++i)
		{
			for (int j = 0; j < 5; j++)
			{
				if (stack[i] == vowel[j])

				{
					vowel_cnt++;
					break;
				}
			}
		}

		consonant_cnt = cnt - vowel_cnt;
		if (vowel_cnt >= 1 && consonant_cnt >= 2)
		{
			for (int i = 0; i < cnt; i++)
				printf("%c", stack[i]);
			printf("\n");
		}

		return;
	}

	for (int i = start; i < C; i++)
	{
		push(list[i]);
		search(i + 1, cnt + 1);
		pop();
	}
}

void solve()
{
	for (int i = 0; i < C; i++)
	{
		push(list[i]);
		search(i+1, 1);
		pop();
	}
}

int main(void)
{
	input();
	solve();
}