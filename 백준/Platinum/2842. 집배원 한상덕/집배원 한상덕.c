#include <stdio.h>
#include <string.h>

#define MAX_QUE 2505
#define Min(a, b)	((a<b)?(a):(b))
#define Max(a, b)	((a>b)?(a):(b))

int N;
int ans_left, ans_right;
int ans = 1<<30;

int altiutde[51][51];
char map[51][51];
char visit[51][51];
char flag[1000001];

typedef struct{
	int r, c;
}LOC;
LOC house[2500];
LOC office;
int house_cnt;

typedef struct {
	int r[8], c[8];
}DIR;
DIR dir = { {-1,-1,-1,0,0,1,1,1},{-1,0,1,-1,1,-1,0,1} };

LOC que[MAX_QUE];
int front, end;

int min = 1 << 30;
int max;

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = front - 1;
	if (temp < 0)
		temp += MAX_QUE;

	if (temp == end)
		return 1;
	return 0;
}

int push(int r, int c)
{
	if (isFull())
		return 0;

	que[end].r = r;
	que[end++].c = c;
	end %= MAX_QUE;
	return 1;
}

int pop(int *r, int *c)
{
	if (isEmpty())
		return 0;

	*r = que[front].r;
	*c = que[front++].c;
	front %= MAX_QUE;
	return 1;
}

void input()
{
	scanf("%d", &N);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf(" %c", &map[r][c]);
			if (map[r][c] == 'K')
			{
				house[house_cnt].r = r;
				house[house_cnt++].c = c;
			}
			else if (map[r][c] == 'P')
			{
				office.r = r;
				office.c = c;
			}
		}

	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &altiutde[r][c]);
			flag[altiutde[r][c]] = 1;

			min = Min(min, altiutde[r][c]);
			max = Max(max, altiutde[r][c]);
		}
}

void solve()
{
	int r, c;
	int left = min, right = min;
	int visit_cnt = 0;
	
	while (left <= right && right <= max)
	{
		memset(visit, 0, sizeof(visit));
		visit_cnt = 0;

		push(office.r, office.c);
		visit[office.r][office.c];

		while (pop(&r, &c))
		{
			if (altiutde[r][c] < left || right < altiutde[r][c])
				continue;

			//printf("pop : %d %d, l:%d, r:%d\n", r, c, left, right);

			if(map[r][c] == 'K')
				visit_cnt++;

			for (int i = 0; i < 8; i++)
			{
				int temp_r = r + dir.r[i];
				int temp_c = c + dir.c[i];
				
				if (temp_r < 0 || temp_r >= N || temp_c < 0 || temp_c >= N)
					continue;

				if (visit[temp_r][temp_c])
					continue;

				visit[temp_r][temp_c] = 1;
				push(temp_r, temp_c);
			}
		}

		if (visit_cnt == house_cnt)
		{
			ans_left = left;
			ans_right = right;
			ans = Min(ans, ans_right - ans_left);

			for (int i = left; i <= max; i++)
			{
				left++;
				if (flag[left])
					break;
			}
		}
		else
		{
			for (int i = right; i <= max; i++)
			{
				right++;
				if (flag[right])
					break;
			}
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}