#include <stdio.h>

#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))

int R, C;
char map[1508][1508];
int ld[753][753];
int rd[753][753];
int lu[753][753];
int ru[753][753];
int ans = 0;

typedef struct {
	int r[4], c[4];
}DIR;
// 좌상, 우상, 우하, 좌하
DIR dir = { {-1,-1,1,1},{-1,1,1,-1} };

void input()
{
	scanf("%d %d", &R, &C);

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			scanf(" %1hhd", &map[r][c]);
}

void solve()
{
	// 좌하->우상 방향으로 좌하카운트
	for (int r = R; r >= 1; --r)
		for (int c = 1; c <= C; ++c)
			if (map[r][c])
				ld[r][c] = ld[r + 1][c - 1] + 1;

	// 우하->좌상 방향으로 우하카운트
	for (int r = R; r >= 1; --r)
		for (int c = C; c >= 1; --c)
			if (map[r][c])
				rd[r][c] = rd[r + 1][c + 1] + 1;

	// 좌상->우하 방향으로 좌상카운트
	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c)
			if (map[r][c])
				lu[r][c] = lu[r - 1][c - 1] + 1;

	// 우상->좌하 방향으로 우상카운트
	for (int r = 1; r <= R; ++r)
		for (int c = C; c >= 1; --c)
			if (map[r][c])
				ru[r][c] = ru[r - 1][c + 1] + 1;

	// 꼭대기로부터 좌하, 우하 방향으로 연결된 카운트 최소값 뽑기
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			int d = Min(ld[r][c], rd[r][c]);	
			// 1단계, 2단계.. d단계까지 크기값 갱신
			for (int i = 1; i <= d; i++)
				if(map[r + ((i - 1) * 2)][c] && lu[r + ((i - 1) * 2)][c] >= i && ru[r + ((i - 1) * 2)][c] >= i)
					ans = Max(ans, i);

			d = Min(ru[r][c], rd[r][c]);
			// 1단계, 2단계.. d단계까지 크기값 갱신
			for (int i = 1; i <= d; i++)
				if (map[r][c + ((i - 1) * 2)] && lu[r][c + ((i - 1) * 2)] >= i && ld[r][c + ((i - 1) * 2)] >= i)
					ans = Max(ans, i);
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}