#include <stdio.h>
#include <string.h>

int N;

typedef struct NODE{
	int end;
	struct NODE *next[10];
}NODE;
NODE node[100000];
NODE head;

int node_size;
int exist_flag;

void init()
{
	memset(node, 0, sizeof(node));
	memset(&head, 0, sizeof(head));
	node_size = 0;
	exist_flag = 0;
}

void add(char n[20])
{
	int i = 0;

	NODE *nd = &head;

	while (n[i])
	{
		int ch = n[i] - '0';

		if (nd->end == 1)
		{
			exist_flag = 1;
		}

		if (!nd->next[ch])
		{
			nd->next[ch] = &node[node_size];
			node_size++;
		}

		nd = nd->next[ch];
		i++;
	}

	nd->end = 1;
	for (int i = 0; i < 10; i++)
	{
		if (nd->next[i])
		{
			exist_flag = 1;
		}
	}
}

void input()
{
	char num[20];

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf(" %s", num);
		add(num);
	}
}

void solve()
{
	if (exist_flag)
		printf("NO\n");
	else
		printf("YES\n");
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		solve();
	}
}