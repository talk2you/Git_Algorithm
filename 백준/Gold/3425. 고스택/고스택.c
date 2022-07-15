#include <stdio.h>

#define MAX_STACK 1003

#define Abs(a)	(((a)<0)?-(a):(a))
#define MAX_VALUE	(int)1E9

int stack[MAX_STACK];
int stack_size;
int N;

// 명령어 셋
typedef struct {
	char cmd;
	int data;
}CMD;
CMD cmd[100003];
int cmd_cnt;

// 명령어 ENUM
enum cmd_list{NUM, POP, INV, DUP, SWP, ADD, SUB, MUL, DIV, MOD};

// 커스텀 strcmp
int mystrcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s2 && *s1) s1++, s2++;
	return *s1 - *s2;
}

// 스택 push
int push(int data)
{
	if (stack_size >= MAX_STACK)
		return -1;

	stack[stack_size++] = data;
	return 1;
}

// 스택 pop
int pop(int *data)
{
	if (stack_size == 0)
		return -1;

	*data = stack[--stack_size];
	return 1;
}

int input()
{
	char temp[5];
	int data;

	cmd_cnt = 0;

	// 입력받은 명령어 저장
	while (1)
	{
		scanf(" %s", temp);

		if (!mystrcmp(temp, "NUM"))
		{
			scanf(" %d", &data);
			cmd[cmd_cnt].cmd = NUM;
			cmd[cmd_cnt].data = data;
		}
		else if (!mystrcmp(temp, "POP"))
			cmd[cmd_cnt].cmd = POP;
		else if (!mystrcmp(temp, "INV"))
			cmd[cmd_cnt].cmd = INV;
		else if (!mystrcmp(temp, "DUP"))
			cmd[cmd_cnt].cmd = DUP;
		else if (!mystrcmp(temp, "SWP"))
			cmd[cmd_cnt].cmd = SWP;
		else if (!mystrcmp(temp, "ADD"))
			cmd[cmd_cnt].cmd = ADD;
		else if (!mystrcmp(temp, "SUB"))
			cmd[cmd_cnt].cmd = SUB;
		else if (!mystrcmp(temp, "MUL"))
			cmd[cmd_cnt].cmd = MUL;
		else if (!mystrcmp(temp, "DIV"))
			cmd[cmd_cnt].cmd = DIV;
		else if (!mystrcmp(temp, "MOD"))
			cmd[cmd_cnt].cmd = MOD;
		else if (!mystrcmp(temp, "END"))
			return 1;
		else if (!mystrcmp(temp, "QUIT"))
			return 2;

		cmd_cnt++;
	}
}

void go_stack(int num)
{
	int temp1=0, temp2=0;
	int error_flag = 0;
	long long l_temp;

	stack_size = 0;
	push(num);

	// 1. pop 했을때 스택에 데이터가 없으면 에러
	for (int i = 0; i < cmd_cnt; i++)
	{
		switch (cmd[i].cmd)
		{
		case NUM:
			push(cmd[i].data);
			break;
		case POP:
			if (pop(&temp1) == -1)
				error_flag = 1;
			break;
		case INV:
			if(pop(&temp1) == -1)
				error_flag = 1;
			push(-temp1);
			break;
		case DUP:
			if (pop(&temp1) == -1)
				error_flag = 1;
			push(temp1);
			push(temp1);
			break;
		case SWP:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			push(temp1);
			push(temp2);
			break;
		case ADD:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			l_temp = temp1;
			l_temp += temp2;
			if (l_temp > MAX_VALUE || l_temp < -MAX_VALUE)
				error_flag = 1;
			else
				push((int)l_temp);
			break;
		case SUB:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			l_temp = temp2;
			l_temp -= temp1;
			if (l_temp > MAX_VALUE || l_temp < -MAX_VALUE)
				error_flag = 1;
			else
				push((int)l_temp);
			break;
		case MUL:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			l_temp = temp1;
			l_temp *= temp2;
			if (l_temp > MAX_VALUE || l_temp < -MAX_VALUE)
				error_flag = 1;
			else
				push((int)l_temp);
			break;
		case DIV:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			// 2. DIV 0으로 나눌수 없을때 ERROR
			if (temp1 == 0)
				error_flag = 1;
			else
				push(temp2 /= temp1);
			break;
		case MOD:
			if (pop(&temp1) == -1)
				error_flag = 1;
			if (pop(&temp2) == -1)
				error_flag = 1;
			// 3. MOD 0으로 나눌수 없을때 ERROR
			if (temp1 == 0)
				error_flag = 1;
			else
				push(temp2 %= temp1);
			break;
		}

		if (error_flag)
		{
			printf("ERROR\n");
			return;
		}
	}

	// 4. 스택에 데이터가 2개 이상일때 ERROR
	if (stack_size > 1)
	{
		printf("ERROR\n");
		return;
	}

	if (pop(&temp1) == -1)
	{
		printf("ERROR\n");
		return;
	}
	// 5. 최대값이 1E9를 넘을때 ERROR
	if (temp1 > MAX_VALUE)
	{
		printf("ERROR\n");
		return;
	}

	printf("%d\n", temp1);
}

void solve()
{
	int data;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &data);
		go_stack(data);
	}

	printf("\n");
}

int main(void)
{
	int flag;

	while (1)
	{
		flag = input();

		if (flag == 1)
			solve();
		else
			break;
	}

	return 0;
}