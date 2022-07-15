#include <stdio.h>
#include <string.h>

#define Max(a, b) ((a>b)?(a):(b))

int N, K;
int str_bit[55];
int ans[1 << 21];
int result;

char filter[5] = { 'a', 'c', 'i', 'n', 't' };

// 총 21개, N < 5 일때 0, N = 26 일때 N으로 출력
// b,d,e,f,g,h,j,k,l,m,o,p,q,r,s,u,v,w,x,y,z 순으로 저장
void input()
{
	char s[20];
	int len, bit_idx = 0, flag = 0;

	scanf("%d %d", &N, &K);

	for (int i = 0;i < N;i++)
	{
		scanf("%s", s);
		len = strlen(s);

		for (int j = 0;j < len;j++)
		{
			bit_idx = 0;
			flag = 0;

			for (int k = 0;k < 5;k++)
			{
				if (s[j] == filter[k])
				{
					flag = 1;
					break;
				}
				else if(s[j] > filter[k])
					bit_idx++;
			}		

			if (flag)
				continue;
			else
				str_bit[i] |= (1 << (s[j]- 'a' - bit_idx));
		}
	}
}

/*void search(int bit, int stage, int prev_cnt, int prev_idx)
{
	register int cnt;

	if (stage >= K - 5)
	{
		result = Max(result, prev_cnt);
		return;
	}

	for (register int j = prev_idx;j < 21;++j)
	{
		cnt = 0;

		if(bit & (1<<j))
			continue;

		
		for (register int i = 0;i < N;++i)
		{
			if ((str_bit[i] & ~(bit | (1 << j))) == 0)
			{
				cnt++;
			}
		}

		if (cnt > 0)
			search(bit | (1 << j), stage + 1, cnt, j+1);
	}
}

void solve()
{
	if (K < 5)
	{
		printf("0\n");
		return;
	}
	else if (K == 26)
	{
		printf("%d\n", N);
		return;
	}

	search(0, 0, 0, 0);

	printf("%d\n", result);
}*/


void solve()
{
	register int bit_idx, cnt;
	register int temp;

	if (K < 5)
	{
		printf("0\n");
		return;
	}
	else if (K == 26)
	{
		printf("%d\n", N);
		return;
	}

	for (register int j = 0;j < N;++j)
	{
		if (str_bit[j] == 0)
			++result;
	}

	for (register int i = 0;i < 1 << 21;++i)
	{
		bit_idx = 0;
		temp = i;

		while (temp)
		{
			if (temp & 0x01)
				bit_idx++;
			temp >>= 1;
		}

		if (bit_idx >= K - 5)
			continue;
		
		for (register int k = 0;k < 21;++k)
		{
			cnt = 0;

			if (i & (1 << k))
				break;

			for (register int j = 0;j < N;++j)
			{	
				if ((str_bit[j] & ~(i | (1 << k))) == 0)
					cnt++;
			}	

			ans[i | (1 << k)] = Max(ans[i | (1 << k)], cnt);
			result = Max(result, ans[i | (1 << k)]);
		}
	}

	printf("%d\n", result);
}

int main(void)
{
	input();
	solve();
}