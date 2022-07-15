#include <stdio.h>

int N, L;
int map[100][100];
int bridge_cnt = 0;

void input()
{
	int start = 0;
	int length = 0;

	scanf("%d %d", &N, &L);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}
}

void solve_c()
{
	int start, length;
	int flag = 0;
	int bridge = 1;

	for (int r = 0; r < N; r++)
	{
		start = map[r][0];
		length = 1;
		bridge = 1;
		flag = 0;
		for (int c = 1; c < N; c++)
		{
			//printf("[%d %d] ", r, c);

			// 평행
			if (map[r][c] == start)
			{
				//printf("--\n");
				length++;
				if (flag == 1)
				{
					if (length >= L)
					{
						flag = 0;
						length = 0;
					}
				}
			}
			// 업
			else if (map[r][c] - 1 == start)
			{
				//printf("_-\n");
				if (length < L)
				{
					bridge = 0;
					//printf("not able\n");
					flag = 0;
					break;
				}
				start = map[r][c];
				length = 1;
			}
			// 다운
			else if (map[r][c] + 1 == start)
			{
				//printf("-_\n");
				if (flag == 1)
				{
					//printf("not able\n");
					bridge = 0;
					flag = 0;
					break;
				}
				
				flag = 1;
				start = map[r][c];
				length = 1;
			}
			else
			{
				//printf("not able\n");
				bridge = 0;
				flag = 0;
				break;
			}
			if (flag && length >= L)
			{
				flag = 0;
				length = 0;
			}
		}
		if (flag)
		{
			//printf("not able\n");
			bridge = 0;
		}
		if (bridge)
			bridge_cnt++;
		//printf("--------------\n");
	}
}

void solve_r()
{
	int start, length;
	int flag = 0;
	int bridge = 1;

	for (int c = 0; c < N; c++)
	{
		start = map[0][c];
		flag = 0;
		length = 1;
		bridge = 1;
		for (int r = 1; r < N; r++)
		{
			//printf("[%d %d] ", r, c);

			// 평행
			if (map[r][c] == start)
			{
				//printf("--\n");
				length++;
				//printf("length : %d, flag : %d\n", length, flag);
				if (flag == 1)
				{
					if (length >= L)
					{
						flag = 0;
						length = 0;
					}
				}
			}
			// 업
			else if (map[r][c] - 1 == start)
			{
				//printf("_-\n");
				if (length < L)
				{
					bridge = 0;
					//printf("not able\n");
					flag = 0;
					break;
				}
				start = map[r][c];
				length = 1;
			}
			// 다운
			else if (map[r][c] + 1 == start)
			{
				//printf("-_\n");
				if (flag == 1)
				{
					//printf("not able\n");
					bridge = 0;
					flag = 0;
					break;
				}

				flag = 1;
				start = map[r][c];
				length = 1;
			}
			else
			{
				//printf("not able\n");
				bridge = 0;
				flag = 0;
				break;
			}
			if (flag && length >= L)
			{
				flag = 0;
				length = 0;
			}
		}
		if (flag)
		{
			//printf("not able\n");
			bridge = 0;
		}
		if (bridge)
			bridge_cnt++;
		//printf("--------------\n");
	}
}

int main(void)
{
	input();
	solve_c();
	solve_r();
	printf("%d\n", bridge_cnt);

	return 0;
}