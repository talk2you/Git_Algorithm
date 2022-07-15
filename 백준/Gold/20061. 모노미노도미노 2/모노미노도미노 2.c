#include <stdio.h>

#define Max(a,b) ((a>b)?(a):(b))

int N;
int blue[4];
int green[4];

int size_b[4];
int size_g[4];

int point;

void blue_solve(int t, int r, int c)
{
	// 한개의 블록
	if (t == 1)
	{
		blue[r] |= (1 << size_b[r]++);
	}
	// 가로 블록
	else if (t == 2)
	{
		blue[r] |= (1 << size_b[r]++);
		blue[r] |= (1 << size_b[r]++);
	}
	// 세로 블록
	else if (t == 3)
	{
		size_b[r] = Max(size_b[r], size_b[r + 1]);
		size_b[r + 1] = size_b[r];

		blue[r] |= (1 << size_b[r]++);
		blue[r+1] |= (1 << size_b[r+1]++);
	}

	// 한줄 삭제 해야할 때
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		if (blue[0] & (1 << i) && blue[1] & (1 << i) &&
			blue[2] & (1 << i) && blue[3] & (1 << i))
		{
			for (int j = 0; j < 4; j++)
			{
				temp = 0xFF ^ ((1 << (i + 1)) - 1);
				temp = (temp & blue[j]) >> 1;
				temp |= (((1 << i) - 1) & blue[j]);
				blue[j] = temp;

				size_b[j] = 0;
				for (int k = 0; k < 4; k++)
				{
					if (blue[j] & (1 << k))
						size_b[j] = k + 1;
				}
			}	
			point++;
			i--;
		}
	}

	// 연한색에 위치했을때
	for (int i = 0; i < 4; i++)
	{
		int block_over = (blue[i] & 0x30) >> 4;
		if (block_over)
		{
			while (block_over)
			{
				for (int j = 0; j < 4; j++)
				{
					blue[j] >>= 1;
					if(size_b[j] >= 1)
						size_b[j] -= 1;
				}
				block_over >>= 1;
			}
		}
	}
}

void green_solve(int t, int r, int c)
{
	if (t == 2)
		t = 3;
	else if (t == 3)
		t = 2;
	
	int temp = r;
	r = 3 - c;
	c = temp;
	

	// 한개의 블록
	if (t == 1)
	{
		green[r] |= (1 << size_g[r]++);
	}
	// 가로 블록
	else if (t == 2)
	{
		green[r] |= (1 << size_g[r]++);
		green[r] |= (1 << size_g[r]++);
	}
	// 세로 블록
	else if (t == 3)
	{
		size_g[r] = Max(size_g[r], size_g[r - 1]);
		size_g[r - 1] = size_g[r];

		green[r] |= (1 << size_g[r]++);
		green[r - 1] |= (1 << size_g[r - 1]++);
	}

	// 한줄 삭제 해야할 때
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		if (green[0] & (1 << i) && green[1] & (1 << i) &&
			green[2] & (1 << i) && green[3] & (1 << i))
		{
			for (int j = 0; j < 4; j++)
			{
				temp = 0xFF ^ ((1 << (i + 1)) - 1);
				temp = (temp & green[j]) >> 1;
				temp |= (((1 << i) - 1) & green[j]);
				green[j] = temp;

				size_g[j] = 0;
				for (int k = 0; k < 4; k++)
				{
					if (green[j] & (1 << k))
						size_g[j] = k + 1;
				}
			}
			point++;
			i--;
		}
	}

	// 연한색에 위치했을때
	for (int i = 0; i < 4; i++)
	{
		int block_over = (green[i] & 0x30) >> 4;
		if (block_over)
		{
			while (block_over)
			{
				for (int j = 0; j < 4; j++)
				{
					green[j] >>= 1;
					if (size_g[j] >= 1)
						size_g[j] -= 1;
				}
				block_over >>= 1;
			}
		}
	}
}

void input()
{
	int t, r, c;
	int ans = 0;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d", &t, &r, &c);
		blue_solve(t, r, c);
		green_solve(t, r, c);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (blue[i] & (1 << j))
				ans++;
			if (green[i] & (1 << j))
				ans++;
		}
	}

	printf("%d\n%d\n", point, ans);
}

int main(void)
{
	input();
}