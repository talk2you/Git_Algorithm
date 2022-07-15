#include <stdio.h>

#define Max(a, b) a>b?a:b
#define Min(a, b) a>b?b:a

// 드래곤----------- 커브!!!!!!!!!!!!!!!!!!

int N;
int x, y, d, g;

typedef struct {
	int x[4], y[4];
}DIR;

// 범위를 벗어날 수 있어서 위아래 1024씩 범위 지정
// 길이 = g <= 10, 최대 2^10 = 1024;
int map[2050][2050];
int x_off = 1000;
int y_off = 1000;

typedef struct {
	int x, y, d, g;
}DC;
DC dc[20];

// 100x100 안에서만 카운트
typedef struct {
	int min_x, max_x;
	int min_y, max_y;
}SQURE;
SQURE screen = {1100,1000,1100,1000};

int ans = 0;

// 0 <= x,y <= 100
// 0 <= d <= 3
// 0 <= g <= 10

//우상좌하
DIR dir = { {1,0,-1,0}, {0,-1,0,1} };

// 큐
char que_dir[1024];
int end = 0;

// 큐 초기화는 end만 0으로 조진다
void que_clear()
{
	end = 0;
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%d %d %d %d", &dc[i].x, &dc[i].y, &dc[i].d, &dc[i].g);
}

// 드래곤 커브 그리는 방법
// 1. g = 0일때의 방향을 큐에 넣는다
// 2. 큐를 역방향으로 읽으면서 dir값을 1 추가한 값을 다시 큐에 이어서 추가한다.
// 3. 4를 넘어가면 %4로 나머지로 저장
// 4. 처음부터 저장된 큐까지 읽으면 드래곤 커브 완성
void draw_dc(int _n)
{
	int temp_end;
	int temp_dir;
	int x = x_off + dc[_n].x, y = y_off + dc[_n].y;

	que_dir[end++] = dc[_n].d;

	for (int j = 0; j < dc[_n].g; j++)
	{	
		temp_end = end;
		for (int i = temp_end - 1; i >= 0; i--)
		{
			temp_dir = que_dir[i] + 1;
			temp_dir %= 4;
			que_dir[end++] = temp_dir;
		}		
	}

	map[y][x] = 1;
	screen.max_x = Max(x, screen.max_x);
	screen.min_x = Min(x, screen.min_x);
	screen.max_y = Max(y, screen.max_y);
	screen.min_y = Min(y, screen.min_y);

	for (int i = 0; i < end; i++)
	{
		y += dir.y[que_dir[i]];
		x += dir.x[que_dir[i]];
		map[y][x] = 1;

		screen.max_x = Max(x, screen.max_x);
		screen.min_x = Min(x, screen.min_x);
		screen.max_y = Max(y, screen.max_y);
		screen.min_y = Min(y, screen.min_y);
	}
}

void print_map()
{
	for (int y = screen.min_y; y <= screen.max_y; y++)
	{
		for (int x = screen.min_x; x <= screen.max_x; x++)
		{
			printf("%d ", map[y][x]);
		}
		printf("\n");
	}
}

void count_squre()
{
	for (int y = screen.min_y; y <= screen.max_y; y++)
	{
		for (int x = screen.min_x; x <= screen.max_x; x++)
		{
			if (map[y][x] && map[y][x+1] && map[y+1][x] && map[y+1][x+1])
			{
				ans++;
			}
		}
	}
}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		draw_dc(i);
		
		/*printf("dc[%d]:\n", i);
		for (int i = 0; i < end; i++)
			printf("%d ", que_dir[i]);
		printf("\n");*/


		que_clear();
	}
	
	count_squre();
	printf("%d\n", ans);
	//print_map();
}

int main(void)
{
	input();
	solve();
}