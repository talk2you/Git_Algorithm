#include <stdio.h>
#include <string.h>

#define LEN 110

char apple[LEN];
char diff[LEN];

char claudia[LEN];
char natalia[LEN];

void str_substract(char res[LEN], char a[LEN], char b[LEN])
{
	strcpy(res, a);
	int len1 = strlen(res);
	int len2 = strlen(b);

	int i = len1 - 1;
	int j = len2 - 1;

	while (j >= 0)
	{
		res[i] -= b[j];
		res[i] += '0';

		if (res[i] < '0')
		{
			int k = i - 1;
			while (k >= 0)
			{
				res[k]--;
				res[k + 1] += 10;

				if (res[k] < '0')
					k--;
				else
					break;
			}
		}

		i--, j--;
	}
}

void str_2divide(char res[LEN], char a[LEN])
{
	strcpy(res, a);
	
	int len = strlen(res);
	int flag = 0;
	int temp;

	for (int i = 0; i < len; i++)
	{
		temp = 0;
		if (flag)
			temp = 10;
		temp += (res[i] - '0');
		
		if (res[i] % 2)
			flag = 1;
		else
			flag = 0;

		res[i] = temp / 2 + '0';
	}
}

void str_sum(char res[LEN], char a[LEN], char b[LEN])
{
	char temp[LEN] = { 0, };
	strcpy(res, a);
	int len1 = strlen(res);
	int len2 = strlen(b);

	int i = len1 - 1;
	int j = len2 - 1;
	int flag = 0;

	while (j >= 0)
	{
		res[i] += b[j];
		res[i] -= '0';

		if (res[i] > '9')
		{
			int k = i - 1;
			while (1)
			{
				if (k >= 0)
				{
					res[k]++;
					res[k + 1] -= 10;

					if (res[k] > '9')
						k--;
					else
						break;
				}
				else
				{
					flag = 1;
					break;
				}
			}
		}

		i--, j--;
	}

	if (flag)
		temp[0] = '1';
	strcat(temp, res);
}

void str_print(char str[LEN])
{
	int len = strlen(str);
	int start = 0;

	for (int i = 0; i < len; i++)
	{
		if (start == 0 && str[i] == '0')
			continue;
		else
			start = 1;

		printf("%c", str[i]);
	}
	printf("\n");
}

void input()
{
	char res[LEN];

	scanf("%s %s", apple, diff);
	
	str_substract(res, apple, diff);
	strcpy(apple, res);
	str_2divide(res, apple);
	strcpy(natalia, res);

	str_sum(res, natalia, diff);
	strcpy(claudia, res);

	str_print(claudia);
	str_print(natalia);
}

int main(void)
{
	input();
}