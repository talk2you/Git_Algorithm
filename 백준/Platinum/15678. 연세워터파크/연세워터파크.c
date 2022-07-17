#include <stdio.h>

#define MAX 100003
#define Max(a, b) ((a>b)?(a):(b))

int N, D;
long long ans = -9223372036854775807;

long long dp[MAX];

typedef struct {
	int idx;
	long long data;
}DEQUE;
DEQUE deque[MAX];
int start, end;


int isEmpty()
{
	if (start == end)
		return 1;
	return 0;
}

int isFull()
{
	int temp = start - 1;
	if (temp < 0)
		temp += MAX;
	if (temp == end)
		return 1;
	return 0;
}

int front_push(int idx, long long data)
{
	if (isFull())
		return 0;
	
	--start;
	if (start < 0)
		start += MAX;
	deque[start].idx = idx;
	deque[start].data = data;
	return 1;
}

int back_push(int idx, long long data)
{
	if (isFull())
		return 0;

	deque[end].idx = idx;
	deque[end].data = data;
	end++;
	end %= MAX;
	return 1;
}

int front_pop(int *idx, long long* data)
{
	if (isEmpty())
		return 0;
	
	*idx = deque[start].idx;
	*data = deque[start].data;
	start++;
	start %= MAX;
	return 1;
}

int back_pop(int *idx, long long *data)
{
	if (isEmpty())
		return 0;
	--end;
	if (end < 0)
		end += MAX;
	*idx = deque[end].idx;
	*data = deque[end].data;
	return 1;
}

int check_front(int *idx, long long *data)
{
	if (isEmpty())
		return 0;

	*idx = deque[start].idx;
	*data = deque[start].data;
	return 1;
}

int check_back(int *idx, long long *data)
{
	if (isEmpty())
		return 0;

	int temp = end - 1;
	if (temp < 0)
		temp += MAX;

	*idx = deque[temp].idx;
	*data = deque[temp].data;
	return 1;
}


void input()
{
	scanf("%d %d", &N, &D);
}

void solve()
{
	int a;
	int pop_idx = -1, dummy_idx;
	long long pop_data = -1, dummy_data;

	for (int i = 0;i < N;++i)
	{
		scanf("%d", &a);

		// 덱 앞에서 i-D보다 인덱스값이 낮으면 삭제
		if (check_front(&pop_idx, &pop_data))
		{
			if (pop_idx < i - D)
				front_pop(&dummy_idx, &dummy_data);
		}
		dp[i] = a;

		if (!isEmpty())
			dp[i] = Max(dp[i], dp[i]+deque[start].data);			
		
		ans = Max(ans, dp[i]);

		// 덱 뒤에서부터 dp[i]보다 값 낮은값 전부 삭제
		while (check_back(&pop_idx, &pop_data))
		{
			if (dp[i] > pop_data)
			{
				back_pop(&dummy_idx, &dummy_data);
			}
			else
				break;
		}

		back_push(i, dp[i]);
	}

	printf("%lld\n", ans);
}

int main(void)
{
	input();
	solve();
}