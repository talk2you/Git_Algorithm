#include <stdio.h>

#define MAX_KEY 50
#define MAX_TABLE 2000000

#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)
#define Abs(a)	(((a)<0)?-(a):(a))


typedef struct Hash
{
	char key[6][6];
	int data;
	struct Hash *hash;
}Hash;
Hash pool[MAX_TABLE];
Hash head[MAX_TABLE];
int pool_cnt;

typedef struct {
	int r[4], c[4];
}DIR;
// 상,하,좌,우
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

typedef struct {
	int r, c;
	int dir;
	int len;
}BLOCK;
BLOCK block[11];
int max_n = 1;

int max_move = 10;
int min_cnt = 99;
char map[6][6];

void map_copy(char map1[6][6], char map2[6][6])
{
	for (int r = 0; r < 6; r++)
		for (int c = 0; c < 6; c++)
			map1[r][c] = map2[r][c];
}

int map_comp(char map1[6][6], char map2[6][6])
{
	for (int r = 0; r < 6; r++)
		for (int c = 0; c < 6; c++)
			if (map1[r][c] != map2[r][c])
				return 1;
	return 0;
}

unsigned long hash(char _map[6][6])
{
	unsigned long hash = 5381;

	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{	
			hash = (((hash << 5) + hash) + _map[r][c]) % MAX_TABLE;
		} 	
	}
	return hash % MAX_TABLE;
}

int add(char _map[6][6], int data)
{
	unsigned long h = hash(_map);
	Hash *nd = &head[h];

	while (nd->hash) 
	{
		nd = nd->hash;
		if (map_comp(nd->key, _map) == 0)
		{
			if (nd->data > data)
			{
				nd->data = data;
				return 1;
			}
			return 0;
		}
	}
	map_copy(pool[pool_cnt].key, _map);
	pool[pool_cnt].data = data;
	pool[pool_cnt].hash = head[h].hash;
	head[h].hash = &pool[pool_cnt];
	pool_cnt++;
	
	return 1;
}

void init()
{
	for (int i = 0; i <= 10; i++)
		block[i].dir = -1;
}

void input()
{
	int a;
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			scanf(" %d", &a);
			map[r][c] = '0' + a;
			max_n = Max(map[r][c]-'0', max_n);
		}
	}

	add(map, 0);
}

void check_block(int i, char _map[6][6], BLOCK _block[11])
{
	int check_flag = 0;

	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			if (_map[r][c] - '0' == i && check_flag == 0)
			{
				check_flag = 1;
				_block[i].r = r;
				_block[i].c = c;
				_block[i].len++;
			}
			else if (_map[r][c] - '0' == i && check_flag == 1)
			{
				if (_map[r - 1][c] - '0' == i)
					_block[i].dir = 1;
				else
					_block[i].dir = 0;
				_block[i].len++;
			}
			else if (_map[r][c] - '0' != i && check_flag == 1)
			{
				if (_block[i].dir == 0)
					return;
				else if (_map[r - 1][c] - '0' == i)
					return;
			}
		}
	}
}

void dfs(int _cnt, char _map[6][6])
{
	int temp_min=0, temp_max=0;
	char temp_map[6][6];
	BLOCK temp_block[11] = { 0, };
	int diff = 0;

	if (_cnt > 8)
		return;

	for (int i = 1; i <= max_n; i++)
	{
		temp_block[i].dir = -1;
		check_block(i, _map, temp_block);
		
		if (temp_block[i].dir == 0)
		{
			temp_max = temp_min = temp_block[i].c;
			while (_map[temp_block[i].r][temp_min - 1] == '0' && temp_min > 0)
				--temp_min;
			while (_map[temp_block[i].r][temp_max + temp_block[i].len] == '0' && temp_max + temp_block[i].len < 6)
				++temp_max;

			if (i == 1 && temp_max == (6-temp_block[i].len))
			{
				//printf(">>> %d\n", _cnt);
				min_cnt = Min(min_cnt, _cnt + (6-temp_block[1].c));
				return;
			}
		}
		else
		{
			temp_max = temp_min = temp_block[i].r;
			while (_map[temp_min-1][temp_block[i].c] == '0' && temp_min > 0)
				--temp_min;
			while (_map[temp_max + temp_block[i].len][temp_block[i].c] == '0' && temp_max + temp_block[i].len < 6)
				++temp_max;
		}

		map_copy(temp_map, _map);
		
		for (int k = temp_min; k <= temp_max; k++)
		{
			map_copy(temp_map, _map);
			for (int j = 0; j < temp_block[i].len; j++)
			{
				if (temp_block[i].dir == 0)
					temp_map[temp_block[i].r][temp_block[i].c + j] = '0';
				else
					temp_map[temp_block[i].r + j][temp_block[i].c] = '0';
			}

			for (int j = 0; j < temp_block[i].len; j++)
			{
				if (temp_block[i].dir == 0)
				{
					temp_map[temp_block[i].r][k + j] = '0' + i;
					diff = Abs(k - temp_block[i].c);
				}
				else
				{
					temp_map[k + j][temp_block[i].c] = '0' + i;
					diff = Abs(k - temp_block[i].r);
				}
			}

			if (add(temp_map, _cnt + diff))
			{
				/*printf("[%d] (%d %d), %d %d\n", i, temp_block[i].r, temp_block[i].c, temp_block[i].dir, temp_block[i].len);
				printf("%d %d\n", temp_min, temp_max);
				printf("%d\n", _cnt+diff);

				for (int r = 0; r < 6; r++)
				{
					for (int c = 0; c < 6; c++)
						printf("%c ", temp_map[r][c]);
					printf("\n");
				}
				printf("---------\n");*/

				dfs(_cnt + diff, temp_map);
			}
		}	
		

		//printf("[%d] %d %d\n",i, temp_min, temp_max);
	}
}

void solve()
{
	dfs(0, map);
	if (min_cnt == 99 || min_cnt > 10)
		min_cnt = -1;
	printf("%d\n", min_cnt);
}

int main(void)
{
	init();
	input();
	solve();

	return 0;
}