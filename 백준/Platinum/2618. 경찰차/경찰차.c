#include <stdio.h>

#define Abs(a)	((a<0)?-(a):(a))
#define Max(a, b) ((a>b)?(a):(b))
#define Min(a, b) ((a<b)?(a):(b))

int N, W;
typedef struct {
	int x, y;
}LOC;
LOC list[1001];
int ans[1001];

int dp[1001][1001];

void init()
{
	for (int r = 0; r <= 1000; r++)
		for (int c = 0; c <= 1000; c++)
			dp[r][c] = -1;
}

void input()
{
	scanf("%d %d", &N, &W);

	for (int i = 1; i <= W; i++)
		scanf("%d %d", &list[i].x, &list[i].y);
}

int search(int a, int b)
{
	if (a == W || b == W)
		return 0;

	if (dp[a][b] != -1)
		return dp[a][b];

	int next = Max(a, b) + 1;

	int now_x1 = list[a].x;
	int now_y1 = list[a].y;
	int now_x2 = list[b].x;
	int now_y2 = list[b].y;

	if (a == 0)		now_x1 = now_y1 = 1;
	if (b == 0)		now_x2 = now_y2 = N;

	int distA = Abs(list[next].x - now_x1) + Abs(list[next].y - now_y1);
	int distB = Abs(list[next].x - now_x2) + Abs(list[next].y - now_y2);

	int ret1 = distA + search(next, b);
	int ret2 = distB + search(a, next);

	dp[a][b] = Min(ret1, ret2);

	return dp[a][b];
}

void solve()
{
	printf("%d\n", search(0, 0));

	int a = 0, b = 0;
	
	while (1)
	{
		if (a == W || b == W)
			return;

		int next = Max(a, b) + 1;

		int now_x1 = list[a].x;
		int now_y1 = list[a].y;
		int now_x2 = list[b].x;
		int now_y2 = list[b].y;

		if (a == 0)		now_x1 = now_y1 = 1;
		if (b == 0)		now_x2 = now_y2 = N;

		int distA = Abs(list[next].x - now_x1) + Abs(list[next].y - now_y1);
		int distB = Abs(list[next].x - now_x2) + Abs(list[next].y - now_y2);
		
		if (dp[next][b] + distA < dp[a][next] + distB)
		{
			printf("1\n");
			a = next;
		}
		else
		{
			printf("2\n");
			b = next;
		}
	}
}

int main(void)
{
	init();
	input();
	solve();
}