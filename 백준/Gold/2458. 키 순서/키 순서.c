#include <stdio.h>
#include <string.h>

#define MAX 125001
#define Max(a, b)	((a>b)?(a):(b))

int N, M;
int ans;

typedef struct NODE{
	int n;
	struct NODE *next;
}NODE;
NODE upper[MAX];
NODE *upper_head[501];
NODE under[MAX];
NODE *under_head[501];
int upper_size, under_size;

char visit[501];
int cnt[501];

void add_upper(int a, int b)
{
	upper[upper_size].n = a;
	upper[upper_size].next = upper_head[b];
	upper_head[b] = &upper[upper_size++];
}

void add_under(int a, int b)
{
	under[under_size].n = b;
	under[under_size].next = under_head[a];
	under_head[a] = &under[under_size++];
}

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		add_upper(a, b);
		add_under(a, b);
	}
}

int search_upper(int n)
{
	NODE *nd = upper_head[n];

	int ret_cnt = 0;
	while (nd)
	{
		if (visit[nd->n])
		{
			nd = nd->next;
			continue;
		}

		visit[nd->n] = 1;

		ret_cnt += search_upper(nd->n);
		nd = nd->next;
	}

	return ret_cnt + 1;
}

int search_under(int n)
{
	NODE *nd = under_head[n];

	int ret_cnt = 0;
	while (nd)
	{
		if (visit[nd->n])
		{
			nd = nd->next;
			continue;
		}

		visit[nd->n] = 1;

		ret_cnt += search_under(nd->n);
		nd = nd->next;
	}

	return ret_cnt + 1;
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		memset(visit, 0, sizeof(visit));
		cnt[i] += search_upper(i) - 1;

		memset(visit, 0, sizeof(visit));
		cnt[i] += search_under(i) - 1;

		if (cnt[i] == N - 1)
			ans ++;
	}
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}