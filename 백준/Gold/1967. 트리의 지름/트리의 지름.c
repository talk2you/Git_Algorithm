#include <stdio.h>

#define Max(a, b) ((a>b)?(a):(b))

typedef struct NODE{
	int idx, w;
	struct NODE *next;
}NODE;
NODE pool[10003];
NODE head[10003];
int pool_size;

int N;
int ans;

void add_node(int a, int b, int w)
{
	pool[pool_size].idx = b;
	pool[pool_size].w = w;
	pool[pool_size].next = head[a].next;
	head[a].next = &pool[pool_size++];
	head[a].idx = a;
}

void input()
{
	int a, b, c;
	scanf("%d", &N);

	for (int i = 0;i < N-1;i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		add_node(a, b, c);
	}
}

int search(int idx)
{
	NODE *nd = &head[idx];
	int len = 0, first_max = 0, second_max = 0;

	while (nd->next)
	{
		nd = nd->next;

		len = nd->w + search(nd->idx);
		if (len > first_max)
		{
			second_max = first_max;
			first_max = len;
		}
		else if (len > second_max)
			second_max = len;
	}

	ans = Max(ans, first_max + second_max);

	return first_max;
}

void solve()
{
	search(1);

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}