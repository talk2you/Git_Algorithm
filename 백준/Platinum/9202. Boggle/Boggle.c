#include <stdio.h>
#include <string.h>

#define MAX_SIZE 600000
#define Max(a, b) ((a>b)?(a):(b))

int N;
char map[4][5];
char visit[4][4];

typedef struct TRIE{
	char find;
	char end;
	struct TRIE *str[26];
}TRIE;
TRIE pool[MAX_SIZE];
TRIE head;
int pool_size;

char stack[10];
int stack_size;

typedef struct {
	int r[8], c[8];
}DIR;
DIR dir = { {-1,-1,-1,0,0,1,1,1},{-1,0,1,-1,1,-1,0,1} };

int total_score;
int find_cnt;
char max_length_word[9];
int max_length;

void init()
{
	for (int i = 0; i < MAX_SIZE; i++)
		pool[i].find = 0;

	memset(max_length_word, 0, sizeof(char) * 9);
	memset(visit, 0, sizeof(visit));

	stack_size = 0;
	total_score = 0;
	find_cnt = 0;
	max_length = 0;
}

void push(char c)
{
	stack[stack_size++] = c;
}

void pop()
{
	--stack_size;
	stack[stack_size] = 0;
}

void add(char str[9])
{
	int i = 0;

	TRIE *nd = &head;

	while (str[i])
	{
		int ch = str[i] - 'A';

		if (!nd->str[ch])
			nd->str[ch] = &pool[pool_size++];

		nd = nd->str[ch];
		i++;
	}

	nd->end = 1;
}

void input()
{
	char str[9];

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", str);
		add(str);
	}
}

void search(int _r, int _c, int _cnt, TRIE *nd)
{
	int ch = map[_r][_c] - 'A';

	if (nd == 0)
		return;

	if (nd->end)
	{
		if (nd->find == 0)
		{
			nd->find = 1;

			find_cnt++;
			if (_cnt > max_length)
			{
				strcpy(max_length_word, stack);
				max_length = _cnt;
			}
			else if (_cnt == max_length)
			{
				if(strcmp(max_length_word, stack) > 0)
					strcpy(max_length_word, stack);
			}

			int add = 0;
			if (_cnt <= 2);
			else if (_cnt <= 4) add = 1;
			else if (_cnt <= 5) add = 2;
			else if (_cnt <= 6) add = 3;
			else if (_cnt <= 7) add = 5;
			else if (_cnt <= 8) add = 11;

			total_score += add;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		int temp_r = _r + dir.r[i];
		int temp_c = _c + dir.c[i];

		if (temp_r < 0 || temp_r >= 4 || temp_c < 0 || temp_c >= 4)
			continue;
		if (visit[temp_r][temp_c])
			continue;

		int next_ch = map[temp_r][temp_c] - 'A';
		
		visit[temp_r][temp_c] = 1;
		push(map[temp_r][temp_c]);

		search(temp_r, temp_c, _cnt+1, nd->str[next_ch]);
		pop();
		visit[temp_r][temp_c] = 0;
	}
}

void solve()
{
	int n;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		init();

		for (int r = 0; r < 4; r++)
			scanf(" %s", &map[r]);

		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				visit[r][c] = 1;
				push(map[r][c]);
				search(r, c, 1, head.str[map[r][c] - 'A']);
				pop();
				visit[r][c] = 0;
			}
		}

		printf("%d %s %d\n", total_score, max_length_word, find_cnt);
	}
}

int main(void)
{
	input();
	solve();
}