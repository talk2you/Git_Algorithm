#include <stdio.h>
#include <string.h>

char A[10004];
char B[10004];
char temp_swap[10004];
char temp[10005];

void input()
{
	scanf("%s %s", A, B);
}

void str_add(char a[10003], char b[10003])
{
	int len1 = strlen(a);
	int len2 = strlen(b);

	int i = len1-1, j = len2-1;
	int k = 0;
	int add = 0;

	while (1)
	{
		char t;

		t = a[i--] + b[j--] - '0' + add;
		add = 0;

		if (t > '9')
		{
			t -= 10;
			add++;
		}

		temp[k++] = t;

		if (i < 0)
		{
			while (j >= 0)
			{
				t = b[j--] + add;
				add = 0;

				if (t > '9')
				{
					t -= 10;
					add++;
				}
				temp[k++] = t;
			}
			break;
		}
		else if (j < 0)
		{
			while (i >= 0)
			{
				t = a[i--] + add;
				add = 0;

				if (t > '9')
				{
					t -= 10;
					add++;
				}
				temp[k++] = t;
			}
			break;
		}
	}

	if (add)
		temp[k++] = '1';
}

void str_sub(char a[1003], char b[1003])
{
	int len1 = strlen(a);
	int len2 = strlen(b);

	int i = len1 - 1;
	int j = len2 - 1;
	int k = 0;
	int l = 0;

	while (j >= 0)
	{
		a[i] = a[i] - b[j] + '0';
		
		k = i;
		while (a[k] < '0')
		{
			a[k - 1]--;
			a[k] += 10;
			k--;
		}
		temp[l++] = a[i];

		i--, j--;
	}

	while (i >= 0)
		temp[l++] = a[i--];

}

void solve()
{
	// - -
	if (A[0] == '-' && B[0] == '-')
	{
		str_add(&A[1], &B[1]);
		printf("-");

		int len = strlen(temp);
		for (int i = len-1; i >= 0; i--)
			printf("%c", temp[i]);
		printf("\n");
	}
	// - +
	else if (A[0] == '-')
	{
		int len1 = strlen(&A[1]);
		int len2 = strlen(B);

		if (len1 > len2)
		{
			str_sub(&A[1], B);
			printf("-");
		}
		else if (len1 < len2)
			str_sub(B, &A[1]);
		else
		{
			int cmp = strcmp(&A[1], B);
			if (cmp < 0)
				str_sub(B, &A[1]);
			else if(cmp > 0)
			{
				str_sub(&A[1], B);
				printf("-");
			}
			else
			{
				printf("0\n");
				return;
			}
		}

		int len = strlen(temp);
		int start = 0;
		for (int i = len - 1; i >= 0; i--)
		{
			if (temp[i] == '0' && start == 0)
				continue;
			else
				start = 1;

			printf("%c", temp[i]);
		}
		printf("\n");
	}
	// + -
	else if (B[0] == '-')
	{
		strcpy(temp_swap, A);
		strcpy(A, B);
		strcpy(B, temp_swap);

		int len1 = strlen(&A[1]);
		int len2 = strlen(B);

		if (len1 > len2)
		{
			str_sub(&A[1], B);
			printf("-");
		}
		else if (len1 < len2)
			str_sub(B, &A[1]);
		else
		{
			int cmp = strcmp(&A[1], B);
			if (cmp < 0)
				str_sub(B, &A[1]);
			else if (cmp > 0)
			{
				str_sub(&A[1], B);
				printf("-");
			}
			else
			{
				printf("0\n");
				return;
			}
		}

		int len = strlen(temp);
		int start = 0;
		for (int i = len - 1; i >= 0; i--)
		{
			if (temp[i] == '0' && start == 0)
				continue;
			else
				start = 1;

			printf("%c", temp[i]);
		}
		printf("\n");
	}
	// + +
	else
	{
		str_add(A, B);

		int len = strlen(temp);
		for (int i = len - 1; i >= 0; i--)
			printf("%c", temp[i]);
		printf("\n");
	}
}

int main(void)
{
	input();
	solve();
}