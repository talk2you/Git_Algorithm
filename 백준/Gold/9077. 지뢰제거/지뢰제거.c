#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

int N;
char map[10011][10011];
int ans = 0;

typedef struct {
	int x, y;
}LIST;
LIST list[100001];

void init()
{
	ans = 0;
	memset(map, 0, sizeof(map));
}

void input()
{
	int x, y;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &x, &y);
		list[i].x = x;
		list[i].y = y;

		for (int i = x; i <= x + 10; i++)
		{
			for (int j = y; j <= y + 10; j++)
			{
				map[j][i]++;
				ans = Max(ans, map[j][i]);
			}
		}
	}		

	printf("%d\n", ans);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		input();
	}
}