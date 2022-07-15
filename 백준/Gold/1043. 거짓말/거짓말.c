#include <stdio.h>
#include <string.h>

int N, M;
int ans;

int parent[53];
int fix;

typedef struct {
	int n, lie_flag;
	int list[53];
}PARTY;
PARTY party[53];
int visit[53];

int stack[53];
int stack_size;

void push(int n)
{
	stack[stack_size++] = n;
}

int pop(int *n)
{
	if (stack_size == 0)
		return 0;

	*n = stack[--stack_size];
	return 1;
}

void init()
{
	for (int i = 0;i < 53;++i)
		party[i].lie_flag = 1;
}

void input()
{
	int know_true, a;
	int flag = 0;

	scanf("%d %d", &N, &M);
	scanf("%d", &know_true);

	// 진실을 알고있는 사람 집합 만들기
	for (int i = 0;i < know_true;++i)
	{
		scanf("%d", &a);

		if (flag == 0)
		{
			fix = a;
			flag = 1;
		}

		parent[a] = fix;
	}
}

int find_parent(int a)
{
	if (parent[a] == a)
		return a;

	return parent[a] = find_parent(parent[a]);
}

void search(int _visit[53])
{
	int pa = find_parent(fix);
	int pb, n;

	int temp_visit[53];

	for (int i = 0;i < M;++i)
	{
		memcpy(temp_visit, _visit, sizeof(visit));

		if (party[i].lie_flag == 0)
			continue;

		if (temp_visit[i])
			continue;

		temp_visit[i] = 1;

		int flag = 0;

		int limit = party[i].n;
		for (int j = 0;j < limit;++j)
		{
			pb = find_parent(party[i].list[j]);

			if (pa == pb)
				flag = 1;
			else
				push(party[i].list[j]);
		}

		if (flag)
		{
			party[i].lie_flag = 0;
			while (pop(&n))
				parent[n] = fix;

			search(temp_visit);
		}
		else
			while (pop(&n));
	}
}

void solve()
{
	int num;
	int n, lie_flag = 1;

	// 예외 1, 진실을 아는 사람이 없을때 M값 출력
	if (fix == 0)
	{
		for (int i = 0;i < M;++i)
		{
			scanf("%d", &num);
			for (int j = 0;j < num;++j)
				scanf("%d", &n);
		}
		printf("%d\n", M);
		return;
	}

	for (register int i = 0;i < M;i++)
	{
		scanf("%d", &num);
		for (int j = 0;j < num;++j)
		{
			scanf("%d", &n);

			int *idx = &party[i].n;
			party[i].list[(*idx)++] = n;

		}
	}

	search(visit);

	for (int i = 0;i < M;i++)
	{
		if (party[i].lie_flag)
			++ans;
	}

	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}