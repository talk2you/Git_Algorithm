#include <stdio.h>

int T, N;

typedef struct CUBE{
	char a[9];
}CUBE;
CUBE cube[6];

enum face{up, down, left, front, right, behind};
char dir[6][8] = { "up", "down", "left","front","right","behind" };

void init_cube(enum face m, char c)
{
	for (int i = 0; i < 9; i++)
		cube[m].a[i] = c;
}

void init()
{
	init_cube(up, 'w');
	init_cube(down, 'y');
	init_cube(front, 'r');
	init_cube(behind, 'o');
	init_cube(left, 'g');
	init_cube(right, 'b');
}

void print_cube()
{
	for (int i = 0; i < 6; i++)
	{
		printf("%s\n", dir[i]);
		printf("%c %c %c\n", cube[i].a[1], cube[i].a[2], cube[i].a[3]);
		printf("%c %c %c\n", cube[i].a[8], cube[i].a[0], cube[i].a[4]);
		printf("%c %c %c\n", cube[i].a[7], cube[i].a[6], cube[i].a[5]);
		printf("--------------------\n");
	}
}

void roll_a(enum face m, char dir)
{
	char temp;

	for (int j = 0; j < 2; j++)
	{
		if (dir == '+')
		{
			temp = cube[m].a[8];
			for (int i = 0; i < 7; i++)
				cube[m].a[8 - i] = cube[m].a[7 - i];
			cube[m].a[1] = temp;
		}
		else
		{
			temp = cube[m].a[1];
			for (int i = 0; i < 7; i++)
				cube[m].a[1 + i] = cube[m].a[2 + i];
			cube[m].a[8] = temp;
		}
	}
}

void cell_copy(char dst[9], int d1, int d2, int d3, char src[9], int s1, int s2, int s3)
{
	dst[d1] = src[s1];
	dst[d2] = src[s2];
	dst[d3] = src[s3];
}

void excute_cmd(char cmd, char dir)
{
	char temp_row[9];

	if (cmd == 'F')
	{
		roll_a(front, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 7, 6, 5);
			cell_copy(cube[up].a, 7, 6, 5, cube[left].a, 5, 4, 3);
			cell_copy(cube[left].a, 5, 4, 3, cube[down].a, 3, 2, 1);
			cell_copy(cube[down].a, 3, 2, 1, cube[right].a, 1, 8, 7);
			cell_copy(cube[right].a, 1, 8, 7, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 7, 6, 5);
			cell_copy(cube[up].a, 7, 6, 5, cube[right].a, 1, 8, 7);
			cell_copy(cube[right].a, 1, 8, 7, cube[down].a, 3, 2, 1);
			cell_copy(cube[down].a, 3, 2, 1, cube[left].a, 5, 4, 3);
			cell_copy(cube[left].a, 5, 4, 3, temp_row, 0, 1, 2);
		}
	}
	else if (cmd == 'R')
	{
		roll_a(right, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 5, 4, 3);
			cell_copy(cube[up].a, 5, 4, 3, cube[front].a, 5, 4, 3);
			cell_copy(cube[front].a, 5, 4, 3, cube[down].a, 5, 4, 3);
			cell_copy(cube[down].a, 5, 4, 3, cube[behind].a, 1, 8, 7);
			cell_copy(cube[behind].a, 1, 8, 7, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 5, 4, 3);
			cell_copy(cube[up].a, 5, 4, 3, cube[behind].a, 1, 8, 7);
			cell_copy(cube[behind].a, 1, 8, 7, cube[down].a, 5, 4, 3);
			cell_copy(cube[down].a, 5, 4, 3, cube[front].a, 5, 4, 3);
			cell_copy(cube[front].a, 5, 4, 3, temp_row, 0, 1, 2);
		}
	}
	else if (cmd == 'L')
	{
		roll_a(left, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 1, 8, 7);
			cell_copy(cube[up].a, 1, 8, 7, cube[behind].a, 5, 4, 3);
			cell_copy(cube[behind].a, 5, 4, 3, cube[down].a, 1, 8, 7);
			cell_copy(cube[down].a, 1, 8, 7, cube[front].a, 1, 8, 7);
			cell_copy(cube[front].a, 1, 8, 7, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[up].a, 1, 8, 7);
			cell_copy(cube[up].a, 1, 8, 7, cube[front].a, 1, 8, 7);
			cell_copy(cube[front].a, 1, 8, 7, cube[down].a, 1, 8, 7);
			cell_copy(cube[down].a, 1, 8, 7, cube[behind].a, 5, 4, 3);
			cell_copy(cube[behind].a, 5, 4, 3, temp_row, 0, 1, 2);
		}
	}
	else if (cmd == 'U')
	{
		roll_a(up, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[front].a, 1, 2, 3);
			cell_copy(cube[front].a, 1, 2, 3, cube[right].a, 1, 2, 3);
			cell_copy(cube[right].a, 1, 2, 3, cube[behind].a, 1, 2, 3);
			cell_copy(cube[behind].a, 1, 2, 3, cube[left].a, 1, 2, 3);
			cell_copy(cube[left].a, 1, 2, 3, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[front].a, 1, 2, 3);
			cell_copy(cube[front].a, 1, 2, 3, cube[left].a, 1, 2, 3);
			cell_copy(cube[left].a, 1, 2, 3, cube[behind].a, 1, 2, 3);
			cell_copy(cube[behind].a, 1, 2, 3, cube[right].a, 1, 2, 3);
			cell_copy(cube[right].a, 1, 2, 3, temp_row, 0, 1, 2);
		}
	}
	else if (cmd == 'D')
	{
		roll_a(down, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[front].a, 7, 6, 5);
			cell_copy(cube[front].a, 7, 6, 5, cube[left].a, 7, 6, 5);
			cell_copy(cube[left].a, 7, 6, 5, cube[behind].a, 7, 6, 5);
			cell_copy(cube[behind].a, 7, 6, 5, cube[right].a, 7, 6, 5);
			cell_copy(cube[right].a, 7, 6, 5, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[front].a, 7, 6, 5);
			cell_copy(cube[front].a, 7, 6, 5, cube[right].a, 7, 6, 5);
			cell_copy(cube[right].a, 7, 6, 5, cube[behind].a, 7, 6, 5);
			cell_copy(cube[behind].a, 7, 6, 5, cube[left].a, 7, 6, 5);
			cell_copy(cube[left].a, 7, 6, 5, temp_row, 0, 1, 2);
		}
	}
	else if (cmd == 'B')
	{
		roll_a(behind, dir);

		if (dir == '+')
		{
			cell_copy(temp_row, 0, 1, 2, cube[right].a, 3, 4, 5);
			cell_copy(cube[right].a, 3, 4, 5, cube[down].a, 5, 6, 7);
			cell_copy(cube[down].a, 5, 6, 7, cube[left].a, 7, 8, 1);
			cell_copy(cube[left].a, 7, 8, 1, cube[up].a, 1, 2, 3);
			cell_copy(cube[up].a, 1, 2, 3, temp_row, 0, 1, 2);
		}
		else
		{
			cell_copy(temp_row, 0, 1, 2, cube[right].a, 3, 4, 5);
			cell_copy(cube[right].a, 3, 4, 5, cube[up].a, 1, 2, 3);
			cell_copy(cube[up].a, 1, 2, 3, cube[left].a, 7, 8, 1);
			cell_copy(cube[left].a, 7, 8, 1, cube[down].a, 5, 6, 7);
			cell_copy(cube[down].a, 5, 6, 7, temp_row, 0, 1, 2);
		}
	}
}

void input()
{
	char cmd[5];
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf(" %s", cmd);
		excute_cmd(cmd[0], cmd[1]);
	}

	//print_cube();
	
	printf("%c%c%c\n", cube[up].a[1], cube[up].a[2], cube[up].a[3]);
	printf("%c%c%c\n", cube[up].a[8], cube[up].a[0], cube[up].a[4]);
	printf("%c%c%c\n", cube[up].a[7], cube[up].a[6], cube[up].a[5]);
	
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		init();
		input();
	}
}