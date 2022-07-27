#include <stdio.h>

#define MAX 502000
#define Abs(a) ((a<0)?-(a):(a))

int T;
long long ans;

int N, M;
int a_list[1003];
int b_list[1003];

typedef struct HASHMAP{
	int n;
	int cnt;
	struct HASHMAP *next;
}HASHMAP;
HASHMAP pool[500000];
HASHMAP head[500000];
int pool_size;

void input()
{
	scanf("%d", &T);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &a_list[i]);

	scanf("%d", &M);
	for (int i = 0; i < M; i++)
		scanf("%d", &b_list[i]);
}

int make_hash(int n)
{
	int h = 5381;

	while (n)
	{
		h += ((h << 5) + h + (n & 0xFF)) % MAX;
		n >>= 8;
	}
	h %= MAX;

	return h;
}

void add_subTotal(int n)
{
	int temp = Abs(n);
	int h = make_hash(temp);

	HASHMAP *nd = &head[h];
	while (nd->next)
	{
		nd = nd->next;

		if (nd->n == n)
		{
			nd->cnt++;
			return;
		}
	}

	pool[pool_size].n = n;
	pool[pool_size].cnt = 1;
	pool[pool_size].next = head[h].next;
	head[h].next = &pool[pool_size++];
}

int get_subTotal_Cnt(int target)
{
	int temp = Abs(target);
	int h = make_hash(temp);

	HASHMAP *nd = &head[h];
	while (nd->next)
	{
		nd = nd->next;

		if (nd->n == target)
			return nd->cnt;
	}

	return 0;
}

void solve()
{
	for (int i = 0; i < M; i++)
	{
		int sum = 0;
		for (int j = i; j < M; j++)
		{
			sum += b_list[j];
			add_subTotal(sum);
		}
	}

	for (int i = 0; i < N; i++)
	{
		int sum = 0;
		for (int j = i; j < N; j++)
		{
			sum += a_list[j];
			int target = T - sum;

			ans += (long long)get_subTotal_Cnt(target);
		}
	}

	printf("%lld\n", ans);
}

int main(void)
{
	input();
	solve();
}