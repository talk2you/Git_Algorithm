#include <stdio.h>
#include <string.h>

int N;
int ans;

typedef struct {
	int a, b;
}MEETING;
MEETING meeting[100003];
MEETING temp[100003];
int meeting_size, temp_size;

void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (meeting[i].b < meeting[j].b)
			memcpy(&temp[k++], &meeting[i++], sizeof(MEETING));
		else if(meeting[i].b > meeting[j].b)
			memcpy(&temp[k++], &meeting[j++], sizeof(MEETING));
		else
		{
			if(meeting[i].a < meeting[j].a)
				memcpy(&temp[k++], &meeting[i++], sizeof(MEETING));
			else
				memcpy(&temp[k++], &meeting[j++], sizeof(MEETING));
		}			
	}

	while(i<=mid)	memcpy(&temp[k++], &meeting[i++], sizeof(MEETING));
	while(j<=end)	memcpy(&temp[k++], &meeting[j++], sizeof(MEETING));

	for(int i=start;i<=end;i++)
		memcpy(&meeting[i], &temp[i-start], sizeof(MEETING));
}

void sort(int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) >> 1;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		meeting[meeting_size].a = a;
		meeting[meeting_size].b = b;
		meeting_size++;
	}
}

void solve()
{
	if (N == 1)
	{
		printf("1\n");
		return;
	}

	sort(0, N - 1);

	int now = 0;
	for (int i = 0; i < N; i++)
	{
		if (now <= meeting[i].a)
		{
			ans++;
			now = meeting[i].b;
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}
