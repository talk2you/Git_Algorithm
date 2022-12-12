#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s1[1000003];
char s2[1000003];

int fail[1000003] = { 0 };

int result[1000003];
int result_size;

int main()
{
	int n, m;

	gets(s1);
	gets(s2);

	//scanf("%[^\n]s", s1);
	//scanf(" %[^\n]s", s2);

	n = strlen(s1);
	m = strlen(s2);

	for (int i = 1, j = 0; i < m; i++) 
	{
		while (j && s2[i] != s2[j]) 
			j = fail[j - 1];
		if (s2[i] == s2[j]) 
			fail[i] = ++j;
	}

	for (int i = 0, j = 0; i < n; i++) 
	{
		while (j && s1[i] != s2[j]) 
			j = fail[j - 1];

		if (s1[i] == s2[j]) 
		{
			if (j == m - 1) 
			{
				result[result_size++] = i - m + 2;
				j = fail[j];
			}
			else 
				j++;
		}
	}

	printf("%d\n", result_size);
	for (int i = 0; i < result_size; i++)
		printf("%d ", result[i]);
	printf("\n");

	return 0;
}