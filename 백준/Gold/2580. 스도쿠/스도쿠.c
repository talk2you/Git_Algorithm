#include <stdio.h>

int map[9][9];
int row[9], col[9], area[9];

typedef struct {
	int r, c;
}EMPTY;
EMPTY empty[90];
int empty_size;

void input()
{
	for (int r = 0;r < 9;r++)
	{
		for (int c = 0;c < 9;c++)
		{
			scanf("%d", &map[r][c]);
			
			if (map[r][c])
			{
				row[r] |= (1 << (map[r][c] - 1));
				col[c] |= (1 << (map[r][c] - 1));
				area[r/3*3 + c/3] |= (1 << (map[r][c] - 1));
			}
			else
			{
				empty[empty_size].r = r;
				empty[empty_size++].c = c;
			}
		}
	}
}

int backtracking(int _idx)
{
	int temp_r, temp_c;
	int fin_flag = 0;

	if (_idx >= empty_size)
	{
		// 여기까지 오면 종료
		for (int r = 0;r < 9;r++)
		{
			for (int c = 0;c < 9;c++)
				printf("%d ", map[r][c]);
			printf("\n");
		}
		return 1;
	}

	temp_r = empty[_idx].r;
	temp_c = empty[_idx].c;

	for (int i = 0;i < 9;i++)
	{
		if ((area[temp_r / 3 * 3 + temp_c / 3] & (1 << i)) == 0 &&
			(row[temp_r] & (1 << i)) == 0 && (col[temp_c] & (1 << i)) == 0)
		{
			map[temp_r][temp_c] = i + 1;
			area[temp_r / 3 * 3 + temp_c / 3] |= (1 << i);
			row[temp_r] |= (1 << i);
			col[temp_c] |= (1 << i);

			if (backtracking(_idx + 1))
				fin_flag = 1;

			map[temp_r][temp_c] = 0;
			area[temp_r / 3 * 3 + temp_c / 3] &= ~(1 << i);
			row[temp_r] &= ~(1 << i);
			col[temp_c] &= ~(1 << i);
		}
		if (fin_flag)
			return 1;
	}
	return 0;
}

void solve()
{
	int temp_r, temp_c;
	int idx = 0, fin_flag = 0;
	
	// 저장된 빈칸 위치 로드
	temp_r = empty[idx].r;
	temp_c = empty[idx].c;

	for (int i = 0;i < 9;i++)
	{
		// 각 라인배열과 공간 배열에 빈칸이 겹치는지 체크
		if ((area[temp_r / 3 * 3 + temp_c / 3] & (1 << i)) == 0 &&
			(row[temp_r] & (1 << i)) == 0 && (col[temp_c] & (1 << i)) == 0)
		{
			// 맵에 데이터 넣어보고 비트플래그 설정
			map[temp_r][temp_c] = i + 1;
			area[temp_r / 3 * 3 + temp_c / 3] |= (1 << i);
			row[temp_r] |= (1 << i);
			col[temp_c] |= (1 << i);
			
			// 결과 나오면 종료
			if (backtracking(idx + 1))
				fin_flag = 1;

			// 맵관련 데이터 초기화
			map[temp_r][temp_c] = 0;
			area[temp_r / 3 * 3 + temp_c / 3] &= ~(1 << i);
			row[temp_r] &= ~(1 << i);
			col[temp_c] &= ~(1 << i);
		}
		if (fin_flag)
			return;
	}	
}

int main(void)
{
	input();
	solve();
}