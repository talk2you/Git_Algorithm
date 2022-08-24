#include <stdio.h>

char str[3];

void input()
{
	double ans = 0;
	scanf("%s", str);

	switch (str[0])
	{
	case 'A':
		ans = 4.0;
		break;
	case 'B':
		ans = 3.0;
		break;
	case 'C':
		ans = 2.0;
		break;
	case 'D':
		ans = 1.0;
		break;
	default: // F
		printf("%.1f\n", ans);
		return;
	}

	switch (str[1])
	{
	case '+':
		ans += 0.3;
		break;
	case '0':
		break;
	case '-':
		ans -= 0.3;
		break;
	}

	printf("%.1f\n", ans);
}

int main(void)
{
	input();
}