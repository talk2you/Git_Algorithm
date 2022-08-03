#include <stdio.h>

#define MAX_POOL 1000003

int N;
int ans_gcd, ans_k;

int list[1000003];
int temp[1000003];

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE pool[MAX_POOL];
NODE *head[MAX_POOL];
int pool_size;

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
}

void merge(int start, int end)
{
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
	if (start >= end)
		return;

	int mid = (start + end) >> 1;
	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int get_gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return get_gcd(b, a%b);
}

int make_hashmap(int n)
{
	int h = 5381;

	while (n)
	{
		h += ((h << 5) + h + (n & 0xff)) % MAX_POOL;
		n >>= 8;
	}
	return h %= MAX_POOL;
}

void add_num(int n)
{
	int h = make_hashmap(n);

	NODE *nd = head[h];

	while (nd)
	{
		if (nd->n == n)
			return;
		nd = nd->next;
	}

	pool[pool_size].n = n;
	pool[pool_size].next = head[h];
	head[h] = &pool[pool_size++];
}

int exist_num(int n)
{
	int h = make_hashmap(n);

	NODE *nd = head[h];

	while (nd)
	{
		if (nd->n == n)
			return 1;
		nd = nd->next;
	}
	return 0;
}

void solve()
{
	long long cnt = 0;

	sort(0, N - 1);

	for (int i = 0; i < N; i++)
	{
		int gcd = 0;

		for (int j = 0; j < N; j++)
		{
			if (i == j)
				continue;

			if (gcd == 0)
			{
				gcd = list[j];
				continue;
			}
			
			gcd = get_gcd(gcd, list[j]);
			cnt++;

			if (gcd == 1)
				break;

			if (list[i] % gcd == 0)
			{
				gcd = 1;
				break;
			}
		}

		if (gcd >= 2)
		{
			if (list[i] % gcd != 0)
			{
				ans_gcd = gcd;
				ans_k = list[i];
				printf("%d %d\n", ans_gcd, ans_k);
				return;
			}
		}
	}

	printf("-1\n");
}

int main(void)
{
	input();
	solve();
}