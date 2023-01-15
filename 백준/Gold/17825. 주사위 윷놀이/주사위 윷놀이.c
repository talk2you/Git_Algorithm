#include <stdio.h>
#include <string.h>

#define MAX(a, b)	(a>b)?(a):(b)

int dice[10];
int ans = 0;

typedef struct NODE{
	int score;
	struct NODE *next;
	struct NODE *shortcut;
}NODE;
NODE node[100];
NODE *horse[4];

void init()
{
	// 말들은 초기에 node[0] 주소를 갖는다
	for (int i = 0; i < 4; i++)
		horse[i] = &node[0];

	// 노드 점수와 다음으로 이동할 노드의 주소 초기화
	for (int i = 0; i <= 20; i++)
	{
		node[i].score = i * 2;
		node[i].next = &node[i + 1];
	}
	// 도착지점
	node[21].score = -1;

	// 지름길
	node[5].shortcut = &node[30];
	node[10].shortcut = &node[40];
	node[15].shortcut = &node[50];

	// 첫번째 루트
	node[30].score = 10;
	node[31].score = 13;
	node[32].score = 16;
	node[33].score = 19;
	node[30].next = &node[31];
	node[31].next = &node[32];
	node[32].next = &node[33];
	node[33].next = &node[60];

	// 두번째 루트
	node[40].score = 20;
	node[41].score = 22;
	node[42].score = 24;
	node[40].next = &node[41];
	node[41].next = &node[42];
	node[42].next = &node[60];

	// 세번째 루트
	node[50].score = 30;
	node[51].score = 28;
	node[52].score = 27;
	node[53].score = 26;
	node[50].next = &node[51];
	node[51].next = &node[52];
	node[52].next = &node[53];
	node[53].next = &node[60];

	// 모이는 루트
	node[60].score = 25;
	node[61].score = 30;
	node[62].score = 35;
	node[60].next = &node[61];
	node[61].next = &node[62];
	node[62].next = &node[20];
}

void input()
{
	for (int i = 0; i < 10; i++)
		scanf("%d", &dice[i]);
}

// 백트래킹
void bt_yoot(int stage, int t_score, NODE* prev_horse[4])
{
	ans = MAX(ans, t_score);

	if (stage == 10)
		return;

	for (int i = 0; i < 4; i++)
	{
		NODE *t_horse[4];
		NODE *ptr;
		int exist_horse = 0;

		// 이전 말 위치 임시저장소로 복사
		memcpy(t_horse, prev_horse, sizeof(NODE*) * 4);
		ptr = t_horse[i];

		// 말이 도착지점에 도착한 상태라면 패스
		if (ptr == &node[21])
			continue;

		// 주사위 개수만큼 말 이동
		for (int j = 0; j < dice[stage]; j++)
		{
			if (ptr == &node[21])
				break;
			ptr = ptr->next;
		}

		// 지름길 처리
		if (ptr->shortcut != NULL)
			ptr = ptr->shortcut;		

		// 말 이동했을때 다른 말위치랑 중복 되는지 확인
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				continue;
			if (ptr == t_horse[j] && t_horse[j] != &node[21])
			{
				exist_horse = 1;
				break;
			}
		}

		// 다른 말 위치랑 중복 되면 패스
		if (exist_horse)
			continue;

		// 말 위치 업데이트
		t_horse[i] = ptr;
		int next_score = t_score;
		
		// 말 업데이트된 위치가 도착지점이 아니면 점수 덧셈
		if (ptr != &node[21])
			next_score += ptr->score;

		// 백트래킹 ㄱㄱ
		bt_yoot(stage + 1, next_score, t_horse);

		// 이전 말 위치가 0이면 끗
		if (prev_horse[i] == &node[0])
			break;
	}
}

void solve()
{
	bt_yoot(0, 0, horse);
	printf("%d\n", ans);
}

int main(void)
{
	init();
	input();
	solve();
}