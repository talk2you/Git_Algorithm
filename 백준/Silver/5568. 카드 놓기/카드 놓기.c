#include <stdio.h>
#include <string.h>

#define MAX	1000000

int N, K;
int ans;

char card[11][25];
int visit[11];

typedef struct HASH {
	char n[21];
	struct HASH *next;
}HASH;
HASH pool[MAX];
HASH *head[MAX];
int pool_size;

void input()
{
	scanf("%d", &N);
	scanf("%d", &K);

	for (int i = 0; i < N; i++)
		scanf(" %s", &card[i]);
}

int make_hash(char s[25])
{
	int i = 0;
	int h = 5381;

	while (s[i])
		h += ((h << 5) + h + s[i++]) % MAX;
	h %= MAX;
	return h;
}

int add_hash(char s[25])
{
	int h = make_hash(s);

	HASH *nd = head[h];
	while (nd)
	{
		if (strcmp(nd->n, s) == 0)
			return 0;

		nd = nd->next;
	}

	strcpy(pool[pool_size].n, s);
	pool[pool_size].next = head[h];
	head[h] = &pool[pool_size++];
	return 1;
}

void search(int _cnt, char _num[21])
{
	char temp[21];

	if (_cnt >= K)
	{
		if (add_hash(_num))
			ans++;
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (visit[i])
			continue;

		strcpy(temp, _num);
		strcat(temp, card[i]);

		visit[i] = 1;
		search(_cnt + 1, temp);
		visit[i] = 0;
	}
}

void solve()
{
	char num[21] = { 0, };

	search(0, num);

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}