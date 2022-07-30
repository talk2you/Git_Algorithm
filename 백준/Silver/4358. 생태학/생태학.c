#include <stdio.h>
#include <string.h>

#define MAX 1000001

typedef struct HASH{
	char name[31];
	int cnt;
	struct HASH *next;
}HASH;
HASH pool[1000001];
HASH head[1000001];
int pool_size;

char tree[10000][31];
int total_size;
int tree_size;

int make_hash(char name[31])
{
	int h = 5381;

	int i = 0;
	while (name[i])
		h += ((h << 5) + h + name[i++]) % MAX;
	h %= MAX;
	return h;
}

int add_hash(char name[31])
{
	int h = make_hash(name);

	HASH *nd = &head[h];

	if (nd->next)
	{
		nd = nd->next;

		if (strcmp(nd->name, name) == 0)
		{
			nd->cnt += 1;
			return 0;
		}
	}

	strcpy(pool[pool_size].name, name);
	pool[pool_size].cnt += 1;
	pool[pool_size].next = head[h].next;
	head[h].next = &pool[pool_size++];
	return 1;
}

int get_cnt(char name[31])
{
	int h = make_hash(name);

	HASH *nd = &head[h];

	if (nd->next)
	{
		nd = nd->next;

		if (strcmp(nd->name, name) == 0)
			return nd->cnt;
	}

	return 0;
}

void input()
{
	char name[31];
	
	while (scanf(" %[^\n]s\n", name) != EOF)
	{
		total_size++;
		if (add_hash(name))
			strcpy(tree[tree_size++], name);
	}
}

void merge(int start, int end)
{
	char temp[10000][31];

	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (strcmp(tree[i], tree[j]) < 0)
			strcpy(temp[k++], tree[i++]);
		else
			strcpy(temp[k++], tree[j++]);
	}

	while(i<=mid)	strcpy(temp[k++], tree[i++]);
	while(j<=end)	strcpy(temp[k++], tree[j++]);

	for (int i = start; i <= end; i++)
		strcpy(tree[i], temp[i - start]);
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

void solve()
{
	sort(0, tree_size - 1);

	for (int i = 0; i < tree_size; i++)
	{
		float ratio = (float)get_cnt(tree[i]) / (total_size) * 100;
		printf("%s %.4f\n", tree[i], ratio);
	}
}

int main(void)
{
	input();
	solve();
}