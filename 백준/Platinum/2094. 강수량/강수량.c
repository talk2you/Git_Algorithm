#include <stdio.h>
#include <string.h>

#define INF_MIN	-2000000000
#define INF_MAX	2000000000
#define MAX_POOL 100003
int N, M;

typedef struct {
	int year;
	int rain;
}INFO;
INFO info[50003];
INFO tree[200003];

typedef struct NODE{
	int year, rain;
	struct NODE *next;
}NODE;
NODE pool[MAX_POOL];
NODE *head[MAX_POOL];
int pool_size;

int make_map(int n)
{
	int h = 5381;

	if (n < 0)
		n = -n;

	while (n)
	{
		h += ((h << 5) + h + n & 0xFF ) % MAX_POOL;
		n >>= 8;
	}
	h %= MAX_POOL;
	return h;
}

void add_map(int year, int rain)
{
	int h = make_map(year);

	NODE *nd = head[h];
	while (nd)
	{
		if (nd->year == year)
			return;
		nd = nd->next;
	}

	pool[pool_size].year = year;
	pool[pool_size].rain = rain;
	pool[pool_size].next = head[h];
	head[h] = &pool[pool_size++];
}

int search_map(int year)
{
	int h = make_map(year);

	NODE *nd = head[h];
	while (nd)
	{
		if (nd->year == year)
			return nd->rain;
		nd = nd->next;
	}
	return 0;
}

void input()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf(" %d %d", &info[i].year, &info[i].rain);
		//printf("%d %d %d\n", i, info[i].year, info[i].rain);
		add_map(info[i].year, info[i].rain);
	}
}

void make_tree(int start, int end, int idx, INFO *ret)
{
	if (start == end)
	{
		memcpy(&tree[idx], &info[start], sizeof(INFO));
		memcpy(ret, &info[start], sizeof(INFO));
		return;
	}

	int mid = (start + end) >> 1;

	INFO ret1, ret2;
	make_tree(start, mid, idx * 2, &ret1);
	make_tree(mid + 1, end, idx * 2 + 1, &ret2);

	if (ret1.rain > ret2.rain)
		memcpy(ret, &ret1, sizeof(INFO));
	else
		memcpy(ret, &ret2, sizeof(INFO));

	memcpy(&tree[idx], ret, sizeof(INFO));
	return;
}

int search_max(int start, int end, int idx, int left_year, int right_year, INFO *ret)
{
	//printf("%d %d %d %d\n", info[start].year, info[end].year, left_year, right_year);
	if (right_year < info[start].year || info[end].year < left_year)
	{
		ret->rain = INF_MIN;
		ret->year = INF_MIN;
		return 0;
	}

	if (left_year <= info[start].year && info[end].year <= right_year)
	{
		memcpy(ret, &tree[idx], sizeof(INFO));
		return end-start + 1;  
	}

	int mid = (start + end) >> 1;
	INFO ret1, ret2;
	int diff1, diff2;
	diff1 = search_max(start, mid, idx*2, left_year, right_year, &ret1);
	diff2 = search_max(mid+1, end, idx*2+1, left_year, right_year, &ret2);

	if (ret1.rain >= ret2.rain)
		memcpy(ret, &ret1, sizeof(INFO));
	else
		memcpy(ret, &ret2, sizeof(INFO));
	return diff1 + diff2;
}

void solve()
{
	INFO ret;
	int a, b;

	make_tree(1, N, 1, &ret);

	scanf("%d", &M);

	for (int i = 0; i < M; i++) 
	{
		scanf("%d %d", &a, &b);

		int exist_a = search_map(a);
		int exist_b = search_map(b);
		int diff = search_max(1, N, 1, a + 1, b - 1, &ret);

		if (exist_a && exist_b)
		{
			if (exist_a >= exist_b)
			{
				if (ret.rain < exist_b)
				{
					if (b - a + 1 == diff + 2)
						printf("true\n");
					else
						printf("maybe\n");
				}
				else
					printf("false\n");
			}
			else
				printf("false\n");
		}
		else if (exist_a)
		{
			exist_b = exist_a;

			if (ret.rain < exist_b)
				printf("maybe\n");
			else
				printf("false\n");
		}
		else if (exist_b)
		{
			exist_a = INF_MAX;
			if (ret.rain < exist_b)
				printf("maybe\n");
			else
				printf("false\n");
		}
		else
		{
			printf("maybe\n");
		}
	}
}

int main(void)
{
	input();
	solve();
}