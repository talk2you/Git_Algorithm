#include <stdio.h>
#include <string.h>

#define MAX_QUE 10000

typedef struct {
	int n;
	int clip;
	int cnt;
}QUE;

int S;
QUE que[MAX_QUE];
int front, end;
int map[2000][2000];

int isFull()
{
	int temp;
	temp = front - 1;
	if (temp < 0)
		temp = MAX_QUE - 1;

	if (temp == end)
		return 1;
	return 0;
}

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int enque(int d, int clip, int cnt)
{
	if (!isFull())
	{
		que[end].n = d;
		que[end].clip = clip;
		que[end].cnt = cnt;
		end++;
		end %= MAX_QUE;

		return 1;
	}
	return 0;
}

int deque(int *d, int *clip, int *cnt)
{
	if (!isEmpty())
	{
		*d = que[front].n;
		*clip = que[front].clip;
		*cnt = que[front].cnt;
		front++;
		front %= MAX_QUE;
		return 1;
	}
	return 0;
}

void input()
{
	scanf("%d", &S);
	for (int r = 0; r < 2000; r++)
		for (int c = 0; c < 2000; c++)
			map[r][c] = 0;
}

void bfs(int start)
{
	int temp, clip = 0, cnt = 0;
	enque(start, clip, cnt);
	map[start][clip] = 1;

	int case1, case2, case3;

	while (deque(&temp, &clip, &cnt))
	{
		if (1 <= temp && temp <= 2000)
		{
			//printf("%d %d %d\n", temp, clip, cnt);
			// 화면으로 복사
			case1 = temp + clip;
			if (case1 <= 2000)
			{
				if (map[case1][clip] == 0)
				{
					map[case1][clip] = 1;
					enque(case1, clip, cnt + 1);
				}
			}
			// 클립보드 복사
			case2 = temp;
			if (case2 <= 2000)
			{
				if (map[case2][temp] == 0)
				{
					map[case2][temp] = 1;
					enque(case2, temp, cnt + 1);
				}
			}
			// 화면의 이모티콘 하나 삭제
			case3 = temp - 1;
			if (map[case3][clip] == 0)
			{
				map[case3][clip] = 1;
				enque(case3, clip, cnt + 1);
			}

			if (temp == S)
			{
				printf("%d\n", cnt);
				break;
			}
		}
	}
}

int main(void)
{
	input();
	bfs(1);
    
    return 0;
}