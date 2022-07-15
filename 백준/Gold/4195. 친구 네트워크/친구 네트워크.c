#include <stdio.h>
#include <string.h>

#define MAX_HASH 200003

int F;
typedef struct HASH{
	char name[21];
	int idx;
	struct HASH *next;
}HASH;
HASH pool[200003];
int pool_size;
HASH head[200003];

int parent[200003];
int friend_cnt[200003];

int get_hash(char name[21])
{
	register int h = 5381;

	int i = 0;
	while (name[i])
		h += ((h << 5) + h + name[i++]) % MAX_HASH;

	h %= MAX_HASH;

	return h;
}

int hash_add(char name[21])
{
	int h = get_hash(name);

	register HASH *nd = &head[h];
	while (nd->next)
	{
		nd = nd->next;

		if (strcmp(name, nd->name) == 0)
			return nd->idx;
	}

	strcpy(pool[pool_size].name, name);
	pool[pool_size].next = head[h].next;
	pool[pool_size].idx = pool_size;
	head[h].next = &pool[pool_size];

	return pool_size++;
}

void init()
{
	memset(head, 0, sizeof(head));
	memset(pool, 0, sizeof(pool));
	for (register int i = 0;i <= 200003;++i)
	{
		parent[i] = i;
		friend_cnt[i] = 1;
	}
}

void input()
{
	scanf("%d", &F);
}

int find_parent(int idx)
{
	if (parent[idx] == idx)
		return idx;	
	return parent[idx] = find_parent(parent[idx]);
}

void solve()
{
	char name1[21], name2[21];
	int idx1, idx2, pa, pb;

	for (register int i = 0;i < F;++i)
	{
		scanf("%s %s", name1, name2);
		idx1 = hash_add(name1);
		idx2 = hash_add(name2);

		pa = find_parent(idx1);
		pb = find_parent(idx2);

		if (pa != pb)
		{
			parent[pb] = pa;
			friend_cnt[pa] += friend_cnt[pb];
		}

		printf("%d\n", friend_cnt[pa]);
	}
}


int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1;t <= T;++t)
	{
		init();
		input();
		solve();
	}
}