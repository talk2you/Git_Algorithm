#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100003
#define Max(a, b) ((a>b)?(a):(b))

char num[10];
int len;
int K;
int ans;

typedef struct NODE{
	char n[10];
	struct NODE *next;
}NODE;
NODE pool[100003];
NODE hash[100003];
int pool_size;

typedef struct {
	char n[10];
}QUE;
QUE que[100003];
int front, end;
int que_size;

int isFull()
{
	int temp = front - 1;
	if (temp < 0)
		temp += MAX_SIZE;

	if (temp == end)
		return 1;
	return 0;
}

int isEmpty()
{
	if (front == end)
		return 1;
	return 0;
}

int push(char n[10])
{
	if (isFull())
		return 0;

	que_size++;
	strcpy(que[end].n, n);
	end++;
	end %= MAX_SIZE;
	return 1;
}

int pop(char n[10])
{
	if (isEmpty())
		return 0;

	que_size--;
	strcpy(n, que[front].n);
	front++;
	front %= MAX_SIZE;
	return 1;
}

int make_hash(char n[10])
{
	int h = 5381;
	int i = 0;
	
	while (n[i])
		h += ((h << 5) + h + n[i++]) % MAX_SIZE;
	h %= MAX_SIZE;

	return h;
}

int add_hash(char n[10])
{
	int h = make_hash(n);

	NODE *nd = &hash[h];
	while (nd->next)
	{
		nd = nd->next;

		if (strcmp(nd->n, n) == 0)
			return 0;
	}

	strcpy(pool[pool_size].n, n);
	pool[pool_size].next = hash[h].next;
	hash[h].next = &pool[pool_size++];
	return 1;
}

void input()
{
	scanf("%s", num);
	scanf("%d", &K);
	len = strlen(num);
}

int myAtoi(char n[10])
{
	int temp = 0;
	int ten = 1;
	char temp_n[10];
	strcpy(temp_n, n);

	for (int i = len-1; i >= 0; i--)
	{
		temp += ((temp_n[i] - '0')*ten);
		ten *= 10;
	}
	return temp;
}

void solve()
{
	char n[10];
	push(num);

	for (int i = 0; i < K; i++)
	{ 
		int q_size = que_size;
		pool_size = 0;
		memset(hash, 0, sizeof(hash));

		for (int j = 0; j < q_size; j++)
		{
			pop(n);
			
			for (int k = 0; k < len-1; k++)
			{
				for (int l = k + 1; l < len; l++)
				{
					if (!(k == 0 && n[l] == '0'))
					{
						char temp = n[k];
						n[k] = n[l];
						n[l] = temp;

						if (add_hash(n) == 0)
						{
							temp = n[k];
							n[k] = n[l];
							n[l] = temp;
							continue;
						}

						push(n);

						temp = n[k];
						n[k] = n[l];
						n[l] = temp;
					}
				}
			}
		}
	}

	while (pop(n))
		ans = Max(ans, myAtoi(n));
	
	if (ans == 0)
		printf("-1\n");
	else
		printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
}