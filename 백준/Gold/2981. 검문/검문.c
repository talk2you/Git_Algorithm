#include <stdio.h>
#include <math.h>

#define Min(a, b) ((a<b)?(a):(b))
#define Max(a, b) ((a>b)?(a):(b))
#define Abs(a) (((a)<0)?-(a):(a))

int N;
int num[103];
int list[5000];
int sorted[5000];
int size;

// 약수 정렬용으로 합병정렬
void merge(int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;
	

	while (i <= mid && j <= end)
	{
		if (list[i] < list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	while (i <= mid)	sorted[k++] = list[i++];
	while (j <= end)	sorted[k++] = list[j++];

	for (int i = start;i <= end;i++)
		list[i] = sorted[i - start];
}

void sort(int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

// 입력
void input()
{
	scanf("%d", &N);

	for (int i = 0;i < N;i++)
		scanf("%d", &num[i]);
}

// 최대공약수 계산
int gcd(int a, int b)
{
	int aa = Max(a, b);
	int bb = Min(a, b);
	int r = 1;

	while (r)
	{
		r = aa % bb;
		aa = bb;
		bb = r;
	}

	return aa;
}

void solve()
{
	int temp;

	// 정렬 안하고 절대값 취해도 됨
	temp = Abs(num[1] - num[0]);
	for (int i = 2;i < N;i++)
	{
		// 각 차이값에 대한 최대공약수 계산
		temp = gcd(temp, Abs(num[i] - num[i - 1]));
		if (temp == 2)
			break;
	}
	
	// 1보다 큰 약수 리스트 만들기
	list[size++] = temp;
	for (int i = 2;i <= sqrt(temp);i++)
	{
		if (temp %i == 0)
		{
			if (i == temp / i)
				list[size++] = i;
			else
			{
				list[size++] = i;
				list[size++] = (temp / i);
			}
		}
	}
	// 약수 크기순으로 정렬
	sort(0, size-1);

	for (int i = 0;i < size;i++)
		printf("%d ", list[i]);
	printf("\n");
}

int main(void)
{
	input();
	solve();
}