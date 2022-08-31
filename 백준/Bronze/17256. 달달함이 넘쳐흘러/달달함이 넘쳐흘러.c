#include <stdio.h>

typedef struct {
	int x, y, z;
}CAKE;
CAKE a, b, c;

void input()
{
	scanf("%d %d %d", &a.x, &a.y, &a.z);
	scanf("%d %d %d", &c.x, &c.y, &c.z);
	printf("%d %d %d\n", c.x - a.z, c.y / a.y, c.z - a.x);
}

int main(void)
{
	input();
}