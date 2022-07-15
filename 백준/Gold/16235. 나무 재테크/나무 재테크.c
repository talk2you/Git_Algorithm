#include <stdio.h>

#define MAX_TREE 1200
#define Max(a, b) (a>b?(a):(b))

int N, M, K;
typedef struct {
	int e;
	int tree[MAX_TREE];
	int cnt;
}MAP;
MAP map[11][11];
MAP temp_map[11][11];
int add[11][11];
int A[11][11];
int live_tree;

typedef struct {
	int r[8], c[8];
}DIR;
// 좌상, 상, 우상, 우, 우하, 하, 좌하, 좌
DIR dir = { {-1,-1,-1,0,1,1,1,0},{-1,0,1,1,1,0,-1,-1} };

// 맵마다 우선순위 큐로 나무 push
int tree_push(MAP *_map, int data)
{
	int temp;

	if (_map->cnt >= MAX_TREE)
		return -1;

	_map->tree[++(_map->cnt)] = data;

	for (int i = _map->cnt; i > 1; i /= 2)
	{
		if (_map->tree[i] >= _map->tree[i / 2])
			break;

		temp = _map->tree[i];
		_map->tree[i] = _map->tree[i / 2];
		_map->tree[i / 2] = temp;
	}

	return 1;
}
// 맵마다 우선순위 큐로 나무 pop
int tree_pop(MAP *_map, int *data)
{
	int temp;

	if (_map->cnt == 0)
		return -1;

	*data = _map->tree[1];
	_map->tree[1] = _map->tree[_map->cnt];
	_map->tree[(_map->cnt)--] = 9999;

	for (int i = 1; i * 2 <= _map->cnt;)
	{
		if (_map->tree[i] <= _map->tree[i * 2] && _map->tree[i] <= _map->tree[i * 2 + 1])
			break;
		else if (_map->tree[i * 2] < _map->tree[i * 2 + 1])
		{
			temp = _map->tree[i];
			_map->tree[i] = _map->tree[i * 2];
			_map->tree[i * 2] = temp;
			i = i * 2;
		}
		else
		{
			temp = _map->tree[i];
			_map->tree[i] = _map->tree[i * 2 + 1];
			_map->tree[i * 2 + 1] = temp;
			i = i * 2 + 1;
		}
	}

	return 1;
}

// 초기 땅에는 양분 5가 있음
void init()
{
	for (int r = 1; r <= 10; r++)
		for (int c = 1; c <= 10; c++)
			map[r][c].e = 5;
}

// 입력
void input()
{
	int temp_r, temp_c, temp_age;

	scanf("%d %d %d", &N, &M, &K);

	// 겨울마다 뿌릴 양분 입력
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &A[r][c]);

	// 초기 나무 위치
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &temp_r, &temp_c, &temp_age);
		tree_push(&map[temp_r][temp_c], temp_age);
	}
}

// 봄
void spring()
{
	int temp_tree;
	
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			while (tree_pop(&map[r][c], &temp_tree) == 1)
			{
				// 양분이 부족해 죽음
				if (map[r][c].e < temp_tree)
				{
					add[r][c] += (temp_tree / 2);
					continue;
				}

				// 양분 먹고 나이 증가
				map[r][c].e -= temp_tree;
				tree_push(&temp_map[r][c], temp_tree+1);
			}			
		}
	}
}

// 여름
void summer()
{
	// 죽은 나무는 양분이 됨
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
		{
			map[r][c].e += add[r][c];
			add[r][c] = 0;
		}
}

// 가을
void autumn()
{
	int temp_tree;
	int temp_r, temp_c;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			while (tree_pop(&temp_map[r][c], &temp_tree) == 1)
			{
				// 5의 배수인 경우 주변 8방향으로 번식
				if (temp_tree % 5 == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						temp_r = r + dir.r[i];
						temp_c = c + dir.c[i];

						if (temp_r <= 0 || temp_r >= N + 1 || 
							temp_c <= 0 || temp_c >= N + 1)
							continue;

						tree_push(&map[temp_r][temp_c], 1);
					}
				}
				tree_push(&map[r][c], temp_tree);
			}
		}
	}
}

// 겨울
void winter()
{
	live_tree = 0;
	
	// S2D2 로봇이 양분을 추가해줌
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			map[r][c].e += A[r][c];
			live_tree += map[r][c].cnt;
		}
	}
}

void solve()
{
	for (int i = 1; i <= K; i++)
	{
		spring();
		summer();
		autumn();
		winter();
	}

	printf("%d\n", live_tree);
}

int main(void)
{
	init();
	input();
	solve();
}
