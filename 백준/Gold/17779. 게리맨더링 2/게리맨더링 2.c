#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))
#define Min(a, b) ((a<b)?(a):(b))

int N;
int map[23][23];
int visit[23][23];

int popular[6];
int max_pop = 0, min_pop = 1<<31;
int min_diff = 1 << 30;

void input()
{
	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &map[r][c]);
}

void print_visit()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			printf("%d ", visit[r][c]);
		}
		printf("\n");
	}
}


void solve()
{
	int d1 = 1, d2 = 1;
	int x_range;

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			for (d1 = 1; x + d1 + d2 <= N; d1++)
			{
				for (d2 = 1; x + d1 + d2 <= N; d2++)
				{
					if (y - d1 >= 1 && y - d1 < y && y < y + d2 && y + d2 <= N)
					{
						memset(visit, 0, sizeof(map));
						memset(popular, 0, sizeof(popular));
						max_pop = 0;
						min_pop = 1<<30;

						//printf("[%d %d] %d, %d\n", x, y, d1, d2);

						for (int r = y - d1; r <= y; r++)
						{
							x_range = r - (y - d1);
							if (x_range > d2) x_range = -x_range + d2*2;
							
							for (int c = x + d1 - (r - (y - d1));c<= x+d1 + x_range;c++)
							{
								visit[r][c] = 5;
								popular[5] += map[r][c];
							}
						}

						for (int r = y + d2; r > y; r--)
						{
							x_range = -(r - (y + d2));
							if (x_range > d1) x_range = -x_range + d1*2;

							for (int c = x + d2 + (r - (y + d2)); c <= x + d2 + x_range; c++)
							{
								visit[r][c] = 5;
								popular[5] += map[r][c];
							}
						}

						for (int r = 1; r <= N; r++)
						{
							for (int c = 1; c <= N; c++)
							{
								if (visit[r][c] != 0)
									continue;

								// 1번 선거구
								if (c <= x + (y - r > d1 ? d1 : y - r) && r < y)
								{
									visit[r][c] = 1;
									popular[1] += map[r][c];
								}
								// 2번 선거구
								else if (x + d1 + (r - y > 0 ? r - y : 0) < c && c <= N && r <= y - d1 + d2)
								{
									visit[r][c] = 2;
									popular[2] += map[r][c];
								}
								// 3번 선거구
								else if (c < x + d2 && y <= r && r <= N)
								{
									visit[r][c] = 3;
									popular[3] += map[r][c];
								}
								else
								{
									visit[r][c] = 4;
									popular[4] += map[r][c];
								}
							}
						}

						for (int i = 1; i <= 5; i++)
						{
							min_pop = Min(min_pop, popular[i]);
							max_pop = Max(max_pop, popular[i]);
						}
						min_diff = Min(min_diff, max_pop - min_pop);
						//printf("%d %d %d %d %d\n", popular[1], popular[2], popular[3], popular[4], popular[5]);
						//printf("%d\n", min_diff);
						
						//print_visit();
					}
				}

				d2 = 1;
			}
		}
	}

	printf("%d\n", min_diff);
}

int main(void)
{
	input();
	solve();
}