#include <stdio.h>
#include <string.h>

#define MAX 100000

int N, M;
int list[10];
int temp_list[10];
int visit[10];
int roll_cnt;

typedef struct NODE{
	int list[10];
	struct NODE *next;
}NODE;
NODE pool[MAX];
NODE *head[MAX];
int pool_size;

int make_hash(int _list[10])
{
	int h = 381;

	int i = 0;
	while (i < N)
	{
		h += ((h << 5) + h + _list[i]) % MAX;
		i++;
	}
	h %= MAX;
	return h;
}

int add_hash(int _list[10])
{
	int h = make_hash(_list);

	NODE *nd = head[h];
	while (nd)
	{
		int match_cnt = 0;
		for (int i = 0; i < N; i++)
		{
			if (nd->list[i] == _list[i])
				match_cnt++;
		}

		if (match_cnt == N)
			return 0;

		nd = nd->next;
	}

	for (int i = 0; i < N; i++)
		pool[pool_size].list[i] = _list[i];
	pool[pool_size].next = head[h];
	head[h] = &pool[pool_size++];
	return 1;
}

void merge(int start, int end)
{
	int temp[10];
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

void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);

	sort(0, N - 1);
}

void search(int cnt, int start)
{
	if (cnt >= M)
	{
		if (add_hash(temp_list))
		{
			roll_cnt++;
			for (int i = 0; i < M; i++)
				printf("%d ", temp_list[i]);
			printf("\n");
		}
		return;
	}

	for (int i = start; i < N; i++)
	{
		if (visit[i])
			continue;

		visit[i] = 1;

		if(list[i] == 0)
			printf("0 == %d [%d] %d\n", cnt, i, list[i]);

		temp_list[cnt] = list[i];
		search(cnt + 1, i);
		visit[i] = 0;
	}
}

void solve()
{
	search(0, 0);
}

int main(void)
{
	input();
	solve();
}