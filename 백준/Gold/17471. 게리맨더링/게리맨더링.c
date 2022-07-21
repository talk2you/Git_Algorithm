#include <stdio.h>
#include <string.h>

#define MAX_QUE 5000
#define Abs(a) ((a<0)?-(a):(a))
#define Min(a, b) ((a<b)?(a):(b))

int N;
int ans = 1<<30;

int popular[12];
int map[12][12];
int visit[12];

int que[MAX_QUE];
int front, end;

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = front - 1;
	temp += MAX_QUE;
	if (temp == end)
		return 1;
	return 0;
}

int push(int n)
{
	if (isFull())
		return 0;

	que[end++] = n;
	end %= MAX_QUE;
	return 1;
}

int pop(int *n)
{
	if (isEmpty())
		return 0;

	*n = que[front++];
	front %= MAX_QUE;
	return 1;
}

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		scanf("%d", &popular[i]);

	int n, a;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &n);

		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a);
			map[i][a] = 1;
		}
	}
}

int check_sector1(int select[12])
{
	int temp_visit[12] = { 0, };
	int n;
	int sum = 0;
	int start = 0;

	for (int i = 1; i <= N; i++)
	{
		if (select[i])
		{
			start = i;
			break;
		}
	}

	push(start);
	sum = popular[start];
	temp_visit[start] = 1;

	while (pop(&n))
	{
		for (int i = 1; i <= N; i++)
		{
			// 인접한 곳이 아니면 패스
			if (map[n][i] == 0)
				continue;			
			// 선거구로 채택된곳이 아니면 패스
			if (select[i] == 0)
				continue;			
			// 방문했었던 적이 있으면 패스
			if (temp_visit[i])
				continue;

			temp_visit[i] = 1;
			sum += popular[i];
			push(i);
		}
	}

	for (int i = 1; i <= N; i++) 
	{
		// 선거구로 채택된곳 중 방문 못한곳이 있으면 -1 리턴
		if (select[i] - temp_visit[i] >= 1)
			return -1;
	}
	// 모두 방문했으면 인구수 리턴
	return sum;
}

int check_sector2(int select[12])
{
	int temp_visit[12] = { 0, };
	int n;
	int sum = 0;
	int start = 0;

	for (int i = 1; i <= N; i++)
	{
		if (select[i] == 0)
		{
			start = i;
			break;
		}
	}

	push(start);
	sum = popular[start];
	temp_visit[start] = 1;

	while (pop(&n))
	{
		for (int i = 1; i <= N; i++)
		{
			// 인접한 곳이 아니면 패스
			if (map[n][i] == 0)
				continue;
			// 제1 선거구로 채택된곳이면 패스
			if (select[i] == 1)
				continue;
			// 방문했었던 적이 있으면 패스
			if (temp_visit[i])
				continue;

			temp_visit[i] = 1;
			sum += popular[i];
			push(i);
		}
	}

	for (int i = 1; i <= N; i++)
	{
		// 1선거구로 채택되지 않은 곳 중 방문 못한곳이 있으면 -1 리턴
		if ((select[i]^1) - temp_visit[i] >= 1)
			return -1;
	}
	// 모두 방문했으면 인구수 리턴
	return sum;

}

void search(int n)
{
	int sum1 = check_sector1(visit);
	int sum2 = check_sector2(visit);

	if (sum1 != -1 && sum2 != -1)
	{
		ans = Min(ans, Abs(sum1 - sum2));
	}

	for (int i = n+1; i <= N; i++)
	{
		if (visit[i])
			continue;

		visit[i] = 1;
		search(i);
		visit[i] = 0;
	}
}

void solve()
{
	for (int i = 1; i <= N; i++)
	{
		visit[i] = 1;
		search(i);
		visit[i] = 0;
	}

	if (ans == 1 << 30)
		ans = -1;
	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}