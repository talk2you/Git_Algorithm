#include <stdio.h>

int N, M;

int arr[100][100];

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			scanf("%d", &arr[r][c]);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
		{
			int a;
			scanf("%d", &a);
			arr[r][c] += a;
		}

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
			printf("%d ", arr[r][c]);
		printf("\n");
	}
}

int main(void)
{
	input();
}