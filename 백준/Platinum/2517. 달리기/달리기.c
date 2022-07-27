#include <stdio.h>
#include <string.h>

#define MAX 500003

int N;
typedef struct {
	int n;
	int rating;
	int index;
}NODE;
NODE list[MAX];
NODE tree[MAX];
int list_size;

int table[MAX];

void merge(int start, int end, int flag)
{
	int mid = (start + end) / 2;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (flag == 0)
		{
			if (list[i].n < list[j].n)
				memcpy(&tree[k++], &list[i++], sizeof(NODE));
			else
				memcpy(&tree[k++], &list[j++], sizeof(NODE));
		}
		else
		{
			if (list[i].index < list[j].index)
				memcpy(&tree[k++], &list[i++], sizeof(NODE));
			else
				memcpy(&tree[k++], &list[j++], sizeof(NODE));
		}
	}

	while(i<=mid)	memcpy(&tree[k++], &list[i++], sizeof(NODE));
	while(j<=end)	memcpy(&tree[k++], &list[j++], sizeof(NODE));

	for (int t = start; t <= end; t++)
		memcpy(&list[t], &tree[t-start], sizeof(NODE));
}

void sort(int start, int end, int flag)
{
	int mid = (start + end) / 2;
	if (start >= end)
		return;

	sort(start, mid, flag);
	sort(mid + 1, end, flag);
	merge(start, end, flag);
}

void input()
{
	int a;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a);
		list[i].n = a;
		list[i].index = i + 1;
	}
}

int prefixSum(int n)
{
	int ret = 0;

	while (n > 0)
	{
		ret += table[n];
		n -= (n & -n);
	}
	
	return ret;
}

void update(int n)
{
	while (n <= N)
	{
		table[n] += 1;
		n += (n & -n);
	}
}

void solve()
{
	int temp;

	sort(0, N - 1, 0);

	for (int i = 0; i < N; i++)
		list[i].rating = i + 1;

	memset(tree, 0, sizeof(tree));
	sort(0, N - 1, 1);

	for (int i = 0; i < N; i++)
	{
		temp = list[i].rating;

		printf("%d\n", (i + 1) - prefixSum(temp - 1));
		
		update(temp);
	}
}

int main(void)
{
	input();
	solve();
}