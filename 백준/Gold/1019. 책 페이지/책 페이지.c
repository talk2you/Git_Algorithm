#include <stdio.h>

int N;
int n[10];

void input()
{
	scanf("%d", &N);
}

// 제곱
int myPow(int a, int p)
{
	int temp = 1;
	while (p-- > 0)		temp *= a;
	return temp;
}

// 1의자리가 9가 아니면 깎아주면서 숫자 계산하기
// 이때 각 단계에 해당하는 10의 배수로 더해진다.
int make_9(int d, int stage)
{
	int temp1 = d;
	int temp2 = d;

	while (temp1 % 10 != 9)
	{
		while (temp1)
		{
			n[temp1 % 10] += myPow(10, stage);
			temp1 /= 10;
		}

		temp2--;
		temp1 = temp2;
	}
	return temp2;
}

void calc(int start, int end)
{
	int temp_start = start;
	int temp_end = end;
	int stage = 0;

	while (temp_end >= 10)
	{
		// 1의자리 9로 만들어주기
		temp_end = make_9(temp_end, stage);
		
		if (temp_start > temp_end)
			break;

		// 10씩 나눠서 개수 판단
		temp_end /= 10;
		temp_start /= 10;

		for (int i = 0; i < 10; i++)
			n[i] += (temp_end - temp_start + 1) * myPow(10, stage);
		
		stage++;
	}

	// < 10의 숫자들은 한번더 더 해줌
	for (int i = temp_start; i <= temp_end; i++)
		n[i] += myPow(10, stage);

}

void solve()
{
	int stage = -1;
	int temp;
	int temp_start, temp_end;
	int re;

	temp = N;

	while (temp >= 10)
	{
		stage = -1;
		temp_end = temp;

		// 찾는 수의 자리수만큼 10의 배수값 계산
		while (temp)
		{
			temp /= 10;
			stage++;
		}
		temp_start = myPow(10, stage);

		// 페이지 숫자 계산
		calc(temp_start, temp_end);

		// 9로 끝나는 숫자로 업데이트
		temp = temp_start - 1;
	}

	for (int i = 1; i <= temp; i++)
		n[i] += 1;
	
	for (int i = 0; i < 10; i++)
		printf("%d ", n[i]);
	printf("\n");
}

int main(void)
{
	input();
	solve();
}